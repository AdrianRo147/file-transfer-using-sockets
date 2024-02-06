# Simple linux file transfer server made using sockets

[![build](https://github.com/AdrianRo147/file-transfer-using-sockets/actions/workflows/cmake-single-platform.yml/badge.svg)](https://github.com/AdrianRo147/file-transfer-using-sockets/actions/workflows/cmake-single-platform.yml)

## Configuration
- Port in main.c (client and server) `#define PORT`
- IP in server.c and client.c `#define IP_ADDRESS`

## Compile
```
cmake -B YOUR_BUILD_FOLDER --DCMAKE_BUILD_TYPE=Release
cmake --build YOUR_BUILD_FOLDER --config Release
```
