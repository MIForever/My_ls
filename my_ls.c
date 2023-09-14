#include "functions.h"
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>

int main(int ac, char** av){
    int a_exist=0, t_exist = 0, a_t_exist = 0;
    char** list_of_dirs;
    char** names_of_f_files;
    int len=0;
    if (ac>1){
        for (int i=1; i<ac; i++){
            if(!strcmp(av[i],"-a")){
                a_exist=1;
            }
            else if(!strcmp(av[i],"-t")){
                t_exist=1;
            }
            else if(!strcmp(av[i],"-at") || !strcmp(av[i],"-ta")){
                a_t_exist=1;
            }
            else len++;
            
            if (len){
                list_of_dirs = (char**)calloc(len,sizeof(char*));
                int q=0;
                for (int i=1; i<ac; i++){
                    if (av[i][0]!='-'){
                        list_of_dirs[q] = malloc(sizeof(av[i]));
                        strcpy(list_of_dirs[q], av[i]);
                        q++;
                    }
                }
            }
        }
    }
    struct dirent *entry;
    DIR* directory;
    if (!len){
        len=1;
        list_of_dirs = (char**)calloc(len,sizeof(char*));
        list_of_dirs[0] = malloc(2*sizeof(char));
        strcpy(list_of_dirs[0],".");
    }
    list_sorter(list_of_dirs, len);

    for (int i=0; i<len; i++){
        int n=0;
        if (len>1) printf("%s:\n",list_of_dirs[i]);
        directory =  opendir(list_of_dirs[i]);
        while((entry=readdir(directory))!=NULL){
            if(!a_exist && !a_t_exist){
                if (entry->d_name[0]!='.') n++;
            }
            else n++;
        }
        closedir(directory);
        names_of_f_files = calloc(n,sizeof(char*));
        directory =  opendir(list_of_dirs[i]);
        int p=0;
        while((entry=readdir(directory))!=NULL){
            if(!a_exist && !a_t_exist){
                if (entry->d_name[0]!='.'){
                    names_of_f_files[p] = malloc(sizeof(entry->d_name));
                    strcpy(names_of_f_files[p], entry->d_name);
                    p++;
                }
            }
            else{
                names_of_f_files[p] = malloc(sizeof(entry->d_name));
                strcpy(names_of_f_files[p], entry->d_name);
                p++;
            }
        }
        if(!t_exist && !a_t_exist){
            list_sorter(names_of_f_files,n);
        }
        else{
            list_time_sorter(list_of_dirs[i] ,names_of_f_files, n);
        }
        closedir(directory);
        for (int i=0; i<n; i++){
            printf("%s\n", names_of_f_files[i]);
        }
        if(len>1 && len!=(i+1)) printf("\n");
    }

    return 0;
}