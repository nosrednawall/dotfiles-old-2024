#define PATH(name)                      "/home/anderson/.dotfiles/.config/suckless/dwmblocks/scripts/"name

//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/											/*Update Interval*/	/*Update Signal*/
	{"", PATH("sb-music"), 		1, 					1},
	{"", PATH("sb-update"), 		1, 					1},
	{"", PATH("sb-loadavg"), 		1, 					1},
	{"", PATH("sb-memory"), 		1, 					1},
	{"", PATH("sb-disk"), 			1, 					1},
	{"", PATH("sb-wifi"), 			1, 					1},
	{"", PATH("sb-ethernet"), 		1, 					1},
    {"", PATH("sb-brightness"), 	1, 					1},
    {"", PATH("sb-volume"), 		1, 					2},
    {"", PATH("sb-mic"), 			1, 					3},
    {"", PATH("sb-record"), 		1, 					4},
    {"", PATH("sb-keyboard"), 		1, 					5},
    {"", PATH("sb-battery"), 		1, 					6},
    {"", PATH("sb-date"), 			1, 					7},
    {"", PATH("sb-hour"), 			1, 					8},
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = "\0";
static unsigned int delimLen = 5;
