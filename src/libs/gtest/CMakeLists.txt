set(SRCS src/gtest-all.cc)
set(DEFINES GTEST_HAS_EXCEPTIONS=0 GTEST_HAS_RTTI=0)
cp_add_library(LIB gtest SRCS ${SRCS} CFLAGS "-Wno-sign-compare" DEFINES ${DEFINES})
include_directories("${ROOT_DIR}/src/libs/gtest" "${ROOT_DIR}/src/libs/gtest/include")
