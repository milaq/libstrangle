CC=gcc
CFLAGS=-rdynamic -fPIC -shared -Wall -std=c99
LDFLAGS=-Wl,-z,relro,-z,now -ldl
prefix=/usr/local
bindir=$(prefix)/bin
libdir=$(prefix)/lib
DOC_PATH=$(prefix)/share/doc/libstrangle
LIB32_PATH=$(libdir)/libstrangle/lib32
LIB64_PATH=$(libdir)/libstrangle/lib64
SOURCEDIR=src/
BUILDDIR=build/
SOURCES=$(wildcard $(SOURCEDIR)*.c)

all: $(BUILDDIR)libstrangle64.so $(BUILDDIR)libstrangle32.so $(BUILDDIR)libstrangle.conf

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)libstrangle.conf: $(BUILDDIR)
	@echo "$(LIB32_PATH)/" > $(BUILDDIR)libstrangle.conf
	@echo "$(LIB64_PATH)/" >> $(BUILDDIR)libstrangle.conf

$(BUILDDIR)libstrangle64.so: $(BUILDDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -m64 -o $(BUILDDIR)libstrangle64.so $(SOURCES)

$(BUILDDIR)libstrangle32.so: $(BUILDDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -m32 -o $(BUILDDIR)libstrangle32.so $(SOURCES)

install: all
	install -m 0644 -D -T $(BUILDDIR)libstrangle.conf $(DESTDIR)/etc/ld.so.conf.d/libstrangle.conf
	install -m 0755 -D -T $(BUILDDIR)libstrangle64.so $(DESTDIR)$(LIB32_PATH)/libstrangle.so
	install -m 0755 -D -T $(BUILDDIR)libstrangle32.so $(DESTDIR)$(LIB64_PATH)/libstrangle.so
	install -m 0755 -D -T $(SOURCEDIR)strangle.sh $(DESTDIR)$(bindir)/strangle
	install -m 0644 -D -T COPYING $(DESTDIR)$(DOC_PATH)/LICENSE
	ldconfig

clean:
	rm -f $(BUILDDIR)libstrangle64.so
	rm -f $(BUILDDIR)libstrangle32.so
	rm -f $(BUILDDIR)libstrangle.conf

uninstall:
	rm -f $(DESTDIR)/etc/ld.so.conf.d/libstrangle.conf
	rm -f $(DESTDIR)$(LIB32_PATH)/libstrangle.so
	rm -f $(DESTDIR)$(LIB64_PATH)/libstrangle.so
	rm -f $(DESTDIR)$(bindir)/strangle
	rm -f $(DESTDIR)$(DOC_PATH)/LICENSE
