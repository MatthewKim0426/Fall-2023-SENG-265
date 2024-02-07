#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "emalloc.h"

#define MAX_LINE_LEN 5000

void inccounter(Patient *p, void *arg) {
    /* DO NOT CHANGE THIS FUNCTION. */
    int *ip = (int *)arg;
    (*ip)++;
}


void print_word(Patient *p, void *arg) {
    /* DO NOT CHANGE THIS FUNCTION. */
    char *fmt = (char *)arg;
    printf(fmt, p->name, p->birth_year, p->priority);
}


void dump(Patient *list) {
    /* DO NOT CHANGE THIS FUNCTION. */
    int len = 0;

    apply(list, inccounter, &len);    
    printf("Number of patients: %d\n", len);

    apply(list, print_word, "%s,%d,%d\n");
}

Patient *tokenize_line(char *line) {
    /* TODO: You have to implement this function to tokenize a line
        and either:
        1) return a valid Patient pointer if the line command is enqueue
        2) return NULL if the line command is dequeue
*/

//	printf("Start tokenize_line");
	char *token;
	token  = strtok(line, ",");
	char *name;
	int year;
	int prio;
	int i = 0;	

	if(strcmp("dequeue\n", token)==0) {
		return NULL;
	} else {
		token = strtok(NULL, ",");
		i++;
		while (token != NULL) { 
			if (i == 1) {
				name = token;
			} else if (i == 2) {
				year = atoi(token);
			} else if (i == 3) {
				prio = atoi(token);		
			}
			i++;
			token = strtok(NULL, ",");

		}
		Patient *result= new_patient(name, year, prio);
		return result;
	}
							
}

Patient *read_lines(Patient *list) {
    /* TODO: You have to implement this function to tokenize all lines
        from the stdin. You HAVE TO use the tokenize_line function
        as an auxiliary function to parse each line.
        If tokenize_line returns a valid Patient pointer, add the
        patient to the list with the correct priority.
        Otherwise, dequeue the first patient from the list.
        At the end of the function, return the list to the caller.       
    */
	Patient *result;
	char line[1000];
	while(fgets(line, sizeof(line), stdin)) {
		result = tokenize_line(line);
		if (result != NULL) {
			list = add_with_priority(list, result);
		} else {
			list = remove_front(list);
		}
	}
//	printf("end r_l");
	return list;
}

void deallocate_memory(Patient *list) {
    /* TODO: You have to implement this function to deallocate (free) 
        memory from the list before the program ends
    */
//	printf("AHJHHHHH");
	Patient *curr = list;
	Patient *next; 
	
	while (curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}
}


int main(int argc, char *argv[]) {
    /* DO NOT CHANGE THE MAIN FUNCTION. YOU HAVE TO IMPLEMENT YOUR
        CODE TO FOLLOW THE SEQUENCE OF INSTRUCTIONS BELOW. */
    Patient *list = NULL;

    if (argc != 1) {
            printf("Usage: %s\n", argv[0]);
            printf("Should receive no parameters\n");
            printf("Read from the stdin instead\n");
            exit(1);
    }

    list = read_lines(list);
 
    dump(list);
    
    deallocate_memory(list);

    exit(0); 
}
