all:
	g++ -g -fPIC -shared -Wl,-soname=librandom.so.1 -o librandom.so.1.1.0 random.cpp
	ln -s librandom.so.1.1.0 librandom.so.1

.PHONY:clean
clean:
	rm -f librandom.so librandom.so.1 librandom.so.1.1.0
