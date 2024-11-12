#include "Task.h"

#include <stdexcept>
#include <iostream>

#include "LocalDirBackuper.h"
#include "InotifyChecker.h"

#include "boost/filesystem.hpp"

#define TIMEOUT_MS 100

using namespace NFileWatcher;

TTask::TTask(const std::string &path) {
    if(path.empty())
        throw std::runtime_error("Path is empty");

    if(!boost::filesystem::exists(path))
        throw std::runtime_error("Target file " + path + " not exists");

    Backuper = std::make_unique<TLocalDirBackuper>();
    Checker = std::make_unique<TInotifyChecker>();

    Path =  boost::filesystem::absolute(path).string();
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
                std::cout << "File " + Path + " was modified." << std::endl;
                Backuper->Backup();
                std::cout << "File " + Path +  " was restored from backup." << std::endl;
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

