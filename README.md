# Cryptonite
This is Qt/QML trading bot project.

## Prerequisites
Download and install Qt 6.8.3 LTS
- MSVC 2022 64-bit

Download and install CMake 4.1 or higher

IDE: VSCode or Visual Studio

Install "Visual Studio Build Tools 2022" using visual studio installer

Add Qt6_DIR variable to your Environment Variables:
Qt6_DIR = C:\Qt\6.8.3\msvc2022_64\lib\cmake\Qt6

Add the following to your PATH variable:
C:\Qt\6.8.3\msvc2022_64\bin

## Helpful VSCode Extensions
C/C++

C/C++ Extension Pack

C/C++ Themes

Qt Core

Qt Extension Pack

Qt Qml

Qt UI

CMake Tools

YAML

Markdown Preview Enhanced

## Debugging in VSCode
For the better readability of the complex classes such as QString add qt6.natvis as a visualizer tool. To do so add the following line to .vscode/launch.json file:

```"visualizerFile": "${workspaceFolder}/qt6.natvis"```

This settings are already added to the "Cryptonite Debug" configuration as an example.
Note: this settings does not work in VSCode if you use the debug button located in the bottom area (this buttons come from CMake Tools extension).
