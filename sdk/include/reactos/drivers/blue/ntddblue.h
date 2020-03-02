#ifndef _NTDDBLUE_H_INCLUDED_
#define _NTDDBLUE_H_INCLUDED_

#define IOCTL_CONSOLE_RESET_SCREEN              CTL_CODE(FILE_DEVICE_SCREEN, 0x800, METHOD_BUFFERED, FILE_WRITE_ACCESS)

#define IOCTL_CONSOLE_GET_SCREEN_BUFFER_INFO    CTL_CODE(FILE_DEVICE_SCREEN, 0x801, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CONSOLE_SET_SCREEN_BUFFER_INFO    CTL_CODE(FILE_DEVICE_SCREEN, 0x802, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_CONSOLE_GET_CURSOR_INFO           CTL_CODE(FILE_DEVICE_SCREEN, 0x803, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CONSOLE_SET_CURSOR_INFO           CTL_CODE(FILE_DEVICE_SCREEN, 0x804, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_CONSOLE_GET_MODE                  CTL_CODE(FILE_DEVICE_SCREEN, 0x805, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_CONSOLE_SET_MODE                  CTL_CODE(FILE_DEVICE_SCREEN, 0x806, METHOD_BUFFERED, FILE_WRITE_ACCESS)

#define IOCTL_CONSOLE_FILL_OUTPUT_ATTRIBUTE     CTL_CODE(FILE_DEVICE_SCREEN, 0x810, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_CONSOLE_READ_OUTPUT_ATTRIBUTE     CTL_CODE(FILE_DEVICE_SCREEN, 0x811, METHOD_OUT_DIRECT, FILE_READ_ACCESS)
#define IOCTL_CONSOLE_WRITE_OUTPUT_ATTRIBUTE    CTL_CODE(FILE_DEVICE_SCREEN, 0x812, METHOD_IN_DIRECT, FILE_WRITE_ACCESS)
#define IOCTL_CONSOLE_SET_TEXT_ATTRIBUTE        CTL_CODE(FILE_DEVICE_SCREEN, 0x813, METHOD_BUFFERED, FILE_WRITE_ACCESS)

#define IOCTL_CONSOLE_FILL_OUTPUT_CHARACTER     CTL_CODE(FILE_DEVICE_SCREEN, 0x820, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_CONSOLE_READ_OUTPUT_CHARACTER     CTL_CODE(FILE_DEVICE_SCREEN, 0x821, METHOD_OUT_DIRECT, FILE_READ_ACCESS)
#define IOCTL_CONSOLE_WRITE_OUTPUT_CHARACTER    CTL_CODE(FILE_DEVICE_SCREEN, 0x822, METHOD_IN_DIRECT, FILE_WRITE_ACCESS)

#define IOCTL_CONSOLE_DRAW                      CTL_CODE(FILE_DEVICE_SCREEN, 0x830, METHOD_IN_DIRECT, FILE_WRITE_ACCESS)

#define IOCTL_CONSOLE_LOADFONT                  CTL_CODE(FILE_DEVICE_SCREEN, 0x840, METHOD_IN_DIRECT, FILE_WRITE_ACCESS)

/* TYPEDEFS **************************************************************/

typedef struct tagCONSOLE_MODE
{
    ULONG dwMode;
} CONSOLE_MODE, *PCONSOLE_MODE;

typedef struct tagOUTPUT_ATTRIBUTE
{
    USHORT wAttribute;
    ULONG  nLength;
    COORD  dwCoord;
    ULONG  dwTransfered;
} OUTPUT_ATTRIBUTE, *POUTPUT_ATTRIBUTE;

typedef struct tagOUTPUT_CHARACTER
{
    CHAR  cCharacter;
    ULONG nLength;
    COORD dwCoord;
    ULONG dwTransfered;
} OUTPUT_CHARACTER, *POUTPUT_CHARACTER;

typedef struct tagCONSOLE_DRAW
{
    USHORT X;       /* Origin */
    USHORT Y;
    USHORT SizeX;   /* Size of the screen buffer (chars) */
    USHORT SizeY;
    USHORT CursorX; /* New cursor position (screen-relative) */
    USHORT CursorY;
    /* Followed by screen buffer in char/attrib format */
} CONSOLE_DRAW, *PCONSOLE_DRAW;

#endif /* _NTDDBLUE_H_INCLUDED_ */
