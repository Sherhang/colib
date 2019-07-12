edit:
	g++ -g demo_producer.cpp -o demo  -I./colib -L./colib -lcolib -lpthread -ldl
	g++ -g demoBase.cpp -o demoBase  -I./colib -L./colib -lcolib -lpthread -ldl
	g++ -g demoDoublePara.cpp -o demoDoublePara  -I./colib -L./colib -lcolib -lpthread -ldl

