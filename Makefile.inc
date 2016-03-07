DESTDIR =
USRBINDIR = /usr/bin
BINDIR = /bin
MANDIR = /usr/share/man
LIBDIR = /usr/lib
ETCDIR = /etc

AR?=ar
RANLIB?=ranlib

VERSION = 1.99.8

NAME = cards-$(VERSION)

CXXFLAGS += -DNDEBUG -std=c++11
CXXFLAGS += -O2 -Werror -pedantic -D_GNU_SOURCE -DVERSION=\"$(VERSION)\" \
	    -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -fPIC
CFLAGS += -DNDEBUG -std=gnu11
CFLAGS += -D_GNU_SOURCE

LIBARCHIVELIBS := $(shell pkg-config --libs --static libarchive)
LIBCURLLIBS := $(shell pkg-config --libs --static libcurl)

LDFLAGS += $(LIBARCHIVELIBS)


# End of file
