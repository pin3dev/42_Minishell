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

###Quote Handling
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

#I encourage you to try another type and quantity of quotation marks,
# mixing double and single quotation marks, you can use your creativity
```

## Contributors

* Ívany Pinheiro
* Clara Franco


