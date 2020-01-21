//FinalProj
#include <stdlib.h>
#include "myLib.h"
#include "game.h"
#include "spritesheet.h"
#include "scream.h"
#include "collisionmap.h"
#include "gameSong.h"
#include "lose.h"
#include "Warning.h"
#include "clouds.h"

//vars
int lives;
PLAYER player;

int score;
int health;
HEALTH healthPic;
WHEALTH wh;
int hcount;
int fallcount;
int wcount;

int bcount;
BALL ball[BALLCOUNT];
unsigned short hOff;
int vOff;
unsigned short hOff1;
int vOff1;
unsigned short hOff2;
int vOff2;




void initGame() {
	initPlayer();
	initBall();
	initHealth();
	score = 0;
	lives = 3;	
	health = 10;
	hcount = 0;
	bcount = 0;
	fallcount = 0;
	wcount = 0;

}
void updateGame() {
	updatePlayer();
	updateHealth();

	bcount++;
	if ((bcount % (30)) == 0) {
		releaseBall();
		bcount = 0;
	}

	for (int i = 0; i < BALLCOUNT; i++)
		updateBall(&ball[i]);

}

void drawGame() {
	drawPlayer();
	drawHealth();

	for (int i = 0; i < BALLCOUNT; i++)
		drawBall(&ball[i]);

}

void initPlayer() {

	player.cdel = 1;
	player.rdel = 1;
	player.height = 13;
	player.width = 8;
	player.worldCol = 240/2-player.width/2 + hOff;
	player.worldRow = 150-player.height + vOff;
	player.aniCounter = 0;
    player.curFrame = 0;
    player.numFrames = 3;
	player.aniState = PBACK; 
	player.active = 1;
}

