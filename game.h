// Player Struct
typedef struct {
	int worldRow;
	int screenRow;
	int worldCol;
	int screenCol;
	int rdel;
	int cdel;
	int height;
	int width;
	int cDirection; // So the bullet knows which cdel to take
	int aniCounter;
    int aniState;
    int prevAniState;
    int curFrame;
    int numFrames;
    int active;
} PLAYER;

typedef struct {
	int worldRow;
	int worldCol;
	int screenRow;
	int screenCol;
	int rdel;
	int height;
	int width;
	int aniCounter;
    int aniState;
    int prevAniState;
    int curFrame;
    int numFrames;
    int active;
    int index;
} BALL;

typedef struct {
	int width;
	int height;
	int worldRow;
	int worldCol;
	int screenRow;
	int screenCol;
	int index;
	int hide;
} HEALTH;

typedef struct {
	int width;
	int height;
	int worldRow;
	int worldCol;
	int screenRow;
	int screenCol;
	int index;
	int hide;
} WHEALTH;


enum {PBACK, PRIGHT, PLEFT, PJUMP, PFALL, PIDLE};
#define BALLCOUNT 9
#define MAPHEIGHT 512
#define MAPWIDTH 256

// Constants
PLAYER player;
extern BALL ball[BALLCOUNT];
HEALTH healthPic;
WHEALTH wh;
extern char fpsbuffer[30];

extern int score;
extern int lives;
extern int health;
extern int hcount;
extern int fallcount;
extern int wcount;
extern int bcount;
extern unsigned short hOff;
extern int vOff;
extern unsigned short hOff2;
extern int vOff2;

// Prototypes
void initGame();
void updateGame();
void drawGame();
void initPlayer();
void updatePlayer();
void drawPlayer();
void initBall();
void updateBall(BALL *);
void releaseBall();
void drawBall(BALL *);
void hideBalls();
void hideHealth();
void drawHealth();
void updateHealth();
void initHealth();
