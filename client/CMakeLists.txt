
# file( GLOB SOURCE_FILES  lib/*.cpp )
# file( GLOB SOURCE_HEADERS lib/*.hpp )

set(CMAKE_WARN_DEPRECATED TRUE)

add_executable( client client.cpp client.hpp Application.h Application.cpp)

if (WIN32)
    target_include_directories(client PUBLIC "${PROJECT_SOURCE_DIR}/thirdparty/quickfix_win/include")
else()
    target_include_directories(client PUBLIC "${PROJECT_SOURCE_DIR}/thirdparty/quickfix/include")
endif()

target_link_libraries(client PUBLIC quickfix)

configure_file("client_config.cfg" "${CMAKE_CURRENT_BINARY_DIR}/client_config.cfg" COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/thirdparty/quickfix/share/quickfix/FIX44.xml"
               "${CMAKE_CURRENT_BINARY_DIR}/spec/FIX44.xml" COPYONLY)
