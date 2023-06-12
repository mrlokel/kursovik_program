all: app

app: merge_sort.c shell_sort.c
	gcc -fPIC -c merge_sort.c
	gcc -fPIC -c shell_sort.c
	gcc -shared -o libfsdyn.so merge_sort.o shell_sort.o
	gcc -c main.c
	gcc main.o -L. -ldl -lfsdyn -o resultdyn

run:
	./resultdyn

clean:
	rm main.o
	rm merge_sort.o
	rm shell_sort.o
	rm libfsdyn.so
	rm resultdyn
