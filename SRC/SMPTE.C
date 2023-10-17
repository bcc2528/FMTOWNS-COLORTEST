#include <egb.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>

char work[EgbWorkSize];

void Set_Palette(int i, int red, int green, int blue)
{
	_outb( 0xfd90, i );
	_outb( 0xfd94, red );
	_outb( 0xfd96, green );
	_outb( 0xfd92, blue );
}

void Draw_Box(int x, int y, int width, int height, int color)
{
	_Far unsigned char *vram;
	_FP_SEG(vram) = 0x10c;
	_FP_OFF(vram) = 0x0;

	int x2;

	vram += (x + (y * 1024));

	while(height)
	{
		x2 = width;
		while(x2--)
		{
			*vram++ = (unsigned char)color;
		}
		vram += (1024 - width);
		height--;
	}
}

void main(void)
{
	int i, c;

	//Screen set Mode12(640*480,256 Colors, 1 Page only)
	EGB_resolution( work, 0, 12 );

	EGB_displayPage( work, 0, 3 );
	EGB_writePage( work, 0 );

	EGB_color( work, 0, 0x00 );
	EGB_clearScreen( work );

	//SMPTE color bars Palette
	for(i = 0, c = 0; i < 128;i++)
	{
		Set_Palette(i, c, c, c);
		c += 2;
	}
	Set_Palette(128, 255, 255, 255);
	Set_Palette(129, 191, 191, 0);
	Set_Palette(130, 0, 191, 191);
	Set_Palette(131, 0, 191, 0);
	Set_Palette(132, 191, 0, 191);
	Set_Palette(133, 191, 0, 0);
	Set_Palette(134, 0, 0, 191);
	Set_Palette(135, 255, 255, 0);
	Set_Palette(136, 0, 255, 255);
	Set_Palette(137, 0, 255, 0);
	Set_Palette(138, 255, 0, 255);
	Set_Palette(139, 255, 0, 0);
	Set_Palette(140, 0, 0, 255);
	Set_Palette(141, 65, 0, 119);
	Set_Palette(142, 0, 63, 105);

	//Draw
	Draw_Box(0, 0, 80, 320, 51);
	Draw_Box(80, 0, 80, 320, 96);
	Draw_Box(160, 0, 80, 320, 129);
	Draw_Box(240, 0, 80, 320, 130);
	Draw_Box(320, 0, 80, 320, 131);
	Draw_Box(400, 0, 80, 320, 132);
	Draw_Box(480, 0, 80, 320, 133);
	Draw_Box(560, 0, 80, 320, 134);

	Draw_Box(0, 320, 80, 40, 137);
	Draw_Box(80, 320, 80, 40, 140);
	Draw_Box(160, 320, 80, 40, 138);
	Draw_Box(240, 320, 80, 40, 135);
	Draw_Box(320, 320, 80, 40, 139);
	Draw_Box(400, 320, 80, 40, 136);
	Draw_Box(480, 320, 80, 40, 0);
	Draw_Box(560, 320, 80, 40, 128);

	for(i = 0, c = 0; i < 128;i++)
	{
		Draw_Box(5*i,360,5,40,i);
	}

	Draw_Box(0, 400, 100, 80, 141);
	Draw_Box(100, 400, 100, 80, 128);
	Draw_Box(200, 400, 100, 80, 142);
	Draw_Box(300, 400, 100, 80, 0);
	Draw_Box(400, 400, 40, 80, 3);
	Draw_Box(440, 400, 40, 80, 0);
	Draw_Box(480, 400, 40, 80, 6);
	Draw_Box(520, 400, 40, 80, 0);
	Draw_Box(560, 400, 80, 80, 19);

	while(_kbhit() == 0){}

	EGB_init(work, 1536);
}