cc = g++
src = $(shell find ./ -name "*.cpp")
head = $(shell find ./ -name "*.h")
obj = $(src: %.c=%.o)
target = $(patsubst %.cpp, %, $(src)) 

INCS = -I./colib
LIBS = -L./colib -lcolib -lpthread -ldl

CFLAGS += -g 

all:$(target)
	
$(target):%:%.cpp
	$(cc) $(INCS) $(CFLAGS) $^ -o $@ $(LIBS)

%.o: %.cpp $(head)
	$(cc) $(INCS) $(CFLAGS) -c $^ -o $@ $(LIBS)

clean:
	rm -rf $(obj) $(target)	

