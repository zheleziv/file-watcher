#include <algorithm>
#include <iostream>
#include "Process/Manager.h"

using namespace NProcess;

bool TManager::Delete(ProcessID processId) {
    auto findIter = std::find_if(
            Processes.begin(),
            Processes.end(),
            [processId](const std::shared_ptr<Interface>& s) {
                return s->GetId() == processId;
            }
    );

    if(findIter != Processes.end()){
        Processes.erase(findIter);
        return true;
    }
    return false;
}

ProcessID TManager::Add(const std::shared_ptr<Interface> &process) {
    auto findIter = std::find_if(
            Processes.begin(),
            Processes.end(),
            [process](const std::shared_ptr<Interface>& s) {
                return s->GetId() == process->GetId();
            }
    );

    if(findIter != Processes.end())
        return 0;

    Processes.push_back(process);
    return process->GetId();
}

void TManager::Run() {
    std::lock_guard<std::mutex> lock(Mutex);
    if(Running) return;

    for(auto& process : Processes)
        process->Run();
    Running = true;
}

void TManager::Stop() {
    std::lock_guard<std::mutex> lock(Mutex);
    if(!Running) return;

    for(auto& process : Processes){
        process->Stop();
    }
    Running = false;
}

void TManager::Join() {
    for(auto& process : Processes){
        process->Join();
    }
}

bool TManager::IsRunning() const {
    return Running;
}

TManager::~TManager() {
    Stop();
}
