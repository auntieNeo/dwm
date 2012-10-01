#define INSERTMODE 1
#define VIEWMODE 2
#define TOGGLEVIEWMODE 3
#define TAGMODE 4
#define TOGGLETAGMODE 5
#define RENAMETAGMODE 6
#define RENAMETAG_INPUT 7

typedef struct {
  KeySym keysym;
  unsigned int tags;
} TagKey;

static char *renamed_tags[LENGTH(tags)];

static void defkeypress(XEvent *e);
static void defgrabkeys(void);
static void setkeymode(const Arg *arg);

static unsigned int keymode = INSERTMODE;
static unsigned int renametag;
