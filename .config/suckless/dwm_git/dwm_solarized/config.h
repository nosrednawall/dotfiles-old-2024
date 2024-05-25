/* See LICENSE file for copyright and license details. */
/*imports*/
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int tabModKey = 0x40;
static const unsigned int tabCycleKey = 0x17;
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 28;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = {	"CaskaydiaMono Nerd Font:size=15:style=Regular:antialias=true:pixelsize=17"};

/*Tema Solarized Dark*/
static const char col_1[]       = "#002b36";
static const char col_2[]       = "#93a1a1";
static const char col_3[]       = "#ea6962";
static const char col_4[]       = "#e78a4e";
static const char col_5[]       = "#2aa198";

static const char *colors[][3]      = {
	/*                      fg      bg   border   */
	[SchemeNorm]       = { col_2, col_1, col_1 },
	[SchemeSel]        = { col_2, col_1, col_5 },
	[SchemeStatus]     = { col_1, col_1, col_1 }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]    = { col_1, col_5, col_3 }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm]   = { col_2, col_1, col_1 }, // Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel]    = { col_2, col_1, col_1 }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm]   = { col_2, col_1, col_1 }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "ranger", NULL };
const char *spcmd3[] = {"bitwarden", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"bitwarden",   spcmd3},
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 3;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                       instance		title       tags mask     isfloating		monitor */
	{ "Gimp",						NULL,		NULL,		0,				1,				-1 },
	{ "copyq",						NULL,		NULL,		0,				1,				-1 },
	{ "mpv",						NULL,		NULL,		0,				1,				-1 },
	{ NULL,		  "spterm",		NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,		  "spfm",		NULL,		SPTAG(1),		1,			 -1 },
	{ NULL,		  "keepassxc",	NULL,		SPTAG(2),		0,			 -1 },
};

/* layout(s) */
static const float mfact     = 0.65; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ ">M>",      centeredfloatingmaster }, /* first entry is default */
	{ "|M|",      centeredmaster },
	{ "[]=",      tile },
	{ "[M]",      monocle },

	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
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
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };
//static const char scratchpadname[] = "scratchpad";
//static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

