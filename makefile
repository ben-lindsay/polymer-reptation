CC = g++
CFLAGS = -g -Wall
SRCS = main.cpp read_input.cpp init.cpp move_utils.cpp rand_utils.cpp \
       io_utils.cpp calc_utils.cpp

rept.exe: ${SRCS}
	${CC} ${CFLAGS} ${SRCS} -o $@

clean:
	rm -f rept.exe
