prog: Pokemon.o BattleByCategory.o MaxHeap.o LinkedList.o MainSecond.o
	gcc Pokemon.o BattleByCategory.o MaxHeap.o LinkedList.o MainSecond.o -o PokemonsBattles

Pokemon.o: Pokemon.c Pokemon.h Defs.h
	gcc -c Pokemon.c

BattleByCategory.o: BattleByCategory.c BattleByCategory.h Defs.h LinkedList.h MaxHeap.h
	gcc -c BattleByCategory.c

MaxHeap.o: MaxHeap.c MaxHeap.h Defs.h LinkedList.h
	gcc -c MaxHeap.c

LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c

MainSecond.o: MainSecond.c Pokemon.h Defs.h LinkedList.h MaxHeap.h BattleByCategory.h
	gcc -c MainSecond.c

clean:
	rm -f *.o