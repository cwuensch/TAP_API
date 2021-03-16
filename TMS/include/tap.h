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

#define CHANNEL_Main            1
#define CHANNEL_Sub             0

// --- Event Code -------------------------------------------------------

#define EVT_IDLE            0x000   // param1 = none, param2 = none
#define EVT_KEY             0x100   // param1 = keyCode, param2 = none
#define EVT_UART            0x200   // param1 = data
#define EVT_RBACK           0x300   // param1 = mode( 0 = start, 1 = end ), 
#define EVT_SVCSTATUS       0x400   // param1 = service status
#define EVT_VIDEO_CONV      0x500
#define EVT_DEMUX           0x800   // param1 = demux handle, param2 = result

#define EVT_STOP            0x900   // param1 = mode ( 0 = poweroff, 1 = user)
// ---- Service Status Mask -------------------------------------------------------------

#define SVCSTATUS_MASK_MainSub  0x10000000
#define SVCSTATUS_MASK_Error    0x0f000000
#define SVCSTATUS_MASK_Pid      0x00001fff

// ---- OSD -------------------------------------------------------------
#define BASE_PLANE  0   // osd base, ttx
#define SUBT_PLANE  1   // subtitle
#define TAP_PLANE   2   // tap

#define JPEG_OPTION_KEEP_RATIO      0x20

#ifndef TAP_ALPHA
#define TAP_ALPHA	0xFF
#endif

#define ARGB(a,r,g,b)   ((dword)(((a)<<24) | ((r)<<16) | ((g)<<8) | (b<<0)))
#define RGB8888(r,g,b)  ARGB(TAP_ALPHA, r, g, b)
#define RGB1555(r,g,b)  ((0x8000) | ((r)<<10) | ((g)<<5) | (b))

#ifdef OLD_STYLE_COLOR
#define RGB(r,g,b)      RGB8888((r)<<3, (g)<<3, (b)<<3)
#else
#define RGB(r,g,b)      RGB8888(r, g, b)
#endif

// default color
// 8888
#define COLOR_None          ARGB(0,0,0,0)
#define COLOR_Black         RGB8888( 16, 16, 16)
#define COLOR_DarkRed       RGB8888(128,  0,  0)
#define COLOR_DarkGreen     RGB8888(  0,128,  0)
#define COLOR_DarkYellow    RGB8888(128,128,  0)
#define COLOR_DarkBlue      RGB8888(  0,  0,128)
#define COLOR_DarkMagenta   RGB8888(128,  0,128)
#define COLOR_DarkCyan      RGB8888(  0,128,128)
#define COLOR_Gray          RGB8888(128,128,128)
#define COLOR_Red           RGB8888(255,  0,  0)
#define COLOR_Green         RGB8888(  0,255,  0)
#define COLOR_Yellow        RGB8888(255,255,  0)
#define COLOR_Blue          RGB8888(  0,  0,255)
#define COLOR_Magenta       RGB8888(255,  0,255)
#define COLOR_Cyan          RGB8888(  0,255,255)
#define COLOR_White         RGB8888(255,255,255)
#define COLOR_DarkGray      RGB8888( 64, 64, 64)

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
    void    *frameBuffer;
    word    width;
    word    height;
    word    bytePerPixel;
    word    dataFormat;
    byte    enabled;
    byte    visible;
    int     zorder;
} TYPE_OsdBaseInfo;

typedef struct
{
    byte     version;
    byte     reserved;
    byte     dataFormat;
    byte     compessMethod;
    void*    data;
    dword    dataSize;
    word     width;
    word     height;
} TYPE_GrData;


typedef enum
{
    COMPRESS_None,
    COMPRESS_Rle,       // Run Length 
    COMPRESS_Tfp        // Topfield pack
} TYPE_GrData_CompressMethod;

typedef enum
{
    OSD_1555,
    OSD_8888,
    OSD_256,
    OSD_Default = 0xff
} TYPE_Osd_PixelFormat;

#define OSD_Flag_MemRgn     0x8000
#define OSD_Flag_256        0x4000
#define OSD_Flag_PlaneSubt  0x2000  // plane for subtitle
#define OSD_Flag_PlaneBase  0x1000  // plane for main osd

// ----------------------------------------------------------------------

typedef enum
{
    SVC_TYPE_Tv,
    SVC_TYPE_Radio,
} TYPE_ServiceType;

#define MAX_SatName     16
#define MAX_SvcName     ((4*7-1)-4)

// modulation system    : 1 bit
#define DVB_S               0x0
#define DVB_S2              0x1

// modulation type      : 2 bit
#define MODULATION_AUTO     0x0
#define MODULATION_QPSK     0x1
#define MODULATION_8PSK     0x2
#define MODULATION_16QAM    0x3

