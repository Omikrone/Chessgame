# Change Log


## [1.2.1] - 2025-10-25

### Added
- Compatibility with version 1.3.0 of the Chessboard library.


## [1.2.0] - 2025-10-19

### Added

- Compatibility with UCI protocol for chess engines.
- Improved session management for handling multiple and idle games.
- Docker support for easier deployment.

### Fixed

- Fixed a bug causing the server to crash on invalid moves.
- Fixed launch without docker.
- Fixed endgame detection in some edge cases.

## [1.1.0] - 2025-09-28

### Added

- Play chess against another player on the same computer.

### Changed

- Separation between game logic and server code for better maintainability (see [Chessboard library](https://github.com/Omikrone/Chessboard)).


## [1.0.0] - 2025-09-13

### Added

- Initial release of the chess game.