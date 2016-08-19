#include <stdlib.h>		//rand
#include "myLib.h"		//main h

#include "finalcolor.h"		//pics
#include "red.h"

#include "text.h"		//text and string stuff
#include <stdio.h>



int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	OBJECT square = {80,120,0,-1,10,10,RED, red};
	OBJECT bar = {0,229,0,-2,160,10,RED, red};
	OBJECT barV = {0,0,1,0,10,240,RED, red};
	OBJECT sq;
	OBJECT bar2;
	OBJECT barV2;
	bar2 = bar;
	sq = square;
	barV2 = barV;

	GameState gameState = START;

	int startMoving = 1;		// if default to 0, won't move till key pressed
								//if default 1, will start moving on start
	int titleScreen = 0; 		//used to draw screens

	int score = 0;
	char buffer[100];
	

	while(1)
	{
		switch(gameState) {
			case START:
				if (titleScreen == 0) {
					drawImage3(0,0,240,160,finalcolor);
					titleScreen = 2;
				}
				

				if(KEY_DOWN_NOW(BUTTON_START))
				{	
					drawRect(0, 0, 160, 240, BLACK); //clear screen
					gameState = MAIN;

					titleScreen = 2;
				}

				if(KEY_DOWN_NOW(BUTTON_SELECT))
				{	
					gameState = START;
					titleScreen = 0;
					square = sq;
					bar = bar2;
					barV = barV2;
					score = 0;
				}
				break;

			case MAIN:
				if(KEY_DOWN_NOW(BUTTON_SELECT))
				{	
					gameState = START;
					titleScreen = 0;
					square = sq;
					bar = bar2;
					barV = barV2;
					score = 0;
				}

				if(KEY_DOWN_NOW(BUTTON_UP))
				{
					startMoving++;
					square.cdel = 0;
					if (square.rdel > 0) {
						square.rdel = -square.rdel;
					} else if (square.rdel == 0) {
						if (square.row == 0) {
							square.rdel = 1;
							if (score>= 10) {
								square.rdel = 2;
							}
						} else if (square.row == 159){
							square.rdel = -1;
							if (score>= 10) {
								square.rdel = -2;
							}
						} else {
							square.rdel = -1;
							if (score>= 10) {
								square.rdel = -2;
							}
						}
					}
				}
				if(KEY_DOWN_NOW(BUTTON_DOWN))
				{
					startMoving++;
					square.cdel = 0;
					if (square.rdel < 0) {
						square.rdel = 0;
					} else if (square.rdel == 0) {
						if (square.row == 0) {
							square.rdel = 1;
							if (score>= 10) {
								square.rdel = 2;
							}
						} else if (square.row == 159) {
							square.rdel = -1;
							if (score>= 10) {
								square.rdel = -2;
							}

						} else {
							square.rdel = 1;
							if (score>= 10) {
								square.rdel = 2;
							}
						}
					};
				}
				if(KEY_DOWN_NOW(BUTTON_LEFT))
				{
					startMoving++;
					square.rdel = 0;
					if (square.cdel > 0) {
						square.cdel = 0;
					} else if (square.cdel == 0) {
						if (square.col == 0) {
							square.cdel = 1;
							if (score>= 10) {
								square.cdel = 2;
							}
						} else if (square.col == 239) {
							square.cdel = -1;
							if (score>= 10) {
								square.cdel = -2;
							}
						} else {
							square.cdel = -1;
							if (score>= 10) {
								square.cdel = -2;
							}
						}
					}
				}
				if(KEY_DOWN_NOW(BUTTON_RIGHT))
				{	
					startMoving++;
					square.rdel = 0;
					if (square.cdel < 0) {
						square.cdel = 0;
					} else if (square.cdel == 0) {
						if (square.col == 0) {
							square.cdel = 1;
							if (score>= 10) {
								square.cdel = 2;
							}
						} else if (square.col == 239){
							square.cdel = -1;
							if (score>= 10) {
								square.cdel = -2;
							}
						} else {
							square.cdel = 1;
							if (score>= 10) {
								square.cdel = 2;
							}
						}
						
					}
				}

				if(KEY_DOWN_NOW(BUTTON_L))
				{
					square.color = RED;	
					square.image = red;
				}

				if(KEY_DOWN_NOW(BUTTON_A))
				{
					square.color = BLUE;
					square.image = blue;
				}

				if(KEY_DOWN_NOW(BUTTON_B))
				{
					square.color = YELLOW;
					square.image = yellow;
				}

				if(square.col <0)
				{
					square.col = 0;
					square.cdel = 0;
				}
				if(square.col > 239-square.width+1)
				{
					square.col = 239-square.width+1;
					square.cdel = 0;
				}
				if(square.row < 0)
				{
					square.row = 0;
					square.rdel = 0;
				}
				if(square.row > 159-square.height+1)
				{
					square.row = 159-square.height+1;
					square.rdel = 0;
				}

				if (startMoving > 0) 
				{	//character movement
				square.row += square.rdel;
				square.col += square.cdel;
				}

//===========================square=================================
				
				bar.col += bar.cdel;		//bar movement


				if (bar.col< 0) {				//if bar leave screen, randomly chose
					bar.col = 239;				//where it pops up next
					score++;
					int leftOrRight = rand() % 2;
					if (leftOrRight == 0) {
						bar.col = 0;
						bar.cdel = 2;
					} else if (leftOrRight == 1) {
						bar.col = 229;
						bar.cdel = -2;
					}
				}
				if (bar.col > 230) {
					score++;
					bar.col = 0;
					int leftOrRight = rand() % 2;
					if (leftOrRight == 0) {
						bar.col = 0;
						bar.cdel = 2;
					} else if (leftOrRight == 1) {
						bar.col = 229;
						bar.cdel = -2;
					}
				}

				int changeColor = rand() % 3;				//chooses random colors for bar
				if (bar.col == 239 || bar.col == 0) {
					if (changeColor == 0) {
						bar.color = RED;
			
					} else if (changeColor == 1) {
						bar.color = YELLOW;

					} else if (changeColor == 2) {
						bar.color = BLUE;

					}
				}

				int temper = collisionH(square.color, bar.color, square.col, bar.col);
				if (temper == 0) {
					if (score >= 15) {
						gameState = WIN;
						titleScreen = 0;
					} else {
						gameState = LOSE;
						titleScreen = 0;
					}
					
				}

				if (score >= 10) {

					barV.row += barV.rdel;
					if (barV.row < 0) {				//if bar leave screen, randomly chose
										//where it pops up next
						score++;
						int leftOrRight = rand() % 2;
						if (leftOrRight == 0) {
							barV.row = 0;
							barV.rdel = 1;
						} else if (leftOrRight == 1) {
							barV.row = 149;
							barV.rdel = -1;
						}
					}
					if (barV.row > 149) {
						score++;
						int leftOrRight = rand() % 2;
						if (leftOrRight == 0) {
							barV.row = 0;
							barV.rdel = 1;
						} else if (leftOrRight == 1) {
							barV.row = 149;
							barV.rdel = -1;
						}
					}

					if (barV.row == 149 || barV.row == 0) {
						if (changeColor == 0) {

							barV.color = RED;
						} else if (changeColor == 1) {
					
							barV.color = YELLOW;
						} else if (changeColor == 2) {
				
							barV.color = BLUE;
						}
					}

					int temp = collisionV(square.color, barV.color, square.row, barV.row);
					if (temp == 0) {
						if (score >= 15) {
							gameState = WIN;
							titleScreen = 0;
						} else {
							gameState = LOSE;
							titleScreen = 0;
						}
						
					}

				}

			

				
			
				sprintf(buffer, "%d", score);
				drawRect(150, 0, 10, 240, BLACK); // h right 
				drawRect(0, 0, 10, 240, BLACK); 
				drawRect(bar.row, bar.col, bar.height, bar.width, bar.color);
				if (score >= 10){
					drawRect(barV.row, barV.col, barV.height, barV.width, barV.color);
				}
				drawRect(0, 0, 160, 10, BLACK); // v top 
				drawRect(0, 230, 160, 10, BLACK);  

				
				drawImage3(square.row,square.col,10,10,square.image);
				
				waitForVblank();


				drawRect(10,117,8,3*6, BLACK);  // COVERS OLD SCORE
				drawString(10,117,buffer, GREEN);
				drawRect(square.row, square.col, square.height, square.width, BLACK);
			
				drawRect(bar.row, bar.col, bar.height, bar.width, BLACK);
				if (score>= 10) {
					drawRect(barV.row, barV.col, barV.height, barV.width, BLACK);
				}
				
				
				break;

			case WIN:

				if (titleScreen == 0) {
					waitForVblank();
					drawImage3(0,0,240,160,win);
					drawString(113,95,buffer,RED);
					
				}
				if(KEY_DOWN_NOW(BUTTON_SELECT))
				{	
					gameState = START;
					titleScreen = 0;
					square = sq;
					bar = bar2;
					barV = barV2;
					score = 0;
				}
				if(KEY_DOWN_NOW(BUTTON_START))
				{	
					gameState = START; //go start, clear and go game
		
					square = sq;
					bar = bar2;
					barV = barV2;
					score = 0;
				}

				break;
			case LOSE:

				if (titleScreen == 0) {
					waitForVblank();
					drawImage3(0,0,240,160,lost);
					drawString(113,95,buffer,RED);
					
				}
				if(KEY_DOWN_NOW(BUTTON_SELECT))
				{	
					gameState = START;
					titleScreen = 0;
					square = sq;
					bar = bar2;
					barV = barV2;
					score = 0;
				}
				if(KEY_DOWN_NOW(BUTTON_START))
				{	
					gameState = START; //go start, clear and go game
		
					square = sq;
					bar = bar2;
					barV = barV2;
					score = 0;
				}

				break;
				
		}		
	}
}

