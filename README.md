# Chess Game - Simple Chess Game


## Introduction

This project is a straightforward chess game built with C++. It features a C++ backend server and a web-based frontend developed using Vite.
This project is intended to be the main base of the future chess engine "Euphron".

- **Current version:** 1.0.0


## Features

This chess game includes the following features:
- Basic chess rules implemented.
- Communication between server and web interface using WebSockets.
- Play chess against another player on the same computer.


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

2. Build the C++ server using CMake:
```bash
    cd backend
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
    ./chess
```

2. Start the frontend:
```bash
    cd ../frontend
    npm run dev
```
3. Open your web browser and navigate to `http://localhost:5173` to access the chess game interface. 


## Future Improvements

Future improvements for this project may include:
- [ ] Adding zobrist hashing for detecting threefold repetition and other advanced rules.
- [ ] Better Handling of the game session and player management.
- [ ] Implementing a multiplayer mode over the network.
- [ ] Enhancing the user interface with more features and better design.
- [ ] Adding a compatibility mode for chess engines (like Euphron in the future).