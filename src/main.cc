#include <config.h>

#include <iostream>
#include <print>

#include <tclap/CmdLine.h>

int main(int argc, char* argv[]) {
    TCLAP::CmdLine cmd(PACKAGE_NAME, ' ', PACKAGE_VERSION);
    cmd.parse(argc, argv);
    std::println(std::cout, PACKAGE_NAME " version: " PACKAGE_VERSION);
    return 0;
}
