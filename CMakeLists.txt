project(rummy-asio)

set (CMAKE_CXX_STANDARD 20)

add_executable(rummy-asio main.cpp)
target_link_libraries(rummy-asio "pthread" "fmt")