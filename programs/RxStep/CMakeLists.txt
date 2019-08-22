project (RxStep)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

if(UNIX)
    set(CMAKE_INSTALL_PREFIX "/usr")
endif(UNIX)

set(RXSTEP_BIN bin
    CACHE PATH "Location of RxStep binaries.")

set(RXSTEP_CONF local/etc/lab5
    CACHE PATH "Location of RxStep configuration files.")

mark_as_advanced(RXSTEP_BIN 
                 RXSTEP_CONF)


find_package(Qt4 REQUIRED)

if(QT4_FOUND)
    include(${QT_USE_FILE})
else(QT4_FOUND)
    message(FATAL_ERROR "Could not find Qt4")
endif(QT4_FOUND)

find_package(lfDevices REQUIRED)
find_package(QextSerialPort REQUIRED)
find_package(Qwt REQUIRED)
find_package(QRlxLib REQUIRED)
use_qrlxlib()

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(include ${CMAKE_BINARY_DIR} ${QEXTSERIALPORT_INCLUDE_DIR} Qwt ${QWT_INCLUDE_DIR})

link_libraries(
   ${QT_QTCORE_LIBRARY}
   ${QT_QTGUI_LIBRARY}
   ${QWT_LIBRARIES}
   ${QLFDEVICES_LIBRARY}
   ${QEXTSERIALPORT_LIBRARY}
   ${QWT_LIBRARY}
)
 
add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_PLUGIN)
add_definitions(-DQT_NO_DEBUG)
add_definitions(-DQT_SHARED)
add_definitions(-DQT_NO_KEYWORDS)
if(WIN32)
  add_definitions(-D_TTY_WIN_)
else(WIN32)
  add_definitions(-D_TTY_POSIX_)
endif(WIN32)

file(MAKE_DIRECTORY moc)
file(MAKE_DIRECTORY qrc)
file(MAKE_DIRECTORY uiheaders)

aux_source_directory(src SOURCES)

file(GLOB HEADERS include/*.h)
file(GLOB QTUI ui/*.ui)
file(GLOB QTRESOURCES rc/*.qrc)

qt4_wrap_cpp(mocSOURCES ${HEADERS})
qt4_wrap_ui(UI ${QTUI})
qt4_add_resources(RESOURCES ${QTRESOURCES})

add_executable(rxstep ${SOURCES} ${mocSOURCES} ${RESOURCES} ${UI})

#INSTALL


install(TARGETS rxstep
    RUNTIME DESTINATION ${RXSTEP_BIN}
    PERMISSIONS OWNER_EXECUTE OWNER_READ
                GROUP_EXECUTE GROUP_READ
                WORLD_EXECUTE WORLD_READ)
                
install(FILES rxstep.conf 
        DESTINATION ${RXSTEP_CONF}
        COMPONENT resources)
        
set(RXCONFIG_FILENAME "${CMAKE_INSTALL_PREFIX}/${RXSTEP_CONF}/rxstep.conf")
        
configure_file(${CMAKE_SOURCE_DIR}/CMakeModules/RxConfig.h.cmake
    ${CMAKE_BINARY_DIR}/RxConfig.h)
                
#END INSTALL

#find_package(Subversion)
#if(Subversion_FOUND)
#  file(RELATIVE_PATH REPO_PATH ${CMAKE_BINARY_DIR} ${PROJECT_SOURCE_DIR})
#  subversion_wc_info(${REPO_PATH} Project)
#  message("Current revision is ${Project_WC_REVISION}")
#endif(Subversion_FOUND)
                
#CPack section

if(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
    set(CPACK_GENERATOR "DEB")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Lab5 relaxation test system")
    set(CPACK_PACKAGE_VENDOR "lab5")
    set(CPACK_PACKAGE_VERSION_MAJOR "1")
    set(CPACK_PACKAGE_VERSION_MINOR "0")
    #set(CPACK_PACKAGE_VERSION_PATCH "${Project_WC_REVISION}")
    set(CPACK_PACKAGE_VERSION_PATCH "0.4")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "rxstep ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
    #SET(CPACK_SOURCE_PACKAGE_FILE_NAME "gdcm-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt4-designer (>= 4.4.0-4), libqwt5-qt4 (>= 5.1.1-1), zip")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "vedddd@gmail.com")
    # List executables
    include(CPack)
endif(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake") 

set(UPLOAD_HOST srvlab5ld)
set(UPLOAD_USERNAME aapavlyukov)
set(UPLOAD_DEST_DIR /home/ftp/Distr/APT)


include(CreateUploadScripts)
create_upload_script()
