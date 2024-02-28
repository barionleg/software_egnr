G=g++
SOURCEFILE= Entities.cpp  main.cpp Service.cpp cmd.cpp
TEST_DEPENDENCY=test.cpp Entities.cpp Service.cpp cmd.cpp
GITADDR=../../
LIB= jsoncpp

run:app
	./app

##生成可执行文件
app:$(SOURCEFILE) clean
	$G $(SOURCEFILE) -l$(LIB) -o app

##gdb调试
debug:$(SOURCEFILE) clean
	$G $(SOURCEFILE) -g -Wall -o app
	gdb ./app

##git提交
commit:
	git add $(GITADDR)project-c
	git commit $(GITADDR)project-c

#测试
test:test.cpp
	rm -f test
	g++ $(TEST_DEPENDENCY) -g -o test -l$(LIB) -I./
	./test

clean:
	rm -f app test