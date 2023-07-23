cmake_minimum_required(VERSION 3.24.2)
project(wxWidgets_ToDoList)
set(CMAKE_CXX_STANDARD 20)

include(ConfigFunctions.cmake)


# DIRECTORIES
set_project_directories(src src test res include lib out)


# EXECUTABLE
set(EXECUTABLE_NAME ${CMAKE_PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} ${HEADER_FILES} ${SOURCE_FILES})


# LIBRARIES

find_package(wxWidgets REQUIRED COMPONENTS all)
include(${wxWidgets_USE_FILE})
target_link_libraries(${EXECUTABLE_NAME} ${wxWidgets_LIBRARIES})

#find_libraries(LIBRARIES REQUIRED wxWidgets)
#target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARIES})