
#include "parser.h"

static void flush_std_input_buffer();
static void string_tokenizer(char *to_decompose, char *tokens[], unsigned int *num_tokens);
static bool validate_input_and_null_terminate(USR_INP *usr_inp, size_t count);
static void read_pipeline(JOB *job, bool *valid_input,  unsigned int *token_counter);
static void handle_pipe(JOB *job, bool *valid_input, unsigned int *token_counter);
static void handle_background_symbol(JOB *job, bool *valid_input, unsigned int *token_counter);
static void handle_input_redirection(JOB *job, bool *valid_input, unsigned int *token_counter);
static void handle_output_redirection(JOB *job, bool *valid_input, unsigned int *token_counter);
static bool is_special_symbol(char *str);

/**
 * @brief Reads and processes user input.
 *
 * Reads user input from stdin, ensuring it's within 256 characters.
 * If input exceeds the limit or is empty, re-prompts the user. It exits if the user pressed
 * CTRL+D to indicate end-of-file or read failed for non interrupt reasons.
 * Input is tokenized via a helper function.
 * 
 * @param usr_inp Pointer to the USR_INP structure holding the input buffer
 * 
 * @return Does not return anythin but stores the processed user input and tokens in the usr_inp structure.
 */

void get_usr_input(USR_INP *usr_inp) {
  size_t count = 0;
  char shell_prompt[] = "QuantumShell$$: ";
  bool valid_input = FALSE;
  
  while(valid_input == FALSE) {
    
    print_string(shell_prompt);
    count = read(FD_STD_INP, usr_inp->usr_input, MAX_SIZE);

    if (count < 1) {
      handle_read_error(count);
    }
    valid_input = validate_input_and_null_terminate(usr_inp,count);
  }
  
  string_tokenizer(usr_inp->usr_input,usr_inp->argv,&(usr_inp->num_tokens));

}


/**
 * @brief Validates user input and null-terminates it.
 *
 * Handles input validation for length and checks if the user pressed CTRL+D.
 * If the input exceeds 256 characters, the buffer is flushed and an error is printed.
 * Null-terminates the input and checks if it's not empty otherwise.
 *
 * @return Returns TRUE if valid, FALSE otherwise.
 */
static bool validate_input_and_null_terminate(USR_INP *usr_inp, size_t count) {
    char error_msg[] = "Error: The input was longer than 256 characters\n";

    if (usr_inp->usr_input[count - 1] != '\n' && count == 256) { //If input is less than 256 that means user pressed CTRL D which is valid
        print_string(error_msg);
        flush_std_input_buffer();
        return FALSE;
    }


    // Null-terminate the input string
    if (usr_inp->usr_input[count - 1] != '\n') { // Last character might not be '/n' if the user pressed CTRL D
        usr_inp->usr_input[count] = '\0';
        print_string("\n");                    // Since the user didnt enter a newline
    } else {
        usr_inp->usr_input[count - 1] = '\0';
    }


    // Check if the input was not an empty string
    return !is_string_empty(usr_inp->usr_input);
}





/**
 * @brief Helper function to read_usr_input for flushing the standard input buffer.
 *
 * This function clears any remaining data in the standard input buffer by
 * reading and discarding characters until a newline is encountered.
 *
 * @return This function does not return any value.
 */
