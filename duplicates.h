//  CITS2002 Project 2 2021
//  Name(s):             Baxter Cooper, Khanh Huynh
//  Student number(s):   22966805, 22976648

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

// CHECK MEMORY ALLOCATION
#define CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }

// FILES
typedef struct OURFILE
{
    char *filepath;
    char *filename;
    char *hash;
    long long int bytes;
} OURFILE;

// FILES FUNCTIONS
extern OURFILE *file_new();

// DIRECTORIES
typedef struct _directory
{
    OURFILE *file;
    struct _directory *next;
} DIRECTORY;

// DIRECTORIES FUNCTIONS
extern DIRECTORY *directory_new();
extern DIRECTORY *get_directory(char *dirname, bool aflag);
extern DIRECTORY *merge(DIRECTORY *a, DIRECTORY *b);

// DISPLAY
typedef struct DISPLAY
{
    int all_files_count;
    int all_files_size;
    int unique_files_count;
    int unique_files_size;
} DISPLAY;

// DISPLAY FUNCTIONS
extern DISPLAY display_new();
extern void display_quiet(DIRECTORY *directory);
extern void display_dot(DIRECTORY *directory);
extern void display_duplicates(DIRECTORY *directory);
extern void display_duplicates_filename(DIRECTORY *directory, char *filename);
extern void display_duplicates_hash(DIRECTORY *directory, char *hash);
extern void display_stats(DIRECTORY *directory);

// HASHLIST
typedef struct _hashlist
{
    char *hash;
    struct _hashlist *next;
} HASHLIST;

// HASHLIST FUNCTIONS
extern HASHLIST *hashlist_new();
extern HASHLIST *hashlist_add(HASHLIST *hashlist, char *hash);
extern bool hashlist_contains(HASHLIST *hashlist, char *hash);

extern char *strdup(const char *s);
extern char *strSHA2(char *filename); 