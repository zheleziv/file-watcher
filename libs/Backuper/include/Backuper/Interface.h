#pragma once

#include <string>

namespace NBackuper{
    struct Interface{
        virtual ~Interface() {};

        /**
         * @brief Сохранить данные
         */
        virtual void Save(
                const std::string& path
        ) = 0;

        /**
         * @brief Восстановить данные
         */
        virtual void Backup() = 0;
    };
}