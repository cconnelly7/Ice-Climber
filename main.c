/*
Hello! I made a mountain climber game.
You starts at the bottom of the mountain and you climb up when you presses the up arrow. 
Your health decreases as you climb up the mountain and if you runs out of health, you lose. I keep
track of that with my variable titled health. There are icey balls of doom that fall down
and if they hit you, you lose. There are also icey patches that you slip down if you climb on,
so avoid those as well.

The art and the text on the Splash screen was drawn by me in Usenti. The main mountain background
used in the game as well as the clouds overlaying it was also drawn in Usenti by me. All of my sprites
were, you guessed it, also drawn in Usenti by me. I used Alpha blending in my pause screen and lose 
screen as well as on my clouds during the main game. You turn red when you are low on health to
warn yourself that you need to let yourself gain more health soon. The losing part of my game is pretty
cool if you ask me. You get to watch the sprite fall all the way to the bottom of the mountain. My game
was an original concept.

My cheat is if you press A, the balls stop falling and your health is full. It is easy to climb to the
top of the mountain this way. 
*/

#include "myLib.h"
#include "game.h"
#include "spritesheet.h"
#include "imagesICE.h"
#include "startWords.h"
#include "start.h"
#include "instructions.h"
#include "pause.h"
#include "lose.h"
#include "gameSong.h"
#include "win.h"
#include "collisionmap.h"
#include "clouds.h"
#include "Warning.h"
#include "eye.h"
#include "winSong.h"
#include "loseSound.h"
#include "scream.h"

typedef struct{
    const unsigned char* data;
    int length;
    int frequency;
    int isPlaying;
    int loops;
    int duration;
    int priority;
    int vbCount;
}SOUND;

SOUND soundA;
SOUND soundB;

void setupSounds();
void playSoundA( const unsigned char* sound, int length, int frequency, int loops);
void playSoundB( const unsigned char* sound, int length, int frequency, int loops);
void pauseSound();
void unpauseSound();
void muteSound();
void unmuteSound();
void stopSound();
void setupInterrupts();
void interruptHandler();

// Prototypes
void initialize();
void goToStart();
void start();
void goToGame();
void game();
void goToPause();
void pause();
void goToWin();
void win();
void goToLose();
void lose();
void goToFall();
void fall();
void goToWarning();
void warning();
void goToInstruct();
void instruct();

OBJ_ATTR shadowOAM[128];

enum {START, INSTRUCT, GAME, PAUSE, WIN, LOSE, FALL, WARNING};
int state;

// Button Variables
unsigned short buttons;
unsigned short oldButtons;

#define MAPHEIGHT 512
#define MAPWIDTH 256

//Offset
unsigned short hOff;
int vOff;
unsigned short hOff1;
int vOff1;

int wcount;

int seed;


int main() {

    initialize();

    while(1) {


        // Update button variables
        oldButtons = buttons;
        buttons = BUTTONS;
                
        // State Machine
        switch(state) {

            case START:
                start();
                break;
            case INSTRUCT:
                instruct();
                break;
            case GAME:
                game();
                break;
            case PAUSE:
                pause();
                break;
            case WIN:
                win();
                break;
            case LOSE:
                lose();
                break;
             case FALL:
                 fall();
                 break;
            // case WARNING:
            //     warning();
            //     break;
        }
    }
}

// Initialize the game on first launch
void initialize() {
    
    hOff = 0;
    vOff = 0;
    hOff1 = 0;
    vOff1 = 0;
    buttons = BUTTONS;
    setupSounds();
    setupInterrupts();
    goToStart();
}

void goToStart() {

    REG_DISPCTL = MODE0 | BG1_ENABLE | BG2_ENABLE;
    REG_BG2CNT = BG_SIZE_TALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(30);
    REG_BG1CNT = BG_SIZE_SMALL | BG_CHARBLOCK(1) | BG_SCREENBLOCK(29);
    loadPalette(imagesICEPal);
    DMANow(3, imagesICETiles, &CHARBLOCK[0], imagesICETilesLen/2);
    DMANow(3, imagesICEMap, &SCREENBLOCK[30], imagesICEMapLen/2);

    DMANow(3, startWordsTiles, &CHARBLOCK[1], startWordsTilesLen/2);
    DMANow(3, startWordsMap, &SCREENBLOCK[29], startWordsMapLen/2);    

    waitForVBlank();

    REG_BG1HOFF = 0;
    REG_BG1VOFF = 0;

    playSoundA(gameSong, GAMESONGLEN, GAMESONGFREQ, 1);
    state = START;

    seed = 0;
}

