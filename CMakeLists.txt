cmake_minimum_required(VERSION 3.20.0)
project(Lab2 VERSION 0.1.0)

set(wxWidgets_ROOT_DIR "C:/dev/wx") 
set(wxWidgets_LIB_DIR "C:/dev/wx/lib/gcc_x64_dll")

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})

add_executable(Lab2 main.cpp)

target_link_libraries(Lab2 ${wxWidgets_LIBRARIES})
target_include_directories(Lab2 PRIVATE ${wxWidgets_INCLUDE_DIRS})