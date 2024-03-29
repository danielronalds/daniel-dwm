/* See LICENSE file for copyright and license details. */

/* Volume and brightness keys */
#include <X11/XF86keysym.h>


/* appearance */
static const unsigned int borderpx       = 1;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const unsigned int gappih         = 20;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 10;  /* vert inner gap between windows */
static const unsigned int gappoh         = 10;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 30;  /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 1;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon               = 'A';
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int showsystray             = 1;   /* 0 means no systray */

/* Indicators: see patch/bar_indicators.h for options */
//static int tagindicatortype              = INDICATOR_TOP_LEFT_SQUARE;
static int tagindicatortype              = INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;
static const int quit_empty_window_count = 0;   /* only allow dwm to quit if no (<= count) windows are open */
static const char *fonts[]               = { "JetBrains Mono:size=13" };
static const char dmenufont[]            = "JetBrains Mono:size=13";

static char c000000[]                    = "#000000"; // placeholder value

static char normfgcolor[]                = "#ebdbb2"; //#bbbbbb
static char normbgcolor[]                = "#282828"; //#222222
static char normbordercolor[]            = "#504945"; //#444444
static char normfloatcolor[]             = "#d79921"; //#db8fd9

/* Active Window border color */
static char selfgcolor[]                 = "#ebdbb2"; //#eeeeee
static char selbgcolor[]                 = "#d79921"; //#005577
static char selbordercolor[]             = "#d79921"; //#005577
static char selfloatcolor[]              = "#d79921"; //#005577

static char titlenormfgcolor[]           = "#ebdbb2"; //#bbbbbb
static char titlenormbgcolor[]           = "#282828"; //#222222
static char titlenormbordercolor[]       = "#504945"; //#444444 
static char titlenormfloatcolor[]        = "#d79921"; //#db8fd9

/* Center title bar color */
static char titleselfgcolor[]            = "#ebdbb2"; //#eeeeee
static char titleselbgcolor[]            = "#d79921"; //#005577
static char titleselbordercolor[]        = "#d79921"; //#005577
static char titleselfloatcolor[]         = "#d79921"; //#005577

static char tagsnormfgcolor[]            = "#ebdbb2"; //#bbbbbb
static char tagsnormbgcolor[]            = "#282828"; //#222222
static char tagsnormbordercolor[]        = "#504945"; //#444444
static char tagsnormfloatcolor[]         = "#d79921"; //#db8fd9

/* Colors for the tag icons */
static char tagsselfgcolor[]             = "#ebdbb2"; //#eeeeee
static char tagsselbgcolor[]             = "#d79921"; //#005577
static char tagsselbordercolor[]         = "#d79921"; //#005577
static char tagsselfloatcolor[]          = "#d79921"; //#005577

static char hidnormfgcolor[]             = "#d79921"; //#005577
static char hidselfgcolor[]              = "#fabd2f"; //#227799
static char hidnormbgcolor[]             = "#282828"; //#222222
static char hidselbgcolor[]              = "#282828"; //#222222

static char urgfgcolor[]                 = "#ebdbb2"; //#bbbbbb
static char urgbgcolor[]                 = "#282828"; //#222222
static char urgbordercolor[]             = "#fb4934"; //#ff0000
static char urgfloatcolor[]              = "#d79921"; //#db8fd9




