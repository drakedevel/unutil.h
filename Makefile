CFLAGS = -fPIC
LIBS = -pthread -lm -lssl

all: libunutil.so

libunutil.so: unutil.o
	$(CC) $(LIBS) -shared -o $@ -fPIC $^

test: libunutil.so test.o
	$(CC) $(LIBS) -o $@ $^
