AC_DEFUN([AX_CXX_COMPILE_STDCXX_EX], [
  m4_bmatch([$1],
    [^\(11\|14\|17\|20\)$], [AX_CXX_COMPILE_STDCXX([$1], [$2], [$3])],
    [_AX_CXX_COMPILE_STDCXX_EX([$1], [$2], [$3])]
  )
])

AC_DEFUN([_AX_CXX_COMPILE_STDCXX_EX], [dnl
  m4_if([$1], [23], [ax_cxx_compile_alternatives="23 2b"],
        [$1], [26], [ax_cxx_compile_alternatives="26 2c"],
        [m4_fatal([invalid first argument `$1' to AX_CXX_COMPILE_STDCXX_EX])])dnl
  m4_if([$2], [], [],
        [$2], [ext], [],
        [$2], [noext], [],
        [m4_fatal([invalid second argument `$2' to AX_CXX_COMPILE_STDCXX_EX])])dnl
  m4_if([$3], [], [ax_cxx_compile_cxx$1_required=true],
        [$3], [mandatory], [ax_cxx_compile_cxx$1_required=true],
        [$3], [optional], [ax_cxx_compile_cxx$1_required=false],
        [m4_fatal([invalid third argument `$3' to AX_CXX_COMPILE_STDCXX_EX])])
  AC_LANG_PUSH([C++])dnl
  ac_success=no

  m4_if([$2], [], [dnl
    AC_CACHE_CHECK(whether $CXX supports C++$1 features by default,
		   ax_cv_cxx_compile_cxx$1,
      [AC_COMPILE_IFELSE([AC_LANG_SOURCE([_AX_CXX_COMPILE_STDCXX_testbody_$1])],
        [ax_cv_cxx_compile_cxx$1=yes],
        [ax_cv_cxx_compile_cxx$1=no])])
    if test x$ax_cv_cxx_compile_cxx$1 = xyes; then
      ac_success=yes
    fi])

  m4_if([$2], [noext], [], [dnl
  if test x$ac_success = xno; then
    for alternative in ${ax_cxx_compile_alternatives}; do
      echo $alternative
      switch="-std=gnu++${alternative}"
      cachevar=AS_TR_SH([ax_cv_cxx_compile_cxx$1_$switch])
      AC_CACHE_CHECK(whether $CXX supports C++$1 features with $switch,
                     $cachevar,
        [ac_save_CXX="$CXX"
         CXX="$CXX $switch"
         AC_COMPILE_IFELSE([AC_LANG_SOURCE([_AX_CXX_COMPILE_STDCXX_testbody_$1])],
          [eval $cachevar=yes],
          [eval $cachevar=no])
         CXX="$ac_save_CXX"])
      if eval test x\$$cachevar = xyes; then
        CXX="$CXX $switch"
        if test -n "$CXXCPP" ; then
          CXXCPP="$CXXCPP $switch"
        fi
        ac_success=yes
        break
      fi
    done
  fi])

  m4_if([$2], [ext], [], [dnl
  if test x$ac_success = xno; then
    dnl HP's aCC needs +std=c++11 according to:
    dnl http://h21007.www2.hp.com/portal/download/files/unprot/aCxx/PDF_Release_Notes/769149-001.pdf
    dnl Cray's crayCC needs "-h std=c++11"
    dnl MSVC needs -std:c++NN for C++17 and later (default is C++14)
    for alternative in ${ax_cxx_compile_alternatives}; do
      for switch in -std=c++${alternative} +std=c++${alternative} "-h std=c++${alternative}" MSVC; do
        if test x"$switch" = xMSVC; then
          dnl AS_TR_SH maps both `:` and `=` to `_` so -std:c++17 would collide
          dnl with -std=c++17.  We suffix the cache variable name with _MSVC to
          dnl avoid this.
          switch=-std:c++${alternative}
          cachevar=AS_TR_SH([ax_cv_cxx_compile_cxx$1_${switch}_MSVC])
        else
          cachevar=AS_TR_SH([ax_cv_cxx_compile_cxx$1_$switch])
        fi
        AC_CACHE_CHECK(whether $CXX supports C++$1 features with $switch,
                       $cachevar,
          [ac_save_CXX="$CXX"
           CXX="$CXX $switch"
           AC_COMPILE_IFELSE([AC_LANG_SOURCE([_AX_CXX_COMPILE_STDCXX_testbody_$1])],
            [eval $cachevar=yes],
            [eval $cachevar=no])
           CXX="$ac_save_CXX"])
        if eval test x\$$cachevar = xyes; then
          CXX="$CXX $switch"
          if test -n "$CXXCPP" ; then
            CXXCPP="$CXXCPP $switch"
          fi
          ac_success=yes
          break
        fi
      done
      if test x$ac_success = xyes; then
        break
      fi
    done
  fi])
  AC_LANG_POP([C++])
  if test x$ax_cxx_compile_cxx$1_required = xtrue; then
    if test x$ac_success = xno; then
      AC_MSG_ERROR([*** A compiler with support for C++$1 language features is required.])
    fi
  fi
  if test x$ac_success = xno; then
    HAVE_CXX$1=0
    AC_MSG_NOTICE([No compiler with C++$1 support was found])
  else
    HAVE_CXX$1=1
    AC_DEFINE(HAVE_CXX$1,1,
              [define if the compiler supports basic C++$1 syntax])
  fi
  AC_SUBST(HAVE_CXX$1)
])

m4_define([_AX_CXX_COMPILE_STDCXX_testbody_88],
  _AX_CXX_COMPILE_STDCXX_testbody_new_in_11
)

m4_define([_AX_CXX_COMPILE_STDCXX_testbody_23],
  _AX_CXX_COMPILE_STDCXX_testbody_new_in_11
  _AX_CXX_COMPILE_STDCXX_testbody_new_in_14
  _AX_CXX_COMPILE_STDCXX_testbody_new_in_17
  _AX_CXX_COMPILE_STDCXX_testbody_new_in_20
  _AX_CXX_COMPILE_STDCXX_testbody_new_in_23
)

m4_define([_AX_CXX_COMPILE_STDCXX_testbody_26],
  _AX_CXX_COMPILE_STDCXX_testbody_new_in_11
  _AX_CXX_COMPILE_STDCXX_testbody_new_in_14
  _AX_CXX_COMPILE_STDCXX_testbody_new_in_17
  _AX_CXX_COMPILE_STDCXX_testbody_new_in_20
  _AX_CXX_COMPILE_STDCXX_testbody_new_in_23
  _AX_CXX_COMPILE_STDCXX_testbody_new_in_26
)

dnl  Tests for new features in C++23

m4_define([_AX_CXX_COMPILE_STDCXX_testbody_new_in_23], [[

#ifndef __cplusplus

#error "This is not a C++ compiler"

#elif __cplusplus < 202302L && !defined _MSC_VER

#error "This is not a C++23 compiler"

#else

#include <version>

#endif  // __cplusplus < 202302L && !defined _MSC_VER

]])

dnl  Tests for new features in C++26

m4_define([_AX_CXX_COMPILE_STDCXX_testbody_new_in_26], [[

#ifndef __cplusplus

#error "This is not a C++ compiler"

#elif __cplusplus < 202400L && !defined _MSC_VER

#error "This is not a C++26 compiler"

#else

#include <version>

#endif  // __cplusplus < 202400L && !defined _MSC_VER

]])

m4_include([third_party/autoconf-archive/m4/ax_cxx_compile_stdcxx.m4])
