/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "nogroup"; // use "nobody" for arch

static const char *colorname[NUMCOLS] = {
	[INIT] =   "black",     /* after initialization */
	[INPUT] =  "#005577",   /* during input */
	[FAILED] = "#CC3333",   /* wrong password */
	[CAPS] =   "red",       /* CapsLock on */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;

/* Enable blur */
#define BLUR
/* Set blur radius */
static const int blurRadius = 5;
/* Enable Pixelation */
//#define PIXELATION
/* Set pixelation radius */
static const int pixelSize = 10;

