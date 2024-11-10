# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the required CUDA version (optional)
set(CMAKE_CUDA_STANDARD 11)

# Project name
project(Lab5 LANGUAGES CXX CUDA)

#find OPENMP
find_package(OpenMP)

# Include SFML
include_directories(${PROJECT_SOURCE_DIR}/../SFML/include)

link_directories(${PROJECT_SOURCE_DIR}/../SFML/lib)

# Set CUDA architecture
#set(CUDA_ARCHITECTURES 52)

# Specify the target executable
add_executable(talker src/talker.cpp)
add_executable(listener src/listener.cpp)

#file(COPY ${PROJECT_SOURCE_DIR}/white.png
#  DESTINATION "${COMMON_OUTPUT_DIR}/bin")
  
# Link SFML libraries
#target_link_libraries(talker sfml-graphics sfml-window sfml-system)
target_link_libraries(talker sfml-network)
target_link_libraries(listener sfml-network sfml-window sfml-graphics)

# Specify C++11 standard
#set_property(TARGET cuda_sfml_app PROPERTY CXX_STANDARD 17)

#set_target_properties(
#    Lab4 PROPERTIES
#    VS_DEBUGGER_WORKING_DIRECTORY "${COMMON_OUTPUT_DIR}/bin"
#)
# Compile Info
#set_target_properties(Lab4 PROPERTIES CUDA_ARCHITECTURES "50;72")
#target_compile_features(Lab4 PUBLIC cxx_std_11)
#target_compile_features(Lab4 PUBLIC cuda_std_11)
