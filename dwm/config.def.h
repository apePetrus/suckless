/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[] = {
    "CaskaydiaCove Nerd Font Mono:style:medium:size=12",
    "CaskaydiaCove Nerd Font Mono:style:medium:size=19"};
static const char dmenufont[] = "CaskaydiaCove Nerd Font Mono:pixelsize=15";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static char *tags[] = {"一", "二", "三", "四", "五"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
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
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
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
// static const char *dmenucmd[] = { "dmenu_run", "-i", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *browsercmd[] = { "librewolf", NULL };

static const Key keys[] = {
	/* modifier	                 key                        function        argument */

	{ MODKEY,	                   XK_p,                      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,	         XK_Return,                 spawn,          {.v = termcmd } },

	/* Brightness and audio */
	{ MODKEY|ShiftMask,             XK_equal,                  spawn,          SHCMD("amixer -q sset Master 5%+ ; pkill -RTMIN+10 dwmblocks")},
	{ MODKEY|ShiftMask,             XK_minus,                  spawn,          SHCMD("amixer -q sset Master 5%- ; pkill -RTMIN+10 dwmblocks")},
	{ MODKEY|ShiftMask,             XK_m,                      spawn,          SHCMD("amixer -q sset Master toggle ; pkill -RTMIN+10 dwmblocks")},
	{ 0,                            XF86XK_MonBrightnessUp,    spawn,          SHCMD("brightnessctl s 5+ ; pkill -RTMIN+10 dwmblocks")},
	{ 0,                            XF86XK_MonBrightnessDown,  spawn,          SHCMD("brightnessctl s 5- ; pkill -RTMIN+10 dwmblocks")},

	/* Common software */
	{ MODKEY,                       XK_w,                      spawn,          {.v = browsercmd}},
	{ MODKEY,                       XK_e,                      spawn,          SHCMD("st -e yazi")},
	{ MODKEY|ShiftMask,             XK_s,                      spawn,          SHCMD("flameshot gui")},
	{ MODKEY|ShiftMask,             XK_g,                      spawn,          SHCMD("steam")},

	/* Quit, reboot, shutdown */
	{ MODKEY|ShiftMask,             XK_e,                      spawn,          SHCMD("~/.local/bin/prompt 'Do you really want to quit?' 'killall dwm'")},
	{ MODKEY|ShiftMask,             XK_x,                      spawn,          SHCMD("~/.local/bin/prompt 'Do you really want to shutdown the system?' " "'loginctl poweroff'")},
	{ MODKEY|ShiftMask,             XK_r,                      spawn,          SHCMD("~/.local/bin/prompt 'Do you really want to reboot the system?' " "'loginctl reboot'")},

	/* Emoji dmenu script */
	{ MODKEY,                       XK_ccedilla,               spawn,          SHCMD("~/.local/bin/dmenuunicode")},

	{ MODKEY,	                   XK_b,                      togglebar,      {0} },
	{ MODKEY,	                   XK_j,                      focusstack,     {.i = +1 } },
	{ MODKEY,	                   XK_k,                      focusstack,     {.i = -1 } },
	{ MODKEY,	                   XK_i,                      incnmaster,     {.i = +1 } },
	{ MODKEY,	                   XK_d,                      incnmaster,     {.i = -1 } },
	{ MODKEY,	                   XK_h,                      setmfact,       {.f = -0.05} },
	{ MODKEY,	                   XK_l,                      setmfact,       {.f = +0.05} },
	{ MODKEY,	                   XK_Return,                 zoom,           {0} },
	{ MODKEY,	                   XK_Tab,                    view,           {0} },

	{ MODKEY|ShiftMask,	         XK_q,                      killclient,     {0} },
	{ MODKEY,	                   XK_f,                      togglefullscr,  {0} },
	{ MODKEY,	                   XK_t,                      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,	                   XK_m,                      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,	                   XK_space,                  setlayout,      {0} },
	{ MODKEY|ShiftMask,	         XK_space,                  togglefloating, {0} },
	{ MODKEY,	                   XK_0,                      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,	         XK_0,                      tag,            {.ui = ~0 } },

	/* Navigation between multi monitor setup */
	{ MODKEY,	                   XK_comma,                  focusmon,       {.i = -1 } },
	{ MODKEY,	                   XK_period,                 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,	         XK_comma,                  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,	         XK_period,                 tagmon,         {.i = +1 } },
    { MODKEY,                       XK_r,                   xrdb,           {.v = NULL } },


// +	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
// +	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
// +	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
// +	{ MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
// +	{ MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
// +	{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
// +	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
// +	{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
// +	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
// +	{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
// +	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
// +	{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
// +	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
// +	{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
// +	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
// +	{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
// +	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
// +	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
// +	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },

	TAGKEYS(	                    XK_1,                      0)
	TAGKEYS(	                    XK_2,                      1)
	TAGKEYS(	                    XK_3,                      2)
	TAGKEYS(	                    XK_4,                      3)
	TAGKEYS(	                    XK_5,                      4)
	TAGKEYS(	                    XK_6,                      5)
	TAGKEYS(	                    XK_7,                      6)
	TAGKEYS(	                    XK_8,                      7)
	TAGKEYS(	                    XK_9,                      8)
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

