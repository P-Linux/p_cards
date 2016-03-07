include ../Makefile.inc

MANPAGES = cards.8 ports.8 pkgadd.8 pkgrm.8 pkginfo.8 pkgmk.8 cards.conf.5 pkgmk.conf.5

all: man mantxt

man: $(MANPAGES)

mantxt: man $(MANPAGES:=.txt)

%.8.txt: %.8
	nroff -mandoc -c $< | col -bx > $@

%.fr.txt: %.fr
	nroff -mandoc -c $< | col -bx > $@

%.5.txt: %.5
	nroff -mandoc -c $< | col -bx > $@

%: %.in
	sed -e "s/#VERSION#/$(VERSION)/" $< > $@


install: all
	install -D -m0644 cards.8 $(DESTDIR)$(MANDIR)/man8/cards.8
	install -D -m0644 cards.conf.5 $(DESTDIR)$(MANDIR)/man5/cards.conf.5
	install -D -m0644 ports.8 $(DESTDIR)$(MANDIR)/man8/ports.8
	install -D -m0644 pkgadd.8 $(DESTDIR)$(MANDIR)/man8/pkgadd.8
	install -D -m0644 pkgrm.8 $(DESTDIR)$(MANDIR)/man8/pkgrm.8
	install -D -m0644 pkginfo.8 $(DESTDIR)$(MANDIR)/man8/pkginfo.8
	install -D -m0644 pkgmk.8 $(DESTDIR)$(MANDIR)/man8/pkgmk.8
	install -D -m0644 pkgmk.conf.5 $(DESTDIR)$(MANDIR)/man5/pkgmk.conf.5

clean:
	rm -f $(MANPAGES)
	rm -f $(MANPAGES:=.txt)

# End of file
