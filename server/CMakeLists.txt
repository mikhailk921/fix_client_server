
add_executable( server server.cpp server.hpp Application.h Application.cpp logger.h)

if (WIN32)
    target_include_directories(server PUBLIC "${PROJECT_SOURCE_DIR}/thirdparty/quickfix_win/include")
else()
    target_include_directories(server PUBLIC "${PROJECT_SOURCE_DIR}/thirdparty/quickfix/include")
endif()

target_link_libraries(server PUBLIC quickfix)

configure_file("server_config.cfg" "${CMAKE_CURRENT_BINARY_DIR}/server_config.cfg" COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/thirdparty/quickfix/share/quickfix/FIX44.xml"
        "${CMAKE_CURRENT_BINARY_DIR}/spec/FIX44.xml" COPYONLY)

