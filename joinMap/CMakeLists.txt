project(joinmap)
#opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "-std=c++11")
#eigen
include_directories("/usr/include/eigen3/")
#pcl
find_package(PCL REQUIRED COMPONENT common io)
include_directories(${PCL_INCLUDE_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(joinmap main.cpp)

install(TARGETS joinmap RUNTIME DESTINATION bin)

target_link_libraries(joinmap ${OpenCV_LIBS} ${PCL_LIBRARIES})