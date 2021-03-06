cmake_minimum_required(VERSION 3.17)
project(OpenGLEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
set(GCC_COVERAGE_LINK_FLAGS "-lgcov")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

set(SFML_STATIC_LIBRARIES TRUE)
set(assimp_STATIC_LIBRARIES TRUE)

set(SFML_INCLUDE_DIR "libs/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "libs/SFML-2.5.1/lib")
set(SFML_DIR "libs/SFML-2.5.1/lib/cmake/SFML")

#set(assimp_INCLUDE_DIR "C:/Users/User/CLionProjects/OpenGLEngine/libs/assimp/include")
#set(assimp_LIBRARY_DIR "C:/Users/User/CLionProjects/OpenGLEngine/libs/assimp/lib")
#set(assimp_DIR "C:/Users/User/CLionProjects/OpenGLEngine/libs/assimp/lib/cmake")
#подключение файликов----------------------------------------------------------
add_executable(TestProjectLibs main_glew_sfml.cpp
        libs_project/Vector.hpp libs_project/Matrix.hpp
        utils/Shader.hpp utils/shaderLoader.hpp utils/shaderLoader.cpp utils/LightningShaderFiller.hpp
        libs_project/Objects.hpp libs_project/Sphere.cpp libs_project/Sphere.h libs_project/LightSource.hpp
        libs_project/Texture.hpp libs_project/Material.hpp libs_project/VBOObject.hpp libs_project/VAOObject.hpp
        libs_project/Mesh.hpp libs_project/Model.hpp)
add_executable(TestVectorLib test_debug_project/tests_vector.cpp libs_project/Vector.hpp)
add_executable(TestMatrixLib test_debug_project/tests_matrix.cpp libs_project/Matrix.hpp)
#------------------------------------------------------------------------------

#подключение SFML--------------------------------------------------------------
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
include_directories(SFML_INCLUDE_DIR)
link_directories(SFML_LIBRARY_DIR)

if (SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif ()
#------------------------------------------------------------------------------

#подключение assimp--------------------------------------------------------------
set(assimp_INCLUDE_DIR "./libs/assimp/include/assimp")
set(assimp_LIBRARY_DIR "./libs/assimp/lib")
set(assimp_DIR "./libs/assimp/lib/cmake")

find_package(assimp REQUIRED)
include_directories(${assimp_INCLUDE_DIR})
#include_directories(assimp_INCLUDE_DIR)
#link_directories(assimp_LIBRARY_DIR)
#------------------------------------------------------------------------------

#подключение OpenGL------------------------------------------------------------
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIR})
#------------------------------------------------------------------------------

set(LIBRARIES
        ${OpenGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        sfml-system
        sfml-window
        sfml-network
        sfml-graphics
        sfml-audio
        ${OPENGL_LIBRARY}
        ${assimp_LIBRARY}
        ${assimp_LIBRARIES}
        glew32
        glu32
        opengl32
        )

#подключение SFML и glew для каждой проги--------------------------------------
target_link_libraries(TestProjectLibs ${LIBRARIES})
#------------------------------------------------------------------------------

# add coverage-----------------------------------------------------------------
# https://plugins.jetbrains.com/plugin/11031-c-c--coverage
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
    add_link_options(-fprofile-instr-generate)
    #Uncomment in case of linker errors
    link_libraries(clang_rt.profile-x86_64)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(--coverage)
    #Uncomment in case of linker errors
    link_libraries(gcov)
endif ()
#------------------------------------------------------------------------------