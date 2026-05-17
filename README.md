# Ame HTTP Server

Ame HTTP Server is a small C++ TCP/HTTP server built directly on Linux socket
APIs. It opens a TCP socket on port `8080`, accepts incoming connections, reads
the client request, and returns a simple HTTP `200 OK` HTML page.

## Project Growth

The git history shows the project growing in small networking steps:

1. `98932b3` - Added the basic program structure with `main_server.cpp`, a
   `TCPServer` class declaration, and the first implementation file.
2. `29a1b41` - Added server startup, shutdown, logging, and error handling.
   This introduced the socket lifecycle around `startServer()` and
   `closeServer()`.
3. `ace530d` - Added socket address setup and binding, connecting the server to
   an IP address and port.
4. `e812572` - Added listening support so the socket can queue incoming client
   connections.
5. `5e0786d` - Added `acceptConnection()` to accept client connections from the
   listen queue.
6. `43594ec` - Added request reading from the connected client socket.
7. `afd28f8` - Added HTTP response construction and response sending.
8. Current working tree - Added CMake build support and wired `main()` to call
   `startListen()`, so the server now stays running and serves requests.

## Project Layout

```text
.
├── CMakeLists.txt
├── include/
│   └── Ame_http_tcpServer.h
└── src/
    ├── Ame_http_tcpServer.cpp
    └── main_server.cpp
```

## Requirements

- Linux or another POSIX-like environment with socket APIs
- CMake 3.16 or newer
- A C++ compiler with C++17 support
- `curl`, optional, for testing from the terminal

## Build

Configure and build the project from the repository root:

```bash
cmake -S . -B build
cmake --build build
```

The executable is created at:

```text
build/ame_http_server
```

## Run

Start the server:

```bash
./build/ame_http_server
```

Expected terminal output:

```text
Listening on Address0.0.0.0Port: 8080

========= Waiting for a new connection =========
```

The server keeps running and waits for requests on:

```text
http://127.0.0.1:8080
```

Stop it with `Ctrl+C`.

## See The Output

In another terminal, send a request with `curl`:

```bash
curl -i http://127.0.0.1:8080
```

Expected response:

```http
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 100

<!DOCTYPE html><html lang="en"><body><h1> HOME </h1><p> Hello from your Server :) </p></body></html>
```

You can also open this URL in a browser:

```text
http://127.0.0.1:8080
```

The page displays:

```text
HOME
Hello from your Server :)
```

## How It Works

`main_server.cpp` creates a `http::TCPServer` bound to `0.0.0.0:8080` and calls
`startListen()`.

The `TCPServer` class:

1. Creates a socket with `socket(AF_INET, SOCK_STREAM, 0)`.
2. Binds it to the configured address and port with `bind()`.
3. Starts listening with `listen()`.
4. Waits for clients with `accept()`.
5. Reads request bytes from the client socket with `read()`.
6. Sends a basic HTTP response with `write()`.

This is a learning-focused server. It handles one accepted connection at a time
inside a blocking loop and returns the same HTML response for every request.

