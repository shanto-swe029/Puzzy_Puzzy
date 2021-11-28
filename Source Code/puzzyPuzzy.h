/*
Project Name		:	Puzzy Puzzy
Project Type		:	Gaming Project (Puzzle Game)
Author			:	Ariful Islam Shanto
Starting Date		:	march 30, 2021
Ending Date		:	NULL
*/

#include < fstream >

using namespace std;

// music
bool musicOn = true;
char bgMusic[] = "lib\\music\\bgMusic.wav";
char click[] = "lib\\music\\click.wav";
char gmOvr[] = "lib\\music\\gameOver.wav";
char gmMde[] = "lib\\music\\mode.wav";
char buzzer[] = "lib\\music\\buzzer.wav";
char gmStart[] = "lib\\music\\gameStart.wav";

// screen properties
#define SCREEN_WIDTH	1000
#define SCREEN_HEIGHT	700

// background properties
#define BG_WIDTH		SCREEN_WIDTH
#define BG_HEIGHT		SCREEN_HEIGHT

// scrumble array & solution ara
#define TOT_SCRUM_ARA	6
#define TOT_SOLN_ARA	4


// game handling
int bgNo = 0;
int scene = 0;
int gameMode = 01;
int r, g, b;

bool increaseTime = false;
int numOfMoves = 0;
int totTime = 0;

// scrumble array
int scurmbleAra[TOT_SCRUM_ARA][9] = { 
	{ 5, 8, 4, 7, 6, 2, 3, 1, 0 },
	{ 4, 8, 1, 7, 6, 3, 5, 2, 0 },
	{ 2, 4, 7, 8, 6, 1, 3, 5, 0 },
	{ 3, 6, 4, 5, 7, 1, 2, 8, 0 },
	{ 4, 7, 5, 6, 8, 3, 2, 1, 0 },
	{ 4, 8, 2, 7, 1, 5, 6, 3, 0 }
};

// solution array
int solutionNum = 0;
int solutionAra[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };

// player array
int playerAra[9];
int blankPos = 8;

void makePlayerAra(int gameMode)
{
	int randomInt = rand() % TOT_SCRUM_ARA;

	//randomInt = 0;

	for (int i = 0; i < 9; i++) {
		playerAra[i] = scurmbleAra[randomInt][i];
	}
	blankPos = 8;
}

void drawMenuButtons()
{
	iShowBMP(100, 110, "lib\\menu\\exit.bmp");
	//iShowBMP(100, 190, "lib\\menu\\settings.bmp");
	iShowBMP(100, 270, "lib\\menu\\about.bmp");
	iShowBMP(100, 350, "lib\\menu\\help.bmp");
	iShowBMP(100, 430, "lib\\menu\\highscore.bmp");
	iShowBMP(100, 510, "lib\\menu\\play.bmp");
	
	iSetColor(255, 255, 255);
	iRectangle(100, 110, 300, 80);
	//iRectangle(100, 190, 300, 80);
	iRectangle(100, 270, 300, 80);
	iRectangle(100, 350, 300, 80);
	iRectangle(100, 430, 300, 80);
	iRectangle(100, 510, 300, 80);
}

void drawModeButtons()
{
	iShowBMP(205, 300, "lib\\modes\\01.bmp");
	iShowBMP(405, 300, "lib\\modes\\02.bmp");
	iShowBMP(605, 300, "lib\\modes\\03.bmp");
	iShowBMP(205, 100, "lib\\modes\\04.bmp");
	iShowBMP(405, 100, "lib\\modes\\05.bmp");
	
	iRectangle(205, 300, 190, 190);
	iRectangle(405, 300, 190, 190);
	iRectangle(605, 300, 190, 190);
	iRectangle(205, 100, 190, 190);
	iRectangle(405, 100, 190, 190);
	iRectangle(605, 100, 190, 190);

	iShowBMP2(800, 100, "lib\\buttons\\back.bmp", 0);
	iRectangle(900, 100, 100, 100);
}


// scene-01  ::  Menu
void doEverythingForScene01(int button, int state, int mx, int my)

