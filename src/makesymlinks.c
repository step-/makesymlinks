/* vim:set ts=8 sw=4 et: */
/*
makesymlinks - A bulk symbolic link creator acting as a Unix filter.

Copyright (C) 2025 step, https://github.com/step-

Licensed under the GNU General Public License Version 2

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/
/*
glibc C program that reads pairs of lines from stdin: the first line is the link name
(the path where the symlink will be created), and the second line is the target
path (the file or directory the symlink points to). It then creates the symbolic
link accordingly.

STANDARDS:
getline() and getdelim() were originally GNU extensions. They were
standardized in POSIX.1-2008. warn() is a nonstandard BSD extension.
*/

#define _GNU_SOURCE

#include <err.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "autoconfig.h"

void
print_usage (const char *progname)
{
    printf ("Usage: %s [Options]\n", progname);
    printf ("  Create symbolic links from pairs of lines on stdin: the first line\n"
            "  is the link name path, and the second line is the target path.\n"
            "Options:\n"
            "  -f            Overwrite any existing link names\n"
            "  -h            Print this usage message and exit\n"
            "  -i <path>     Read lines from file <path>\n"
            "  -V            Print version and exit\n"
            "  -v            Print the created links\n"
            "Exit Status\n"
            "  The program exits 0 if it can create all the links, and 1 otherwise. Links\n"
            "  are created as soon as a line pair is read. Failing to create a link does\n"
            "  not halt the program. However execution stops immediately when an invalid\n"
            "  link name or target path is detected.\n");
}

int
main (int argc, char *argv[])
{
    char *nl;
    ssize_t nread;
    size_t alloc_size = 4096;
    int retval = EXIT_SUCCESS;
    FILE *stream = stdin;
    char *input_path = NULL;
    char *linkname = NULL;
    char *target = NULL;
    int opt;
    int opt_force = 0;
    int opt_verbose = 0;

    while ((opt = getopt (argc, argv, "fhi:Vv")) != -1)
    {
        switch (opt)
        {
        case 'f':
            opt_force = 1;
            break;
        case 'h':
            print_usage (argv[0]);
            goto out;
        case 'i':
            input_path = optarg;
            break;
        case 'V':
            printf ("%s\n", VERSION);
            goto out;
        case 'v':
            opt_verbose = 1;
            break;
        default:
            print_usage (argv[0]);
            retval = EXIT_FAILURE;
            goto out;
        }
    }
    if (optind != argc)
    {
        print_usage (argv[0]);
        retval = EXIT_FAILURE;
        goto out;
    }
    if (input_path)
    {
        if ((stream = fopen (input_path, "r")) == NULL)
        {
            warn ("'%s'", input_path);
            retval = EXIT_FAILURE;
            goto out;
        }
    }

    linkname = malloc (alloc_size);
    target = malloc (alloc_size);
    while (1)
    {
        errno = 0;
        nread = getline (&linkname, &alloc_size, stream);
        if (nread == -1)
        {
            if (errno)
            {
                warn ("Error: Cannot read link name");
                retval = EXIT_FAILURE;
            }
            goto out;
        }
        if ((nl = strchr (linkname, '\n')))
        {
            *nl = '\0';
        }

        errno = 0;
        nread = getline (&target, &alloc_size, stream);
        if (nread == -1)
        {
            if (errno == 0)
            {
                errno = ENODATA;
            }
            warn ("Error: Expected a target path for link name '%s'", linkname);
            retval = EXIT_FAILURE;
            goto out;
        }
        if ((nl = strchr (target, '\n')))
        {
            *nl = '\0';
        }

        if (opt_force && unlink (linkname) == -1 && errno != ENOENT)
        {
            warn ("Warning: Cannot delete link name '%s'", linkname);
            retval = EXIT_FAILURE;
            continue;
        }
        if (symlink (target, linkname) == -1)
        {
            warn ("Warning: Cannot create symbolic link: %s -> %s", linkname,
                  target);
            retval = EXIT_FAILURE;
            continue;
        }
        else if (opt_verbose)
        {
            printf("%s -> %s\n", linkname, target);
        }
    }

out:
    free (linkname);
    free (target);
    if (stream)
    {
        fclose (stream);
    }
    return retval;
}
