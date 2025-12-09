noinst_HEADERS +=                                                              \
    %reldir%/common.hpp                                                        \
    %reldir%/io.hpp                                                            \
    %reldir%/cmd.hpp                                                           \
    ${NOTHING}

noinst_LIBRARIES += build/lib/libutils.a
build_lib_libutils_a_SOURCES =                                                 \
    %reldir%/io.cc                                                             \
    %reldir%/cmd.cc                                                            \
    ${NOTHING}
