macro(create_upload_script)    

SET(UPLOAD_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_SYSTEM_NAME}")

    if(UNIX)
        configure_file(${CMAKE_SOURCE_DIR}/CMakeModules/upload.sh.cmake
            ${CMAKE_BINARY_DIR}/upload.sh)
    endif(UNIX)
endmacro(create_upload_script)
