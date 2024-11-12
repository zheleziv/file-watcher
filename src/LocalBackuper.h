#pragma once

#include "Backuper/Interface.h"

namespace NFileWatcher {
    struct TLocalBackuper final : public NBackuper::Interface {
        void Save(
                const std::string &path
        ) final;

        void Backup() final;

        ~TLocalBackuper() override;

    private:
        std::string TargetPath;
        std::string SavePath;
    };
}
