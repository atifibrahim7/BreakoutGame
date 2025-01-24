# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

include(FetchContent)
set(SFML_VERSION 2.6.1)
set(BUILD_SHARED_LIBS FALSE)

FetchContent_Declare(
    sfml 
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG        "${SFML_VERSION}"
)

FetchContent_MakeAvailable(sfml)

set(SDK_FILES
    src/sdk/window.cpp
    include/sdk/window.h
    src/sdk/input.cpp
    include/sdk/input.h
)

message("sfml_SOURCE_DIR ${sfml_SOURCE_DIR}")
message("sfml_BINARY_DIR ${sfml_BINARY_DIR}")
message("SFML_DIR ${SFML_DIR}")

# no need to find_package() with FetchContent_MakeAvailable.
# since versions matter, it's better to always Fetch from github

add_library(craft_sdk STATIC ${SDK_FILES})
target_include_directories(craft_sdk PUBLIC include)

if (${MACOSX})
target_link_libraries(craft_sdk PRIVATE sfml-graphics)
elseif(UNIX)
target_link_libraries(craft_sdk PRIVATE sfml-graphics)
else()
target_link_libraries(craft_sdk PRIVATE sfml-main sfml-graphics)
endif()
