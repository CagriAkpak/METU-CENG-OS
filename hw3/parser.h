#ifndef HW3_PARSER_H
#define HW3_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
typedef enum input_type {
    CD,
    LS,
    MKDIR,
    TOUCH,
    MV,
    CAT,
    QUIT,
    ERR
}input_type;

typedef struct parsed_input {
    input_type type;
    char *arg1;
    char *arg2;
} parsed_input;
/*
 * Parses a single line of input and separates it into arguments
 * It does not accept wrong input and all arguments must be separated with a space
 * It can have a newline or not at the end
 * The string must naturally terminate with '\0'
 * */
void parse(parsed_input* inp, char *line);

/* Free the argument arrays. Use before discarding the arguments, otherwise there will be memory leaks.*/
void clean_input(parsed_input* inp);


/**
 * Converts the path 'p' into tokenized set of strings. p can be parsed_input->arg1.
 * Note that the integrity of p is NOT kept after this function has been called.
 * Copy it beforehand if you are going to use p afterwards.
 * 
 * Returns: char**, terminated with a NULL.
 * Example usage:
 * 		char** list = tokenizePath(p->arg1);
 *		for (int i = 0; list[i]; i++){
 *			printf("item: %s\n",list[i]);
 *		}
 *		clean_tokenized_path(list);
 *
 *
 * You also have the option to get "/" as the root element, instead of an empty string "". Check the .c file for that.
 */
char** tokenizePath(char* p);
void clean_tokenized_path(char** nameList);

#ifdef __cplusplus
}
#endif

#endif //HW3_PARSER_H
