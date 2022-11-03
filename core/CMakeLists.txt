cmake_minimum_required(VERSION 3.4)
project("beyondhorizon")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_library(log-lib log)
find_package(game-activity REQUIRED CONFIG)

add_library(beyondhorizon SHARED
    source/init.cc
    source/logging.cc

    source/android/logging.cc

    source/android/main.cpp
    source/android/AndroidOut.cpp
    source/android/Renderer.cpp
    source/android/Shader.cpp
    source/android/TextureAsset.cpp
    source/android/Utility.cpp
)

target_include_directories(beyondhorizon PRIVATE include)
target_link_libraries(beyondhorizon
    android
    game-activity::game-activity
    EGL GLESv3
    jnigraphics
    ${log-lib}
)
