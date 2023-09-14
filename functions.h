#include <stdlib.h>
#include <string.h>
// #include <dirent.h>
#include <sys/stat.h>

int my_strlen(char* str){
    int n=0;
    while(str[n]!='\0'){
        n++;
    }
    return n;
}

char* str_con(char* str1, char* str2){
    char* result = (char*)malloc(sizeof(str1)+sizeof(str2)+sizeof(char));
    int i=0;
    for(int j=0; j<my_strlen(str1); j++){
        result[i]=str1[j];
        i++;
    }
    if (result[i-1]!='/'){
        result[i]='/';
        i++;
    }
    for(int j=0; j<my_strlen(str2); j++){
        result[i]=str2[j];
        i++;
    }    
    return result;
}

int my_strcmp(char* param_1, char* param_2)
{
    while(*param_1!='\0' || *param_2!='\0'){
        if (*param_1>*param_2){
            return 1;
        }
        if (*param_1<*param_2){
            return -1;
        }
        param_1++;
        param_2++;
    }
    return 0;
}

void list_sorter(char** string_list, int length){
    char* temp = (char*)malloc(sizeof(char*));
    for(int i=0; i<length; i++){
        for(int j=0; j<length-1-i; j++){
            if (my_strcmp(string_list[j], string_list[j+1])>0){
                strcpy(temp, string_list[j]);
                strcpy(string_list[j], string_list[j+1]);
                strcpy(string_list[j+1], temp);
            }
        }
    }
}

void list_time_sorter(char* name_of_dir, char** string_list, int length){
    char* temp = (char*)malloc(sizeof(char*));
    for(int i=0; i<length; i++){
        for(int j=0; j<length-1-i; j++){
            struct stat *filestat1 = (struct stat*)malloc(sizeof(*filestat1));
            struct stat *filestat2 = (struct stat*)malloc(sizeof(*filestat1));
            stat(str_con(name_of_dir , string_list[j]),filestat1);
            stat(str_con(name_of_dir , string_list[j+1]),filestat2);
            if (filestat1->st_mtim.tv_sec<filestat2->st_mtim.tv_sec){
                strcpy(temp, string_list[j]);
                strcpy(string_list[j], string_list[j+1]);
                strcpy(string_list[j+1], temp);
            }
            else if (filestat1->st_mtim.tv_sec==filestat2->st_mtim.tv_sec){
                if (filestat1->st_mtim.tv_nsec<filestat2->st_mtim.tv_nsec){
                    strcpy(temp, string_list[j]);
                    strcpy(string_list[j], string_list[j+1]);
                    strcpy(string_list[j+1], temp);
                }
            }
        }
    }
}