// FEC inner            : 4 bit
#define FEC_AUTO            0x0
#define FEC_1_2             0x1
#define FEC_2_3             0x2
#define FEC_3_4             0x3
#define FEC_5_6             0x4
#define FEC_7_8             0x5
#define FEC_8_9             0x6
#define FEC_3_5             0x7
#define FEC_4_5             0x8
#define FEC_9_10            0x9
#define FEC_RESERVED        0xa
#define FEC_NO_CONV         0xf

// pilot
#define PILOT_OFF           0
#define PILOT_ON            1

//audio & video format
#define STREAM_AUDIO_MP3                0x01
#define STREAM_AUDIO_MPEG1              0x03
#define STREAM_AUDIO_MPEG2              0x04
#define STREAM_AUDIO_MPEG4_AC3_PLUS     0x06
#define STREAM_AUDIO_MPEG4_AAC          0x0F
#define STREAM_AUDIO_MPEG4_AAC_PLUS     0x11
#define STREAM_AUDIO_MPEG4_AC3          0x81
#define STREAM_AUDIO_MPEG4_DTS          0x82

#define STREAM_VIDEO_MPEG1              0x01
#define STREAM_VIDEO_MPEG2              0x02
#define STREAM_VIDEO_MPEG4_PART2        0x10
#define STREAM_VIDEO_MPEG4_H263         0x1A
#define STREAM_VIDEO_MPEG4_H264         0x1B
#define STREAM_VIDEO_VC1                0xEA
#define STREAM_VIDEO_VC1SM              0xEB

#define STREAM_UNKNOWN                  0xFF

typedef struct
{
    char    satName[ MAX_SatName ];
    char    chName[ MAX_SvcName ];
    word    flag;
    byte    tunerNum : 2;
    byte    polar : 1;
    byte    ttxAvailable:1;
    word    freq;
    word    sr;
    byte    modSystem:1;    //modulation system.
    byte    modType:2;      //modulation type. only effective for DVB-S2 mode.
    byte    fecInner:4;     //fec inner for DVB-S2
    byte    pilot:1;        //pilot for DVB-S2
    byte    satIdx;
    word    svcId;
    word    pmtPid;
    word    pcrPid;
    word    videoPid;
    word    audioPid;
    byte    vformat;
    byte    aformat;
    byte    dolbyTrack;     // 0xff = No Dolby Audio, other value = Dolby Track Number
    byte    multifeed;      // 0 = No Multifeed, other value = Subfeed Number
    word    orgNetId;
    word    tsId;
    word    logicalChNum;
   	dword   reserved[2];    
} TYPE_TapChInfo;

typedef struct
{
    word    evtId;          // event ID
    dword   startTime;      // start time((MJD << 16) | (Hour << 8) | Min)
    dword   endTime;
    word    duration;       // duration((Hour << 8) | Min)
    byte    runningStatus;  // running status
    char    eventName[128];
    char    description[128];
    byte    parentalRating; // parental Rating

    byte    satIdx;
    word    svcId;
    word    orgNetId;
    word    tsId;
} TYPE_TapEvent;

typedef struct
{
    void *data;
    dword pixelFormat;
    dword width;
    dword height;
} TYPE_VideoFrame;

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
    byte    isRec;              // 1 = Recording, 0 = VCR Timer
    byte    tuner;              // 0 = Tuner1 , 1 = Tuner2
    byte    svcType;            // 0 = TV, 1 = Radio
    byte    reserved;
    word    svcNum;
    byte    reservationType;    // reservation type, refer TYPE_ReservationType
    byte    nameFix;            // 1 = fileName is fixed
    word    duration;           // Total Recording Time( Minute )
    dword   startTime;          // Reserved Time, (MJD << 16) | (Hour << 8) | Min
    char    fileName[MAX_FILE_NAME_SIZE + 1];
} TYPE_TimerInfo;

typedef enum
{
    RECTYPE_None,               // No Recording 
    RECTYPE_Normal,             // Normal Recording 
    RECTYPE_Timeshift,          // Recording for Time shifting ( Cannot stop )
    RECTYPE_Copy                // Copy
} TYPE_RecType;

typedef enum
{
    PLAYMODE_None,              // No playback started
    PLAYMODE_Playing = 2,       // Normal Playback 
    PLAYMODE_TempPlaying,       // Time shifting
    PLAYMODE_RecPlaying,        // Time shifting in recording service.
    PLAYMODE_Mp3,               // MP3
    N_PLAYMODE
} TYPE_PlayMode;

typedef enum
{
    TRICKMODE_Normal,           // Normal Playback
    TRICKMODE_Forward,          // Fast Forward
    TRICKMODE_Rewind,           // Rewid
    TRICKMODE_Slow,             // Slow Motion
    TRICKMODE_Pause             // Paused
} TYPE_TrickMode;


