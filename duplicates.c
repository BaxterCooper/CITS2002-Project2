//  CITS2002 Project 2 2021
//  Name(s):             Baxter Cooper, Khanh Huynh
//  Student number(s):   22966805, 22976648

#include "duplicates.h"

// usage/error message when inputting an invalid command line arguement
void usage(char *progname)
{
    fprintf(stderr, "Usage: %s [options] dirname [dirname2 ...]\n", progname);
    fprintf(stderr, "where opetions are:\n");

    fprintf(stderr, "-a\t\tcheck all files, including those beginning with '.'\n");
    fprintf(stderr, "-A\t\tindicates if this program attempts the advanced features\n");
    fprintf(stderr, "-f filename\tthe relative filepaths of all files whose SHA2 hash matches that of the indicated file\n");
    fprintf(stderr, "-h hash\t\tlist the relative filepaths of all files with the indicated SHA2 hash\n");
    fprintf(stderr, "-l\t\tlist the relative filepaths of all duplicates found\n");
    fprintf(stderr, "-q\t\tquietly test if any duplicates exist\n");

    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    // program name
    char *progname = (progname = strrchr(argv[0], '/')) ? progname + 1 : argv[0];

    // command line arguement options
    bool aflag = false;
    char *fflag = NULL;
    char *hflag = NULL;
    char lflag = false;
    char qflag = false;

    // inialise variables
    int opt;
    int index;

    // check command line arguements
    while ((opt = getopt(argc, argv, "aAf:h:ql")) != -1)
    {
        switch (opt)
        {
        case 'a':
            aflag = !aflag;
            break;

        case 'A':
            exit(EXIT_SUCCESS);
            break;

        case 'f':
            fflag = strdup(optarg);
            break;

        case 'h':
            hflag = strdup(optarg);
            break;

        case 'q':
            qflag = !qflag;
            break;

        case 'l':
            lflag = !lflag;
            break;

        default:
            fprintf(stderr, "%s : illegal options -%c\n", progname, optopt);
            usage(progname);
            break;
        }
    }

    DIRECTORY *merged = directory_new();

    // for each directory provided
    for (index = optind; index < argc; ++index)
    {
        DIRECTORY *directory = get_directory(argv[index], aflag);

        merged = merge(merged, directory);
    }

    if (qflag)
    {
        display_quiet(merged);
    }

    if (fflag)
    {
        display_duplicates_filename(merged, fflag);
    }

    else if (hflag)
    {
        display_duplicates_hash(merged, hflag);
    }

    else if (lflag)
    {
        display_duplicates(merged);
    }

    else
    {
        display_stats(merged);
    }

    return 0;
}