/*
 * TS utils for test.
 * (C) 2017 QPE <qpe@users.noreply.github.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <errno.h>
#include <stdio.h>
#include <libgen.h>
#include <stdarg.h>
#include <string.h>
#include <linux/limits.h>

#include "msg.h"

#define MSG_SIZE_MAX  2048

void _pmsg(const char *fname, message_type_t msgtype, const char *fmt, ...)
{
	va_list list;
	int lasterr = 0;
	char msg[MSG_SIZE_MAX] = {0};
	const char *bname;
	char buf[PATH_MAX] = {0};

	if (msgtype == MSG_SYSERROR) {
		lasterr = errno;
	}

	/* get filename */
	strcpy(buf, fname);
	bname = basename(buf);

	va_start(list, fmt);
	vsnprintf(msg, sizeof(msg) - 1, fmt, list);
	va_end(list);

	switch(msgtype) {
	case MSG_SYSERROR:
		fprintf(stderr, "%s: %s(errno=%d)\n", bname, msg, lasterr);
		break;
	case MSG_ERROR:
	case MSG_PACKETERROR:
		fprintf(stderr, "%s: %s\n", bname, msg);
		break;
	default:
		printf("%s: %s\n", bname, msg);
		break;
	}
}
