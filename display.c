#include "duplicates.h"

// create new display
DISPLAY display_new()
{
    DISPLAY display = { 0 };

    return display;
}

// lflag option implementation
void display_duplicates(DIRECTORY *directory)
{
    DIRECTORY *full = directory;
    // creates a hashlist to store unique file hashes
    HASHLIST *hashlist = hashlist_new();

    // ensures only files with duplictates are printed
    bool duplicate = false;

    // loop through directory until end
    while (directory->next != NULL)
    {
        char *hash_1 = directory->file->hash;
        char *filepath_1 = directory->file->filepath;

        // stop duplicates from being printed for each duplicates file
        if (hashlist_contains(hashlist, hash_1) == 0)
        {
            // adds files hash to hashlist
            hashlist = hashlist_add(hashlist, hash_1);

            // loop through files in directory for duplicates
            DIRECTORY *loop = full;
            while (loop->next != NULL)
            {
                char *hash_2 = loop->file->hash;
                char *filepath_2 = loop->file->filepath;
                int same_hash = strcmp(hash_1, hash_2);

                // duplicate files must have same hash but different filepath
                if (same_hash == 0 && filepath_1 != filepath_2)
                {
                    // print with tab duplicate filepath
                    if (duplicate)
                    {
                        printf("    %s", filepath_2);
                    }
                    // print with tab target file then duplicates file
                    else
                    {
                        printf("%s    %s", filepath_1, filepath_2);
                        duplicate = true;
                    }
                }
                loop = loop->next;
            }
        }
        // print new line if duplicates were found
        if (duplicate)
        {
            printf("\n");
        }
        directory = directory->next;
        // reset duplicates to false for next file
        duplicate = false;
    }
}

// fflag option implementation
void display_duplicates_filename(DIRECTORY *directory, char *filename)
{
    DIRECTORY *full = directory;
    bool duplicate = false;
    char hash[64];

    // loop through directory to find hash of the file 
    while (directory->next != NULL)
    {
        int same_filename = strcmp(directory->file->filename, filename);
        if (same_filename == 0)
        {
            strcpy(hash, directory->file->hash);
            break;
        }
        directory = directory->next;
    }

    // reset pointer back to start of directory
    directory = full;

    // loop through directory 
    while (directory->next != NULL)
    {
        int same_hash = strcmp(directory->file->hash, hash);

        // print filepath if file hash same hash and isnt the file provided
        if (same_hash == 0)
        {
            printf("%s\n", directory->file->filepath);
            duplicate = true;
        }
        directory = directory->next;
    }

    if (duplicate) {
        exit(EXIT_SUCCESS);
    } else {
        exit(EXIT_FAILURE);
    }
}

// hflag option implementation
void display_duplicates_hash(DIRECTORY *directory, char *hash)
{
    bool duplicate = false;

    // loop through directory 
    while (directory->next != NULL)
    {
        int same_hash = strcmp(directory->file->hash, hash);
        // print filepath if file hash same as hash provided
        if (same_hash == 0)
        {
            printf("%s\n", directory->file->filepath);
            duplicate = true;
        }
        directory = directory->next;
    }

    if (duplicate) {
        exit(EXIT_SUCCESS);
    } else {
        exit(EXIT_FAILURE);
    }
}

// qflag option implementation 
void display_quiet(DIRECTORY *directory)
{
    // create a hashlist to store unique hashes
    HASHLIST *hashlist = hashlist_new();

    // loop through directory
    while (directory->next != NULL)
    {
        // see if hashlist already contains hash
        bool contains = hashlist_contains(hashlist, directory->file->hash);

        // if hashlist does not contain hash then file is not a duplicates
        if (!contains)
        {
            hashlist = hashlist_add(hashlist, directory->file->hash);
        }
        // if hashlist does contain hash then file is a duplictate EXIT_SUCCESS
        else
        {
            exit(EXIT_SUCCESS);
        }
        directory = directory->next;
    }
    // no duplicates were found EXIT_FAILURE
    exit(EXIT_FAILURE);
}

// print directory stats 
void display_stats(DIRECTORY *directory)
{
    // create new display to store stats
    DISPLAY display = display_new();
    // create new hashlist to store unique hashes
    HASHLIST *hashlist = hashlist_new();

    // loop through directory
    while (directory->next != NULL)
    {
        // for each file increase total file count and size
        display.all_files_count++;
        display.all_files_size += directory->file->bytes;

        // get if hashlist contains file hash
        bool contains = hashlist_contains(hashlist, directory->file->hash);

        // if does not contain increase unique file count and size
        if (!contains)
        {
            display.unique_files_count++;
            display.unique_files_size += directory->file->bytes;
            hashlist = hashlist_add(hashlist, directory->file->hash);
        }
        directory = directory->next;
    }

    // print directory stats
    printf("%i\n", display.all_files_count);
    printf("%i\n", display.all_files_size);
    printf("%i\n", display.unique_files_count);
    printf("%i\n", display.unique_files_size);
}