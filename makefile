CC=gcc
CFLAGS=-rdynamic -fPIC -D_GNU_SOURCE -shared -Wall -std=c99 -ldl
LDFLAGS=-Wl,-z,relro,-z,now
prefix=/usr/local
bindir=$(prefix)/bin
libdir=$(prefix)/lib
DOC_PATH=$(prefix)/share/doc/libstrangle
LIB32_PATH=$(libdir)/libstrangle/lib32
LIB64_PATH=$(libdir)/libstrangle/lib64

all: libstrangle64.so libstrangle32.so libstrangle.conf

libstrangle.conf:
	@echo "$(LIB32_PATH)/" > libstrangle.conf
	@echo "$(LIB64_PATH)/" >> libstrangle.conf

libstrangle64.so:
	$(CC) $(CFLAGS) $(LDFLAGS) -m64 -o libstrangle64.so libstrangle.c

libstrangle32.so:
	$(CC) $(CFLAGS) $(LDFLAGS) -m32 -o libstrangle32.so libstrangle.c

install: all
	install -m 0644 -D -T libstrangle.conf $(DESTDIR)/etc/ld.so.conf.d/libstrangle.conf
	install -m 0755 -D -T libstrangle64.so $(DESTDIR)$(LIB32_PATH)/libstrangle.so
	install -m 0755 -D -T libstrangle32.so $(DESTDIR)$(LIB64_PATH)/libstrangle.so
	install -m 0755 -D -T strangle.sh $(DESTDIR)$(bindir)/strangle
	install -m 0644 -D -T COPYING $(DESTDIR)$(DOC_PATH)/LICENSE
	ldconfig

clean:
	rm -f libstrangle64.so
	rm -f libstrangle32.so
	rm -f libstrangle.conf

uninstall:
	rm -f $(DESTDIR)/etc/ld.so.conf.d/libstrangle.conf
	rm -f $(DESTDIR)$(LIB32_PATH)/libstrangle.so
	rm -f $(DESTDIR)$(LIB64_PATH)/libstrangle.so
	rm -f $(DESTDIR)$(bindir)/strangle
	rm -f $(DESTDIR)$(DOC_PATH)/LICENSE
