/* See LICENSE file for copyright and license details. */
/*imports*/
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {	"Comic code:size=10:antialias=true:autohint=true:pixelsize=16",
					"Mononoki Nerd Font:style=Bold:size=10:antialias=true:autohint=true:pixelsize=16"};
/*gruvbox*/
static const char col_1[]       = "#282828";
static const char col_2[]       = "#695F55";
static const char col_3[]       = "#ebdbb2";
static const char col_4[]       = "#d65d0e";
static const char col_5[]       = "#B8bb26";
static const char col_6[]       = "#cc241d";
static const char col_7[]       = "#689d68";

static const char *colors[][3]      = {
	/*                      fg      bg   border   */
	[SchemeNorm]       = { col_3, col_1, col_1 },
	[SchemeSel]        = { col_3, col_1, col_5 },
	[SchemeStatus]     = { col_1, col_1, col_1 }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]    = { col_1, col_5, col_4 }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm]   = { col_3, col_1, col_1 }, // Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel]    = { col_3, col_1, col_1 }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm]   = { col_3, col_1, col_1 }, // infobar middle  unselected {text,background,not used but cannot be empty}
};
/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                       instance		title       tags mask     isfloating		monitor */
	{ "Gimp",			NULL,		NULL,		0,		1,		-1 },
	{ "copyq",			NULL,		NULL,		0,		1,		-1 },
	{ "mpv",			NULL,		NULL,		0,		1,		-1 },
	//{ "Emacs",			"emacs",	NULL,		1 << 1,		0,		-1 },
	//{ "R_x11",			NULL,		NULL,		1 << 1,		0,		-1 },
	//{ NULL,			NULL,		"R Data Editor",1 << 1,		0,		-1 },
	//{ "rstudio",			"rstudio",	NULL,		1 << 1,		0,		-1 },
	//{ "Soffice",			"soffice",	NULL,           5,		0,		 1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *roficmd[]   = { "/bin/sh", "-c", "rofi -m -4 -modi 'window,drun,ssh,combi' -font 'Comic code 15' -show drun -icon-theme 'Gruvbox' -show-icons -theme 'gruvbox-dark' -sidebar-mode", NULL };
static const char *rofialttabcmd[]   = { "/bin/sh", "-c", "rofi -m -4 -modi 'window' -font 'Comic code 15' -show window -icon-theme 'Gruvbox' -show-icons -theme 'gruvbox-dark' -sidebar-mode", NULL };
/* atalhos teclado */
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,			XK_d,	   spawn,          {.v = roficmd } },
	{ Mod1Mask,			XK_Tab,	   spawn,          {.v = rofialttabcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_s,      togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },

	/*minhas alterações*/
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

	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
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
	{ MODKEY,                       XK_a,                           spawn,          SHCMD("~/.local/bin/dmenu/dmenu-atalhos-programas") },
	{ MODKEY|ShiftMask,             XK_a,                           spawn,          SHCMD("~/.local/bin/dmenu/dmenu-docker-images") },
	{ MODKEY|ControlMask,           XK_a,                           spawn,          SHCMD("~/.local/bin/dmenu/dmenu-docker-lista-funcionando") },
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
	{ 0,				XF86XK_MonBrightnessUp,		spawn,          SHCMD("~/.local/bin/brilho_tela_aumenta") },
	{ 0,				XF86XK_MonBrightnessDown,	spawn,          SHCMD("~/.local/bin/brilho_tela_diminui") },

	{ MODKEY,                       XK_q,                           spawn,          SHCMD("~/.local/bin/dmenu/dmenu-power" ) },
	{ ControlMask|Mod1Mask,         XK_p,                           spawn,          SHCMD("~/.local/bin/dmenu/dmenu-pass" ) },
	{ MODKEY,			XK_e,				spawn,		SHCMD("~/.local/bin/dmenu/dmenu-monitor" ) },
	{ MODKEY,                       XK_w,                           spawn,          SHCMD("~/.local/bin/dmenu/dmenu-pulseaudio-sink") },
	{ MODKEY,                       XK_k,                           spawn,          SHCMD("~/.local/bin/dmenu/dmenu-teclados") }
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
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
