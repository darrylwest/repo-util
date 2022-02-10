
#include <iostream>
#include "repo.hpp"

int main(int argc, char *argv[]) {
    repo::Config config = repo::parse(argc, argv);

    // TODO : move this part to process module to enable unit tests...
    if (config.skip) {
        return 0;
    } else {
        std::cout << repo::BANNER << ", Version: " << repo::APP_VERSION << std::endl;

        auto conf = scan_folders(config);

        repo::show_config(conf);

        return 0;
    }

    return 0;
}
