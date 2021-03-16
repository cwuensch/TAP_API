#ifndef _INFHEADER_H_
#define _INFHEADER_H_

typedef struct
{
  tRecInfHeader         RecInfHeader;       //Offset = 0x0000
  tRecInfServiceInfo    RecInfServiceInfo;  //         0x001c
  tRecInfEventInfo      RecInfEventInfo;    //         0x0044
  tRecInfExtEventInfo   RecInfExtEventInfo; //         0x0168
  tRecInfTPInfo         RecInfTPInfo;       //         0x0570
  tRecInfBookmarks      RecInfBookmarks;    //         0x0584
  byte                  filler[8192];       //         0x0850: reserved space
  tPreviewImages        PreviewImages;      //         0x2850: Preview images
} tRecInf;

typedef struct
{
  char                  Magic[4];           //"TFrc"
  word                  Version;            //0x8000
  byte                  Unknown1[2];        //possibly an unused filler
  dword                 StartTime;          //start of the recording
  word                  DurationMin;
  word                  DurationSec;
  byte                  CryptFlag;          //0=FTA, 1=scrambled, 2=descrambled, 3=partly scrambled

  byte                  FlagUnused:5;
  byte                  FlagUnknown:1;
  byte                  FlagTimeShift:1;    //This is a TimeShift file
  byte                  FlagCopy:1;         //This is a copy (C icon)

  byte                  Unknown2[10];       //Reserved for future use?
} tRecInfHeader;  //28 bytes

typedef struct
{
  byte                  SatIndex;
  byte                  ServiceType;

  word                  TPIndex:10;
  word                  FlagTuner:2;
  word                  FlagSkip:1;
  word                  FlagLock:1;
  word                  FlagCAS:1;
  word                  FlagDel:1;

  word                  ServiceID;
  word                  PMTPID;
  word                  PCRPID;
  word                  VideoPID;
  word                  AudioPID;
  char                  ServiceName[24];
  byte                  VideoStreamType;    //see tap.h for possible video and audio stream types
  byte                  AudioStreamType;
} tRecInfServiceInfo; //40 bytes

typedef struct
{
  byte                  Unknown1[2];
  byte                  DurationMin;        //Duration of the event
  byte                  DurationHour;
  dword                 EventID;
  dword                 StartTime;          //Event times
  dword                 EndTime;
  byte                  RunningStatus;
  byte                  EventNameLength;
  byte                  ParentalRate;
  char                  EventNameAndDescription[273];
} tRecInfEventInfo; //292 bytes

typedef struct
{
  word                  ServiceID;
  word                  TextLength;
  dword                 EventID;
  char                  Text[1024];
} tRecInfExtEventInfo; //1032 bytes

typedef struct
{
  dword                 Unknown1;

  dword                 SatIndex:8;
  dword                 Polarization:1;     //0=vert, 1=hor
  dword                 Mode:3;
  dword                 ModSystem:1;        //see tap.h
  dword                 ModType:2;          //see tap.h
  dword                 FEC:4;              //see tap.h
  dword                 Pilot:1;
  dword                 UnusedFlags1:4;
  dword                 Unknown2:8;

  dword                 Frequency;
  word                  SymbolRate;
  word                  TSID;

  word                  ClockSync:1;
  word                  UnusedFlags2:15;

  word                  OriginalNetworkID;
} tRecInfTPInfo; //20 bytes

typedef struct
{
  dword                 NrBookmarks;
  dword                 BookmarkPosition[177];
  dword                 Resume;      //in blocks (1 block = 9024 bytes = LeastCommonMultiple(188, 192))
} tRecInfBookmarks; //716 bytes 

typedef struct
{
  word                  NrOfImages;         //Check if the inf file size is at least 10322 bytes to
                                            //  make sure that NrOfImages is valid
  word                  unknown1;             
  dword                 unknown2;
  dword                 unknown3;
  dword                 PixelData1[196*156];  //ARGB
  dword                 unknown4;
  dword                 unknown5;
  dword                 PixelData2[196*156];  //ARGB
  dword                 unknown6;
  dword                 unknown7;
  dword                 PixelData3[196*156];  //ARGB
  dword                 unknown8;
  dword                 unknown9;
  dword                 PixelData4[196*156];  //ARGB
} tPreviewImages;

#endif