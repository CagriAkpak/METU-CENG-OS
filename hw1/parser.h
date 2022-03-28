#ifndef HW1_PARSER_H
#define HW1_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

    typedef enum command_type{
        PROCESS_BUNDLE_CREATE,      // Indicate that pbc command is received.
        PROCESS_BUNDLE_STOP,        // Indicate that pbs command is received.
        PROCESS_BUNDLE_EXECUTION,   // Indicate that one or more bundles want to be executed.
        QUIT                        // Indicate that quit command is received.
    }command_type;

    typedef struct bundle_execution {
        char *name;     // Name of the bundle that is meant to be executed.
        char *output;   // Output redirection file name of the bundle.
        char *input;    // Input redirection file name of the bundle.
    } bundle_execution;

    typedef struct parsed_command {
      command_type type; // To show which command it is.
      char *bundle_name; // Name of the bundle if the command is pbc.
      int bundle_count;  // If there is a bundle execution, this indicates the number of bundles in the pipeline.

      // If it is a pipeline, the order is the same. For example input bundle1 | bundle2 would translate to:
      // [{"bundle1", NULL, NULL}, {"bundle2", NULL, NULL}]
      // This means that output of the "bundle1" should be redirected to the input of "bundle2"
      // The size of the array is known from the previous variable, therefore, there is no NULL value at the end.
      bundle_execution *bundles;

    } parsed_command;

    // This union meant to show that it is either one of the three specific commands or
    // The shell is currently creating a bundle and will return the command and its arguments.
    // With one exception, "pbs" command. It will fill the command argument and return 1 from the parse function.
    // Details are explained above the parse function.
    typedef union parsed_input {
        parsed_command command; // This is filled correctly when the input is a specific command
        char **argv;     // This is filled when the input is a process inside a bundle
    } parsed_input;


    // This function will take a single line of input and int to indicate whether a bundle creation is going on.
    // If the program received a "pbc" command and not yet received the corresponding "pbs", this int should be 1.
    // The line string should end with a terminating '\0' character. Do not remove the '\n' at the end as well.
    // After receiving the arguments, it will fill the parsed_input variable. This variable cannot be NULL.
    // This parser also supports quoted arguments (ex: "arg") and ignores extra whitespaces if they are not inside quotes.
    // Length of each argument should be no bigger than 255.
    // Returns 1 if there is a bundle creation going on and receives "pbs" command, otherwise returns 0 on all cases.
    int parse(char *line, int is_bundle_creation, parsed_input *parsedInput);


#ifdef __cplusplus
}
#endif

#endif //HOMEWORKS_PARSER_H
