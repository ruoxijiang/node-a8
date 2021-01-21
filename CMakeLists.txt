cmake_minimum_required(VERSION 3.10)
project(a8)
set(CMAKE_CXX_STANDARD 14)

OPTION(DEBUG_SQLITE_IN_MAC "Debug sqlite lib in Mac OS" OFF)

message(STATUS PROJECT_SOURCE_DIR:${PROJECT_SOURCE_DIR})
message(STATUS CMAKE_SYSTEM_NAME:${CMAKE_SYSTEM_NAME})
message(STATUS CMAKE_CXX_COMPILER:${CMAKE_CXX_COMPILER})
message(STATUS CMAKE_OSX_SYSROOT:${CMAKE_OSX_SYSROOT})
message(STATUS ANDROID:${ANDROID},APPLE:${APPLE},IOS:${IOS},WIN32:${WIN32},UNIX:${UNIX})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-function -Wno-unused-variable")

set(CPP_HEADERS ${PROJECT_SOURCE_DIR}/lib/vendor/headers/include ${PROJECT_SOURCE_DIR}/lib/vendor/headers/thirdparty/curlcpp/include)
include_directories(${CPP_HEADERS})
#Node Native configs
include_directories(${CMAKE_JS_INC})
file(GLOB ADDON_SRC_FILES ${PROJECT_SOURCE_DIR}/lib/addon/**.cpp)
add_library(addon SHARED ${ADDON_SRC_FILES} ${CMAKE_JS_SRC})
set_target_properties(addon PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(addon ${CMAKE_JS_LIB} ${PROJECT_SOURCE_DIR}/lib/vendor/liba8.a)
set(NODE_ADDON_API_DIR ${PROJECT_SOURCE_DIR}/node_modules/node-addon-api)
message(NODE_API_DIR:${NODE_ADDON_API_DIR})
target_include_directories(addon PRIVATE ${NODE_ADDON_API_DIR})

# define NPI_VERSION
add_definitions(-DNAPI_VERSION=4)

#Adding additional libraries
find_package(CURL)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    target_link_libraries(addon ${CURL_LIBRARIES} curl)
else ()
    message(STATUS "Could not find CURL")
endif (CURL_FOUND)
target_link_libraries(addon ${PROJECT_SOURCE_DIR}/lib/vendor/libedo-dns.a ${PROJECT_SOURCE_DIR}/lib/vendor/libsqlite3d.a)
