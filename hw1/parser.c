#include "parser.h"

int parse(char *line, int is_bundle_creation, parsed_input *parsedInput) {
    if ( !parsedInput )
        return 0;
    int is_quoted;
    char buffer[256];
    int argument_count, argument_index;
    int index;
    
    memset(buffer, 0, sizeof(char)*256); 
    if ( is_bundle_creation ) {
        is_quoted = 0;
        index = 0;
        argument_index = 0;
        argument_count = 0;
        for ( char *current = line; *current ; current++) {
            if ( is_quoted ) {
                if ( *current == '"' ) {
                    is_quoted = 0;
                }
                else
                    index++;
            }
            else {
                if (*current == '"')
                    is_quoted = 1;
                else if (isspace(*current)) {
                    if ( index == 0 ) continue;
                    argument_count++;
                    index = 0;
                }
                else
                    index++;
            }
        }

        parsedInput->argv = (char **)calloc(argument_count+1, sizeof(char*));
        parsedInput->argv[argument_count] = NULL;

        is_quoted = 0;
        index = 0;
        for ( char *current = line; *current ; current++) {
            if ( is_quoted ) {
                if ( *current == '"' )
                    is_quoted = 0;
                else
                    buffer[index++] = *current;
            }
            else {
                if ( *current == '"' )
                    is_quoted = 1;
                else if ( isspace(*current) ) {
                    if ( index == 0 ) continue;
                    else if ( strcmp(buffer, "pbs") == 0 ) {
                        parsedInput->command.type = PROCESS_BUNDLE_STOP;
                        return 1;
                    }
                    buffer[index++] = '\0';
                    parsedInput->argv[argument_index] = (char*) calloc(index, sizeof(char));
                    strcpy(parsedInput->argv[argument_index], buffer);
                    index = 0;
                    argument_index++;
                }
                else
                    buffer[index++] = *current;
            }
        }
    }
    else {
        is_quoted = 0;
        argument_count = 1;
        for ( char *current = line; *current ; current++) {
            if (is_quoted) {
                if (*current == '"')
                    is_quoted = 0;
            }
            else {
                if (*current == '"')
                    is_quoted = 1;
                else if ( *current == '|' )
                    argument_count++;
            }
        }
        is_quoted = 0;
        index = 0;
        argument_index = 0;
        int is_next_input, is_next_output, executable_index;
        for ( char *current = line; *current ; current++) {
            if (is_quoted) {
                if (*current == '"')
                    is_quoted = 0;
                else
                    buffer[index++] = *current;
            } else {
                if (*current == '"')
                    is_quoted = 1;
                else if (isspace(*current)) {
                    if ( index == 0 ) continue;
                    buffer[index++] = '\0';
                    if (!argument_index) {
                        if ( strcmp(buffer, "pbc") == 0 )
                            parsedInput->command.type = PROCESS_BUNDLE_CREATE;
                        else if ( strcmp(buffer, "pbs") == 0 ) {
                            parsedInput->command.type = PROCESS_BUNDLE_STOP;
                            return 1;
                        }
                        else if ( strcmp(buffer, "quit") == 0 ) {
                            parsedInput->command.type = QUIT;
                            return 0;
                        }
                        else {
                            parsedInput->command.type = PROCESS_BUNDLE_EXECUTION;
                            parsedInput->command.bundle_count = argument_count;
                            parsedInput->command.bundles = (bundle_execution*) calloc(argument_count, sizeof(bundle_execution));

                            is_next_input = 0;
                            is_next_output = 0;
                            executable_index = 0;

                            parsedInput->command.bundles[executable_index].name = (char*)calloc(index, sizeof(char));
                            strcpy(parsedInput->command.bundles[executable_index].name, buffer);

                            parsedInput->command.bundles[executable_index].input = NULL;
                            parsedInput->command.bundles[executable_index].output = NULL;

                        }
                    }
                    else {
                        if ( parsedInput->command.type == PROCESS_BUNDLE_CREATE ) {
                            parsedInput->command.bundle_name = (char*) calloc(index, sizeof(char));
                            strcpy(parsedInput->command.bundle_name, buffer);
                            return 0;
                        }
                        else {
                            if ( argument_index % 2 == 1 ) {
                                if ( strcmp(buffer, "<") == 0 )
                                    is_next_input = 1;
                                else if ( strcmp(buffer, ">") == 0 )
                                    is_next_output = 1;
                                else if ( strcmp(buffer, "|") == 0 )
                                    executable_index++;
                            }
                            else {
                                if ( is_next_input ) {
                                    parsedInput->command.bundles[executable_index].input = (char*)calloc(index, sizeof(char));
                                    strcpy(parsedInput->command.bundles[executable_index].input, buffer);
                                    is_next_input = 0;
                                }
                                else if ( is_next_output ) {
                                    parsedInput->command.bundles[executable_index].output = (char*)calloc(index, sizeof(char));
                                    strcpy(parsedInput->command.bundles[executable_index].output, buffer);
                                    is_next_output = 0;
                                }
                                else {
                                    parsedInput->command.bundles[executable_index].name = (char*)calloc(index, sizeof(char));
                                    strcpy(parsedInput->command.bundles[executable_index].name, buffer);
                                }
                            }
                        }
                    }
                    index = 0;
                    argument_index++;
                } else
                    buffer[index++] = *current;
            }
        }
    }
}
