
#include <iostream>
#include "repo.hpp"

int main(int argc, char *argv[]) {
    repo::Config config = repo::parse(argc, argv);

    // TODO : move this part to process module to enable unit tests...
    if (config.skip) {
        return 0;
    } else {
        std::cout << repo::BANNER << '\n';
        std::cout << "Version: " << repo::APP_VERSION << std::endl;

        // show the complete config...
        std::cout << "Config: name: " << config.name << std::endl;
        std::cout << "Config: home: " << config.repo_home << std::endl;
        std::cout << "Config: file: " << config.config_file << std::endl;

        return 0;
    }

    return 0;
}
