bin_PROGRAMS += build/bin/year2025/day8
build_bin_year2025_day8_SOURCES =                                              \
    src/year2025/day8/main.cc                                                  \
    ${NOTHING}
build_bin_year2025_day8_LDADD =                                                \
    build/lib/libutils.a                                                       \
    -l@CXXFS@                                                                  \
    ${NOTHING}
