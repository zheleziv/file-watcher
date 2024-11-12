#pragma once

#include <string>
#include "Process/Manager.h"

namespace NFileWatcher{
    extern std::shared_ptr<NProcess::TManager> Configurator(
            const std::string& pathToConfig
    );
}


