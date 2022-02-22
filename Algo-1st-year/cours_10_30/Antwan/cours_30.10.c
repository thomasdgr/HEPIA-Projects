#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

typedef struct pile
{
    int *data;
    int capacity;
    int sommet;
} pile;

bool pile_est_valide(pile stack)
{
    return (stack.capacity >= 0 && stack.sommet >= -1);
}

bool pile_est_vide(pile stack)
{
    
    return (-1 == stack.sommet);
}

bool pile_est_pleine(pile stack)
{
    assert(pile_est_valide(stack));
    return (stack.capacity - 1 == stack.sommet);
}

pile pile_create(int max)
{
    pile stack;
    stack.capacity = max;
    stack.sommet = -1;
    stack.data = malloc(max * sizeof(int));
    return stack;
}

void pile_destroy(pile *stack)
{
    stack->capacity = -1;
    stack->sommet = -40;
    free(stack->data);
}

void pile_resize(pile *stack, int size)
{
    assert(pile_est_valide(*stack));
    stack->capacity = size;
    stack->data = realloc(stack->data, size * sizeof(int));
}

int pile_sommet(pile stack)
{
    if (!pile_est_vide(stack)){
        return stack.data[stack.sommet];
    }
}

void pile_empiler(pile *stack, int val)
{
    assert(pile_est_valide(*stack));
    if (pile_est_pleine(*stack))
    {
        pile_resize(stack, stack->capacity + 1);
    }
    stack->sommet++;
    stack->data[stack->sommet] = val;
}

int pile_depiler(pile *stack)
{
    assert(pile_est_valide(*stack));
    int val = pile_sommet(*stack);
    stack->sommet--;
    return val;
}

int main()
{

    int liste[] = {3, 8, 7, 1, 3};
    int size = sizeof(liste) / sizeof(liste[0]);
    pile a = pile_create(size);
    pile b = pile_create(size);

    //Tri à deux piles

    pile_empiler(&a, liste[0]);
    for (int i = 0; i < size; i++)
    {

        if (pile_est_vide(a))
        {
            pile_empiler(&a, liste[i]);
            printf("test");
        }
        if (!pile_est_vide(a))
        {
            if (liste[i] < pile_sommet(a))
                pile_empiler(&a, liste[i]);
            else if (liste[i] > pile_sommet(a))
            {
                while (liste[i] > pile_sommet(a))
                {
                    pile_empiler(&b, pile_depiler(&a));
                }
                pile_empiler(&a, liste[i]);
            }
        }
        if (!pile_est_vide(b))
        {
            if (liste[i] < pile_sommet(b))
            {
                while (liste[i] < pile_sommet(b))
                {
                    pile_empiler(&a, pile_depiler(&b));
                }
                pile_empiler(&b, liste[i]);
            }
        }
    }

    for (int i = 0; i < b.sommet; i++)
    {
        pile_empiler(&a, pile_depiler(&b));
    }

    for (int i = 0; i < size; i++)
    {
        liste[i] = pile_depiler(&a);
        printf("%d ", liste[i]);
    }
    printf("\n");
}