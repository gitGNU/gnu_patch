/* utility functions for `patch' */

/* Copyright (C) 1986 Larry Wall

   Copyright (C) 1992, 1993, 1997, 1998, 1999, 2001, 2002, 2003, 2009, 2010
   Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <utimens.h>
#include <timespec.h>
#include <stat-time.h>

#include <timespec.h>

/* An upper bound on the print length of a signed decimal line number.
   Add one for the sign.  */
#define LINENUM_LENGTH_BOUND (sizeof (lin) * CHAR_BIT / 3 + 1)

XTERN enum backup_type backup_type;

bool ok_to_reverse (char const *, ...) __attribute__ ((format (printf, 1, 2)));
void ask (char const *, ...) __attribute__ ((format (printf, 1, 2)));
void say (char const *, ...) __attribute__ ((format (printf, 1, 2)));

void fatal (char const *, ...)
	__attribute__ ((noreturn, format (printf, 1, 2)));
void pfatal (char const *, ...)
	__attribute__ ((noreturn, format (printf, 1, 2)));

char *fetchname (char const *, int, char **, struct timespec *);
char *parse_name (char const *, int, char const **);
char *savebuf (char const *, size_t);
char *savestr (char const *);
char const *version_controller (char const *, bool, struct stat const *, char **, char **);
bool version_get (char const *, char const *, bool, bool, char const *, struct stat *);
int create_file (char const *, int, mode_t, bool);
int systemic (char const *);
char *format_linenum (char[LINENUM_LENGTH_BOUND + 1], lin);
void Fseek (FILE *, file_offset, int);
void copy_file (char const *, char const *, struct stat *, int, mode_t, bool);
void append_to_file (char const *, char const *);
void exit_with_signal (int) __attribute__ ((noreturn));
void ignore_signals (void);
void init_backup_hash_table (void);
void init_time (void);
void xalloc_die (void) __attribute__ ((noreturn));
void create_backup (char *, struct stat *, int *, bool);
void move_file (char const *, int volatile *, struct stat const *, char *, mode_t, bool);
void read_fatal (void) __attribute__ ((noreturn));
void remove_prefix (char *, size_t);
void removedirs (char *);
void set_signals (bool);
void write_fatal (void) __attribute__ ((noreturn));
bool file_already_seen (struct stat const *);

static inline char const *
skip_spaces (char const *str)
{
  while (ISSPACE (*str))
    str++;
  return str;
}
