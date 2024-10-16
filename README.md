# Quantum Shell - A basic shell by Juan and Depanshu
Quantum Shell is a very basic shell made in C. It has the following functionalities:
- N-stage pipelining: Supports chaining multiple commands using pipes (|)
- I/O redirection: Supports Input(<) and Output(>) redirection
- Command search pathways:  Searches system paths for commands (e.g., ls -l works), but arguments like file paths still need to be fully specified (e.g., ls /path/to/some_file)
- Built in cd command: Allows changing of directories
- Basic Signal handling: Ctrl C is ignored for the current shell process. SIGCHLD for proper background process and cleanup.
 
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
| Environment  variable expansion | The shell does not support environment variable expansion. For example,  \`echo $PATH\`  will not expand "PATH". |


## References
THe syntax description was taken from our teacher, Mark Shroeder's guidance document