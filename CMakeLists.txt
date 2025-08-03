cmake_minimum_required(VERSION 3.10)

project("notes")



set(SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(SOURCES ${SRC_DIR}/main.cpp ${SRC_DIR}/modules/)



add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES CXX_STANDARD 14
             CXX_STANDARD_REQUIRED OFF
             CXX_EXTENSIONS ON)
