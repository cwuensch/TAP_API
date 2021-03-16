#ifndef __TAP__
#define __TAP__

#include "stddef.h"
#include "type.h"
#include "key.h"
#include "hdd.h"
#include "font.h"
#include "win.h"

#ifdef __cplusplus
extern "C" {
#endif

extern  dword _tap_startAddr;

#define XDATA __attribute__ ((section(".xdata"))) 

#define CHANNEL_Main            1
#define CHANNEL_Sub             0

// --- Event Code -------------------------------------------------------

#define EVT_IDLE                0x000   // param1 = none, param2 = none
#define EVT_KEY                 0x100   // param1 = keyCode, param2 = none
#define EVT_UART                0x200   // param1 = data
#define EVT_RBACK               0x300   // param1 = mode( 0 = start, 1 = end ), 
#define EVT_SVCSTATUS		0x400	// param1 = service status
#define EVT_VIDEO_CONV		0x500

// ---- Service Status Mask -------------------------------------------------------------

#define SVCSTATUS_MASK_MainSub	0x10000000
#define SVCSTATUS_MASK_Error			0x0f000000
#define SVCSTATUS_MASK_Pid				0x00001fff

// ---- OSD -------------------------------------------------------------

#define RGB(r,g,b)	  	( (0x8000) | ((r)<<10) | ((g)<<5) | (b) )
#define ARGB(a,r,g,b)	( (a<<15) | ((r)<<10) | ((g)<<5) | (b))
#define RGB8888(r,g,b)	RGB( (r>>3), (g>>3), (b>>3) )

// default color
// 1555
#define	COLOR_None			ARGB(0,0,0,0)
#define	COLOR_Black			RGB(1,1,1)
#define	COLOR_DarkRed		RGB(16,0,0)
#define	COLOR_DarkGreen		RGB(0,16,0)
#define	COLOR_DarkYellow	RGB(16,16,0)
#define	COLOR_DarkBlue		RGB(0,0,16)
#define	COLOR_DarkMagenta	RGB(16,0,16)
#define	COLOR_DarkCyan		RGB(0, 14, 16 )
#define	COLOR_Gray			RGB(16,16,16)
#define	COLOR_Red			RGB(31,0,0)
#define	COLOR_Green			RGB(0,31,0)
#define	COLOR_Yellow		RGB(31,31,0)
#define	COLOR_Blue			RGB(0,0,31)
#define	COLOR_Magenta		RGB(31,0,31)
#define	COLOR_Cyan			RGB(0,27,31)
#define	COLOR_White			RGB(31,31,31)
#define	COLOR_DarkGray		RGB( 6,6,8 )

// User defined Color
enum
{
	COLOR_User0 = RGB8888(   0,  16,  64 ),
	COLOR_User1 = RGB8888(  12,  28,  76 ),
	COLOR_User2 = RGB8888(  24,  44,  88 ),
	COLOR_User3 = RGB8888(  36,  56, 100 ),
	COLOR_User4 = RGB8888(  48,  72, 112 ),
	COLOR_User5 = RGB8888(  60,  84, 124 ),
	COLOR_User6 = RGB8888(  72,  96, 136 ),
	COLOR_User7 = RGB8888(  84, 112, 148 ),
	COLOR_User8 = RGB8888(  96, 124, 164 ),
	COLOR_User9 = RGB8888( 112, 140, 176 ),
	COLOR_User10= RGB8888( 132, 156, 188 ),
	COLOR_User11= RGB8888( 156, 176, 200 ),
	COLOR_User12= RGB8888( 180, 196, 216 ),
	COLOR_User13= RGB8888( 200, 216, 228 ),
	COLOR_User14= RGB8888( 224, 232, 240 ),
	COLOR_User15= RGB8888( 248, 252, 252 )
};


typedef struct
{
	void *eAddr;
   	void *oAddr;
	word width;
	word height;
   	word bytePerPixel;
	word dataFormat;
	word reserved[4];
} TYPE_OsdBaseInfo;

typedef struct
{
	byte 	version;
	byte 	reserved;
	byte 	dataFormat;
	byte 	compessMethod;
	void* 	data;
	dword 	dataSize;
	word 	width;
	word 	height;
} TYPE_GrData;


typedef enum
{
	COMPRESS_None,
	COMPRESS_Rle,			// Run Length 
	COMPRESS_Tfp			// Topfield pack
} TYPE_GrData_CompressMethod;

typedef enum
{
	OSD_1555,
	OSD_565,
	OSD_8888,
	OSD_4444,
	OSD_256,
	OSD_Default = 0xff
} TYPE_Osd_PixelFormat;

#define OSD_Flag_MemRgn     0x8000
#define OSD_Flag_256        0x4000
#define OSD_Flag_Plane2     0x2000

// ----------------------------------------------------------------------

typedef enum
{
	SVC_TYPE_Tv,
	SVC_TYPE_Radio,
} TYPE_ServiceType;

#define MAX_SatName 	16
#define MAX_SvcName 	((4*7-1)-4)

typedef struct
{
	char    satName[ MAX_SatName ];
	char    chName[ MAX_SvcName ];
	word	flag;
	byte	tunerNum : 2;
	byte	polar : 1;
	byte	ttxAvailable:1;		
	word	freq;
	word	sr;
	word	svcId;
	word	pmtPid;
	word	pcrPid;
	word	videoPid;
	word	audioPid;
	byte	dolbyTrack;		// 0xff = No Dolby Audio, other value = Dolby Track Number
	byte	multifeed;		// 0 = No Multifeed, other value = Subfeed Number

	byte	satIdx;				
	word	orgNetId;			
	word	tsId;				
	word	logicalChNum;		
		
} TYPE_TapChInfo;

typedef struct
{
	word	evtId;				// event ID
	dword	startTime;			// start time((MJD << 16) | (Hour << 8) | Min)
	dword	endTime;
	word	duration;			// duration((Hour << 8) | Min)
	byte	runningStatus;		// running status
	char	eventName[128];
	char	description[128];
	byte	parentalRating; 	// parental Rating
	
	byte	satIdx;				
	word	svcId;				
	word	orgNetId;			
	word	tsId;				
} TYPE_TapEvent;

typedef struct
{
	byte *yAddress;
	byte *cAddress;
	word width;
	word height;
} TYPE_VideoBank;


typedef enum
{
	RESERVE_TYPE_Onetime,
	RESERVE_TYPE_Everyday,
	RESERVE_TYPE_EveryWeekend,
	RESERVE_TYPE_Weekly,
	RESERVE_TYPE_WeekDay,
	N_ReserveType
} TYPE_ReservationType;


typedef struct
{
	byte	isRec;				// 1 = Recording, 0 = VCR Timer
	byte	tuner;				// 0 = Tuner1 , 1 = Tuner2
	byte	svcType;			// 0 = TV, 1 = Radio
	byte	reserved;
	word	svcNum;
	byte	reservationType;	// reservation type, refer TYPE_ReservationType
	byte	nameFix;			// 1 = fileName is fixed
	word	duration;			// Total Recording Time( Minute )
	dword	startTime;			// Reserved Time, (MJD << 16) | (Hour << 8) | Min
	char	fileName[100];
} TYPE_TimerInfo;

typedef enum
{
	RECTYPE_None,					// No Recording 
	RECTYPE_Normal,					// Normal Recording 
	RECTYPE_Timeshift,				// Recording for Time shifting ( Cannot stop )
	RECTYPE_Copy					// Copy
} TYPE_RecType;

typedef enum
{
	PLAYMODE_None,					// No playback started
	PLAYMODE_Playing = 2,			// Normal Playback 
	PLAYMODE_TempPlaying,			// Time shifting
	PLAYMODE_RecPlaying,			// Time shifting in recording service.
	PLAYMODE_Mp3,					// MP3
	N_PLAYMODE
} TYPE_PlayMode;

typedef enum
{
	TRICKMODE_Normal,				// Normal Playback
	TRICKMODE_Forward,				// Fast Forward
	TRICKMODE_Rewind,				// Rewid
	TRICKMODE_Slow,					// Slow Motion
	TRICKMODE_Pause					// Paused
} TYPE_TrickMode;


typedef struct
{
	byte	recType;		// Recording Type, refer TYPE_RecType
	byte	tuner;					// 0 = tuner 1, 1 = tuner 2
	byte	reserved;			
	byte	svcType;				// 0 = TV, 1 = Radio
	word	svcNum;				
	word	duration;				// Total Recording Time ( Minute )
	dword	startTime;				// (MJD << 16) | (Hour << 8) | Min
	dword	endTime;				// (MJD << 16) | (Hour << 8) | Min
	dword	recordedSec;			// Recorded Time ( Sec )
	char	fileName[95];			
}TYPE_RecInfo;

typedef struct
{
	byte	playMode;		// Playback Mode, refer TYPE_PlayMode
	byte 	trickMode;		// Trick Mode, refer TYPE_TrickMode
	byte 	speed;					// playback speed 
	byte	svcType;				// 0 = TV, 1 = Radio
	word	svcNum;
	word	duration;
	dword	currentBlock;
	dword	totalBlock;
	TYPE_File *file;
	TYPE_TapEvent	evtInfo;

	byte	repeatStatus;
	byte	reserved[3];
} TYPE_PlayInfo;


// ----------------------------------------------------------------------

#define MAX_PROGRAM_NAME	64
#define MAX_AUTHOR_NAME		64
#define MAX_DESCRIPTION		128
#define MAX_ETCINFO_STR        64

#define TAP_PROGRAM_NAME(name)  const char __tap_program_name__[MAX_PROGRAM_NAME] __attribute__ ((section("._tap_program_name"))) = (name);
#define TAP_AUTHOR_NAME(name)  const char __tap_author_name__[MAX_AUTHOR_NAME]    __attribute__ ((section("._tap_author_name")))  = (name);
#define TAP_DESCRIPTION(desc)  const char __tap_description__[MAX_DESCRIPTION]    __attribute__ ((section("._tap_description")))  = (desc);
#define TAP_ETCINFO(etc)  const char __tap_etc_str__[MAX_ETCINFO_STR]            __attribute__ ((section("._tap_etcinfo")))      = (etc);
#define TAP_ID(id)  const dword  __tap_ud__                                       __attribute__ ((section("._tap_id")))          = (id);
#define TAP_ATTRIBUTE(attr) const dword __tap_attr__				__attribute__((section("._tap_attribute")))		= (attr);


// ----------------------------------------------------------------------

typedef enum
{
    STATE_Normal,
    STATE_Menu,
    STATE_Epg,
    STATE_List,
    STATE_Ttx,
    STATE_Game,
    STATE_FileList,
    STATE_Tap,
} TYPE_State;

typedef enum
{
	SUBSTATE_MainMenu,
	SUBSTATE_TimeMenu,
	SUBSTATE_TimeSettingMenu,
	SUBSTATE_InstallationMenu,
	SUBSTATE_TimerMenu,
	SUBSTATE_LanguageMenu,
	SUBSTATE_ParentMenu,
	SUBSTATE_ParentLockMenu,
	SUBSTATE_AvMenu,
	SUBSTATE_ChListMenu,
	SUBSTATE_FavChListMenu,
	SUBSTATE_SearchMenu,
	SUBSTATE_LnbSettingMenu,
	SUBSTATE_Diseqc12SettingMenu,
	SUBSTATE_USALSMenu,
	SUBSTATE_CiMenu,
	SUBSTATE_Ci,
	SUBSTATE_CiSlotMenu,
	SUBSTATE_SatSearch,
	SUBSTATE_TpSearch,
	SUBSTATE_SmatvSearch,
	SUBSTATE_ChannelEditMenu,
	SUBSTATE_InformationMenu,
	SUBSTATE_SystemMenu,
	SUBSTATE_GameMenu,
	SUBSTATE_OtaMenu,
	SUBSTATE_IrdStatus,
	SUBSTATE_Carlendar,
	SUBSTATE_PvrRecord,
	SUBSTATE_PvrReservation,
	SUBSTATE_ReservationList,
	SUBSTATE_Normal,
	SUBSTATE_Audio,
	SUBSTATE_Subt,
	SUBSTATE_Ttx,
	SUBSTATE_Fav,
	SUBSTATE_Sat,
	SUBSTATE_PvrTimeSearch,
	SUBSTATE_PvrPlayingSearch,
	SUBSTATE_PvrRecSearch,
	SUBSTATE_PipList,
	SUBSTATE_Multifeed,
	SUBSTATE_List,
	SUBSTATE_Epg,
	SUBSTATE_Game,
	SUBSTATE_PvrList,
	SUBSTATE_ExeList,
	SUBSTATE_Exec,
	SUBSTATE_TtxEmul,
} TYPE_SubState;

typedef enum
{
	FREQ_16K = 0,
	FREQ_22K05,
	FREQ_24K,
	FREQ_32K,
	FREQ_44K1,
	FREQ_48K,
} TYPE_PCM_Freq;


typedef enum
{
	SYSVAR_Vol,
	SYSVAR_OsdLan,
	SYSVAR_SubLan,
	SYSVAR_AudLan,
	SYSVAR_TvType,
	SYSVAR_VideoOut,
	SYSVAR_ScartType,
	SYSVAR_TvRatio,
	SYSVAR_16_9_Display,
	SYSVAR_SoundMode,
	SYSVAR_UhfType,
	SYSVAR_UhfCh,
	SYSVAR_OsdAlpha,
	SYSVAR_IBoxTime,
	SYSVAR_IBoxPos,
	SYSVAR_Timeshift,
} TAP_SysVarId;

#define MAX_Vol 		17
#define MAX_IBoxPos		3
#define MIN_IBoxPos		-10

typedef enum
{
	LAN_English,
	LAN_French,
	LAN_German,
	LAN_Italy,
	LAN_Spain,
 	LAN_Arab,
	LAN_Greek,
	LAN_Turk,
	LAN_Danish,
	LAN_Swedish,
	LAN_Norwegian,
	LAN_Dutch,
	LAN_Russian,
	LAN_Polish,
	LAN_Iran,

      N_OsdLan
}   TYPE_Language;

typedef enum
{
	TVTYPE_Auto,
	TVTYPE_Pal,
	TVTYPE_Ntsc,
	N_TvType
} TYPE_TvType;

// sound mode
typedef enum
{
	SOUND_MODE_Stereo,
	SOUND_MODE_Mono,
	SOUND_MODE_Left,
	SOUND_MODE_Right,
	N_SoundMode
}	TYPE_SoundMode;

// screen ratio
typedef enum
{
	SCREEN_RATIO_4_3,
	SCREEN_RATIO_16_9,
	N_ScreenRatio
}	TYPE_ScreenRatio;

typedef enum
{
	VIDEO_TYPE_Cvbs,
	VIDEO_TYPE_Rgb,
	VIDEO_TYPE_Svhs,
	VIDEO_TYPE_Yuv,
	N_VideoType
} TYPE_VideoType;

// 16_9_Display
typedef enum
{
	DISPLAY_MODE_LetterBox,
	DISPLAY_MODE_CenterExtract,
} TYPE_16_9_DISPLAY;

// System Osd ID
typedef enum
{
	SYSOSD_InfoBox,
	SYSOSD_PvrInfo,
	SYSOSD_VolumeBar,
	SYSOSD_ServiceStatus,
} TYPE_TapSysOsdId;

// Playback Repeat Status
typedef enum
{
	REPEAT_None,
	REPEAT_Region,
	REPEAT_Total,
	N_RepeatMode
} TYPE_RepeatMode;

// VFD Status
typedef enum
{
	VFD_NotSupport,
	VFD_LedEmulMode,
	VFD_VfdMode
} TYPE_VFD_Status;

// -- SYSTEM FUNCTION ---------------------------------------------------
extern	void	(*TAP_SystemProc)(void);
extern  dword	(*TAP_GetState)( dword *state, dword *subState );
extern	void	(*TAP_ExitNormal)( void );
extern	void	(*TAP_EnterNormal)( void );
extern	void	(*TAP_Exit)(void);

extern	byte	(*TAP_KbHit)(void);
extern	byte	(*TAP_GetCh)(void);
extern	void	(*TAP_PutCh)(byte c);
extern	void (*TAP_PutByte)(byte c);
extern	void	(*TAP_PrintSys)(const void *fmt, ...);
extern	void	(*TAP_Print)(const void *fmt, ...);

extern	void	(*TAP_SysOsdControl)( TYPE_TapSysOsdId osdId, bool ctrl );
extern	void	(*TAP_SetBaudRate)( dword baudRate );
extern	word	(*TAP_SetBk)( bool onOff );

// -- COMMON FUNCTION ---------------------------------------------------
extern	int	    (*TAP_SetSoundLevel)(byte soundLevel);
extern	int	    (*TAP_GetTime)(word *mjd, byte *hour, byte *min, byte *sec);
extern	void	(*TAP_MemInfo)(dword *heapSize, dword *freeHeapSize, dword *availHeapSize);
extern	void*	(*TAP_MemAlloc)(dword size);
extern	int	    (*TAP_MemFree)(const void *addr);
extern	dword	(*TAP_GetTick)(void);
extern	void	(*TAP_Delay)(dword dm10);
extern	int	    (*TAP_ExtractMjd)(word mjd, word *year, byte *month, byte *day, byte *weekDay);
extern	int	    (*TAP_MakeMjd)(word year, byte month, byte day);
extern	long	(*TAP_Sin)( long mul, long th );
extern	long	(*TAP_Cos)( long mul, long th );
extern	void	(*TAP_SPrint)(void *s, const void *fmt, ...);
extern	int 	(*TAP_GetSignalLevel)(void);
extern	int 	(*TAP_GetSignalQuality)(void);
extern  int 	(*TAP_SetInfoboxTime)( int sec );
extern  int		(*TAP_PlayPCM)( void *pcmdata, int size, int freq, void (*Callback)(void) );
extern	int 	(*TAP_CaptureScreen)( int mainSub, TYPE_VideoBank *videoBank );

extern	int 	(*TAP_SetSystemVar)( int varId, int value );
extern	int 	(*TAP_GetSystemVar)( int varId );
extern	int 	(*TAP_WriteSystemVar)( void );
extern	void	(*TAP_GenerateEvent)(  word evtCode, dword param1, dword param2 );

// -- OSD FUNCTION ---------------------------------------------------
extern	int	(*TAP_Osd_Create)( dword x, dword y, dword w, dword h, byte lutIdx, int flag );
extern	int	(*TAP_Osd_Delete)(word rgn);
extern	int	(*TAP_Osd_Move)(word rgn, dword x, dword y);
extern	int	(*TAP_Osd_FillBox)(word rgn, dword x, dword y, dword w, dword h, dword color);
extern	int	(*TAP_Osd_PutBox)(word rgn, dword x, dword y, dword w, dword h, const void *data, bool sprite, byte dataFormat );
extern	int	(*TAP_Osd_GetBox)(word rgn, dword x, dword y, dword w, dword h, void *data);
extern	int	(*TAP_Osd_SetLut)(byte lutIdx, byte lut[][4] );
extern	int	(*TAP_Osd_Ctrl)(word rgn, dword ctrl);
extern	int	(*TAP_Osd_SetTransparency)( word rgn, char rt);

extern	int	(*TAP_Osd_Draw3dBox)( word rgn, dword x, dword y, dword w, dword h, dword c1, dword c2 );
extern	int	(*TAP_Osd_Draw3dBoxFill)( word rgn, dword x, dword y, dword w, dword h, dword c1, dword c2, dword fc );

extern	int	(*TAP_Osd_DrawRectangle)(word rgn, dword x, dword y, dword w, dword h, dword t, dword color);
extern	int	(*TAP_Osd_DrawPixmap)(word rgn, dword x, dword y, dword w, dword h, void *pixmap, bool sprite, byte dataFormat );
extern  int (*TAP_Osd_Zoom)( int xzoom, int yzoom );
extern  int (*TAP_Osd_GetBaseInfo)( TYPE_OsdBaseInfo *info );
extern	int (*TAP_Osd_Copy)(word srcRgnNum, word dstRgnNum, dword srcX, dword srcY, dword w, dword h, dword dstX, dword dstY,  bool sprite);
//extern  int	(*TAP_Osd_PutGd__)(word rgn, int x, int y, TYPE_GrData * gd, bool sprite);
extern  int	TAP_Osd_PutGd(word rgn, int x, int y, TYPE_GrData * gd, bool sprite);

extern	byte*	(*TAP_Osd_SaveBox)( word rgn, dword x, dword y, dword w, dword h );
extern	void	(*TAP_Osd_RestoreBox)( word rgn, dword x, dword y, dword w, dword h, void *data );

extern	int	(*TAP_Osd_GetPixel)( word rgn, dword x, dword y, void *pix );
extern	int	(*TAP_Osd_PutPixel)( word rgn, dword x, dword y, dword pix );

// -- HDD FUNCTION ---------------------------------------------------

extern	TYPE_File*	(*TAP_Hdd_Fopen)( char *name );
extern	dword		(*TAP_Hdd_Fread)( void *buf, dword blksize, dword blk, TYPE_File *file );
extern	dword		(*TAP_Hdd_Fwrite)( void *buf, dword blksize, dword blk, TYPE_File *file );
extern	void		(*TAP_Hdd_Fclose)( TYPE_File *file );
extern	dword		(*TAP_Hdd_FindFirst)( TYPE_File *file );
extern	dword		(*TAP_Hdd_FindNext)( TYPE_File *file );
extern	dword		(*TAP_Hdd_Fseek)( TYPE_File *file, long pos, long where );
extern	dword		(*TAP_Hdd_Flen)( TYPE_File *file );
extern	dword		(*TAP_Hdd_Ftell)( TYPE_File *file );
extern	dword		(*TAP_Hdd_TotalSize)( void );
extern	dword		(*TAP_Hdd_FreeSize)( void );
extern	word		(*TAP_Hdd_Delete)( char *name );
extern	bool		(*TAP_Hdd_Exist)( char *name );
extern	dword		(*TAP_Hdd_Create)( char *name, byte attr );
extern	word		(*TAP_Hdd_ChangeDir)( char *dir );

extern	int			(*TAP_Hdd_PlayTs)( char *name );
extern	int			(*TAP_Hdd_StopTs)( void);
extern	int			(*TAP_Hdd_PlayMp3)( char *name );
extern	int			(*TAP_Hdd_StopMp3)( void );
extern	bool		(*TAP_Hdd_Rename)(   	char *oldName, char *newName );

extern	bool		(*TAP_Hdd_StartRecord)( void );
extern	bool		(*TAP_Hdd_StopRecord)( byte recSlot );
extern	bool		(*TAP_Hdd_GetRecInfo)( byte recSlot, TYPE_RecInfo *recInfo );
extern	bool		(*TAP_Hdd_GetPlayInfo)( TYPE_PlayInfo *playInfo );
extern	bool		(*TAP_Hdd_GetHddID)(char *modelNo, char *serialNo);

extern	bool		(*TAP_Hdd_ChangePlaybackPos)( dword blockPos );
extern	bool		(*TAP_Hdd_GotoBookmark)( void );
extern	bool		(*TAP_Hdd_SetBookmark)( void );

// -- STRING FUNCTION ---------------------
extern  int	(*TAP_Osd_PutS)(word rgn, dword x, dword y, dword maxX, const char * str, word fcolor, word bcolor, byte fntType, byte fntSize, byte bDot, byte align);
extern	int	(*TAP_Osd_GetW)( const char *str, byte fntType, byte fntSize );
extern  int	(*TAP_Osd_PutString)(word rgn, dword x, dword y, dword maxX, const char * str, word fcolor, word bcolor, byte fntType, byte fntSize, byte nextLine);
extern  int	(*TAP_Osd_DrawString)(const char * str, dword dstWidth, word color, byte * dest, dword maxWidth, byte fntType, byte fntSize);
extern  int	(*TAP_Osd_PutStringAf)(word rgn, dword x, dword y, dword maxX, const char * str, word fcolor, word bcolor, byte fntType, byte fntSize, byte nextLine);

// -- WINDOW FUNCTION ---------------------------------------------------
extern	void	(*TAP_Win_SetTitle)( TYPE_Window *win, const char *str, byte fntType, byte fntSize );
extern  void	(*TAP_Win_SetColor)(TYPE_Window * win, word titleBack, word titleText, word bodyBack, word bodyText, word border, word shadow, word dark, word light);
extern	void	(*TAP_Win_SetDefaultColor)( TYPE_Window *win );
extern	void	(*TAP_Win_Draw) 	( TYPE_Window *win );
extern	void	(*TAP_Win_Create)	( TYPE_Window *win, word rgn, dword x, dword y, dword w, dword h, byte save, byte bScr );
extern	dword	(*TAP_Win_Delete)	( TYPE_Window *win );
extern	void	(*TAP_Win_SetFont)	( TYPE_Window *win, byte fntType, byte fntSize );
extern	void	(*TAP_Win_AddItem)	( TYPE_Window *win, char *str );
extern	dword	(*TAP_Win_GetSelection)( TYPE_Window *win );
extern	void	(*TAP_Win_SetSelection)( TYPE_Window *win, dword pos );
extern	void	(*TAP_Win_Action)	( TYPE_Window *win, dword key );

typedef void (*TYPE_DrawItemFunc)( TYPE_Window *win, dword itemNo );

extern	void	(*TAP_Win_SetAvtice)( TYPE_Window *win, dword itemNo, byte active );
extern	void	(*TAP_Win_SetDrawItemFunc)( TYPE_Window *win, TYPE_DrawItemFunc func );


// ---------------------------------------------------------------------

extern	int (*TAP_Channel_GetTotalNum)( int *nTvSvc, int *nRadioSvc );
extern	int (*TAP_Channel_GetFirstInfo)( int svcType, TYPE_TapChInfo *chInfo );
extern	int (*TAP_Channel_GetNextInfo)( TYPE_TapChInfo *chInfo );
extern	int (*TAP_Channel_GetInfo)( int svcType, int svcNum, TYPE_TapChInfo *chInfo );
extern	int (*TAP_Channel_GetCurrent)( int *tvRadio, int *svcNum );
extern	int (*TAP_Channel_GetCurrentSubTV)(int *svcNum );
extern  int (*TAP_Channel_Start)( int mainSub, int svcType, int chNum );
extern  int (*TAP_Channel_Scale)( int mainSub, long x, long y, long w, long h, bool anim );
extern  int (*TAP_Channel_IsPlayable)( int mainSub, int svcType, int chNum );
extern  int (*TAP_Channel_Move)( int mainSub, int dir );
extern  int (*TAP_Channel_Stop)( int mainSub );
extern  int (*TAP_Channel_GetTotalAudioTrack)( void );
extern  char *(*TAP_Channel_GetAudioTrackName)( int trkNum, char *trkName );
extern  int (*TAP_Channel_SetAudioTrack)( int trkNum );
extern  int (*TAP_Channel_GetTotalSubtitleTrack)( void );
extern  char *(*TAP_Channel_GetSubtitleTrackName)( int trkNum, char *trkName );
extern  int (*TAP_Channel_SetSubtitleTrack)( int trkNum );
extern  bool (*TAP_Channel_IsStarted)( int mainSub );

// --- EPG FUNCTIONS ---------------------------------------------------

extern	TYPE_TapEvent*	(*TAP_GetEvent)( int svcType, int svcNum, int *eventNum );
extern	TYPE_TapEvent*	(*TAP_GetCurrentEvent)( int svcType, int svcNum );
extern	bool (*TAP_PutEvent)( byte *eitData );

extern	word (*TAP_ControlEit)( bool enable );

extern	bool (*TAP_EPG_UpdateEvent)(  int svcType, int svcNum, dword evtid, dword runningStatus );
extern	bool (*TAP_EPG_DeleteEvent)(  int svcType, int svcNum, dword evtid );
extern	byte *(*TAP_EPG_GetExtInfo)( TYPE_TapEvent *tapEvtInfo );


// --- USB FUNCTIONS ---------------------------------------------------

extern void (*TAP_Usb_Read)( byte *pBuff, word size, void (*pFunc)(word size) );
extern void (*TAP_Usb_Write)( byte *pBuff, word size, void (*pFunc)(word size) );
extern void (*TAP_Usb_PacketRead)( byte *pBuff, word size, word (*pFunc)(word size) );
extern void (*TAP_Usb_PacketWrite)( byte *pBuff, word size, void (*pFunc)(word size), dword cmd );
extern void (*TAP_Usb_Cancel)(void);

// --- TIMER FUNCTIONS ---------------------------------------------------

extern int  (*TAP_Timer_GetTotalNum)( void );
extern bool (*TAP_Timer_GetInfo)( int entryNum, TYPE_TimerInfo *info );
extern int (*TAP_Timer_Add)( TYPE_TimerInfo *info );
extern int (*TAP_Timer_Modify)( int entryNum, TYPE_TimerInfo *info );
extern bool (*TAP_Timer_Delete)( int entryNum );

// --- VFD FUNCTIONS ---------------------------------------------------

extern int (*TAP_Vfd_GetStatus)( void );
extern void (*TAP_Vfd_Control)( bool underTapCtrl );
extern void (*TAP_Vfd_SendData)( byte *data, byte dataLen );

// ---------------------------------------------------------------------

#define sprintf	TAP_SPrint
#define malloc  TAP_MemAlloc
#define free    TAP_MemFree

// ---------------------------------------------------------------------

#ifdef __cplusplus
};
#endif

#endif
