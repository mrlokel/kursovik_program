#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/time.h>
#include <math.h>
#include "func.h"

#define N 1000000

// генерирование рандомных чисел
int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

// таймер, для подсчёта времени сортировки
double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main()
{
    // открытие динамической библиотеки, для использования в программе
    void *library_handler = dlopen("./libfsdyn.so", RTLD_LAZY);
    if (!library_handler)
    {
        fprintf(stderr, "dlopen() error: %s\n", dlerror());
        exit(1);
    }
    void (*adress_func1)(int size, int mass[]) = dlsym(library_handler, "ShellSort");
    void (*adress_func2)(int *a, int p, int r) = dlsym(library_handler, "MergeSort");

    printf("Выберите один из вариантов и введите его цифру:\n1. Проверка алгоритмов сортировки на отсортированные/неотсортированные значения\n2. Ввод массива самостоятельно\n");
    printf("Ввод: ");
    int vibor;
    scanf("%d", &vibor);
    if (vibor == 1)
    {
        printf("Merge Sort неотсортированный массив (рандомные значения)\n");
        for (int size = pow(2, 8); size <= pow(2, 15); size += 3000)
        {
            int *a = malloc(size * sizeof(int));
            for (int i = 0; i < size; i++)
            {
                a[i] = getrand(0, N);
            }
            double start = wtime();
            adress_func2(a, 0, size - 1);
            double result_time = wtime() - start;
            printf("Time sort: %lf\n", result_time);
            free(a);
        }

        printf("Merge Sort отсортированный массив (значения по возрастанию)\n");
        for (int size = pow(2, 8); size <= pow(2, 15); size += 3000)
        {
            int *a = malloc(size * sizeof(int));
            for (int i = 0; i < size; i++)
            {
                a[i] = i + 1;
            }
            double start = wtime();
            adress_func2(a, 0, size - 1);
            double result_time = wtime() - start;
            printf("Time sort: %lf\n", result_time);
            free(a);
        }

        printf("Merge Sort отсортированный массив (значения по убыванию)\n");
        for (int size = pow(2, 8); size <= pow(2, 15); size += 3000)
        {
            int *a = malloc(size * sizeof(int));
            for (int i = 0; i < size; i++)
            {
                a[i] = size - i;
            }
            double start2 = wtime();
            adress_func2(a, 0, size - 1);
            double result_time = wtime() - start2;
            printf("Time sort: %lf\n", result_time);
            free(a);
        }

        printf("Shell Sort неотсортированный массив (рандомные значения)\n");
        for (int size = pow(2, 8); size <= pow(2, 15); size += 3000)
        {
            int *a = malloc(size * sizeof(int));
            for (int i = 0; i < size; i++)
            {
                a[i] = getrand(0, N);
            }
            double start = wtime();
            adress_func1(size, a);
            double result_time = wtime() - start;
            printf("Time sort: %lf\n", result_time);
            free(a);
        }

        printf("Shell Sort отсортированный массив (значения по возрастанию)\n");
        for (int size = pow(2, 8); size <= pow(2, 15); size += 3000)
        {
            int *a = malloc(size * sizeof(int));
            for (int i = 0; i < size; i++)
            {
                a[i] = i + 1;
            }
            double start = wtime();
            adress_func1(size, a);
            double result_time = wtime() - start;
            printf("Time sort: %lf\n", result_time);
            free(a);
        }

        printf("Shell Sort отсортированный массив (значения по убыванию)\n");
        for (int size = pow(2, 8); size <= pow(2, 15); size += 3000)
        {
            int *a = malloc(size * sizeof(int));
            for (int i = 0; i < size; i++)
            {
                a[i] = size - i;
            }
            double start2 = wtime();
            adress_func1(size, a);
            double result_time = wtime() - start2;
            printf("Time sort: %lf\n", result_time);
            free(a);
        }
    }

    else if (vibor == 2)
    {
        printf("Введите кол-во элементов в массиве: ");
        int size_arr;
        scanf("%d", &size_arr);
        if (size_arr == 1)
        {
            printf("Не корректный ввод количества элементов массива!\n");
            return 1;
        }
        int *arr = malloc(size_arr * sizeof(int));
        int *arr1 = malloc(size_arr * sizeof(int));

        if (arr == NULL || arr1 == NULL)
        {
            printf("Не удалось выделить память под массив.\n");
            return 1;
        }

        printf("Введите элементы массива через пробел: ");
        for (int i = 0; i < size_arr; i++)
        {
            if (scanf("%d", &arr[i]) != 1)
            {
                printf("Некорретный ввод элемента массива!\n");
                free(arr);
                free(arr1);
                return 1;
            }
            arr1[i] = arr[i];
        }

        printf("Сортировка слиянием\n");
        adress_func2(arr, 0, size_arr - 1);
        for (int i = 0; i < size_arr; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");

        printf("Сортировка Шелла\n");
        adress_func1(size_arr, arr1);
        for (int i = 0; i < size_arr; i++)
        {
            printf("%d ", arr1[i]);
        }
        printf("\n");
    }

    return 0;
}
