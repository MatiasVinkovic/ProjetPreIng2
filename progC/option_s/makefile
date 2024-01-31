prog : option_s.o s_fifo.o s_first_avl.o
		gcc -o prog option_s.o s_fifo.o s_first_avl.o -lm

option_s.o : option_s.c
		gcc -o option_s.o -c option_s.c

s_fifo.o : s_fifo.c
		gcc -o s_fifo.o -c s_fifo.c

clean :
	rm -f option_s.o s_first_avl.o s_fifo.o  prog