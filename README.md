# Client Server Chat System in C

A server and client model in C using sockets to send chats back and forth. 

## Table of Contents

- [Description](#description)
- [Installation](#installation)
- [Usage](#usage)

## Description
This project uses sockets to send messages between a server and client on the same network.

## Installation

Clone the repository:

```sh
git clone https://github.com/aaron10l/c-chat-server.git
cd c-chat-server
```

## Usage

**Running on same machine:**
compile both server.c and client.c using:
    ```bash
    gcc client.c -o client
    ```
then run both of them, each on separate terminals:
**Starting the server**
   ```bash
   ./server 9898
   ```

**Starting the client**
    ```bash
    ./client 127.0.0.1 9898
    ```

