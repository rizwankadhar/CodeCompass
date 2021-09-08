include_directories(
  include
  ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp
  ${PROJECT_SOURCE_DIR}/util/include
  ${PROJECT_SOURCE_DIR}/webserver/include)

include_directories(SYSTEM
  ${THRIFT_LIBTHRIFT_INCLUDE_DIRS})

add_custom_command(
  OUTPUT
    ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/github_constants.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/github_constants.h
    ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/github_types.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/github_types.h
    ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/GithubService.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/GithubService.h
    ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp
  COMMAND
    ${THRIFT_EXECUTABLE} --gen cpp
      -o ${CMAKE_CURRENT_BINARY_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}/github.thrift
  DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/github.thrift
  COMMENT
    "Generating Thrift for github.thrift")

add_library(githubthrift STATIC
  ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/github_constants.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/github_types.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/GithubService.cpp)

target_compile_options(githubthrift PUBLIC -fPIC)

add_library(githubservice SHARED
  src/githubservice.cpp
  src/plugin.cpp)

target_compile_options(githubservice PUBLIC -Wno-unknown-pragmas)

target_link_libraries(githubservice
  util
  ${THRIFT_LIBTHRIFT_LIBRARIES}
  ${ODB_LIBRARIES}
  githubthrift)

install(TARGETS githubservice DESTINATION ${INSTALL_SERVICE_DIR})
