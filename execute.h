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
