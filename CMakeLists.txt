# Minimum version of CMake
 cmake_minimum_required (VERSION 2.6 FATAL_ERROR)

# Project name
project (Simulation)

# Find ROOT installation
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{ROOTSYS}/etc/cmake)
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT COMPONENTS Tree REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})

# Find Geant4 files
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# Locating headers and sources
file(GLOB sources ${PROJECT_SOURCE_DIR}/source/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Copy all mac files
file(GLOB MACRO_FILES "*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

# Add an executable and link Geant4-ROOT libraries
add_executable(sim sim.cc ${sources} ${headers})
target_link_libraries(sim ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} -lrt)

add_custom_target (Simulation DEPENDS sim) # The project "Simulation" runs after the "sim" even if it fails.
install(TARGETS sim DESTINATION bin)
