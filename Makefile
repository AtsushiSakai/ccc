CFLAGS=-std=c11 -g -static

ccc: ccc.o
	$(CC) -o $@ $? $(LDFLAGS)

test: ccc
	./test.sh

clean:
	rm -f ccc *.o *~ tmp*

.PHONY: test clean
