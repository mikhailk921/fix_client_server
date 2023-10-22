
set(CLIENT_TARGET "client" CACHE INTERNAL "")

set(CMAKE_WARN_DEPRECATED TRUE)

add_executable( ${CLIENT_TARGET} client.cpp client.hpp Application.h Application.cpp)

if (WIN32)
    target_include_directories(${CLIENT_TARGET} PUBLIC "${PROJECT_SOURCE_DIR}/thirdparty/quickfix_win/include")
else()
    target_include_directories(${CLIENT_TARGET} PUBLIC "${PROJECT_SOURCE_DIR}/thirdparty/quickfix/include")
endif()

target_link_libraries(${CLIENT_TARGET} PUBLIC quickfix)

configure_file("client_config.cfg" "${CMAKE_CURRENT_BINARY_DIR}/client_config.cfg" COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/thirdparty/quickfix/share/quickfix/FIX44.xml"
               "${CMAKE_CURRENT_BINARY_DIR}/spec/FIX44.xml" COPYONLY)


#
# targets install
#

install(TARGETS ${CLIENT_TARGET} DESTINATION "${PROJECT_SOURCE_DIR}/bin/${CLIENT_TARGET}")
install(FILES "client_config.cfg" DESTINATION "${PROJECT_SOURCE_DIR}/bin/${CLIENT_TARGET}")
install(FILES "${PROJECT_SOURCE_DIR}/thirdparty/quickfix/share/quickfix/FIX44.xml"
        DESTINATION "${PROJECT_SOURCE_DIR}/bin/${CLIENT_TARGET}/spec/")

install(DIRECTORY "${PROJECT_SOURCE_DIR}/thirdparty/quickfix/lib/"
        DESTINATION "${PROJECT_SOURCE_DIR}/bin/${CLIENT_TARGET}"
        COMPONENT "Copy prebuilt quickfix libs to bin folder")
