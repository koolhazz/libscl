# This file is part of the SCL software.
# The license which this software falls under is as follows:
#
# Copyright (C) 2004-2010 Douglas Jerome <douglas@backstep.org>
#
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 2.1 of the License, or (at
# your option) any later version.
#
# This library is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
# License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


# *****************************************************************************
#
# FILE NAME
#
#	$RCSfile: Makefile,v $
#	$Revision: 1.21 $
#	$Date: 2010/04/14 02:52:20 $
#
# PROJECT INFORMATION
#
#	Developed by:	SCL project
#	Developer:	Douglas Jerome, drj, <douglas@backstep.org>
#
# FILE DESCRIPTION
#
#	Small Container Library: makefile for the source code directory.
#
# CHANGE LOG
#
#	13apr10	drj	Fixed a hash table bug, so the SUBLEVEL revision level
#			increased.
#
#	04apr10	drj	Added callback context pointer; this changed the API
#			so the MINOR revision level increased and the SUBLEVEL
#			revision level is set to zero.
#
#	31mar10	drj	Changed __COPYRIGHT__, __TIMESTAMP__ and __REVISION__
#			to LIBSCL_COPYRIGHT, LIBSCL_TIMESTAMP and
#			LIBSCL_REVISION, respectively.  GCC added __TIMESTAMP__
#			so all three of were changed to be similar.
#
#	02feb07	drj	Fixed INSTALLPREFIX to be INSTALL_PREFIX.
#			More mindless finessing.
#
#	11jun06	drj	Removed verbose flag -v from commands.
#
#	09jun06	drj	General format changes and cleanup.
#
#	27sep05	drj	SCL version 1.0.2
#
#	27sep05	drj	SCL version 1.0.1
#
#	27jul05	drj	Mindless format changes to comments in this makefile.
#
#	14jul05	drj	Used ${ECHO} in more places.
#
#	11jul05	drj	SCL version 1.0.0 (official)
#			Updated copyright to include personal name.
#			Added use of ".depend" file.
#
#	10jul05	drj	Updated copyright dates and version number (vers 1.0.0).
#
#	16dec04	drj	SCL version 0.5.0
#
#	02dec04	drj	SCL version 0.1.2
#			Fixed generation of NAMELC to be more portable.
#
#	02dec04	drj	SCL version 0.1.1
#			Fixed OPTIMIZ to check /proc/cpuinfo only for Linux.
#			Removed -std=c99 and -Wextra from the gcc command line.
#
#	26nov04	drj	Added scl-config.  Separated shared, static libs for
#			the client flags.
#
#	23nov04	drj	SCL version 0.1.0
#			File generation.
#
# *****************************************************************************


# *************************************************************************** #
# Macro Definitions                                                           #
# *************************************************************************** #

# -- Product Configuration
#
MAJOR		= 1
MINOR		= 1
SUBLEVEL	= 1
VERSION		= ${MAJOR}.${MINOR}
FULL_VERSION	= ${MAJOR}.${MINOR}.${SUBLEVEL}

# -- Make Configuration
#
MAKEFLAGS	+= --no-print-directory
DEBUGFLAGS	= CDEBUGFLAGS=-DDEBUG CC_PARAMS=-g
OPTIMFLAGS	= CC_PARAMS=-O3

# -- Host Build Environment
#
DATE	= $(shell date)
OSTYPE	= $(shell                                                             \
	if [ "`uname -s`" = "SunOS" -a "`uname -r | cut -c 1`" = "5" ]; then  \
		echo "SOLARIS";                                               \
	fi;                                                                   \
	if [ "`uname -s`" = "Linux" ]; then                                   \
		echo "LINUX";                                                 \
	fi                                                                    \
	)

# -- Target Build Environment
#
OPTIMIZ	= $(shell                                                             \
	if [ "`uname -s`" = "Linux" ]; then                                   \
	if [ -n "`cat /proc/cpuinfo | egrep "^model name.*Athlon"`" ]; then   \
	if [ -n "`cat /proc/cpuinfo | egrep "^flags.* sse "`" ]; then         \
	echo "-march=athlon-xp -mfpmath=sse,387";                             \
	fi;                                                                   \
	fi;                                                                   \
	fi                                                                    \
	)

# -- Product Name
#
NAMEUC	= SCL
NAMELC	= $(shell echo ${NAMEUC} | tr '[:upper:]' '[:lower:]')

# -- Input Files
#
HEADERS	=		\
	SCL.h		\
	SCL_config.h	\
	SCL_hash.h	\
	SCL_list.h	\
	SCL_map.h	\
	SCL_queuebuf.h	\
	SCL_stackbuf.h	\
	SCL_symbol.h	\
	SCL_tree.h	\
	SCL_vector.h
OBJECTS	=		\
	config.o	\
	hash.o		\
	list.o		\
	map.o		\
	queuebuf.o	\
	stackbuf.o	\
	symbol.o	\
	tree.o		\
	vector.o
SOURCES	=		\
	config.c	\
	hash.c		\
	list.c		\
	map.c		\
	queuebuf.c	\
	stackbuf.c	\
	symbol.c	\
	tree.c		\
	vector.c

# -- Generated Files
#
CONFIG	= make_config.h
CONFIGN	= $(shell echo ${CONFIG} | tr '.' '_' | tr '[:lower:]' '[:upper:]')
SCLCFG	= ${NAMELC}-config
ARCHIVE	= lib${NAMELC}.a
LIBRARY	= lib${NAMELC}.so
SONAME	= lib${NAMELC}.so.${MAJOR}
SONAMEV	= lib${NAMELC}.so.${MAJOR}.${MINOR}.${SUBLEVEL}

# -- Install Locations
#
ifeq ("${INSTALL_PREFIX}","")
INSTALL_PREFIX	= /usr/local
endif
INSTALL_BIN	= ${INSTALL_PREFIX}/bin
INSTALL_INCLUDE	= ${INSTALL_PREFIX}/include/${NAMELC}
INSTALL_LIB	= ${INSTALL_PREFIX}/lib
INSTALL_LIBEXEC	= ${INSTALL_PREFIX}/libexec
INSTALL_SHARE	= ${INSTALL_PREFIX}/share/${NAMELC}


# *************************************************************************** #
# More Macro Definitions                                                      #
# *************************************************************************** #

# -- General Host Tools
#
CAT	= cat
CHMOD	= chmod
CP	= cp
ECHO	= echo
INSTALL	= install -c
LINK	= ln -f -s
MV	= mv
RM	= rm -f

# -- Target Development Tools
#
AR	= ar
CC	= gcc
LD	= ld
RANLIB	= ranlib
STRIP	= strip
SZ	= size

# -- cpp Flags
#
CPP_DEFINES	= ${CDEBUGFLAGS} -D_unix -D${OSTYPE} -D${NAMEUC}_EXPORTS
CPP_INCLUDES	= -I.
CPP_FLAGS	= -MMD ${CPP_DEFINES} ${CPP_INCLUDES}

# -- cc Flags
#
CC_COMPILER	= -ansi -c -fPIC -pipe ${CC_PARAMS} ${OPTIMIZ}
CC_WARNING	= -Wall -W -Wcast-align -Wshadow
CC_WARNING2	= -Wmissing-prototypes -Wmissing-declarations
CC_FLAGS	= ${CC_COMPILER} ${CC_WARNING} ${CC_WARNING2}

# -- ld Flags
#
LIB_DIRS	=
LIBS		= -lc
LD_SONAME_FLAGS	= -shared -Wl,-soname=${SONAME}

# -- Client Flags
#
CLIENT_CFLAGS	= -I${INSTALL_INCLUDE}
CLIENT_SHARLIBS	= -L${INSTALL_LIB} -Wl,-rpath,${INSTALL_LIB} -l${NAMELC} ${LIBS}
CLIENT_STATLIBS	= -L${INSTALL_LIB} -l${NAMELC} ${LIBS}


# *************************************************************************** #
# Make Rules                                                                  #
# *************************************************************************** #

%::	${PROJECTDIR}/RCS/%,v
	${CO} ${COFLAGS} $@ $<

.c.o:
	@${ECHO} "CC	$<"
	@${CC} ${CPP_FLAGS} ${CC_FLAGS} $<


# *************************************************************************** #
# Make Targets                                                                #
# *************************************************************************** #

.PHONY:	default
.PHONY:	testh
.PHONY:	clean config
.PHONY:	install uninstall
.PHONY:	debug optimize objects sources libs

# -----------------------------------------------------------------------------
# -- Default Target
# -----------------------------------------------------------------------------

default:	libs

# -----------------------------------------------------------------------------
# -- Debug Targets
# -----------------------------------------------------------------------------

testh:	${HEADERS}
	@for file in ${HEADERS}; do					\
		cfile=_`expr $${file} : "\(.*\)\.h"`.c;			\
		dfile=_`expr $${file} : "\(.*\)\.h"`.d;			\
		ofile=_`expr $${file} : "\(.*\)\.h"`.o;			\
		${RM} $${cfile} $${dfile};				\
		${ECHO} "#include \"$${file}\""    >> $${cfile};	\
		${ECHO} "int main() { return 0; }" >> $${cfile};	\
		make $${ofile};						\
		${RM} $${cfile} $${dfile} $${ofile};			\
	done

# -----------------------------------------------------------------------------
# -- Housekeeping Targets
# -----------------------------------------------------------------------------

clean:
	@${ECHO} "RM	*.d .depend"
	@${ECHO} "RM	${CONFIG} ${SCLCFG}"
	@${ECHO} "RM	OBJECTS ${ARCHIVE} ${LIBRARY} ${LIBRARY}.*"
	@${RM} ${OBJECTS:.o=.d} .depend
	@${RM} ${CONFIG} ${SCLCFG} ${OBJECTS} ${ARCHIVE} ${LIBRARY} ${LIBRARY}.*

config ${CONFIG}:	Makefile ${SCLCFG}
	@${ECHO} "RM	${CONFIG}"
	@${RM} ${CONFIG}
	@${ECHO} "CAT	${CONFIG}"
	@${ECHO} "/*"                                              >> ${CONFIG}
	@${ECHO} " * This file is generated by Makefile."          >> ${CONFIG}
	@${ECHO} " * Edits to this file will be lost."             >> ${CONFIG}
	@${ECHO} " */"                                             >> ${CONFIG}
	@${ECHO} ""                                                >> ${CONFIG}
	@${ECHO} "#ifndef ${NAMEUC}_${CONFIGN}"                    >> ${CONFIG}
	@${ECHO} "#define ${NAMEUC}_${CONFIGN} 1"                  >> ${CONFIG}
	@${ECHO} ""                                                >> ${CONFIG}
	@${ECHO} "static const char* const LIBSCL_COPYRIGHT = \"Copyright (C) 2004-2010 Douglas Jerome <douglas@backstep.org>\";" >> ${CONFIG}
	@${ECHO} "static const char* const LIBSCL_TIMESTAMP = __TIME__ \", \" __DATE__;"                                          >> ${CONFIG}
	@${ECHO} "static const char* const LIBSCL_REVISION  = \"vers. ${VERSION}\";"                                              >> ${CONFIG}
	@${ECHO} ""                                                >> ${CONFIG}
	@${ECHO} "#define CLIENT_CFLAGS   \"${CLIENT_CFLAGS}\""    >> ${CONFIG}
	@${ECHO} "#define CLIENT_SHARLIBS \"${CLIENT_SHARLIBS}\""  >> ${CONFIG}
	@${ECHO} "#define CLIENT_STATLIBS \"${CLIENT_STATLIBS}\""  >> ${CONFIG}
	@${ECHO} ""                                                >> ${CONFIG}
	@${ECHO} "#define MAKE_INSTALLDIR \"${INSTALL_PREFIX}\""   >> ${CONFIG}
	@${ECHO} "#define MAKE_BINDIR     \"${INSTALL_BIN}\""      >> ${CONFIG}
	@${ECHO} "#define MAKE_INCLUDEDIR \"${INSTALL_INCLUDE}\""  >> ${CONFIG}
	@${ECHO} "#define MAKE_LIBDIR     \"${INSTALL_LIB}\""      >> ${CONFIG}
	@${ECHO} "#define MAKE_LIBEXECDIR \"${INSTALL_LIBEXEC}\""  >> ${CONFIG}
	@${ECHO} "#define MAKE_SHAREDIR   \"${INSTALL_SHARE}\""    >> ${CONFIG}
	@${ECHO} ""                                                >> ${CONFIG}
	@${ECHO} "#endif"                                          >> ${CONFIG}

${SCLCFG}:	Makefile
	@${ECHO} "RM	${SCLCFG}"
	@${RM} ${SCLCFG}
	@${ECHO} "CAT	${SCLCFG}"
	@${ECHO} '#!/bin/sh'                                       >> ${SCLCFG}
	@${ECHO} ''                                                >> ${SCLCFG}
	@${ECHO} "prefix=\"${INSTALL_PREFIX}\""                    >> ${SCLCFG}
	@${ECHO} "credits=\"Copyright (C) 2004-2006 Douglas Jerome <douglas@backstep.org>\""                                                       >> ${SCLCFG}
	@${ECHO} "version=\"${FULL_VERSION}\""                     >> ${SCLCFG}
	@${ECHO} "cflags=\"${CLIENT_CFLAGS}\""                     >> ${SCLCFG}
	@${ECHO} "sharedlibs=\"${CLIENT_SHARLIBS}\""               >> ${SCLCFG}
	@${ECHO} "staticlibs=\"${CLIENT_STATLIBS}\""               >> ${SCLCFG}
	@${ECHO} ''                                                >> ${SCLCFG}
	@${ECHO} 'usage="Usage: scl-config [--prefix] [--credits] [--version] [--cflags] [--shared-libs] [--static-libs]"'                         >> ${SCLCFG}
	@${ECHO} ''                                                >> ${SCLCFG}
	@${ECHO} 'if test $$# -eq 0; then'                         >> ${SCLCFG}
	@${ECHO} '	echo "$${usage}" 1>&2'                     >> ${SCLCFG}
	@${ECHO} '	exit 1'                                    >> ${SCLCFG}
	@${ECHO} 'fi'                                              >> ${SCLCFG}
	@${ECHO} ''                                                >> ${SCLCFG}
	@${ECHO} 'while test $$# -gt 0; do'                        >> ${SCLCFG}
	@${ECHO} '	case $$1 in'                               >> ${SCLCFG}
	@${ECHO} '		--prefix)'                         >> ${SCLCFG}
	@${ECHO} '			echo $${prefix}'           >> ${SCLCFG}
	@${ECHO} '			;;'                        >> ${SCLCFG}
	@${ECHO} '		--credits)'                        >> ${SCLCFG}
	@${ECHO} '			echo $${credits}'          >> ${SCLCFG}
	@${ECHO} '			;;'                        >> ${SCLCFG}
	@${ECHO} '		--version)'                        >> ${SCLCFG}
	@${ECHO} '			echo $${version}'          >> ${SCLCFG}
	@${ECHO} '			;;'                        >> ${SCLCFG}
	@${ECHO} '		--cflags)'                         >> ${SCLCFG}
	@${ECHO} '			echo $${cflags}'           >> ${SCLCFG}
	@${ECHO} '			;;'                        >> ${SCLCFG}
	@${ECHO} '		--shared-libs)'                    >> ${SCLCFG}
	@${ECHO} '			echo $${sharedlibs}'       >> ${SCLCFG}
	@${ECHO} '			;;'                        >> ${SCLCFG}
	@${ECHO} '		--static-libs)'                    >> ${SCLCFG}
	@${ECHO} '			echo $${staticlibs}'       >> ${SCLCFG}
	@${ECHO} '			;;'                        >> ${SCLCFG}
	@${ECHO} '		*)'                                >> ${SCLCFG}
	@${ECHO} '			echo "$$1: huh?" 1>&2'     >> ${SCLCFG}
	@${ECHO} '			echo "$${usage}" 1>&2'     >> ${SCLCFG}
	@${ECHO} '			exit 1'                    >> ${SCLCFG}
	@${ECHO} '			;;'                        >> ${SCLCFG}
	@${ECHO} '	esac'                                      >> ${SCLCFG}
	@${ECHO} '	shift'                                     >> ${SCLCFG}
	@${ECHO} 'done'                                            >> ${SCLCFG}
	@${ECHO} ''                                                >> ${SCLCFG}
	@${ECHO} 'exit 0'                                          >> ${SCLCFG}
	@${CHMOD} 755 ${SCLCFG}

# -----------------------------------------------------------------------------
# -- Installation Targets
# -----------------------------------------------------------------------------

install:
	for file in ${HEADERS}; do \
		${INSTALL} -D -m 644 $${file} ${INSTALL_INCLUDE}/$${file}; \
	done
	${INSTALL} -m 644 ${ARCHIVE} ${INSTALL_LIB}
	${INSTALL} -m 755 ${SONAMEV} ${INSTALL_LIB}
	${LINK} ${SONAMEV} ${INSTALL_LIB}/${LIBRARY}
	${LINK} ${SONAMEV} ${INSTALL_LIB}/${SONAME}
	${INSTALL} -m 755 ${SCLCFG} ${INSTALL_BIN}

uninstall:
	${RM} -r ${INSTALL_INCLUDE}
	${RM} ${INSTALL_LIB}/${ARCHIVE}
	${RM} ${INSTALL_LIB}/${LIBRARY}
	${RM} ${INSTALL_LIB}/${SONAME}
	${RM} ${INSTALL_LIB}/${SONAMEV}
	${RM} ${INSTALL_BIN}/${SCLCFG}

# -----------------------------------------------------------------------------
# -- Build Targets
# -----------------------------------------------------------------------------

debug:
	${MAKE} ${MAKEFLAGS} clean
	${MAKE} ${MAKEFLAGS} ${DEBUGFLAGS}

optimize:
	${MAKE} ${MAKEFLAGS} clean
	${MAKE} ${MAKEFLAGS} ${OPTIMFLAGS}

objects:	${CONFIG} ${OBJECTS}

sources:	${CONFIG} ${HEADERS} ${SOURCES}

libs:	${SCLCFG} ${CONFIG} ${HEADERS} ${SOURCES} ${OBJECTS}
	@${ECHO} "CAT	.depend"
	@${RM} .depend
	@${CAT} ${OBJECTS:.o=.d} > .depend
	@${ECHO} "AR	${ARCHIVE}"
	@${RM} ${ARCHIVE}
	@${AR} r ${ARCHIVE} ${OBJECTS} 2> /dev/null
	@${RANLIB} ${ARCHIVE}
	@${CHMOD} 644 ${ARCHIVE}
	@${ECHO} "LD	${SONAMEV}"
	@${RM} ${LIBRARY} ${SONAME} ${SONAMEV}
	@${CC} ${LD_SONAME_FLAGS} -o ${SONAMEV} ${OBJECTS} ${LIB_DIRS} ${LIBS}
	@${LINK} ${SONAMEV} ${LIBRARY}
	@${LINK} ${SONAMEV} ${SONAME}
	@${CHMOD} 755 ${SONAMEV}


# *************************************************************************** #
# The .depend file contains the header file dependencies.                     #
# *************************************************************************** #

-include .depend


# end of Makefile
