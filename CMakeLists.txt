cmake_minimum_required(VERSION 3.25.0)

project(EOP C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(AppName ${CMAKE_PROJECT_NAME})


set(EOP_APP_DIRECTORY ${CMAKE_SOURCE_DIR}/app)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EOP_APP_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EOP_APP_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${EOP_APP_DIRECTORY})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${EOP_APP_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${EOP_APP_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${EOP_APP_DIRECTORY})


add_executable(
        ${AppName} main.c
        third_party/mongoose.c
        third_party/mongoose.h
        third_party/sqlite3.c
        third_party/sqlite3.h
)

add_subdirectory(EOP/attendance)
target_link_libraries(${AppName} PRIVATE EOP_Attendance)