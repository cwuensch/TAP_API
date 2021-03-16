//
// TOPFIELD Dynamic Application Toolkit.
// key.h
// Remote controller code definition file.
//

#ifndef __REKEY__
#define __REKEY__

//    Remote controller key codes
#define RKEY_0            0x10000
#define RKEY_1            0x10001
#define RKEY_2            0x10002
#define RKEY_3            0x10003
#define RKEY_4            0x10004
#define RKEY_5            0x10005
#define RKEY_6            0x10006
#define RKEY_7            0x10007
#define RKEY_8            0x10008
#define RKEY_9            0x10009
#define RKEY_Power        0x1000a
#define RKEY_Recall       0x1000b
#define RKEY_Mute         0x1000c
#define RKEY_NoUse        0x1000d
#define RKEY_Uhf          0x1000e
#define RKEY_Left         0x1000f
#define RKEY_Sleep        0x10010
#define RKEY_Easy         0x10011
#define RKEY_Up           0x10012
#define RKEY_AudioTrk     0x10013
#define RKEY_Info         0x10014
#define RKEY_Right        0x10015
#define RKEY_Guide        0x10016
#define RKEY_Exit         0x10017
#define RKEY_TvRadio      0x10018
#define RKEY_NoUse4       0x10019
#define RKEY_Pause        0x1001a
#define RKEY_NoUse5       0x1001b
#define RKEY_Menu         0x1001c
#define RKEY_Down         0x1001d
#define RKEY_Ok           0x1001e

#define RKEY_Fav          0x10020
#define RKEY_Subt         0x10021
#define RKEY_TvSat        0x10022

#define RKEY_F1           0x10023
#define RKEY_F2           0x10024
#define RKEY_F3           0x10025
#define RKEY_F4           0x10026

#define RKEY_Cmd_0        0x10027
#define RKEY_Cmd_1        0x10028
#define RKEY_Cmd_2        0x10029
#define RKEY_Cmd_3        0x1002a
#define RKEY_Cmd_4        0x1002b
#define RKEY_Cmd_5        0x1002c
#define RKEY_Cmd_6        0x1002d
#define RKEY_Cmd_7        0x1002e
#define RKEY_Cmd_8        0x1002f
#define RKEY_Cmd_9        0x10030
#define RKEY_Cmd_a        0x10031
#define RKEY_Cmd_b        0x10032
#define RKEY_Cmd_c        0x10033
#define RKEY_Cmd_d        0x10034
#define RKEY_Cmd_e        0x10035
#define RKEY_Cmd_f        0x10036

#define RKEY_Teletext     0x10037
#define RKEY_Rewind       0x10038
#define RKEY_Play         0x10039
#define RKEY_Forward      0x1003a
#define RKEY_Stop         0x1003c
#define RKEY_Record       0x1003d

#define RKEY_NewF1        0x1003f
#define RKEY_Sat          0x10040
#define RKEY_Prev         0x10041
#define RKEY_PlayList     0x10042
#define RKEY_Next         0x10043
#define RKEY_VFormat      0x10044

#define RKEY_ChUp         0x10045
#define RKEY_ChDown       0x10046
#define RKEY_VolUp        0x10047
#define RKEY_VolDown      0x10048

#define RKEY_Bookmark     RKEY_F2
#define RKEY_Goto         RKEY_F3
#define RKEY_Check        RKEY_F4

#define RKEY_Ab           0x1003e
#define RKEY_Slow         0x1003b

// Front key codes
#define FKEY_ChUp         0x00001
#define FKEY_ChDown       0x00002
#define FKEY_VolUp        0x00003
#define FKEY_VolDown      0x00004
#define FKEY_Ok           0x00005
#define FKEY_Exit         0x00006

#define Keyflag_ASCII     0x20000     //missing definition in key.h (but is not submitted to TAPs)
#define Keyflag_Push	  0x01000000  //wrong definition in key.h
#define Keyflag_Click	  0x02000000  //wrong definition in key.h

//#define RKEY_White	  0x10049     //missing definition in key.h (-> defined in FirebirdLib)
#define RKEY_Red          RKEY_NewF1  //ambiguous definition in key.h

#endif
