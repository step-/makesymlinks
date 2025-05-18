# Project name, version number, bug report address, tar name, url.
AC_INIT([makesymlinks], [1.0.0], [https://github.com/step-/makesymlinks/issues], [makesymlinks], [https://github.com/step-/makesymlinks])

AC_CONFIG_HEADERS([autoconfig.h])

# Sanity check.
AC_CONFIG_SRCDIR([src/makesymlinks.c])

# Keep AC tools in their own directory ./build-aux.
AC_CONFIG_AUX_DIR([build-aux])

# 'foreign': follow minimal GNU coding standards not to
# clobber ChangeLog, COPYING, AUTHORS, INSTALL, README etc.
# 'subdir-objects': keep .o files in their own sub-directory.
# 'no-installman': require "make install-man" to install the manual pages.
# 'silent-rules': run Makefile rules silently.
AM_INIT_AUTOMAKE([1.11 foreign subdir-objects no-installman silent-rules
	-Wall -Werror])

AC_PATH_PROG(HELP2MAN, [help2man], [false])

# C compiler check.
AC_PROG_CC

# Tell automake to create a Makefile.
AC_CONFIG_FILES([Makefile])

# Generate files/dirs.
AC_OUTPUT
