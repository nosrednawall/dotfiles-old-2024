/* See LICENSE file for copyright and license details. */
/*imports*/
#include <X11/XF86keysym.h>
#include "tatami.c"
#include "tcl.c"
#include "layouts.c"
#include "fibonacci.c"

/* appearance */
static const unsigned int borderpx         = 5;        /* border pixel of windows */
static const unsigned int gappx            = 10;       /* gaps between windows */
static const unsigned int snap             = 32;       /* snap pixel */
static const unsigned int systraypinning   = 0;        /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft    = 0;        /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing   = 4;        /* systray spacing */
static const int systraypinningfailfirst   = 1;        /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray               = 1;        /* 0 means no systray */
static const int showbar                   = 1;        /* 0 means no bar */
static const int topbar                    = 1;        /* 0 means bottom bar */
static const int user_bh                   = 0;        /* 2 is the default spacing around the bar's font */
static const char *fonts[]                 = {
	"Comic code:size=12:antialias=true:autohint=true:pixelsize=16",
	"Mononoki Nerd Font:style=Bold:size=12:antialias=true:autohint=true:pixelsize=16",
	"DejaVu Sans Mono for Powerline:size=12:pixelsize=16"
};
/*gruvbox2*/
static const char col_1[]       = "#32302f";
static const char col_2[]       = "#73675c";
static const char col_3[]       = "#dfbf8e";
static const char col_4[]       = "#fbf1c7";
static const char col_5[]       = "#B8bb26";
static const char col_6[]       = "#C42824";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]       = { col_3, col_1, col_1 },
	[SchemeSel]        = { col_3, col_2, col_3 },
	[SchemeStatus]     = { col_3, col_1, col_1 }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]    = { col_1, col_3, col_5 }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm]   = { col_3, col_1, col_1 }, // Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel]    = { col_3, col_1, col_3 }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm]   = { col_3, col_1, col_1 }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] =   { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
//static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
//static const char *tags[] = { "󰞷","","","","","","","",""};
//static const char *tags[] = { "Term", "Emacs", "Firefox", "Config", "Chat", "Tools", "Music", "Misc", "Misc"};
//static const char *tags[] = { "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };
//static const char *tags[] = { "Um", "Dois", "Treis", "Quatro", "Cinco", "Seis", "Sete", "Oito", "Nove" };
//static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

static const unsigned int ulinepad      = 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                       instance		title       tags mask     isfloating   monitor */
	{ "Gimp",			  NULL,		NULL,		0,		1,		-1 },
	{ "copyq",			  NULL,		NULL,		0,		1,		-1 },
	{ "openboard",			  NULL,		NULL,	   1 << 8,		1,		-1 },
	{ "mpv",			  NULL,          NULL,           0,              1,		-1 },
      /*{ "Spotube",		     "spotube",		NULL,	   1 << 6,              0,              -1 },
	{ "Spotify",		     "spotify",		NULL,	   1 << 6,              0,              -1 },
	{ "discord",		     "discord",		NULL,	   1 << 4,              0,              -1 },
	{ "TelegramDesktop","telegram-desktop",		NULL,	   1 << 4,              0,              -1 },
	{ "QtPass",                   "qtpass",		NULL,	   1 << 5,              0,              -1 },
	{ "Bitwarden",             "bitwarden",		NULL,	   1 << 5,              0,              -1 },
	{ "Blueman-manager", "blueman-manager",		NULL,		0,		1,		-1 },
	{ "Emacs",		       "emacs",		NULL,	   1 << 1,		0,		-1 },
	{ "Thunar",		      "thunar",		NULL,	   1 << 3,		0,		-1 },
	{ "Firefox-esr",		  NULL,		NULL,	   1 << 2,		0,		-1 },
	*/
};

/* layout(s) */
static const float mfact          = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster          = 1;    /* number of clients in master area */
static const int resizehints      = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen   = 1; /* 1 will force focus on the fullscreen window */
static const Layout layouts[]     = {
	/* symbol     arrange function */
	{ "[]=",      tile      },    /* first entry is default */
	{ "><>",      NULL      },    /* no layout function means floating behavior */
	{ "[M]",      monocle   },
	{ "|+|",      tatami    },
	{ "|||",      tcl       },
	{ "[D]",      deck      },
	{ "HHH",      grid      },
	{ "[@]",      spiral    },
	{ "[\\]",     dwindle   },
	{ "TTT",      bstack    },
	{ "===",      bstackhoriz },
	{  NULL,      NULL      }

};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/*  for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2]        = "0";
static const char *dmenucmd[]  = { "dmenu_run", NULL };
static const char *roficmd[]   = { "/bin/sh", "-c", "rofi -modi 'window,drun,ssh,combi' -font 'Comic code 15' -show drun -icon-theme 'Gruvbox' -show-icons -theme 'gruvbox-dark' ", NULL };
static const char *termcmd[]   = { "kitty", "--single-instance", NULL };

/* scratch pad */
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

