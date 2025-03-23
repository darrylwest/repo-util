
//
// Created by Darryl West on 2022-02-10 13:06:59
//

#pragma once

#include <iostream>
#include <vector>
#include <fmt/color.h>

namespace repos::reporter {
    const auto CYAN = fmt::color::cyan;
    const auto BLUE = fmt::terminal_color::bright_blue;
    const auto RED = fmt::terminal_color::bright_red;
    const auto GREEN = fmt::terminal_color::bright_green;
    const auto BOLD = fmt::emphasis::bold;

    inline auto show_header(const std::string &banner, const std::string &version) {
        fmt::print(fg(BLUE) | BOLD, "{} Version: {}.\n", banner, version);
    }

    inline auto show_repo_count(size_t count) {
        fmt::print(BOLD, "Repo count: {}\n", count);
    }

    inline auto show_results(const std::vector<Context> &results) {
        for (const auto &result : results) {
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

