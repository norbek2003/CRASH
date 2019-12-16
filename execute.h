int redirect_stdout(int fd);
int re_redirect_stdout(int fd);
void execute(char ** command);
void split_redirects(int num_args, char ** command, int * positions);
void execute_with_redirects(char ** command, int new_fd, int old_fd);
void execute_redirects(char ** command);
