#pragma once

#include <string>

namespace NChecker {
    enum EEvent {
        OnModified = 0,
        OnOpen,
        OnClose,
        OnCreate,
        OnDelete
        // ...
    };

    struct Interface {
        virtual ~Interface() {}

        virtual void Init(
                const std::string& path,
                EEvent event
        ) = 0;

        virtual bool Check() noexcept = 0;
    };
}