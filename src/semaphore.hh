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

#ifndef SEMAPHORE_HH
#define SEMAPHORE_HH

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <stdexcept>

#ifndef __linux__
#include <stdlib.h>
#endif

#include <semaphore.h>

class semaphore {
	sem_t sem;

	semaphore(const semaphore &) = delete;
	semaphore& operator=(const semaphore &) = delete;
public:
	semaphore(unsigned int value = 0) throw(std::logic_error)
	{
		if(sem_init(&sem, 0, value))
			throw std::logic_error(strerror(errno));
	}

	~semaphore() throw()
	{ sem_destroy(&sem); }

	void post() throw(std::overflow_error)
	{
		if(sem_post(&sem))
			throw std::overflow_error(strerror(errno));
	}

	void wait() throw()
	{
		while(sem_wait(&sem)) {
			if(errno != EINTR)
				abort();
		}
	}

	bool trywait() throw()
	{
		while(sem_trywait(&sem)) {
			if(errno == EAGAIN)
				return false;
			else if(errno != EINTR)
				abort();
		}
		return true;
	}
};

#endif