/* atalhos teclado */
static const Key keys[] = {
	/* modifier                     key        		function        argument */
	{ MODKEY,                       XK_p,      		spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, 		spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      		togglebar,      {0} },
	{ MODKEY,            			XK_s,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            			XK_r,	   togglescratch,  {.ui = 1 } },
	{ MODKEY,            			XK_n,	   togglescratch,  {.ui = 2 } },

	/*Modimentacao das janelas*/
	{ MODKEY,                       XK_Right,      	focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Left,      	focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Up,      	incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Down,      	incnmaster,     {.i = -1 } },
	{ MODKEY,           			XK_Up,      	setmfact,       {.f = -0.05} },
	{ MODKEY,             			XK_Down,      	setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, 		zoom,           {0} },
	{ MODKEY,                       XK_Tab,    		view,           {0} },


	{ MODKEY|ShiftMask,             XK_c,      		killclient,     {0} },
	{ MODKEY,                       XK_space,  		setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  		togglefloating, {0} },
	{ MODKEY,                       XK_0,      		view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      		tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  		focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 		focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  		tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 		tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)

	{ MODKEY|ShiftMask,             XK_q,      						quit,           {0} },
	{ MODKEY|ShiftMask,				XK_r,      						quit,           {1} },

	// Alt tab
	{ MODKEY|ShiftMask,             XK_w,      winview,        {0} },
	{ Mod1Mask,                     XK_Tab,    alttab,         {0} },

	/*minhas alterações*/

	//Layouts
	{ MODKEY,                       	XK_F1,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       	XK_F2,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,              				XK_F3,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,              				XK_F4,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,             				XK_F5,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,             				XK_F6,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,              				XK_F7,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,              				XK_F8,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,             				XK_F9,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY,                       	XK_F10,     setlayout,      {.v = &layouts[9]} },
	{ MODKEY,             				XK_F11,     setlayout,      {.v = &layouts[10]} },
	{ MODKEY,             				XK_F12,     setlayout,      {.v = &layouts[11]} },
	{ MODKEY|ShiftMask,              	XK_F1,      setlayout,      {.v = &layouts[12]} },
	{ MODKEY|ShiftMask,                 XK_F2,      setlayout,      {.v = &layouts[13]} },

	//Gaps
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },

	/*Meus atalhos*/
	{ ControlMask|Mod1Mask,         XK_l,                           spawn,          SHCMD("~/.local/bin/dwm/slock_personalizado") },
	{ 0,					        XK_Caps_Lock,                   spawn,          SHCMD("~/.local/bin/dwm/som_capslock_numlock") },
	{ 0,					        XK_Num_Lock,                    spawn,          SHCMD("~/.local/bin/dwm/som_capslock_numlock") },
	{ 0,					        XK_Scroll_Lock,                 spawn,          SHCMD("~/.local/bin/dwm/som_capslock_numlock") },
	{ MODKEY|ShiftMask,             XK_k,                           spawn,          SHCMD("~/.local/bin/dwm/altera-layout-teclado") },

	/*volume pulseaudio*/
	{ 0,                            XF86XK_AudioLowerVolume,        spawn,          SHCMD("~/.local/bin/dwm/diminui_volume") },
	{ 0,                            XF86XK_AudioRaiseVolume,        spawn,          SHCMD("~/.local/bin/dwm/aumenta_volume") },
	{ 0,                            XF86XK_AudioMute,               spawn,          SHCMD("~/.local/bin/dwm/muta_volume") },

	/*Volume Microfone Pulseaudio*/
	{ ControlMask,                  XF86XK_AudioRaiseVolume,        spawn,          SHCMD("~/.local/bin/dwm/aumenta_volume_microfone") },
	{ ControlMask,                  XF86XK_AudioLowerVolume,        spawn,          SHCMD("~/.local/bin/dwm/diminui_volume_microfone") },
	{ ControlMask,                  XF86XK_AudioMute,               spawn,          SHCMD("~/.local/bin/dwm/muta_microfone") },

	/*Player de musica*/
	{ 0,                            XF86XK_AudioPlay,               spawn,          SHCMD("~/.local/bin/dwm/playerctl_play") },
	{ 0,                            XF86XK_AudioStop,               spawn,          SHCMD("~/.local/bin/dwm/playerctl_stop") },
	{ 0,                            XF86XK_AudioPrev,               spawn,          SHCMD("~/.local/bin/dwm/playerctl_prev") },
	{ 0,                            XF86XK_AudioNext,               spawn,          SHCMD("~/.local/bin/dwm/playerctl_next") },

	/*Outros atalhos teclado*/
	{ 0,                            XF86XK_HomePage,                spawn,          SHCMD("~/.local/bin/dwm/homepage_program") },
	{ 0,                            XF86XK_Mail,                    spawn,          SHCMD("~/.local/bin/dwm/mail_program") },
	{ 0,                            XF86XK_Search,                  spawn,          SHCMD("~/.local/bin/dwm/search_program") },
	{ 0,                            XF86XK_Calculator,              spawn,          SHCMD("~/.local/bin/dwm/calculator_program") },

	/*Printscreen*/
	{ MODKEY|ShiftMask,             XK_s,                           spawn,          SHCMD("~/.local/bin/dwm/print_edita") },
	{ 0,                            XK_Print,                       spawn,          SHCMD("~/.local/bin/dwm/print_copia") },

	/*Brilho tela notebook*/
	{ 0,							XF86XK_MonBrightnessUp,			spawn,          SHCMD("~/.local/bin/dwm/brilho_tela_aumenta") },
	{ 0,							XF86XK_MonBrightnessDown,		spawn,          SHCMD("~/.local/bin/dwm/brilho_tela_diminui") },

	/*Dmenus*/
	{ MODKEY|ShiftMask,             XK_e,                           spawn,          SHCMD("~/.local/bin/dmenu/dmenu-saida-sistema" ) },
	{ ControlMask|Mod1Mask,         XK_p,                           spawn,          SHCMD("~/.local/bin/dmenu/dmenu-pass" ) },
	{ MODKEY|ShiftMask,				XK_w,							spawn,			SHCMD("~/.local/bin/dmenu/dmenu-controle-monitor" ) },
	{ MODKEY|ShiftMask,             XK_v,                           spawn,          SHCMD("~/.local/bin/dmenu/dmenu-controle-som") },

	/*Rofi menus*/
	{ MODKEY,						XK_d,	   						spawn,          SHCMD("~/.local/bin/dwm/roficmd") },

	/*Lancamento Programas*/
	{ MODKEY,						XK_w,							spawn,			SHCMD("google-chrome" ) },
	{ MODKEY,						XK_f,							spawn,			SHCMD("pcmanfm" ) }
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
