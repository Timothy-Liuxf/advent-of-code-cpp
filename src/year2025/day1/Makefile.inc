bin_PROGRAMS += build/bin/year2025/day1
build_bin_year2025_day1_SOURCES =                                              \
    src/year2025/day1/main.cc                                                  \
    ${NOTHING}
build_bin_year2025_day1_LDADD =                                                \
    build/lib/libutils.a                                                       \
    -l@CXXFS@                                                                  \
    ${NOTHING}
