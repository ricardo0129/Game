ECHO OFF
g++ main.cpp shader.cpp render.cpp object.cpp camera.cpp physics.cpp projectile.cpp -lglfw3 -lopengl32 -lgdi32 -lglad -lglm_shared
a.exe
PAUSE