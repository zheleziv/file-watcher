#include "Configurator.h"

#include "Task.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>

std::shared_ptr<NProcess::TManager> NFileWatcher::Configurator(
        const std::string& pathToConfig
){
    if(!boost::filesystem::exists(pathToConfig))
        throw std::runtime_error("Config file " + pathToConfig + " not exists");

    auto manager = std::make_shared<NProcess::TManager>();

    boost::property_tree::ptree data;
    boost::property_tree::json_parser::read_json(pathToConfig, data);

    if(!data.count("files"))
        throw std::runtime_error("Bad config file " + pathToConfig + " no \"files\" value");

    for(auto file : data.get_child("files")){
        auto task = std::make_shared<NFileWatcher::TTask>(file.second.data());
        manager->Add(task);
    }

    return manager;
};
