
set(CLIENT_TARGET "client" CACHE INTERNAL "")

add_executable( ${CLIENT_TARGET} client.cpp Application.h Application.cpp)

target_include_directories(${CLIENT_TARGET} PUBLIC "${PROJECT_SOURCE_DIR}/thirdparty/quickfix/include")
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
