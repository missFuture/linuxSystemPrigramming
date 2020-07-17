#ifndef MEDIALIB_H_
#define MEDIALIB_H_
#include <unistd.h>
#include "../include/proto.h"
struct mlib_listentry_st
{
    chnid_t chnid;
    char *desc;//description
};

int mlib_getchnlist(struct mlib_listentry_st **, int *);

int mlib_freechnlist(struct mlib_listentry_st *);

ssize_t mlib_readchn(chnid_t, void *, size_t);


#endif