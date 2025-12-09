bin_PROGRAMS += build/bin/year2025/day2
build_bin_year2025_day2_SOURCES =                                              \
    src/year2025/day2/main.cc                                                  \
    ${NOTHING}
build_bin_year2025_day2_LDADD =                                                \
    build/lib/libutils.a                                                       \
    -l@CXXFS@                                                                  \
    ${NOTHING}
