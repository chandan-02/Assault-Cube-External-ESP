#include "draw.h"


void Draw::setupDrawing(HDC HDC_Desktop, HWND handle) {
	Draw::hDesktop = HDC_Desktop;
	Draw::Handle = handle;
}

void Draw::drawFilledRectangles(int x, int y, int w, int h, HBRUSH brushColor) {
	RECT rect = { x,y,x + w,y + h };
	FillRect(Draw::hDesktop, &rect, brushColor);
}

void Draw::drawBorderBox(int x, int y, int w, int h, int thickness, HBRUSH brushColor) {
	drawFilledRectangles(x,y,w,thickness,brushColor);
	drawFilledRectangles(x, y, thickness,h, brushColor);
	drawFilledRectangles((x+w), y, thickness, h,brushColor);
	drawFilledRectangles(x, y+h, w+thickness, thickness,brushColor);
}
void Draw::drawEsp(int x, int y, float distance, HBRUSH hBrush, COLORREF colorBol,int widths,int heights) {
	int w = widths;
	int h = heights;
	int newWidth = (37/100  * widths) + w ;
	int newHeight = (300/100 * heights) + h;
	int width = newWidth  / distance;
	int height = newHeight / distance;
	drawBorderBox(x - (width / 2), y - height, width, height, 1, hBrush);
}

DWORD WINAPI Draw::esp(Entities listOfEnemy, Player me, MyMaths calc) {
	GetWindowRect(FindWindow(NULL, L"AssaultCube"),& mRect);
	while (true) {
		me.getInfoPlayer();
		listOfEnemy.getInfoEntity();

		for (int i = 1; i < listOfEnemy.amount; i++) {
			if (calc.worldToScreen(listOfEnemy.list[i].feetPos, me.screen, me.matrix,me.width,me.height) && listOfEnemy.list[i].health > 0 ) {
				if (listOfEnemy.list[i].team != me.teamC) {
					Draw::drawEsp(calc.screen.x,calc.screen.y,calc.getDistance3d(me.feetPos,listOfEnemy.list[i].feetPos),Draw::hBrushEnemy, Draw::enemyColor,me.width,me.height);
				}
				if (listOfEnemy.list[i].team == me.teamC) {
					Draw::drawEsp(calc.screen.x, calc.screen.y, calc.getDistance3d(me.feetPos, listOfEnemy.list[i].feetPos), Draw::hBrushTeam, Draw::teamColor,me.width, me.height);
				}
			}
		}
	}
}