typedef struct
{
    byte    recType;            // Recording Type, refer TYPE_RecType
    byte    tuner;              // 0 = tuner 1, 1 = tuner 2
    byte    reserved;
    byte    svcType;            // 0 = TV, 1 = Radio
    word    svcNum;
    word    duration;           // Total Recording Time ( Minute )
    dword   startTime;          // (MJD << 16) | (Hour << 8) | Min
    dword   endTime;            // (MJD << 16) | (Hour << 8) | Min
    dword   recordedSec;        // Recorded Time ( Sec )
    char    fileName[MAX_FILE_NAME_SIZE + 1];
}TYPE_RecInfo;

typedef struct
{
    byte    playMode;           // Playback Mode, refer TYPE_PlayMode
    byte    trickMode;          // Trick Mode, refer TYPE_TrickMode
    byte    speed;              // playback speed 
    byte    svcType;            // 0 = TV, 1 = Radio
    word    svcNum;
    word    duration;
    byte    durationSec;
    byte    reserved;    
    dword   currentBlock;
    dword   totalBlock;
    TYPE_File *file;
    TYPE_TapEvent   evtInfo;

    byte    repeatStatus;
    byte    reserved2[3];
} TYPE_PlayInfo;


#define DEMUX_FILTER_TABLE      0
#define DEMUX_FILTER_ONESHOT    1
#define DEMUX_FILTER_REPEAT     0xFF
typedef struct
{
    word pid;
    byte filterVal[8];          // filterVal[0,1,2,3...] => section[0,3,4,5...] 
    byte filterMask[8];
    byte nSec;                  // section count. 0:table loading, 0xff:repeat mode
    word timeOut;               // * 100ms
} TYPE_DemuxFilter;


typedef void* TYPE_WavHandle;

// ----------------------------------------------------------------------

#define MAX_PROGRAM_NAME    64
#define MAX_AUTHOR_NAME     64
#define MAX_DESCRIPTION     128
#define MAX_PROGRAM_VERSION 64 // 64 (Firebird)
#define MAX_ETCINFO_STR     64

