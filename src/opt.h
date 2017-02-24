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
#ifndef __TSUTILS_OPT_H__
#define __TSUTILS_OPT_H__

#include <stdbool.h>
#include <stdint.h>
#include <linux/limits.h>

#define OPT_IN_NONE 0x00
#define OPT_IN_FILE 0x01
#define OPT_IN_DTB  0x02

typedef struct {
	uint8_t in_type;
	char *input;
	char *device;
	char dir[PATH_MAX];
	bool help;
	bool version;
} tsutils_opt_t;

void show_version(void);
void show_usage(const char *prog);
bool opt_parse(int argc, char * const argv[]);
bool opt_check(void);

/*
 * if you need to get option...
 * extern tsutils_opt_t g_opt;
 */

#endif
