cmake_minimum_required(VERSION 3.10)





#TODO: stop if we use vs2015 or older

project(lzma VERSION 24.09
                  DESCRIPTION "Cross-platform decompiler for scenes.image file."
                  LANGUAGES C)


#Only select archs have hand-written assembly.



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
    "include/Threads.h")

set(SOURCES_WIN
    "src/win/LzmaLibExports.c"
    "src/win/LzmaLib.def"
    "src/win/resource.rc")

#Some generators do not like final libraries using only object libraries. This exists just to shut them up.
set(SOURCE_DUMMY 
    src/LzmaDummy.c)

# Dodaj źródło do pliku wykonywalnego tego projektu.
set(CMAKE_C_VISIBILITY_PRESET hidden)
add_library (lzma_common OBJECT ${SOURCES})
set_property(TARGET lzma_common PROPERTY POSITION_INDEPENDENT_CODE ON)


if(WIN32)
add_library (lzma_s STATIC $<TARGET_OBJECTS:lzma_common> ${SOURCE_DUMMY})
add_library (lzma SHARED $<TARGET_OBJECTS:lzma_common> ${SOURCES_WIN})
else()
add_library (lzma_s STATIC $<TARGET_OBJECTS:lzma_common> ${SOURCE_DUMMY})
add_library (lzma SHARED $<TARGET_OBJECTS:lzma_common> ${SOURCE_DUMMY})
endif()

#if (NOT MSVC)
    #set (CFLAGS " -c -O2 -Wall -fPIC")
 #   target_compile_definitions(lzma_s PUBLIC _7ZIP_ST)
#elseif(MINGW)
    #set (CFLAGS " -c -O2 -Wall")
#endif()

target_precompile_headers(lzma_common PUBLIC "include/Precomp.h")


target_include_directories(lzma_common PUBLIC
    "${PROJECT_SOURCE_DIR}/include/")


if(WIN32)
    target_include_directories(lzma PUBLIC
        "${PROJECT_SOURCE_DIR}/include/win")
endif()


