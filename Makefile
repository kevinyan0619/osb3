all:	
	g++ -c Aging.cpp -o Aging.o
	g++ -c Clock.cpp -o Clock.o
	g++ -c FIFO.cpp -o FIFO.o
	g++ -c NRU.cpp -o NRU.o
	g++ -c Random.cpp -o Random.o
	g++ -c Second_Chance.cpp -o Second_Chance.o
	g++ -c options.cpp -o options.o
	g++ -c print_util.cpp -o print_util.o
	g++ -c random_generator.cpp -o random_generator.o
	g++ -c fileReader.cpp -o fileReader.o
	g++ -c frameTable.cpp -o frameTable.o
	g++ -c lab3.cpp -o lab3.o
	g++ -o mmu lab3.o Aging.o Clock.o FIFO.o NRU.o Random.o Second_Chance.o options.o print_util.o random_generator.o fileReader.o frameTable.o


clean:
	rm -rf *.o
	rm -rf mmu
