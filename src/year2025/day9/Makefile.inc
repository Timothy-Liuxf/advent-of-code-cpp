bin_PROGRAMS += build/bin/year2025/day9
build_bin_year2025_day9_SOURCES =                                              \
    src/year2025/day9/main.cc                                                  \
    ${NOTHING}
build_bin_year2025_day9_LDADD =                                                \
    build/lib/libutils.a                                                       \
    -l@CXXFS@                                                                  \
    ${NOTHING}
