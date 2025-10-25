# Chess Game - Simple Chess Game


## Introduction

This project is a straightforward chess game built with C++. It features a C++ backend server and a web-based frontend developed using Vite.

- **Current version:** 1.2.1


## Features

This chess game includes the following features:
- Session management for handling multiple games.
- Compatible with standard chess rules.
- Communication between server and web interface using WebSockets.
- Compatibility with UCI protocol for chess engines.
- Play chess against [Euphron](https://github.com/Omikrone/Euphron), a chess engine developed in C++ !


## Installation

This project is compatible with Windows and Linux, and requires CMake for building.

### Prerequisites

Make sure you have the following dependencies installed:
- CMake (see [CMake installation guide](https://cmake.org/install/))
- A C++ compiler (e.g., g++)
- Node.js and npm (see [Node.js installation guide](https://nodejs.org/en/download/))

Moreover, this project uses Crow for handling HTTP requests and WebSockets.
You can install Crow by following the instructions on its [GitHub repository](https://github.com/CrowCpp/Crow).

### Building the Project

1. Clone the repository:
```bash
    git clone https://github.com/Omikrone/Chessgame.git
    cd Chessgame
```

This project is meant to be used with the [Chessboard](https://github.com/Omikrone/Chessboard) library for the chess rules and logic. To install it, follow these steps:
```bash
    cd backend
    git clone https://github.com/Omikrone/Chessboard.git chess
```

2. Build the C++ server using CMake:
```bash
    cmake -S . -B build
    cd build && cmake --build . --config Release
```

3. Build the frontend using npm:
```bash
    cd ../frontend
    npm install
```

### Running the Project

1. Start the C++ server:
```bash
    cd backend/build
    ./game/Release/chessgame.exe
```

2. Start the frontend:
```bash
    cd ../frontend
    npm run dev
```
3. Open your web browser and navigate to `http://localhost:5173` to access the chess game interface. 


## Future Improvements

Future improvements for this project may include:
- [X] Adding compatibility with the Chessboard library for chess rules and logic.
- [X] Better Handling of the game session and player management.
- [ ] Implementing a multiplayer mode over the network.
- [ ] Enhancing the user interface with more features and better design.