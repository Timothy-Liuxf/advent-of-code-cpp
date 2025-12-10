bin_PROGRAMS += build/bin/year2025/day7
build_bin_year2025_day7_SOURCES =                                              \
    src/year2025/day7/main.cc                                                  \
    ${NOTHING}
build_bin_year2025_day7_LDADD =                                                \
    build/lib/libutils.a                                                       \
    -l@CXXFS@                                                                  \
    ${NOTHING}
