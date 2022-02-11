
#include <iostream>
#include <fmt/core.h>
#include <fmt/color.h>
#include "config.hpp"
#include "repos.hpp"

const auto CYAN = fmt::color::cyan;
const auto BLUE = fmt::terminal_color::bright_blue; 
const auto RED = fmt::terminal_color::bright_red;
const auto GREEN = fmt::terminal_color::bright_green;
const auto BOLD = fmt::emphasis::bold;

int main(int argc, char *argv[]) {
    repos::config::Config config = repos::config::parse(argc, argv);

    if (config.skip) {
        return 0;
    } else {
        fmt::print(fg(BLUE) | BOLD, "{} Version: {}.\n", repos::config::BANNER, repos::config::APP_VERSION);

        config = repos::scan_folders(config);
        fmt::print(fg(CYAN), "Repo count: {}\n", config.folders.size());
        int errors = repos::process(config);

        if (errors != 0) {
            fmt::print(fg(RED) | BOLD, "{} errors.\n", errors);
        } else {
            fmt::print(fg(GREEN) | BOLD, "{} errors.\n", errors);
        }

        return errors;
    }
}
