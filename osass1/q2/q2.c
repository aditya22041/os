#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#define MAX_LIMIT 100

int countSpaces(const char *str) {
    int count = 0;
    while (*str != '\0') {
        if (*str == ' ') {
            count++;
        }
        str++; 
    }
    
    return count;
}

void justWord(char copy[]){
    int wrd = 1;
    char *ptr = strtok(NULL,"\n");
    FILE *demo = fopen(ptr, "r");
        if(demo == NULL){
            perror("Error opening file");
            return;
        }       
        else{
            char ch = fgetc(demo);
            while(ch != EOF){
                if(ch == ' ' || ch == '\n')
                    wrd++;
                ch = fgetc(demo);
            }
        }
        fclose(demo);
        printf("%d\n",wrd);
        return;
}

void pword(char copy[]){
    int wrd = 1;
    if(countSpaces(copy) == 1){
        justWord(copy);
        return;
    }
    char *ptr = strtok(NULL," ");

    if(strcmp(ptr, "-n") == 0){
        ptr = strtok(NULL,"\n");
        FILE *demo = fopen(ptr, "r");
        if(demo == NULL){
            perror("Error opening file");
            return;
        }       
        else{
            char ch = fgetc(demo);
            while(ch != EOF){
                if(ch == ' ' )
                    wrd++;
                ch = fgetc(demo);
            }
        }
        fclose(demo);
        printf("%d\n",wrd);
        return;
    }

    else if(strcmp(ptr, "-d") == 0) {
        int wrd1 = 1, wrd2 = 1;
        ptr = strtok(NULL," ");
        FILE *demo = fopen(ptr, "r");
        if(demo == NULL){
            perror("Error opening file");
            return;
        }       
        else{
            char ch = fgetc(demo);
            while(ch != EOF){
                if(ch == ' ' || ch == '\n')
                    wrd1++;
                ch = fgetc(demo);
            }
        }
        fclose(demo);

        ptr = strtok(NULL,"\n");
        FILE *demo2 = fopen(ptr, "r");
        if(demo == NULL){
            perror("Error opening file");
            return;
        }       
        else{
            char ch = fgetc(demo);
            while(ch != EOF){
                if(ch == ' ' || ch == '\n')
                    wrd2++;
                ch = fgetc(demo);
            }
        }
        fclose(demo2);
        printf("%d\n",wrd1-wrd2);
        return;
    }    
    else
        printf("Error : The command is incorrect\n");
}

void cngDir(char *ptr,char pro[]){

            if (chdir(ptr) == 0) {
                printf("Successfully Changed directory to: %s\n",ptr);
                strcat(pro,ptr);
                strcat(pro,"/");
            } else {
                perror("Error changing directory");
                return;
            }
        
    
}
void createDir(char copy[], char pro[]){

    if(countSpaces(copy) == 1){
        char *ptr = strtok(NULL,"\n");
        if (mkdir(ptr, 0777) == 0) cngDir(ptr,pro);
        else {
            perror("Error creating directory");
            return;
        }
        return;
    }
    char *ptr = strtok(NULL, " ");
    // dir -r filename
    if(strcmp(ptr,"-r") == 0) {
        ptr = strtok(NULL, "\n");
                if (rmdir(ptr) == 0) 
                    printf("Directory '%s' removed successfully.\n", ptr);
                //else
                //    perror("Error removing directory");
                if (mkdir(ptr, 0777) == 0) cngDir(ptr,pro);
                else {
                    perror("Error creating directory 1");
                    return;
                }
        return;
    }// dir -v filename
    else if(strcmp(ptr,"-v") == 0){
            ptr = strtok(NULL, "\n");
            printf("Creating directory\n");
            if (mkdir(ptr, 0777) == 0) {
                printf("Directory created successfully\nchanging directory to: %s\n",ptr);
                cngDir(ptr,pro);
            }
            else {
                perror("Error creating directory 1");
                return;
            }
        return;
    }
    else
        printf("Error : The command is incorrect\n");
}
void knowDate(char copy[]){
    char *file_name = NULL;
    char *option = NULL;
    if(countSpaces(copy) == 1){
        file_name = strtok(NULL,"\n");
    }
    else{
        option = strtok(NULL," ");
        file_name = strtok(NULL,"\n");
    }
    struct stat file_info;
    if (stat(file_name, &file_info) == -1) {
        perror("Error reading file information");
        return;
    }
    if(option == NULL){
        char *formatted_time = ctime(&file_info.st_mtime);
        printf("%s",formatted_time);
    }
    else if(strcmp(option,"-d") == 0) {
        struct tm *time_info = gmtime(&file_info.st_mtime);
        printf("Last modified time of %s (time only): %02d:%02d:%02d\n", file_name, time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
    }
    else if(strcmp(option,"-R") == 0){
        struct tm *time_info = gmtime(&file_info.st_mtime);
        char formatted_time[50]; // Buffer for formatted time
        strftime(formatted_time, sizeof(formatted_time), "%a, %d %b %Y %T %z", time_info);
        printf("%s\n",formatted_time);
    }
    else
        printf("Error : The command is incorrect\n");
    return;
}
int main(){
    char str[MAX_LIMIT];
    char pro[] = "<prompt>/";
    while(1){
        printf("%s ",pro);
        fgets(str, MAX_LIMIT, stdin);
        char copy[MAX_LIMIT];
        strcpy(copy,str);
        char *token = strtok(str, " ");

        if(strcmp(token, "word") == 0)
            pword(copy);
        else if(strcmp(token, "dir") == 0)
            createDir(copy,pro);
        else if(strcmp(token,"date") == 0)
            knowDate(copy);
    }
    return 0;
}

