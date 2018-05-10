#include <iostream>
#include <ctime>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <iomanip>

using namespace std;

void cl() {
	system("cls");
}

void gotoxy (int x, int y) {
    COORD coordinates = { x, y };
    HANDLE outputHandle = GetStdHandle (STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition (outputHandle, coordinates);
}

// MENU /////////////////////////////////////////////////////////////////////////////////

//void addvpos(char *ai, int to) {
//	int max = strlen(ai), h;
//	ai[max + 1] = ' ';
//	h = max;
//	while (h >= to)
//	{
//		swap(ai[h + 1], ai[h]);
//		h--;
//	}
//	max = strlen(ai);
//	ai[max + 1] = '>';
//	h = max;
//	while (h >= to)
//	{
//		swap(ai[h + 1], ai[h]);
//		h--;
//	}
//}
//void correct(char *ai) {
//	int h = 0;
//	while (ai[h] != '\0')
//	{
//		if (ai[h] == '|') ai[h] = '\n';
//		h++;
//	}
//}
//void addzn(char *ai, int to) {
//	int om = 0, h = 0, konets;
//	while (ai[h] != '\0')
//	{
//		if (ai[h] == '|' && om != to) {
//			om++;
//		}
//		else if (om == to) {
//			konets = h;
//			break;
//		}
//		h++;
//	}
//	addvpos(ai, konets);
//	correct(ai);
//}

char ** menussu(char ** to, int &size, char *in) {
	char** mass_1 = new char*[size + 1];
	for (int i = 0; i < size + 1; i++) {
		if (i != size) mass_1[i] = to[i];
		else {
			mass_1[i] = in;
		}
	}
	size++;
	//delete[] mass;
	return mass_1;
}

int menus(const char *pnkts, int &menu) {
	char act;
	int ch = 0, size = 0;
	char temp[1001] ;
	strcpy_s(temp, 1000, pnkts);
	int te_menu = -1;
	CONSOLE_SCREEN_BUFFER_INFO bi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
	int to_pos_x = bi.dwCursorPosition.X;
	int to_pos_y = bi.dwCursorPosition.Y;
	char **menuu = nullptr;
	char *nxt_tokin = NULL, *tokin = strtok_s(temp, "|", &nxt_tokin);
	while (tokin != nullptr) {
		menuu = menussu(menuu, size, tokin);
		tokin = strtok_s(NULL, "|", &nxt_tokin);
	}
	for (int i = 0; i < size; i++)
	{
		cout << "   ";
		cout << menuu[i] << endl;
	}
	while (ch != 13)
	{
		ch = 0;
		if (te_menu > -1) { 
			gotoxy(0, to_pos_y + te_menu);
			cout << "   ";
			cout << menuu[te_menu] << "\0\0\0\0\0\0\0\0\0\0\0\0";
		}
		gotoxy(0, to_pos_y + menu);
		cout << ">> ";
		cout << menuu[menu] << "\0\0\0\0\0\0\0\0\0\0\0\0";
		while (ch != 13 && ch != 80 && ch != 72)
		{
			act = _getch();// считываю
			ch = static_cast<int>(act);//привожу к соответствующему коду
			switch (ch)
			{
			case 80: // вниз
				te_menu = menu;
				if (menu < size - 1) { menu++; }
				
				//else menu = 0;
				break;
			case 72: // вверх
				te_menu = menu;
				if (menu > 0) { menu--; }
				
				//else menu = size - 1;
				break;
			}
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
int onlynums(char *text) {
	char temp[31];
	int h = 0, m = 0;
	while (text[m] != '\0')
	{
		if (text[m] >= '0' && text[m] <= '9') {
			temp[h] = text[m];
			h++;
		}
		m++;
	}
	temp[h] = '\0';
	if (strlen(temp) == 0) {
		temp[0] = '0';
		temp[1] = '\0';
	}
	strcpy_s(text, 29, temp);
	return atoi(text);
}
base binput() {
	base temp;
	char ttm[30];
	do
	{
		cl();
		cout << "( p = printer )\n( computer_block = c )\n( monitor = m )\n( keyboard = k )\n( mouse = o )\n( scaner = a )\nInput type: ";
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
		cout << "// Inputing mouse \\\\" << endl;
		break;
	case 'a':
		cout << "// Inputing scaner \\\\" << endl;
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
			cin.getline(ttm, 29);
			temp.u.mn.screen_width = onlynums(ttm);
		} while (temp.u.mn.screen_width < 1);
		do
		{
			cout << "Input screen height: ";
			cin.getline(ttm, 29);
			temp.u.mn.screen_height = onlynums(ttm);
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
			cin.getline(ttm, 29);
			temp.u.scn.scan_width = onlynums(ttm);
		} while (temp.u.scn.scan_width < 1);
		do
		{
			cout << "Input scan height: ";
			cin.getline(ttm, 29);
			temp.u.scn.scan_height = onlynums(ttm);
		} while (temp.u.scn.scan_height < 1);
		break;
	}
	do
	{
		cout << "Input width: ";
		cin.getline(ttm, 29);
		temp.width = onlynums(ttm);
	} while (temp.width < 1);
	do
	{
		cout << "Input height: ";
		cin.getline(ttm, 29);
		temp.height = onlynums(ttm);
	} while (temp.height < 1);
	do
	{
		cout << "Input sum: ";
		cin.getline(ttm, 29);
		temp.kol = onlynums(ttm);
	} while (temp.kol < 1);
	do
	{
		cout << "Input price in dollars: ";
		cin.getline(ttm, 29);
		temp.buy_dollars = onlynums(ttm);
	} while (temp.buy_dollars < 1);
	do
	{
		cout << "Input price in grn: ";
		cin.getline(ttm, 29);
		temp.buy_grn = onlynums(ttm);
	} while (temp.buy_grn < 1);
	return temp;
}

base* AddOneToMass(base *bs, int &size, base oo) {
	base *tempbase = new base[size + 1];
	for (int i = 0; i < size; i++)
	{
		tempbase[i] = bs[i];
	}
	tempbase[size] = oo;
	size++;
	delete[] bs;
	bs = tempbase;
	return bs;
}

base* DeleteOneToMass(base *bs, int &size, int index) {
	base *tempbase = new base[size - 1];
	for (int i = 0; i < index; i++)
	{
		tempbase[i] = bs[i];
	}
	for (int i = index + 1; i < size; i++)
	{
		tempbase[i - 1] = bs[i];
	}
	delete[] bs;
	bs = tempbase;
	size--;
	return bs;
}

base* FileToMass(fstream &f, base *bs, int &size) {
	if (f.is_open()) {
		base temp;
		while (f.read(reinterpret_cast<char *>(&temp), sizeof(base)))
		{
			bs = AddOneToMass(bs, size, temp);
		}
	}
	return bs;
}

base* synhronize(const char *fname, base * bs, int &size) {
	fstream f(fname, ios::in);
	char temp;
	if (f.is_open()) {
		bs = FileToMass(f, bs, size);
		f.close();
	}
	else
	{
		f.open(fname, ios::out);
		while (true)
		{
			base tt = binput();
			f.write(reinterpret_cast<char *>(&tt), sizeof(base));
			do
			{
				cout << "Continue inputing (y = yes, n = not):";
				cin >> temp;
			} while (temp != 'y' && temp != 'Y' && temp != 'N' && temp != 'n');
			cl();
			if (temp == 'n' || temp == 'N') break;
		}
		f.close();
		f.open(fname, ios::in);
		if (f.is_open()) {
			bs = FileToMass(f, bs, size);
			f.close();
		}
	}
	return bs;
}

void InputBToFile(const char *fname, base * bs, const int size) {
	fstream f(fname, ios::out);
	if (f.is_open()) {
		for (int i = 0; i < size; i++)
		{
			f.write(reinterpret_cast<char *>(&bs[i]), sizeof(base));
		}
		f.close();
	}
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
	msg[0] = '\0';
}

const char* ysno(bool in) {
	if (in) {
		return "Yes";
	}
	else
	{
		return "No";
	}
}

void CoutAll(base * bs, const int size) {
	cout << "\t\t\t\tPRITERS" << endl << endl;
	cout << setw(4) << 'ID' << setw(19) << "Name" << setw(30) << "Is multti color" << setw(30) << "Type" << setw(30) << "With scaner" << endl;
	for (int i = 0; i < size; i++)
	{
		if (bs[i].type == 'p') {
			cout << setw(4) << i + 1 << setw(19) << bs[i].name << setw(19) << ysno(bs[i].u.pr.Multi_color_cartridge) << setw(6) << ysno(bs[i].u.pr.with_scaner) << endl;
		}
	}
}

void main() {
	int size = 0, menu = 0;
	bool exit = false;
	char message[301] = { "Hello in main base!" }, filename[20] = { "my.txt" };
	base *bs = nullptr;
	bs = synhronize(filename, bs, size);
	while (!exit) {
		cl();
		message_send(message);
		menus("Exit|Go|Splash|sdfsdfsdf|dsfsdfsd|sdfsdfsdf|sdfsdf", menu);
		switch (menu)
		{
			case 0:
			exit = true;
			break;

		}
	}
}
