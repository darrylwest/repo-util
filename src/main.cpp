
#include <iostream>
#include "config.hpp"
#include "repo.hpp"

int main(int argc, char *argv[]) {
    repo::config::Config config = repo::config::parse(argc, argv);

    // TODO : move this part to process module to enable unit tests...
    if (config.skip) {
        return 0;
    } else {
        std::cout << repo::config::BANNER << ", Version: " << repo::config::APP_VERSION << std::endl;

        config = repo::scan_folders(config);
        std::cout << "Folder count: " << config.folders.size() << std::endl;
        repo::process(config);

        return 0;
    }

    return 0;
}
