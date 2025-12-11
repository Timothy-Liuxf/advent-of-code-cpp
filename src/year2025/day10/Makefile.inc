bin_PROGRAMS += build/bin/year2025/day10
build_bin_year2025_day10_SOURCES =                                             \
    src/year2025/day10/main.cc                                                 \
    ${NOTHING}
build_bin_year2025_day10_LDADD =                                               \
    build/lib/libutils.a                                                       \
    -l@CXXFS@                                                                  \
    ${NOTHING}