#define TAP_PROGRAM_NAME(name) const char __tap_program_name__[MAX_PROGRAM_NAME] __attribute__ ((section("._tap_program_name"))) = (name)
#define TAP_AUTHOR_NAME(name)  const char __tap_author_name__[MAX_AUTHOR_NAME]   __attribute__ ((section("._tap_author_name")))  = (name)
#define TAP_DESCRIPTION(desc)  const char __tap_description__[MAX_DESCRIPTION]   __attribute__ ((section("._tap_description")))  = (desc)
#define TAP_PROGRAM_VERSION(name) const char __tap_program_version__[MAX_PROGRAM_VERSION] __attribute__ ((section("._tap_program_version"))) = (name)  // Firebird
#define TAP_ETCINFO(etc)       const char __tap_etc_str__[MAX_ETCINFO_STR]       __attribute__ ((section("._tap_etcinfo")))      = (etc)
#define TAP_ID(id)             const dword  __tap_ud__                           __attribute__ ((section("._tap_id")))           = (id)
#define TAP_ATTRIBUTE(attr)    const dword __tap_attr__                          __attribute__((section("._tap_attribute")))     = (attr)

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
    SUBSTATE_SysRecoverMenu,
    SUBSTATE_FirmUpgradeMenu,
    SUBSTATE_TransferMenu,	
    SUBSTATE_TimerMenu,
    SUBSTATE_LanguageMenu,
    SUBSTATE_RecordingSetMenu,
    SUBSTATE_PlaybackMenu,
    SUBSTATE_OsdSettingMenu,
    SUBSTATE_ParentMenu,
    SUBSTATE_ParentLockMenu,
    SUBSTATE_AvMenu,
    SUBSTATE_OtherSettingMenu,
    SUBSTATE_EditServiceListMenu,
    SUBSTATE_EditFavoriteListMenu,
    SUBSTATE_SearchMenu,
    SUBSTATE_SearchModeMenu,
    SUBSTATE_LnbSettingMenu,
    SUBSTATE_Diseqc12SettingMenu,
    SUBSTATE_USALSMenu,
    SUBSTATE_CiMenu,
    SUBSTATE_Ci,
    SUBSTATE_CiSlotMenu,
    SUBSTATE_SatSearch,
    SUBSTATE_TpSearch,
    SUBSTATE_QuickSearch,
    SUBSTATE_SmatvSearch,
    SUBSTATE_FastScan,
    SUBSTATE_Normal,
    SUBSTATE_ServiceList,
    SUBSTATE_Epg,
    SUBSTATE_Fav,
    SUBSTATE_Sat,
    SUBSTATE_Audio,
    SUBSTATE_Subt,
    SUBSTATE_Ttx,
    SUBSTATE_SystemStatus,
    SUBSTATE_InformationMenu,
    SUBSTATE_SettingMenu,
    SUBSTATE_GameMenu,
    SUBSTATE_CanalEpgMenu,
    SUBSTATE_Game,
    SUBSTATE_AntenaSettingMenu,
    SUBSTATE_PositionSettingMenu,
    SUBSTATE_PvrList,
    SUBSTATE_PvrRecord,
    SUBSTATE_PvrTimeSearch,
    SUBSTATE_PvrPlayingSearch,
    SUBSTATE_PvrRecSearch,
    SUBSTATE_Exec,
    SUBSTATE_PipList,
    SUBSTATE_EditServicesMenu,
    SUBSTATE_TtxEmul,
    SUBSTATE_ConaxMenu,
    SUBSTATE_NorConax,
    SUBSTATE_ConaxSubscription,
    SUBSTATE_EventSts,
    SUBSTATE_ConaxCaPin,
    SUBSTATE_ConaxSignPin,
    SUBSTATE_MatRating,
    SUBSTATE_CaInfo,
    SUBSTATE_RateLock,
    SUBSTATE_TokenSts,
    SUBSTATE_DebitSts,
    SUBSTATE_CreditSts,
    SUBSTATE_TokenPPV,
    SUBSTATE_MailBox,  // conax cas message
    SUBSTATE_OtaFirmUpMenu,
    SUBSTATE_NetSettingMenu,
    SUBSTATE_IPSettingMenu,
    SUBSTATE_NetFirmUpMenu,
    SUBSTATE_LANMenu,
    SUBSTATE_LANStatusMenu,
    SUBSTATE_LANIPConfigMenu,
    SUBSTATE_ServiceCopyMenu,
    SUBSTATE_Multifeed,
    SUBSTATE_NVOD,
    SUBSTATE_GetBer,
    SUBSTATE_SimpleLang,
    SUBSTATE_SSUMenu,
    SUBSTATE_CheckSSU,
    SUBSTATE_TimerModify,
    SUBSTATE_CanalEpgRetrieve,
    SUBSTATE_QuickRecWin,
    SUBSTATE_PinCode,   
    SUBSTATE_EXTSignalBar,
    SUBSTATE_DelTimerEntry,
    SUBSTATE_SysMsg,
    SUBSTATE_SysConfirmMsg,
    SUBSTATE_StopRecordMsg,
    SUBSTATE_ExtEvtInfo,
    SUBSTATE_SatTpEditMenu,
    SUBSTATE_SatelliteSettingMenu,
    SUBSTATE_DCMSearch,
    SUBSTATE_RecordingMenu,
    SUBSTATE_EntertainmentMenu,
    SUBSTATE_FrontDisplaySettingMenu,
    SUBSTATE_PhotoAlbumList,
    SUBSTATE_UCCList,
    SUBSTATE_SnapShot,
    SUBSTATE_Weather,
    SUBSTATE_Flickr,
    SUBSTATE_EpgSetting,

	N_SUBSTATE
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
    SYSVAR_HDOutputMode,
    SYSVAR_HDVideoFormat,    
    SYSVAR_ScartOut,
    SYSVAR_ScartType,
    SYSVAR_TvRatio,
    SYSVAR_DisplayFormat,
    SYSVAR_SoundMode,
    SYSVAR_UhfType,
    SYSVAR_UhfCh,
    SYSVAR_OsdAlpha,
    SYSVAR_IBoxTime,
    SYSVAR_IBoxPos,
    SYSVAR_Timeshift,
    SYSVAR_TimeshiftStorage,
    SYSVAR_OsdAnimation,
    SYSVAR_OsdTextScroll
} TAP_SysVarId;

#define MAX_Vol         17
#define MAX_IBoxPos     3
#define MIN_IBoxPos     -10

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
    TVTYPE_Pal,
    TVTYPE_Ntsc,
    TVTYPE_Auto,
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
} TYPE_SoundMode;

// screen ratio
typedef enum
{
    SCREEN_RATIO_4_3,
    SCREEN_RATIO_16_9,
    N_ScreenRatio
} TYPE_ScreenRatio;

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

typedef enum
{
	DISPLAY_MODE_Full,
	DISPLAY_MODE_Center,
	N_WindowMode43
} TYPE_4_3_DISPLAY;


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

typedef enum
{
    TIMESHIFT_Disable,
    TIMESHIFT_30min,
    TIMESHIFT_1hour,
    TIMESHIFT_2hour,
    TIMESHIFT_3hour,
    TIMESHIFT_4hour,
    TIMESHIFT_5hour,
    N_TimeShiftMode
} TYPE_TimeShiftMode;

typedef enum
{
    HD_OUTPUT_Scart,
    HD_OUTPUT_Component,
    N_HDOutput
} TYPE_HDOutputMode;

