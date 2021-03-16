#ifndef __APPLFILE__
#define __APPLFILE__

#define TS_FILE_NAME_SIZE	100

#define ATTR_NORMAL 	0xd0
#define ATTR_TS 		0xd1
#define ATTR_PROGRAM	0xd2
#define ATTR_FOLDER 	0xf2

#define SIZE_FileBlock	512

typedef struct 
{
	dword	attr:8;
	dword	mjd:16;
	dword	hour:8;
	
	dword	min :8;
	dword	sec :8;
	dword	localOffset:16;
	
	dword	startCluster;
	dword	totalCluster;
	dword	unusedByte;
	char	name[ TS_FILE_NAME_SIZE ];
    byte    skip;
    byte    crypt;
    byte	playLst;
    byte    reserved[5];

	void	*handle;
	ulong64	size;
	dword 	currentPos;
} TYPE_File;

#endif

