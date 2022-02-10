
#include <iostream>
#include "repo.hpp"

int main(int argc, char *argv[]) {
    repo::Config config = repo::parse(argc, argv);

    // TODO : move this part to process module to enable unit tests...
    if (config.skip) {
        return 0;
    } else {
        std::cout << repo::BANNER << ", Version: " << repo::APP_VERSION << std::endl;

        config = repo::scan_folders(config);
        std::cout << "Folder count: " << config.folders.size() << std::endl;
        repo::process(config);

        return 0;
    }

    return 0;
}