{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (mx > 100 && mx < 400) {
			if (my > 510 && my < 590) {
				// play button
				scene = 2;
				bgNo = 2;
				if (musicOn) PlaySound(0, 0, 0);
				if (musicOn) PlaySound(gmMde, NULL, SND_LOOP | SND_ASYNC);
			}
			else if (my > 430 && my < 510) {
				// high score
				scene = 5;
				bgNo = 5;
			}
			else if (my > 350 && my < 430) {
				// help
				scene = 6;
				bgNo = 6;
			}
			else if (my > 270 && my < 350) {
				// About
				scene = 7;
				bgNo = 7;
			}
			else if (my > 190 && my < 270) {
				// settings
			}
			else if (my > 110 && my < 190) {
				// exit
				exit(0);
			}
		}
	}
	return;
}

// scene-02  ::  Game Mode
void doEverythingForScene02(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// detect modes
		if (mx > 205 && mx < 395) {
			if (my > 300 && my < 490) {
				//mode-01
				gameMode = 1;
				scene++;
				bgNo++;
				solutionNum = 1;
				if(musicOn) PlaySound(gmStart, NULL, SND_ASYNC);
			}
			else if (my > 100 && my < 290) {
				//mode-04
				gameMode = 4;
				scene++;
				bgNo++;
				solutionNum = 4;
				if (musicOn) PlaySound(gmStart, NULL, SND_ASYNC);
			}
		}
		if (mx > 405 && mx < 595) {
			if (my > 300 && my < 490) {
				//mode-02
				gameMode = 2;
				scene++;
				bgNo++;
				solutionNum = 2;
				if (musicOn) PlaySound(gmStart, NULL, SND_ASYNC);
			}
			else if (my > 100 && my < 290) {
				//mode-05
				gameMode = 5;
				scene++;
				bgNo++;
				solutionNum = 5;
				if (musicOn) PlaySound(gmStart, NULL, SND_ASYNC);
			}
		}
		if (mx > 605 && mx < 795) {
			if (my > 300 && my < 490) {
				//mode-03
				gameMode = 3;
				scene++;
				bgNo++;
				solutionNum = 3;
				if (musicOn) PlaySound(gmStart, NULL, SND_ASYNC);
			}
			else if (my > 100 && my < 290) {
				//mode-06
				//gameMode = 6;
				//scene++;
				//bgNo++;
				solutionNum = 6;
			}
		}
		// detect back button
		if (mx > 900 && mx < 1000 && my > 100 && my < 200) {
			scene--;
			bgNo--;
			return;
		}
		// make player array
		makePlayerAra(gameMode);
		// totMoves = 0
		numOfMoves = 0;
	}
}

// scene-03  :: Gameplay
char gridImgname[40];

void makeName(int d)
{
	char ch1 = d + '0';
	char nm1[5]; nm1[0] = ch1; nm1[1] = '\0';
	char ext1[6] = ".bmp";
	char name1[40] = "lib\\blocks\\num\\";
	strcat_s(name1, nm1);
	strcat_s(name1, ext1);

	char ch2 = d + '0';
	char nm2[5]; nm2[0] = ch2; nm2[1] = '\0';
	char ext2[6] = ".bmp";
	char name2[40] = "lib\\blocks\\char1\\";
	strcat_s(name2, nm2);
	strcat_s(name2, ext2);

	char ch3 = d + '0';
	char nm3[5]; nm3[0] = ch3; nm3[1] = '\0';
	char ext3[6] = ".bmp";
	char name3[40] = "lib\\blocks\\spidy2\\";
	strcat_s(name3, nm3);
	strcat_s(name3, ext3);

	char ch4 = d + '0';
	char nm4[5]; nm4[0] = ch4; nm4[1] = '\0';
	char ext4[6] = ".bmp";
	char name4[40] = "lib\\blocks\\sust3\\";
	strcat_s(name4, nm4);
	strcat_s(name4, ext4);

	char ch5 = d + '0';
	char nm5[5]; nm5[0] = ch5; nm5[1] = '\0';
	char ext5[6] = ".bmp";
	char name5[40] = "lib\\blocks\\ahb4\\";
	strcat_s(name5, nm5);
	strcat_s(name5, ext5);


	if (gameMode == 1) strcpy_s(gridImgname, name1);
	if (gameMode == 2) strcpy_s(gridImgname, name2);
	if (gameMode == 3) strcpy_s(gridImgname, name3);
	if (gameMode == 4) strcpy_s(gridImgname, name4);
	if (gameMode == 5) strcpy_s(gridImgname, name5);
}

