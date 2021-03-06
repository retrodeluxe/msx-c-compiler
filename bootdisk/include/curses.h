/********************************/
/*  header file for MSX-CURSES  */
/*          "curses.h"          */
/********************************/

#ifndef     _NOCHANGE
/*
#include    <msxbios.h>
*/

/*
as both  "curses.c"  and  user  program include this header file,
we need  a  trick  to  avoid  conflicting  definition between "curses.c"
and user program.
*/
#ifndef     EXTERN
#define     EXTERN      extern
#endif
/* end of trick */

#define     ERR         0xFF

#define     _SUBWIN     0x01
#define     _ENDLINES   0x02
#define     _FULLWIN    0x04
#define     _FLUSH      0x08
#define     _SCROLLWIN  0x10

#define     _RAW         0x01
#define     _ECHO        0x04

#define     _NOCHANGE   -1

typedef struct {
	char    *_y;
	int     _firstch;
	int     _lastch;
	int     _ins_del;
	} INDEXLIN;

typedef struct {
	TINY        _cury, _curx;
	TINY        _maxy, _maxx;
	int         _begy, _begx;
	int         _flags;
	BOOL        _clear;
	BOOL        _leave;
	BOOL        _scroll;
	INDEXLIN    *_index;
	} WINDOW;

typedef TINY SGTTY;  /* flags for terminal type */

EXTERN      SGTTY _tty;

EXTERN      TINY LINES;   /* MAX lines */
EXTERN      TINY COLS;    /* MAX columns */

EXTERN      WINDOW *stdscr;
EXTERN      WINDOW *curscr;

/*
 * MSX work areas
 */
#define     LINLEN  ((TINY *)(0xf3b0))  /* Number of columns */
#define     CRTCNT  ((TINY *)(0xf3b1))  /* CRT horizontal line number */
#define     CNFDFG  ((TINY *)(0xf3de))  /* Function key displayed or not */

/*
 * char constants definitions
 */
#define     BEL     '\007'
#define     BS      '\010'
#define     TAB     '\011'
#define     LF      '\012'
#define     HOME    '\013'
#define     FF      '\014'
#define     CR      '\015'
#define     ESC     '\033'
#define     RIGHT   '\034'
#define     LEFT    '\035'
#define     UP      '\036'
#define     DOWN    '\037'
#define     SPACE   '\040'
#define     DEL     '\177'

#define     ERR     ERROR
#define     TABS    (TINY)8  /* normal horizontal TAB */

/*
 * pseudo functions
 */
#define     scrollok(win, bf)   win->_scroll = bf
#define     clearok(win, bf)    win->_clear = bf

#define     getyx(win, y, x)    y = (int)win->_cury, x = (int)win->_curx

#define     INSERT  TRUE
#define     DELETE  FALSE

#define     wclrtobot   wclrbot
#define     wclrtoeol   wclreol

#define     echo()      _tty |= _ECHO
#define     noecho()    _tty &= ~_ECHO
#define     raw()       _tty |= _RAW

/*
 * initializing function
 */
WINDOW      *initscr();
WINDOW      *newwin();
WINDOW      *subwin();

/*
 * console output function
 */
STATUS      wrefresh();
STATUS      refresh();

/*
 * logical screen output functions
 */
STATUS      move(), addch(), addstr(), delch(), insch(), printw(.);
STATUS      wmove(), waddch(), waddstr(), wdelch(), winsch(), wprintw(.);
STATUS      box(), touchwin();
STATUS      wclear(), clear();

STATUS      mvprintw(.), mvwprintw(.);

VOID        overwrite(), erase(), clrtobot(),
	    clrtoeol();

VOID        werase(),  wclrtobot(),
	    wclrtoeol();

VOID        delwin();

VOID        insertln(), deleteln();
VOID        winsertln(), wdeleteln();

STATUS      scroll();

char        inch(), winch();

/*
 * Internal functions
 */
VOID        _rotate();     /* insertln, deleteln */
VOID        _move();

/*
 * "mv" functions
 */
#define     mvwgetch    mvwgtch
#define     mvwgetstr   mvwgtstr
#define     mvwaddch    mvwadch
#define     mvwaddstr   mvwadstr
#define     getch       cgetch

#define     mvwadd  mvwad

STATUS      mvwadch(),       mvwadstr(),      mvwgtstr(),
	    mvwdelch(),      mvwinsch(),      mvaddch(),
	    mvaddstr(),      mvgetstr(),      mvdelch(),
	    mvinsch();

STATUS      mvwin();

char        mvwinch(), mvwgtch(), mvinch(), mvgetch();

/*
 * pseudo functions for console I/O
 */
#define     TURBO       ON                      /* TURBO ON !!! gain speed */
						/* of console output routine. */
#ifdef      TURBO                               /* if TURBO ON ... */
VOID        chput();
#define     putch   chput                       /* then call BIOS directly */
#else                                           /* else ... */
#define     BIOS_CONOUT '\003'
char        bios();
#define     putch(ch)   bios(BIOS_CONOUT, ch)   /* use library function */
#endif

/*
 * console input functions
 */
char        cgetch();
char        wgetch();
STATUS      getstr();
STATUS      wgetstr();

/*
 * others
 */
VOID        endwin();
VOID        _rollup();     /* == scroll() */

/*
 * other utility function
 */
VOID        memmove();

#endif
         