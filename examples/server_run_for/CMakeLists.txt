cmake_minimum_required(VERSION 3.0.0)
project(server)

# Normally, you would want to distribute Findrpclib.cmake
# within your project directory; I wanted to avoid copies
# of this file here, so I'm just setting the CMake module path.
# In your project, you don't need the following line:
#set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake")

find_package(Threads REQUIRED)

option(CMAKE_ENSURE_LOCAL_RPCLIB FALSE)
if (CMAKE_ENSURE_LOCAL_RPCLIB)
	set(RPCLIB_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/../../include")
	set(RPCLIB_LIB_DIR "${PROJECT_SOURCE_DIR}/../../build")
else ()
	message([STATUS] "using installed rpclib. use -DCMAKE_ENSURE_LOCAL_RPCLIB=TRUE to use from local source")
	find_package(rpclib REQUIRED)
endif(CMAKE_ENSURE_LOCAL_RPCLIB)

add_executable(server main.cc)

if (CMAKE_ENSURE_LOCAL_RPCLIB)
	target_include_directories(server PUBLIC ${RPCLIB_INCLUDE_DIR})
	target_link_libraries(server ${RPCLIB_LIB_DIR}/librpc.a)
else ()
	target_link_libraries(server ${RPCLIB_LIBS})
endif(CMAKE_ENSURE_LOCAL_RPCLIB)
target_link_libraries(server Threads::Threads)
set_property(TARGET server PROPERTY CXX_STANDARD 14)

