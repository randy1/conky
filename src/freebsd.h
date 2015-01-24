/* -*- mode: c; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

#ifndef FREEBSD_H_
#define FREEBSD_H_

#include "common.h"
#include <sys/param.h>
#include <sys/mount.h>
#include <sys/ucred.h>
#include <fcntl.h>
#include <kvm.h>
#if (defined(i386) || defined(__i386__))
#include <machine/apm_bios.h>
#endif /* i386 || __i386__ */

#ifndef HAVE_STATFS64
#define statfs64 statfs
#endif

int get_entropy_avail(unsigned int *);
int get_entropy_poolsize(unsigned int *);

#endif /*FREEBSD_H_*/
