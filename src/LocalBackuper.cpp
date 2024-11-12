#include <iostream>
#include "LocalBackuper.h"

#include "boost/filesystem.hpp"

#define SAVE_DIR "./backup/"

using namespace NFileWatcher;

void TLocalBackuper::Backup() {
    if(!boost::filesystem::exists(SavePath))
        throw std::runtime_error("Backup file " + SavePath + " not exists");

    if(boost::filesystem::exists(TargetPath))
        boost::filesystem::remove(TargetPath);

    boost::filesystem::copy(SavePath, TargetPath);
}

void TLocalBackuper::Save(const std::string &path) {
    if(!boost::filesystem::exists(path))
        throw std::runtime_error("Target file " + path + " not exists");

    if(!boost::filesystem::exists(SAVE_DIR))
        if(!boost::filesystem::create_directory(SAVE_DIR))
            throw std::runtime_error("Cannot create backup directory: " SAVE_DIR);

    auto savePath = SAVE_DIR + boost::filesystem::path(path).filename().string();

    if(boost::filesystem::exists(savePath))
        boost::filesystem::remove(savePath);

    boost::filesystem::copy(path, savePath);

    TargetPath = path;
    SavePath = savePath;
}

TLocalBackuper::~TLocalBackuper() {
    std::cout << "Deleting backup: " << SavePath << std::endl;
    if(boost::filesystem::exists(SavePath))
        boost::filesystem::remove(SavePath);
    if(boost::filesystem::is_empty(SAVE_DIR))
        boost::filesystem::remove(SAVE_DIR);
}
