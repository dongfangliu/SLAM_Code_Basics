project(feature_extraction)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(feature_extraction main.cpp)

install(TARGETS feature_extraction RUNTIME DESTINATION bin)
target_link_libraries(feature_extraction ${OpenCV_LIBS})