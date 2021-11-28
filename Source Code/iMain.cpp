/*
		Project Name		:	Puzzy Puzzy
		Project Type		:	Gaming Project (Puzzle Game)
		Author			:	Ariful Islam Shanto
		Starting Date		:	march 30, 2021
		Ending Date		:	april 07, 2021
*/

#include <iostream>
#include <string>
#include < fstream >
#include "iGraphics.h"
#include "puzzyPuzzy.h"

using namespace std;

void iDraw()
{
	iClear();
	drawBackground(bgNo);
	// std::cout << bgNo << endl;
}

void iMouseMove(int mx, int my)
{
	
}

void iPassiveMouseMove(int mx, int my)
{
	
}

void iMouse(int button, int state, int mx, int my)
{
	
	if (scene == 0) {
		scene++;
		bgNo++;
		return;
	}
	if (scene == 1) {
		doEverythingForScene01(button, state, mx, my);
		return;
	}
	if (scene == 2) {
		doEverythingForScene02(button, state, mx, my);
		return;
	}
	if (scene == 3) {
		doEverythingForScene03(button, state, mx, my);
		return;
	}
	if (scene == 5) {
		doEverythingForScene05(button, state, mx, my);
		return;
	}
	if (scene == 6) {
		doEverythingForScene06(button, state, mx, my);
		return;
	}
	if (scene == 7) {
		doEverythingForScene07(button, state, mx, my);
		return;
	}
}

void iKeyboard(unsigned char key)
{
	if (scene == 3) {
		keyBoardMoveForGameplay(key);
		return;
	}
	if (key == '\r')
	{
		if (scene == 0) {
			scene++;
			bgNo++;
		}
		if (scene == 4) {
			scene = 1;
			bgNo = 1;
			if (musicOn) {
				PlaySound(bgMusic, NULL, SND_LOOP | SND_ASYNC);
			}
		}
		return;
	}

	if (key == 'm' || key == 'M') {
		if (musicOn) {
			musicOn = false;
			PlaySound(0, 0, 0);
		}
		else {
			musicOn = true;
			if (scene == 1 || scene == 5 || scene == 6 || scene == 7) PlaySound(bgMusic, NULL, SND_LOOP | SND_ASYNC);
			else if (scene == 2) PlaySound(gmMde, NULL, SND_LOOP | SND_ASYNC);
		}
	}
}

void iSpecialKeyboard(unsigned char key)
{

	if (scene == 3) {
		SpkeyBoardMoveForGameplay(key);
		return;
	}
	
}

void change()
{
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
	if (increaseTime) totTime++;
}

int main()
{
	if (musicOn) {
		PlaySound(bgMusic, NULL, SND_LOOP | SND_ASYNC);
	}

	iSetTimer(1000, change);

	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Puzzy Puzzy");
	iStart();
	return 0;
}
