//You shouldn't need any prototypes, #defines, or 
//typedefs in main.cc.  They should all be in assign3.h
//and the following line will automatically bring them
//into main.cc.
#include "structures.h"

int main()
{
	person_t p0, p1, p2;
	person_t people[3];

	//Getting first person into p0.
	getOnePerson(&p0);

	//Getting next two p1 and p2 people using an array.
	people[0] = p1;
	people[1] = p2;
	getPeople(people, 2);
	
	//Printing the first person.
	printOnePerson(p0);

	//printing from the array.
	printPeople(people, 2);

	return 0;
}

