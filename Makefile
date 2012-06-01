all:
	g++ CS154Project3/Decoder.cpp CS154Project3/Decoded.cpp CS154Project3/Execute.cpp CS154Project3/Executed.cpp CS154Project3/Fetch.cpp CS154Project3/Fetched.cpp CS154Project3/Memoried.cpp CS154Project3/WriteBack.cpp CS154Project3/driver.cpp CS154Project3/Memory.cpp -o cs154proj3 -Wall
turnin: clean
	mkdir turnin
	mkdir turnin/src
	cp CS154Project3/Decoder.cpp  turnin/src
	cp CS154Project3/Decoded.cpp  turnin/src
	cp CS154Project3/Execute.cpp  turnin/src
	cp CS154Project3/Executed.cpp turnin/src
	cp CS154Project3/Fetch.cpp turnin/src
	cp CS154Project3/Fetched.cpp turnin/src
	cp CS154Project3/Memoried.cpp turnin/src
	cp CS154Project3/WriteBack.cpp turnin/src
	cp CS154Project3/driver.cpp turnin/src
	cp CS154Project3/Memory.cpp turnin/src
	cp CS154Project3/Decoder.h  turnin/src
	cp CS154Project3/Decoded.h  turnin/src
	cp CS154Project3/Execute.h  turnin/src
	cp CS154Project3/Executed.h turnin/src
	cp CS154Project3/Fetch.h turnin/src
	cp CS154Project3/Fetched.h turnin/src
	cp CS154Project3/Memoried.h turnin/src
	cp CS154Project3/WriteBack.h turnin/src
	cp CS154Project3/driver.h turnin/src
	cp CS154Project3/Memory.h turnin/src

	cp turnin_make turnin/Makefile
	cp README.txt turnin/
	cp Writeup.txt turnin/

clean:
	if test -d turnin; then rm -r turnin; fi
	rm -f cs154proj3
