#ifndef A_FONT_H
#define A_FONT_H

typedef enum
{
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT
} TYPE_Align;

typedef enum
{
	FNT_Size_1419,
	FNT_Size_1622,
	FNT_Size_1926,
	N_FntSize
} TYPE_FontSize;

#define TAP_Osd_PutString1419( r, x, y, mx, str, fc, bc ) TAP_Osd_PutString( r, x, y, mx, str, fc, bc, 0, FNT_Size_1419, 0 )
#define TAP_Osd_PutString1622( r, x, y, mx, str, fc, bc ) TAP_Osd_PutString( r, x, y, mx, str, fc, bc, 0, FNT_Size_1622, 0 )
#define TAP_Osd_PutString1926( r, x, y, mx, str, fc, bc ) TAP_Osd_PutString( r, x, y, mx, str, fc, bc, 0, FNT_Size_1926, 0 )

#define TAP_Osd_DrawString1419( s, w, c, d, mx )  TAP_Osd_DrawString( s, w, c, d, mx, 0, FNT_Size_1419 )
#define TAP_Osd_DrawString1622( s, w, c, d, mx )  TAP_Osd_DrawString( s, w, c, d, mx, 0, FNT_Size_1622 )
#define TAP_Osd_DrawString1926( s, w, c, d, mx )  TAP_Osd_DrawString( s, w, c, d, mx, 0, FNT_Size_1926 )

#define TAP_Osd_PutStringAf1419( r, x, y, mx, str, fc, bc )  TAP_Osd_PutStringAf( r, x, y, mx, str, fc, bc, 0, FNT_Size_1419, 0 )
#define TAP_Osd_PutStringAf1622( r, x, y, mx, str, fc, bc )  TAP_Osd_PutStringAf( r, x, y, mx, str, fc, bc, 0, FNT_Size_1622, 0 )
#define TAP_Osd_PutStringAf1926( r, x, y, mx, str, fc, bc )  TAP_Osd_PutStringAf( r, x, y, mx, str, fc, bc, 0, FNT_Size_1926, 0 )

#define TAP_Osd_GetW1419( s )  TAP_Osd_GetW( s, 0, FNT_Size_1419 )
#define TAP_Osd_GetW1622( s )  TAP_Osd_GetW( s, 0, FNT_Size_1622 )
#define TAP_Osd_GetW1926( s )  TAP_Osd_GetW( s, 0, FNT_Size_1926 )

#endif	// A_FONT_H

