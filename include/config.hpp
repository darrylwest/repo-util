
//
// Created by Darryl West on 2022-02-10 13:06:59
//

#pragma once
#ifndef REPO_CONFIG_HPP
#define REPO_CONFIG_HPP

#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <filesystem>
#include "cxxopts.hpp"

namespace repos {
    const char* APP_VERSION = "22.2.16";
    const char* BANNER = "Repository Maintenance Utilities © 2022 Rain City Software";

    namespace config {
        namespace fs = std::filesystem;

        struct Config {
            std::string name;
            std::string repo_home = ".repo-utils";
            std::string config_file = "config.json";
            std::string cmd = "pull";
            std::vector<fs::path> folders;
            // op : pull, new branch, switch branch, merge to release
            bool skip = false;
        };

        Config parse(int argc, char* argv[]) {
            Config config;

            config.name = std::string(argv[0]);

            try {
                cxxopts::Options options(config.name, BANNER);

                options.add_options()
                    ("v,version", "Show the current version")
                    ("h,help", "Show this help")
                    ("c,command", "The command to run on all repos", cxxopts::value<std::string>())
                    ("config", "The configuration file", cxxopts::value<std::string>());

                auto result = options.parse(argc, argv);

                if (result.count("version")) {
                    std::cout << config.name << " Version: " << APP_VERSION << std::endl;
                    config.skip = true;
                }

                if (result.count("help")) {
                    std::cout << options.help() << std::endl;
                    config.skip = true;
                }

                if (result.count("command")) {
                    config.cmd = result["command"].as<std::string>();
                }

                if (result.count("config")) {
                    config.config_file = result["config"].as<std::string>();
                }
            } catch (const cxxopts::OptionException& e) {
                std::cout << "error parsing options: " << e.what() << std::endl;
                config.skip = true;
            }

            return config;
        }
    }
}

#endif
