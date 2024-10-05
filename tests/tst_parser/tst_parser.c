#include <stdio.h>

#include "parser.h"



int main() {


  JOB job;


    get_usr_input(&job.usr_input);
    
    if(validate_and_parse_job(&job) == FALSE) {
        printf("REJECTED\n");
    }


    
    


}
