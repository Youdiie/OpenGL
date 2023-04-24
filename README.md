## Learn OpneGL

[Learn OpenGL](https://learnopengl.com/) 사이트 공부용


## Prerequisite

| Library | Version |
|:--------|--------:|
| GLAD    |     3.3 |
| GLFW    |   3.3.8 |
| GLM     | 0.9.9.8 |
| ASSIMP  |   5.2.5 | 


## Build

- Install CMake for Windows
- Install MinGW 64-bit for Windows
- Install ninja.exe and add to **System Path**
- Clone OpenGL project
- Build CMake
```commandline
$ cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B build
$ cmake --build build --target Learn-OpenGL -j 12
```
- Run `build/Learn-OpenGL.exe`