cmake_minimum_required(VERSION 3.1)





#TODO: stop if we use vs2015 or older

project(lzma VERSION 19.0
                  DESCRIPTION "Cross-platform decompiler for scenes.image file."
                  LANGUAGES C)


              option(MULTITHREADED "Set this to on if you want multithreaded compression algorythm. (Community supplied in POSIX systems.)" off)






set(SOURCES
    "src/Alloc.c"
    "src/LzFind.c"
    "src/LzmaDec.c"
    "src/LzmaEnc.c"
    "src/LzmaLib.c"
    "include/Alloc.h"
    "include/LzFind.h"
    "include/LzmaDec.h"
    "include/LzmaEnc.h"
    "include/LzmaLib.h"
    "include/7zTypes.h")


if (MULTITHREADED)
    find_package(Threads)

    set(SOURCES ${SOURCES}
        "include/LzFindMt.h"

        "src/LzFindMt.c" #this one uses external interface to use threads, defined in Threads.h
    )

    if(CMAKE_USE_WIN32_THREADS_INIT) #implies WIN32

        set(SOURCES ${SOURCES}
            "src/win/Threads.c"

            "include/win/Threads.h")
    elseif(CMAKE_USE_PTHREADS_INIT)

        set(SOURCES ${SOURCES}


            "include/posix/Threads.h"
            "include/posix/event_objects_posix.h"
            "src/posix/Threads.c"
            "src/posix/event_objects_posix.c")
    endif()


endif()



if(WIN32)
    set(SOURCES ${SOURCES}
        "src/win/LzmaLibExports.c"
        "src/win/LzmaLib.def"
        "src/win/resource.rc")
endif()
# Dodaj źródło do pliku wykonywalnego tego projektu.
add_library (lzma STATIC ${SOURCES})


if (NOT MSVC)
    set (CFLAGS " -c -O2 -Wall -fPIC")
    target_compile_definitions(lzma PUBLIC _7ZIP_ST)
elseif(MINGW)
    set (CFLAGS " -c -O2 -Wall")
endif()

target_precompile_headers(lzma PUBLIC "include/Precomp.h")


target_include_directories(lzma PUBLIC
    "${PROJECT_SOURCE_DIR}/include/")




if(MULTITHREADED)

    if(CMAKE_USE_WIN32_THREADS_INIT) #implies WIN32

        target_include_directories(lzma PUBLIC
            "${PROJECT_SOURCE_DIR}/include/win/")
    elseif(CMAKE_USE_PTHREADS_INIT)

        target_include_directories(lzma PUBLIC
            "${PROJECT_SOURCE_DIR}/include/posix/")
    endif()

endif()




