
# Build

```
clang -std=c11 -o chttp chttp.c socket_util.c string_util.c die_with_error.c handle_request.c line_reader.c
```

# Run

./chttp <port> <path-to-files>

```
./chttp 8080 test
```