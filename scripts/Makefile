include ../Makefile.inc

all: pkgmk ports

pkgmk: pkgmk.in

ports: ports.in
%: %.in
	sed -e "s/#VERSION#/$(VERSION)/" $< > $@


.PHONY:	install clean distclean dist

install: all
	install -D -m0755 pkgmk $(DESTDIR)$(USRBINDIR)/pkgmk
	install -D -m0755 p_linux_common_func.sh $(DESTDIR)$(USRBINDIR)/p_linux_common_func.sh
	install -D -m0644 pkgmk.conf $(DESTDIR)$(ETCDIR)/pkgmk.conf.example
	install -D -m0755 ports $(DESTDIR)$(USRBINDIR)/ports
	install -D -m0755 cards.driver $(DESTDIR)/var/lib/pkg/drivers/cards


clean:
	rm -f pkgmk
	rm -f ports

distclean: clean
	rm -f pkgmk
	rm -f ports

# End of file
