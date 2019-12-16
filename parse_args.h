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

