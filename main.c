// main.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct choice_1
{
    int a;
    int b;
    int c;
};

struct choice_2
{
    double a;
    double b;
    double c;
    double d;
};

double random_double()
{
    return (double)rand() / (double)RAND_MAX;
}

int random_int()
{
    return (int)rand();
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
    }
    else if (choice == 2)
    {
        struct choice_2 *ptr = (struct choice_2*)data;
        printf("Choice 2\n");
        printf("a: %f\n", ptr->a);
        printf("b: %f\n", ptr->b);
        printf("c: %f\n", ptr->c);
        printf("d: %f\n", ptr->d);
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
        return data;
    }
    else if (choice == 2)
    {
        struct choice_2 *data = malloc(sizeof(struct choice_2));
        data->a = random_double();
        data->b = random_double();
        data->c = random_double();
        data->d = random_double();
        return data;
    }
    return NULL;
}

int main()
{
    srand(time(NULL)); // Seed the random number generator with current time

    int choice = random_int() % 2 + 1;
    void *data = init_choice(choice);
    print_choice(data, choice);
    free(data);
}