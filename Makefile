# CFLAGS

all: exec-main

exec-main: main.cpp
	g++ main.cpp -o exec-main

clean:
	echo -e "\033[1;35mRemoving specified files\033[0m"
	rm exec-main
