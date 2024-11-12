#include <boost/program_options.hpp>
#include <iostream>
#include <csignal>
#include <thread>
#include "src/Configurator.h"

using namespace boost::program_options;

std::shared_ptr<NProcess::TManager> ProcManager;

void exception_handler (int sg)
{
    std::cout << std::endl;
    if (ProcManager){
        ProcManager->Stop();
    }
}

int main(int argc, char **argv) {
    std::string config_file{"./config.json"};
    signal (SIGTERM, exception_handler);
    signal (SIGKILL, exception_handler);
    signal (SIGINT, exception_handler);

    options_description generic("General options");
    generic.add_options()
            ("help, h", "Print help message")
            ("config_file, c",
                    value<std::string>(&config_file)->value_name("config_file"),
                    "Set path to config file");
    options_description all("Help menu");
    all.add(generic);

    try {
        variables_map vm;
        command_line_parser parser{argc, argv};
        parsed_options parsed = parser
                .options(all)
                .style(
                        command_line_style::default_style |
                        command_line_style::allow_slash_for_short
                        )
                .allow_unregistered()
                .run();

        store(parsed, vm);
        notify(vm);

        if (vm.count("help")) {
            std::cout <<  std::endl;
            all.print(std::cout);
            return 0;
        }

        // main process
        ProcManager = NFileWatcher::Configurator(config_file);
        ProcManager->Run();
        ProcManager->Join();
    }
    catch (const std::exception &exc) {
        std::cerr << "Error:\t" << exc.what() << std::endl;
    }
    return 0;
}