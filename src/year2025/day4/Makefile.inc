bin_PROGRAMS += build/bin/year2025/day4
build_bin_year2025_day4_SOURCES =                                              \
    src/year2025/day4/main.cc                                                  \
    ${NOTHING}
build_bin_year2025_day4_LDADD =                                                \
    build/lib/libutils.a                                                       \
    -l@CXXFS@                                                                  \
    ${NOTHING}
