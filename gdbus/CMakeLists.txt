CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (GDbusCodegenGlibmmProxyTest)
FIND_PACKAGE(PkgConfig)

PKG_CHECK_MODULES (GLIBMM REQUIRED glibmm-2.4)
PKG_CHECK_MODULES (GIOMM  REQUIRED giomm-2.4)

SET (CODEGEN gdbus-codegen-glibmm3)
SET (INTROSPECTION_XML ${CMAKE_SOURCE_DIR}/bar.xml)

SET (SRC_ALL
    ${CMAKE_BINARY_DIR}/generated/bar_stub.h
    ${CMAKE_BINARY_DIR}/generated/bar_common.h
)

set (SRC_COMMON
    ${CMAKE_BINARY_DIR}/generated/bar_common.cpp
)
set (SRC_PROXY
    ${CMAKE_BINARY_DIR}/generated/bar_proxy.cpp
)
set (SRC_STUB
    ${CMAKE_BINARY_DIR}/generated/bar_stub.cpp
)
set (SRC_ALL ${SRC_COMMON} ${SRC_PROXY} ${SRC_STUB})

add_custom_command (OUTPUT ${SRC_ALL}
                    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/generated/
                    COMMAND ${CODEGEN} --generate-cpp-code=${CMAKE_BINARY_DIR}/generated/bar
                                        ${INTROSPECTION_XML}
                    DEPENDS ${INTROSPECTION_XML}
                    COMMENT "Generate the stub for the test program")
add_custom_target (GENERATED_FILES DEPENDS ${SRC_ALL})

add_executable(server server.cpp ${SRC_COMMON} ${SRC_STUB})

add_executable(client client.cpp ${SRC_COMMON} ${SRC_PROXY})

add_dependencies (server GENERATED_FILES)
add_dependencies (client GENERATED_FILES)

include_directories(    
${CMAKE_SOURCE_DIR}
${CMAKE_BINARY_DIR}
${GLIBMM_INCLUDE_DIRS}
${GIOMM_INCLUDE_DIRS})

message("GLIBMM_LDFLAGS = ${GLIBMM_LDFLAGS}")

target_link_libraries(server PRIVATE ${GLIBMM_LDFLAGS} ${GIOMM_LDFLAGS})
target_link_libraries(client PRIVATE ${GLIBMM_LDFLAGS} ${GIOMM_LDFLAGS})
