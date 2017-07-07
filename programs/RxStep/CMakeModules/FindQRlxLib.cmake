find_path(QRLXLIB_INCLUDE_DIR QRlxData.h
../QRlxLib/src
${QRLXLIB_INCLUDE_DIR}
${QRLXLIB_DIR}/src
)

if(NOT QRLXLIB_INCLUDE_DIR)
  message(FATAL_ERROR "QRlxData not found. Use cmake -DQRLXLIB_DIR=QRlxLibDirectory")
endif(NOT QRLXLIB_INCLUDE_DIR)

find_library(QRLXLIB_LIBRARY qrlx
../QRlxLib/
${QRLXLIB_LIB_DIR}
${QRLXLIB_DIR}
)

if(NOT QRLXLIB_LIBRARY)
  message(FATAL_ERROR "QRlxLib library not found. Use cmake -DQRLXLIB_DIR=QRlxLibDirectory")
endif(NOT QRLXLIB_LIBRARY)

macro (USE_QRLXLIB)
    include_directories(${QRLXLIB_INCLUDE_DIR})
    link_libraries(${QRLXLIB_LIBRARY})
endmacro (USE_QRLXLIB)
