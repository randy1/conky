/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*-
 * vim: ts=4 sw=4 noet ai cindent syntax=cpp
 *
 * Conky, a system monitor, based on torsmo
 *
 * Please see COPYING for details
 *
 * Copyright (C) 2010 Pavel Labath et al.
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
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "config.h"

#include "c++wrap.hh"

#include <fcntl.h>
#include <string.h>

std::string strerror_r(int errnum)
{
	char buf[100];
#ifdef _GNU_SOURCE
	return strerror_r(errnum, buf, sizeof(buf));
#else
	strerror_r(errnum, buf, sizeof(buf));
	return buf;
#endif
}

std::pair<int, int> pipe2(int flags)
{
	int fd[2];
#ifdef __linux__
	if (pipe2(fd, flags) == -1)
        throw errno_error("pipe2");
#else
	if (pipe(fd) == -1)
		throw errno_error("pipe");
	else if (fcntl(fd[0], F_SETFD, flags) == -1)
		throw errno_error("fcntl fd[0]");
	else if (fcntl(fd[1], F_SETFD, flags) == -1)
		throw errno_error("fcntl fd[1]");
#endif
	else
		return std::pair<int, int>(fd[0], fd[1]);
}