typedef enum
{
    VIDEO_STANDARD_AUTO,
    VIDEO_STANDARD_1080I,
    VIDEO_STANDARD_720P,
    VIDEO_STANDARD_576P480P,
    VIDEO_STANDARD_576I480I,
    //pal	
    VIDEO_STANDARD_AUTO_PAL,
    VIDEO_STANDARD_1080I50,
    VIDEO_STANDARD_720P50,
    VIDEO_STANDARD_576P,
    VIDEO_STANDARD_Pal,//576I
    //ntsc	
    VIDEO_STANDARD_AUTO_NTSC,
    VIDEO_STANDARD_1080I60,
    VIDEO_STANDARD_720P60,
    VIDEO_STANDARD_480P,
    VIDEO_STANDARD_Ntsc,//480I

    VIDEO_STANDARD_Invalid,
    N_VideoStandard
} TYPE_VideoStandard;

typedef enum
{
    TEXT_SCROLL_Disable,
    TEXT_SCROLL_Full,
    TEXT_SCROLL_Part,
    N_TextScrollMode
} TYPE_TextScrollMode;


// -- SYSTEM FUNCTION ---------------------------------------------------
extern  dword   (*TAP_GetSystemId)(void);
extern  dword   (*TAP_GetVersion)(void);

extern  void    (*TAP_SystemProc)(void);
extern  dword   (*TAP_GetState)( dword *state, dword *subState );
extern  void    (*TAP_ExitNormal)( void );
extern  void    (*TAP_EnterNormal)( void );
extern  void    (*TAP_Exit)(void);

extern  byte    (*TAP_KbHit)(void);
extern  byte    (*TAP_GetCh)(void);
extern  void    (*TAP_PutCh)(byte c);
extern  void    (*TAP_PutByte)(byte c);
extern  void    (*TAP_PrintSys)(const void *fmt, ...);
extern  void    (*TAP_Print)(const void *fmt, ...);
extern  void    (*TAP_SPrint)(void *s, const void *fmt, ...);

extern  void    (*TAP_SysOsdControl)( TYPE_TapSysOsdId osdId, bool ctrl );
extern  void    (*TAP_SetBaudRate)( dword baudRate );
extern  void    (*TAP_Reboot)( void );

// -- COMMON FUNCTION ---------------------------------------------------
extern  void*   (*TAP_MemSet)(void *dest, byte c, dword n);
extern  void*   (*TAP_MemCpy)(void *dest, void *src, dword n);
extern  int     (*TAP_MemCmp)(const void *s1, const void *s2, dword n);
extern  char*   (*TAP_StrCpy)(char *dest, const char* src);
extern  char*   (*TAP_StrNCpy)(char *dest, const char* src, dword n);
extern  int     (*TAP_StrCmp)(const char *s1, const char *s2);
extern	int     (*TAP_StrNCmp)(const char *s1, const char *s2, dword n);
extern  int     (*TAP_StrCaseCmp)(const char *s1, const char *s2);
extern  int     (*TAP_StrNCaseCmp)(const char *s1, const char *s2, dword n);
extern  dword   (*TAP_StrLen)(const char* s);
extern  char*   (*TAP_StrCat)(char *s1, const char *s2);

extern  void    (*TAP_Srand)(dword seed);
extern  dword   (*TAP_Rand)(dword limit);

extern  int     (*TAP_SetSoundLevel)(byte soundLevel);
extern  int     (*TAP_GetTime)(word *mjd, byte *hour, byte *min, byte *sec);
extern  void    (*TAP_MemInfo)(dword *heapSize, dword *freeHeapSize, dword *availHeapSize);
extern  void*   (*TAP_MemAlloc)(dword size);
extern  int     (*TAP_MemFree)(const void *addr);

extern  dword   (*TAP_GetTick)(void);
extern  dword   (*TAP_DiffTick)(dword oldTick, dword newTick);
extern  void    (*TAP_Delay)(dword dm10);
extern  void    (*TAP_Sleep)(dword ms);
extern  int     (*TAP_ExtractMjd)(word mjd, word *year, byte *month, byte *day, byte *weekDay);
extern  int     (*TAP_MakeMjd)(word year, byte month, byte day);
extern  long    (*TAP_Sin)( long mul, long th );
extern  long    (*TAP_Cos)( long mul, long th );

extern  int     (*TAP_GetSignalLevel)(void);
extern  int     (*TAP_GetSignalQuality)(void);
extern  int     (*TAP_SetInfoboxTime)( int sec );
extern  int     (*TAP_PlayPCM)( void *pcmdata, int size, int freq, void (*Callback)(void) );
extern  int     (*TAP_CaptureScreen)( int mainSub, TYPE_VideoFrame *videoFrame, dword margin );

extern  int     (*TAP_SetSystemVar)( int varId, int value );
extern  int     (*TAP_GetSystemVar)( int varId );
extern  int     (*TAP_WriteSystemVar)( void );
extern  void    (*TAP_GenerateEvent)(  word evtCode, dword param1, dword param2 );
extern  void    (*TAP_SetRemote)(byte waitTime, byte repeatTime);

