# Chess Game - C++ Chessgame server & Web Interface

<img src="./assets/logo.png" alt="Chessgame Logo" width="200"/>

## Introduction

This project is a straightforward chess game built with C++. It features a C++ backend server and a web-based frontend developed using Vite. **Chessgame** is compatible with the [Euphron](https://github.com/Omikrone/Euphron) chess engine and uses the [Chessboard](https://github.com/Omikrone/Chessboard) library for chess rules and logic.

- **Current version:** 1.4.2


## Features

This chess game includes the following features:
- Session management for handling multiple games.
- Compatible with standard chess rules.
- Communication between server and web interface using WebSockets.
- Simple and intuitive web interface for playing chess.
- Compatibility with UCI protocol (via an http wrapper) for chess engines.
- Play chess against [Euphron](https://github.com/Omikrone/Euphron), a chess engine developed in C++ !


## Installation

This project is compatible with Windows and Linux, and requires CMake for building.

### Prerequisites

Make sure you have the following dependencies installed:
- CMake (see [CMake installation guide](https://cmake.org/install/))
- A C++ compiler (e.g., g++)
- Node.js and npm (see [Node.js installation guide](https://nodejs.org/en/download/))

Moreover, this project uses [Crow](https://github.com/CrowCpp/Crow) for handling HTTP requests and WebSockets.
You can either let CMake install it for you or install Crow manually by following the instructions on its [GitHub repository](https://github.com/CrowCpp/Crow).

Or, you can use [Docker](https://www.docker.com/get-started) to run the project without installing dependencies manually.

### Build with Docker

To build and run the project using Docker, follow these steps:

1. Build the images with Docker Compose:
```bash
    docker-compose build
```

2. You can then start the backend server and frontend with:
```bash
    docker-compose up
```

### Build the Project (from source)

If you prefer to build the project from source, follow these steps:

1. Clone the repository:
```bash
    git clone https://github.com/Omikrone/Chessgame.git
    cd Chessgame
```

2. Build the C++ server using CMake:
```bash
    cmake -S . -B build
    cmake --build build --config Release
```

3. Install the frontend dependencies:
```bash
    cd ../frontend
    npm install
```

### Start the game

After building the project manually, you can start the chess game as follows:

1. Start the C++ server:
```bash
    ./build/chessgame.exe
```

2. Start the frontend:
```bash
    cd ../frontend
    npm run dev
```

3. Don't forget to install and run [Euphron](https://github.com/Omikrone/Euphron) chess engine if you want to play against it.

4. Open your web browser and navigate to `http://localhost:5173` to access the chess game interface. 


## Roadmap

Future improvements for this project may include:
- Implementing a multiplayer mode over the network.
- Add a clock/timer feature for timed games.
- Add compatibility with more chess engines.