/*
 * linkedlist.c
 *
 * Based on the implementation approach described in "The Practice 
 * of Programming" by Kernighan and Pike (Addison-Wesley, 1999).
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "list.h"


Patient *new_patient(char *name, int birth_year, int priority) {
    assert( name != NULL);

    Patient *temp = (Patient *)emalloc(sizeof(Patient));

    temp->name       = strdup(name);
    temp->birth_year = birth_year;
    temp->priority   = priority;
    temp->next       = NULL;

    return temp;
}


Patient *add_front(Patient *list, Patient *new) {
    new->next = list;
    return new;
}


Patient *add_end(Patient *list, Patient *new) {
    Patient *curr;

    if (list == NULL) {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return list;
}


Patient *add_with_priority(Patient *list, Patient *new) {
    /* TODO: You have to implement this method to add patients with the
        correct priority in the list. Recall that a patient with higher
        priority must come before patients with lower priority. Also
        recall that a patient with the same priority as other patients
        must come after those patients, and before patients with lower
        priority.
        In the emergency room, higher priority means a smaller number 
        than lower priority. For instance, a patient with priority 1  
        has a higher priority than a patient with priority 2. */
//	printf("start add");
//
	Patient *curr = list;

	//add a case here to check if the queue is empty, or to add a node to front
	if (list == NULL || new->priority < list->priority) {
		new->next = list;
		list = new;
		return list;
	} 
		//now traverse the queue and compare priorities
		//check if curr->next is null, and check if prio of next > curr		
	while(curr->next != NULL && curr->next->priority < new->priority) {
		curr = curr->next;
	//	printf("%d || %s", curr->priority, curr->name);
	}

	//handle the case where the priorities are equal (add new to back of its prio)
	while(curr->next != NULL && new->priority == curr->next->priority) {
		curr = curr->next;
	}
		
		//now arrived at point where prio is equal
	new->next = curr->next;
	curr->next = new;
//	printf("end add");	
	return list;


	
}


Patient *peek_front(Patient *list) {
    return list;
}


Patient *remove_front(Patient *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->next;
}


void apply(Patient *list,
           void (*fn)(Patient *list, void *),
           void *arg)
{
    for ( ; list != NULL; list = list->next) {
        (*fn)(list, arg);
    }
}
