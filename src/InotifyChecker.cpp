#include "InotifyChecker.h"

#include <stdexcept>
#include <unistd.h>

#include <sys/poll.h>
#include "sys/inotify.h"


#define MAX_EVENTS 1
#define POLL_TIMEOUT 100

using namespace NFileWatcher;

void TInotifyChecker::Init(
        const std::string &path,
        NChecker::EEvent event
) noexcept(false) {
    InotifyFd = inotify_init();
    if (InotifyFd < 0) {
        InotifyFd = 0;
        throw std::runtime_error("Couldn't initialize inotify");
    }

    InotifyWd = inotify_add_watch(
            InotifyFd,
            path.c_str(),
            EventToMask(event)
    );
    if (InotifyWd < 0) {
        InotifyFd = 0;
        InotifyWd = 0;
        throw std::runtime_error("Couldn't add watch to " + path);
    }
    Event = event;
}

TInotifyChecker::~TInotifyChecker() {
    if (InotifyFd > 0 && InotifyWd > 0)
        inotify_rm_watch(InotifyFd, InotifyWd);
}

uint64_t TInotifyChecker::EventToMask(NChecker::EEvent event) {
    switch (event) {
        case NChecker::EEvent::OnModified:
            return IN_MODIFY;
        case NChecker::EEvent::OnOpen:
            return IN_OPEN;
        case NChecker::EEvent::OnClose:
            return IN_CLOSE;
        case NChecker::EEvent::OnCreate:
            return IN_CREATE;
        case NChecker::EEvent::OnDelete:
            return IN_DELETE;
        default:
            return IN_MODIFY; // throw / log warning ?
    }
}

bool TInotifyChecker::Check() noexcept {
    if (InotifyFd < 0 || InotifyWd < 0)
        return false;

    uint bufSize = MAX_EVENTS * (sizeof(struct inotify_event) + Path.size());
    char buffer[bufSize];


    struct pollfd pfd = { InotifyFd, POLLIN, 0 };
    auto ret = poll(&pfd, 1, POLL_TIMEOUT);
    if(!ret)
        return false;

    auto length = read(InotifyFd, buffer, bufSize);

    uint32_t counter = 0;
    while (counter < length) {
        auto event = (struct inotify_event *) &buffer[counter];

        if (event->mask & EventToMask(Event))
            return true;

        counter += sizeof(struct inotify_event) + event->len;
    }
    return false;
}
