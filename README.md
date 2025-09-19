# Cryptonite
This is Qt/QML trading bot project.

## Prerequisites
Qt 6.8.3 LTS

CMake 4.1 or higher

VSCode or Visual Studio

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
