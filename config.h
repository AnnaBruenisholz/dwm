/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int borderfloatpx  = 2;        /* border pixel of windows which are floating; seems not correctly implemented yet! window freezes if toggled to floating if different to borderpx*/
static const unsigned int snap      = 10;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 20;       /* horizontal padding of bar */
static const char *fonts[]          = { "monospace:size=13",
					"IPAGothic:size=13",
					"symbola:size=13"};
static const char dmenufont[]       = "monospace:size=13";
#define bblack "#000000"
#define nord0 "#2E3440"
#define nord1 "#3B4252"
#define nord2 "#434C5E"
#define nord3 "#4C566A"
#define nord4 "#D8DEE9"
#define nord5 "#E5E9F0"
#define nord6 "#ECEFF4"
#define nord7 "#8FBCBB"
#define nord8 "#88C0D0"
#define nord9 "#81A1C1"
#define nord10 "#5E81AC"
#define nord11 "#BF616A"
#define nord12 "#D08770"
#define nord13 "#EBCB8B"
#define nord14 "#A3BE8C"
#define nord15 "#B48EAD"

static char normfgcolor[] = nord4;
static char normbgcolor[] = nord0;
static char normbordercolor[] = nord2;

static char selfgcolor[] = nord6;
static char selbgcolor[] = nord10;
static char selbordercolor[] = nord4;

static const char col_urgborder[]   = nord11;

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
        [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
        [SchemeUrg]  = { normfgcolor, normbgcolor,  col_urgborder},
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "scratchpadterm", "-t", "Scratchpad", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "scratchcalc", "-t", "Calculator", "-g", "120x34", "-e", "dropdowncalc", NULL };

