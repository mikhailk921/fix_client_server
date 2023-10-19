#
# quickfix
#


add_library(quickfix SHARED IMPORTED)

if (WIN32)
    set_property(TARGET quickfix PROPERTY
                IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/quickfix_win/lib/quickfixd.lib")
    set_target_properties(quickfix PROPERTIES PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/quickfix_win/include/")
else()
    set_property(TARGET quickfix PROPERTY
                IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/quickfix_linux/lib/quickfixd.a")
    set_target_properties(quickfix PROPERTIES PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/quickfix_linux/include/")
endif()
             
