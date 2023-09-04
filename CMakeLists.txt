cmake_minimum_required(VERSION 3.15)

project(Imagesocket)

set(CMAKE_BUILD_TYPE Debug)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
find_package(OpenCV REQUIRED)

add_executable(server server.cpp)
add_executable(client client.cpp)

target_link_libraries(server PRIVATE ${OpenCV_LIBS})
target_link_libraries(client PRIVATE ${OpenCV_LIBS})