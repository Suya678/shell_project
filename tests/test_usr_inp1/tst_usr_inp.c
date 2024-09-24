#include <stdio.h>
#include <unistd.h>
#include "usr_input.h"

void test_valid_input();
void test_invalid_input();
void test_max_valid_input();
void test_multiple_invalid_inputs();
void test_print_string();
void test_string_compare();



int main() {
  
  printf("TESTING READ_USR_INP MODULE\n");
  printf("Testing the read_usr_inp function...\n");
  
  test_valid_input();
  test_invalid_input();
  test_max_valid_input();
  test_multiple_invalid_inputs();

  printf("Testing print string function\n\n");
  test_print_string();
  
  printf("Testing the string compare function...\n\n");
  test_string_compare();

  return 0;
}

void test_string_compare(){
  char *compare_tst_5[] = {"VPQUBLULTSAKCTBNEQZBARCGPYXVZMYVPXVGZJKJSQMYELHEDWSUCHMTNHQUUSKZRDQPKAZWRMHQUBLFDSJNJEKAMUUZLTWEVNBK\0",
                     "VPQUBLULTSAKCTBNEQZBARCGPYXVZMYVPXVGZJKJSQMYELHEDWSUCHMTNHQUUSKZRDQPKAZWRMHQUBLFDSJNJEKAMUUZLTWEVNBK\0"};
  
  bool are_equal = FALSE;


  printf("TEST CASE 1: Two strings are equal, String 1: Hello, String 2: Hello \n");
  printf( "Expected: true\n");
  are_equal = string_compare("HELLO\0","HELLO\0", -1);
  if(are_equal) {
    printf( "Actual: true\nTest Passed\n\n");
  } else {
    printf( "Actual: false\nTest Failed\n\n");
  }

  printf("TEST CASE 2: Two strings are not equall, String 1: HELLO, String 2: WORKS \n");
  printf( "Expected: false\n");
  are_equal = string_compare("HELLO\0","WORKS\0", -1);
  if(are_equal) {
    printf( "Actual: true\nTest Failedn\n");
  } else {
    printf( "Actual: false\nTest Passed\n\n");
  }

  printf("TEST CASE 3: Only compares the first three characters and fails,\nString 1: DHDDD, String 2: DHCDD");
  printf( "Expected: false\n");
  are_equal = string_compare("DHDDD", "DHCDD", 3);
  if(are_equal) {
    printf( "Actual: true\nTest Failed\n");
  } else {
    printf( "Actual: false\nTest Passed\n\n");
  }


  printf("TEST CASE 4: Only compares the first three characters and passes, String 1: SHOP, String 2: SHOC \n");
  printf( "Expected: true\n");
  are_equal = string_compare("SHOP", "SHOC", 3);
  if(are_equal) {
    printf( "Actual: true\nTest Passed\n");
  } else {
    printf( "Actual: false\nTest Failed\n\n");
  }


  printf("TEST CASE 5: Two equal long strings\nString 1: %s\n\nString 2: %s\n\n", compare_tst_5[1], compare_tst_5[0]);
  printf( "Expected: true\n");
  are_equal = string_compare(compare_tst_5[0], compare_tst_5[1],-1);
  if(are_equal) {
    printf( "Actual: true\nTest Passed\n");
  } else {
    printf( "Actual: false\nTest Failed\n\n");
  }
  
  

}




void test_valid_input() {
    char array[256];

    printf("CASE 1: Testing if valid input is accepted.\n");
    printf("Please enter a string with less than 256 characters:\n");

    read_usr_inp(array);
    
    printf("You entered: %s\n", array);
}


void test_invalid_input() {
    char array[256];

    printf("CASE 2: Testing if invalid input is rejected.\n");
    printf("Please enter a string with more than 256 characters, then enter a valid string:\n");

    read_usr_inp(array);
    
   printf("You entered: %s\n", array);
}

void test_max_valid_input() {
    char array[257]; 

    printf("CASE 3: Testing maximum valid input length.\n");
    printf("Please enter a string with exactly 256 characters:\n The string should be accepted without any errors \n");

    read_usr_inp(array);

    printf("You entered: %s\n", array);

}

void test_multiple_invalid_inputs() {
    char array[256];

    printf("CASE 4: Testing rejection of multiple invalid inputs.\n");
    printf("Please enter strings longer than 256 and then enter string shorter than that to end this test case:\n");

    read_usr_inp(array);

    printf("You entered: %s\n", array);
}







void test_print_string() {

  char str1[] = "1\n\0";
  char str2[] = "Hello\n\0";
  char str3[] = "WORKS sadasdOOO\n\0";
  char str4[] = "HEllo world hello world\n\0";
  char str5[] =  "Hello\n\0World!\0";
  
  write(FD_STD_OUT, "TEST CASE 1: Prints with just one character plus newline\n", 58);
  write(FD_STD_OUT, "Expected: ", 10);
  write(FD_STD_OUT, str1, 2);
  write(FD_STD_OUT, "\nActual: ", 9);
  print_string(str1);
  write(FD_STD_OUT, "\n", 1);
  
  write(FD_STD_OUT, "TEST CASE 2: Prints a string with one word\n", 43);
  write(FD_STD_OUT, "Expected: ", 10);
  write(FD_STD_OUT, str2, 7);
  write(FD_STD_OUT, "\nActual: ", 9);
  print_string(str2);
  write(FD_STD_OUT, "\n", 1);
   
  write(FD_STD_OUT, "TEST CASE 3: Prints a string with two words\n", 44);
  write(FD_STD_OUT, "Expected: ", 10);
  write(FD_STD_OUT, str3, 17);
  write(FD_STD_OUT, "\nActual: ", 9);
  print_string(str3);
  write(FD_STD_OUT, "\n", 1);
    

  write(FD_STD_OUT, "TEST CASE 4: Prints a string with multiple words\n", 49);
  write(FD_STD_OUT, "Expected: ", 10);
  write(FD_STD_OUT, str4, 24);
  write(FD_STD_OUT, "\nActual: ", 9);
  print_string(str4);
  write(FD_STD_OUT, "\n", 1);

  write(FD_STD_OUT, "TEST CASE 5: Prints a string with multiple null characters\n", 60);
  write(FD_STD_OUT, "Expected: ", 10);
  write(FD_STD_OUT, str5, 6);
  write(FD_STD_OUT, "\nActual: ", 9);
  print_string(str5);
  write(FD_STD_OUT, "\n", 1);


}




