
//
// Created by Darryl West on 2022-02-10 13:06:59
//

#pragma once
#ifndef REPO_REPORTER_HPP
#define REPO_REPORTER_HPP

#include <iostream>
#include <string>
#include <vector>

namespace repos {
    namespace reporter {
        const auto CYAN = fmt::color::cyan;
        const auto BLUE = fmt::terminal_color::bright_blue; 
        const auto RED = fmt::terminal_color::bright_red;
        const auto GREEN = fmt::terminal_color::bright_green;
        const auto BOLD = fmt::emphasis::bold;

        auto show_header(std::string banner, std::string version) {
            fmt::print(fg(BLUE) | BOLD, "{} Version: {}.\n", banner, version);
        }

        auto show_repo_count(int count) {
            fmt::print(BOLD, "Repo count: {}\n", count);
        }

        auto show_results(std::vector<Context> results) {
            for (auto result : results) {
                // TODO write these results to a single log/report file

                if (result.errors != 0) {
                    fmt::print(fg(RED) | BOLD, "{}\n", result.to_string());
                    fmt::print(fg(RED) | BOLD, "{} errors.\n", result.errors);
                } else {
                    fmt::print(BOLD, "{}", result.to_string());
                }
            }
        }
    }
}

#endif
