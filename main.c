#include "headers.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
int arr_len(char ** command){
  int i = 0;
  while(command[i++]);
  return i - 1;
}
int redirect_stdout(int fd){
  int d = dup(STDIN_FILENO);
  dup2(fd, STDIN_FILENO);
  return d;
}
int re_redirect_stdout(int fd){
  return dup2(STDIN_FILENO, fd);
}
void execute(char ** command){
  int pid = fork();
  int status;
  if(pid < 0){
    exit(1);
  }else if (pid == 0){
    //printf();
    int s = execvp(*command, command);
    if(s < 0){
      printf("NOOOOO! Execution Failed!\n");
      exit(1);
    }
  }else{
    while(wait(&status) != pid);
  }
}
void split_redirects(int num_args, char ** command, int * positions){
  for(int i = 0; i < num_args; i++){
    positions[i] = 0;
    if(!strcmp(command[i], ">")){
      command[i] = NULL;
      positions[i] = 1;
    }else if(!strcmp(command[i], ">>")){
      command[i] = NULL;
      positions[i] = 2;
    }else if(!strcmp(command[i], "<")){
      command[i] = NULL;
      positions[i] = 3;
    }else if(!strcmp(command[i], "|")){
      command[i] = NULL;
      positions[i] = 4;
    }else if(!command[i]){
      positions[i] = 5;
    }
  }
}
void execute_with_redirects(char ** command, int new_fd, int old_fd){
  //Replaces old_fd with new_fd ! Then executes
  int backup  = dup(old_fd);
  dup2(new_fd, old_fd);
  execute(command);
  close(old_fd);
  dup2(backup, old_fd);
}
void execute_redirects(char ** command){
  int num_args = arr_len(command);
  //printf("Well we made it this far \n");
  int positions[num_args];
  split_redirects(num_args, command, positions);
  int pos = 0;
  int last = 0;
  while(pos < num_args){
    //printf(">>>>%d %s %d\n", pos, command[pos], positions[pos]);
    if(positions[pos] || pos == num_args - 1){
      int flags = 0;
      int location = pos + 1 < num_args && positions[pos] < 3 ? STDOUT_FILENO : STDIN_FILENO;
      int in_out[] = {STDIN_FILENO, STDOUT_FILENO};
      int fd = STDIN_FILENO;
      if(positions[pos] == 1){ // >
	flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(command[pos + 1], flags, 0644);
	in_out[1] = fd;
	execute_with_redirects(command + last + (last ? 1 : 0), fd, STDOUT_FILENO);
      }else if(positions[pos] == 2){ // >>
	flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(command[pos + 1], flags, 0644);
	in_out[1] = fd;
	execute_with_redirects(command + last + (last ? 1 : 0), fd, STDOUT_FILENO);
      }else if(positions[pos] == 3){ // <
	flags = O_RDONLY;
	fd = open(command[pos + 1], flags, 0644);
	in_out[0] = fd;
	execute_with_redirects(command + last + (last ? 1 : 0), fd, STDIN_FILENO);
      }else if(positions[pos] == 4){ // |
	pipe(in_out);
	execute_with_redirects(command + last + (last ? 1 : 0), in_out[1], STDOUT_FILENO);
	execute_with_redirects(command + pos + 1, in_out[0], STDIN_FILENO);

      }else{
	execute(command + last + (last ? 1 : 0));
      }      
      pos += 2;
      last = pos;
    }
    pos++;
  }
}
void intHandler(int n){
}
void red () {
  printf("\033[1;31m");
}
void reset () {
  printf("\033[0m");
}
void print_header(){
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
}
int main(){
  //signal(SIGINT, intHandler);
  char * home_dir = getenv("HOME");
  int HOME_LEN = strlen(home_dir);
  red();
  printf("The Cool and Really Awesome Shell! (CRASH)\n");
  print_header();
  reset();
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
      //printf("executing -- %s", commands[i]);
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