void updatePlayer() {
	
	player.prevAniState = player.aniState;
    player.aniState = PIDLE;

    // Change the animation frame every 20 frames of gameplay
    if(player.aniCounter % 20 == 0) {
        if(player.curFrame == player.numFrames-1) {
            player.curFrame = 0;
            health -= 2;
        }
        else {
            player.curFrame++;
        }
    }
    if (health > 0) {
	    //UP
	    if(BUTTON_HELD(BUTTON_UP)) {
	        player.aniState = PBACK;
	        if(!collisionmapBitmap[OFFSET(player.worldRow - player.rdel, player.worldCol, 256)]
		    	|| !collisionmapBitmap[OFFSET(player.worldRow - player.rdel, player.worldCol +player.width -1, 256)]) {
		    	if ((vOff <= 352) && (player.screenRow == 150-player.height)) {
		    		player.worldRow++;
		    		player.screenRow++;
		    		vOff++;
		    		vOff1++;
		    		healthPic.worldRow++;
		    		healthPic.screenRow++;
		    		wh.screenRow++;
		    		wh.worldRow++;
		    	}
		    } else if ((player.screenRow == 150-player.height) && (vOff > 0)) {
	    		vOff--;
	    		vOff1--;
	    		player.screenRow--;
	    		player.worldRow--;
	    		healthPic.screenRow--;
	    		healthPic.worldRow--;
	    		wh.screenRow--;
	    		wh.worldRow--;
	    	} else {
	    		player.worldRow--;
	    	}
	    }
	    if(!collisionmapBitmap[OFFSET(player.worldRow - player.rdel, player.worldCol, 256)]
	    	|| !collisionmapBitmap[OFFSET(player.worldRow - player.rdel, player.worldCol +player.width -1, 256)]) {
	    	if ((vOff <= 352) && (player.screenRow == 150-player.height)) {
	    		player.worldRow++;
	    		player.screenRow++;
	    		vOff++;
	    		vOff1++;
	    		healthPic.worldRow++;
	    		healthPic.screenRow++;
	    		wh.screenRow++;
	    		wh.worldRow++;
	    	}
	    }
	    


	    //DOWN
	    if(BUTTON_HELD(BUTTON_DOWN)) {
	        player.aniState = PBACK;
	        if(!collisionmapBitmap[OFFSET(player.worldRow + player.height - 1 + player.rdel, player.worldCol, 256)]
		    	|| !collisionmapBitmap[OFFSET(player.worldRow + player.height -1 + player.rdel, player.worldCol +player.width -1, 256)]) {
		    	if ((vOff <= 352) && (player.screenRow == 150-player.height)) {
		    		player.worldRow++;
		    		player.screenRow++;
		    		vOff++;
		    		vOff1++;
		    		healthPic.worldRow++;
		    		healthPic.screenRow++;
		    		wh.screenRow++;
		    		wh.worldRow++;
		    	}
	    	} else if ((vOff <= 352) && (player.screenRow == 150-player.height)) {
		        vOff = vOff + 1;
		        vOff1++;
		        player.screenRow++;
		    	player.worldRow++;
		    	healthPic.screenRow++;
	    		healthPic.worldRow++;
	    		wh.screenRow++;
	    		wh.worldRow++;
		    } else if (!(player.screenRow == 150-player.height) && !(vOff > 0)){
		    	player.worldRow++;
		    } else {
		    	player.worldRow = 150-player.height + vOff;
		    	player.aniState = PIDLE;
		    	//healthPic.worldRow = 4;
		    }
	    }
	    if(!collisionmapBitmap[OFFSET(player.worldRow + player.height - 1 + player.rdel, player.worldCol, 256)]
	    	|| !collisionmapBitmap[OFFSET(player.worldRow + player.height -1 + player.rdel, player.worldCol +player.width -1, 256)]) {
	    	if ((vOff <= 352) && (player.screenRow == 150-player.height)) {
	    		player.worldRow++;
	    		player.screenRow++;
	    		vOff++;
	    		vOff1++;
	    		healthPic.worldRow++;
	    		healthPic.screenRow++;
	    		wh.screenRow++;
	    		wh.worldRow++;
	    	} else if ((vOff <= 352) && (player.screenRow == 150-player.height)) {
		        vOff = vOff + 1;
		        vOff1++;
		        player.screenRow++;
		    	player.worldRow++;
		    	healthPic.screenRow++;
	    		healthPic.worldRow++;
	    		wh.screenRow++;
	    		wh.worldRow++;
		    } else if (!(player.screenRow == 150-player.height) && !(vOff > 0)){
		    	player.worldRow++;
		    } else {
		    	player.worldRow = 150-player.height + vOff;
		    	player.aniState = PIDLE;
		    	//healthPic.worldRow = 4;
		    }
    	}

	    //LEFT
	    if(BUTTON_HELD(BUTTON_LEFT)) {
	        player.aniState = PLEFT;
	        if(!collisionmapBitmap[OFFSET(player.worldRow, player.worldCol, 256)]
		    	|| !collisionmapBitmap[OFFSET(player.worldRow + player.height -1, player.worldCol, 256)]) {
		    	if ((vOff <= 352) && (player.screenRow == 150-player.height)) {
		    		player.worldRow++;
		    		player.screenRow++;
		    		vOff++;
		    		vOff1++;
		    		healthPic.worldRow++;
		    		healthPic.screenRow++;
		    		wh.screenRow++;
		    		wh.worldRow++;
		    	}
	    	} else if((player.screenCol == 240/2-player.width/2) && (hOff > 0)) {
		        hOff--;
		        hOff1--;
		        player.screenCol--;
		        player.worldCol--;
		        healthPic.screenCol--;
		        healthPic.worldCol--;
		        wh.screenCol--;
		        wh.worldCol--;
		    } else if((hOff <= 0) && (player.screenCol >= 1)){
		    	player.worldCol--;
		    } else if((hOff <= 0) && (player.screenCol == 0)) {
		    	//player.aniState = PIDLE;
		    //Go back to the center of the screen if all the way to the right
		    } else if (!(player.screenCol == 240/2-player.width/2) && !(hOff < MAPWIDTH - SCREENWIDTH)) {
		    	player.worldCol--;
		    }
	    }
	    if(!collisionmapBitmap[OFFSET(player.worldRow, player.worldCol, 256)]
	    	|| !collisionmapBitmap[OFFSET(player.worldRow + player.height -1, player.worldCol, 256)]) {
	    	if ((vOff <= 352) && (player.screenRow == 150-player.height)) {
	    		player.worldRow++;
	    		player.screenRow++;
	    		vOff++;
	    		vOff1++;
	    		healthPic.worldRow++;
	    		healthPic.screenRow++;
	    		wh.screenRow++;
	    		wh.worldRow++;
	    	}
    	}

	    //RIGHT
	    if(BUTTON_HELD(BUTTON_RIGHT)) {
	    	player.aniState = PRIGHT;
	    	//if collision while walking right
	    	if(!collisionmapBitmap[OFFSET(player.worldRow, player.worldCol +player.width -3, 256)]
		    	|| !collisionmapBitmap[OFFSET(player.worldRow + player.height -1, player.worldCol +player.width - 3, 256)]
		    	&& (player.worldCol - 1 < SCREENWIDTH - player.cdel)) {
		    	if ((vOff <= 352) && (player.screenRow == 150-player.height)) {
		    		player.worldRow++;
		    		player.screenRow++;
		    		vOff++;
		    		vOff1++;
		    		healthPic.worldRow++;
		    		healthPic.screenRow++;
		    		wh.screenRow++;
		    		wh.worldRow++;
		    	}
		    //if he's walking right, go right
		    } else if ((player.screenCol == 240/2-player.width/2) && (hOff < MAPWIDTH - SCREENWIDTH)) {
		        hOff++;
		        hOff1++;
		        player.screenCol++;
		        player.worldCol++;
		        healthPic.screenCol++;
		        healthPic.worldCol++;
		        wh.screenCol++;
		        wh.worldCol++;
		    //if he's all the way to the right but not at the edge 
		    } else if ((hOff >= MAPWIDTH - SCREENWIDTH) && (player.screenCol < 240 - player.width)) {
		    	player.worldCol++;
		    //if at the edge, STOP
		    } else if((hOff >= MAPWIDTH - SCREENWIDTH) && (player.screenCol >= (240 - player.width))) {
		    	//player.aniState = PIDLE;
		    //Go back to the center of the screen if all the way to the left
		    } else if (!(player.screenCol == 240/2-player.width/2) && !(hOff > 0)) {
		    	player.worldCol++;
		    }
	    }
	    if((!collisionmapBitmap[OFFSET(player.worldRow, player.worldCol +player.width -3, 256)]
	    	|| !collisionmapBitmap[OFFSET(player.worldRow + player.height -1, player.worldCol +player.width - 3, 256)]
	    	&& (player.worldCol - 1 < SCREENWIDTH - player.cdel)) && player.aniState != PFALL) {
	    	if ((vOff <= 352) && (player.screenRow == 150-player.height)) {
	    		player.worldRow++;
	    		player.screenRow++;
	    		vOff++;
	    		vOff1++;
	    		healthPic.worldRow++;
	    		healthPic.screenRow++;
	    		wh.screenRow++;
	    		wh.worldRow++;
	    	}
		}
	}

     //If health = 0, reposition and animate falling
	/*
    if (health <= 0) {
    	hideBalls();
    	hideHealth();
    	DMANow(3, shadowOAM, OAM, 128*4);
    	REG_DISPCTL |= BG1_ENABLE;
    	REG_BLDMOD = BG1_A | BG0_B | OBJ_B | NORMAL_TRANS;
		REG_COLEV = WEIGHTOFA(6) | WEIGHTOFB(10);
		DMANow(3, loseTiles, &CHARBLOCK[1], loseTilesLen/2);
		DMANow(3, loseMap, &SCREENBLOCK[29], loseMapLen/2);

		//REG_DISPCTL = MODE0 | BG0_ENABLE | BG2_ENABLE;
		REG_BG1CNT = BG_SIZE_SMALL | BG_CHARBLOCK(1) | BG_SCREENBLOCK(29) | 0;
    	player.aniState = PFALL;
    	if (vOff <= 352) {
			player.worldRow++;
			player.screenRow++;
			vOff++;
			vOff1++;
    	} else {
    		goToLose();
    	}
    }*/


//	WARNING
  //   if(health <= 2 && health > 0) {
  //   	REG_DISPCTL |= BG1_ENABLE;
  //   	REG_BLDMOD = BG1_A | BG0_B | OBJ_B | NORMAL_TRANS;
		// REG_COLEV = WEIGHTOFA(6) | WEIGHTOFB(10);
		// DMANow(3, WarningTiles, &CHARBLOCK[1], WarningTilesLen/2);
		// DMANow(3, WarningMap, &SCREENBLOCK[28], WarningMapLen/2);
		// REG_BG1CNT = BG_SIZE_SMALL | BG_CHARBLOCK(1) | BG_SCREENBLOCK(28) | 1;
		// REG_BG1HOFF = 0 - hOff;
  //   	REG_BG1VOFF = 0 - vOff;
  //   	wcount++;
  //   	if(wcount%30 == 0) {
  //   		REG_BLDMOD = BG1_A | BG0_B | OBJ_B | NORMAL_TRANS;
  //   		REG_COLEV = WEIGHTOFA(8) | WEIGHTOFB(8);
  //   		DMANow(3, cloudsTiles, &CHARBLOCK[1], cloudsTilesLen/2);
  //   		DMANow(3, cloudsMap, &SCREENBLOCK[28], cloudsMapLen/2);
  //   		REG_BG1CNT = BG_SIZE_TALL | BG_CHARBLOCK(1) | BG_SCREENBLOCK(28) | 1; // clouds screen
  //   		REG_BG1HOFF = hOff1;
  //   		REG_BG1VOFF = vOff1;
  //   	}
  //   }

    if(player.aniState == PIDLE) {
        player.curFrame = 0;
        hcount++;
        //REGAIN HEALTH
        if (health < 10) {
	        if (hcount%120 == 0){
	        	health++;
	        	hcount = 0;
	        }
    	}
    } else {
        player.aniCounter++;
    }

	player.screenRow = player.worldRow - vOff;
    player.screenCol = player.worldCol - hOff;



}

