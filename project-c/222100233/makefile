G=g++
SOURCEFILE= Entities.cpp  main.cpp

LIB= jsoncpp

run:app
	./app

app:$(SOURCEFILE) clean
	$G $(SOURCEFILE) -l$(LIB) -o app

debug:$(SOURCEFILE) clean
	$G $(SOURCEFILE) -g -Wall -o app
	gdb ./app

clean:
	rm -f app