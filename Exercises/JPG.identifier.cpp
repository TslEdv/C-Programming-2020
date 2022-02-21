#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <malloc.h>
#pragma warning ( disable : 4996 )

/*
This exercise was provided by another course.
We were given a file with 50 files with no extentions and the aim was to identify the jpegs in it.
I chose to do it in C.
*/

size_t file_list(const char* path, char*** ls) {
    size_t count = 0;
    size_t length = 0;
    DIR* dp = NULL;
    struct dirent* ep = NULL;
    dp = opendir(path);
    if (NULL == dp) 
    {
        fprintf(stderr, "no such directory: '%s'", path);
        return 0;
    }
    *ls = NULL;
    ep = readdir(dp);
    while (NULL != ep)
    {
        count++;
        ep = readdir(dp);
    }
    rewinddir(dp);
    *ls =(char**) calloc(count, sizeof(char*));
    count = 0;
    ep = readdir(dp);
    while (NULL != ep) 
    {
        (*ls)[count++] = strdup(ep->d_name);
        ep = readdir(dp);
    }
    closedir(dp);
    return count;
}

int main(int argc, char** argv) {

    char** files;
    size_t count;
    int i;
    char filelocation[] = "C:\\Users\\User\\Desktop\\aleksei\\random_files\\";
    count = file_list("C:\\Users\\User\\Desktop\\aleksei\\random_files", &files);
    for (i = 0; i < count; i++) {
    }
    char* realfiles[192];
    for (int i = 0; i < 192; i++)
    {
        realfiles[i]=(char*)malloc(sizeof(char) * (strlen(filelocation) + strlen(files[i]) + 1));
        strcpy(realfiles[i], filelocation);
        strcat(realfiles[i] , files[i]);
    }
    for (i = 2; i < count; i++)
    {
        FILE* fp = fopen(realfiles[i], "r+");
        unsigned char bytes[3];
        if (fp == NULL)
        {
            printf("Sorry, the file that you are looking for, does not exist.\n");
        }
        else
        {
            fread(bytes, 3, 1, fp);
            if (bytes[0] == 0xff
                && bytes[1] == 0xd8
                && bytes[2] == 0xff)
            {
                printf("This Image is "
                    "in JPEG format! %s\n", files[i]);
            }
        }
        fclose(fp);
    }
    return 0;
}