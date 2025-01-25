cmake_minimum_required(VERSION 3.11)
project(Craftout)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
    message("CMAKE_OSX_SYSROOT: ${CMAKE_OSX_SYSROOT}")
endif()

set(SRC_FILES
    src/main.cpp
    src/Paddle.h 
    src/Ball.h
    src/Brick.h
    # List the source files that you add here
)

set(CMAKE_CXX_STANDARD 17)
if (${MACOSX})
    set(CMAKE_CXX_FLAGS "-stdlib=libc++")
endif()

add_subdirectory(sdk)
enable_testing()
add_subdirectory(test)

add_executable(${CMAKE_PROJECT_NAME} WIN32 ${SRC_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} craft_sdk)
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
message("Current VS work directory: ${CMAKE_SOURCE_DIR}")

install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION bin)




