/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "Kochi Mincho Gothic 7";  // FIXME: use a better font for roman characters
/*
static const char normbordercolor[] = "#808080";
static const char normbgcolor[]     = "#808080";
static const char normfgcolor[]     = "#000000";
static const char selbordercolor[]  = "#edf280";
static const char selbgcolor[]      = "#edf280";
static const char selfgcolor[]      = "#000000";
*/
static const char normbordercolor[] = "#ffffff";
static const char normbgcolor[]     = "#ffffff";
static const char normfgcolor[]     = "#000000";
static const char selbordercolor[]  = "#000000";
static const char selbgcolor[]      = "#000000";
static const char selfgcolor[]      = "#ffffff";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
//static const char *tags[] = { "1main", "2web", "3irc", "4code", "5sch", "6ja", "7music", "8dict", "9misc" };
//static const char *tags[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

#include "modal.pre.h"

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "xbmc.bin", NULL,       NULL,       0,            True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

#include "bstack.c"
#include "bstackhoriz.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* custom function declarations */

/* key definitions */
#define MODKEY Mod4Mask
#define VOLKEY ControlMask|ShiftMask|Mod1Mask
#define CMUSKEY ControlMask|ShiftMask
#define MISCKEY Mod1Mask|Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,              KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask|ShiftMask,    KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvt", NULL };
//static const char *termcmd[]  = { "Eterm", "--theme", "xterm", "--foreground-color", "white", "--font-fx", "bottom_right #777777", "--trans", "--buttonbar", "0", "--scrollbar", "0", NULL };
//static const char *termcmd[]  = { "Eterm", "--theme", "xterm", "--foreground-color", "black", "--font-fx", "bottom_right #FFFFFF", "--trans", "--buttonbar", "0", "--scrollbar", "0", NULL };
/* volume */
static const char *volup[] = { "amixer", "-q", "-c", "0", "set", "Master", "2dB+", NULL };
static const char *voldown[] = { "amixer", "-q", "-c", "0", "set", "Master", "1dB-", NULL };
/* cmus */
static const char *cmusnext[] = { "cmus-remote", "--next", NULL };
static const char *cmusprev[] = { "cmus-remote", "--prev", NULL };
static const char *cmusvolup[] = { "cmus-remote", "--volume", "+10%", NULL };
static const char *cmusvoldown[] = { "cmus-remote", "--volume", "-10%", NULL };
static const char *cmusstop[] = { "cmus-remote", "--stop", NULL };
static const char *cmuspause[] = { "cmus-remote", "--pause", NULL };
static const char *cmuscontinue[] = { "cmus-remote", "-C", "toggle continue", NULL };
static const char *cmusrepeat[] = { "cmus-remote", "-C", "toggle repeat", NULL };
static const char *cmusshuffle[] = { "cmus-remote", "-C", "toggle shuffle", NULL };
static const char *brightness_up[] = { "sudo", "brightness_up.sh", NULL };
static const char *brightness_down[] = { "sudo", "brightness_down.sh", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_u,      setkeymode,     {.ui = VIEWMODE} },
	{ MODKEY,                       XK_space,  setkeymode,     {.ui = TOGGLEVIEWMODE} },
	{ MODKEY,                       XK_l,      setkeymode,     {.ui = TAGMODE} },
	{ MODKEY,                       XK_w,      setkeymode,     {.ui = TOGGLETAGMODE} },
	{ MODKEY,                       XK_v,      setkeymode,     {.ui = RENAMETAGMODE} },
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_t,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_n,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_s,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_d,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_k,      killclient,     {0} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_c,      setlayout,      {.v = &layouts[4]} },
//	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_e,      togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|Mod1Mask,              XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|Mod1Mask,              XK_n,      focusmon,       {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_t,      focusmon,       {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_h,      tagmon,         {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_s,      tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
  { VOLKEY,                       XK_Up,     spawn,          {.v = volup } },
  { VOLKEY,                       XK_Down,   spawn,          {.v = voldown } },
  { VOLKEY,                       XK_n,      spawn,          {.v = volup } },
  { VOLKEY,                       XK_t,      spawn,          {.v = voldown } },
  { CMUSKEY,                      XK_Right,  spawn,          {.v = cmusnext } },
  { CMUSKEY,                      XK_Left,   spawn,          {.v = cmusprev } },
  { CMUSKEY,                      XK_s,      spawn,          {.v = cmusnext } },
  { CMUSKEY,                      XK_h,      spawn,          {.v = cmusprev } },
  { CMUSKEY,                      XK_Up,     spawn,          {.v = cmusvolup} },
  { CMUSKEY,                      XK_Down,   spawn,          {.v = cmusvoldown} },
  { CMUSKEY,                      XK_n,      spawn,          {.v = cmusvolup} },
  { CMUSKEY,                      XK_t,      spawn,          {.v = cmusvoldown} },
  { CMUSKEY,                      XK_v,      spawn,          {.v = cmusstop} },
  { CMUSKEY,                      XK_c,      spawn,          {.v = cmuspause} },
  { CMUSKEY,                      XK_w,      spawn,          {.v = cmuscontinue} },
  { CMUSKEY,                      XK_r,      spawn,          {.v = cmusrepeat} },
  { CMUSKEY,                      XK_l,      spawn,          {.v = cmusshuffle} },
  { MISCKEY,                      XK_n,      spawn,          {.v = brightness_up} },
  { MISCKEY,                      XK_t,      spawn,          {.v = brightness_down} },
  { MISCKEY,                      XK_Up,     spawn,          {.v = brightness_up} },
  { MISCKEY,                      XK_Down,   spawn,          {.v = brightness_down} },
};

/* keys used with modal tags */
static TagKey tagkeys[] = {
  { XK_1, 1 },
  { XK_2, 1 << 1 },
  { XK_3, 1 << 2 },
  { XK_4, 1 << 3 },
  { XK_5, 1 << 4 },
  { XK_6, 1 << 5 },
  { XK_7, 1 << 6 },
  { XK_8, 1 << 7 },
  { XK_9, 1 << 8 },
  { XK_0, ~0 },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         Mod1Mask,       Button1,        movemouse,      {0} },
//	{ ClkClientWin,         MODKEY,         Button1,        togglefloating, {0} },
	{ ClkClientWin,         Mod4Mask,       Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

#include "modal.post.h"
