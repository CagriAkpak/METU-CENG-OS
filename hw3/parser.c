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
    else if ( !strcmp(tmp, "quit") ) {
        inp->type = QUIT;
    }else{
        inp->type = ERR;
    }

    tmp = strtok(NULL, " ");

    if ( tmp ) {
        size = strlen(tmp);

        inp->arg1 = (char*) calloc(size+1, sizeof(char));
        strcpy(inp->arg1, tmp);
    }

    tmp = strtok(NULL, " ");

    if ( tmp ) {
        size = strlen(tmp);

        inp->arg2 = (char*) calloc(size+1, sizeof(char));
        strcpy(inp->arg2, tmp);
    }
}
void clean_input(parsed_input* inp) {
    if ( inp->arg1 )
        free(inp->arg1);
    if ( inp->arg2 )
        free(inp->arg2);
}

char** tokenizePath(char* p){
    if(!p){
        char** ret = (char**)malloc(sizeof(char*));
        ret[0] = NULL;
        return ret;
    }

	char* tmp;
	int len = strlen(p);
    if(len==0){
        char** ret = (char**)malloc(sizeof(char*));
        ret[0] = NULL;
        return ret;
    }
    int count = 1;

	if ( p[len-1] == '\n' )
	p[len-1] = '\0';

    if(p[len-1]=='/')count--;

    for(int i=0;i<len;i++){
        if(p[i]=='/')count++;
    }

    char** ret = (char**)malloc(sizeof(char*)*(count+1));
    int i=0;

    //* change this flag if you want to have / for paths starting from root. Currently it is ""(empty string) instead of "/"
    int useSlashAsRootToken = 0;

    if(p[0]=='/'){
        if(useSlashAsRootToken){
            ret[0] = (char*) calloc(2, sizeof(char));
            ret[0][0] = '/';
            ret[0][1] = '\0';
        }else{
            ret[0] = (char*) calloc(1, sizeof(char));
            ret[0][0] = '\0';
        }
        i++;
    }

    int f = 1;
    for(;i<count;i++){
        tmp = strtok(f?p:NULL, "/");
        f=0;

        int size = strlen(tmp);
        ret[i] = (char*) calloc(size+1, sizeof(char));
        strcpy(ret[i], tmp);
    }

    ret[count] = NULL;
    return ret;
}

void clean_tokenized_path(char** nameList){
    for (int i = 0; nameList[i]; i++){
        free(nameList[i]);
    }
    free(nameList);
}