extern  dword   (*TAP_Get12bit)(const byte *p);
extern  void    (*TAP_Put12bit)(byte *p, word data);
extern  dword   (*TAP_Get13bit)(const byte *p);
extern  void    (*TAP_Put13bit)(byte *p, word data);
extern  dword   (*TAP_Get16bit)(const byte *p);
extern  void    (*TAP_Put16bit)(byte *p, word data);
extern  dword   (*TAP_Get24bit)(const byte *p);
extern  void    (*TAP_Put24bit)(byte *p, dword data);
extern  dword   (*TAP_Get32bit)(const byte *p);
extern  void    (*TAP_Put32bit)(byte *p, dword data);
extern  dword   (*TAP_GetMpegCrc32)(const void *data, dword n);


// -- OSD FUNCTION ---------------------------------------------------
extern  int     (*TAP_Osd_Create)( dword x, dword y, dword w, dword h, byte lutIdx, int flag );
extern  int     (*TAP_Osd_Delete)(word rgn);
extern  int     (*TAP_Osd_Move)(word rgn, dword x, dword y);
extern  int     (*TAP_Osd_FillBox)(word rgn, dword x, dword y, dword w, dword h, dword color);
extern  int     (*TAP_Osd_PutBox)(word rgn, dword x, dword y, dword w, dword h, const void *data, bool sprite, byte dataFormat );
extern  int     (*TAP_Osd_GetBox)(word rgn, dword x, dword y, dword w, dword h, void *data);
extern  int     (*TAP_Osd_SetLut)(byte lutIdx, byte lut[][4] );
extern  int     (*TAP_Osd_Ctrl)(word rgn, dword ctrl);
extern  int     (*TAP_Osd_SetTransparency)( word rgn, char rt);

extern  int     (*TAP_Osd_Draw3dBox)( word rgn, dword x, dword y, dword w, dword h, dword c1, dword c2 );
extern  int     (*TAP_Osd_Draw3dBoxFill)( word rgn, dword x, dword y, dword w, dword h, dword c1, dword c2, dword fc );

extern  int     (*TAP_Osd_DrawRectangle)(word rgn, dword x, dword y, dword w, dword h, dword t, dword color);
extern  int     (*TAP_Osd_DrawPixmap)(word rgn, dword x, dword y, dword w, dword h, void *pixmap, bool sprite, byte dataFormat );
extern  int     (*TAP_Osd_Zoom)( int xzoom, int yzoom );
extern  int     (*TAP_Osd_GetBaseInfo)( TYPE_OsdBaseInfo *info );
extern  int     (*TAP_Osd_GetPlaneBaseInfo)( TYPE_OsdBaseInfo *info, byte plane );
extern  int     (*TAP_Osd_Copy)(word srcRgnNum, word dstRgnNum, dword srcX, dword srcY, dword w, dword h, dword dstX, dword dstY,  bool sprite);
extern  int     (*TAP_Osd_PutGd)(word rgn, int x, int y, TYPE_GrData * gd, bool sprite);

extern  byte*   (*TAP_Osd_SaveBox)( word rgn, dword x, dword y, dword w, dword h );
extern  void    (*TAP_Osd_RestoreBox)( word rgn, dword x, dword y, dword w, dword h, void *data );
extern  int     (*TAP_Osd_GetPixel)( word rgn, dword x, dword y, void *pix );
extern  int     (*TAP_Osd_PutPixel)( word rgn, dword x, dword y, dword pix );

extern  void*   (*TAP_Osd_DecompressJpeg)(const char* fileName, dword w, dword h, dword option);
extern  int     (*TAP_Osd_DrawJpeg)(word rgn, dword x, dword y, dword w, dword h, const char* file, dword option);

extern  void    (*TAP_Osd_Sync)(void);

// -- STRING FUNCTION ---------------------
extern  int     (*TAP_Osd_PutS)(word rgn, dword x, dword y, dword maxX, const char * str, dword fcolor, dword bcolor, byte fntType, byte fntSize, byte bDot, byte align);
extern  int     (*TAP_Osd_GetW)( const char *str, byte fntType, byte fntSize );
extern  int     (*TAP_Osd_PutString)(word rgn, dword x, dword y, dword maxX, const char * str, dword fcolor, dword bcolor, byte fntType, byte fntSize, byte nextLine);
extern  int     (*TAP_Osd_DrawString)(const char * str, dword dstWidth, dword color, void *dest, byte dataFormat, dword maxWidth, byte fntType, byte fntSize);
extern  int     (*TAP_Osd_PutStringAf)(word rgn, dword x, dword y, dword maxX, const char * str, dword fcolor, dword bcolor, byte fntType, byte fntSize, byte nextLine);


