#pragma once

#include "Checker/Interface.h"

namespace NFileWatcher {
    struct TInotifyChecker final: public NChecker::Interface {
        void Init(
                const std::string& path,
                NChecker::EEvent event
        ) noexcept(false) final;

        bool Check() noexcept final;

        ~TInotifyChecker() override;

    private:
        static uint64_t EventToMask(NChecker::EEvent event);

        std::string Path;
        int InotifyFd{0};
        int InotifyWd{0};
        NChecker::EEvent Event;
    };
} // NFileWatcher
