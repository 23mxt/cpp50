#通用Makefile
out:=server.out#可执行文件名称需要根据需要更改
SRCS:=$(wildcard *.cpp)#拿到当前目录下所有的.c文件
OBJS:=$(patsubst %.cpp,%.o,$(SRCS))#把.c文件替换为.o文件
#预定义变量
CC:=g++
#CFLAGS:=-g
$(out):$(OBJS)
	$(CC) $^ -o $@ -llog4cpp -lpthread /usr/local/lib/libhiredis.a   /usr/local/lib/libredis++.so  

%.o:%.cpp
	$(CC) -c $^ -o $@ -g

#.PHONY:clean rebuild
rebuild:clean $(out)
clean:
	rm -rf $(OBJS) $(out)



