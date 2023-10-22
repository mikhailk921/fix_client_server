
set(SERVER_TARGET "server" CACHE INTERNAL "")

add_executable( ${SERVER_TARGET} server.cpp Application.h Application.cpp logger.h)

target_include_directories(${SERVER_TARGET} PUBLIC "${PROJECT_SOURCE_DIR}/thirdparty/quickfix/include")
target_link_libraries(${SERVER_TARGET} PUBLIC quickfix)

configure_file("server_config.cfg" "${CMAKE_CURRENT_BINARY_DIR}/server_config.cfg" COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/thirdparty/quickfix/share/quickfix/FIX44.xml"
        "${CMAKE_CURRENT_BINARY_DIR}/spec/FIX44.xml" COPYONLY)


#
# targets install
#

install(TARGETS ${SERVER_TARGET} DESTINATION "${PROJECT_SOURCE_DIR}/bin/${SERVER_TARGET}")
install(FILES "server_config.cfg" DESTINATION "${PROJECT_SOURCE_DIR}/bin/${SERVER_TARGET}")
install(FILES "${PROJECT_SOURCE_DIR}/thirdparty/quickfix/share/quickfix/FIX44.xml"
        DESTINATION "${PROJECT_SOURCE_DIR}/bin/${SERVER_TARGET}/spec/")

install(DIRECTORY "${PROJECT_SOURCE_DIR}/thirdparty/quickfix/lib/"
        DESTINATION "${PROJECT_SOURCE_DIR}/bin/${SERVER_TARGET}"
        COMPONENT "Copy prebuilt quickfix libs to bin folder")
