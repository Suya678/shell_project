#include "add_features.h"

#define PATH_MAX_SIZE 400
#define MAX_NUM_PATHS 40

static void parse_path_var(char *to_path, char paths[MAX_NUM_PATHS][PATH_MAX_SIZE]);
static void extract_path_from_envp(char *envp[], char paths[MAX_NUM_PATHS][PATH_MAX_SIZE]);
static void search_and_append_executable_paths(char paths[MAX_NUM_PATHS][PATH_MAX_SIZE],
                                        char spare_for_commands[MAX_ARGS][MAX_SIZE + PATH_MAX_SIZE],
                                        Command *current_pipeline, int *spare_count);

static void sig_int_handler(int sig);
static void signal_child_handler(int sig);




/**
 * @brief Resolves the command paths for each stage in the pipeline
 *
 * This function checks if the command provided in each stage of the pipeline is an absolute 
 * or relative path. If it is not, the function searches through the environment paths 
 * to resolve the command's executable and appends the correct path to the command. 
 *
 * When this function is called first, it will set the 'paths' array using a helper function.
 * Subsequent calls will not do this.The spare_for_commands array is used as a buffer to 
 * store updated versions of command arguments since the buffer pointed to by current pipeline
 * cannot accomade extra characters.
 *
 * @param job Pointer to the job containing the pipeline stages.
 * @param envp Array of environment variables used to extract the executable paths.
 */
void resolve_command_path(JOB *job, char *envp[]){

  Command *current_pipeline;
 
  static char paths[MAX_NUM_PATHS][PATH_MAX_SIZE]; /*holds all paths*/
  static char spare_for_commands[MAX_ARGS][MAX_SIZE + PATH_MAX_SIZE];
  static bool path_variables_extracted = FALSE;

  int spare_count = 0;
  if(path_variables_extracted == FALSE){
    path_variables_extracted= TRUE;
    extract_path_from_envp(envp, paths);
  }
  
  for(unsigned int i = 0; i < job->num_stages ; i++) {
    current_pipeline = &job->pipeline[i];
  
    /*this means the user provided an absolute or a relative path*/
    if(string_compare(current_pipeline->argv[0],"/",1) || string_compare(current_pipeline->argv[0],"./",2)){
        continue;
    }
    
    search_and_append_executable_paths(paths, spare_for_commands, current_pipeline, &spare_count);  

    }
  
}


/**
 * @brief Sets up the sigaction struct 
 *
 * This function creates a sigfunction structure sa. 
 * The handler attribute is assigned to the signal_child_handler function.
 * sigemptyset allows for no signal interrupts to be masked.
 * 
 * @param None
 * @return Does not return anything
 */
 void signal_child_setup(){
  struct sigaction sa;
  sa.sa_handler = signal_child_handler; //in cmd_runner.c
  sigemptyset(&sa.sa_mask);        // Initialize an empty set *i got this from chatgpt it says we need it for predictability*
  sa.sa_flags = SA_RESTART;     // The read system call will otherwise fail during some background jobs


  if (sigaction(SIGCHLD, &sa, NULL) == -1) { //SIGCHLD is child stopped or terminated
    perror("Could not install SIGCHLD handler");
    exit(EXIT_FAILURE);;
  }
  
}


/**
 * @brief Sets up signal handling for SIg INT signal 
 *
 * This function creates a sigfunction structure sa. 
 * The handler attribute is assigned to the sig_int_handler function.
 * sigemptyset allows for no signal interrupts to be masked.
 * 
 * @param None
 * @return Does not return anything
 */
void signal_int_setup(){

  struct sigaction sa;
  sa.sa_handler = sig_int_handler; 
  sigemptyset(&sa.sa_mask);        // Initialize an empty set *i got this from chatgpt it says we need it for predictability*
  sa.sa_flags = SA_RESTART;     // The read system call will otherwise fail during some background jobs


  if (sigaction(SIGINT, &sa, NULL) == -1) { //SIGCHLD is child stopped or terminated
    perror("Could not install SIGCHLD handler");
    exit(EXIT_FAILURE);;
  }


}

/**
 * @brief Helper function to search if a given pipeline command is in one of the paths in the "paths" array.
 *
 * This function searches through each path by appending the pipeline command to the each path and calling
 * stat which will return a 0 if the file exsists. If found, it replaces the pipeline's command with the appnded
 * version. If not found, it does nothing.
 *
 * @param paths Array of possible paths.
 * @param spare_for_commands Array to store updated commands with paths.
 * @param current_pipeline Pointer to the current pipeline's command.
 * @param spare_count Counter to track the number of spare commands.
 */
