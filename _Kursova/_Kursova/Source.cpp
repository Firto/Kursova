#include <iostream>
#include <ctime>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
using namespace std;

void cl() {
	system("cls");
}

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

// WORK WITH BASE ////////////////////////////////////////////////////////////

struct printer {
	bool Multi_color_cartridge, with_scaner;
	char name[30], type[30];
};

struct computer_bl {
	bool windows_in;
	char name_processor[30], name_mat_plat[30], name_vid_card[30], name_power_block[30];
};

struct monitor {
	int screen_width, screen_height;
	char matric_type[30];
};

struct keyboards {
	bool with_ua;
	char type_keyb[30];
};

struct mouses {
	bool with_shnur;
	char type_sensor[30];
};

struct scaners {
	int scan_width, scan_height;
};

union s {
	printer pr;
	computer_bl cbl;
	monitor mn;
	keyboards kbrd;
	mouses mous;
	scaners scn;
};

struct base
{
	char type, name[30];
	int width, height, buy_dollars, buy_grn, kol;
	s u;
};

bool yesno(const char * text) {

	char ttm[30];
	do
	{
		cout << text;
		cin.getline(ttm, 29);
	} while (strcmp(ttm, "yes") != 0 && strcmp(ttm, "Yes") != 0 && strcmp(ttm, "Y") != 0 && strcmp(ttm, "y") != 0 &&  strcmp(ttm, "No") != 0 && strcmp(ttm, "no") != 0 && strcmp(ttm, "n") != 0 && strcmp(ttm, "N") != 0);

	if (strcmp(ttm, "Yes") == 0 || strcmp(ttm, "yes") == 0 || strcmp(ttm, "Y") == 0 || strcmp(ttm, "y") == 0) {
		return true;
	}
	else if (strcmp(ttm, "No") == 0 || strcmp(ttm, "no") == 0 || strcmp(ttm, "N") == 0 || strcmp(ttm, "n") == 0) {
		return false;
	}
}

base binput() {
	base temp;
	char ttm[30];
	do
	{
		cl();
		cout << "Input type(p = printer, computer_block = c, monitor = m, keyboard = k, mouse = o, scaner = a ): ";
		cin >> temp.type;
	} while (temp.type != 'p' && temp.type != 'c' && temp.type != 'm' && temp.type != 'k' && temp.type != 'o' && temp.type != 'a');
	cl();
	cin.ignore();
	switch (temp.type)
	{

	case 'p':
		cout << "// Inputing printer \\\\" << endl;
		break;
	case 'c':
		cout << "// Inputing computer block \\\\" << endl;
		break;
	case 'm':
		cout << "// Inputing monitor \\\\" << endl;
		break;
	case 'k':
		cout << "// Inputing keyboard \\\\" << endl;
		break;
	case 'o':
		break;
	case 'a':
		break;
	}
	do
	{
		cout << "Input name: ";
		cin.getline(temp.name, 29);
	} while (strlen(temp.name) < 1);
	switch (temp.type)
	{
	case 'p':
		do
		{
			cout << "Input type: ";
			cin.getline(temp.u.pr.type, 29);
		} while (strlen(temp.u.pr.type) < 1);
		temp.u.pr.Multi_color_cartridge = yesno("Input multi color (Yes or No): ");
		temp.u.pr.with_scaner = yesno("Input scaner (Yes or No): ");
		
		break;
	case 'c':
		do
		{
			cout << "Input name processor: ";
			cin.getline(temp.u.cbl.name_processor, 29);
		} while (strlen(temp.u.cbl.name_processor) < 1);
		do
		{
			cout << "Input name power block: ";
			cin.getline(temp.u.cbl.name_power_block, 29);
		} while (strlen(temp.u.cbl.name_power_block) < 1);
		do
		{
			cout << "Input name motherboard: ";
			cin.getline(temp.u.cbl.name_mat_plat, 29);
		} while (strlen(temp.u.cbl.name_mat_plat) < 1);
		do
		{
			cout << "Input name videocard: ";
			cin.getline(temp.u.cbl.name_vid_card, 29);
		} while (strlen(temp.u.cbl.name_vid_card) < 1);
		temp.u.cbl.windows_in = yesno("Input windows installed (Yes or No): ");
		break;
	case 'm':
		do
		{
			cout << "Input screen type: ";
			cin.getline(temp.u.mn.matric_type, 29);
		} while (strlen(temp.u.mn.matric_type) < 1);
		do
		{
			cout << "Input screen width: ";
			cin >> temp.u.mn.screen_width;
		} while (temp.u.mn.screen_width < 1);
		do
		{
			cout << "Input screen height: ";
			cin >> temp.u.mn.screen_height;
		} while (temp.u.mn.screen_height < 1);
		break;
	case 'k':
		do
		{
			cout << "Input type: ";
			cin.getline(temp.u.kbrd.type_keyb, 29);
		} while (strlen(temp.u.kbrd.type_keyb) < 1);
		break;
		temp.u.kbrd.with_ua = yesno("Input with Ukrainian keys (Yes or No): ");
	case 'o':
		do
		{
			cout << "Input type sensor: ";
			cin.getline(temp.u.mous.type_sensor, 29);
		} while (strlen(temp.u.mous.type_sensor) < 1);
		break;
		temp.u.mous.with_shnur = yesno("Input with shnur (Yes or No): ");
		break;
	case 'a':
		do
		{
			cout << "Input scan width: ";
			cin >> temp.u.scn.scan_width;
		} while (temp.u.scn.scan_width < 1);
		do
		{
			cout << "Input scan width: ";
			cin >> temp.u.scn.scan_height;
		} while (temp.u.scn.scan_height < 1);
		break;
	}
	do
	{
		cout << "Input width: ";
		cin >> temp.width;
	} while (temp.width < 1);
	do
	{
		cout << "Input height: ";
		cin >> temp.height;
	} while (temp.height < 1);
	do
	{
		cout << "Input sum: ";
		cin >> temp.kol;
	} while (temp.kol < 1);
	do
	{
		cout << "Input price in dollars: ";
		cin >> temp.buy_dollars;
	} while (temp.buy_dollars < 1);
	do
	{
		cout << "Input price in grn: ";
		cin >> temp.buy_grn;
	} while (temp.buy_grn < 1);
	return temp;
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
	base my = binput();
	/*char message[301] = { "Hello in main base!" }, filename[20] = { "my.txt" };
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
	}*/
}