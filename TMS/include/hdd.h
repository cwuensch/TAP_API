#ifndef __APPLFILE__
#define __APPLFILE__

#define MAX_FILE_NAME_SIZE  127

#define ATTR_NORMAL 	0xd0
#define ATTR_FOLDER 	0xe0

typedef struct 
{
    dword   info;
    dword   time;   // mjd << 16 | h << 8 | m
    long64  size;
    char    name[ MAX_FILE_NAME_SIZE + 1];
    void*   handle;
} TYPE_File;

typedef struct
{
    dword   attr;
    dword   info;
    dword   time;   //mjd << 16 | h<<8 | m
    long64  size;
    char    name[ MAX_FILE_NAME_SIZE + 1 ];
} TYPE_FolderEntry;

#endif

