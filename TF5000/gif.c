#include "tap.h"
#include "gif.h"

#define MAX_COLOR	  256
#define MAX_CODES	  4096

static short curr_size;
static short clear;
static short ending;
static short newcodes;
static short top_slot;
static short slot;
static short navail_bytes = 0;
static short nbits_left = 0;
static byte  b1;
static byte  byte_buff[257];
static byte *pbytes;
static byte *stack;
static byte *suffix;
static word *prefix;
static byte *gifData;

static dword code_mask[13] =
{
   0L,
   0x0001L, 0x0003L,
   0x0007L, 0x000FL,
   0x001FL, 0x003FL,
   0x007FL, 0x00FFL,
   0x01FFL, 0x03FFL,
   0x07FFL, 0x0FFFL
};

static short _get_next_code( void )
{
	short i;
	static dword ret;

	if (!nbits_left)
	{
		if (navail_bytes <= 0)
		{
			pbytes = byte_buff;
			navail_bytes = *gifData++;
			if (navail_bytes)
			{
				for (i = 0; i < navail_bytes; ++i )
					*(byte_buff + i) = *gifData++;
			}
		}
		b1 = *pbytes++;
		nbits_left = 8;
		--navail_bytes;
	}

	ret = b1 >> (8 - nbits_left);
	while (curr_size > nbits_left)
	{
		if (navail_bytes <= 0)
		{
			pbytes = byte_buff;
			navail_bytes = *gifData++;
			if (navail_bytes)
			{
				for( i = 0; i < navail_bytes; ++i )
				  *(byte_buff + i) = *gifData++;
			}
		}
		b1 = *pbytes++;
		ret |= b1 << nbits_left;
		nbits_left += 8;
		--navail_bytes;
	}

	nbits_left -= curr_size;
	return((short)(ret & *(code_mask + curr_size)));
}

typedef void (*FUNC)(void);

int LoadGif( GIF *gif, char *name )
{
	TYPE_File *fp;
	byte	*sp,*OrgBuffer;
	short	code, fc, oc,i,c;
	byte	size;
	int 	bSize;
	byte	*buf;
	dword	fileSize;
	int 	pos=0, x, y;
	dword	heapSize, freeHeapSize, availHeapSize;

	fp = TAP_Hdd_Fopen( name );
	if(fp==NULL)
	{
		return 0;
	}

	fileSize = (dword)(fp->size);
	buf = (byte *)TAP_MemAlloc( fileSize );

	if( buf == 0 )
	{
		TAP_Hdd_Fclose( fp );
		return 0;
	}

	TAP_Hdd_Fread( buf, fileSize, 1, fp );
	TAP_Hdd_Fclose( fp );
	gifData = buf;

	if( gifData[0] != 'G' || gifData[1] != 'I' || gifData[2] != 'F' )
	{
		TAP_MemFree( buf );
		return 0;
	}
	gifData += 6;

	gifData += 7;
	for (i = 0; i < MAX_COLOR; i++)
	{
		gif->lut[i][0] = *gifData++;
		gif->lut[i][1] = *gifData++;
		gif->lut[i][2] = *gifData++;
		gif->lut[i][3] = 0;
	}

	gifData += 5;
	gif->width = gifData[1]*256 + gifData[0];
	gifData += 2;
	gif->height = gifData[1]*256 + gifData[0];
	gifData += 2;

	bSize = ((int)(gif->width) * (int)(gif->height)) + 1; // + (sizeof(short) * 2);

	gif->data = (byte *)TAP_MemAlloc(bSize);
	if( gif->data == NULL )
	{
		TAP_MemFree( buf );
		return 0;
	}

	OrgBuffer = gif->data;

	gifData++;
	size = *gifData++;

	/* not 256 color */
	if (size < 2 || 9 < size)
	{
		TAP_MemFree( buf );
		TAP_MemFree( gif->data );
		return 0;
	}

	TAP_MemInfo( &heapSize, &freeHeapSize, &availHeapSize );
	if( availHeapSize < ( MAX_CODES + 1 ) * 4 )
	{
		TAP_MemFree( buf );
		TAP_MemFree( gif->data );
		return 0;
	}

	stack  = (byte *)TAP_MemAlloc(MAX_CODES + 1);
	suffix = (byte *)TAP_MemAlloc(MAX_CODES + 1);
	prefix = (unsigned short *)TAP_MemAlloc(sizeof(short) * (MAX_CODES + 1));

	curr_size = size + 1;
	top_slot = 1 << curr_size;
	clear = 1 << size;
	ending = clear + 1;
	slot = newcodes = ending + 1;
	navail_bytes = nbits_left = 0;
	oc = fc = 0;
	sp = stack;

	while ( (c = _get_next_code()) != ending )
	{
		if (c == clear)
		{
			curr_size = size + 1;
			slot = newcodes;
			top_slot = 1 << curr_size;
			while ( (c = _get_next_code()) == clear );
			if( c == ending ) break;
			if( c >= slot ) c = 0;
			oc = fc = c;
			*OrgBuffer++ = c;

			 x = pos % gif->width;
			 y = pos / gif->width;
			 pos++;
			//_Pixel( x, y, COLOR( gif->pal[c*3+0]>>3, gif->pal[c*3+1]>>3, gif->pal[c*3+2]>>3 ) );
		}
		else
		{
			code = c;
			if (code >= slot)
			{
				code = oc;
				*sp++ = fc;
			}

			while (code >= newcodes)
			{
				*sp++ = *(suffix + code);
				code = *(prefix + code);
			}

			*sp++ = code;
			if (slot < top_slot)
			{
				*(suffix + slot) = fc = code;
				*(prefix + slot++) = oc;
				oc = c;
			}

			if (slot >= top_slot && curr_size < 12)
			{
				top_slot <<= 1;
				++curr_size;
			}

			while (sp > stack)
			{
				--sp;
				*OrgBuffer++ = *sp;

				c = *sp;
				 x = pos % gif->width;
				 y = pos / gif->width;
				 pos++;
				//_Pixel( x, y, COLOR( gif->pal[c*3+0]>>3, gif->pal[c*3+1]>>3, gif->pal[c*3+2]>>3 ) );
			}
		}
	}

	TAP_MemFree(stack);
	TAP_MemFree(suffix);
	TAP_MemFree(prefix);

	TAP_MemFree( buf );

	return 1;
}

