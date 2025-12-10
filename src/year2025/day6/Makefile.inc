bin_PROGRAMS += build/bin/year2025/day6
build_bin_year2025_day6_SOURCES =                                              \
    src/year2025/day6/main.cc                                                  \
    ${NOTHING}
build_bin_year2025_day6_LDADD =                                                \
    build/lib/libutils.a                                                       \
    -l@CXXFS@                                                                  \
    ${NOTHING}
