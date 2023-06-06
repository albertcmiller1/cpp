cmake_minimum_required(VERSION 3.2.0)
project(sock VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")


include_directories(/opt/homebrew/Cellar/boost/1.80.0/include)
include_directories(/opt/homebrew/Cellar/asio/1.24.0/include)
link_directories(/opt/homebrew/lib)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/Crow/include)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/Crow/include/crow)

add_executable(sock main.cpp)

target_link_libraries(sock boost_system)
target_link_libraries(sock pthread)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)





