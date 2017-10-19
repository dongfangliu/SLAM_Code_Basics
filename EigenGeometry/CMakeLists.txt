project(eigengeometry)

add_executable(eigengeometry main.cpp)

install(TARGETS eigengeometry RUNTIME DESTINATION bin)
include_directories("/usr/include/eigen3")