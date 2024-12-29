TARGET := ../out/photograph

CC:= arm-linux-gcc

CSRCS:=$(wildcard *.c)

OBJS:= $(patsubst %.c, %.o, $(CSRCS))

#INC保存的是工程中所有头文件的搜索路径
INC := -I ./
INC += -I ../inc/

#LIBS保存的是工程所有需要用到的库以及库的搜索路径
LIBS += -L . -l pthread 
LIBS += -L ../lib_jpeg  -l jpeg -static

$(TARGET):$(OBJS)
		$(CC) $^ $(LIBS) -o $@
%.o:%.c
		$(CC) -c $< $(INC) -o $@

clean:
		rm -rf $(OBJS)
		rm -rf $(TARGET)