#pragma once

#include "Process/Interface.h"
#include "Backuper/Interface.h"
#include "Checker/Interface.h"

#include <thread>
#include <memory>
#include <mutex>

namespace NFileWatcher{
    struct TTask final : public NProcess::Interface {
        TTask(
                const std::string& path
        );

        void Run() override;

        void Stop() override;

        void Join() override;

        bool IsRunning() const override;

    private:
        std::mutex Mutex;
        std::string Path;
        std::thread Thread;
        std::unique_ptr<NBackuper::Interface> Backuper;
        std::unique_ptr<NChecker::Interface> Checker;
        volatile bool Running{false};
    };
}

