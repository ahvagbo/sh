#ifndef SH_BUILTIN_H
#define SH_BUILTIN_H 1

int sh_builtin_echo(char* args[]);
int sh_builtin_cat(char* args[]);
int sh_builtin_uname(char* args[]);

extern int (*builtin_commands[])(char* args[]);
extern char* builtins[];

int sh_num_builtins();

#endif