void drawPlayer() {
	if (health <= 2 && health > 0) {
		// shadowOAM[3+BALLCOUNT].attr0 = ((player.screenRow-20) & ROWMASK) | ATTR0_4BPP | ATTR0_WIDE;
  //       shadowOAM[3+BALLCOUNT].attr1 = (player.screenCol-6 & COLMASK) | ATTR1_MEDIUM;
  //       shadowOAM[3+BALLCOUNT].attr2 = ATTR2_PALROW(2) | ATTR2_TILEID(27,0) | ATTR2_PRIORITY(1);

		shadowOAM[0].attr0 = (player.screenRow & ROWMASK) | ATTR0_4BPP | ATTR0_TALL;
		shadowOAM[0].attr1 = (player.screenCol & COLMASK) | ATTR1_TINY;
		shadowOAM[0].attr2 = ATTR2_PALROW(2) | ATTR2_TILEID(player.curFrame*2, player.aniState) | ATTR2_PRIORITY(2);
    }
	if (health > 2 || health <= 0) {
		shadowOAM[0].attr0 = (player.screenRow & ROWMASK) | ATTR0_4BPP | ATTR0_TALL;
		shadowOAM[0].attr1 = (player.screenCol & COLMASK) | ATTR1_TINY;
		shadowOAM[0].attr2 = ATTR2_PALROW(player.curFrame>>3) | ATTR2_TILEID(player.curFrame*2, player.aniState) | ATTR2_PRIORITY(2);
    }
    if(player.aniState == PIDLE) {
        player.curFrame = 0;
        player.aniState = player.prevAniState;
    }
}

