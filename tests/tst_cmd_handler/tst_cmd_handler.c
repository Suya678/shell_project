#include <stdio.h>
#include <unistd.h>
#include "cmd_handler.h"

void test_valid_input();
void test_invalid_input();
void test_max_valid_input();
void test_multiple_invalid_inputs();



int main() {
  
  printf("TESTING CMD HANDLER MODULE\n");
  printf("Testing the get command function...\n");
  
  test_valid_input();
  test_invalid_input();
  test_max_valid_input();
  test_multiple_invalid_inputs();

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



 





