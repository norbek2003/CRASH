#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int parse_multiple(char *line, char **args){
  //Fix this for ";"
  int parses = 0;
  int len = strlen(line);
  int p = 0;
  int in_quote = 0;
  int last = 0;
  while(p <= len){
    if(line[p] == '"'){
      in_quote = !in_quote;
    }
    if(!in_quote && (line[p] == ';' || !line[p])){
      line[p] = '\0';
      *args = line + last;
      *args++;
      parses += 1;
      last = p + 1;
    }
    p++;
  }
  *args = NULL;
  return parses;
}
void parse(char *line, char **args){
   //Returns a parsed string of a command, removes multiple spaces and preserves quotes as strings
  if(line == NULL){
    return;
  }
  char arr[strlen(line)];
  strcpy(arr, line);
  char * pos = arr;
  char * token = strtok_r(line, " ", &pos);
  *args = token;
  *args++;
  while(token){
    if(pos[0] == '\"'){
      token = strtok_r(NULL, "\"", &pos);
    }else{
      token = strtok_r(NULL, " ", &pos);
    }
    *args = token;
    *args++;
  }
  *args = NULL;
}

