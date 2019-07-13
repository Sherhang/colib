CXX = g++

src = $(wildcard *.cpp)
head = $(wildcard *.h)
obj = $(src:%.cpp=%.o) #get all .h with the same name of .cpp 
target = $(patsubst %.cpp, %, $(src)) #similar with the above，use this mostly 

INCS = -I./colib
LIBS = -L./colib -lcolib -lpthread -ldl

CFLAGS += -g 

all:$(target)

$(target):%:%.o   	#用模式规则对每个独立的目标进行编译
	$(CXX) $(INCS) $(CFLAGS) $^ -o $@ $(LIBS)
%.o:%.cpp 
	$(CXX) $(INCS) $(CFLAGS) -c $^ -o $@ $(LIBS)

.PHONY:all clean
clean:
<<<<<<< HEAD
	@echo "clean all .o and exe: "
	rm -rf  $(obj) $(target)	
=======
	rm -rf $(obj) $(target)	
>>>>>>> 02aff67ccb3cb26511f05b9ce1910d22b8d93516

