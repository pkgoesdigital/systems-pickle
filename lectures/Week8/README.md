# Week 8 — Sockets

A minimal client/server pair over TCP on port 8098.

- **`head.c`** — the server. `socket()` → `bind()` → `listen()` → `accept()`,
  then reads one message, replies `"I got your message"`, and exits.
- **`node.c`** — the client. `socket()` → `gethostbyname("localhost")` →
  `connect()`, then sends a line you type and prints the reply.
- **`duSocket.c` / `duSocket.h`** — the professor's helper library wrapping
  the same calls in Java-shaped names (`setupServerSocket`, `callServer`,
  `serverSocketAccept`, `readInt`, `writeInt`). No `main()`, so `make` only
  compiles it.
- **`Client.java` / `Server.java`** — the same exercise in Java, for
  comparison. Not part of `make`.

## Run the pair

Two terminals, server first:

```bash
make head node
./build/head          # waiting for a call...
```

```bash
./build/node          # Please enter the message: _
```

Type a line and press enter. `head` prints
`Here is the message: <your line>`, `node` prints `I got your message`, and
both exit. `make test` automates exactly this.

## `SO_REUSEADDR`

`head.c` sets it before `bind()`:

```c
int reuse = 1;
setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
```

The 2019 version didn't, which is why re-running the server right after
stopping it printed `ERROR on binding`. When a TCP connection closes, the
listening side leaves the port in `TIME_WAIT` for roughly a minute so any
straggling packets can't be misdelivered to a new socket. `SO_REUSEADDR`
tells the kernel it's fine to bind anyway — standard for servers, and the
first thing to reach for when a port "is still in use" but nothing is
running.

## Byte order

Both files call `htons(portno)` — host to network byte order. Network byte
order is big-endian (most significant byte first), which may or may not match
your CPU; x86 is little-endian, so on your laptop `htons` really does swap
the bytes. See `lectures/Week4/lab4/tc.c` for the same idea from the other
direction: inspecting how an `int` is actually laid out in memory.
