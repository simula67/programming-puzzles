min_rope:min_rope.c permute.o
	cc min_rope.c permute.o -o min_rope
permute.o:permute.h permute.c
	cc -c permute.c
clean:
	rm *.o
clean-all:clean
	rm min_rope
