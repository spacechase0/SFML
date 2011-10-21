
# include the SFML specific macros
include(${PROJECT_SOURCE_DIR}/cmake/Macros.cmake)

# let CMake know about our additional libraries paths (on Windows, GP2X Wiz, and OS X)
if (WINDOWS)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers")
    if(COMPILER_GCC)
        set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-mingw")
        if(ARCH_32BITS)
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/bin/x86")
        else()
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/bin/x64")
        endif()
    elseif(COMPILER_MSVC)
        if(ARCH_32BITS)
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-msvc/x86")
        else()
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-msvc/x64")
        endif()
    endif()
elseif(GP2X_WIZ)
    include_directories("${PROJECT_SOURCE_DIR}/extlibs/headers-gp2x-wiz" )
    include_directories("${PROJECT_SOURCE_DIR}/extlibs/headers")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-gp2x-wiz")
    link_directories("${PROJECT_SOURCE_DIR}/extlibs/libs-gp2x-wiz")
    
    # Also define SFML_SYSTEM_GP2X_WIZ and SFML_WINDOW_OPENGLES
	add_definitions(-DSFML_SYSTEM_GP2X_WIZ)
	add_definitions(-DSFML_WINDOW_OPENGLES)
elseif(MACOSX)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-osx/lib/")
endif()

# add the SFML sources path
include_directories(${PROJECT_SOURCE_DIR}/src)

# define the path of our additional CMake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/")

# set the output directory for SFML libraries
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

# define the export symbol
add_definitions(-DSFML_EXPORTS)

# add the modules subdirectories
add_subdirectory(System)
add_subdirectory(Window)
add_subdirectory(Network)
if(GP2X_WIZ)
	message("No graphics on GP2X Wiz; Waiting for new API.")
	message("No audio on GP2X Wiz; Look into software OpenAL.")
else()
	add_subdirectory(Graphics)
	add_subdirectory(Audio)
endif()
if(WINDOWS)
    add_subdirectory(Main)
endif()
