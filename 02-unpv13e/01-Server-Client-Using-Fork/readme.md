## Server-Client

### How to use

```
make

# run the server

./server.o

# run the the client, you can run mulitple clients.
./client
./client
```

### Zombie Process

Because we don't use `wait, waitpid`，when one client disconnected from the server the process will become one zombie process.

- [ ] Handle Zombie Process.
