bin_PROGRAMS += build/bin/advent_of_code_cpp
build_bin_advent_of_code_cpp_SOURCES =                                         \
    %reldir%/main.cc                                                           
    ${NOTHING}

include %reldir%/common/Makefile.inc
include %reldir%/utils/Makefile.inc
include %reldir%/year2025/Makefile.inc