void drawPuzzle()
{	
	int transparency, k = 0;

	transparency = -1;
	if (blankPos == k) transparency = 0;
	k++;
	makeName(playerAra[0]);
	iShowBMP2(275, 400, gridImgname, transparency);
	transparency = -1;
	if (blankPos == k) transparency = 0;
	k++;
	makeName(playerAra[1]);
	iShowBMP2(425, 400, gridImgname, transparency);
	transparency = -1;
	if (blankPos == k) transparency = 0;
	k++;
	makeName(playerAra[2]);
	iShowBMP2(575, 400, gridImgname, transparency);


	transparency = -1;
	if (blankPos == k) transparency = 0;
	k++;
	makeName(playerAra[3]);
	iShowBMP2(275, 250, gridImgname, transparency);
	transparency = -1;
	if (blankPos == k) transparency = 0;
	k++;
	makeName(playerAra[4]);
	iShowBMP2(425, 250, gridImgname, transparency);
	transparency = -1;
	if (blankPos == k) transparency = 0;
	k++;
	makeName(playerAra[5]);
	iShowBMP2(575, 250, gridImgname, transparency);


	transparency = -1;
	if (blankPos == k) transparency = 0;
	k++;
	makeName(playerAra[6]);
	iShowBMP2(275, 100, gridImgname, transparency);
	transparency = -1;
	if (blankPos == k) transparency = 0;
	k++;
	makeName(playerAra[7]);
	iShowBMP2(425, 100, gridImgname, transparency);
	transparency = -1;
	if (blankPos == k) transparency = 0;
	k++;
	makeName(playerAra[8]);
	iShowBMP2(575, 100, gridImgname, transparency);
}

void showElapsedTime()
{
	// show elapsed time tag
	iShowBMP2(730, 450, "lib\\elapsedTime\\ElapsedTime.bmp", 255);

	// calculate hh-mm-ss
	int totTime2 = totTime;
	int ss = totTime2 % 60; totTime2 /= 60;
	int mm = totTime2 % 60; totTime2 /= 60;
	int hh = totTime2;

	// show hour
	string hour_d = "lib\\digits\\" + to_string(hh / 10) + ".bmp";
	int length_hour_d = hour_d.size();
	char hour_dd[200];
	for (int i = 0; i < length_hour_d; i++) {
		hour_dd[i] = hour_d[i];
	}
	hour_dd[length_hour_d] = '\0';
	iShowBMP2(730, 350, hour_dd, 255);

	string hour_u = "lib\\digits\\" + to_string(hh % 10) + ".bmp";
	int length_hour_u = hour_u.size();
	char hour_uu[200];
	for (int i = 0; i < length_hour_u; i++) {
		hour_uu[i] = hour_u[i];
	}
	hour_uu[length_hour_u] = '\0';
	iShowBMP2(775, 350, hour_uu, 255);

	// show minute
	string minute_d = "lib\\digits\\" + to_string(mm / 10) + ".bmp";
	int length_minute_d = minute_d.size();
	char minute_dd[200];
	for (int i = 0; i < length_minute_d; i++) {
		minute_dd[i] = minute_d[i];
	}
	minute_dd[length_minute_d] = '\0';
	iShowBMP2(820, 350, minute_dd, 255);

	string minute_u = "lib\\digits\\" + to_string(mm % 10) + ".bmp";
	int length_minute_u = minute_u.size();
	char minute_uu[200];
	for (int i = 0; i < length_minute_u; i++) {
		minute_uu[i] = minute_u[i];
	}
	minute_uu[length_minute_u] = '\0';
	iShowBMP2(865, 350, minute_uu, 255);

	// show minute
	string second_d = "lib\\digits\\" + to_string(ss / 10) + ".bmp";
	int length_second_d = second_d.size();
	char second_dd[200];
	for (int i = 0; i < length_second_d; i++) {
		second_dd[i] = second_d[i];
	}
	second_dd[length_second_d] = '\0';
	iShowBMP2(910, 350, second_dd, 255);

	string second_u = "lib\\digits\\" + to_string(ss % 10) + ".bmp";
	int length_second_u = second_u.size();
	char second_uu[200];
	for (int i = 0; i < length_second_u; i++) {
		second_uu[i] = second_u[i];
	}
	second_uu[length_second_u] = '\0';
	iShowBMP2(955, 350, second_uu, 255);
}

