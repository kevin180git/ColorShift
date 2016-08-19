#include "myLib.h"
#include <stdlib.h>

unsigned short *videoBuffer = (unsigned short *)0x6000000;

void setPixel(int row, int col, unsigned short color)
{
	videoBuffer[OFFSET(row, col, 240)] = color;
}

void drawRect(int row, int col, int height, int width, unsigned short color)
{
	for(int r=0; r<height; r++)
	{

		DMA[3].src = &color;
		DMA[3].dst = videoBuffer + OFFSET(row+r, col, 240);
		DMA[3].cnt = width | DMA_SOURCE_FIXED | DMA_ON;
	}
}

void drawImage3(int x, int y, int width, int height, const unsigned short *image) {

	for (int i = 0; i < height; i++)
	{
    	DMA[3].src = &image[OFFSET(i, 0, width)];
    	DMA[3].dst = &videoBuffer[OFFSET(x + i, y,240)];
    	DMA[3].cnt = DMA_ON | width ; 
	}

}

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER<160);
}

int collisionH(u16 color, u16 barColor, int col, int barCol) {
	if (((col+10) >= barCol) && ((col+10) <= barCol + 10) && (color != barColor)) {
		return 0;
	
	}
	if (((barCol+10) >= col) && ((barCol+10) <= col + 10) && (color != barColor)) {
		return 0;
	
	}
	return 1;

}


int collisionV(u16 color, u16 barColor, int row, int barRow) {
	if (((row+10) >= barRow) && ((row+10) <= barRow + 10) && (color != barColor)) {
		return 0;
	
	}
	if (((barRow+10) >= row) && ((barRow+10) <= row + 10) && (color != barColor)) {
		return 0;
	
	}
	return 1;

}