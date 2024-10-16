# Final Test

## Known bugs and limitations
## Tables created using https://ozh.github.io/ascii-tables/ and https://htmlmarkdown.com/html-table-to-markdown/

## Known Issues and Limitations
|     |     |
| --- | --- |
| Quotes (' ' / " ") | Programs like \`awk\` and \`grep\` don't work with arguments enclosed in quotes. Instead of \`grep "#include"\`, use \`grep #include\`. Since the tokenizer treats each word separated by whitespace as a single token, unlike bash, this shell can't treat multiple words as a single token |
| Environment  variable expansion | The shell does not support environment variable expansion. For example,  \`echo $PATH\`  will not expand "PATH". |

## Test Cases

### Valid Input Cases

| Test Case | Command | Expected Behaviour | Actual | Result |
| --- | --- | --- | --- | --- |
| One Stage Pipeline | ls  | Lists the contents of the current directory | Same as expected | Pass |
| Two-stage Pipeline | cat headers/cmd\_runner.h \| grep #include | Filters lines containing '#include' | Same as expected | Pass |
| Three stage Pipeline | ls src \| grep .c \| sort | Lists, filters, and sorts files ending with '.c'. | Same as expected | Pass |
| Output Redirection | ls > out.txt | Redirects the output of ls to "output.txt" | Same as expected | Pass |
| Input Redirection | grep #include < headers/cmd\_runner.h | Filters lines containing '#include' in "cmd\_runner.h" | Same as expected | Pass |
| Output Redirection with a multi Pipeline | ls \| sort \| wc > out.txt | List the files in the current directory, sort them, count the number of words, and outputs to "out.txt" | Same as expected| Pass |
| Input Redirection with a multi pipeline | grep #include \| sort < headers/cmd\_runner.h | Filters lines containing '#include' in "cmd\_runner.h", and sorts the output | Same as expected | Pass |
| Background execution | sleep 10 & | The shell should return immediately compared to running: sleep 10 | Same as expected| Pass |
| Input redirection and output redirection with multiple pipeline | grep #include \| sort \| uniq \| awk {print} < headers/cmd\_runner.h > out.txt | Filters lines containing "#include" in the infile, sorts them, find the uniq values and then just outputs them to the the output file | Same as expected | Pass |


### Rejecting Invalid Input
| Test Case | Command | Expected Behaviour | Actual | Result |
| --- | --- | --- | --- | --- |
| Input longer than 256 character | Just enter a string longer than 256 characters | Displays an error | Same as expected | Pass |
| Begins with special symbol | enter: '&', '<', '>' or '\|' ex: \| ls | Display an error | Same as expected | Pass |
| Missing Input File | 'ls <' | Displays an error | Same as expected | Pass |
| Missing Output File | 'ls >' | Displays an error | Same as expected | Pass |
| Input File Provided, Output File Missing | 'ls < inp.txt > | Displays an error | Same as expected | Pass |
| Extra token after background | sleep 10 & ls | Displays an error | Same as expected| Pass |  
| Multi pipeline but missing command after a \| symbol | ex: "ls \|", "cat t.txt \| sort \|" or "cat t.txt \| sort \| unq \|" | Displays an error | Same as expected | Pass |  
| Multi pipeline with a missing output file | ls \| sort \| grep headers > | Displays an error | Same as expected |   Pass  |
| Multi pipeline with a missing input file | grep #include \| sort < | Displays an error | Same as expected |  Pass   |

### Change Directory and exit
|                  Test Case                   |      Command      |              Expected Behaviour               |      Actual       | Result |
|----------------------------------------------|-------------------|-----------------------------------------------|-------------------|--------|
| cd: change to parent directory               | cd ..             | Changes the working directory to parent       |  Same as expected | Pass   |
| cd: change to the given absolute path            | cd /usr/local     | Changes the working directory to `/usr/bin` | Same as expected  | Pass   |
| cd: change to the given relative path            | cd ./headers      | Changes the working directory to `./headers`  | Same as expected  | Pass   |
| cd: change to the non-existent path             | cd ./random       | Displays an error message                     | Same as expected  | Pass   |
| cd: change to a the directory without permission | in home: cd admin | Displays an error message  | Same as expected | Pass |
| exit:exits the shell      | exit   | Exits the shell        | Same as expected   | Pass    |

### SIGINT(Ctrl C) and CTRL D behavior
| Test Case | Command | Expected Behaviour | Actual | Result |
| --- | --- | --- | --- | --- |
| Pressing Ctrl C at an empty prompt | At the prompt, before typing any input press ctrl c | Shows a new prompt at a new line | Same as expected | Pass |
| Pressing Ctrl C during the running of a process will terminate the process but not the shell | Run \`sleep 40', then Ctrl C | Terminates sleep, and prints a new prompt | Same as expected | Pass |
| Pressing Ctrl C after typing in some valid input before | Type \`ls -l\`, then pressing Ctrl+C\` | 'ls -l' will be discarded, and the user will be re-prompted | Same as expected | Pass |
| Pressing Ctrl D at the prompt will exit the shell | Press Ctrl D at an empty prompt|  Shell will exit | Same as expected | Pass |     |
| Pressing Ctrl+D after typing input | ex: 'ls -l' then ctrl d | Should treat ls -l as the input and execute it | Same as expected | Pass |



### Executing commands without specifying the path
| Test Case | Command | Expected Behaviour | Actual | Result |
| --- | --- | --- | --- | --- |
| One stage pipeline without a path | 'ls' | ls is executed | Same as expected | Pass |
| Multi-stage pipeline without a command | ' ls \| sort \| wc' | ls sends its output to sort which sends it to wc who outputs it | Same as expected | Pass |
| Multi pipeline with providing a path for some commands and not for some | 'ls \| /bin/sort \| /bin/wc' | ls sends its output to sort which sends it to wc who outputs it | Same as expected | Pass |

## Proper Background Processing
Here, proper background processing refers to not having zombie/defunct processes when a particular process is ran in the background using '&'.

#### First we create two terminals
- One for running the command, which will run under our shell
- Second  one for running ps u to test if the process becomes a zombie, will be run under Bash.

The shell's background processing is correct if after the background process finishes execution, it does not become a zombie and is removed the process table in the ps u command. 

## In the first terminal
```
//First run a background operations in the first terminal
QuantumShell$$: sleep 20 &

//Then, before 20 seconds run another command ls
QuantumShell$$: ls
README.md  build  final_tst.md  headers  makefile  src  tests  week-3-4
```
## In the second terminal
```
##Just after executing sleep 20, we do this in the second terminal

dsuya637@dsuya637:~$ ps u
dsuya637  294107  0.0  0.0   2792  1016 pts/17   S+   18:19   0:00 /bin/sleep 20

//After waiting for 20 we executee
dsuya637@dsuya637:~$ ps u
```
The sleep process is no longer on the table, therefore, background processing works.