void start() {

    seed++;

    // Lock the framerate to 60 fps
    waitForVBlank();

    // State transitions
    if (BUTTON_PRESSED(BUTTON_START)) {

        hOff = 0;
        vOff = 354;
        hOff1 = 0;
        vOff1 = 354;
        goToGame();
        initGame();
        playSoundA(eye, EYELEN, EYEFREQ, 1);
    }

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToInstruct();
    }
}
 //DMA BGS IN GOTO AND HIDE SPRITES DMA SPRITES IN GOTO

void goToInstruct(){
    REG_DISPCTL = MODE0 | BG2_ENABLE | SPRITE_ENABLE;
    waitForVBlank();
    loadPalette(instructionsPal);
    DMANow(3, instructionsTiles, &CHARBLOCK[0], instructionsTilesLen/2);
    DMANow(3, instructionsMap, &SCREENBLOCK[30], instructionsMapLen/2);
    REG_BG2CNT = BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(30);


    state = INSTRUCT;

}

void instruct(){

    seed++;
    waitForVBlank();

    // State transitions
    if (BUTTON_PRESSED(BUTTON_START)) {

        hOff = 0;
        vOff = 354;
        hOff1 = 0;
        vOff1 = 354;
        hOff2 = 0;
        vOff2 = 354;
        goToGame();
        initGame();
        playSoundA(eye, EYELEN, EYEFREQ, 1);
    }
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToStart();
    }

}

void goToGame() {

    REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE | BG1_ENABLE;
    REG_BG0CNT = BG_SIZE_TALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(30) | 2; //game screen
    loadPalette(imagesICEPal);
    DMANow(3, imagesICETiles, &CHARBLOCK[0], imagesICETilesLen/2);
    DMANow(3, imagesICEMap, &SCREENBLOCK[30], imagesICEMapLen/2);

    DMANow(3, spritesheetPal, SPRITEPALETTE, 256);
    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen/2);

    REG_BLDMOD = BG1_A | BG0_B | OBJ_B | NORMAL_TRANS;
    REG_COLEV = WEIGHTOFA(8) | WEIGHTOFB(8);
    DMANow(3, cloudsTiles, &CHARBLOCK[1], cloudsTilesLen/2);
    DMANow(3, cloudsMap, &SCREENBLOCK[28], cloudsMapLen/2);
    REG_BG1CNT = BG_SIZE_TALL | BG_CHARBLOCK(1) | BG_SCREENBLOCK(28) | 1; // clouds screen


    hideSprites();

    DMANow(3, shadowOAM, OAM, 128*4);
    state = GAME;
}

void game() {

    updateGame();
    waitForVBlank();
    drawGame();
    REG_BG0HOFF = hOff;
    REG_BG0VOFF = vOff;
    REG_BG1HOFF = hOff1;
    REG_BG1VOFF = vOff1;

    DMANow(3, shadowOAM, OAM, 128*4);
    
    if (BUTTON_PRESSED(BUTTON_START)) 
        goToPause();

    //CHEAT
    else if (BUTTON_HELD(BUTTON_A)) {
        hideBalls();
        health = 10;
        DMANow(3, shadowOAM, OAM, 128*4);
        if ((player.screenRow <= 16) && (player.worldRow <= 16)) {
            goToWin();
            stopSound();
            playSoundB(winSong, WINSONGLEN, WINSONGFREQ, 0);
        }
    }

    else if ((player.screenRow <= 16) && (player.worldRow <= 16)) {
        goToWin();
        stopSound();
        playSoundB(winSong, WINSONGLEN, WINSONGFREQ, 0);
    }
    else if (health <= 0)
        goToFall();

}

void goToPause() {
    pauseSound();
    REG_BLDMOD = BG1_A | BG0_B | OBJ_B | NORMAL_TRANS;
    REG_COLEV = WEIGHTOFA(8) | WEIGHTOFB(8);
    DMANow(3, pauseTiles, &CHARBLOCK[1], pauseTilesLen/2);
    DMANow(3, pauseMap, &SCREENBLOCK[29], pauseMapLen/2);
    REG_BG1CNT = BG_SIZE_SMALL | BG_CHARBLOCK(1) | BG_SCREENBLOCK(29) | 0; // pause screen

    REG_BG1HOFF = 0;
    REG_BG1VOFF = 0;

    state = PAUSE;
}

