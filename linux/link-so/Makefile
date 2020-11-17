all:
	g++ -g -o test test.cpp -L. -lrandom
	g++ -g -Wl,-rpath="\$$ORIGIN"/random_1,--disable-new-dtags -o test_rpath_random1 test.cpp -L. -lrandom
	g++ -g -Wl,-rpath="\$$ORIGIN"/random_2,--disable-new-dtags -o test_rpath_random2 test.cpp -L. -lrandom
	g++ -g -Wl,-rpath="\$$ORIGIN"/random_1,--enable-new-dtags -o test_runpath_random1 test.cpp -L. -lrandom
	g++ -g -Wl,-rpath="\$$ORIGIN"/random_2,--enable-new-dtags -o test_runpath_random2 test.cpp -L. -lrandom

.PHONY: clean
clean:
	rm -f test test_rpath_random1 test_rpath_random2 test_runpath_random1 test_runpath_random2
