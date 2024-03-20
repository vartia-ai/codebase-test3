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

void choice1_cast(void *data)
{
    printf("Choice 1\n");

    struct choice_1 *ptr = (struct choice_1*)data;
}

void choice2_cast(void *data)
{
    struct choice_2 *ptr = (struct choice_2*)data;
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
        struct choice_1 *c1 = malloc(sizeof(struct choice_1));
        c1->a = 11;
        c1->b = 22;
        c1->c = 33;
        c1->func_ptr = func1;
        return c1;
    }
    else if (choice == 2)
    {
        struct choice_2 *c2 = malloc(sizeof(struct choice_2));
        c2->a = 0.44;
        c2->b = 0.55;
        c2->c = 0.66;
        c2->d = 0.77;
        c2->func_ptr = func2;
        return c2;
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
    struct choice_1 *c1 = init_choice(1);
    choice1_cast(c1);
    print_choice(c1, 1);
    free(c1);

    struct choice_2 *c2 = init_choice(2);
    choice1_cast(c2);
    print_choice(c2, 2);
    free(c2);

    char *str = init_choice(3);
    print_choice(str, 3);
    free(str);
}
