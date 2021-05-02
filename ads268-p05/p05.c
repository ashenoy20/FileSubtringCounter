#include <stdio.h> 
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ctype.h>

int main(int argc, char *argv[]){
	if(argc == 1){
	 		printf("Error: No arguments found\n");
	 		return(-1);
	}
	if(strcmp(argv[1], "--systemcalls") == 0){
	    	  if(argc <= 3){
			printf("Error: Insufficent/Wrong arguments\n");
			return(-1);
		  }
		  int fd;
		  fd = open(argv[2], O_RDONLY, 0);

		  if(fd < 0){
		      perror("File error\n");
		      return(-1);
		  }else{
		      int number[argc-3];
		      char ch;
		      int counterIndex = 0;
		      for(int i = 3; i < argc; i++){
		          int counter = 0;
		          int index = 0;
		          char *cmdLine = argv[i];
		          int length = strlen(cmdLine);
		           for(int k = 0; k < length; k++){
		          	cmdLine[k] = tolower(cmdLine[k]);
		          }
		          while(read(fd, &ch, 1) > 0){
		              if(ch == cmdLine[index]){
		                  if(index == length - 1){
		                      counter++;
		                      index = 0;
		                      int offset = -1*(length-1);
		                      lseek(fd,offset,SEEK_CUR);
		                  }else{
		                      index++;
		                  }
		              }else{
		                  index = 0;
		              }

		          }
		          lseek(fd,0, SEEK_SET);
		          number[counterIndex] = counter;
		          counterIndex++;
		          counter = 0;
		      }

		      for(int j = 0; j < argc - 3; j++){
		          printf("%d\n", number[j]);
		      }


		      close(fd);
		      
		  }
	}else{
		  if(argc <= 2){
		  	printf("Error: Insufficent/Wrong arguments\n");
		  	return(-1);
		  }
		  FILE *fp;
		  fp = fopen(argv[1], "r");

		  if(fp == NULL){
		      perror("File error\n");
		      return(-1);
		  }else{

		      int number[argc-2];
		      char ch;
		      int counterIndex = 0;
		      for(int i = 2; i < argc; i++){
		          int counter = 0;
		          int index = 0;
		          char *cmdLine = argv[i];
		          int length = strlen(cmdLine);
		          for(int k = 0; k < length; k++){
		          	cmdLine[k] = tolower(cmdLine[k]);
		          }
		          while((ch = fgetc(fp)) != EOF){
		              if(ch == cmdLine[index]){
		                  if(index == length - 1){
		                      counter++;
		                      index = 0;
		                      int offset = -1*(length-1);
		                      fseek(fp,offset,SEEK_CUR);
		                  }else{
		                      index++;
		                  }
		              }else{
		                  index = 0;
		              }

		          }
		          fseek(fp,0, SEEK_SET);
		          number[counterIndex] = counter;
		          counterIndex++;
		          counter = 0;
		      }

		      for(int j = 0; j < argc - 2; j++){
		          printf("%d\n", number[j]);
		      }


		      fclose(fp);
		      
		  }
   }
   return(0);
}