// -- HDD FUNCTION ---------------------------------------------------
extern  TYPE_File* (*TAP_Hdd_Fopen)(const char *name );
extern  dword   (*TAP_Hdd_Fread)( void *buf, dword blksize, dword blk, TYPE_File* file );
extern  dword   (*TAP_Hdd_Fwrite)( void *buf, dword blksize, dword blk, TYPE_File* file );
extern  void    (*TAP_Hdd_Fclose)( TYPE_File* file );
extern  dword   (*TAP_Hdd_FindFirst)( TYPE_FolderEntry* file, const char* extension);
extern  dword   (*TAP_Hdd_FindNext)( TYPE_FolderEntry* file );

extern  dword   (*TAP_Hdd_Fseek)( TYPE_File* file, long pos, long where );
extern  dword   (*TAP_Hdd_Flen)( TYPE_File* file );
extern  dword   (*TAP_Hdd_Ftell)( TYPE_File* file );
extern  dword   (*TAP_Hdd_TotalSize)( void );
extern  dword   (*TAP_Hdd_FreeSize)( void );
extern  word    (*TAP_Hdd_Delete)(const char *name );
extern  bool    (*TAP_Hdd_Exist)(const char *name );
extern  dword   (*TAP_Hdd_Create)(const char *name, byte attr );
extern  int     (*TAP_Hdd_ChangeDir)(const char *dir );

extern  int     (*TAP_Hdd_PlayTs)(const char *name );
extern  int     (*TAP_Hdd_StopTs)( void);
extern  int     (*TAP_Hdd_PlayMp3)(const char *name );
extern  int     (*TAP_Hdd_StopMp3)( void );
extern  bool    (*TAP_Hdd_Rename)(const char *oldName, const char *newName );

extern  bool    (*TAP_Hdd_StartRecord)( void );
extern  bool    (*TAP_Hdd_StopRecord)( byte recSlot );
extern  bool    (*TAP_Hdd_GetRecInfo)( byte recSlot, TYPE_RecInfo *recInfo );
extern  bool    (*TAP_Hdd_GetPlayInfo)( TYPE_PlayInfo *playInfo );
extern  bool    (*TAP_Hdd_GetHddID)(char *modelNo, char *serialNo);

extern  bool    (*TAP_Hdd_ChangePlaybackPos)( dword blockPos );
extern  bool    (*TAP_Hdd_GotoBookmark)( void );
extern  bool    (*TAP_Hdd_SetBookmark)( void );


// -- WINDOW FUNCTION ---------------------------------------------------
typedef void    (*TYPE_DrawItemFunc)( TYPE_Window win, dword itemNo );

extern  void    (*TAP_Win_SetTitle)( TYPE_Window win, const char *str, byte fntType, byte fntSize );
extern  void    (*TAP_Win_SetColor)(TYPE_Window win, dword titleBack, dword titleText, dword bodyBack, dword bodyText, dword border, dword shadow, dword dark, dword light);
extern  void    (*TAP_Win_SetDefaultColor)( TYPE_Window win );
extern  void    (*TAP_Win_Draw)( TYPE_Window win );
extern  TYPE_Window    (*TAP_Win_Create)(word rgn, dword x, dword y, dword w, dword h, dword maxItem, byte save, byte bScr );
extern  dword   (*TAP_Win_Delete)( TYPE_Window win );
extern  void    (*TAP_Win_SetFont)( TYPE_Window win, byte fntType, byte fntSize );
extern  void    (*TAP_Win_AddItem)( TYPE_Window win, char *str );
extern  dword   (*TAP_Win_RemoveItem)( TYPE_Window win, dword itemNo );
extern  dword   (*TAP_Win_RemoveAllItems)( TYPE_Window win);
extern  dword   (*TAP_Win_GetSelection)( TYPE_Window win );
extern  void    (*TAP_Win_SetSelection)( TYPE_Window win, dword pos );
extern  void    (*TAP_Win_Action)( TYPE_Window win, dword key );
extern  void    (*TAP_Win_SetAvtice)( TYPE_Window win, dword itemNo, byte active );
extern  dword   (*TAP_Win_GetAvtice)( TYPE_Window win, dword itemNo);
extern  void    (*TAP_Win_SetDrawItemFunc)( TYPE_Window win, TYPE_DrawItemFunc func );
extern  dword   (*TAP_Win_GetTotalItem)(TYPE_Window win);
extern  char*   (*TAP_Win_GetItem)(TYPE_Window win, dword itemNo);
extern  dword   (*TAP_Win_GetStartPos)(TYPE_Window win);
extern  dword   (*TAP_Win_GetWindowInfo)(TYPE_Window win, TYPE_WindowInfo *info);
extern  dword   (*TAP_Win_GetMaxViewItem)(TYPE_Window win);
extern  dword   (*TAP_Win_SetItemXpos)(TYPE_Window win, dword *xpos);

