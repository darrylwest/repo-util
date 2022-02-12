
#include <iostream>
#include <fmt/core.h>
#include <fmt/color.h>

#include "repos.hpp"
#include "config.hpp"
#include "reporter.hpp"


int main(int argc, char *argv[]) {
    repos::config::Config config = repos::config::parse(argc, argv);

    if (config.skip) {
        return 0;
    } else {
        repos::reporter::show_header(repos::BANNER, repos::APP_VERSION);

        config = repos::scan_folders(config);
        auto results = repos::process(config);
        repos::reporter::show_results(results);
    }

    return 0;
}
