#include "duplicates.h"

// create new hashlist
HASHLIST *hashlist_new()
{
    HASHLIST *hashlist = calloc(1, sizeof(HASHLIST));
    CHECK_ALLOC(hashlist);

    return hashlist;
}

// add hash to hashlist
HASHLIST *hashlist_add(HASHLIST *hashlist, char *hash)
{
    // create a new hashlist
    HASHLIST *new = hashlist_new();

    // add original hashlist to new hashlist
    new->hash = strdup(hash);
    new->next = hashlist;

    return new;
}

// check if hashlist contains hash
bool hashlist_contains(HASHLIST *hashlist, char *hash)
{
    // loop through hashlist
    while (hashlist != NULL)
    {
        if (hashlist->hash != NULL) {
            int same_hash = strcmp(hashlist->hash, hash);
            // if hash is same as hash provided return true
            if (same_hash == 0)
            {
                return true;
            }
        }
        hashlist = hashlist->next;
    }
    // if none of hashes in hashlist match hash provided return false
    return false;
}
