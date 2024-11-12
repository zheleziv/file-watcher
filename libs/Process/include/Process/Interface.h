#pragma once

#include <cstdint>

namespace NProcess{
    typedef uint64_t ProcessID;

    struct Interface{
        virtual ~Interface() {};

        virtual void Run() = 0;

        virtual void Stop() = 0;

        virtual void Join() = 0;

        virtual bool IsRunning() const = 0;

        virtual ProcessID GetId() {return (ProcessID)this;};
    };
}