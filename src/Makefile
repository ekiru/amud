CFLAGS=-Wall -I . -I dep/bstrlib -g
LDFLAGS=-pthread

main: main.o event_thread.o io_thread.o listener_thread.o \
      event.o events/new_connection.o \
      io_util.o \
      message.o messages/close.o messages/send.o \
      player.o \
      queue.o \
      dep/bstrlib/bstrlib.o

main.c: event_thread.h io_thread.h listener_thread.h

event_thread.c: event_thread.h event.h
io_thread.c: io_thread.h message.h
listener_thread.c: listener_thread.h error_status.h event.h events/new_connection.h

event.c: event.h queue.h
events/new_connection.c: events/new_connection.h error_status.h \
                         io_util.h \
                         message.h messages/send.h \
                         player.h
events/new_connection.h: event.h

io_util.c: io_util.h error_status.h message.h messages/send.h player.h

message.c: message.h queue.h
messages/close.c: messages/close.h
messages/close.h: message.h
messages/send.c: messages/send.h
messages/send.h: message.h player.h

player.c: player.h

queue.c: queue.h

dep/bstrlib/bstrlib.o: dep/bstrlib/bstrlib.c dep/bstrlib/bstrlib.h

clean:
	rm *.o events/*.o messages/*.o main
