G=g++
SOURCEFILE= Entities.cpp  main.cpp Service.cpp cmd.cpp
GITADDR=../../
LIB= jsoncpp

run:app
	./app

app:$(SOURCEFILE) clean
	$G $(SOURCEFILE) -l$(LIB) -o app

debug:$(SOURCEFILE) clean
	$G $(SOURCEFILE) -g -Wall -o app
	gdb ./app

commit:
	git add $(GITADDR)project-c
	git commit $(GITADDR)project-c


test:test.cpp
	rm -f test
	g++  test.cpp Entities.cpp Service.cpp cmd.cpp -o test -l$(LIB) -I./
	./test

clean:
	rm -f app test