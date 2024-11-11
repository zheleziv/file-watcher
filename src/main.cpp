#include <boost/program_options.hpp>
#include <iostream>

using namespace boost::program_options;

int main(int argc, char **argv) {
    std::string config_file{"./config.ini"};

    options_description generic("General options");
    generic.add_options()
            ("config_file, c", value<std::string>(&config_file)->value_name("config_file"), "Set path to config file");
    options_description all("Help menu");
    all.add(generic);

    try {
        variables_map vm;
        command_line_parser parser{argc, argv};
        parsed_options parsed = parser.options(all).style(
                command_line_style::default_style |
                command_line_style::allow_slash_for_short).allow_unregistered().run();

        store(parsed, vm);
        notify(vm);

        if (vm.count("help")) {
            std::cout <<  std::endl;
            all.print(std::cout);
            return 0;
        }

        // main execution


    }
    catch (const std::exception &exc) {
        std::cout << "Error:\t" << exc.what() << std::endl;
    }
    return 0;
}