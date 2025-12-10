bin_PROGRAMS += build/bin/year2025/day5
build_bin_year2025_day5_SOURCES =                                              \
    src/year2025/day5/main.cc                                                  \
    ${NOTHING}
build_bin_year2025_day5_LDADD =                                                \
    build/lib/libutils.a                                                       \
    -l@CXXFS@                                                                  \
    ${NOTHING}
