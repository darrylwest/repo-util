
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
        auto results = repos::process(config);

        for (auto result : results) {

            if (result.errors != 0) {
                fmt::print(fg(RED) | BOLD, "{}\n", result.to_string());
                fmt::print(fg(RED) | BOLD, "{} errors.\n", result.errors);
            } else {
                fmt::print(BOLD, "{}", result.to_string());
            }
        }

    }

    return 0;
}