void drawTarget()
{
	char ch = gameMode + '0';
	char nm[5]; nm[0] = ch; nm[1] = '\0';
	char ext[6] = ".bmp";
	char name[30] = "lib\\target\\";
	strcat_s(name, nm);
	strcat_s(name, ext);

	iShowBMP(50, 201, name);
}

void drawEevrythingOfGameplay()
{
	increaseTime = true;
	
	iSetColor(0, 0, 255);
	iFilledRectangle(900, 100, 100, 100);
	iShowBMP2(800, 100, "lib\\buttons\\back.bmp", 0);

	// target
	iSetColor(0, 0, 0);
	iRectangle(50, 200, 191, 191);

	drawTarget();

	// puzzle
	iSetColor(r, g, b);
	iFilledRectangle(270, 96, 461, 460);

	drawPuzzle();

	//iSetColor(255, 255, 255);
	iLine(275, 250, 725, 250);
	iLine(275, 400, 725, 400);
	iLine(425, 100, 425, 550);
	iLine(575, 100, 575, 550);

	// elapsed time
	iSetColor(0, 0, 0);
	iRectangle(730, 450, 270, 100);
	iRectangle(730, 350, 90, 100);
	iRectangle(820, 350, 90, 100);
	iRectangle(910, 350, 90, 100);

	// show elapsed time
	showElapsedTime();
}

void doEverythingForScene03(int button, int state, int mx, int my)
{
	if (mx > 900 && mx < 1000 && my > 100 && my < 200) {
		scene--;
		bgNo--;
		blankPos = 8;
		return;
	}
}

// show score
string getTimeString(int t){
	string ans = "";
	while (t > 0){
		ans += (char)((int)'0' + (t % 10));
		t /= 10;
	}
	return ans;
}

void saveScoreToFile(int scoreToSave, char fileName[], int mode){
	
	// to make the file if it is not made yet
	ofstream fileMake(fileName, ios::app);
	fileMake.close();

	// to take input from the file
	ifstream inputFile(fileName);
	int highestTillNow = 0;
	//if (mode == 2) highestTillNow = 99999999;
	inputFile >> highestTillNow;
	inputFile.close();
	if (mode == 2 && highestTillNow == 0) highestTillNow = 99999999;

	// cheking if the file needs to be updated or not
	//mode = 1 , max score
	if (mode == 1 && highestTillNow < scoreToSave){
		ofstream outputFile(fileName);
		outputFile << scoreToSave << '\n';
		outputFile.close();
	}
	// mode = 2, min score
	else if (mode == 2 && highestTillNow > scoreToSave){
		ofstream outputFile(fileName);
		outputFile << scoreToSave << '\n';
		outputFile.close();
	}
}

void showScore()
{
	// press enter to continue
	iText(100, 250, "Press `Enter\' to continue", GLUT_BITMAP_HELVETICA_18);
	
	// taken time
	char takenTime[50] = "Time Taken     -  ";
	char sec[20];
	string ans = getTimeString(totTime);

	int cnt = 0;
	for (int i = ans.size()-1; i >= 0; i--){
		sec[cnt] = ans[i]; cnt++;
	}
	sec[cnt] = NULL;
	strcat_s(takenTime,sec);
	strcat_s(takenTime, " seconds");

	iText(100, 450, takenTime, GLUT_BITMAP_HELVETICA_18);

	// total moves
	char totMoves[50] = "Total Moves   -   ";
	char numMoves[20];
	ans = getTimeString(numOfMoves);
	cnt = 0;
	for (int i = ans.size() - 1; i >= 0; i--){
		numMoves[cnt] = ans[i]; cnt++;
	}
	numMoves[cnt] = '\0';
	strcat_s(totMoves, numMoves);

	iText(100, 410, totMoves, GLUT_BITMAP_HELVETICA_18);

	// score
	char score[50] = "Score              -   ";
	char numScore[20];
	int tmpScr = (numOfMoves * totTime);
	if (tmpScr == 0) tmpScr = 1000000;
	int theScore = (int)(1000000 / tmpScr);
	ans = getTimeString(theScore);
	cnt = 0;
	for (int i = ans.size() - 1; i >= 0; i--){
		numScore[cnt] = ans[i]; cnt++;
	}
	numScore[cnt] = '\0';
	strcat_s(score, numScore);
	strcat_s(score, " points");

	// totTime = total time taken
	saveScoreToFile(totTime, "timeTaken.txt", 2);
	// numOfMoves = total move number
	saveScoreToFile(numOfMoves, "moveTaken.txt", 2);
	// theScore = Final Score
	saveScoreToFile(theScore, "score.txt", 1);

	iText(100, 370, score, GLUT_BITMAP_HELVETICA_18);
}


