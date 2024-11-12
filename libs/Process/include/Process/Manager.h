#pragma once

#include "Interface.h"

#include <memory>
#include <list>
#include <mutex>

namespace NProcess {
    struct TManager : public Interface{
        ~TManager() override;

        ProcessID Add(
                const std::shared_ptr<Interface> &process
        );

        bool Delete(
                ProcessID id
        );

        void Run() override;

        void Stop() override;

        void Join() override;

        bool IsRunning() const override;

    private:
        std::mutex Mutex;
        std::list<std::shared_ptr<Interface>> Processes;
        bool Running{false};
    };
}