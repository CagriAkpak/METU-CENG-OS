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
    CAT
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

#ifdef __cplusplus
}
#endif

#endif //HW3_PARSER_H
