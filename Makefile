#OBJS specifies which files to compile as part of the project
OBJS_APP = src/Simulator.cpp
#OBJS_APP = src/MyApplication.cpp src/Mesh.cpp 

OBJS_CORE = src/core/Exception.cpp src/core/Renderer.cpp src/core/Shader.cpp src/core/Program.cpp src/core/Buffer.cpp src/core/Computer.cpp

OBJS_GLUT = src/core/GLUTApplication.cpp $(OBJS_CORE) $(OBJS_APP)
OBJS_SDL2 = src/core/SDL2Application.cpp $(OBJS_CORE) $(OBJS_APP)

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = 

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = 

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS_BASE = -lmingw32 -lglew32 -lglu32 -lopengl32 

LINKER_FLAGS_GLUT = -lfreeglut $(LINKER_FLAGS_BASE)
LINKER_FLAGS_SDL2 = -lSDL2main -lSDL2 $(LINKER_FLAGS_BASE)


#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Engine3D

#This is the target that compiles our executable
all : $(OBJS_SDL2)
	$(CC) $(OBJS_SDL2) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS_SDL2) -o $(OBJ_NAME)

glut : $(OBJS_GLUT)
	$(CC) $(OBJS_GLUT) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS_GLUT) -o $(OBJ_NAME)