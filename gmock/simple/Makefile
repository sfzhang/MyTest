all: libnet.so test_netclient

libnet.so: inetstream.h netclient.h netclient.cpp
	g++ -g -std=c++11 -c netclient.cpp --coverage -fPIC
	g++ -shared -o libnet.so netclient.o --coverage

test_netclient: libnet.so test_netclient.cpp
	g++ -g -std=c++11 -c test_netclient.cpp --coverage
	g++ -g -o $@ test_netclient.o libnet.so --coverage -lgmock -lgtest -lgcov -lpthread

.PHONY: clean
clean:
	rm -f netclient.o test_netclient.o libnet.so test_netclient
