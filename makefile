main: main.o input_output.o
	gcc -o $@ $^
%.o: %.c
	gcc -c $<
clean: 
	rm *.o
