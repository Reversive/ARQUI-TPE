#ifndef _KB_SCANCODES_H
#define _KB_SCANCODES_H


#define OUT_OF_RANGE 89
#ifndef NULL
#define NULL 0
#endif
#define ESC    27
#define BACKSPACE '\b'
#define TAB       '\t'
#define ENTER     '\n'
#define RETURN    '\r'
#define NEWLINE ENTER

// Non-ASCII special scancodes // Esc in scancode is 1
#define    KESC         1
#define    KF1          0x80
#define    KF2         (KF1 + 1)
#define    KF3         (KF2 + 1)
#define    KF4         (KF3 + 1)
#define    KF5         (KF4 + 1)
#define    KF6         (KF5 + 1)
#define    KF7         (KF6 + 1)
#define    KF8         (KF7 + 1)
#define    KF9         (KF8 + 1)
#define    KF10        (KF9 + 1)
#define    KF11        (KF10 + 1)
#define    KF12        (KF11 + 1)

// Cursor Keys
#define    KINS         0x90
#define    KDEL        (KINS + 1)
#define    KHOME       (KDEL + 1)
#define    KEND        (KHOME + 1)
#define    KPGUP       (KEND + 1)
#define    KPGDN       (KPGUP + 1)
#define    KLEFT       (KPGDN + 1)
#define    KUP         (KLEFT + 1)
#define    KDOWN       (KUP + 1)
#define    KRIGHT      (KDOWN + 1)

// "Meta" keys
#define    KMETA_ALT     0x0200                                // Alt is pressed
#define    KMETA_CTRL    0x0400                                // Ctrl is pressed
#define    KMETA_SHIFT   0x0800                                // Shift is pressed
#define    KMETA_ANY    (KMETA_ALT | KMETA_CTRL | KMETA_SHIFT)
#define    KMETA_CAPS    0x1000                                // CapsLock is on
#define    KMETA_NUM     0x2000                                // NumLock is on
#define    KMETA_SCRL    0x4000                                // ScrollLock is on

// Other keys
#define    KPRNT    ( KRT + 1 )
#define    KPAUSE   ( KPRNT + 1 )
#define    KLWIN    ( KPAUSE + 1 )
#define    KRWIN    ( KLWIN + 1 )
#define    KMENU    ( KRWIN + 1 )

#define    KRLEFT_CTRL          0x1D
#define    KRRIGHT_CTRL         0x1D   
#define    KRCTRL_RELEASE       0x9D

#define    KRLEFT_ALT           0x38
#define    KRRIGHT_ALT          0x38   
#define    KRALT_RELEASE        0xB8

#define    KRLEFT_SHIFT             0x2A
#define    KRLEFT_SHIFT_RELEASE     0xAA
#define    KRRIGHT_SHIFT            0x36
#define    KRRIGHT_SHIFT_RELEASE    0x36

#define    KRCAPS_LOCK          0x3A
#define    KRCAPS_LOCK_RELEASE  0xBA

#define    KRSCROLL_LOCK        0x46
#define    KRNUM_LOCK           0x45
#define    KRDEL                0x53

// Keymaps: US International



#endif


// https://www.henkessoft.de/OS_Dev/OS_Dev1.htm#mozTocId185043