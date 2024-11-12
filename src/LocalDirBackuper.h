#pragma once

#include "Backuper/Interface.h"

namespace NFileWatcher {
    struct TLocalDirBackuper final : public NBackuper::Interface {

        /**
         * @brief Копирует файл в локальную директорию
         */
        void Save(
                const std::string &path
        ) final;

        /**
         * @brief Восстанавливает файл из локальной директории
         */
        void Backup() final;

        /**
         * @brief Очистка и удаление локальной директории
         */
        ~TLocalDirBackuper() override;

    private:
        std::string TargetPath;
        std::string SavePath;
    };
}
