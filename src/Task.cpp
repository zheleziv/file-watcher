#include "Task.h"

#include <stdexcept>
#include <iostream>

#include "LocalBackuper.h"
#include "InotifyChecker.h"

using namespace NFileWatcher;

#define TIMEOUT_MS 100

TTask::TTask(const std::string &path) {
    if(path.empty()) {
        throw std::runtime_error("Path is empty");
    }

    Backuper = std::make_unique<TLocalBackuper>();
    Checker = std::make_unique<TInotifyChecker>();

    Path = path;
    std::cout <<"Add monitoring file: " << Path << std::endl;
}

void NFileWatcher::TTask::Run() {
    std::lock_guard<std::mutex> lock(Mutex);
    if(Running) return;

    Running = true;
    Thread = std::thread([this] {
        Backuper->Save(Path);

        while(Running) {
            Checker->Init(
                    Path,
                    NChecker::EEvent::OnModified
            );

            bool modified = false;

            while(Running && !modified){
                modified = Checker->Check();
                std::this_thread::sleep_for(
                        std::chrono::milliseconds(TIMEOUT_MS)
                        );
            }
            if(Running && modified) {
                std::cout << "File " + Path + " was modified!" << std::endl;
                Backuper->Backup();
                std::cout << "The file was restored from backup" << std::endl;
            }
        }
    });
}

void NFileWatcher::TTask::Stop() {
    std::lock_guard<std::mutex> lock(Mutex);
    Running = false;
}

void NFileWatcher::TTask::Join() {
    if(Thread.joinable()) {
        Thread.join();
    }
}

bool TTask::IsRunning() const {
    return Running;
}

