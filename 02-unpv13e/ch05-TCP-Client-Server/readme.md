## How to use

### Build the server and client

```
make
```

### Run the server

```
./server
```

### Use client to test the server

```
./client localhost
```

### Use `nc(netcat)` to test the server

```
nc localhost 8082
```

**Note**: nc, netcat 不仅可以用于测试 TCP, UDP ，还可以用于 Unix Domain Socket(UDS) 的测试.
