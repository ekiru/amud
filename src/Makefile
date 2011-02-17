CFLAGS=-Wall -I . -g
LDFLAGS=-pthread

main: main.o event_thread.o io_thread.o listener_thread.o \
      event.o events/new_connection.o

main.c: event_thread.h io_thread.h listener_thread.h

event_thread.c: event_thread.h
io_thread.c: io_thread.h
listener_thread.c: listener_thread.h error_status.h event.h events/new_connection.h

event.c: event.h
events/new_connection.c: events/new_connection.h
events/new_connection.h: event.h

clean:
	rm *.o events/*.o main
