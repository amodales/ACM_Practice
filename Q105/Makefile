SOURCE = code.c
OUTPUT = code.out

normal:
	gcc $(SOURCE) -o $(OUTPUT) -g

edit:
	vim $(SOURCE)

remove:
	rm $(OUTPUT)

t1:
	./$(OUTPUT) < 1.txt > t1.txt
	vim -d t1.txt a1.txt

t2:
	./$(OUTPUT) < 2.txt > t2.txt
	vim -d t2.txt a2.txt

t3:
	./$(OUTPUT) < 3.txt > t3.txt
	vim -d t3.txt a3.txt

t4:
	./$(OUTPUT) < 4.txt > t4.txt
	vim -d t4.txt a4.txt
