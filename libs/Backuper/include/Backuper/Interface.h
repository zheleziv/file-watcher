#pragma once

#include <string>

namespace NBackuper{
    struct Interface{
        virtual ~Interface() {};

        virtual void Save(
                const std::string& path
        ) = 0;

        virtual void Backup() = 0;
    };
}