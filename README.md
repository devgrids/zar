# [Zar](https://github.com/devgrids/zar)

## Summary
Zar is a library designed to reuse classes and facilitate programming.
## How to add the library to your project?
Locate the path of your project and in the console write the following command:
```bash
git submodule add https://github.com/devgrids/zar
```
Add the following code to your project's CMakeLists.txt file:
```bash
add_subdirectory(zar)
...
target_link_libraries(${PROJECT_NAME} PUBLIC zar)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/zar)
```

## Dependencies

Library                                                | Functionality            |
------------------------------------------------------ |--------------------------|
[assimp](https://github.com/assimp/assimp)             | Mesh Loading             |
[glew](https://github.com/nigels-com/glew)             | OpenGL Function Loader   |
[glfw](https://github.com/glfw/glfw)                   | Windowing and Input      |
[glm](https://github.com/g-truc/glm)                   | OpenGL Mathematics       |
[stb](https://github.com/nothings/stb)                 | Texture Loading          |
[spdlog](https://github.com/gabime/spdlog)             | Logging                  |
