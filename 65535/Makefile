PROG_SERVER=	_server

PROG_CLIENT=	_client

CPPFLAGS_STD?=	-D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700
CPPFLAGS+=	${CPPFLAGS_STD}

CFLAGS_OPT?=	-O2 -g -pipe
CFLAGS_STD?=	-std=c11
CFLAGS_WARN?=	-Wall -W -Wextra -w

CFLAGS?=	${CFLAGS_OPT}
CFLAGS+=	${CFLAGS_STD} ${CFLAGS_WARN}

all:		${PROG_SERVER} ${PROG_CLIENT}

	
		${CC} ${LDFLAGS} -o ${PROG_SERVER} server/*.c comm/*.c -I server -I comm

	
		${CC} ${LDFLAGS} -o ${PROG_CLIENT} client/*.c comm/*.c -I client -I comm

clean:
		rm -f ${PROG_SERVER} ${OBJS_SERVER} ${PROG_CLIENT} ${OBJS_CLIENT}
