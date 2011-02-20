CFLAGS=-Wall -I . -g
LDFLAGS=-pthread

main: main.o event_thread.o io_thread.o listener_thread.o \
      event.o events/new_connection.o \
      message.o messages/close.o messages/send.o \
      queue.o

main.c: event_thread.h io_thread.h listener_thread.h

event_thread.c: event_thread.h event.h
io_thread.c: io_thread.h message.h
listener_thread.c: listener_thread.h error_status.h event.h events/new_connection.h

event.c: event.h queue.h
events/new_connection.c: events/new_connection.h error_status.h \
                         message.h messages/close.h messages/send.h
events/new_connection.h: event.h

message.c: message.h queue.h
messages/close.c: messages/close.h
messages/close.h: message.h
messages/send.c: messages/send.h
messages/send.h: message.h

queue.c: queue.h

clean:
	rm *.o events/*.o messages/*.o main
