SOURCE = code.cpp
OUTPUT = code.out
CSOURCE = check.cpp
COUTPUT = check.out
TEST = t.txt
R1 = r1.txt
R2 = r2.txt

normal:
	g++ $(SOURCE) -o $(OUTPUT)
	./$(OUTPUT) < $(TEST) > $(R1)
	g++ $(CSOURCE) -o $(COUTPUT)
	./$(COUTPUT) < $(TEST) > $(R2)
	vim -d $(R1) $(R2)

clear:
	rm $(OUTPUT) $(COUTPUT)

edit:
	vim $(SOURCE)

cedit:
	vim $(CSOURCE)

try:
	g++ $(SOURCE) -o $(OUTPUT)
	./$(OUTPUT) < $(TEST)

ctry:
	g++ $(CSOURCE) -o $(COUTPUT)
	./$(COUTPUT) < $(TEST)
