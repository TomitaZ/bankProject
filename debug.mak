project2_debug: user_interface.o llist.o
	g++ -o project2_debug user_interface.o llist.o
llist.o: llist.cpp
	g++ -ansi -pedantic-errors -Wall -c -DDEBUG llist.cpp
user_interface.o: user_interface.cpp
	g++ -ansi -pedantic-errors -Wall -c -DDEBUG user_interface.cpp

