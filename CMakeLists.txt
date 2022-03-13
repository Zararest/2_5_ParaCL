cmake_minimum_required(VERSION 3.13.4)
project(ParaCL)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_package(Boost 1.40 COMPONENTS program_options REQUIRED)

set(GRAMMAR "./bin/bisoner.y" CACHE STRING "file with grammar" FORCE)

set(FRONTEND_DIR "./src/frontend/")
set(INTERPRETER_DIR "./src/interpreter/")
set(LINTER_DIR "./src/linter/")
set(TEST_DIR "./tests/")

flex_target(scanner
  ./bin/flexer.l
  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cc
)

bison_target(parser
  ${GRAMMAR}
  ${CMAKE_CURRENT_BINARY_DIR}/parser.cc
  COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/Paragrammar.tab.hh")

add_flex_bison_dependency(scanner parser)

include_directories(./src/headers)

add_executable(${PROJECT_NAME} ./main.cpp  
  ${FRONTEND_DIR}Ioperator.cpp
  ${FRONTEND_DIR}Istatement.cpp

  ${LINTER_DIR}Print_req.cpp
  ${LINTER_DIR}Check_scope_req.cpp
  ${INTERPRETER_DIR}Interpreter.cpp
  ${INTERPRETER_DIR}Objects_manager.cpp
  ${INTERPRETER_DIR}Deleter_req.cpp

  ${BISON_parser_OUTPUTS}
  ${FLEX_scanner_OUTPUTS}
)

add_executable(Tests  ./tests/test.cpp
  ${FRONTEND_DIR}Ioperator.cpp
  ${FRONTEND_DIR}Istatement.cpp

  ${LINTER_DIR}Print_req.cpp
  ${LINTER_DIR}Check_scope_req.cpp
  ${INTERPRETER_DIR}Interpreter.cpp
  ${INTERPRETER_DIR}Objects_manager.cpp
  ${INTERPRETER_DIR}Deleter_req.cpp

  ${BISON_parser_OUTPUTS}
  ${FLEX_scanner_OUTPUTS}
)

target_link_libraries(Tests Boost::program_options)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(Tests PRIVATE cxx_std_20)
target_include_directories(Tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(Tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})