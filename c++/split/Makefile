CXX = $(CPPTEST) g++
RM  = rm -f

libsplit.so: split.cpp
	$(CXX) -g -c split.cpp -std=c++11 -fPIC
	$(CXX) -shared -o libsplit.so split.o

.PHONY: clean
clean:
	$(RM) split.o libsplit.so