/* brilho da tela */
static const char *brighter[] = { "brightnessctl", "set", "10%+", NULL };
static const char *dimmer[]   = { "brightnessctl", "set", "10%-", NULL };

/* atalhos teclado */
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,			XK_d,	   spawn,          {.v = roficmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_s,      togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },

	/*Padra
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	*/
	/*minhas alterações*/
	{ MODKEY|ShiftMask,             XK_Right,  rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,   rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_Right,  focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Left,   focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Up,     incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Down,   incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_Down,   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Up,     setmfact,       {.f = +0.05} },

	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY,                       XK_a,      setlayout,      {.v = &layouts[9]} },
	{ MODKEY,                       XK_z,      setlayout,      {.v = &layouts[10]} },

	{ MODKEY|ControlMask,		XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,		XK_r,      quit,           {1} },

	/*Meus atalhos*/
	//	{ MODKEY,                       XK_a,                           spawn,          SHCMD("~/.local/bin/dmenu/dmenu-atalhos-programas") },
	{ ControlMask|Mod1Mask,         XK_l,                           spawn,          SHCMD("~/.local/bin/slock_personalizado") },
	/*volume pulseaudio*/
	{ 0,                            XF86XK_AudioLowerVolume,        spawn,          SHCMD("~/.local/bin/diminui_volume") },
	{ 0,                            XF86XK_AudioRaiseVolume,        spawn,          SHCMD("~/.local/bin/aumenta_volume") },
	{ 0,                            XF86XK_AudioMute,               spawn,          SHCMD("~/.local/bin/muta_volume") },

    /*Volume Microfone Pulseaudio*/
	{ ControlMask,                  XF86XK_AudioRaiseVolume,        spawn,          SHCMD("~/.local/bin/aumenta_volume_microfone") },
	{ ControlMask,                  XF86XK_AudioLowerVolume,        spawn,          SHCMD("~/.local/bin/diminui_volume_microfone") },
	{ ControlMask,                  XF86XK_AudioMute,               spawn,          SHCMD("~/.local/bin/muta_microfone") },
	{ 0,                            XF86XK_AudioPlay,               spawn,          SHCMD("~/.local/bin/playerctl_play") },
	{ 0,                            XF86XK_AudioStop,               spawn,          SHCMD("~/.local/bin/playerctl_stop") },
	{ 0,                            XF86XK_AudioPrev,               spawn,          SHCMD("~/.local/bin/playerctl_prev") },
	{ 0,                            XF86XK_AudioNext,               spawn,          SHCMD("~/.local/bin/playerctl_next") },
	{ 0,                            XF86XK_HomePage,                spawn,          SHCMD("~/.local/bin/homepage_program") },
	{ 0,                            XF86XK_Mail,                    spawn,          SHCMD("~/.local/bin/mail_program") },
	{ 0,                            XF86XK_Search,                  spawn,          SHCMD("~/.local/bin/search_program") },
	{ 0,                            XF86XK_Calculator,              spawn,          SHCMD("~/.local/bin/calculator_program") },

	{ MODKEY|ShiftMask,             XK_s,                           spawn,          SHCMD("~/.local/bin/print_edita") },
	{ 0,                            XK_Print,                       spawn,          SHCMD("~/.local/bin/print_copia") },
	{ 0,                            XF86XK_MonBrightnessDown,       spawn,          {.v = dimmer } },
	{ 0,                            XF86XK_MonBrightnessUp,         spawn,          {.v = brighter } },
	{ MODKEY,                       XK_q,                           spawn,          SHCMD("~/.local/bin/dmenu/dmenu-power" ) },
	{ ControlMask|Mod1Mask,         XK_p,                           spawn,          SHCMD("~/.local/bin/dmenu/dmenu-pass" ) },
	{ MODKEY,			XK_e,				spawn,		SHCMD("~/.local/bin/dmenu/dmenu-monitor" ) },
	{ MODKEY,                       XK_w,                           spawn,          SHCMD("~/.local/bin/dmenu/dmenu-pulseaudio-sink") }
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */

static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
