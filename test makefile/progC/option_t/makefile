prog : option_t.o t_abr.o t_avl_in.o t_fifo.o t_first_avl.o t_second_avl.o
		gcc -o prog option_t.o t_abr.o t_avl_in.o t_fifo.o t_first_avl.o t_second_avl.o -lm

option_t.o : option_t.c
		gcc -o option_t.o -c option_t.c

t_abr.o : t_abr.c
		gcc -o t_abr.o -c t_abr.c

t_avl_in.o : t_avl_in.c
		gcc -o t_avl_in.o -c t_avl_in.c

t_fifo.o : t_fifo.c
		gcc -o t_fifo.o -c t_fifo.c

t_first_avl.o : t_first_avl.c
		gcc -o t_first_avl.o -c t_first_avl.c

t_second_avl.o : t_second_avl.c
		gcc -o t_second_avl.o -c t_second_avl.c
