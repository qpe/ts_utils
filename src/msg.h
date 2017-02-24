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
#ifndef __TSUTILS_MSG_H__
#define __TSUTILS_MSG_H__

#define pmsg(type, ...) _pmsg(__FILE__, type, __VA_ARGS__)

typedef enum {
	MSG_NONE,
	MSG_WARNING,
	MSG_ERROR,
	MSG_SYSERROR,
	MSG_NOTIFY,
	MSG_DISP,
	MSG_PACKETERROR,
	MSG_DEBUG,
} message_type_t;

void _pmsg(const char *fname, message_type_t msgtype, const char *fmt, ...);

#endif
