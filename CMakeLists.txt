cmake_minimum_required(VERSION 3.5)
project(WindowHandler CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

# Output config
set(OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Exe path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${OUTPUT_DIRECTORY}")

# Lib path
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}/archive")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}/archive")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${OUTPUT_DIRECTORY}/archive")

# Compile flags
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -std=c++17 -Xclang -fcxx-exceptions /fp:fast /arch:AVX -flto -fwhole-program-vtables -Xclang -O0")
	add_definitions(-DDEBUG)
else()
 	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -std=c++17 -Xclang -fcxx-exceptions /fp:fast /arch:AVX -flto -fwhole-program-vtables -Xclang -O3")
	add_definitions(-DNDEBUG)
endif()

message(STATUS "Using ${CMAKE_CXX_COMPILER_ID} in ${CMAKE_BUILD_TYPE} mode")
message(STATUS "Flags: ${CMAKE_CXX_FLAGS}")

add_subdirectory(${PROJECT_SOURCE_DIR}/deps EXCLUDE_FROM_ALL)

add_library(window_handler SHARED ${PROJECT_SOURCE_DIR}/src/window_handler.cpp)
target_include_directories(window_handler PRIVATE ${PROJECT_SOURCE_DIR}/include
                                                  ${PROJECT_SOURCE_DIR}/deps/glfw/include)
target_link_libraries(window_handler PRIVATE "glfw")
set_target_properties(window_handler PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS} -DWINDOW_HANDLER_DLL_EXPORTS")