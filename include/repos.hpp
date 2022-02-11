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

#include "config.hpp"

namespace fs = std::filesystem;

namespace repos {
    /// assume that the script is currently at the root of the repos
    /// use directory iterator to get the list of git repos
    auto scan_folders(config::Config config) {
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

    struct Context {
        fs::path target_repo;
        std::string cmd;
        std::vector<std::string> response;
        int errors = 0;

        std::string to_string() {
            std::string rstr = "";
            for (std::string line : this->response) {
                rstr += line;
            }

            return rstr;
        }
    };

    Context run_command(Context context) {
        auto filename = std::string(context.target_repo.filename());
        context.response.push_back("Run: " + context.cmd + " for " + filename + ": ");

        // write the output to file to enable reassembly after run is complete

        FILE *fp;
        fp = popen(context.cmd.c_str(), "r");

        if (fp == NULL) {
            std::cout << "ERROR! opening pipe" << std::endl;
            context.errors++; 
            return context;
        }

        char buffer[1000];
        while (fgets(buffer, 1000, fp) != NULL) {
            // std::cout << buffer ;
            context.response.push_back(std::string(buffer));
        }

        int status = pclose(fp);
        if (status < 0) {
            std::cout << "ERROR! could not close pipe" << std::endl;
            context.errors++;
        }

        return context;
    }

    int process(config::Config config) {
        int errors = 0;
        std::vector<std::shared_future<Context>> jobs;

        for (auto const& folder : config.folders) {
            const char *path = folder.c_str();
            if (chdir(path) != 0) {
                std::cout << "ERROR! could not change to dir: " << path << std::endl;
                errors++;
            } else {
                Context context;
                context.target_repo = folder;
                context.cmd = std::string("git pull");

                std::shared_future<Context> job = std::async(std::launch::async, run_command, context);

                jobs.push_back(job);
            }
        }

        for (auto job : jobs) {
            Context ctx = job.get();

            errors += ctx.errors;

            std::cout << ctx.to_string();
        }

        return errors;
    }

    void show_config(config::Config config) {
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
