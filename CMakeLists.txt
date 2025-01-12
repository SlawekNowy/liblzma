cmake_minimum_required(VERSION 3.01)





#TODO: stop if we use vs2015 or older

project(lzma VERSION 24.09
                  DESCRIPTION "Cross-platform decompiler for scenes.image file."
                  LANGUAGES C)






set(SOURCES
    "src/Alloc.c"
    "src/LzFind.c"
    "src/LzmaDec.c"
    "src/LzmaEnc.c"
    "src/LzmaLib.c"
    "src/Threads.c"
    "include/Alloc.h"
    "include/LzFind.h"
    "include/LzmaDec.h"
    "include/LzmaEnc.h"
    "include/LzmaLib.h"
    "include/7zTypes.h"
    "include/Threads.h"

set(SOURCES_WIN
    "src/win/LzmaLibExports.c"
    "src/win/LzmaLib.def"
    "src/win/resource.rc")

# Dodaj źródło do pliku wykonywalnego tego projektu.

if(WIN32)
add_library (lzma_s STATIC ${SOURCES})
add_library (lzma SHARED ${SOURCES} ${SOURCES_WIN})
else()
add_library (lzma_s STATIC ${SOURCES})
add_library (lzma SHARED ${SOURCES})
endif()

#if (NOT MSVC)
    #set (CFLAGS " -c -O2 -Wall -fPIC")
 #   target_compile_definitions(lzma_s PUBLIC _7ZIP_ST)
#elseif(MINGW)
    #set (CFLAGS " -c -O2 -Wall")
#endif()

target_precompile_headers(lzma PUBLIC "include/Precomp.h")


target_include_directories(lzma PUBLIC
    "${PROJECT_SOURCE_DIR}/include/")


if(WIN32)
    target_include_directories(lzma PUBLIC
        "${PROJECT_SOURCE_DIR}/include/win")
endif()


