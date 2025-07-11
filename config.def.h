/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 3; /* border pixel of windows */
static const unsigned int gappx = 5;    /* gaps between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int systraypinning =
    0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
          X */
static const unsigned int systrayonleft =
    0; /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 3; /* systray spacing */
static const int systraypinningfailfirst =
    1; /* 1: if pinning fails, display systray on the first monitor, False:
          display systray on the last monitor*/
static const int showsystray = 1; /* 0 means no systray */
static const int showbar = 1;     /* 0 means no bar */
static const int topbar = 1;      /* 0 means bottom bar */
static const char *fonts[] = {"JetBrainsMono Nerd Font:weight=medium:size=11",
                              "Symbols Nerd Font:weight=medium:size=12",
                              "Font Awesome 6 Free:weight=medium:size=12"};
static const char dmenufont[] = "JetBrainsMono Nerd Font:weight=medium:size=14";
static char normbgcolor[] = "#2E3440";
static char normbordercolor[] = "#2E3440";
static char normfgcolor[] = "#8FBCBB";
static char selfgcolor[] = "#D8DEE9";
static char selbordercolor[] = "#81A1C1";
static char selbgcolor[] = "#3B4252";
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

static const char *const autostart[] = {
    /* Autostart applications for dwm */
    /* Autostart slstatus */
    "slstatus", NULL, "dex", "--autostart", "--environment", "i3", NULL,
    /* Autostart terminal */
    "kitty", NULL, NULL /* terminate */
};

/* tagging */
// static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = {" ", " ", " ", " ", " ",
                             " ", " ", " ", " "};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"firefox", NULL, NULL, 1 << 1, 1, -1},
    {"Thunar", NULL, NULL, 1 << 2, 1, -1},
    {"Code", NULL, NULL, 1 << 3, 0, -1},
    {"TelegramDesktop", NULL, NULL, 1 << 4, 1, -1},
    {"Gimp", NULL, NULL, 1 << 5, 1, -1},
    {"Yad", NULL, NULL, 1 << 7, 1, -1},
    {"steam_proton", NULL, NULL, 1 << 7, 1, -1},
    {"PortProton", NULL, NULL, 1 << 7, 1, -1},
    {"lgc.exe", NULL, NULL, 1 << 7, 1, -1},
    {"worldoftanks.exe", NULL, NULL, 1 << 7, 1, -1},
    {"pavucontrol", NULL, NULL, 0, 1, -1},
    {"Lxappearance", NULL, NULL, 0, 1, -1},
    {"Hiddify", NULL, NULL, 0, 1, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"󰝘", tile}, /* first entry is default */
    {"", NULL},  /* no layout function means floating behavior */
    {"", monocle},
};

/* key definitions */
#define MOD4KEY Mod4Mask
#define MOD1KEY Mod1Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MOD4KEY, KEY, view, {.ui = 1 << TAG}},                                      \
      {MOD4KEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},              \
      {MOD4KEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                       \
      {MOD4KEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

#include <X11/XF86keysym.h>

/* commands */
/* component of dmenucmd, manipulated in spawn() */
static char dmenumon[2] = "0";
static const char *dmenucmd[] = {"dmenu_run", "-m",  dmenumon,       "-fn",
                                 dmenufont,   "-nb", normbgcolor,    "-nf",
                                 normfgcolor, "-sb", selbordercolor, "-sf",
                                 selfgcolor,  NULL};
static const char *termcmd[] = {"kitty", NULL};
static const char *browser[] = {"firefox", NULL};
static const char *filemgr[] = {"thunar", NULL};
static const char *editor[] = {"kitty", "-e", "nvim", NULL};
static const char *zellicmd[] = {"kitty", "-e", "zellij", NULL};
static const char *roficmd[] = {"rofi", "-show", "drun", NULL};
static const char *exitcmd[] = {
    "rofi",
    "-show",
    "power-menu",
    "-modi",
    "power-menu:rofi-power-menu --choices=logout/shutdown/reboot",
    NULL};

static const char *up_vol[] = {"pactl", "set-sink-volume", "@DEFAULT_SINK@",
                               "+10%", NULL};
static const char *down_vol[] = {"pactl", "set-sink-volume", "@DEFAULT_SINK@",
                                 "-10%", NULL};
static const char *mute_vol[] = {"pactl", "set-sink-mute", "@DEFAULT_SINK@",
                                 "toggle", NULL};

static const Key keys[] = {
    /* modifier                     key        function        argument */
    {MOD1KEY, XK_Return, spawn, {.v = zellicmd}},
    {MOD4KEY, XK_Return, spawn, {.v = termcmd}},
    {MOD1KEY, XK_d, spawn, {.v = dmenucmd}},
    {MOD4KEY, XK_d, spawn, {.v = roficmd}},
    {MOD4KEY, XK_v, spawn, {.v = editor}},
    {MOD4KEY, XK_n, spawn, {.v = filemgr}},
    {MOD4KEY, XK_w, spawn, {.v = browser}},
    {MOD4KEY, XK_b, togglebar, {0}},
    {MOD4KEY, XK_j, focusstack, {.i = +1}},
    {MOD4KEY, XK_k, focusstack, {.i = -1}},
    {MOD4KEY, XK_Left, focusstack, {.i = +1}},
    {MOD4KEY, XK_Right, focusstack, {.i = -1}},
    {MOD4KEY, XK_i, incnmaster, {.i = +1}},
    {MOD4KEY, XK_p, incnmaster, {.i = -1}},
    {MOD4KEY, XK_h, setmfact, {.f = -0.05}},
    {MOD4KEY, XK_l, setmfact, {.f = +0.05}},
    {MOD4KEY | ShiftMask, XK_Return, zoom, {0}},
    {MOD4KEY, XK_Tab, view, {0}},
    {MOD4KEY | ShiftMask, XK_q, killclient, {0}},
    {MOD4KEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MOD4KEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MOD4KEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MOD4KEY, XK_space, setlayout, {0}},
    {MOD4KEY | ShiftMask, XK_space, togglefloating, {0}},
    {MOD4KEY, XK_0, view, {.ui = ~0}},
    {MOD4KEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MOD4KEY, XK_comma, focusmon, {.i = -1}},
    {MOD4KEY, XK_period, focusmon, {.i = +1}},
    {MOD4KEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MOD4KEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MOD4KEY, XK_minus, setgaps, {.i = -1}},
    {MOD4KEY, XK_equal, setgaps, {.i = +1}},
    {MOD4KEY | ShiftMask, XK_equal, setgaps, {.i = 0}},
    {MOD4KEY, XK_F5, xrdb, {.v = NULL}},
    {MOD1KEY, XK_Right, viewnext, {0}},
    {MOD1KEY, XK_Left, viewprev, {0}},
    {MOD1KEY | ShiftMask, XK_Right, tagtonext, {0}},
    {MOD1KEY | ShiftMask, XK_Left, tagtoprev, {0}},
    {MOD1KEY | ShiftMask, XK_e, quit, {0}},
    {MOD4KEY | ShiftMask, XK_e, spawn, {.v = exitcmd}},
    {0, XF86XK_AudioMute, spawn, {.v = mute_vol}},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = down_vol}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = up_vol}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8)};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MOD4KEY, Button1, movemouse, {0}},
    {ClkClientWin, MOD4KEY, Button2, togglefloating, {0}},
    {ClkClientWin, MOD4KEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MOD4KEY, Button1, tag, {0}},
    {ClkTagBar, MOD4KEY, Button3, toggletag, {0}},
};
