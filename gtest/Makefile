all: utest_assert utest_setup utest_param utest_death

utest_assert: utest_assert.cpp
	g++ -g -std=c++11 -o utest_assert utest_assert.cpp -lgtest -lgtest_main -lpthread

utest_setup: utest_setup.cpp
	g++ -g -std=c++11 -o utest_setup utest_setup.cpp -lgtest -lpthread

utest_param: utest_param.cpp
	g++ -g -std=c++11 -o utest_param utest_param.cpp -lgtest -lgtest_main -lpthread

utest_param: utest_death.cpp
	g++ -g -std=c++11 -o utest_death utest_death.cpp -lgtest -lgtest_main -lpthread

.PHONY: clean
clean:
	rm -f utest_assert utest_setup utest_param
