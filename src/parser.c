#include "parser.h"
#include "stdio.h"


/**
 * @brief The funcition reads user input
 *
 * This function will read user input from the standard input buffer.
 * If the user enters more than 256 characters, it will print an error
 * message to the standard output and re-prompt the user. The user
 * will also be re-prompted if they enter just a new line. The input string will
 * be null terminated and will be at most 256 characters including the null terminator.
 * It will be stored in the command strucutre. The function will also tokenize the
 * the string via a helper function. It will also set the background processing flag
 * via a helper fucniton
 *
 * @param Command *command structure containing the buffer to holding users input 
 *                 The function assumes that the inpu buffer has a length of 256 characters.
 *
 * @return Does not return anything direcly but stores the user input in the user_input
 * array in the command structure.
 */
void get_usr_input(USR_INP *usr_inp) {
  ssize_t count = 0;
  char shell_prompt[] = "jdshell$$: ";
  char error_msg[] ="Error: The input was longer than 256 characters\n";
  bool valid_input = FALSE;
  
  while(valid_input == FALSE) {
    
    print_string(shell_prompt);
    count = read(FD_STD_INP, usr_inp->usr_input, MAX_SIZE);

    /*Exit if read failed*/
    if (count == -1) {
      write(FD_STD_ERR, "Error reading input in read_usr_inp function\n", 46);
      _exit(1); 
    }
    
    
    if(usr_inp->usr_input[count -1] != '\n') {         /*User entered more than 256 characters*/
      print_string(error_msg);
      flush_std_input_buffer();
    }else if(!is_string_empty(usr_inp->usr_input)) {    /*Check if user did not enter an empty line*/
      valid_input = TRUE;
    }
    
  }
  
  usr_inp->usr_input[count - 1] = '\0';

  string_tokenizer(usr_inp->usr_input,usr_inp->argv,&(usr_inp->num_tokens));
  

}


/**
 * @brief Helper function to read_usr_input for flushing the standard input buffer.
 *
 * This function clears any remaining data in the standard input buffer by
 * reading and discarding characters until a newline is encountered.
 *
 * @return This function does not return any value.
 */
void flush_std_input_buffer(){
  
  size_t buff_size = 100;
  char temp_buff[buff_size];
  bool input_flushed = FALSE;
  ssize_t count = 0;

  while(input_flushed == FALSE) {  
    count = read(FD_STD_INP, temp_buff, buff_size);
    
    /*Exit if read failed*/
    if (count == -1) {
      write(FD_STD_ERR, "Error reading input in read_usr_inp function\n", 46);
      _exit(1);
    }

    if(temp_buff[count -1] == '\n') {
      input_flushed = TRUE;
    }
  }
  
}





/**
 * @brief Flushes the contents of a string buffer.
 *
 * This function clears all characters in a given string buffer by setting 
 * every character to the null terminator.
 * @param str[] array of characters to be flushed.
 * @return This function does not return any value.
 */
void flush_input_string(char str[]){

  for(int i = 0; str[i] != '\0'; i++) {
    str[0] = '\0';
  }
}





/**
 * @brief Checks if the given string is empty.
 *
 * An empty string is defined as one with only consecutive whispace terminated by \n.
 * For ex : "      \n" is empty, so is "            \n"
 * The function assumes the string ends eventually with a newline
 * @param string[] to be checked.
 * @return This function returns TRUE if the string is empty, otherwise false.
 */
bool is_string_empty(char string[]) {

  char *str = string;

  while (*str != '\n') {

    if(*str != ' ') {
      return FALSE;
    }
    str++;
  }
  return TRUE;
}



/**
 * @brief decomposes a commandline string into the separate words/tokens removing the
 * whitespace. It stores the tokens in an array and tracks how many tokens were found.
 * 
 * curr is initialized to pint to the start of the string to_decompose and is iterated until
 * '\0', looking for words. It will also skip over leading whitespaces in the string. If curr reaches 
 * the null terminator it breaks out indicating no more tokens.
 * The curr position after skipping whitespace is saved in the tokens array as the start of a new token.
 * This is the pointer to the first character in the word.
 * The second inner while loop finds where the current word ends, a '\0' then ends the token.
 * Curr is then incremented to start scanning the next token.
 * Finally once all tokens have been processed tokens[*num_tokens] is set to NULL to finalize the 
 * end of the array. The function will not allow the number of tokens to exceed the MAX_SIZE
 *
 * @param *to_decompose input string to be tokenized
 * @param *tokens[] array of pointers to characters within to_decompose
 * @param *num_of_tokens pointer to an int where the number of tokens found is stored
 *
 * @return This function does not return any value.
 */
void string_tokenizer(char *to_decompose, char *tokens[], unsigned int *num_tokens){
  char *curr = to_decompose;
  *num_tokens = 0;
  
  while(*curr != '\0'){
    
    while(*curr == ' ' || *curr == '\t' || *curr == '\n'){
      curr++;
    }
    
    if(*curr == '\0'){
      break;
    }
    

    tokens[*num_tokens] = curr; /*stores the start of the word*/
    
    while(*curr != ' ' && *curr != '\t' && *curr != '\n' && *curr != '\0'){
      curr++;                   /*looking for the end of the word*/
    }
    
    if(*curr != '\0'){
      *curr = '\0';
      curr++;
    }
    (*num_tokens)++;
    if(*num_tokens >= MAX_ARGS){
      break;
    }
  }
  tokens[*num_tokens] = NULL; 
  
}




bool validate_and_parse_job(JOB *job) {
  
  bool valid_input = TRUE;
  job->infile_path = NULL;        /* NULL for no output redirection     */
  job->outfile_path = NULL;           /* NULL for no input redirection      */
  job->background = FALSE;
  int token_counter = 0;
  
  printf("%d\n", job->usr_input.num_tokens);

  /*We are guarnteed at least one token and it must start with an argumnet*/
  if(string_compare(job->usr_input.argv[token_counter],"&", 0)  ||
    string_compare(job->usr_input.argv[token_counter],">", 0)   ||
    string_compare(job->usr_input.argv[token_counter],"<", 0)   ||
    string_compare(job->usr_input.argv[token_counter],"|", 0)  ) {
    printf("here\n");
    valid_input = FALSE;
  }
  state_reading_argument(job, &valid_input, &token_counter);

  return valid_input;

}



void state_reading_argument(JOB *job, bool *valid_input, int *token_counter){

  unsigned int num_arguments = 0;
  Command *current_pipeline  = &job->pipeline[(job->num_stages)++];

  current_pipeline->argv[num_arguments++] = job->usr_input.argv[*token_counter];

  (*token_counter)++;



 
    if(job->usr_input.argv[*token_counter] == NULL) {
  
    }else if (string_compare(job->usr_input.argv[*token_counter],"|", 0))  {



    } else if (string_compare(job->usr_input.argv[*token_counter],">", 0)) {


    } else if (string_compare(job->usr_input.argv[*token_counter],"<", 0)) {

      
    }


  


/*
  printf("%s \n", current_pipeline->argv[num_arguments]);
*/

}




void state_encountered_pipe(JOB *job, bool *valid_input){


  
}

void state_encountered_ampersand_sign(JOB *job, bool *valid_input){


  
}


void state_encountered_outfile_sign(JOB *job, bool *valid_input){


  
}

void state_encountered_infile_sign(JOB *job, bool *valid_input){


  
}


void input_incorrect(JOB *job, bool *valid_input){


  
}



void state_input_valid(JOB *job, bool *valid_input){

*valid_input = FALSE;

  
}




