# consider allowing find_package as an option for existing Catch2 on system.
include(FetchContent)
FetchContent_Declare(
    Catch2 
    GIT_REPOSITORY "https://github.com/catchorg/Catch2.git"
    GIT_TAG        "v3.5.2"
)
FetchContent_MakeAvailable(Catch2)

set(TEST_FILES
    test_sdk.cpp
)

add_executable(tests ${TEST_FILES})
target_include_directories(craft_sdk PUBLIC include)

# if(WIN32)
target_link_libraries(tests craft_sdk Catch2::Catch2)
# endif()

include(CTest)
include(Catch)

catch_discover_tests(tests WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
