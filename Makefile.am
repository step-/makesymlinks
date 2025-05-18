bin_PROGRAMS = makesymlinks
man_MANS = man/makesymlinks.1
doc_DATA = doc/CHANGELOG.md

##
## https://autotools.io/automake/nonrecursive.html
##

makesymlinks_SOURCES = src/makesymlinks.c
makesymlinks_CFLAGS = -Wall -Wextra -Os

$(top_srcdir)/man/makesymlinks.1: $(top_srcdir)/doc/makesymlinks.1.h2m \
	$(top_srcdir)/src/makesymlinks.c
	@[ $(HELP2MAN) = false ] && exit; \
	$(HELP2MAN) -N -h-h -v-V -i "$<" \
	--name='A bulk symbolic link creator acting as a Unix filter' \
	./makesymlinks | \
	awk '/^Exit Status/ {print ".SH \"EXIT STATUS\""; getline; next} {print}' \
	> "$@"

## Distribution archive
## usage: ./configure && make dist-gzip; make distclean
EXTRA_DIST = \
	$(CONFIG_HEADER) README.md \
	$(man_MANS) \
	$(doc_DATA) doc/makesymlinks.1.h2m

SUFFIXES = .c

## Run the C preprocessor
## usage: ./configure && make source/main.i; make distclean; rm source/main.i
.c.i:
	$(COMPILE) $(GTK_CFLAGS) -E $< -o $@