void initBall() {
	for (int i = 0; i < BALLCOUNT; i++) {
		ball[i].height = 16;
		ball[i].width = 16;
		ball[i].worldCol = rand() % 228;
		ball[i].rdel = 1;
		ball[i].aniCounter = 0;
		ball[i].curFrame = 0;
		ball[i].numFrames = 3;
		ball[i].active = 0;
		ball[i].index = 3 + i;
	}
}

void updateBall(BALL* b) {
	if (b->active) {
		if(b->aniCounter % 20 == 0) {
		    if(b->curFrame == b->numFrames-1) {
		        b->curFrame = 0;
		    } else {
		        b->curFrame++;
		    }
		    if(b->screenRow > 160) {
		    	b->active = 0;
		    	b->worldRow = 0 - b->height + vOff;
		    }
		    //for (int i = 0; i < BULLETCOUNT; i++) {
				if (player.active && collision(b->worldRow, b->worldCol, b->height, b->width,
					player.worldRow, player.worldCol, player.height, player.width)) {
					//goToLose();
					health = health - 5;
					b->active = 0;

					//hide player and ball
					hideSprites();
					DMANow(3, shadowOAM, OAM, 128*4);
					//player.aniState = PFALL;
				}
			//}

    	}
    	b->aniCounter++;
    	b->worldRow += b->rdel;
	}

	b->screenRow = b->worldRow - vOff;
    b->screenCol = b->worldCol - hOff;
}