// keyboard move
bool isSolved()
{
	for (int i = 0; i < 9; i++) {
		if (playerAra[i] != solutionAra[i]) return false;
	}
	return true;
}

void gameOver()
{
	scene++;
	bgNo++;
}

void swapThem(int a, int b)
{
	int temp = playerAra[a];
	playerAra[a] = playerAra[b];
	playerAra[b] = temp;

	if (isSolved()) {
		gameOver();
	}

	return;
}

void keyBoardMoveForGameplay(unsigned char key)
{
	if (key == 'm' || key == 'M') {
		if (musicOn) {
			musicOn = false;
			PlaySound(0, 0, 0);
		}
		else {
			musicOn = true;
		}
	}
	if (key == '0') {
		gameOver();
	}
	if (key == 'A' || key == 'a') {
		if (blankPos != 0 && blankPos != 3 && blankPos != 6) {
			swapThem(blankPos, blankPos - 1);
			blankPos--;
			numOfMoves++;
			if (musicOn) PlaySound(0, 0, 0);
			if (musicOn) PlaySound(click, NULL, SND_ASYNC);
		}
		else {
			if (musicOn) PlaySound(buzzer, NULL, SND_ASYNC);
		}
		return;
	}
	if (key == 'D' || key == 'd') {
		if (blankPos != 2 && blankPos != 5 && blankPos != 8) {
			swapThem(blankPos, blankPos + 1);
			blankPos++;
			numOfMoves++;
			if (musicOn) PlaySound(0, 0, 0);
			if (musicOn) PlaySound(click, NULL, SND_ASYNC);
		}
		else {
			if (musicOn) PlaySound(buzzer, NULL, SND_ASYNC);
		}
		return;
	}
	if (key == 'S' || key == 's') {
		if (blankPos != 6 && blankPos != 7 && blankPos != 8) {
			swapThem(blankPos, blankPos + 3);
			blankPos += 3;
			numOfMoves++;
			if (musicOn) PlaySound(0, 0, 0);
			if (musicOn) PlaySound(click, NULL, SND_ASYNC);
		}
		else {
			if (musicOn) PlaySound(buzzer, NULL, SND_ASYNC);
		}
		return;
	}
	if (key == 'W' || key == 'w') {
		if (blankPos != 0 && blankPos != 1 && blankPos != 2) {
			swapThem(blankPos, blankPos - 3);
			blankPos -= 3;
			numOfMoves++;
			if (musicOn) PlaySound(0, 0, 0);
			if (musicOn) PlaySound(click, NULL, SND_ASYNC);
		}
		else {
			if (musicOn) PlaySound(buzzer, NULL, SND_ASYNC);
		}
		return;
	}
}

