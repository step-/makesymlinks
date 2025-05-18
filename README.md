# makesymlinks
A bulk symbolic link creator acting as a Unix filter

## INSTALLING

This project builds using GNU Autotools.

1. **Release build**: install the binary and its documentation:

   ```sh
   ( mkdir -p build && cd build && ../configure CFLAGS= &&
     make clean all install-strip install-man )
   ```

**Optional build-time dependencies**

_The source distribution archive includes pre-formatted manual pages.
If you need to regenerate them, you will need the following tools:_

  * [GNU help2man] to build the man1 page.

[GNU help2man]: <https://www.gnu.org/software/help2man/>

## Building from the Git directory

When building from the Git directory, you must first generate the
configuration files for your build target by running `autoreconf -fiv`.
