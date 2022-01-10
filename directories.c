#include "duplicates.h"

// create and return a new directory pointer
DIRECTORY *directory_new()
{
    DIRECTORY *directory = calloc(1, sizeof(DIRECTORY));
    CHECK_ALLOC(directory);

    return directory;
}

// creates and returns a directory pointer containing all files in that directory
DIRECTORY *get_directory(char *dirname, bool aflag)
{
    DIRECTORY *directory = directory_new(); 

    DIR *dirp;
    struct dirent *dp; 

    dirp = opendir(dirname);

    // ensure directory could be openned properly
    if (dirp == NULL)
    {
        perror(dirname);
        exit(EXIT_FAILURE);
    }

    while ((dp = readdir(dirp)) != NULL)
    {   
        struct stat stat_info;

        char filepath[260];
        sprintf(filepath, "%s/%s", dirname, dp->d_name);

        if(stat(filepath, &stat_info) != 0) {
            perror( filepath );
            exit(EXIT_FAILURE);
        }

        if (S_ISDIR(stat_info.st_mode))
        {
            if (dp->d_name[0] != '.') {
                DIRECTORY *sub = directory_new();

                char dirpath[260];
                sprintf(dirpath, "%s/%s", dirname, dp->d_name);

                sub = get_directory(dirpath, aflag);

                // merge subdirectories with parent directory
                directory = merge(directory, sub);
            }
            
        } else if (dp->d_name[0] != '.' || aflag) {
            OURFILE *file = file_new();
            file->filename = strdup(dp->d_name);
            file->filepath = strdup(filepath);
            file->bytes = stat_info.st_size;
            file->hash = strdup(strSHA2(filepath));

            DIRECTORY *new = directory_new();
            new->file = file;
            new->next = directory;

            directory = new;
        }
    }
    
    // close directory
    closedir(dirp);

    return directory;
}

DIRECTORY *merge(DIRECTORY *a, DIRECTORY *b)
{
    DIRECTORY *merged = directory_new();

    while (a->next != NULL)
    {
        DIRECTORY *loop = directory_new();
        loop->file = a->file;
        loop->next = merged;

        merged = loop;
        a = a->next;
    }

    while (b->next != NULL)
    {
        DIRECTORY *loop = directory_new();
        loop->file = b->file;
        loop->next = merged;

        merged = loop;
        b = b->next;
    }

    return merged;
}