// --- CHANNEL FUNCTIONS ---------------------------------------------------
extern  int     (*TAP_Channel_GetTotalNum)( int *nTvSvc, int *nRadioSvc );
extern  int     (*TAP_Channel_GetFirstInfo)( int svcType, TYPE_TapChInfo *chInfo );
extern  int     (*TAP_Channel_GetNextInfo)( TYPE_TapChInfo *chInfo );
extern  int     (*TAP_Channel_GetInfo)( int svcType, int svcNum, TYPE_TapChInfo *chInfo );
extern  int     (*TAP_Channel_GetCurrent)( int *tvRadio, int *svcNum );
extern  int     (*TAP_Channel_GetCurrentSubTV)(int *svcNum );
extern  int     (*TAP_Channel_Start)( int mainSub, int svcType, int chNum );
extern  int     (*TAP_Channel_Scale)( int mainSub, long x, long y, long w, long h, bool anim );
extern  int     (*TAP_Channel_IsPlayable)( int mainSub, int svcType, int chNum );
extern  int     (*TAP_Channel_Move)( int mainSub, int dir );
extern  int     (*TAP_Channel_Stop)( int mainSub );
extern  int     (*TAP_Channel_GetTotalAudioTrack)( void );
extern  char    *(*TAP_Channel_GetAudioTrackName)( int trkNum, char *trkName );
extern  int     (*TAP_Channel_SetAudioTrack)( int trkNum );
extern  int     (*TAP_Channel_GetTotalSubtitleTrack)( void );
extern  char    *(*TAP_Channel_GetSubtitleTrackName)( int trkNum, char *trkName );
extern  int     (*TAP_Channel_SetSubtitleTrack)( int trkNum );
extern  bool    (*TAP_Channel_IsStarted)( int mainSub );
extern  int     (*TAP_Channel_ExchangePip)( void );

// --- EPG FUNCTIONS ---------------------------------------------------
extern  TYPE_TapEvent*    (*TAP_GetEvent)( int svcType, int svcNum, int *eventNum );
extern  TYPE_TapEvent*    (*TAP_GetCurrentEvent)( int svcType, int svcNum );
extern  bool    (*TAP_PutEvent)( byte *eitData );
extern  bool    (*TAP_EPG_UpdateEvent)(  int svcType, int svcNum, dword evtid, dword runningStatus );
extern  bool    (*TAP_EPG_DeleteEvent)(  int svcType, int svcNum, dword evtid );
extern  byte    *(*TAP_EPG_GetExtInfo)( TYPE_TapEvent *tapEvtInfo );
extern  word    (*TAP_ControlEit)( bool enable );

// --- TIMER FUNCTIONS ---------------------------------------------------
extern int      (*TAP_Timer_GetTotalNum)( void );
extern bool     (*TAP_Timer_GetInfo)( int entryNum, TYPE_TimerInfo *info );
extern int      (*TAP_Timer_Add)( TYPE_TimerInfo *info );
extern int      (*TAP_Timer_Modify)( int entryNum, TYPE_TimerInfo *info );
extern bool     (*TAP_Timer_Delete)( int entryNum );

// --- VFD FUNCTIONS ---------------------------------------------------
extern int      (*TAP_Vfd_GetStatus)( void );
extern void     (*TAP_Vfd_Control)( bool underTapCtrl );
extern void     (*TAP_Vfd_SendData)( byte *data, byte dataLen );

// -- SOUND FUNCTION ----------------------
extern  TYPE_WavHandle (*TAP_Wav_PlayerOpen)(const char *name);
extern  int     (*TAP_Wav_PlayerClose)(TYPE_WavHandle handle);
extern  int     (*TAP_Wav_PlayerStart)(TYPE_WavHandle handle, dword loop);
extern  int     (*TAP_Wav_PlayerStop)(TYPE_WavHandle handle);
extern  int     (*TAP_Wav_PlayerSetVolume)(TYPE_WavHandle handle, byte level);

// -- DEMUX FUNCTION ----------------------
extern  int     (*TAP_Demux_StartFilter)(int mainSub, TYPE_DemuxFilter *filter);
extern  int     (*TAP_Demux_StopFilter)(int demuxHandle);
extern  int     (*TAP_Demux_GetData)(int demuxHandle, dword** data);


// ---------------------------------------------------------------------





#define malloc      TAP_MemAlloc
//#define calloc      TAP_MemCalloc
//#define realloc     TAP_MemRealloc
#define free        TAP_MemFree
#define memcpy      TAP_MemCpy
#define memcmp      TAP_MemCmp
#define memset      TAP_MemSet
#define printf      TAP_Print
#define sprintf     TAP_SPrint


#define UNUSED(x)    (void)x


// --- User Define Function --------------------------------------------
extern  int     TAP_Main(void);
extern  dword   TAP_EventHandler( word event, dword param1, dword param2 );
extern unsigned char (*TAP_GetActiveTuner)(unsigned char);  // missing definition in tap.h


#ifdef __cplusplus
};
#endif

#endif
