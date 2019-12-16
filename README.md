# CRASH! The Cool and Really Awesome Shell
## What I Implemented
- Everything required
- Smart Quote Escaping: Anything in between quotes will be counted as one singular token
- Colorful Opening Header: A red devil themed ascii art header

## What I Tried and Failed
- Double Redirection

## "Features"
- When redirecting stdin to the shell, the output is entirely red. `$ make run < TEST_COMMANDS`
- Multiple ;'s will redo the previous command that many times
## Files and Function Headers
### main.c
```
/**
 * A function that does nothing to catch C-c
 *  
 * @param n The signal
 */
void intHandler(int n);

/**
 * A function that prints the shell logo and name in red.
 */
void print_header();
```
### parse_args.c
```
/**
 * Returns the number of seperate commands contained in the line
 * Splits a string by ";", taking care not to break apart quotes
 *  
 * @param line: The line to be parsed
 * @param args: A char* array to write the commands to
 * @return The number of seperate/individual commands in the string
 */
int parse_multiple(char *line, char **args);

/**
 * Splits a string into its args, taking care not to keep quotes intact
 *  
 * @param line: The line to be parsed
 * @param args: A char* array to write the args to
 * @return void
 */
void parse(char *line, char **args);
```
### execute.c
```
/**
 * Returns the length of a char **
 *  
 * @param command: A char** array whose length you wish to find
 * @return The length of the char** array in terms of consecutive non_null strings
 */
int arr_len(char ** command);
/**
 * Forks a child process and executes the passed command
 *  
 * @param command A char** containing the command you wish to execute 
 */
void execute(char ** command);
/**
 * Loops through command and replaces all redirection chars with NULL while
 *  marking their location and type in positions
 *  
 * @param num_args The number of arguments in the command
 * @param command  A char** containing the command you wish to execute
 * @param positions An int* the same length of commands
 */
void split_redirects(int num_args, char ** command, int * positions);
/**
 * Executes the given command with old_fd being redirected to new_fd
 *  
 * @param command  A char** containing the command you wish to execute
 * @param new_fd   The new file descriptor
 * @param new_fd   The old file descriptor
 */
void execute_with_redirects(char ** command, int new_fd, int old_fd);
/**
 * Executes the given commands with specified redirects
 *  
 * @param command  A char** containing the commands you wish to execute
 */
void execute_redirects(char ** command);
```
