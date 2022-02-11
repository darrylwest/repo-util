
#include <iostream>
#include <fmt/core.h>
#include <fmt/color.h>
#include "config.hpp"
#include "repos.hpp"

const fmt::color CYAN = fmt::color::cyan;
const fmt::color FUCHSIA = fmt::color::fuchsia;
const fmt::terminal_color BLUE = fmt::terminal_color::bright_blue;
const fmt::terminal_color RED = fmt::terminal_color::bright_red;
const fmt::terminal_color GREEN = fmt::terminal_color::bright_green;

int main(int argc, char *argv[]) {
    repos::config::Config config = repos::config::parse(argc, argv);

    if (config.skip) {
        return 0;
    } else {
        fmt::print(fg(BLUE), "{} Version: {}.\n", repos::config::BANNER, repos::config::APP_VERSION);

        config = repos::scan_folders(config);
        fmt::print(fg(CYAN), "Repo count: {}\n", config.folders.size());
        int errors = repos::process(config);

        if (errors != 0) {
            fmt::print(fg(RED), "{} errors.\n", errors);
        } else {
            fmt::print(fg(GREEN), "{} errors.\n", errors);
        }

        return errors;
    }
}
