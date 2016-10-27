
lecture_bmp: lecture_bmp.o
	gcc -o $@ $^
%.o: %.c
	gcc -c $<
clean: 
	rm *.o