static void search_and_append_executable_paths(char paths[MAX_NUM_PATHS][PATH_MAX_SIZE],
                                        char spare_for_commands[MAX_ARGS][MAX_SIZE + PATH_MAX_SIZE],
                                        Command *current_pipeline, int *spare_count){
   struct stat statbuf;
   char temp[MAX_SIZE + PATH_MAX_SIZE];

   for(int j = 0; paths[j][0] != '\0'; j++) { /* '\0' as the first character indicates that there are no more paths*/
      string_copy(paths[j], temp, '\0');          
      my_str_cat(current_pipeline->argv[0],temp);
      if(stat(temp,&statbuf) == 0) {
        string_copy(temp,spare_for_commands[*spare_count], '\0');
        current_pipeline->argv[0] = spare_for_commands[(*spare_count)++];
        break;
      }
    
    }

}




/**
 * @brief Helper function to resolve command for extracting PATH environment variable from `envp` and parsing it into individual paths.
 *
 * This function earches through the environment variables array `envp` to find the `PATH` variable.
 * Once found, it extracts its value (excluding the `"PATH="` prefix) and passes it to the helper function
 * `parse_path_var` to split it into individual paths, which are stored in the `paths` array.
 *
 * @param envp array of environment variable strings.
 * @param paths array to store the parsed individual paths.
 */
static void extract_path_from_envp(char *envp[], char paths[MAX_NUM_PATHS][PATH_MAX_SIZE]) {
  char *to_path = NULL; 

  for(int i = 0; envp[i] != NULL; i++)  {
    if(string_compare(envp[i], "PATH=", 5)) {
      to_path = envp[i];
      to_path += 5;
      break;
    }
  }
  parse_path_var(to_path, paths);
}

/**
 * @brief Helper function to store each individual path in the paths array.
 *
 * It first stores the default path in the 'paths' array, then makes sure that
 * 'to_path' does not equal NULL which will indicate that the parent function did
 * not find the PATH variable. IF to_path is not NULL, it splits each individual path
 * using ':' as a delimiter and stores them in 'paths' array. It also appends a '/' at the end
 * of each path.
 *
 * @param to_path The string containg all the paths to be parsed
 * @param paths Array to store the individual parsed paths
 */
static void parse_path_var(char *to_path, char paths[MAX_NUM_PATHS][PATH_MAX_SIZE]){
  int number_of_paths = 0;
  char *default_path = "/bin";
  string_copy(default_path, paths[number_of_paths++],'\0');
  
  if(to_path == NULL){
    return;
  }
  
  while(*to_path != '\0') {
    string_copy(to_path, paths[number_of_paths],':');
    my_str_cat("/", paths[number_of_paths++]);

    while(*to_path != ':' && *to_path != '\0') {
      to_path++;
    }
    
    if(*to_path == ':'){
      to_path++;
    }  
    
  }

  paths[number_of_paths][0] = '\0'; /*indicate the end of path */
}


/**
 * @brief Terminates zombie children
 *
 * This function will check all children and 
 * while not blocking will deallocate the resources the
 * zombie is using by waiting on it. It will do this in a loop
 * until no more children are zombies.  
 *
 * @param int sig - signal that triggered the handler
 * @return Does not return anything
 */
static void signal_child_handler(int sig){
  int status;
  if(sig == SIGCHLD) { /*Redundant but otherwise compiler complains about unused parameters*/
    while(waitpid(-1, &status, WNOHANG) > 0);
  }

}



/**
 * @brief Prints a fresh prompt
 *
 * This function will check all children and 
 * while not blocking will deallocate the resources the
 * zombie is using by waiting on it. It will do this in a loop
 * until no more children are zombies.  
 *
 * @param int sig - signal that triggered the handler
 * @return Does not return anything
 */
static void sig_int_handler(int sig){
  if(sig == SIGINT) { /*Redundant but otherwise compiler complains about unused parameters*/
    print_string("\nQuantumShell$$: ");  
  }
}




bool _chdir(JOB *job){

struct stat statbuf;


if(job->num_stages > 1)
  return FALSE;


if(job->infile_path != NULL || job->infile_path != NULL)
  return FALSE;

if(job->pipeline[0].argc > 2 || job->pipeline[0].argc < 2)
  return FALSE;

if(stat(job->pipeline[0].argv[1],&statbuf) == 0) {
  return TRUE;
}  

return FALSE;



}

  