void pause() {
    waitForVBlank();
    if (BUTTON_PRESSED(BUTTON_START)) {
        REG_BG0HOFF = hOff;
        REG_BG0VOFF = vOff;
        goToGame();
        unpauseSound();
    }
    else if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToStart();
    }
}

void goToWin() {
    REG_DISPCTL = MODE0 | BG2_ENABLE | SPRITE_ENABLE;
    waitForVBlank();
    hideSprites();
    DMANow(3, shadowOAM, OAM, 128*4);
    
    loadPalette(winPal);
    DMANow(3, winTiles, &CHARBLOCK[0], winTilesLen/2);
    DMANow(3, winMap, &SCREENBLOCK[30], winMapLen/2);
    REG_BG2CNT = BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(30);
    REG_BG2HOFF = 0;
    REG_BG2VOFF = 0;
    state = WIN;
}

void win() {
    waitForVBlank();
    if (BUTTON_PRESSED(BUTTON_START))
        goToStart();
}

void goToFall() {
    waitForVBlank();
    hideBalls();
    hideHealth();
    DMANow(3, shadowOAM, OAM, 128*4);
    REG_DISPCTL |= BG1_ENABLE;
    REG_BLDMOD = BG1_A | BG0_B | OBJ_B | NORMAL_TRANS;
    REG_COLEV = WEIGHTOFA(6) | WEIGHTOFB(10);
    DMANow(3, loseTiles, &CHARBLOCK[1], loseTilesLen/2);
    DMANow(3, loseMap, &SCREENBLOCK[29], loseMapLen/2);

    REG_BG1CNT = BG_SIZE_SMALL | BG_CHARBLOCK(1) | BG_SCREENBLOCK(29) | 0;
    player.aniState = PFALL;
    REG_BG1HOFF = 0;
    REG_BG1VOFF = 0;
    player.aniCounter = 0;
    state = FALL;
    playSoundB(scream, SCREAMLEN, SCREAMFREQ, 0);
}

void fall() {
   waitForVBlank();
   shadowOAM[0].attr0 = (player.screenRow & ROWMASK) | ATTR0_4BPP | ATTR0_TALL;
   shadowOAM[0].attr1 = (player.screenCol & COLMASK) | ATTR1_TINY;
   shadowOAM[0].attr2 = ATTR2_PALROW(player.curFrame>>3) | ATTR2_TILEID(player.curFrame*2, PFALL) | ATTR2_PRIORITY(1);
   
   // Change the animation frame every 20 frames of gameplay
   if(player.aniCounter % 20 == 0) {
       if(player.curFrame == player.numFrames-1) {
           player.curFrame = 0;
       }
       else {
           player.curFrame++;
       }
   }
   //If health = 0, reposition and animate falling
   if (vOff <= 352) {
       player.worldRow++;
       player.screenRow++;
       vOff++;
       vOff1++;
       player.aniCounter++;
   } else {
       goToLose();
       playSoundA(loseSound, LOSESOUNDLEN, LOSESOUNDFREQ, 0);
   }
   player.screenRow = player.worldRow - vOff;
   REG_BG0HOFF = hOff;
   REG_BG0VOFF = vOff;
   

   if (BUTTON_PRESSED(BUTTON_START)) 
        goToStart();
}

void goToLose() {
    waitForVBlank();
    hideSprites();
    DMANow(3, shadowOAM, OAM, 128*4);
    REG_DISPCTL |= BG1_ENABLE;
    
    REG_BLDMOD = BG1_A | BG0_B | OBJ_B | NORMAL_TRANS;
    REG_COLEV = WEIGHTOFA(6) | WEIGHTOFB(10);
    DMANow(3, loseTiles, &CHARBLOCK[1], loseTilesLen/2);
    DMANow(3, loseMap, &SCREENBLOCK[29], loseMapLen/2);
    REG_BG1CNT = BG_SIZE_SMALL | BG_CHARBLOCK(1) | BG_SCREENBLOCK(29) | 0;
    REG_BG1HOFF = 0;
    REG_BG1VOFF = 0;
    state = LOSE;
}

void lose() {
    waitForVBlank();
    hideSprites();
    DMANow(3, shadowOAM, OAM, 128*4);
    if (BUTTON_PRESSED(BUTTON_START)) 
        goToStart();

}








