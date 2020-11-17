all:
	g++ -g -shared -fPIC -o libfoo.so foo.cpp
	g++ -g -shared -fPIC -o libbar_dumb.so bar.cpp
	g++ -g -shared -fPIC -o libbar.so bar.cpp -L. -lfoo
	g++ -g -o test test.cpp -L. -lbar -Wl,-rpath-link=.
	g++ -g -o test_ab test.cpp -L. -lbar -lfoo
	g++ -g -o test_fail test.cpp -L. -lbar

.PHONY:clean
clean:
	rm -f libfoo.so libbar.so libbar_dumb.so test
