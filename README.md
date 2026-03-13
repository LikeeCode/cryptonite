# Cryptonite

A C++/Qt6/QML algorithmic trading bot for the [Binance](https://www.binance.com) exchange. Rest-api documentation: [binance-spot-api-docs](https://github.com/binance/binance-spot-api-docs/blob/master/testnet/rest-api.md)

**Platform:** Windows &nbsp;|&nbsp; **Compiler:** MSVC 2022 &nbsp;|&nbsp; **Qt:** 6.8.3 LTS &nbsp;|&nbsp; **Standard:** C++17

---

## Table of Contents

- [Features](#features)
- [Prerequisites](#prerequisites)
- [API Key Setup](#api-key-setup)
- [Build](#build)
- [Running](#running)
- [Testing](#testing)
- [Debugging in VSCode](#debugging-in-vscode)
- [Project Structure](#project-structure)

---

## Features

- Binance REST API client (market data, order book, trades, klines)
- Testnet support for safe development and testing
- Qt/QML UI with a reactive data model layer
- Unit-tested parsing layer via Google Test

---

## Prerequisites

Install the following tools in order:

1. **Git** — [git-scm.com](https://git-scm.com)
2. **CMake 3.14 or higher** — [cmake.org](https://cmake.org/download)
3. **Qt 6.8.3 LTS** — [qt.io/download](https://www.qt.io/download)
   > [!IMPORTANT]
   > During installation, select the **MSVC 2022 64-bit** component under Qt 6.8.3.
4. **MSVC 2022 Build Toolchain** — required to compile and link against the `msvc2022_64` Qt binaries.
   You have two options (either is sufficient — you do not need both):
   - **Visual Studio Build Tools 2022** *(recommended if you only use VSCode)* — [download](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022)
     Includes the compiler, linker, Windows SDK, and the `cppvsdbg` debugger used by VSCode. Lighter than the full IDE.
   - **Visual Studio 2022 Community** *(optional, includes the Build Tools)* — [release history](https://learn.microsoft.com/en-us/visualstudio/releases/2022/release-history)

   > [!NOTE]
   > Whichever you install, run the **Visual Studio Installer** and ensure the
   > **"Desktop development with C++"** workload is checked.

5. **VSCode** with the following extensions:
   - [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
   - [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)
   - [Qt Extension Pack](https://marketplace.visualstudio.com/items?itemName=qt-official.qt-extension-pack)
   - [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)

### Environment Variables

After installing Qt, add the following to your system environment:

| Variable | Value |
|---|---|
| `Qt6_DIR` | `C:\Qt\6.8.3\msvc2022_64\lib\cmake\Qt6` |

Also append to your `PATH`:

```
C:\Qt\6.8.3\msvc2022_64\bin
```

---

## API Key Setup

The application reads Binance API credentials from `apiKeys/binanceAPI.txt` at runtime.
This file is excluded from version control — you must create it manually before building.

Create `apiKeys/binanceAPI.txt` with your API key on the first line and your secret key on the second:

```
YOUR_BINANCE_API_KEY
YOUR_BINANCE_SECRET_KEY
```

> [!TIP]
> The application uses the **Binance Testnet** by default, so you can generate safe testnet
> credentials at [testnet.binance.vision](https://testnet.binance.vision) without risking real funds.

---

## Build

Configure and build from the repository root:

```bash
cmake -S . -B build
cmake --build build
```

The compiled executable and all required Qt DLLs are placed in `build/bin/Debug/` (or `Release/`).

### Selecting the Compiler Kit in VSCode

After the first build, reload VSCode and select the compiler kit when prompted by CMake Tools:

```
Qt-6.8.3-msvc2022_64_VSCommunity_2022_Release_amd64
```

This corresponds to the MSVC 2022 64-bit Qt component installed in step 3.

---

## Running

Launch the executable directly from the build output directory:

```bash
./build/bin/Debug/Cryptonite.exe
```

Or use the **CMake Tools** launch button in VSCode after selecting a build target.

---

## Testing

Tests are built automatically as part of the main build. Run them with CTest:

```bash
ctest --test-dir build -C Debug --output-on-failure
```

---

## Debugging in VSCode

The repository includes a pre-configured launch configuration (`Target (Debug)`) in `.vscode/launch.json`.

It uses `.vscode/qt.natvis` as a visualizer, which provides human-readable display of Qt types
such as `QString` and `QList` in the debugger watch window.

> [!NOTE]
> The natvis visualizer only works when launching via the **Run and Debug** panel (`F5`).
> It does not apply when using the debug button in the CMake Tools bottom toolbar.

---

## Project Structure

```
cryptonite/
├── api/
│   └── binance/          # Binance REST API client (requests, parsers, enums, filters)
├── models/               # Qt data models exposed to QML
├── tests/                # Google Test unit tests for API parsers
├── 3rdParty/
│   └── googletest/       # Vendored Google Test / Google Mock
├── apiKeys/              # API credentials — git-ignored, must be created manually
├── main.cpp              # Application entry point
├── main.qml              # Root QML component
└── CMakeLists.txt        # Top-level build configuration
```
