all:
	g++ -std=c++11 -Wall -Werror -Wextra main.cpp -D MERGESORT
	./a.out ../test/100.txt
	./a.out ../test/500.txt
	./a.out ../test/1000.txt
	./a.out ../test/5000.txt
	./a.out ../test/10000.txt
	./a.out ../test/50000.txt
	./a.out ../test/100000.txt
	g++ -std=c++11 -Wall -Werror -Wextra main.cpp -D QUICKSORT
	./a.out ../test/100.txt
	./a.out ../test/500.txt
	./a.out ../test/1000.txt
	./a.out ../test/5000.txt
	./a.out ../test/10000.txt
	./a.out ../test/50000.txt
	./a.out ../test/100000.txt
	g++ -std=c++11 -Wall -Werror -Wextra main.cpp -D INSERTSORT
	./a.out ../test/100.txt
	./a.out ../test/500.txt
	./a.out ../test/1000.txt
	./a.out ../test/5000.txt
	./a.out ../test/10000.txt
	./a.out ../test/50000.txt
	./a.out ../test/100000.txt
mergesort:
	g++ -std=c++11 -Wall -Werror -Wextra main.cpp -D MERGESORT
quicksort:
	g++ -std=c++11 -Wall -Werror -Wextra main.cpp -D QUICKSORT
insertsort:
	g++ -std=c++11 -Wall -Werror -Wextra main.cpp -D INSERTSORT
clean:
	rm -f insertSort.txt mergeSort.txt quickSort.txt sort.txt a.out