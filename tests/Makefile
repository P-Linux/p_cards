include ../Makefile.inc

test:
	$(CXX) -DNDEBUG -std=c++11 -O2 -Werror -pedantic -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -fPIC -c -o test.o test.cpp
	$(CXX) test.o -o $@ -lcards -lcurl -larchive
	rm test.o

clean:
	rm -f test

# End of file
