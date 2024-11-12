#pragma once

#include <string>
#include "Process/Manager.h"

namespace NFileWatcher{

    /**
     * @brief Парсит данные из файла и создает Менеджер потоков для мониторинга состояний файлов
     */
    extern std::shared_ptr<NProcess::TManager> Configurator(
            const std::string& pathToConfig
    );
}


