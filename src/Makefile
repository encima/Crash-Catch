CC=g++
CFLAGS+=`pkg-config --cflags opencv`
LDFLAGS+=`pkg-config --libs opencv`

PROG=crash-catch
OBJS=$(PROG).o

.PHONY: all clean
$(PROG): $(OBJS)
	$(CC) -o ../build/$(PROG) ../build/$(OBJS) $(LDFLAGS)
%.o: %.cpp
	$(CC) -c $(CFLAGS) $<
	mv $(OBJS) ../build/$(OBJS)
all:
	$(PROG)
clean:
	rm -f $(OBJS) $(PROG)
