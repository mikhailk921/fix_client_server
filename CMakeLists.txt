cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(FIX_client_server)

# Disable warnings about deprecated functions
add_compile_options("-Wno-deprecated")


#
# Sub-directories
#

add_library(quickfix SHARED IMPORTED)
set_property(TARGET quickfix PROPERTY
        IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/thirdparty/quickfix/lib/libquickfix.so"
        )
set_target_properties(quickfix PROPERTIES
        PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/thirdparty/quickfix/include"
        )

#
# client and server
#

add_subdirectory(client)
add_subdirectory(server)

