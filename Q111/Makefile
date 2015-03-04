SOURCE = code.c
OUTPUT = code.out

normal:
	gcc $(SOURCE) -o $(OUTPUT) -g

t1:
	make normal
	./code.out < 1.txt > t1.txt
	vim -d t1.txt a1.txt

t2:
	make normal
	./code.out < 2.txt > t2.txt
	vim -d t2.txt a2.txt

t3:
	make normal
	./code.out < 3.txt > t3.txt
	vim -d t3.txt a3.txt

edit:
	vim $(SOURCE)

remove:
	rm $(OUTPUT)
