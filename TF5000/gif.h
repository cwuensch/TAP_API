#ifndef __GIF_H
#define __GIF_H

typedef struct
{
	short	width;
	short	height;
	byte	lut[256][4];
	byte	*data;
} GIF;

int LoadGif( GIF *gif, char *name );

#endif
