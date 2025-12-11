bin_PROGRAMS += build/bin/year2025/day11
build_bin_year2025_day11_SOURCES =                                              \
    src/year2025/day11/main.cc                                                  \
    ${NOTHING}
build_bin_year2025_day11_LDADD =                                                \
    build/lib/libutils.a                                                       \
    -l@CXXFS@                                                                  \
    ${NOTHING}
