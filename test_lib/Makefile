.PHONY:  clean


TEST_CFLAGS:=-I. 
TEST_LIBS:=libtest.so.1 


libtest.so:test.o
	gcc -shared $^ -o $@ 
test.o:test.c 
	gcc $(TEST_CFLAGS) -c $< -o $@


clean:
	rm *.o  *so.1 
