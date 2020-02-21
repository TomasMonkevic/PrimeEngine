cmake_minimum_required(VERSION 3.0.0)
project(FreeType VERSION 0.1.0)

#include(CTest)
#enable_testing()

set(FREETYPE_HEADERS
    "freetype-gl/common.h"
    "freetype-gl/freetype-gl.h"
    "freetype-gl/opengl.h"
    "freetype-gl/platform.h"
    "freetype-gl/texture-atlas.h"
    "freetype-gl/texture-font.h"
    "freetype-gl/vec234.h"
    "freetype-gl/vector.h"
    "include/config/ftconfig.h"
    "include/config/ftheader.h"
    "include/config/ftmodule.h"
    "include/config/ftoption.h"
    "include/config/ftstdlib.h"
    "include/ft2build.h"
    "include/internal/ftdebug.h"
)

set(FREETYPE_SOURCES
    "freetype-gl/platform.c"
    "freetype-gl/texture-atlas.c" 
    "freetype-gl/texture-font.c"
    "freetype-gl/vector.c"
    "src/autofit/autofit.c"
    "src/base/ftbase.c"
    "src/base/ftbbox.c"
    "src/base/ftbitmap.c"
    "src/base/ftdebug.c"
    "src/base/ftfstype.c"
    "src/base/ftgasp.c"
    "src/base/ftglyph.c"
    "src/base/ftgxval.c"
    "src/base/ftinit.c"
    "src/base/ftlcdfil.c"
    "src/base/ftmm.c"
    "src/base/ftotval.c"
    "src/base/ftpatent.c"
    "src/base/ftpfr.c"
    "src/base/ftstroke.c"
    "src/base/ftsynth.c"
    "src/base/ftsystem.c"
    "src/base/fttype1.c"
    "src/base/ftwinfnt.c"
    "src/base/ftxf86.c"
    "src/bdf/bdf.c"
    "src/cache/ftcache.c"
    "src/cff/cff.c"
    "src/cid/type1cid.c"
    "src/gzip/ftgzip.c"
    "src/lzw/ftlzw.c"
    "src/pcf/pcf.c"
    "src/pfr/pfr.c"
    "src/psaux/psaux.c"
    "src/pshinter/pshinter.c"
    "src/psnames/psmodule.c"
    "src/raster/raster.c"
    "src/sfnt/sfnt.c"
    "src/smooth/smooth.c"
    "src/truetype/truetype.c"
    "src/type1/type1.c"
    "src/type42/type42.c"
    "src/winfonts/winfnt.c"
)

add_definitions(-DFT2_BUILD_LIBRARY)

include_directories("include")

if(${CMAKE_SYSTEM_NAME} MATCHES "Android")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -frtti -fexceptions -Wall")
    add_definitions(-DPE_ANDROID)
    if (${ANDROID_PLATFORM_LEVEL} LESS 12)
    message(FATAL_ERROR "OpenGL 2 is not supported before API level 11 \
                        (currently using ${ANDROID_PLATFORM_LEVEL}).")
    return()
    elseif (${ANDROID_PLATFORM_LEVEL} LESS 18)
    add_definitions("-DDYNAMIC_ES3")
    set(GL3STUB_SRC ../../PrimeEngine-Core/Platforms/Android/gl3stub.c)
    set(OPENGL_LIB GLESv2)
    else ()
    set(OPENGL_LIB GLESv3)
    endif (${ANDROID_PLATFORM_LEVEL} LESS 12)

    include_directories(../../PrimeEngineCore/Platforms/Android)

    add_library(FreeType STATIC
                ${GL3STUB_SRC}
                ${FREETYPE_HEADERS} 
                ${FREETYPE_SOURCES})

    # Include libraries needed for gles3jni lib
    target_link_libraries(FreeType
                ${OPENGL_LIB}
                android
                EGL
                log
                m)
else()
    include_directories("../GLEW/include")

    add_library(FreeType STATIC ${FREETYPE_HEADERS} ${FREETYPE_SOURCES})
endif()


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
