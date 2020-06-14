cmake_minimum_required(VERSION 3.4.1)

# create variable SOURCES with all file *.cpp into sub-directory native-app
file(GLOB_RECURSE SOURCES "native-app/*.cpp")

add_library(native-lib SHARED ${SOURCES})

find_library( # Sets the name of the path variable.
        log-lib
        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log
        )

target_link_libraries( # Specifies the target library.
        native-lib
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        )
