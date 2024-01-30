# Simple linux file transfer server made using sockets

[![build](https://github.com/AdrianRo147/file-transfer-using-sockets/actions/workflows/cmake-single-platform.yml/badge.svg)](https://github.com/AdrianRo147/file-transfer-using-sockets/actions/workflows/cmake-single-platform.yml)

## Configuration
You can change port in main.c files on line with
`#define PORT 8888`
but make sure to change it for both client and server, otherwise you won't connect to your socket


## Compile
```
cmake -B YOUR_BUILD_FOLDER --DCMAKE_BUILD_TYPE=Release
cmake --build YOUR_BUILD_FOLDER --config Release
```