void releaseBall() {
	for (int i = 0; i < BALLCOUNT; i++) {
		if (!ball[i].active) {
			ball[i].active = 1;
			ball[i].worldCol = rand() % 228;
			ball[i].worldRow = 0 - ball[i].height + vOff;
			break;
		}
	}
	//playSoundB(ice, ICELEN, ICEFREQ, 0);
}


void drawBall(BALL* b) {
	if(b->active) {
        shadowOAM[b->index].attr0 = (b->screenRow & ROWMASK) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[b->index].attr1 = (b->screenCol & COLMASK) | ATTR1_SMALL;
        shadowOAM[b->index].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(b->curFrame*2, 7) | ATTR2_PRIORITY(2);
    } else {
    	shadowOAM[b->index].attr0 = ATTR0_HIDE;
    }
}

void hideBalls() {
    for (int i = 3; i < BALLCOUNT+3; i++) {
        shadowOAM[i].attr0 = ATTR0_HIDE;
    }
}
void hideHealth() {
	for (int i = 0; i <= 1; i++) {
		shadowOAM[i+1].attr0 = ATTR0_HIDE;
	}
}

void initHealth() {
    
    healthPic.width = 8;
    healthPic.height = 16;
    healthPic.worldRow = 4 + vOff + 10;
    healthPic.worldCol = 240 - healthPic.width - 4 + hOff;
    healthPic.index = 1;
    healthPic.hide = 0;

    wh.width = 32;
    wh.height = 8;
    wh.worldRow = 4 + vOff;
    wh.worldCol = 240 - wh.width - 4 + hOff;
    wh.index = 2;
    wh.hide = 0;
}

void updateHealth() {
	healthPic.screenRow = healthPic.worldRow - vOff;
    healthPic.screenCol = healthPic.worldCol - hOff;
    wh.screenRow = wh.worldRow - vOff;
    wh.screenCol = wh.worldCol - hOff;
	if(health == 0) {
		healthPic.hide = 1;
		wh.hide = 1;
	}
}

void drawHealth() {
	if(healthPic.hide) {
        shadowOAM[healthPic.index].attr0 |= ATTR0_HIDE;
        shadowOAM[wh.index].attr0 |= ATTR0_HIDE;
    } else {
        shadowOAM[healthPic.index].attr0 = (healthPic.screenRow & ROWMASK) | ATTR0_4BPP | ATTR0_TALL;
        shadowOAM[healthPic.index].attr1 = (healthPic.screenCol & COLMASK) | ATTR1_TINY;
        shadowOAM[healthPic.index].attr2 = ATTR2_PALROW(1) | ATTR2_TILEID(30,health-1) | ATTR2_PRIORITY(1);

        shadowOAM[wh.index].attr0 = (wh.screenRow & ROWMASK) | ATTR0_4BPP | ATTR0_WIDE;
        shadowOAM[wh.index].attr1 = (wh.screenCol & COLMASK) | ATTR1_SMALL;
        shadowOAM[wh.index].attr2 = ATTR2_PALROW(1) | ATTR2_TILEID(29,0) | ATTR2_PRIORITY(1);
    }
}
