CC = gcc
CFLAGS = -Wall 

TARGET = nyush
OBJS = nyush.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

nyush.o: nyush.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)