static char *colors[][ColCount] = {
	/*                       fg                bg                border                float */
	[SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
	[SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
	[SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
	[SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
	[SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
};



static const char *const autostart[] = {
    //"sh", "-c", "/home/daniel/.dwm/dwmbar", NULL,
    "dwmbarstart", NULL,
	NULL /* terminate */
};


/* Tags
 * In a traditional dwm the number of tags in use can be changed simply by changing the number
 * of strings in the tags array. This build does things a bit different which has some added
 * benefits. If you need to change the number of tags here then change the NUMTAGS macro in dwm.c.
 *
 * Examples:
 *
 *  1) static char *tagicons[][NUMTAGS*2] = {
 *         [DEFAULT_TAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I" },
 *     }
 *
 *  2) static char *tagicons[][1] = {
 *         [DEFAULT_TAGS] = { "•" },
 *     }
 *
 * The first example would result in the tags on the first monitor to be 1 through 9, while the
 * tags for the second monitor would be named A through I. A third monitor would start again at
 * 1 through 9 while the tags on a fourth monitor would also be named A through I. Note the tags
 * count of NUMTAGS*2 in the array initialiser which defines how many tag text / icon exists in
 * the array. This can be changed to *3 to add separate icons for a third monitor.
 *
 * For the second example each tag would be represented as a bullet point. Both cases work the
 * same from a technical standpoint - the icon index is derived from the tag index and the monitor
 * index. If the icon index is is greater than the number of tag icons then it will wrap around
 * until it an icon matches. Similarly if there are two tag icons then it would alternate between
 * them. This works seamlessly with alternative tags and alttagsdecoration patches.
 */
static char *tagicons[][NUMTAGS] = {
	[DEFAULT_TAGS]        = { "", "", "", "", "", "", "ﯚ", "", "" },
	[ALTERNATIVE_TAGS]    = { "A", "B", "C", "D", "E", "F", "G", "H", "I" },
	[ALT_TAGS_DECORATION] = { "<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>" },
};


/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	// RULE(.class = "Gimp", .tags = 1 << 4)
	// RULE(.class = "firefox", .tags = 1 << 1) // Spawns firefox on tag 2
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
	/* monitor   bar    alignment         widthfunc                drawfunc                clickfunc                name */
	{ -1,        0,     BAR_ALIGN_LEFT,   width_tags,              draw_tags,              click_tags,              "tags" },
	{  0,        0,     BAR_ALIGN_RIGHT,  width_systray,           draw_systray,           click_systray,           "systray" },
	{ -1,        0,     BAR_ALIGN_LEFT,   width_ltsymbol,          draw_ltsymbol,          click_ltsymbol,          "layout" },
	{ statusmon, 0,     BAR_ALIGN_RIGHT,  width_status,            draw_status,            click_status,            "status" },
	{ -1,        0,     BAR_ALIGN_NONE,   width_wintitle,          draw_wintitle,          click_wintitle,          "wintitle" },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */



static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
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
static const char *dmenucmd[] = {
	"dmenu_run",
	"-m", dmenumon,
	"-fn", dmenufont,
	"-nb", normbgcolor,
	"-nf", normfgcolor,
	"-sb", selbgcolor,
	"-sf", selfgcolor,
	NULL
};
// Applications
static const char *termcmd[]  = { "kitty", NULL };
static const char *browsercmd[]  = { "firefox", NULL };
static const char *filemanagercmd[]  = { "nemo", NULL };
static const char *virtualmachinescmd[]  = { "virt-manager", NULL };

// Utility
static const char *screenshotcmd[]  = { "gnome-screenshot", NULL };
static const char *bluetoothcmd[]  = { "blueman-manager", NULL };

// Brightness command
static const char *brightnessup[] = {"light", "-A", "5", NULL};
static const char *brightnessdown[] = {"light", "-U", "5", NULL};

// Volume command
static const char *volumeup[] = {"pactl", "set-sink-volume", "@DEFAULT_SINK@", "+10%", NULL};
static const char *volumedown[] = {"pactl", "set-sink-volume", "@DEFAULT_SINK@", "-10%", NULL};
//static const char *volumetoggle[] = {"pactl", "set-sink-volume", "@DEFAULT_SINK@", "toggle", NULL};
static const char *volumetoggle[] = {"amixer", "-D","pulse", "sset", "Master", "toggle", NULL};

// Command to refresh the bar
static const char *refreshbar[] = { "refresh", "dwmbar", NULL};

static Key keys[] = {
	/* modifier                     key            function                argument */

    // Applications
	{ MODKEY,                       XK_d,          spawn,                  {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,     spawn,                  {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return,     spawn,                  {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_f,          spawn,                  {.v = filemanagercmd } },
	{ MODKEY|ShiftMask,             XK_v,          spawn,                  {.v = virtualmachinescmd } },

	{ MODKEY|ShiftMask,             XK_s,          spawn,                  {.v = screenshotcmd } },
	{ MODKEY|ShiftMask,             XK_b,          spawn,                  {.v = bluetoothcmd } },

    // Volume Keys
    {0,                             XF86XK_AudioRaiseVolume, spawn,        {.v = volumeup } },
    {0,                             XF86XK_AudioRaiseVolume, spawn,        {.v = refreshbar } }, // Refresh bar
    {0,                             XF86XK_AudioLowerVolume, spawn,        {.v = volumedown } },
    {0,                             XF86XK_AudioLowerVolume, spawn,        {.v = refreshbar } }, // Refresh bar
    {0,                             XF86XK_AudioMute,        spawn,        {.v = volumetoggle } },

    // Brightness Keys
    {0,                             XF86XK_MonBrightnessUp,  spawn,        {.v = brightnessup } },
    {0,                             XF86XK_MonBrightnessUp,  spawn,        {.v = refreshbar } },
    {0,                             XF86XK_MonBrightnessDown,spawn,        {.v = brightnessdown } },
    {0,                             XF86XK_MonBrightnessDown,spawn,        {.v = refreshbar } },

	{ MODKEY,                       XK_b,          togglebar,              {0} },
	{ MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_j,          inplacerotate,          {.i = +2 } }, // same as rotatestack
	{ MODKEY|Mod1Mask,              XK_k,          inplacerotate,          {.i = -2 } }, // same as reotatestack
	{ MODKEY|Mod1Mask|ShiftMask,    XK_j,          inplacerotate,          {.i = +1} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_k,          inplacerotate,          {.i = -1} },
	{ MODKEY,                       XK_Up,         incnmaster,             {.i = +1 } },
	{ MODKEY,                       XK_Down,       incnmaster,             {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },
	{ MODKEY,                       XK_s,          zoom,                   {0} }, // Sets window as master
	{ MODKEY|Mod1Mask,              XK_u,          incrgaps,               {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,          incrgaps,               {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,          incrigaps,              {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,          incrigaps,              {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,          incrogaps,              {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,          incrogaps,              {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,          incrihgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,          incrihgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,          incrivgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,          incrivgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,          incrohgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,          incrohgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,          incrovgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,          incrovgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,          togglegaps,             {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,          defaultgaps,            {0} },
	{ MODKEY,                       XK_Tab,        view,                   {0} },
	{ MODKEY|ShiftMask,             XK_q,          killclient,             {0} },
	{ MODKEY|ShiftMask,             XK_c,          quit,                   {0} },
	{ MODKEY|ShiftMask,             XK_F5,         xrdb,                   {.v = NULL } },

    // Managing Layouts
	{ MODKEY,                       XK_t,          setlayout,              {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,          setlayout,              {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,          setlayout,              {.v = &layouts[2]} },
	{ MODKEY,                       XK_c,          setlayout,              {.v = &layouts[3]} },

	{ MODKEY,                       XK_space,      setlayout,              {0} },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating,         {0} },
	{ MODKEY,                       XK_0,          view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~0 } },
	{ MODKEY,                       XK_comma,      focusmon,               {.i = -1 } },
	{ MODKEY,                       XK_period,     focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } },
	TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	TAGKEYS(                        XK_6,                                  5)
	TAGKEYS(                        XK_7,                                  6)
	TAGKEYS(                        XK_8,                                  7)
	TAGKEYS(                        XK_9,                                  8)
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask           button          function        argument */
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};



