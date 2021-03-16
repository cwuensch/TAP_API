#ifndef __LWIN__
#define __LWIN__

typedef struct
{
	dword titleBack;
	dword titleText;
	dword bodyBack;
	dword bodyText;	
	dword border;
	dword shadow;
	dword dark;
	dword light;
	dword check;
} TYPE_WindowColor;

typedef struct
{
	word	rgn;
	byte	fntType;
	byte	fntSize;
	dword	x;
	dword	y;
	dword	w;
	dword	h;
	dword	bodyX;
	dword	bodyY;
	dword	bodyW;
	dword	bodyH;
	TYPE_WindowColor color;

	dword	reserved[4];
}	TYPE_WindowInfo;

typedef void* TYPE_Window;

#endif
