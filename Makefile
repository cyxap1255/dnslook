CC = gcc
CFLAGS = -Wall -Wextra -o
TARGET = dnslook
PREFIX = /usr/local/bin

SRCS = dnslook.c

all:
	$(CC) $(SRCS) $(CFLAGS) $(TARGET)

install: $(TARGET)
	mkdir -p $(DESTDIR)$(PREFIX)
	cp -f $(TARGET) $(DESTDIR)$(PREFIX)/
	chmod 755 $(DESTDIR)$(PREFIX)/$(TARGET)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/$(TARGET)
