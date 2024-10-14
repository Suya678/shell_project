# Quantum Shell - A basic shell by Juan and Depanshu
Quantum Shell is a very basic shell made in C. It has the following functionalities:
- n stage pipelining
- I/O redirection
- Command Search PAthways - Don't have to type in the exact path of the command
- Built in cd command
- Basic Signal handling: Ctrl c for not terminating and SIGCHILD for proper background processing

## Installation
The build directory already has the executable - quantum_shell. Otherwise, run the makefile

## Usage

```
//List the directories
QuantumShell$$: ls -l

// Output to the file 
QuantumShell$$: ls -l > out.txt

// Change the working directory to parent
QuantumShell$$: cd ..

// Multi Stage pipelining
QuantumShell$$: grep #include | sort < headers/cmd_runner.h

```
### Testing -  Test cases are included in final_tst.md file

## Syntax
```
The Syntax cam ne described in terms of a CFG :
Job → Pipeline [< token] [> token] [&]
Pipeline → Command [| Pipeline]
Command → Args
Args → token [Args]

Above:
- The '<', '>', '&' and | are terminal symbols. Token represent any sequence of non-whitespace characters.
- Square brackets indicate an optional segment
```

### Known bugs and limitations

|     |     |
| --- | --- |
| Quotes (' ' / " ") | Programs like \`awk\` and \`grep\` don't work with arguments enclosed in quotes. Instead of \`grep "#include"\`, use \`grep #include\`. Since the tokenizer treats each word separated by whitespace as a single token, unlike bash, this shell can't treat multiple words as a single token |
| less | The \`less\` command will not behave as expected if the user doesn't press \`q\` to exit when reaching the (END) of the content |
| echo | Running \`echo $PATH\` does not correctly expand and print the environment variable values. This behavior is the same for all environment variables |


## References
THe syntax description was taken from our teacher, Mark Shroeder's guidance document