/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static unsigned int borderpx        = 2;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 5};
static unsigned int snap            = 32;       /* snap pixel */
static int showbar                  = 1;        /* 0 means no bar */
static int topbar                   = 1;        /* 0 means bottom bar */
#define ICONSIZE (bh - 10)                      /* icon size */
#define ICONSPACING (bh - 12)                   /* space between icon and title */
static const char buttonbar[]       = "";
static const char powerbutton[]     = "";
static const char statussep         = ';';      /* separator between status bars */
static const unsigned int systrayspacing = 16;  /* systray spacing */
static const int showsystray             = 1;   /* 0 means no systray */
static char font[]                  = "monospace:pixelsize=18";
static char dmenufont[]             = "monospace:pixelsize=18";
static const char *fonts[]          = { font };
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

static const unsigned int baralpha = 0xF0;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

static const char *const autostart[] = {
	"dwmblocks", NULL,
	NULL /* terminate */
};

static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const unsigned int ulinepad	    = 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		        = 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class              instance    title       tags mask     isfloating   monitor */
	{ "floatingterm",     NULL,       NULL,       0,            1,           -1 },
	{ "Gimp",             NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",          NULL,       NULL,       1 << 8,       0,           -1 },
};

/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
	/* monitor  bar    alignment               widthfunc              drawfunc              clickfunc           name */
	{ -1,       0,     BAR_ALIGN_CENTER,       width_tags,            draw_tags,            click_tags,         "tags" },
	{ -1,       0,     BAR_ALIGN_LEFT_LEFT,    width_stbutton,        draw_stbutton,        click_stbutton,     "statusbutton" },
	{ -1,       0,     BAR_ALIGN_LEFT_LEFT,    width_ltsymbol,        draw_ltsymbol,        click_ltsymbol,     "layout" },
	{ -1,       0,     BAR_ALIGN_LEFT_LEFT,    width_wintitle,        draw_wintitle,        click_wintitle,     "wintitle" },
	{ -1,       0,     BAR_ALIGN_LEFT_LEFT,    width_status2d_es,     draw_status2d_es,     click_statuscmd_es, "status2d_es" },
	{ -1,       0,     BAR_ALIGN_RIGHT_RIGHT,  width_powerbutton,     draw_powerbutton,     click_powerbutton,  "powerbutton" },
	{ -1,       0,     BAR_ALIGN_RIGHT_RIGHT,  width_systray,         draw_systray,         click_systray,      "systray" },
	{ -1,       0,     BAR_ALIGN_RIGHT_RIGHT,  width_status2d,        draw_status2d,        click_statuscmd,    "status2d" },
};

/* layout(s) */
static float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod3Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|Mod4Mask,              KEY,      tagnextmon,     {.ui = 1 << TAG} }, \
	{ MODKEY|Mod4Mask|ShiftMask,    KEY,      tagprevmon,     {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-l", "20", "-c", "-F", NULL };
static const char *lockcmd[] = { "slock", NULL };
static const char *powermenucmd[] = { "dwm-powermenu", NULL };
#define TERMINAL_ENVVAR "TERMINAL"
static char *floatingtermcmd[]  = { "st", "-c", "floatingterm", NULL };
static const char *layoutmenu_cmd = "dwm-layoutmenu";
static const char *upvol[] = { "volume", "up", NULL };
static const char *downvol[] = { "volume", "down", NULL };
static const char *mutevol[] = { "volume", "mute", NULL };
static const char *laptop_brightness_up[]   = { "sudo", "brightness-laptop", "up", NULL };
static const char *laptop_brightness_down[] = { "sudo", "brightness-laptop", "down", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font",               STRING,  &font },
		{ "dmenufont",          STRING,  &dmenufont },
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};


#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,             spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,        spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return,        spawn,          {.v = floatingtermcmd} },
	{ MODKEY,                       XK_equal,         spawn,          SHCMD("brightness up") },
	{ MODKEY,                       XK_minus,         spawn,          SHCMD("brightness down") },
	{ MODKEY,                       XK_apostrophe,    spawn,          {.v = lockcmd} },
	{ MODKEY|ShiftMask,             XK_apostrophe,    spawn,          {.v = powermenucmd} },
	{ MODKEY,                       XK_b,             togglebar,      {0} },
	{ MODKEY,                       XK_j,             focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,             focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,             incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,             incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_comma,         setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_period,        setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,             movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,             movestack,      {.i = -1 } },
	// { MODKEY|ShiftMask,             XK_Return,        zoom,           {0} },
	{ MODKEY,                       XK_Tab,           view,           {0} },
	{ MODKEY,                       XK_q,             killclient,     {0} },
	{ MODKEY,                       XK_t,             setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,             setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,             setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,             setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,             setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,         setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,         togglefloating, {0} },
	{ MODKEY,                       XK_y,             togglesticky,   {0} },
	{ MODKEY|ShiftMask,		        XK_h,             cyclelayout,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,             cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_0,             view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,             tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_l,             focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_h,             focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,         tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,        tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_bracketleft,   setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_bracketright,  setgaps,        {.i = 5 } },
	{ MODKEY|ShiftMask,             XK_bracketleft,   setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_bracketright,  setgaps,        {.i = GAP_TOGGLE} },
	{ MODKEY|ShiftMask,             XK_n,             tagnextmon,     {.ui = 0  } },
	{ MODKEY|ShiftMask,             XK_p,             tagprevmon,     {.ui = 0  } },
	TAGKEYS(                        XK_1,                             0)
	TAGKEYS(                        XK_2,                             1)
	TAGKEYS(                        XK_3,                             2)
	TAGKEYS(                        XK_4,                             3)
	TAGKEYS(                        XK_5,                             4)
	TAGKEYS(                        XK_6,                             5)
	TAGKEYS(                        XK_7,                             6)
	TAGKEYS(                        XK_8,                             7)
	TAGKEYS(                        XK_9,                             8)
	{ MODKEY|ShiftMask,             XK_q,             quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,             quit,           {1} },
  { 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                       XF86XK_AudioMute, spawn, {.v = mutevol } },
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
  { 0,                       XF86XK_MonBrightnessUp, spawn, {.v = laptop_brightness_up } },
  { 0,                       XF86XK_MonBrightnessDown, spawn, {.v = laptop_brightness_down } },
};

/* button definitions */
/* click can be ClkButton, ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkButton,            0,              Button1,        spawn,          {.v = dmenucmd } },
	{ ClkPowerButton,       0,              Button1,        spawn,          {.v = powermenucmd } },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        layoutmenu,     {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1 } },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2 } },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3 } },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4 } },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5 } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

