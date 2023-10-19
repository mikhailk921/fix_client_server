
file( GLOB SOURCE_FILES  lib/*.cpp )
file( GLOB SOURCE_HEADERS lib/*.hpp )

add_executable( client client.cpp )

target_link_libraries(client PRIVATE quickfix)
