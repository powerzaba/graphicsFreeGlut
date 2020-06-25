cmake_minimum_required(VERSION 3.16)
project(g53gra_framework)

set(CMAKE_CXX_STANDARD 17)

include_directories(G53GRA.Framework/freeglut)
include_directories(G53GRA.Framework/freeglut/include)
include_directories(G53GRA.Framework/freeglut/include/GL)
include_directories(G53GRA.Framework/G53GRA.Framework/Code)
include_directories(G53GRA.Framework/G53GRA.Framework/Framework/Engine)
include_directories(G53GRA.Framework/G53GRA.Framework/Framework/Interface)
include_directories(G53GRA.Framework/G53GRA.Framework/Framework/Utility)

add_executable(g53gra_framework
        G53GRA.Framework/freeglut/include/GL/freeglut.h
        G53GRA.Framework/freeglut/include/GL/freeglut_ext.h
        G53GRA.Framework/freeglut/include/GL/freeglut_std.h
        G53GRA.Framework/freeglut/include/GL/glut.h
        G53GRA.Framework/G53GRA.Framework/Code/main.cpp
        G53GRA.Framework/G53GRA.Framework/Code/MultiLight.cpp
        G53GRA.Framework/G53GRA.Framework/Code/MultiLight.h
        G53GRA.Framework/G53GRA.Framework/Code/MyScene.cpp
        G53GRA.Framework/G53GRA.Framework/Code/MyScene.h
        G53GRA.Framework/G53GRA.Framework/Code/TexturedCube.cpp
        G53GRA.Framework/G53GRA.Framework/Code/TexturedCube.h
        G53GRA.Framework/G53GRA.Framework/Code/TexturedCylinder.cpp
        G53GRA.Framework/G53GRA.Framework/Code/TexturedCylinder.h
        G53GRA.Framework/G53GRA.Framework/Code/TexturedSphere.cpp
        G53GRA.Framework/G53GRA.Framework/Code/TexturedSphere.h
        G53GRA.Framework/G53GRA.Framework/Framework/Engine/Engine.cpp
        G53GRA.Framework/G53GRA.Framework/Framework/Engine/Engine.h
        G53GRA.Framework/G53GRA.Framework/Framework/Engine/Scene.cpp
        G53GRA.Framework/G53GRA.Framework/Framework/Engine/Scene.h
        G53GRA.Framework/G53GRA.Framework/Framework/Interface/Animation.h
        G53GRA.Framework/G53GRA.Framework/Framework/Interface/DisplayableObject.h
        G53GRA.Framework/G53GRA.Framework/Framework/Interface/Input.h
        G53GRA.Framework/G53GRA.Framework/Framework/Utility/Camera.cpp
        G53GRA.Framework/G53GRA.Framework/Framework/Utility/Camera.h
        G53GRA.Framework/G53GRA.Framework/Framework/Utility/Texture.cpp
        G53GRA.Framework/G53GRA.Framework/Framework/Utility/Texture.h
        G53GRA.Framework/G53GRA.Framework/Framework/Utility/VectorMath.h
        G53GRA.Framework/G53GRA.Framework/Textures/.gitignore
        G53GRA.Framework/G53GRA.Framework/Textures/marble.bmp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(graphics_cw2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})