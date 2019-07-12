mian.o:main.cpp
	g++ -g main.cpp -o main -I./colib -L./colib -lcolib -lpthread -ldl