static void flush_std_input_buffer() {
  
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
 * @param to_decompose input string to be tokenized
 * @param tokens[] array of pointers to characters within to_decompose
 * @param num_of_tokens pointer to an int where the number of tokens found is stored
 *
 * @return This function does not return any value.
 */
static void string_tokenizer(char *to_decompose, char *tokens[], unsigned int *num_tokens){
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




/**
 * @brief Validates that the user's input is in the correct syntax and initializes the job structure
 * 
 * The function verifies whether the first token is a special symbol. 
 * If it is, it return early with FALSE as the first symbol should start with a non special 
 * symbol. If the first symbol is not a special one, then it calls read_pipeline to parse 
 * the input and update the job structure
 * 
 * @param *job pointer to the JOB structure containing user input, pipeline and other info.
 * 
 * @return Returns TRUE if the input is valid; otherwise, FALSE.
 */
bool validate_and_parse_job(JOB *job) {
  bool valid_input  = TRUE;
  job->infile_path = NULL;            /* NULL for no output redirection     */
  job->outfile_path = NULL;           /* NULL for no input redirection      */
  job->background = FALSE;
  job->num_stages = 0;
  unsigned int token_counter = 0;
  
  /*We are guarnteed at least one token and it must start with an non special symbol*/
  if(is_special_symbol(job->usr_input.argv[token_counter])){
    return FALSE;
  }
  read_pipeline(job, &valid_input, &token_counter);

  return valid_input;

}


/**
 * @brief Reads a command pipeline from user input and populates the current stage.
 * 
 * The function iterates through user input, collecting token until a special
 * symbol or NULL is encountered. It then checks for special symbols to handle 
 * redirection and background execution.
 * 
 * @param *job pointer to the JOB structure with the pipeline and user input.
 * @param *token_counter pointer to an unsigned integer tracking the current token position.
 * @param *valid_input pointer to a boolean indicating whether the input is valid.
 * 
 * @return This function does not return any value but modifies the passed in pointers
 */

static void read_pipeline(JOB *job, bool *valid_input, unsigned int *token_counter){

  unsigned int num_arguments = 0;
  Command *current_pipeline  = &job->pipeline[job->num_stages];

  (job->num_stages)++;

  // Keep adding to the current pipeline until we encounter a NULL or special symbol
  while(job->usr_input.argv[*token_counter] != NULL &&
      is_special_symbol(job->usr_input.argv[*token_counter]) == FALSE) {
      current_pipeline->argv[num_arguments++] = job->usr_input.argv[*token_counter];
      (*token_counter)++;

  }  
  current_pipeline->argv[num_arguments] = NULL;
  current_pipeline->argc = num_arguments; 


  if (job->usr_input.argv[*token_counter] != NULL) {
    switch (*job->usr_input.argv[*token_counter]) {
    case '|':
      handle_pipe(job,valid_input,token_counter);
      break;
    case '<':
      handle_input_redirection(job,valid_input,token_counter);
      break;
    case '>':
      handle_output_redirection(job,valid_input,token_counter);
      break;
    case '&':
      handle_background_symbol(job,valid_input,token_counter);
      break;
    }
    
  }

}


/**
 * @brief Handles the detection of a pipe symbol (`|`) in user input.
 * 
 * The function increments the token counter and checks if the next token is valid.
 * The next token is valid if it is not NULL and does not represent a special symbol. 
 * If valid, it recursively calls read_pipeline to continue parsing the command stages in the pipeline.
 * If the token is invalid, it marks the input as invalid.
 * 
 * @param *job pointer to the JOB structure containing the command pipeline.
 * @param *valid_input pointer to a boolean indicating whether the input is valid.
 * @param *token_counter pointer to an unsigned integer tracking the current token position.
 * 
 * @return This function does not return any value but will modified the passed in values
 */

static void handle_pipe(JOB *job, bool *valid_input, unsigned int *token_counter){
  (*token_counter)++;

  if(job->usr_input.argv[*token_counter] == NULL ||
    is_special_symbol(job->usr_input.argv[*token_counter]) == TRUE) {
    *valid_input = FALSE;
  } else {
    read_pipeline(job,valid_input,token_counter);
  }

}


/**
 * @brief Handles the detection of the background execution symbol (`&`).
 * 
 * The function sets the background flag in the job structure and increments the token 
 * counter. If additional tokens are present after `&`, it marks the input as invalid.
 * 
 * @param *job pointer to the JOB structure containing the background flag.
 * @param *valid_input pointer to a boolean indicating whether the input is valid.
 * @param *token_counter pointer to an unsigned integer tracking the current token position.
 * 
 * @return This function does not return any value but may modify valid input parameter
 */

static void handle_background_symbol(JOB *job, bool *valid_input, unsigned int *token_counter){
  job->background = TRUE;
  (*token_counter)++; //Consume the current '&' token

  // There cannot be ay more tokens after '&'
  if (job->usr_input.argv[*token_counter] != NULL){
    *valid_input = FALSE;
  }
}

/**
 * @brief Handles output redirection from user input.
 * 
 * The function consumes the output redirection symbol (`>`) and checks if the 
 * next token is a valid path( ie not a NULL or a special symbol.
 * If valid, it updates the job structure. It also verifies that no tokens
 * other than "&" are next.
 *  
 * @param *job pointer to the JOB structure containing the output file path.
 * @param *valid_input pointer to a boolean indicating whether the input is valid.
 * @param *token_counter pointer to an unsigned integer tracking the current token position.
 * 
 * @return This function does not return any value but will modify the passed in parameters.
 */

static void handle_output_redirection(JOB *job, bool *valid_input, unsigned int *token_counter){
  
  (*token_counter)++; // Consume the '<' token

  // Check if the user has provided a infile path
  if(job->usr_input.argv[*token_counter] == NULL ||
     is_special_symbol(job->usr_input.argv[*token_counter]) == TRUE) {
      *valid_input = FALSE;
      return;
  } 
  
  job->outfile_path = job->usr_input.argv[*token_counter];

  (*token_counter)++;
  
  //Check next token. It cannot be the beginning of a new pipeline or
  //any special symbol other than '&'
  if(job->usr_input.argv[*token_counter] != NULL) {
    
    if(string_compare(job->usr_input.argv[*token_counter], "&", 0)) {
      handle_background_symbol(job,valid_input,token_counter);
    } else {
      *valid_input = FALSE;
    }
  }

}

/**
 * @brief Handles input redirection from user input.
 * 
 * The function consumes the input redirection symbol (`<`) checks if the 
 * next token is a valid path(ie not a NULL or a special symbol).
 * It updates the job structure and ensures that the next token 
 * does not start a new pipeline or contain special symbols, except for '&' or '<'.
 * 
 * @param *job pointer to the JOB structure containing the input file path.
 * @param *valid_input pointer to a boolean indicating whether the input is valid.
 * @param *token_counter pointer to an unsigned integer tracking the current token position.
 * 
 * @return This function does not return any value.
 */

static  void handle_input_redirection(JOB *job, bool *valid_input, unsigned int *token_counter){

  // Consumer the > token
  (*token_counter)++;

  //Make sure next token is not NULL or a special symbol as we need an input path
  if(job->usr_input.argv[*token_counter] == NULL || is_special_symbol(job->usr_input.argv[*token_counter]) == TRUE) {
    *valid_input = FALSE;
    return;
  }
  
  job->infile_path = job->usr_input.argv[*token_counter];
  
  (*token_counter)++;
  
  //Check the next token
  if(job->usr_input.argv[*token_counter] != NULL) {
    
    if(string_compare(job->usr_input.argv[*token_counter],"&",0)) {
      handle_background_symbol(job,valid_input,token_counter);
    } else if(string_compare(job->usr_input.argv[*token_counter],">",0)){
      handle_output_redirection(job,valid_input,token_counter);
    } else {
      *valid_input = FALSE; // Next token cant be the beginning of a new pipeline
    }
    
  }

}









/**
 * @brief Checks if the given string matches a special symbol.
 *
 * These symbols are defined as special characters used in the shell 
 * such as '&', '>', '<', or '|'. This function compares the input string 
 * to these symbols and returns TRUE if a match is found.
 *
 * @param str[] The string to be checked.
 * @return This function returns TRUE if the string is a terminal symbol, otherwise FALSE.
 */
static bool is_special_symbol(char *str){

   if(string_compare(str,"&", 0)  ||
    string_compare(str,">", 0)   ||
    string_compare(str,"<", 0)   ||
    string_compare(str,"|", 0)  ) {
    return TRUE;
  }

  return FALSE;

}

