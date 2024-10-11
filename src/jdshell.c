
#include <unistd.h>
#include <fcntl.h>
#include "parser.h"
#include "cmd_runner.h"
#include "our_string.h"
#include <stdio.h>
#include <sys/stat.h>

#define PATH_MAX_SIZE 400
#define MAX_NUM_PATHS 40


bool check_exit(JOB *job);
bool _chdir(JOB *job);

void parse_path_var(char *to_path, char paths[MAX_NUM_PATHS][PATH_MAX_SIZE]);
void extract_path_from_envp(char *envp[], char paths[MAX_NUM_PATHS][PATH_MAX_SIZE]);
void setups_command_paths(char paths[MAX_NUM_PATHS][PATH_MAX_SIZE], char *spare[]);
void resolve_command_path(JOB *job, char spare_for_commands[MAX_ARGS][MAX_SIZE + PATH_MAX_SIZE], char paths[MAX_NUM_PATHS][PATH_MAX_SIZE]);

int main(char argc, char *argv[], char *envp[]) {
  JOB job;
  bool is_job_valid;
  char paths[MAX_NUM_PATHS][PATH_MAX_SIZE];
  char spare_for_commands[MAX_ARGS][MAX_SIZE + PATH_MAX_SIZE];  

  extract_path_from_envp(envp, paths);


  
  get_usr_input(&job.usr_input);
  validate_and_parse_job(&job);
  resolve_command_path(&job, spare_for_commands, paths);
  
  for(int i = 0; i < job.num_stages; i++)
    printf("%s \n", job.pipeline[i].argv[0]);



/*
  while(1) {
    is_job_valid = validate_and_parse_job(&job);
    if(is_job_valid){
      if(string_compare("exit", job.pipeline[0].argv[0], 0)) break;
      run_job(&job, NULL);
    }
    get_usr_input(&job.usr_input);
  }
*/
  return 0;
}


/**
 * @brief Extracts the PATH environment variable from `envp` and parses it into individual paths.
 *
 * This function earches through the environment variables array `envp` to find the `PATH` variable.
 * Once found, it extracts its value (excluding the `"PATH="` prefix) and passes it to the helper function
 * `parse_path_var` to split it into individual paths, which are stored in the `paths` array.
 *
 * @param envp array of environment variable strings.
 * @param paths array to store the parsed individual paths.
 */

void extract_path_from_envp(char *envp[], char paths[MAX_NUM_PATHS][PATH_MAX_SIZE]) {
  int num_paths = 0;
  char *to_path = NULL; 
  char *default_path = "/bin/";



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
 * @param to_path The PATH string to be parsed
 * @param paths Array to store the individual parsed paths
 */
void parse_path_var(char *to_path, char paths[MAX_NUM_PATHS][PATH_MAX_SIZE]){
  int number_of_paths = 0;
  char *default_path = "/bin";
  string_copy(default_path, paths[number_of_paths++],'\0');
  
  if(to_path != NULL){
  
    while(*to_path != '\0') {
      string_copy(to_path, paths[number_of_paths++],':');

      while(*to_path != ':' && *to_path != '\0'){
        to_path++;
      }
    
      if(*to_path == ':'){
        to_path++;
      }  
    
    }
  }

  paths[number_of_paths][0] = '\0';

  for(int i = 0; paths[i][0] != '\0'; i++) {
    my_str_cat("/", paths[i]);
  }
  
}



void resolve_command_path(JOB *job, char spare_for_commands[MAX_ARGS][MAX_SIZE + PATH_MAX_SIZE], char paths[MAX_NUM_PATHS][PATH_MAX_SIZE]){

  char temp[MAX_SIZE + PATH_MAX_SIZE];
  Command *current_pipeline;
  struct stat statbuf;
  int spare_count = 0;
  temp[0] = '\0';
  
  for(unsigned int i = 0; i < job->num_stages ; i++) {
    current_pipeline = &job->pipeline[i];
  
    /*this means the user provided an absolute or arleative path*/
    if(string_compare(current_pipeline->argv[0],"/",1) ||
      string_compare(current_pipeline->argv[0],"./",2)){
              continue;
      }  

    for(int j = 0; paths[j][0] != '\0'; j++) {
      string_copy(paths[j], temp, '\0');
      my_str_cat(current_pipeline->argv[0],temp);
      

      if(stat(temp,&statbuf) == 0) {
        string_copy(temp,spare_for_commands[spare_count], '\0');
        current_pipeline->argv[0] = spare_for_commands[spare_count++];
        break;
      }
    }
  }
  

}
