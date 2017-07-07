project (QRlxLib)

cmake_minimum_required(VERSION 2.6)

find_package(Qt4 REQUIRED)

if(QT4_FOUND)
    include(${QT_USE_FILE})
else(QT4_FOUND)
    message(FATAL_ERROR "Could not find Qt4")
endif(QT4_FOUND)

include_directories(include ${QT_QTXML_INCLUDE_DIR})

link_libraries(
   ${QT_QTCORE_LIBRARY}
   ${QT_QTXML_LIBRARY}
)
 
add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_PLUGIN)
add_definitions(-DQT_NO_DEBUG)
add_definitions(-DQT_SHARED)

#file(MAKE_DIRECTORY moc)

aux_source_directory (src SOURCES)

file(GLOB HEADERS src/*.h)

qt4_wrap_cpp(mocSOURCES ${HEADERS})

add_library(qrlx STATIC ${SOURCES} ${mocSOURCES})