//SOUND!!!!!!!!!!!!!!!!!!!!!!!!!!!

void setupSounds()
{
    REG_SOUNDCNT_X = SND_ENABLED;

    REG_SOUNDCNT_H = SND_OUTPUT_RATIO_100 | 
                     DSA_OUTPUT_RATIO_100 | 
                     DSA_OUTPUT_TO_BOTH | 
                     DSA_TIMER0 | 
                     DSA_FIFO_RESET |
                     DSB_OUTPUT_RATIO_100 | 
                     DSB_OUTPUT_TO_BOTH | 
                     DSB_TIMER1 | 
                     DSB_FIFO_RESET;

    REG_SOUNDCNT_L = 0;
}

void playSoundA( const unsigned char* sound, int length, int frequency, int loops) {
        dma[1].cnt = 0;
    
        int ticks = PROCESSOR_CYCLES_PER_SECOND/frequency;
    
        DMANow(1, sound, REG_FIFO_A, DMA_DESTINATION_FIXED | DMA_AT_REFRESH | DMA_REPEAT | DMA_32);
    
        REG_TM0CNT = 0;
    
        REG_TM0D = -ticks;
        REG_TM0CNT = TIMER_ON;
    
        soundA.data = sound;
        soundA.length = length;
        soundA.frequency = frequency;
        soundA.isPlaying = 1;
        soundA.loops = loops;
        soundA.duration = ((VBLANK_FREQ * soundA.length) / soundA.frequency);
        soundA.vbCount = 0;
        
}


void playSoundB(const unsigned char* sound, int length, int frequency, int loops) {

        dma[2].cnt = 0;

        int ticks = PROCESSOR_CYCLES_PER_SECOND/frequency;

        DMANow(2, sound, REG_FIFO_B, DMA_DESTINATION_FIXED | DMA_AT_REFRESH | DMA_REPEAT | DMA_32);

        REG_TM1CNT = 0;
    
        REG_TM1D = -ticks;
        REG_TM1CNT = TIMER_ON;
    
        soundB.data = sound;
        soundB.length = length;
        soundB.frequency = frequency;
        soundB.isPlaying = 1;
        soundB.loops = loops;
        soundB.loops = 0;//loops;
        soundB.duration = ((VBLANK_FREQ * soundB.length) / soundB.frequency);
        soundB.vbCount = 0;
        
}

void pauseSound()
{
    soundA.isPlaying = 0;
    soundB.isPlaying = 0;
    REG_TM0CNT = 0;
    REG_TM1CNT = 0;
    
}

void unpauseSound()
{
    soundA.isPlaying = 1;
    soundB.isPlaying = 1;
    REG_TM0CNT = TIMER_ON;
    REG_TM1CNT = TIMER_ON;
    
}

void stopSound()
{
    soundA.isPlaying = 0;
    soundB.isPlaying = 0;
    REG_TM0CNT = 0;
    REG_TM1CNT = 0;
    dma[1].cnt = 0;
    dma[2].cnt = 0;
    
}

void setupInterrupts()
{
    REG_IME = 0;
    REG_INTERRUPT = (unsigned int)interruptHandler;
    
    REG_IE |= INT_VBLANK;
    REG_DISPSTAT |= INT_VBLANK_ENABLE;
    REG_IME = 1;
}

void interruptHandler()
{
    REG_IME = 0;
    if(REG_IF & INT_VBLANK)
    {

        if(soundA.isPlaying) {
            soundA.vbCount++;
            if(soundA.vbCount > soundA.duration) {
                if(soundA.loops) {
                    //play it again
                    playSoundA(soundA.data, soundA.length, soundA.frequency, soundA.loops);
                } else {
                    soundA.isPlaying = 0;
                    dma[1].cnt = 0;
                    REG_TM0CNT = 0;
                }
            }
        }
        if(soundB.isPlaying) {
            soundB.vbCount++;
            if(soundB.vbCount > soundB.duration) {
                if(soundB.loops) {
                    //play it again
                    playSoundB(soundB.data, soundB.length, soundB.frequency, soundB.loops);
                } else {
                    soundB.isPlaying = 0;
                    dma[2].cnt = 0;
                    REG_TM1CNT = 0;
                }
            }
        }
        

        REG_IF = INT_VBLANK; 
    }

    REG_IME = 1;
}
