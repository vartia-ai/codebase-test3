// main.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef void (*FuncPtr)(int);

void func1(int a)
{
    printf("func1: %d\n", a);
}

void func2(int a)
{
    printf("func1: %d\n", a);
}

struct choice_1
{
    int a;
    int b;
    int c;
    FuncPtr func_ptr;
};

struct choice_2
{
    double a;
    double b;
    double c;
    double d;
    FuncPtr func_ptr;
};

double random_double()
{
    return (double)rand() / (double)RAND_MAX;
}

int random_int()
{
    return (int)rand();
}

void choice1_cast(void *data)
{
    printf("Choice 1\n");

    struct choice_1 *ptr = (struct choice_1*)data;
}

void print_choice(void *data, int choice)
{
    if (choice == 1)
    {
        struct choice_1 *ptr = (struct choice_1*)data;
        printf("Choice 1\n");
        printf("a: %d\n", ptr->a);
        printf("b: %d\n", ptr->b);
        printf("c: %d\n", ptr->c);
        ptr->func_ptr(ptr->a);
    }
    else if (choice == 2)
    {
        struct choice_2 *ptr = (struct choice_2*)data;
        printf("Choice 2\n");
        printf("a: %f\n", ptr->a);
        printf("b: %f\n", ptr->b);
        printf("c: %f\n", ptr->c);
        printf("d: %f\n", ptr->d);
        ptr->func_ptr(ptr->a);
    }
    else if (choice == 3)
    {
        printf("Choice 3\n");
        printf("String: %s\n", (char*)data);
    }
    else
    {
        printf("Invalid choice\n");
    }
}

void* init_choice(int choice)
{
    if (choice == 1)
    {
        struct choice_1 *data = malloc(sizeof(struct choice_1));
        data->a = random_int();
        data->b = random_int();
        data->c = random_int();
        data->func_ptr = func1;
        return data;
    }
    else if (choice == 2)
    {
        struct choice_2 *data = malloc(sizeof(struct choice_2));
        data->a = random_double();
        data->b = random_double();
        data->c = random_double();
        data->d = random_double();
        data->func_ptr = func2;
        return data;
    }
    else if (choice == 3)
    {
        char *string = "Hello Buffer Overflow!";
        char *data = malloc(strlen(string) + 1);
        strcpy(data, string);
        return data;
    }
    else
    {
        printf("Invalid choice\n");
    }
    return NULL;
}

int main()
{
    srand(time(NULL)); // Seed the random number generator with current time

    struct choice_1 *c1 = malloc(sizeof(struct choice_1));
    c1->a = 11;
    c1->b = 22;
    c1->c = 33;
    c1->func_ptr = func1;

    void *data = c1;
    choice1_cast(data);

    int choice = random_int() % 3 + 1;
    data = init_choice(choice);
    print_choice(data, choice);
    free(data);
}
