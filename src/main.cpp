//
// Created by Darryl West on 2022-02-10 13:06:59
//

#include <iostream>

#define FMT_HEADER_ONLY
#include "fmt/format.h"

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
        repos::reporter::show_repo_count(config.folders.size());

        auto results = repos::process(config);
        repos::reporter::show_results(results);
    }

    return 0;
}
