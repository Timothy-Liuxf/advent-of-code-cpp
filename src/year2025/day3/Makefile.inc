bin_PROGRAMS += build/bin/year2025/day3
build_bin_year2025_day3_SOURCES =                                              \
    src/year2025/day3/main.cc                                                  \
    ${NOTHING}
build_bin_year2025_day3_LDADD =                                                \
    build/lib/libutils.a                                                       \
    -l@CXXFS@                                                                  \
    ${NOTHING}
