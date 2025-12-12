bin_PROGRAMS += build/bin/year2025/day12
build_bin_year2025_day12_SOURCES =                                              \
    src/year2025/day12/main.cc                                                  \
    ${NOTHING}
build_bin_year2025_day12_LDADD =                                                \
    build/lib/libutils.a                                                       \
    -l@CXXFS@                                                                  \
    ${NOTHING}
