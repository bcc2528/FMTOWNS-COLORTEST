#include <egb.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>

char work[1536];

void Draw_Box(int x, int y, int width, int height, int r, int g, int b)
{
	int x2;
	unsigned short color;

	_Far unsigned short *vram;
	_FP_SEG(vram) = 0x104;
	_FP_OFF(vram) = 0x0;

	vram += (x + (y * 256));

	g <<= 10;
	g &= 0x7c00;
	r <<= 5;
	r &= 0x3e0;
	b &= 0x1f;
	color = g + r + b;

	while(height)
	{
		x2 = width;
		while(x2--)
		{
			*vram++ = color;
		}
		vram += (256 - width);
		height--;
	}
}

void main(void)
{
	int i;
	char para[64];

	EGB_init(work, 1536);
	EGB_resolution(work, 1, 5);
	EGB_resolution(work, 0, 5);
	EGB_writePage(work, 1);
	EGB_displayStart(work, 0, 64, 0);
	EGB_displayStart(work, 2, 2, 2);
	EGB_displayStart(work, 3, 256, 240);
	EGB_writePage(work, 0);
	EGB_displayStart(work, 0, 64, 0);
	EGB_displayStart(work, 2, 2, 2);
	EGB_displayStart(work, 3, 256, 240);
	EGB_color(work, 0, 0x7fff);
	EGB_displayPage(work, 0, 3);

	//Draw

	sprintf(para, "      FM TOWNS 32768 Color Mode");
	WORD(para+0) = 28;
	WORD(para+2) = 32;
	WORD(para+4) = 25;
	EGB_sjisString(work, para);

	sprintf(para, "      RGB 31 steps gradation TEST");
	WORD(para+0) = 20;
	WORD(para+2) = 52;
	WORD(para+4) = 27;
	EGB_sjisString(work, para);

	for(i = 0;i < 32;i++)
	{
		Draw_Box(56 + (i * 6), 64, 6, 32, i, 0, 0);
		Draw_Box(56 + (i * 6), 104, 6, 32, 0, i, 0);
		Draw_Box(56 + (i * 6), 144, 6, 32, 0, 0, i);
		Draw_Box(56 + (i * 6), 184, 6, 32, i, i, i);
	}

	sprintf(para, "      RED");
	WORD(para+0) = 24;
	WORD(para+2) = 88;
	WORD(para+4) = 3;
	EGB_sjisString(work, para);
	sprintf(para, "      GREEN");
	WORD(para+0) = 8;
	WORD(para+2) = 128;
	WORD(para+4) = 5;
	EGB_sjisString(work, para);
	sprintf(para, "      BLUE");
	WORD(para+0) = 16;
	WORD(para+2) = 168;
	WORD(para+4) = 4;
	EGB_sjisString(work, para);
	sprintf(para, "      WHITE");
	WORD(para+0) = 8;
	WORD(para+2) = 208;
	WORD(para+4) = 5;
	EGB_sjisString(work, para);

	while(_kbhit() == 0){}

	EGB_init(work, 1536);
}