a.exe: bst.o treenode.o phone.o
	g++ -o a.exe bst.o treenode.o phone.o

bst.o: bst.cpp treenode.cpp
	g++ -c bst.cpp

treenode.o: bst.cpp treenode.cpp
	g++ -c treenode.cpp

test.o: bst.cpp treenode.cpp test.cpp
	g++ -c test.cpp

phone.o: phone.cpp bst.cpp treenode.cpp
	g++ -c phone.cpp
