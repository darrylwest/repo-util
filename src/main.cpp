
#include <iostream>
#include "config.hpp"
#include "repos.hpp"

int main(int argc, char *argv[]) {
    repos::config::Config config = repos::config::parse(argc, argv);

    // TODO : move this part to process module to enable unit tests...
    if (config.skip) {
        return 0;
    } else {
        std::cout << repos::config::BANNER << ", Version: " << repos::config::APP_VERSION << std::endl;

        config = repos::scan_folders(config);
        std::cout << "Repo count: " << config.folders.size() << std::endl;
        repos::process(config);

        return 0;
    }

    return 0;
}
