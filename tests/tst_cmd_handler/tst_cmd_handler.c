#include <stdio.h>
#include <unistd.h>
#include "cmd_handler.h"

void test_valid_input();
void test_invalid_input();
void test_max_valid_input();
void test_multiple_invalid_inputs();
void test_string_tokenizer_1_tok();
void test_string_tokenizer_max_tokens();
void test_string_tokenizer_whitespacess(); 
void test_run_valid_command();
void test_run_invalid_command();
void test_fork_failure();


int main() {
  
  printf("TESTING CMD HANDLER MODULE\n");
  printf("Testing the get command function...\n");
  
  test_valid_input();
  printf("\n");
  test_invalid_input();
  printf("\n");
  test_max_valid_input();
  printf("\n");
  test_multiple_invalid_inputs();
  printf("\n\n\n");

  printf("TESTING STRING TOKENIZER FUNCTION\n");
  test_string_tokenizer_1_tok();
  printf("\n");
  test_string_tokenizer_max_tokens();
  printf("\n");
  test_string_tokenizer_whitespacess();
  printf("\n\n\n");


  printf("TESTING RUN COMMAND FUNCTION\n");
  printf("please preface all commands with /bin/*your command*\n");
  test_run_valid_command();
  printf("\n");
  test_run_invalid_command();
  printf("\n");
  test_fork_failure();
  printf("\n\n\n");

  return 0;
}

void print_each_token(Command *command) {
  int index = 0;  
  while(command->argv[index] != NULL) {
    printf("%s ", command->argv[index++]);
  }
  printf("\n");
}

void test_valid_input() {
  Command command;
 
    printf("CASE 1: Testing if valid input is accepted.\n");
    printf("Please enter a string with less than 256 characters:\n");

    get_command(&command);
    
    printf("You entered(each token): ");
    print_each_token(&command);
}


void test_invalid_input() {
   Command command;
    printf("CASE 2: Testing if invalid input is rejected.\n");
    printf("Please enter a string with more than 256 characters, then enter a valid string:\n");
    get_command(&command);

    printf("You entered(each token): ");
    print_each_token(&command);
}

void test_max_valid_input() {
  Command command;

    printf("CASE 3: Testing maximum valid input length.\n");
    printf("Please enter a string with exactly 256 characters:\n The string should be accepted without any errors \n");
get_command(&command);

    printf("You entered(each token): ");
    print_each_token(&command);
}

void test_multiple_invalid_inputs() {
    Command command;

    printf("CASE 4: Testing rejection of multiple invalid inputs.\n");
    printf("Please enter strings longer than 256 and then enter string shorter than that to end this test case:\n");
    get_command(&command);

    printf("You entered(each token): ");
    print_each_token(&command);
}

void test_string_tokenizer_1_tok() {
    Command command;

    printf("CASE 1: Testing with just one tokens.\n");
    printf("Please enter only one token:\n");
    get_command(&command);

    printf("You entered(each token): ");
    print_each_token(&command);
}


void test_string_tokenizer_max_tokens() {
    Command command;

    printf("CASE 2: Testing with max  tokens.\n");
    printf("Please enter a string containg 128 spaces, containing 128 characters followed by the whitespaces:\n");
    get_command(&command);

    printf("You entered(each token): ");
    print_each_token(&command);
}

void test_string_tokenizer_whitespacess() {
    Command command;

    printf("CASE 3: Testing with multiple leading white spaces before a character.\n");
    printf("Please enter a string with multiple white spaces before the first character and between other tokens:\n");
    get_command(&command);

    printf("You entered(each token): ");
    print_each_token(&command);
}

void test_run_valid_command(){
  Command command;

  printf("CASE 1: Testing the execution of a valid command.\n");
  printf("Please enter a valid command.\n");
  get_command(&command);
  run_command(&command);
  printf("Were the results as expected? Hopefully...\n");
}

void test_run_invalid_command(){
  Command command;

  printf("CASE 2: Testing the execution of an invalid command.\n");
  printf("Please enter an invalid command.\n");
  get_command(&command);
  run_command(&command);
  printf("Expected results: ERROR: COMMAND NOT FOUND OR COULD NOT BE EXECUTED \n");
  printf("INVALID COMMAND WAS: ");
  print_each_token(&command);
  printf("\n");
}

void test_fork_failure(){
  Command command;

  printf("CASE 3: Testing the creation of the child process.\n");
  printf("Please enter a valid command\n");
  get_command(&command);
  run_command(&command);
  printf("Expected results on fail: cannot create process\n");
  printf("Otherwise fork created successfully and output is as expected\n");
}


 






