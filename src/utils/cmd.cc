#include "cmd.hpp"

#include <cstdint>
#include <format>
#include <print>
#include <stdexcept>
#include <string>
#include <string_view>

#include <tclap/CmdLine.h>

#include <common/common.hpp>
#include <utils/io.hpp>

ADVENT_OF_CODE_CPP_UTILS_NAMESPACE_BEGIN

void SolveProblemFromArgs(int argc, char* argv[], const std::string& title,
                          std::function<std::string(std::uint64_t, std::string_view)> solver) {
    TCLAP::CmdLine cmd(title, ' ', PACKAGE_VERSION);

    TCLAP::ValueArg<std::uint64_t> part_arg("p", "part", "Part number", false, 1, "1 or 2");
    cmd.add(part_arg);

    TCLAP::ValueArg<std::filesystem::path> file_arg("f", "file", "Path to input file", false, ".", "path");
    cmd.add(file_arg);

    TCLAP::ValueArg<std::string> url_arg("u", "url", "URL to input file", false, ".", "url");
    cmd.add(url_arg);

    cmd.parse(argc, argv);

    auto part = part_arg.getValue();
    if (part != 1 && part != 2) {
        throw std::invalid_argument(std::format("Part number can only be 1 or 2, got: {}", part));
    }

    std::string result;
    if (url_arg.isSet()) {
        auto content = utils::GetContentsFromUrl(url_arg.getValue());
        result       = solver(part, content);
    } else if (file_arg.isSet()) {
        auto content = utils::GetContentsFromFile(file_arg.getValue());
        result       = solver(part, content);
    } else {
        throw std::invalid_argument("Either --file or --url must be specified.");
    }
    std::println(std::cout, "Answer of Part {}: {}", part_arg.getValue(), result);
}

ADVENT_OF_CODE_CPP_UTILS_NAMESPACE_END
