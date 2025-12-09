# Cryptonite
This is Qt/QML trading bot project.

## Prerequisites
1. Install Git
2. Install CMake 4.1 or higher
3. Install Qt 6.8.3 LTS
- MSVC 2022 64-bit
4. Install Visual Studio 2022 Community (https://learn.microsoft.com/en-us/visualstudio/releases/2022/release-history)
5. Install VSCode with extensions:
- C/C++
- C/C++ Extension Pack
- C/C++ Themes
- Qt Extension Pack
- CMake Tools
- Markdown Preview Enhanced
6. Install "Visual Studio Build Tools 2022" using visual studio installer
7. Add Qt6_DIR variable to your Environment Variables:
Qt6_DIR = C:\Qt\6.8.3\msvc2022_64\lib\cmake\Qt6
8. Add the following to your PATH variable:
C:\Qt\6.8.3\msvc2022_64\bin

## Build
```>cmake -S . -B build```
```>cmake --build build```
Restart VSCode
Choose the following compiler kit:
Visual Studio Community 2022 Release - amd64_x86

## Debugging in VSCode
For the better readability of the complex classes such as QString add qt6.natvis as a visualizer tool. To do so add the following line to .vscode/launch.json file:

```"visualizerFile": "${workspaceFolder}/qt6.natvis"```

This settings are already added to the "Cryptonite Debug" configuration as an example.
Note: this settings does not work in VSCode if you use the debug button located in the bottom area (this buttons come from CMake Tools extension).
