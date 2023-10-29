# Minishell
Minishell - As beautiful as a shell 🐚

>In this repository, you'll find a detailed description of what this project entails, instructions on how to test it, and soon, a comprehensive theoretical breakdown of its construction. Our aim is to provide a clear and thorough overview, making it easy for you to navigate, explore, or contribute to this project. Scroll down for more in-depth details and relevant information.

## Table of Contents
- [Project Overview](#overview)
- [Mandatory Features](#mandatory-features)
- [Project Compilation and Execution](#compilation-and-execution)
- [Tests -  Usage Examples (toggle-able)](#usage-examples)
- [Theoretical Explanation (toggle-able)](#theoretical-explanation)
- [Copyright](#contributors)

<p align="center">
  <img src=".gif" alt="gif_minishell_test" style="display: block; margin: 0 auto; width: 100%;">
</p>

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

---

<details><summary><h2 id="Usage Examples">Usage Examples</h2></summary>

The tests below were thought up by my friend `@waltergcc`, for more examples you can visit his [repository here](https://github.com/waltergcc/42-minishell#tests)

## Table of Tests
- [General](#general)
- [Quotes](#quote-handling)
- [Builtins](#builtins)
- [Expanding $?](#expanding-exit-status-variables-by-)
- [Expanding $](#expanding-environment-variables-by-)
- [Signals](#signal-control-by-ctrlc-ctrld-ctrl)
- [Pipes](#pipes)
- [Redirs and Heredocs](#redirs-and-heredoc)

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
cliva_minixHell> echo '$HOME > home.txt'
#[$HOME > home.txt]

#I encourage you to test the status with other commands such as expr for example, you can use your creativity
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

### Expanding Exit Status Variables By `$?`
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

#
```

### Expanding Environment Variables By `$`
```bash
cliva_minixHell> echo $HOME
#[...your HOME path...]
cliva_minixHell> echo "$HOME"
#[...your HOME path...]
cliva_minixHell> echo '$HOME'
#[$HOME]
cliva_minixHell> echo $HOME.test
#[...your HOME path + .test...]
cliva_minixHell> echo $HOME/test
#[...your HOME path + /test...]
cliva_minixHell> echo $HOME.test/$USER
#[...your HOME path + /test + / +  your USER name...]
```

### Signal Control by `CTRL+C`, `CTRL+D`, `CTRL+\`
###### EMPTY PROMPT

```bash
cliva_minixHell> #HOLD CTRL+C
#[^C]
cliva_minixHell> echo $?
#[130]
cliva_minixHell> #HOLD CTRL+\
#[...nothing happens...]
cliva_minixHell> #HOLD CTRL+D
#[exit]
bash> echo $?
#[0]
```

###### FULL PROMPT

```bash
cliva_minixHell> digit anything here #HOLD CTRL+C
#[^C]
cliva_minixHell> echo $?
#[130]
cliva_minixHell> digit anything here #HOLD CTRL+\
#[...nothing happens...]
cliva_minixHell> digit anything here #HOLD CTRL+D
#[...nothing happens...]
```

###### INTERACTIVE MODE

```bash
cliva_minixHell> cat
#[...interactive mode]
cliva_minixHell> #HOLD CTRL+C
#[^C]
cliva_minixHell> echo $?
#[130]
cliva_minixHell> cat
#[...interactive mode]
cliva_minixHell> #HOLD CTRL+\
#[\Quit (core dumped)]
cliva_minixHell> echo $?
#[131]
cliva_minixHell> cat
#[...interactive mode]
cliva_minixHell> #HOLD CTRL+D
#[exit]
bash> echo $?
#[0]
```

### Pipes
```bash
cliva_minixHell> cat Makefile | grep NAME | wc -l
#[...how many lines are in the Makefile with NAME...]
cliva_minixHell> ps aux | sort -rk 4 | head
#[...List the processes that consume the most memory...]
cliva_minixHell> ls -l | grep "^-" | wc -l
#[...Count the number of files in a directory...]
```

### Redirs and Heredoc
```bash
cliva_minixHell> ls -l > test
#[...create test file with the ls output inside...]
cliva_minixHell> cat Makefile >> test
#[...add Makefile content on file test...]
cliva_minixHell> wc -l < test
#[...count the number of lines of file test..]
cliva_minixHell> cat << EOF
HI GUYS
EOF
#[HI GUYS]
cliva_minixHell> cat << EOF | wc -l
HI GUYS
EOF
#[1]
cliva_minixHell> cat << EOF
HI GUYS
HERE IS "$USER"
EOF
#[HI GUYS 
# HERE IS "YOUR_USER"]
cliva_minixHell> < test cat > test2
#[...create test2 file with thetest file content]
cliva_minixHell> wc -l < /etc/passwd > file1 > file2 > file3 > file4
#[...create file1, 2 and 3 empty and file4 with the  countn lines of passwd file content]
```
</details>

<details><summary><h2 id="Theoretical Explanation">Theoretical Explanation</h2></summary>

  >soon

</details>

## Contributors

>I would like to extend my deepest gratitude to the `@clima-fr` for the remarkable partnership. Together, we navigated 42 intense days, filled with challenges and learning experiences. Your commitment and dedication were pivotal in bringing this project to fruition. Thank you for every shared moment and all the hard work throughout this journey.

* Ívany Pinheiro aka [`@pin3dev`](https://github.com/pin3dev)
* Clara Franco aka [`@clima-fr`](https://github.com/clima-fr)


