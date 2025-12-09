#include "cmd.hpp"

#include <print>
#include <stdexcept>
#include <string>
#include <string_view>

#include <tclap/CmdLine.h>

#include <common/common.hpp>
#include <utils/io.hpp>

ADVENT_OF_CODE_CPP_UTILS_NAMESPACE_BEGIN

void SolveProblemFromArgs(int argc, char** argv, std::function<std::string(std::string_view)> solver) {
    TCLAP::CmdLine cmd(PACKAGE_NAME ": year2025 day1", ' ', PACKAGE_VERSION);

    TCLAP::ValueArg<std::filesystem::path> file_arg("f", "file", "Path to input file", false, ".", "path");
    cmd.add(file_arg);

    TCLAP::ValueArg<std::string> url_arg("u", "url", "URL to input file", false, ".", "url");
    cmd.add(url_arg);

    cmd.parse(argc, argv);

    std::string result;
    if (url_arg.isSet()) {
        auto content = utils::GetContentsFromUrl(url_arg.getValue());
        result       = solver(content);
    } else if (file_arg.isSet()) {
        auto content = utils::GetContentsFromFile(file_arg.getValue());
        result       = solver(content);
    } else {
        throw std::invalid_argument("Either --file or --url must be specified.");
    }
    std::println(std::cout, "{}", result);
}

ADVENT_OF_CODE_CPP_UTILS_NAMESPACE_END
