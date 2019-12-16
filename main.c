#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "execute.h"
#include "parse_args.h"
/**
 * A function that does nothing to catch C-c
 *  
 * @param n The signal
 */
void intHandler(int n){
}
/**
 * A function that prints the shell logo and name in red.
 */
void print_header(){
  printf("\033[1;31m");
  printf("The Cool and Really Awesome Shell! (CRASH)\n");  
  char * h =
    "             (`-')  (`-')  _  (`-').-> (`-').-> \n"
    " _        <-.(OO )  (OO ).-/  ( OO)_   (OO )__  \n"
    " \\-,-----.,------,) / ,---.  (_)--\\_) ,--. ,'-' \n"
    "  |  .--./|   /`. ' | \\ /`.\\ /    _ / |  | |  | \n"
    " /_) (`-')|  |_.' | '-'|_.' |\\_..`--. |  `-'  | \n"
    " ||  |OO )|  .   .'(|  .-.  |.-._)   \\|  .-.  | \n"
    "(_'  '--'\\|  |\\  \\  |  | |  |\\       /|  | |  | \n"
    "   `-----'`--' '--' `--' `--' `-----' `--' `--'\n";
  printf("%s\n", h);
  printf("\033[0m");
}
int main(){
  signal(SIGINT, intHandler);
  char * home_dir = getenv("HOME");
  int HOME_LEN = strlen(home_dir);
  print_header();
  char * argv[32];
  char * commands[32];
  while(1){
    for(int i = 0; i < 32; i++){
      argv[i] = NULL;
      commands[i] = NULL;
    }
    char CWD[1024];
    getcwd(CWD, 1024);
    if(!strncmp(home_dir, CWD, strlen(home_dir))){
      printf("~%s $ ", CWD + HOME_LEN);
    }else{
      printf("%s $ ", CWD);
    }
    char *buffer = "";
    size_t  n = 1024;
    buffer = calloc(n, 1);
    getline(&buffer, &n, stdin);
    buffer[strlen(buffer) - 1] = '\0';
    int parses = parse_multiple(buffer, commands);
    for(int i = 0; i < parses; i++){
      parse(commands[i], argv);
      if(!argv[0]){
      }else if(!strcmp(argv[0], "exit")){
	exit(0);
      }else if (!strcmp(argv[0], "cd")){
	if(argv[1]){
	  chdir(argv[1]);
	}else{
	  chdir("/");
	}
      }else{
	execute_redirects(argv);
      }
    }
    free(buffer);
  }
  return 0;
}
