CFLAGS=-Wall
LDFLAGS=-pthread

main: main.o event_thread.o io_thread.o listener_thread.o

main.c: event_thread.h io_thread.h listener_thread.h

event_thread.c: event_thread.h
io_thread.c: io_thread.h
listener_thread.c: listener_thread.h error_status.h
