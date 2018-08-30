PROJECT(authz)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
ADD_DEFINITIONS(-std=c++11
    -DBOOST_LOG_DYN_LINK
)
SET(CMAKE_BUILE_TYPE DEBUG)
SET(CMAKE_C_FLAGS_DEBUG "-g -Wall")
SET(CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols")

FIND_PACKAGE(Boost REQUIRED COMPONENTS
    regex
    filesystem
    log
    log_setup
)

IF(NOT Boost_FOUND)
    message("Not found Boost")
ENDIF()

message("${Boost_INCLUDE_DIRS}")
message("${Boost_LIBRARIES}")

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/ ${Boost_INCLUDE_DIRS})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/lib ${PROJECT_SOURCE_DIR}/third_party/libevent/lib/)

AUX_SOURCE_DIRECTORY(. DIR_SRCS)
SET(SOURCES ${DIR_SRCS})

ADD_EXECUTABLE(main ${SOURCES})
TARGET_LINK_LIBRARIES(main
    pthread
    boost_system
    boost_filesystem
    boost_log_setup
    boost_log
    boost_thread
)
