CC=gcc
CFLAGS=-rdynamic -fPIC -D_GNU_SOURCE -shared -Wall
prefix=$(DESTDIR)/usr
bindir=$(prefix)/bin
libdir=$(prefix)/lib
LIB32_PATH=$(libdir)/i386-linux-gnu
LIB64_PATH=$(libdir)/x86_64-linux-gnu

all: libstrangle64.so libstrangle32.so

libstrangle64.so:
	$(CC) $(CFLAGS) -m64 -o libstrangle64.so libstrangle.c

libstrangle32.so:
	$(CC) $(CFLAGS) -m32 -o libstrangle32.so libstrangle.c

install: all
	install -m 0755 -T libstrangle64.so $(LIB64_PATH)/libstrangle.so
	install -m 0755 -T libstrangle32.so $(LIB32_PATH)/libstrangle.so
	install -m 0755 -T strangle.sh $(bindir)/strangle

clean:
	rm -f libstrangle64.so
	rm -f libstrangle32.so
