run: main.cpp CommandCD.o ModeHandler.o
	g++ main.cpp -o beta

DisplayHandler.o: DisplayHandler.cpp DisplayHandler.h
	g++ -c DisplayHandler.cpp	

CommandCD.o: CommandCD.cpp CommandCD.h HistoryManager.o DisplayHandler.o
	g++ -c CommandCD.cpp

HistoryManager.o: HistoryManager.cpp HistoryManager.h DisplayHandler.o
	g++ -c HistoryManager.cpp	

ModeHandler.o: ModeHandler.cpp ModeHandler.h CommandCD.o
	g++ -c ModeHandler.cpp

clean:
	rm *.o
	rm beta