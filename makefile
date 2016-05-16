CC=gcc
CFLAGS=-rdynamic -fPIC -D_GNU_SOURCE -shared -Wall
LIB32_PATH=/usr/lib/i386-linux-gnu
LIB64_PATH=/usr/lib/x86_64-linux-gnu
BIN_PATH=/usr/bin

all: libstrangle64.so libstrangle32.so

libstrangle64.so:
	$(CC) $(CFLAGS) -m64 -o libstrangle64.so libstrangle.c

libstrangle32.so:
	$(CC) $(CFLAGS) -m32 -o libstrangle32.so libstrangle.c

install: all
	install -m=755 -T libstrangle64.so $(LIB64_PATH)/libstrangle.so
	install -m=755 -T libstrangle32.so $(LIB32_PATH)/libstrangle.so
	install -m=755 -T strangle.sh $(BIN_PATH)/strangle

clean:
	rm libstrangle64.so
	rm libstrangle32.so