void SpkeyBoardMoveForGameplay(unsigned char key)
{
	if (key == GLUT_KEY_LEFT) {
		if (blankPos != 0 && blankPos != 3 && blankPos != 6) {
			swapThem(blankPos, blankPos - 1);
			blankPos--;
			numOfMoves++;
			if (musicOn) PlaySound(0, 0, 0);
			if (musicOn) PlaySound(click, NULL, SND_ASYNC);
		}
		else {
			if (musicOn) PlaySound(buzzer, NULL, SND_ASYNC);
		}
		return;
	}
	if (key == GLUT_KEY_RIGHT) {
		if (blankPos != 2 && blankPos != 5 && blankPos != 8) {
			swapThem(blankPos, blankPos + 1);
			blankPos++;
			numOfMoves++;
			if (musicOn) PlaySound(0, 0, 0);
			if (musicOn) PlaySound(click, NULL, SND_ASYNC);
		}
		else {
			if (musicOn) PlaySound(buzzer, NULL, SND_ASYNC);
		}
		return;
	}
	if (key == GLUT_KEY_DOWN) {
		if (blankPos != 6 && blankPos != 7 && blankPos != 8) {
			swapThem(blankPos, blankPos + 3);
			blankPos += 3;
			if (musicOn) PlaySound(0, 0, 0);
			if (musicOn) PlaySound(click, NULL, SND_ASYNC);
		}
		else {
			if (musicOn) PlaySound(buzzer, NULL, SND_ASYNC);
		}
		return;
	}
	if (key == GLUT_KEY_UP) {
		if (blankPos != 0 && blankPos != 1 && blankPos != 2) {
			swapThem(blankPos, blankPos - 3);
			blankPos -= 3;
			numOfMoves++;
			if (musicOn) PlaySound(0, 0, 0);
			if (musicOn) PlaySound(click, NULL, SND_ASYNC);
		}
		else {
			if (musicOn) PlaySound(buzzer, NULL, SND_ASYNC);
		}
		return;
	}
}

// show highscore
void showHighScore(){
	ofstream fileMake("timeTaken.txt", ios::app); fileMake.close();
	fileMake.open("moveTaken.txt", ios::app); fileMake.close();
	fileMake.open("score.txt", ios::app); fileMake.close();

	char timeTaken[20], moveTaken[20], score[20];

	ifstream inputFile;

	inputFile.open("timeTaken.txt");
	inputFile >> timeTaken;
	inputFile.close();

	inputFile.open("moveTaken.txt");
	inputFile >> moveTaken;
	inputFile.close();

	inputFile.open("score.txt");
	inputFile >> score;
	inputFile.close();

	iText(155, 170, timeTaken, GLUT_BITMAP_HELVETICA_18);
	iText(480, 310, score, GLUT_BITMAP_HELVETICA_18);
	iText(830, 170, moveTaken, GLUT_BITMAP_HELVETICA_18);

}

//scene 05
void doEverythingForScene05(int button, int state, int mx, int my)
{
	// if(musicOn) PlaySound(gmOvr, NULL, SND_ASYNC);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (mx > 900 && mx < 1000 && my > 0 && my < 100) {
			scene = 1;
			bgNo = 1;
		}
	}
}

// scene 06
void doEverythingForScene06(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (mx > 900 && mx < 1000 && my > 0 && my < 100) {
			scene = 1;
			bgNo = 1;
		}
	}
}

// scene 07
void doEverythingForScene07(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (mx > 900 && mx < 1000 && my > 600 && my < 700) {
			scene = 1;
			bgNo = 1;
		}
	}
}

// background
void drawBackground(int bgNo)
{
	if (bgNo == 0) {
		// home page
		iShowBMP(0, 0, "lib\\bg\\StartScreene.bmp");
	}
	if (bgNo == 1) {
		// menu
		totTime = 0;
		iShowBMP(0, 0, "lib\\bg\\menuBG.bmp");
		drawMenuButtons();
	}
	if (bgNo == 2) {
		// game mode
		iShowBMP(0, 0, "lib\\bg\\gameMode.bmp");
		drawModeButtons();
	}
	if (bgNo == 3) {
		// gameplay
		iShowBMP(0, 0, "lib\\bg\\gameplay.bmp");
		drawEevrythingOfGameplay();
	}
	if (bgNo == 4) {
		// game over
		increaseTime = false;
		iShowBMP(0, 0, "lib\\bg\\gameOver.bmp");
		showScore();
	}
	if (bgNo == 5) {
		// high score
		iShowBMP(0, 0, "lib\\bg\\highScore.bmp");
		iShowBMP2(800, 0, "lib\\buttons\\back.bmp", 0);
		showHighScore();
	}
	if (bgNo == 6) {
		// help
		iShowBMP(0, 0, "lib\\bg\\help.bmp");
		iSetColor(0, 0, 255);
		iFilledRectangle(900, 0, 100, 100);
		iShowBMP2(800, 0, "lib\\buttons\\back.bmp", 0);
	}
	if (bgNo == 7) {
		// about
		iShowBMP(0, 0, "lib\\bg\\about.bmp");
		iShowBMP2(800, 600, "lib\\buttons\\back.bmp", 0);
	}
}
