#include <stdio.h>
#include <string.h>
#include "structures.h"

void getOnePerson(person_t *t)
{
    printf("Enter full name: ");
    scanf("%s", t->name);
    printf("Enter ssn: ");
    scanf("%s", t->ssn);
    printf("Enter year of birth: ");
    scanf("%d", &t->yearOfBirth);
}

void printOnePerson(person_t t)
{
    printf("%s:%s:%d\n",t.name, t.ssn, t.yearOfBirth);
}

void getPeople(person_t t[], int numPeople)
{
    for (int i = 0; i < numPeople; i++)
    {
        getOnePerson(&t[i]);
    }
}

void printPeople(person_t t[], int numPeople)
{
    for (int i = 0; i < numPeople; i++)
    {
        printOnePerson(t[i]);
    }
}
