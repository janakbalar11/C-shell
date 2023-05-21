#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

void execMulPipes(char* args[]){

  char* args2[32];
char* args3[32];
  char* args4[32];
char* args5[32];
  int count;
  int d;
    for(int i =0; args[i]!=NULL; i++){
      if(strcmp(args[i],"|")==0){
          count = i;
          d = i+1;
          break;
  }
      }
  

  for(int i = 0; i<count; i++){
    args2[i]=args[i];
    args2[i+1]= NULL;
  }    
     


int elms=0;
  for(int i =0; args[i]!=NULL;i++){
    elms++;
  }


for(int i = d; i<elms; i++){
  args3[i-d] = args[i];
  args3[i-d+1]=NULL;

}
int e = 0;
for(int i =0; args3[i]!=NULL; i++){
      if(strcmp(args3[i],"|")==0){
          e = i+1;
          break;
  }
      }

  int elms2=0;
  for(int i =0; args3[i]!=NULL;i++){
    elms2++;
  }




for(int i =0; i<=e-2;i++){
    args4[i]=args3[i];
    args4[i+1]=NULL;
  }



for(int i = e; i<elms2; i++){
  args5[i-e] = args3[i];
  args5[i-e+1]=NULL;

}
  
 int fd[2], fd2[2];
  pid_t pid;
  int status;

  if(pipe(fd)==-1){
    exit(1);
  }

  if(pipe(fd2)==-1){
    exit(1);
  }

  
  pid = fork();
  if(pid ==-1){
    exit(1);
  }

  if(pid == 0){
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    close(fd2[0]);
    close(fd2[1]);
    for(int i = 0; args2[i]!=NULL; i++){
       if(strcmp(args2[i],"<")==0){
              int fp = open(args2[i+1], O_RDONLY);
              
              if(fp < 0){
                continue;
              }
              if(dup2(fp,STDIN_FILENO)<0){
                continue;
              }
            
        int p = 0;
         for (int i = 0; i < count; i++) {
        if (strcmp(args2[i], "<") == 0) {
            p = i;
            break;
        }
    }

         if (p != 0) {
        for (int i = p; i < count-1; i++) {
            strcpy(args2[i], args2[i + 1]);
            args2[i+1]=NULL;
        }
             
        count--;

            }
    int i,j,k;
         for (i = 0; i < count; i++) {
        for (j = i+1; j < count; j++) {
            if (strcmp(args2[i],args2[j])==0) {
                for (k = j; k < count - 1; k++) {
                    args2[k] = args2[k+1];
                }
                count--;
                j--; 
            }
        }
    }

         args2[count]=NULL;
       
   
   
    
  }
      }
         execvp(args2[0], args2);


    }
  
  pid_t pid2 = fork();

  if(pid2==-1){
    exit(1);
  }
  if(pid2==0){

    dup2(fd[0], STDIN_FILENO);
    dup2(fd2[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    close(fd2[0]);
    close(fd2[1]);

    int out_fd;
     for(int i = 0; args4[i]!=NULL; i++){
      if(strcmp(args4[i],">")==0){
        if(args4[i+1]!=NULL){
          int fp = open(args4[i+1],  O_WRONLY | O_CREAT | O_TRUNC, 0666);

                if(fp == -1){
                  perror("open");
                  exit(1);
                }
                dup2(fp,STDOUT_FILENO);
                args4[i]=NULL;
                args4[i+1]=NULL;
                
              
              
            }
        }
       else if(strcmp(args4[i],"<")==0){
              int fp = open(args4[i+1], O_RDONLY);
              
              if(fp < 0){
                perror("Error");
                continue;
              }
              if(dup2(fp,STDIN_FILENO)<0){
                perror("Error");
                continue;
              }
             
            }
    
        }
    execvp(args4[0],args4);


      }


  pid_t pid3 = fork();
   if(pid2==-1){
    exit(1);
  }
  if(pid3==0){
      dup2(fd2[0], STDIN_FILENO);
      close(fd[0]);
      close(fd[1]);
      close(fd2[0]);
      close(fd2[1]);

     int out_fd;
     for(int i = 0; args5[i]!=NULL; i++){
      if(strcmp(args5[i],">")==0){
        if(args3[i+1]!=NULL){
          int fp = open(args5[i+1],  O_WRONLY | O_CREAT | O_TRUNC, 0666);

                if(fp == -1){
                  perror("open");
                  exit(1);
                }
                dup2(fp,STDOUT_FILENO);
                args5[i]=NULL;
                args5[i+1]=NULL;
                
              
              
            }
        }
       else if(strcmp(args3[i],"<")==0){
              int fp = open(args5[i+1], O_RDONLY);
              
              if(fp < 0){
                perror("Error");
                continue;
              }
              if(dup2(fp,STDIN_FILENO)<0){
                perror("Error");
                continue;
              }
             
            }
    
        }
    execvp(args5[0],args5);



    
    }


  close(fd[0]);
  close(fd[1]);
  close(fd2[0]);
  close(fd2[1]);

  waitpid(pid,NULL,0);
  waitpid(pid2,NULL,0);
  waitpid(pid3,NULL,0);
  
      
  }

void execPipes(char* args[]){
char* args3[32];
  int count;
  int d;
    for(int i =0; args[i]!=NULL; i++){
      if(strcmp(args[i],"|")==0){
          count = i;
          d = i+1;
          break;
  }
      }

  char* args2[32];

  for(int i = 0; i<count; i++){
    args2[i]=args[i];
    args2[i+1]= NULL;
  }    
     


int elms=0;
  for(int i =0; args[i]!=NULL;i++){
    elms++;
  }


for(int i = d; i<elms; i++){
  args3[i-d] = args[i];
  args3[i-d+1]=NULL;
}

  
  int fd[2];
    pid_t pid;

  if(pipe(fd)==-1){
    exit(1);
  }
  pid = fork();
  if(pid ==-1){
    exit(1);
  }

  if(pid == 0){
    dup2(fd[1],STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    for(int i = 0; args2[i]!=NULL; i++){
       if(strcmp(args2[i],"<")==0){
              int fp = open(args2[i+1], O_RDONLY);
              
              if(fp < 0){
                continue;
              }
              if(dup2(fp,STDIN_FILENO)<0){
                continue;
              }
            
        int p = 0;
         for (int i = 0; i < count; i++) {
        if (strcmp(args2[i], "<") == 0) {
            p = i;
            break;
        }
    }

         if (p != 0) {
        for (int i = p; i < count-1; i++) {
            strcpy(args2[i], args2[i + 1]);
            args2[i+1]=NULL;
        }
             
        count--;

            }
    int i,j,k;
         for (i = 0; i < count; i++) {
        for (j = i+1; j < count; j++) {
            if (strcmp(args2[i],args2[j])==0) {
                for (k = j; k < count - 1; k++) {
                    args2[k] = args2[k+1];
                }
                count--;
                j--; 
            }
        }
    }

         args2[count]=NULL;
       
   
   
    
  }
      }
         execvp(args2[0], args2);

    }

  pid_t pid2 = fork();

  if(pid2==-1){
    exit(1);
  }
  if(pid2==0){
    dup2(fd[0],STDIN_FILENO);
    close(fd[0]);
    close(fd[1]);
  int out_fd;
     for(int i = 0; args3[i]!=NULL; i++){
      if(strcmp(args3[i],">")==0){
        if(args3[i+1]!=NULL){
          int fp = open(args3[i+1],  O_WRONLY | O_CREAT | O_TRUNC, 0666);

                if(fp == -1){
                  perror("open");
                  exit(1);
                }
                dup2(fp,STDOUT_FILENO);
                args3[i]=NULL;
                args3[i+1]=NULL;
                
              
              
            }
        }
       else if(strcmp(args3[i],"<")==0){
              int fp = open(args3[i+1], O_RDONLY);
              
              if(fp < 0){
                perror("Error");
                continue;
              }
              if(dup2(fp,STDIN_FILENO)<0){
                perror("Error");
                continue;
              }
             
            }
    
        }
    execvp(args3[0],args3);
  

      }
  close(fd[0]);
  close(fd[1]);
  waitpid(pid,NULL,0);
  waitpid(pid2,NULL,0);
  
      
  }


typedef struct job{
  char* input;
  pid_t pid;
  int numjob;
  struct job *next;
}job;

job *head = NULL;
int numjob=0;
void addJob(pid_t pid, char* input){
  
  job *newjob = malloc(sizeof(job));
  newjob->pid = pid;
  newjob->numjob = numjob+=1;
  newjob->input= strdup(input);
  newjob->next = NULL;

  if (head == NULL) {
    head = newjob;
  } else {
    job *currentjob = head;
    while (currentjob->next != NULL) {
      currentjob = currentjob->next;
    }
    currentjob->next = newjob;
  }
}


// void removeJob(pid_t pid){
  
// }





void resumeJob(int id){
  job *prev = NULL;
  job *job = head;

  while(job!=NULL){
    if(job->numjob == id){
      kill(job->pid, SIGCONT);
      
      
      int status;
      waitpid(job->pid, &status, WUNTRACED);
      if (WIFSTOPPED(status)) { 
          addJob(job->pid, job->input);
        }


        if(prev!=NULL){
          prev->next = job->next;
          // prev->numjob = prev->numjob+1;
          struct job* temp = job->next;
          while(temp!=NULL){
            temp->numjob--;
            temp = temp->next;
          }
        }

      if(prev==NULL){
          if(head != NULL) {
          head = job->next;
           struct job* temp = job->next;
          while(temp!=NULL){
            temp->numjob--;
            temp = temp->next;
          }
     }
      }

    

      
//       if(prev==NULL){
//         if(head != NULL) {
//           head = job->next;
//         if(head != NULL) {
//             head->numjob = head->numjob-1;
//             if(head->numjob == 0){
//               head->numjob = head->numjob+1;
//             }
//         }
//      }

//         }         
//       else if (job != NULL) {
//         prev->next = job->next;
//         prev->numjob = prev->numjob-1;
//          if(prev->numjob == 0){
//               prev->numjob = prev->numjob+1;
// }
//         }
      
      // free(job->input);
      free(job);

      return;
      }
    prev = job;
    job = job->next;
  }
  fprintf(stderr, "Error: invalid job\n");
}



void changeDir(char* args[]){
  char* cwd;
  char * cwd_base = NULL;
  cwd = getcwd(NULL, 0);
  cwd_base = basename(cwd);

  int count=0;
  for(int i =0; args[i]!=NULL; i++){
    count++;
  }

  
  if(args[1] == NULL){
    fprintf(stderr,"Error: invalid command\n");
  }
   else if(count>2){
     fprintf(stderr,"Error: invalid command\n");
     
   } 
  else if(strcmp(args[1],"..")==0){
    chdir("..");
    }
      
  else{
    int result = chdir(args[1]);
    if(result == 0){
      chdir(args[1]);
    }
  
    else{
      fprintf(stderr,"Error: invalid directory\n");
    }
  }
}

int main(int argc, char **argv){

  char input[1024];
  size_t input_size = 0;
  char *cwd = NULL;

  char *args[32];
  int in_fd = STDIN_FILENO;
  int out_fd = STDOUT_FILENO;


 label: 
  while(1){
    char * cwd_base = NULL;
    cwd = getcwd(NULL, 0);
    cwd_base = basename(cwd);
    printf("[nyush %s]$ ", cwd_base);
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
      }
        
    input[strcspn(input,"\n")] = 0;

 char input2[1024];
  strcpy(input2,input);
    

    if(strcmp(input2,"exit")==0){
      job *job = head;
      if(job!=NULL){
        fprintf(stderr,"Error: there are suspended jobs\n");
        goto label;
      }
      else{
         break;
      }
     
    }

 
    int i = 0;
    args[i] = strtok(input2, " ");
    while(args[i]!=NULL){
      i++;
      args[i]=strtok(NULL, " ");
    }

    
    for(int i = 0; args[i]!=NULL;i++){
      if(strcmp(args[i],"exit")==0){
        if(args[i+1]==NULL){
          break;
        }
        else{
          fprintf(stderr,"Error: invalid command\n");
          goto label;
        }
      }
    }

    int sig;
    if(strcmp(args[0], "killall") == 0) {
      sig = atoi(args[1]+1);
      
      if(sig == 0) {
        continue;
      }

      if(kill(0, sig) == -1) {
        perror("killall");
      }

      }

    

if(strcmp(args[0],"|")==0){
  fprintf(stderr,"Error: invalid command\n");
  goto label;
}

    

int fd = 0;
int mfd = 0;
    for(int i =0; args[i]!=NULL; i++){
      if(strcmp(args[i],"|")==0){
        if(args[i+1]!=NULL){
           fd++;
          for(int j = i+1; args[j]!=NULL;j++){
            if(strcmp(args[j],"|")==0){
              mfd++;
              break;
            }
          }
        
        }
      }
      }
    
  
    if(mfd>0){
      execMulPipes(args);
      goto label;
    }
    else if(fd>0){
    execPipes(args);
    goto label;
   }

    if(strcmp(input2,"cd")==0){
      changeDir(args);
      continue;
    }

    if(strcmp(input2,"fsck")==0){
      fprintf(stderr,"Error: invalid program\n");
      goto label;
    }

    if(strcmp(input2,"jobs")==0){
        job *job = head;
        while(job!=NULL){
          printf("[%d] %s\n",job->numjob,job->input);
          job=job->next;
        }

      goto label;
    }

   if(strcmp(args[0],"fg")==0){
     if(args[1]!=NULL){
       resumeJob(atoi(args[1]));
        goto label;
   }
     else{
       fprintf(stderr,"Error: invalid command");
     }
     }
    

    

    for(int i = 0; args[i]!=NULL;i++){
      if(strcmp(args[i],"cat")==0){
        if(args[i+1]==NULL){
          fprintf(stderr, "Error: invalid command\n");
          goto label;
        }
      }
    }

  

    for(int i = 0; args[i]!=NULL; i++){
      if(strcmp(args[i],"<")==0){
        if(args[i+1]!=NULL){
          in_fd = open(args[i+1], O_RDONLY);
          if(in_fd ==-1){
            fprintf(stderr,"Error: invalid file\n");
            continue;
          }
        }
        else{
          fprintf(stderr,"Error: invalid command\n");
          goto label;
        }
        args[i]=NULL;
        }
      else if(strcmp(args[i],">")==0){
        if(args[i+1]!=NULL){
          out_fd = open(args[i+1],O_WRONLY | O_CREAT, 0644);
          if(out_fd == -1){
            perror("open");
            continue;
          }
          ftruncate(out_fd, 0);
        }
        args[i]=NULL;
      }
      else if(strcmp(args[i],">>")==0){
        if(args[i+1]!=NULL){
          
          out_fd = open(args[i+1], O_WRONLY | O_CREAT, 0644);

          if(out_fd == -1){
            perror("open");
            continue;
          }
          lseek(out_fd, 0, SEEK_END);
        }
        args[i] = NULL;
      }
    }

    pid_t pid;  
    int status;

    pid = fork();

    if(pid == 0){
      if(in_fd!=STDIN_FILENO){
        if(dup2(in_fd, STDIN_FILENO)==-1){
          exit(1);
        }
      }
      if(out_fd!=STDOUT_FILENO){
        if(dup2(out_fd,STDOUT_FILENO)==-1){
          exit(1);
        }
      }
      if(execvp(args[0],args)==-1){
        fprintf(stderr, "Error: invalid program\n");
        exit(1);
        
      }
    }
    else if(pid<0){
      perror("fork");
      return -1;
      
    }
    else{
      int status;
       waitpid(pid, &status, WUNTRACED);
        if (WIFSTOPPED(status)) { 
          addJob(pid, input);
          goto label;
      }
      }
    

    if(in_fd != STDIN_FILENO){
      close(in_fd);
      in_fd = STDIN_FILENO;
      
    }
    if(out_fd!=STDOUT_FILENO){
      close(out_fd);
      out_fd = STDOUT_FILENO;
    }
    
  }
  return 0;
  
}
