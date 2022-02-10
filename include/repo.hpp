//
// Created by Darryl West on 2022-02-10 13:06:59
//

#pragma once
#ifndef REPO_HPP
#define REPO_HPP

#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <future>
#include <filesystem>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "cxxopts.hpp"

namespace fs = std::filesystem;

namespace repo {
    const char* APP_VERSION = "22.2.10";
    const char* BANNER = "Repository Maintenance Utilities © 2022 Rain City Software";

    struct Config {
        std::string name;
        std::string repo_home = ".repo-utils";
        std::string config_file = "config.json";
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
                ("c,config", "The configuration file", cxxopts::value<std::string>());

            auto result = options.parse(argc, argv);

            if (result.count("version")) {
                std::cout << config.name << " Version: " << repo::APP_VERSION << std::endl;
                config.skip = true;
            }

            if (result.count("help")) {
                std::cout << options.help() << std::endl;
                config.skip = true;
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

    /// assume that the script is currently at the root of the repos
    /// use directory iterator to get the list of git repos
    auto scan_folders(Config config) {
        auto cwd = fs::current_path();

        for (auto const& dir : fs::directory_iterator{cwd}) {
            // exclude only if there is a .git folder
            auto file =  fs::path(dir).append(".git");
            if (fs::exists(file)) {
                config.folders.push_back(dir);
            }
        }


        return config;
    }

    int run_command(Config config, std::string cmd) {
        auto home = config.repo_home;

        // write the output to file to enable reassembly after run is complete

        FILE *fp;
        fp = popen(cmd.c_str(), "r");

        if (fp == NULL) {
            std::cout << "ERROR! opening pipe" << std::endl;
            return(-1);
        }

        char buffer[1000];
        while (fgets(buffer, 1000, fp) != NULL) {
            std::cout << buffer ;
        }
        std::cout << std::endl;

        int status = pclose(fp);
        if (status < 0) {
            std::cout << "ERROR! could not close pipe" << std::endl;
        }

        return 0;
    }

    int process(Config config) {
        int errors = 0;
        std::vector<std::shared_future<int>> jobs;

        for (auto const& folder : config.folders) {
            const char *path = folder.c_str();
            if (chdir(path) != 0) {
                std::cout << "ERROR! could not change to dir: " << path << std::endl;
                errors++;
            } else {
                auto cmd = std::string("git pull");
                std::cout << "Run cmd: " << cmd << " for repo: " << path << std::endl;
                std::shared_future<int> job = std::async(std::launch::async, run_command, config, cmd);

                jobs.push_back(job);
            }
        }

        return errors;
    }

    void show_config(Config config) {
        // show the complete config...
        std::cout << "Config: name: " << config.name << std::endl;
        std::cout << "Config: home: " << config.repo_home << std::endl;
        std::cout << "Config: file: " << config.config_file << std::endl;

        for (auto const& dir : config.folders) {
            std::cout << dir << std::endl;
        }
    }
}

#endif
