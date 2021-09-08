include_directories(
  include
  ${PROJECT_SOURCE_DIR}/model/include
  ${PROJECT_SOURCE_DIR}/util/include
  ${PROJECT_SOURCE_DIR}/parser/include)

add_library(githubparser SHARED
  src/githubparser.cpp)

target_compile_options(githubparser PUBLIC -Wno-unknown-pragmas)

install(TARGETS githubparser DESTINATION ${INSTALL_PARSER_DIR})
