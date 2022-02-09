cmake_minimum_required(VERSION 2.6)

project(learn_opengl)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

link_libraries("${PROJECT_SOURCE_DIR}/lib/libglfw.so")

find_library(GLEW_LIB NAMES GLEW glew glew32 glew32s REQUIRED)
find_library(GL_LIB NAMES GL REQUIRED)
find_library(X11_LIB NAMES X11 REQUIRED)
find_library(PTHREAD_LIB NAMES pthread REQUIRED)
find_library(XRANDR_LIB NAMES Xrandr REQUIRED)
find_library(XI_LIB NAMES Xi REQUIRED)
find_library(DL_LIB NAMES dl REQUIRED)
include_directories(include)
aux_source_directory(src SOURCES)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${DL_LIB} ${PTHREAD_LIB} ${GLEW_LIB} ${GL_LIB} ${X11_LIB} ${XRANDR_LIB} ${XI_LIB})