static Sp scratchpads[] = {
	/* name          cmd  */
	{"scratchpad",    spcmd1},
	{"dropdowncalc",      spcmd2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    		title      	 tags mask    	 isfloating   		monitor */
	{ "Gimp",	  NULL,			NULL,		0,			1,			 -1 },
	{ "vncviewer",	  NULL,			NULL,		0,			1,			 -1 },
	{ "Vncviewer",	  NULL,			NULL,		0,			1,			 -1 },
	{ "Firefox",  	  NULL,			NULL,		1 << 8,			0,			 -1 },
	{ NULL,		  "scratchpadterm",	NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,		  "scratchcalc",       NULL,		SPTAG(1),		1,			 -1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[@]",      spiral },	   /* first entry is default */
 	{ "[\\]",     dwindle },   /* Default: Master on left, slaves on right */
	{ "H[]",	deck },			/* Master on left, slaves in monocle-like mode on right */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */
	{ "[]=",      tile },      /* Default: Master on left, slaves on right */
	{ "TTT",      bstack },	   /* Master on top, slaves on bottom */
	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */
	{ "[M]",      monocle },
	{ "===",      bstackhoriz },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "movestack.c"
#include <X11/XF86keysym.h>
#include "shiftview.c"
static Key keys[] = {
	/* { MODKEY|ShiftMask,		XK_Escape,	spawn,	SHCMD("") }, */
	{ MODKEY,			XK_grave,	spawn,	SHCMD("dmenuunicode") },
	/* { MODKEY|ShiftMask,		XK_grave,	togglescratch,	SHCMD("") }, */
	TAGKEYS(			XK_1,		0)
	TAGKEYS(			XK_2,		1)
	TAGKEYS(			XK_3,		2)
	TAGKEYS(			XK_4,		3)
	TAGKEYS(			XK_5,		4)
	TAGKEYS(			XK_6,		5)
	TAGKEYS(			XK_7,		6)
	TAGKEYS(			XK_8,		7)
	TAGKEYS(			XK_9,		8)
	{ MODKEY,			XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,		tag,		{.ui = ~0 } },
	{ MODKEY,			XK_minus,	spawn,		SHCMD("lmc down 5 ; pkill -RTMIN+10 dwmblocks") },
	{ MODKEY|ShiftMask,		XK_minus,	spawn,		SHCMD("lmc down 15 ; pkill -RTMIN+10 dwmblocks") },
	{ MODKEY,			XK_equal,	spawn,		SHCMD("lmc up 5 ; pkill -RTMIN+10 dwmblocks") },
	{ MODKEY|ShiftMask,		XK_equal,	spawn,		SHCMD("lmc up 15; pkill -RTMIN+10 dwmblocks") },
	/* { MODKEY,			XK_BackSpace,	spawn,		SHCMD("") }, */
	{ MODKEY|ShiftMask,		XK_BackSpace,	spawn,		SHCMD("prompt \"Reboot computer?\" \"sudo -A reboot\"") },
	{ MODKEY,			XK_Tab,		view,		{0} },
	/* { MODKEY|ShiftMask,		XK_Tab,		spawn,		SHCMD("") }, */
	{ MODKEY,			XK_q,		killclient,	{0} },
	/* { MODKEY|ShiftMask,		XK_q,		spawn,		SHCMD("") }, */
	{ MODKEY,			XK_w,		spawn,		SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask,		XK_w,		spawn,		SHCMD("chromium") }, /*using ungoogled-chromium as backup browser*/
	{ MODKEY,			XK_e,		spawn,		SHCMD("st -e neomutt -e 'set sidebar_visible = no'; pkill -RTMIN+12 dwmblocks") },
	{ MODKEY|ShiftMask,		XK_e,		spawn,		SHCMD("element-desktop") },
	{ MODKEY,			XK_r,		spawn,		SHCMD("st -e $FILE") },
	{ MODKEY|ShiftMask,		XK_r,		spawn,		SHCMD("st -e lf") },
	{ MODKEY,			XK_t,		setlayout,	{.v = &layouts[0]} },
	{ MODKEY|ShiftMask,		XK_t,		setlayout,	{.v = &layouts[1]} },
	{ MODKEY,			XK_y,		setlayout,	{.v = &layouts[2]} },
	{ MODKEY|ShiftMask,		XK_y,		setlayout,	{.v = &layouts[3]} },
	{ MODKEY,			XK_u,		setlayout,	{.v = &layouts[4]} },
	{ MODKEY|ShiftMask,		XK_u,		setlayout,	{.v = &layouts[5]} },
	{ MODKEY,			XK_i,		setlayout,	{.v = &layouts[6]} },
	{ MODKEY|ShiftMask,		XK_i,		setlayout,	{.v = &layouts[7]} },
	{ MODKEY,			XK_o,		incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,		incnmaster,     {.i = -1 } },
	{ MODKEY,			XK_p,			spawn,		SHCMD("mpc toggle; pkill -RTMIN+11 dwmblocks") },
	{ MODKEY|ShiftMask,		XK_p,			spawn,		SHCMD("passmenu2") },
	/* { MODKEY,			XK_bracketleft,		spawn,		SHCMD("mpc seek -10; pkill -RTMIN+11 dwmblocks") }, */
	/* { MODKEY|ShiftMask,		XK_bracketleft,		spawn,		SHCMD("mpc seek -120; pkill -RTMIN+11 dwmblocks") }, */
	/* { MODKEY,			XK_bracketright,	spawn,		SHCMD("mpc seek +10; pkill -RTMIN+11 dwmblocks") }, */
	/* { MODKEY|ShiftMask,		XK_bracketright,	spawn,		SHCMD("mpc seek +120; pkill -RTMIN+11 dwmblocks") }, */
	{ MODKEY,			XK_backslash,		view,		{0} },
	/* { MODKEY|ShiftMask,		XK_backslash,		spawn,		SHCMD("") }, */
	{ MODKEY,			XK_a,		spawn,		SHCMD("st pulsemixer ; pkill -RTMIN+10 dwmblocks") },
	{ MODKEY|ShiftMask,		XK_a,		spawn,		SHCMD("anki") },
	{ MODKEY,                       XK_s,           togglesticky,   {.i=False} },
	{ MODKEY|ShiftMask,		XK_s,		spawn,		SHCMD("temp=\"$(pwd)\"; cd $HOME/dox/notes; st $EDITOR $HOME/dox/notes/Main.md; cd \"$temp\"") },
	{ MODKEY,			XK_d,		spawn,          {.v = dmenucmd } },
	//{ MODKEY|ShiftMask,		XK_d,		togglegaps,	{0} },
	{ MODKEY,			XK_f,		togglefullscr,	{0} },
	{ MODKEY|ShiftMask,		XK_f,		setlayout,	{.v = &layouts[8]} },
	{ MODKEY,			XK_g,		shiftview,	{ .i = -1 } },
	//{ MODKEY|ShiftMask,		XK_g,		spawn,		SHCMD("hover center") },
	{ MODKEY,			XK_h,		focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_h,		setmfact,	{.f = -0.05} },
	{ MODKEY|ControlMask, 		XK_h,		tagmon,		{.i = -1 } },
	{ MODKEY,			XK_j,		focusstack,    	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_j,		movestack,     	{.i = +1 } },
	{ MODKEY,			XK_k,		focusstack,    	{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_k,		movestack,     	{.i = -1 } },
	{ MODKEY,			XK_l,		focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_l,		setmfact,      	{.f = +0.05} },
	{ MODKEY|ControlMask, 		XK_l,		tagmon,		{.i = +1 } },
	{ MODKEY,			XK_semicolon,	shiftview,	{ .i = 1 } },
	/* { MODKEY|ShiftMask,		XK_semicolon,	shiftview,	SHCMD("") }, */
	/* { MODKEY,			XK_apostrophe,	spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,		XK_apostrophe,	spawn,		SHCMD("") }, */
	{ MODKEY,			XK_Return,	spawn,		{.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_Return,	togglescratch,	{.ui = 0 } },
	{ MODKEY,			XK_z,		spawn,		SHCMD("st -e tremc") },
	{ ControlMask|ShiftMask,	XK_z,		spawn,		SHCMD("xdotool click 2")},
	{ MODKEY,			XK_x,		spawn,		SHCMD("slock & ( sleep 4; xset dpms force off; mpc pause ; pauseallmpv)") },
	{ MODKEY|ShiftMask,		XK_x,		spawn,		SHCMD("prompt \"Shutdown computer?\" \"sudo -A shutdown -h now\"") },
	{ MODKEY,			XK_c,		togglescratch,	{.ui = 1 } },
	{ MODKEY|ShiftMask,		XK_c,		setfloating,	{.i = True} },
	{ MODKEY|ShiftMask,		XK_c,		spawn,		SHCMD("hover center") },
	{ MODKEY,			XK_v,		spawn,		SHCMD("st -e $EDITOR -c \"VimwikiIndex\"") },
	{ MODKEY|ShiftMask,		XK_v,		setfloating,	{ .i=True} },
	{ MODKEY|ShiftMask,		XK_v,		setsticky,	{.i=True} },
	{ MODKEY|ShiftMask,		XK_v,		spawn,		SHCMD("hover left") },
	{ MODKEY,			XK_b,		spawn,		SHCMD("bt") },
	{ MODKEY|ShiftMask,		XK_b,		togglebar,	{0} },
	{ MODKEY,			XK_n,		spawn,		SHCMD("st -e newsboat; pkill -RTMIN+13 dwmblocks") },
	{ MODKEY|ShiftMask,		XK_n,		setfloating,	{ .i=True}	 },
	{ MODKEY|ShiftMask,		XK_n,		setsticky,	{.i=True}	 },
	{ MODKEY|ShiftMask,		XK_n,		spawn,		SHCMD("hover right") },
	{ MODKEY,			XK_m,		spawn,		SHCMD("st -e ncmpcpp") },
	{ MODKEY|ShiftMask,		XK_m,		spawn,		SHCMD("dunstctl set-paused toggle; pkill -RTMIN+5 dwmblocks") },
	{ MODKEY,			XK_comma,	spawn,		SHCMD("mpc prev; pkill -RTMIN+11 dwmblocks") },
	{ MODKEY|ShiftMask,		XK_comma,	spawn,		SHCMD("mpc seek 0%; pkill -RTMIN+11 dwmblocks") },
	{ MODKEY,			XK_period,	spawn,		SHCMD("mpc next; pkill -RTMIN+11 dwmblocks") },
	/* { MODKEY|ShiftMask,		XK_period,	spawn,		SHCMD("") }, */
	{ MODKEY,			XK_Left,	focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_Left,	tagmon,		{.i = -1 } },
	{ MODKEY,			XK_Right,	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_Right,	tagmon,		{.i = +1 } },

	{ MODKEY,			XK_Page_Up,	shiftview,	{ .i = -1 } },
	{ MODKEY,			XK_Page_Down,	shiftview,	{ .i = 1 } },
	{ MODKEY,			XK_Insert,	spawn,		SHCMD("notify-send \"📋 Clipboard contents:\" \"$(xclip -o -selection clipboard)\"") },
	{ MODKEY,			XK_F1,		spawn,		SHCMD("dmenuunicode") },
	{ MODKEY,			XK_F2,		quit,		{0} },
	{ MODKEY|ShiftMask,		XK_F2,		spawn,		SHCMD("killdwm") },
	{ MODKEY,			XK_F3,		spawn,		SHCMD("displayselect") },
	{ MODKEY,			XK_F4,		spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ MODKEY,			XK_F5,		spawn,		SHCMD("bt") },
	{ MODKEY,			XK_F6,		spawn,		SHCMD("passmenu2") },
	{ MODKEY,			XK_F7,		spawn,		SHCMD("dmenuvpn") },
	{ MODKEY,			XK_F8,		spawn,		SHCMD("mailsync; pkill -RTMIN+13 dwmblocks") },
	{ MODKEY,			XK_F9,		spawn,		SHCMD("dmenumount") },
	{ MODKEY,			XK_F10,		spawn,		SHCMD("dmenuumount") },
	{ MODKEY,			XK_F11,		spawn,		SHCMD("searx") },
	{ MODKEY,			XK_F12,		spawn,		SHCMD("st -e sudo nmtui") },
	/* { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, */
	{ MODKEY,			XK_space,	zoom,		{0} },
	{ MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} },
	{ MODKEY|ShiftMask,		XK_space,	setsticky,	{.i = False} },
	{ 0,				XK_Print,	spawn,		SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,			XK_Print,	spawn,		SHCMD("maimpick") },
	{ MODKEY,			XK_Print,	spawn,		SHCMD("dmenurecord") },
	{ MODKEY|ShiftMask,		XK_Print,	spawn,		SHCMD("dmenurecord kill") },
	{ MODKEY,			XK_Delete,	spawn,		SHCMD("dmenurecord kill") },
	{ MODKEY,			XK_Scroll_Lock,	spawn,		SHCMD("killall screenkey || screenkey &") },

	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("lmc mute; pkill -RTMIN+10 dwmblocks") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("lmc up 5; pkill -RTMIN+10 dwmblocks") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("lmc down 5; pkill -RTMIN+10 dwmblocks") },
	{ 0, XF86XK_AudioPrev,		spawn,		SHCMD("mpc prev; pkill -RTMIN+11 dwmblocks") },
	{ 0, XF86XK_AudioNext,		spawn,		SHCMD("mpc next; pkill -RTMIN+11 dwmblocks") },
	{ 0, XF86XK_AudioPause,		spawn,		SHCMD("mpc pause; pkill -RTMIN+11 dwmblocks") },
	{ 0, XF86XK_AudioPlay,		spawn,		SHCMD("mpc toggle; pkill -RTMIN+11 dwmblocks") },
	{ 0, XF86XK_AudioStop,		spawn,		SHCMD("mpc stop; pkill -RTMIN+11 dwmblocks") },
	{ 0, XF86XK_AudioRewind,	spawn,		SHCMD("mpc seek -10; pkill -RTMIN+11 dwmblocks") },
	{ 0, XF86XK_AudioForward,	spawn,		SHCMD("mpc seek +10; pkill -RTMIN+11 dwmblocks") },
	{ 0, XF86XK_AudioMedia,		spawn,		SHCMD("st -e ncmpcpp") },
	{ 0, XF86XK_PowerOff,		spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Shutdown computer?\")\" = Yes ] && sudo -A shutdown -h now") },
	{ 0, XF86XK_Calculator,		spawn,		SHCMD("st -e bc -l") },
	{ 0, XF86XK_Sleep,		spawn,		SHCMD("sudo -A zzz") },
	{ 0, XF86XK_WWW,		spawn,		SHCMD("$BROWSER") },
	{ 0, XF86XK_DOS,		spawn,		SHCMD("st") },
	{ 0, XF86XK_ScreenSaver,	spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,		spawn,		SHCMD("st -e htop") },
	{ 0, XF86XK_Mail,		spawn,		SHCMD("st -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,		spawn,		SHCMD("st -e lf /") },
	/* { 0, XF86XK_Battery,		spawn,		SHCMD("") }, */
	{ 0, XF86XK_Launch1,		spawn,		SHCMD("xset dpms force off") },
	{ 0, XF86XK_TouchpadToggle,	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,	spawn,		SHCMD("synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOn,		spawn,		SHCMD("synclient TouchpadOff=0") },
	{ 0,	XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 5; pkill -RTMIN+2 dwmblocks") },
	{ 0,	XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 5; pkill -RTMIN+2 dwmblocks") },
	{ ShiftMask,	XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -set 1; pkill -RTMIN+2 dwmblocks") },
	{ ShiftMask,	XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -set 100; pkill -RTMIN+2 dwmblocks") },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        setfloating,	{.i=True} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
