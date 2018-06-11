
# Build

```
clang -std=c11 -o chttp chttp.c usage.c socket_util.c string_util.c die_with_error.c handle_request.c line_reader.c
```

# Run

./chttp <port> <path-to-files>

```
./chttp 8080 test
```

# LOC

Comfortably under 200.

```
$ cat *.h *.c | sed 's/^\s*//' | grep -x '.\{2,\}' | wc -l
195
```
