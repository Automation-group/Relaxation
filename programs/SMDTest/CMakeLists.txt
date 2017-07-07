PROJECT (SMDTest)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
find_package(lfDevices REQUIRED)
find_package(QextSerialPort REQUIRED)

include(${QT_USE_FILE})

include_directories(${QLFDEVICES_INCLUDE_DIR} )

include_directories(${QEXTSERIALPORT_INCLUDE_DIR})

if(WIN32)
  add_definitions(-D_TTY_WIN_)
else(WIN32)
  add_definitions(-D_TTY_POSIX_)
endif(WIN32)

link_libraries(
   ${QT_QTCORE_LIBRARY}
   ${QT_QTGUI_LIBRARY}
   ${QLFDEVICES_LIBRARY}
   ${QEXTSERIALPORT_LIBRARY}
)
 
add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_PLUGIN)
add_definitions(-DQT_NO_DEBUG)
add_definitions(-DQT_SHARED)
#add_definitions(-DQT_NO_KEYWORDS)

aux_source_directory(src SOURCES)
file(GLOB HEADERS src/*.h)
file(GLOB QTUI ui/*.ui)
file(GLOB QTRESOURCES rc/*.qrc)

qt4_wrap_cpp(mocSOURCES ${HEADERS})
qt4_wrap_ui(UI ${QTUI})
qt4_add_resources(RESOURCES ${QTRESOURCES})

add_executable(SMDTest ${SOURCES} ${mocSOURCES} ${RESOURCES} ${MATRIXHEADERS} ${UI})
target_link_libraries(SMDTest ${QT_LIBRARIES})
            
#FIND_PACKAGE(Subversion)
#IF(Subversion_FOUND)
#    Subversion_WC_INFO(${PROJECT_SOURCE_DIR} Project)
#    MESSAGE("Current revision is ${Project_WC_REVISION}")
#ENDIF(Subversion_FOUND)

#CPack section

#IF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
#    SET(CPACK_GENERATOR "DEB")
#    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Lab5 Step motor driver test program.")
#    SET(CPACK_PACKAGE_VENDOR "lab5")
#    SET(CPACK_PACKAGE_VERSION_MAJOR "0")
#    SET(CPACK_PACKAGE_VERSION_MINOR "1")
#    SET(CPACK_PACKAGE_VERSION_PATCH "${Project_WC_REVISION}")
#    SET(CPACK_PACKAGE_INSTALL_DIRECTORY "SMDTest ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
#    SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt4-gui (>= 4.4.0-4)")
#    SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "lexaficus@list.ru")
    # List executables
#    INCLUDE(CPack)
#ENDIF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake") 

