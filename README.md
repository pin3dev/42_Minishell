# Minishell

## Overview

This project is a simplified implementation of a Unix shell, adhering to the `minishell` project curriculum of 42 school.

## Mandatory Features

1.  Display command prompt.
2.  Maintain command history.
3.  Locate and launch executables using PATH, relative, or absolute paths.
4.  Restrict to one global variable for signal indication.
5.  Ignore unneeded special characters (e.g., `\` and `;`).
6.  Proper handling of quotes (`'` and `"`).
7.  Redirections: `<`, `>`, `<<`, `>>`.
8.  Piping using `|`.
9.  Manage environment variables (`$` and `$?`).
10.  Handle signals: `CTRL-C`, `CTRL-D`, `CTRL-\`.
11.  Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

## Compilation and Execution

```bash
make
./minishell
```

## Usage Examples

The tests below were thought up by my friend `@waltergcc`, for more examples you can visit his [repository here](https://github.com/waltergcc/42-minishell#tests)

### General
```bash
cliva_minixHell> date
#[...command output...]
cliva_minixHell> who
#[...command output...]
cliva_minixHell> touch 1 2 3
cliva_minixHell> ls
#[...command output + files 1 2 3 created...]
cliva_minixHell> rm 1 2 3
#[...command output + files 1 2 3 created...]
cliva_minixHell> ls
#[...command output without removed files 1 2 3...]
cliva_minixHell> /bin/ls
#[...command output...]

#I encourage you to test with more commands, you can use your creativity
```

### Quote Handling
```bash
cliva_minixHell> "/bin/ls"
#[...command output...]
cliva_minixHell> "ls"
#[...command output...]
cliva_minixHell> "ls -l"
#[...error output...]
cliva_minixHell> "cat" existing_files
#[...content of existing file output...]
cliva_minixHell> "cat existing_files"
#[...error output...]

#I encourage you to try another type and quantity of quotation marks, mixing double and single quotation marks, you can use your creativity
```

### Builtins

###### ECHO:
```bash
cliva_minixHell> echo This is a test
#[This is a test]
cliva_minixHell> echo -n Hello World
#[Hello Worldcliva_minixHell>]
cliva_minixHell> echo -n -n -n -n -n Hello World
#[Hello Worldcliva_minixHell>]
cliva_minixHell> echo -nnnnnnnnn Hello World
#[Hello Worldcliva_minixHell>]
cliva_minixHell> echo "Hello      with       spaces"
#["Hello with spaces"]
cliva_minixHell> echo "test with %specials *chars"
#[test with %specials *chars]
cliva_minixHell> echo "cat lol.c cat > Iol.c"
#[cat lol.c cat > Iol.c]
cliva_minixHell> echo 'Hello      with       spaces'
#["Hello with spaces"]
cliva_minixHell> echo 'test with %specials *chars'
#[test with %specials *chars]
cliva_minixHell> echo 'cat lol.c cat > Iol.c'
#[cat lol.c cat > Iol.c]

#I encourage you to test the echo command together with other associated commands, you can use your creativity
```

###### CD, PWD & ENV
```bash
cliva_minixHell> env
#[...current list of environment variables with their values output...]
cliva_minixHell> pwd
#[...path of your current directory output...] 
cliva_minixHell> cd .
#[...stay on your current directory...]
cliva_minixHell> cd ..
#[...change to the parent directory of the current directory...]
cliva_minixHell> cd /path/to/a/directory
#[...change to the directory provided...]
cliva_minixHell> cd 
#[...change to the HOME directory...]
```

###### EXPORT:
```bash
cliva_minixHell> export NEW_VAR
cliva_minixHell> export
#[...current list of environment variables with their values in alphabetical order, including the NEW_VAR...]
cliva_minixHell> env
#[...current list of environment variables with their values in common order, without the NEW_VAR...]
cliva_minixHell> export NEW_VAR=42
cliva_minixHell> export
#[...current list of environment variables with their values in alphabetical order, including the NEW_VAR and their new value...]
cliva_minixHell> env
#[...current list of environment variables with their values in common order, with the NEW_VAR and their value...]
cliva_minixHell> export NEW_VAR="A little change"
cliva_minixHell> export
#[...current list of environment variables with their values in alphabetical order, including the NEW_VAR and their new value...]
cliva_minixHell> export NEW_VAR=$USER
cliva_minixHell> export
#[...current list of environment variables with their values in alphabetical order, including the NEW_VAR and their new value (YOUR_USERNAME)...]
cliva_minixHell> export 123=VALUE
#[...error output...]
cliva_minixHell> export _123=VALUE
cliva_minixHell> export
#[...current list of environment variables with their values in alphabetical order, including the _123 and their value...]
```

###### UNSET:
```bash
cliva_minixHell> unset NEW_VAR _123
cliva_minixHell> export
#[...current list of environment variables with their values in alphabetical order, without NEW_VAR and _123...]
cliva_minixHell> env
#[...current list of environment variables with their values in common order, without NEW_VAR and _123...]
cliva_minixHell> unset HOME
cliva_minixHell> cd
#[...error output...]
cliva_minixHell> unset PATH
cliva_minixHell> #HERE TRY ANY COMMAND
#[...error output...]
```

###### EXIT
```bash
cliva_minixHell> exit
#[exit]
```

### ENVIROMMENTS VARIBLES `$` AND `$?`
```bash
cliva_minixHell> ./minishell
cliva_minixHell> exit 1
#[exit]
cliva_minixHell> echo $?
#[1]
cliva_minixHell> ./minishell
cliva_minixHell> exit 42
#[exit]
cliva_minixHell> echo $?
#[42]
cliva_minixHell> ./minishell
cliva_minixHell> exit -42
#[exit]
cliva_minixHell> echo $?
#[214]
cliva_minixHell> ./minishell
cliva_minixHell> exit 42 10
#[exit]
#[...error output...]
cliva_minixHell> echo $?
#[1]
cliva_minixHell> ./minishell
cliva_minixHell> exit 42blabla
#[...error output...]
```



## Contributors

* Ívany Pinheiro
* Clara Franco


