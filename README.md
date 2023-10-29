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

The tests below were thought up by my friend `@waltergcc`, for more examples you can visit his repository here

```bash
$> echo "Hello, world!"
Hello, world!
$> ls -l
[...command output...]
$> exit
```

## Contributors

* Ívany Pinheiro
* Clara Franco


