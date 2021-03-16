#ifndef __LWIN__
#define __LWIN__

typedef unsigned short word;
typedef unsigned long dword;

typedef struct
{
	word titleBack;
	word titleText;
	word bodyBack;
	word bodyText;	
	word border;
	word shadow;
	word dark;
	word light;
	word check;
} TYPE_WindowColor;


typedef struct
{
	word  rgn;
	dword x;
	dword y;
	dword w;
	dword h;
	dword titleX;
	dword titleY;
	dword titleW;
	dword titleH;
	dword bodyX;
	dword bodyY;
	dword bodyW;
	dword bodyH;
	TYPE_WindowColor color;
	void  *saveBuf;
	byte  save;
}	TYPE_Win;

#define MAX_ListWindowItem			3500

typedef struct
{
	TYPE_Win win;
	char	*itemBuf;
	char	*item[MAX_ListWindowItem];	//[MAX_ListWindowItemLen];
	byte	check[MAX_ListWindowItem];
	word	idx[MAX_ListWindowItem];
	long	itemNum;
	long	startPos;
	long	currentPos;
	long	maxItemView;
	byte	fntType;
	byte	fntSize;
	byte    bScr;
	byte	onlyEng;
} TYPE_Window;

#endif
