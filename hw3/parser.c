#include "parser.h"

void parse(parsed_input* inp, char *line) {
    char *tmp;
    unsigned long size;

    size = strlen(line);

    if ( line[size-1] == '\n' )
        line[size-1] = '\0';

    tmp = strtok(line, " ");

    inp->arg1 = inp->arg2 = NULL;
    if ( !strcmp(tmp, "cd") ) {
        inp->type = CD;
    }
    else if ( !strcmp(tmp, "ls") ) {
        inp->type = LS;
    }
    else if ( !strcmp(tmp, "mkdir") ) {
        inp->type = MKDIR;
    }
    else if ( !strcmp(tmp, "touch") ) {
        inp->type = TOUCH;
    }
    else if ( !strcmp(tmp, "mv") ) {
        inp->type = MV;
    }
    else if ( !strcmp(tmp, "cat") ) {
        inp->type = CAT;
    }

    tmp = strtok(NULL, " ");

    size = strlen(tmp);

    inp->arg1 = (char*) calloc(size, sizeof(char));
    strcpy(inp->arg1, tmp);

    tmp = strtok(NULL, " ");

    if ( tmp ) {
        size = strlen(tmp);

        inp->arg2 = (char*) calloc(size, sizeof(char));
        strcpy(inp->arg2, tmp);
    }
}
void clean_input(parsed_input* inp) {
    free(inp->arg1);
    if ( inp->arg2 )
        free(inp->arg2);
}
