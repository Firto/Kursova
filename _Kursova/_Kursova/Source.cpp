#include <iostream>
#include <ctime>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
using namespace std;

void cl() {
	system("cls");
}
struct base
{
	char type;
	int width, height, buy_dollars, buy_grn, kol;
};
struct printer {
	bool Multi_color_cartridge, with_scaner;
	char name[30], type[30];
};
struct computer_bl {
	bool windows_in;
	char name_processor[30], name_block[30], name_mat_plat[30], name_vid_card[30], name_power_block[30];
};
struct monitor {

};
struct keyboards {

};
struct mouses {

};
struct scaners {

};
// MENU /////////////////////////////////////////////////////////////////////////////////


void addvpos(char *ai, int to) {
	int max = strlen(ai), h;
	ai[max + 1] = ' ';
	h = max;
	while (h >= to)
	{
		swap(ai[h + 1], ai[h]);
		h--;
	}
	max = strlen(ai);
	ai[max + 1] = '>';
	h = max;
	while (h >= to)
	{
		swap(ai[h + 1], ai[h]);
		h--;
	}
}
void correct(char *ai) {
	int h = 0;
	while (ai[h] != '\0')
	{
		if (ai[h] == '|') ai[h] = '\n';
		h++;
	}
}
void addzn(char *ai, int to) {
	int om = 0, h = 0, konets;
	while (ai[h] != '\0')
	{
		if (ai[h] == '|' && om != to) {
			om++;
		}
		else if (om == to) {
			konets = h;
			break;
		}
		h++;
	}
	addvpos(ai, konets);
	correct(ai);
}
int menus(const char *pnkts, int size, int &menu) {
	char act;
	int ch = 0;
	char temp[1001];
	strcpy_s(temp, 1000, pnkts);
	addzn(temp, menu);
	cout << temp << endl;
	while (ch != 13 && ch != 80 && ch != 72)
	{
		act = _getch();// считываю
		ch = static_cast<int>(act);//привожу к соответствующему коду
		switch (ch)
		{
		case 80: // вниз
			if (menu < size - 1) menu++;
			//else menu = 0;
			break;
		case 72: // вверх
			if (menu > 0) menu--;
			//else menu = size - 1;
			break;
		}
	}
	return ch;
}


void message_send(char *msg) {
	if (strlen(msg) > 0) {
		for (int i = 0; i < strlen(msg); i++)
		{
			cout << "-";
		}
		cout << endl;
		cout << msg << endl;
		for (int i = 0; i < strlen(msg); i++)
		{
			cout << "-";
		}
		cout << endl;
	}
}

void main() {
	char message[301] = { "Hello in main base!" }, filename[20] = { "my.txt" };
	bool exit = false;
	int menu = 0;
	while (!exit) {
		cl();
		message_send(message);
		if (menus("Exit|Go|Splash", 3, menu) == 13) {
			if (strlen(message) > 0) message[0] = '\0';
			switch (menu)
			{
			default:
				break;
			}
		}
	}
}s