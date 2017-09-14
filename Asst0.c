/*
 * Asst0.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
Struct for growing arraylist
that allocates memory as each new element
is added. 
*/
typedef struct{
	char **arr;
	int size;
}ArrayList;

/*
Adds new string to given ArrayList
and creates new ArrayList if given is NULL.
Also allocates memory as needed
*/
void add(ArrayList **arrayl, char *str){
	if(*arrayl == NULL){
		ArrayList *a = (ArrayList*)malloc(sizeof(ArrayList));
		a->arr = (char**)malloc(sizeof(char*));
		a->arr[0] = str;
		*arrayl = a;
		(*arrayl)->size = 1;
	}
	else{
		(*arrayl)->arr = (char**)realloc((*arrayl)->arr, (((*arrayl)->size) + 1)*sizeof(char*));
		(*arrayl)->arr[(*arrayl)->size] = str;
		(*arrayl)->size++;
	}
}

//Appends char to end of string
void append(char *s, char c){
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

/*
Wraps compared strings to const
type required by qsort. 
Appropriately named.
*/
int cmpShit(const void *a, const void *b){ 
    return strcmp(*(char* const*)a, *(char* const*)b);
}

int main(int argc, char** argv){
	
	//ERROR CHECKING STRING EXISTENCE
	if(argv[1] == NULL || strlen(argv[1]) <= 0){
		printf("ERROR: INVALID INPUT\n");
		return 1;
	}
	
	//ERROR CHECKING FOR NON ALPHA STRING
	int c;
	int alphaExists = 0;
	for(c = 0; c < strlen(argv[1]); c++){
		if(isalpha(argv[1][c])){
			alphaExists = 1;
		}
	}
	if(!alphaExists){
		printf("ERROR: NO ALPHABET CHARACTERS IN STRING\n");
		return 1;
	}
	
	//Obtaining pointer to argv[1]
	int length = strlen(argv[1]) + 1;
	char *str = (char*)malloc(length);
	str = argv[1];
	str[length] = '\0';
	
	//Initialize ArrayList and create temp pointer (s)
	ArrayList *array = NULL;
	char *s = NULL;
	int sSize = 1;
	int i;
	
	//Traverses string and creates "token" letter by letter
	for(i = 0; i < length; i++){
		if(isalpha(str[i])){
			sSize += 1;
			s = (char*)realloc(s, sSize);
			append(s, str[i]);
		}
		//Non-alpha chars result in adding created string
		else{
			if(s != NULL){
				add(&array, s);
			}
			sSize = 1;
			s = NULL;
		}
	}
	
	//Quicksort array
	qsort(array->arr, array->size, sizeof(char*), cmpShit);
	
	//Print that mofo and free memory
	for(i = 0; i < array->size; i++){
		printf("%s\n",array->arr[i]);
		free(array->arr[i]);
	}
	
	free(array);
	
	return 0;
}
