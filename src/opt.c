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

#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>

#include "msg.h"
#include "opt.h"

static const char show_version_str[] =
"ts utils for test " GIT_VERSION " - (C) 2017 QPE.\n"
"  dev info: https://github.com/qpe/ts_utils\n";

static const char usage_str[] =
"Usage: %s [options] dir\n"
"[options]\n"
"  -d,--device=DEVICE  target device(DTV)\n"
"  -i,--input=FILE     target file(TS file)\n"
"\n"
"  -h,--help           show this help meesage\n"
"  -v,--version        show version\n"
"\n"
"[DTV only]\n"
"\n"
"[file source only]\n"
"\n";

static const char shortopts[] = {
	"d:i:hv"
};

static const struct option longopts[] = {
	{"device",  required_argument, NULL, 'd'},
	{"input",   required_argument, NULL, 'i'},
	{"help",    no_argument,       NULL, 'h'},
	{"version", no_argument,       NULL, 'v'},
	/* end of option */
	{NULL, 0, NULL, 0},
};


enum error_msg_t {
	ERR_OPT_INFILE_MUST_ONE,
	ERR_OPT_INTYPE_NOTDEFINED,
	ERR_OPT_DIR_NOT_DEFINED,
	ERR_OPT_DIR_PATH_TOO_LONG,
	ERR_OPT_PATH_NOT_DIR,
	ERR_OPT_DIR_STAT_FAILED,
};
static const char *error_msg[] = {
	"input related option can be defined only once.",
	"Either -d or -i must be defined.",
	"output diretory must be defined.",
	"output diretory path too long.",
	"specified path is not directory.",
	"fail to stat of specified dir path.",
};


tsutils_opt_t g_opt;

void show_version(void)
{
	printf(show_version_str);
}

void show_usage(const char *prog)
{
	printf(usage_str, prog);
}

static void opt_init()
{
	g_opt.help = false;
	g_opt.version = false;
	g_opt.in_type = OPT_IN_NONE;
	g_opt.input = NULL;
	g_opt.device = NULL;
	memset(g_opt.dir, 0, PATH_MAX);
}



bool opt_parse(int argc, char * const argv[])
{
	int opt;
	int longindex;

	opt_init();

	while ((opt = getopt_long(argc, argv, shortopts, longopts, &longindex))
	       != -1) {
		switch(opt) {
		case 'h':
			g_opt.help = true;
			break;
		case 'v':
			g_opt.version = true;
			break;
		case 'i':
			if(optarg) {
				g_opt.in_type = OPT_IN_FILE;
				g_opt.input = optarg;
			}
			break;
		case 'd':
			if(optarg) {
				g_opt.in_type = OPT_IN_DTB;
				g_opt.device = optarg;
			}
			break;
		default:
			return false;
			break;
		}
	}

	/* define target dir */
	if((argc - 1) == optind) {
		size_t len = strlen(argv[optind]) + 1;
		if(len <= PATH_MAX)
			memcpy(g_opt.dir, argv[optind], len);
	}

	return true;
}

static bool opt_check_dir()
{
	size_t len = 0;
	struct stat sbuf;

	len = strlen(g_opt.dir);

	/* remove last slash */
	if(len > 0 && g_opt.dir[len - 1] == '/') {
		g_opt.dir[len - 1] = '\0';
	}

	if(stat(g_opt.dir, &sbuf) != 0) {
		pmsg(MSG_SYSERROR, error_msg[ERR_OPT_DIR_STAT_FAILED]);
		return false;
	}

	if(!S_ISDIR(sbuf.st_mode)) {
		pmsg(MSG_ERROR, error_msg[ERR_OPT_PATH_NOT_DIR]);
		return false;
	}

	return true;
}

bool opt_check(void) {

	/* check input exists. */
	if(g_opt.in_type == OPT_IN_NONE) {
		pmsg(MSG_ERROR, error_msg[ERR_OPT_INTYPE_NOTDEFINED]);
		return false;
	}

	/* dir defined? */
	if(strlen(g_opt.dir) == 0) {
		pmsg(MSG_ERROR, error_msg[ERR_OPT_DIR_NOT_DEFINED]);
		return false;
	}
	if(!opt_check_dir()) {
		return false;
	}

	return true;
}
