#include <iostream>
#include <ctime>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <sstream>

float usd_to_grn;

using namespace std;

void cl() {
	system("cls");
}

void gotoxy (int x, int y) {
    COORD coordinates = { x, y };
    HANDLE outputHandle = GetStdHandle (STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition (outputHandle, coordinates);
}

HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;
int GetBufferChars()
{
	GetConsoleScreenBufferInfo(hCon, &csbInfo);
	return csbInfo.srWindow.Right - csbInfo.srWindow.Left;

}

int GetBufferCharsbot() {
	GetConsoleScreenBufferInfo(hCon, &csbInfo);
	return csbInfo.srWindow.Bottom - csbInfo.srWindow.Top;
}

const char* ftoa(float num) {
	stringstream iostr;
	char *s, *ss;

	s = new char[30];
	iostr << num;
	iostr >> s;
	return s;
}
// MENU /////////////////////////////////////////////////////////////////////////////////

const POINT pos_cur() {
	POINT pos;
	CONSOLE_SCREEN_BUFFER_INFO bi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
	pos.x = bi.dwCursorPosition.X;
	pos.y = bi.dwCursorPosition.Y;
	return pos;
}

void clearToPos(POINT pos) {
	POINT current_pos = pos_cur();
	while (current_pos.y >= pos.y)
	{
		if (current_pos.y > pos.y) {
			gotoxy(0, current_pos.y);
			for (int i = 0; i < GetBufferChars(); i++)
			{
				cout << '\0';
			}
		}
		else if (current_pos.y == pos.y) {
			gotoxy(pos.x, current_pos.y);
			if (current_pos.x != pos.x) for (int i = 0; i < GetBufferChars() - pos.x; i++)
			{
				cout << '\0';
			}
		}

		current_pos.y--;
	}
	gotoxy(pos.x, pos.y);
}

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

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
	int to_pos_x = pos_cur().x;
	int to_pos_y = pos_cur().y;
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
		}
		gotoxy(0, to_pos_y + menu);
		cout << ">> ";
		while (ch != 13 && ch != 80 && ch != 72)
		{
			act = _getch();// считываю
			ch = static_cast<int>(act);//привожу к соответствующему коду
		}
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
	return ch;
}

// WORK WITH BASE ////////////////////////////////////////////////////////////

struct printer {
	bool Multi_color_cartridge, with_scaner;
	char type[30];
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
	int width, height, kol;
	float buy;
	s u;
};

bool yesno(const char * text) {
	POINT current_pos = pos_cur();
	char ttm[30];
	cout << text;
	current_pos = pos_cur();
	do
	{
		clearToPos(current_pos);
		cin.getline(ttm, 29);
	} while (strcmp(ttm, "yes") != 0 && strcmp(ttm, "Yes") != 0 && strcmp(ttm, "Y") != 0 && strcmp(ttm, "y") != 0 &&  strcmp(ttm, "No") != 0 && strcmp(ttm, "no") != 0 && strcmp(ttm, "n") != 0 && strcmp(ttm, "N") != 0);

	if (strcmp(ttm, "Yes") == 0 || strcmp(ttm, "yes") == 0 || strcmp(ttm, "Y") == 0 || strcmp(ttm, "y") == 0) {
		return true;
	}
	else if (strcmp(ttm, "No") == 0 || strcmp(ttm, "no") == 0 || strcmp(ttm, "N") == 0 || strcmp(ttm, "n") == 0) {
		return false;
	}
}
float onlynums(char *text) {
	char temp[30];
	int h = 0, m = 0;
	while (text[m] != '\0')
	{
		if (text[m] >= '0' && text[m] <= '9' || (text[m] == '.' && h>0 && text[m-1] >= '0' && text[m-1] <= '9')) {
			temp[h] = text[m];
			h++;
		}
		else return 0;
		m++;
	}
	temp[h] = '\0';
	if (strlen(temp) == 0) {
		temp[0] = '0';
		temp[1] = '\0';
	}
	strcpy_s(text, 29, temp);
	return atof(text);
}

void toLine(const char * in, char * out, int size) {
	POINT pos_curr;
	cout << in;
	pos_curr = pos_cur();
	do
	{
		clearToPos(pos_curr);
		cin.getline(out, 29);
	} while (strlen(out) < 1);
}

base binput() {
	base temp;
	char ttm[30], tmtm;
	POINT pos_curr;
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
	toLine("Input name: ", temp.name, 29);
	switch (temp.type)
	{
	case 'p':
		toLine("Input type: ", temp.u.pr.type, 29);
		temp.u.pr.Multi_color_cartridge = yesno("Input multi color (Yes or No): ");
		temp.u.pr.with_scaner = yesno("Input scaner (Yes or No): ");
		
		break;
	case 'c':
		toLine("Input name processor: ", temp.u.cbl.name_processor, 29);
		toLine("Input name power block: ", temp.u.cbl.name_power_block, 29);
		toLine("Input name motherboard: ", temp.u.cbl.name_mat_plat, 29);
		toLine("Input name videocard: ", temp.u.cbl.name_vid_card, 29);
		temp.u.cbl.windows_in = yesno("Input windows installed (Yes or No): ");
		break;
	case 'm':
		toLine("Input screen type: ", temp.u.mn.matric_type, 29);
		cout << "Input screen width: ";
		pos_curr = pos_cur();
		do
		{
			clearToPos(pos_curr);
			cin.getline(ttm, 29);
			temp.u.mn.screen_width = onlynums(ttm);
		} while (temp.u.mn.screen_width < 1);

		cout << "Input screen height: ";
		pos_curr = pos_cur();
		do
		{
			clearToPos(pos_curr);
			cin.getline(ttm, 29);
			temp.u.mn.screen_height = onlynums(ttm);
		} while (temp.u.mn.screen_height < 1);
		break;
	case 'k':
		toLine("Input type: ", temp.u.kbrd.type_keyb, 29);
		temp.u.kbrd.with_ua = yesno("Input with Ukrainian keys (Yes or No): ");
		break;
	case 'o':
		toLine("Input type sensor: ", temp.u.mous.type_sensor, 29);
		temp.u.mous.with_shnur = yesno("Input with shnur (Yes or No): ");
		break;
	case 'a':
		cout << "Input scan width: ";
		pos_curr = pos_cur();
		do
		{
			clearToPos(pos_curr);
			cin.getline(ttm, 29);
			temp.u.scn.scan_width = onlynums(ttm);
		} while (temp.u.scn.scan_width < 1);
		cout << "Input scan height: ";
		pos_curr = pos_cur();
		do
		{
			clearToPos(pos_curr);
			cin.getline(ttm, 29);
			temp.u.scn.scan_height = onlynums(ttm);
		} while (temp.u.scn.scan_height < 1);
		break;
	}

	cout << "Input width: ";
	pos_curr = pos_cur();
	do
	{
		clearToPos(pos_curr);
		cin.getline(ttm, 29);
		temp.width = onlynums(ttm);
	} while (temp.width < 1);

	cout << "Input height: ";
	pos_curr = pos_cur();
	do
	{
		clearToPos(pos_curr);
		cin.getline(ttm, 29);
		temp.height = onlynums(ttm);
	} while (temp.height < 1);
	
	cout << "Input sum: ";
	pos_curr = pos_cur();
	do
	{
		clearToPos(pos_curr);
		cin.getline(ttm, 29);
		temp.kol = onlynums(ttm);
	} while (temp.kol < 1);

	cout << "Input type of price (g = grn, u = usd): ";
	pos_curr = pos_cur();
	do
	{
		clearToPos(pos_curr);
		cin >> tmtm;
	} while (tmtm != 'u' && tmtm != 'g');
	if (tmtm == 'g') {
		cout << "Input price in grn: ";
	}
	else if (tmtm == 'u') {
		cout << "Input price in usd: ";
	}
	pos_curr = pos_cur();
	do
	{
		clearToPos(pos_curr);
		cin.getline(ttm, 29);
		if (tmtm == 'u') temp.buy = onlynums(ttm);
		else if (tmtm == 'g') temp.buy = onlynums(ttm)/usd_to_grn;
	} while (temp.buy <= 0);

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

bool* DeleteOneToMassI(bool *bs, int &size, int index) {
	bool *tempbase = new bool[size - 1];
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
		f.read(reinterpret_cast<char *>(&usd_to_grn), sizeof(int));
		while (f.read(reinterpret_cast<char *>(&temp), sizeof(base)))
		{
			bs = AddOneToMass(bs, size, temp);
		}
	}
	return bs;
}

base* synhronize(const char *fname, base * bs, int &size) {
	POINT pos_curr;
	char ttm[30];
	fstream f(fname, ios::in);
	if (f.is_open()) {
		bs = FileToMass(f, bs, size);
		f.close();
	}
	else
	{
		f.open(fname, ios::out);

		cout << "Input Kurs 1 USD to GRN: ";
		pos_curr = pos_cur();
		do
		{
			clearToPos(pos_curr);
			cin.getline(ttm, 29);
			usd_to_grn = onlynums(ttm);
		} while (usd_to_grn <= 0);
		f.write(reinterpret_cast<char *>(&usd_to_grn), sizeof(float));
		while (true)
		{
			base tt = binput();
			f.write(reinterpret_cast<char *>(&tt), sizeof(base));
			cl();
			if (!yesno("Continue inputing (Yes or No): ")) break;
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
		f.write(reinterpret_cast<char *>(&usd_to_grn), sizeof(float));
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

void fullline(char a , int font = LightGray, int back = Black) {
	SetConsoleTextAttribute(hCon, (WORD)((back << 4) | font));
	int _chars = GetBufferChars();
	for (int i = 0; i < _chars; i++)
	{
		cout << a;
	}
	cout << endl;
	SetConsoleTextAttribute(hCon, (WORD)((Black << 4) | LightGray));
}
const char * cout_cl(const char* out, int font = LightGray, int back = Black) {
	SetConsoleTextAttribute(hCon, (WORD)((back << 4) | font));
	cout << out;
	SetConsoleTextAttribute(hCon, (WORD)((Black << 4) | LightGray));
	return "";
}
void coutNoAllcolor(int i,char * name, int kol, int width, int height, float buy, int promiz_kol) {
	cout << setw(6) << i + 1;
	cout_cl("|", promiz_kol);
	cout << setw(24) << name;
	cout_cl("|", promiz_kol);
	cout << setw(6) << kol;
	cout_cl("|", promiz_kol);
	cout << setw(6) << width;
	cout_cl("|", promiz_kol);
	cout << setw(6) << height;
	cout_cl("|", promiz_kol);
	cout << setw(10) << buy;
	cout_cl("|", promiz_kol);
	cout << setw(10) << buy*usd_to_grn;
	cout_cl("|", promiz_kol);
	cout << endl;
}
void punks(int colorr) {
	cout << setw(6) << "ID";
	cout_cl("|", colorr);
	cout << setw(24) << "Name";
	cout_cl("|", colorr);
	cout << setw(6) << "Kol";
	cout_cl("|", colorr);
	cout << setw(6) << "Width";
	cout_cl("|", colorr);
	cout << setw(6) << "Height";
	cout_cl("|", colorr);
	cout << setw(10) << "USD";
	cout_cl("|", colorr);
	cout << setw(10) << "GRN";
	cout_cl("|", colorr);
	cout << endl;
}
void coutnoallone(base * bs, const int size, char in, const char *iin, const int color_items, const int color_line, const int color_row) {
	cout << resetiosflags(ios::left) << setw((GetBufferChars() + strlen(iin)) / 2) << iin << endl;
	fullline('-', color_items);
	cout << setiosflags(ios::left);
	punks(color_items);
	fullline('-', color_items);
	for (int i = 0; i < size; i++)
	{
		if (bs[i].type == in) {
			coutNoAllcolor(i, bs[i].name, bs[i].kol, bs[i].width, bs[i].height, bs[i].buy, color_row);
			fullline('-', color_line);
		}

	}
}
int kolbs(base * bs, const int size, char h) {
	int kol = 0;
	for (int i = 0; i < size; i++)
	{
		if (bs[i].type == h) {
			kol++;
		}
	}
	return kol;
}
void CoutNOAll(base * bs, const int size, int a = 0) {
	const int color_items = 15, color_line = 4, color_row = 12;
	if (a == 0 || a == 1) {
		if (kolbs(bs, size, 'p') || a == 0) {
			coutnoallone(bs, size, 'p', "PRINTERS", color_items, color_line, color_row);
			cout << endl;
		}
		if (kolbs(bs, size, 'c') || a == 0) {
			coutnoallone(bs, size, 'c', "COMPUTER BLOCKS", color_items, color_line, color_row);
			cout << endl;
		}
		if (kolbs(bs, size, 'm') || a == 0) {
			coutnoallone(bs, size, 'm', "MONITORS", color_items, color_line, color_row);
			cout << endl;
		}
		if (kolbs(bs, size, 'k') || a == 0) {
			coutnoallone(bs, size, 'k', "KEYBOARDS", color_items, color_line, color_row);
			cout << endl;
		}
		if (kolbs(bs, size, 'o') || a == 0) {
			coutnoallone(bs, size, 'o', "MOUSES", color_items, color_line, color_row);
			cout << endl;
		}
		if (kolbs(bs, size, 'a') || a == 0) {
			coutnoallone(bs, size, 'a', "SCANERS", color_items, color_line, color_row);
		}
	}
	else if (a == 2) {
		fullline('-', color_items);
		cout << setiosflags(ios::left);
		punks(color_items);
		fullline('-', color_items);
		for (int i = 0; i < size; i++)
		{
			coutNoAllcolor(i, bs[i].name, bs[i].kol, bs[i].width, bs[i].height, bs[i].buy, color_row);
			fullline('-', color_line);
		}
	}
}
void coutall(base * bs, const int size, const int color_items, const int color_line, const int color_row,const int start, const int finish) {
	if (start > -1 && finish <= size) {
		fullline('-', color_items);
		cout << setiosflags(ios::left);
		cout << setw(2);
		cout << " ";
		cout << setw(2);
		cout << " ";
		punks(color_items);
		fullline('-', color_items);
		for (int i = start; i < finish; i++)
		{
			cout << setw(2);
			cout << " ";
			cout << setw(2);
			cout << " ";
			coutNoAllcolor(i, bs[i].name, bs[i].kol, bs[i].width, bs[i].height, bs[i].buy, color_row);
			fullline('-', color_line);
		}
	}
	else
	{
		fullline('-', color_items);
		cout << setiosflags(ios::left);
		cout << setw(2);
		cout << " ";
		cout << setw(2);
		cout << " ";
		punks(color_items);
		fullline('-', color_items);
		for (int i = 0; i < size; i++)
		{
			cout << setw(2);
			cout << " ";
			cout << setw(2);
			cout << " ";
			coutNoAllcolor(i, bs[i].name, bs[i].kol, bs[i].width, bs[i].height, bs[i].buy, color_row);
			fullline('-', color_line);
		}
	}
}
void clear_line(int y) {
	gotoxy(0, y);
	int _chars = GetBufferChars();
	for (int i = 0; i < _chars; i++)
	{
		cout << '\0';
	}
	gotoxy(0, y);
}
int SelectItems(base *bs, const int size, bool *masstoseind) {
	char act, message[301] = { "" }, options[301] = { "BACK : B, OK : O, Select all : S, Unselectall : U" };
	int ch = 0, start = 0, conc = GetBufferCharsbot(),finish = (conc-4)/2, item = 0;
	bool reload = true, exit = false, reload_back = false, new_options = true;
	const int color_items = 15, color_line = 4, color_row = 12;
	while (!exit)
	{
		ch = 0;
		if (reload) {
			cl();
			coutall(bs, size, color_items, color_line, color_row, start, finish);
			reload = false;
			for (int i = start; i < finish; i++)
			{
				if (masstoseind[i] == true) {
					gotoxy(2, 3 + ((i-start) * 2));
					cout << '*';
				}
			
			}
		}
		if (strlen(message)) {
			gotoxy(0, conc);
			cout << options << message;
			message[0] = '\0';
			new_options = true;
		}
		else if (new_options) {
			clear_line(conc);
			cout << options;
			new_options = false;
		}
		if (item > 0 && item < finish - 1) {
			gotoxy(0, 3 + ((item - 1 - start) * 2));
			cout << '\0';
			gotoxy(0, 3 + ((item + 1 - start) * 2));
			cout << '\0';
		}
		else
		if (item == 0) {
			gotoxy(0, 3 + ((item + 1 - start) * 2));
			cout << '\0';
		}
		else
		if (item == finish-1) {
			gotoxy(0, 3 + ((item - 1 - start) * 2));
			cout << '\0';
		}
		
		gotoxy(0, 3 + ((item - start) * 2));
		cout << '>';
		while (ch != 13 && ch != 80 && ch != 72 && ch != -88 && ch != -23 && ch != 111 && ch != 98 && ch != 63 && ch != 115 && ch != -93 && ch != 117)
		{
			act = _getch();
			ch = static_cast<int>(act);
			switch (ch)
			{
			case 80:
				if (item < size - 1) item++; 
				else ch = 0;
				if (item+1 > finish && finish < size && ch != 0) {
					finish++;
					start++;
					reload = true;
				}
				break;
			case 72: 
				if (item > 0) item--;
				else ch = 0;
				if (item < start && start > 0 && ch != 0) {
					finish--;
					start--;
					reload = true;
				}
				break;
			case -88:
			case 98:
				clear_line(conc);
				if (yesno("Back to menu (Yes or No): ")) exit = true;
				else {
					clear_line(conc);
					cout << options;
				}
				break;
			case -23:
			case 111:
				for (int i = 0; i < size; i++)
				{
					if (masstoseind[i]) return 1;
				}
				strcpy_s(message, 300, " | None Selected |");
				break;
			case 13:

				if (!masstoseind[item]) {
					masstoseind[item] = true;
					cout << " *";
				}
				else { 
					masstoseind[item] = false;
					cout << "  ";
				}
				break;
			case 63:
			case 115:
				for (int i = 0; i < size; i++)
				{
					if (!masstoseind[i]) masstoseind[i] = 1;
				}
				reload = true;
				strcpy_s(message, 300, " | All selected! |");
				break;
			case -93:
			case 117:
				for (int i = 0; i < size; i++)
				{
					if (masstoseind[i]) masstoseind[i] = 0;
				}
				reload = true;
				strcpy_s(message, 300, " | All deselected! |");
				break;
			}
		}
	}
	return 0;
}

base* copytos(base *bs, const int size, base * to, int &ssize, char is) {
	ssize = 0;
	to = nullptr;
	for (int i = 0; i < size; i++) {
		if (is == bs[i].type || is == 'e') {
			to = AddOneToMass(to, ssize, bs[i]);
		}
	}
	return to;
}

void showpodrobno(base *bs, int i) {
	fullline('-', LightRed);
	cout << cout_cl("Index\t: ", White) << i + 1 << endl;
	cout << cout_cl("\tType: ", 14);
	switch (bs[i].type)
	{

	case 'p':
		cout << "Printers";
		break;
	case 'c':
		cout << "Computer block";
		break;
	case 'm':
		cout << "Monitor";
		break;
	case 'k':
		cout << "Keyboard";
		break;
	case 'o':
		cout << "Mouse";
		break;
	case 'a':
		cout << "Scaner";
		break;
	}
	cout << endl;
	cout << cout_cl("\tName\t\t: ", 14) << bs[i].name << endl;
	cout << cout_cl("\tHow many\t: ", 14) << bs[i].kol << endl;
	cout << cout_cl("\tWidth\t\t: ", 14) << bs[i].width << endl;
	cout << cout_cl("\tHeigth\t\t: ", 14) << bs[i].height << endl;
	cout << cout_cl("\tBuy in GRN\t: ", 14) << bs[i].buy*usd_to_grn << endl;
	cout << cout_cl("\tBuy in USD\t: ", 14) << bs[i].buy << endl;

	switch (bs[i].type)
	{

	case 'p':
		cout << cout_cl("\t\tType\t\t: ", 13) << bs[i].u.pr.type << endl;
		cout << cout_cl("\t\tMulticolor\t: ", 13) << ysno(bs[i].u.pr.Multi_color_cartridge) << endl;
		cout << cout_cl("\t\tScaner\t\t: ", 13) << ysno(bs[i].u.pr.with_scaner) << endl;
		break;
	case 'c':
		cout << cout_cl("\t\tMat Plat\t: ", 13) << bs[i].u.cbl.name_mat_plat << endl;
		cout << cout_cl("\t\tPower bl\t: ", 13) << bs[i].u.cbl.name_power_block << endl;
		cout << cout_cl("\t\tProcessor\t: ", 13) << bs[i].u.cbl.name_processor << endl;
		cout << cout_cl("\t\tVideo Card\t: ", 13) << bs[i].u.cbl.name_vid_card << endl;
		cout << cout_cl("\t\tWindows\t\t: ", 13) << ysno(bs[i].u.cbl.windows_in) << endl;
		break;
	case 'm':
		cout << cout_cl("\t\tMatric type\t: ", 13) << bs[i].u.mn.matric_type << endl;
		cout << cout_cl("\t\tScreen width\t: ", 13) << bs[i].u.mn.screen_width << endl;
		cout << cout_cl("\t\tScreen height\t: ", 13) << bs[i].u.mn.screen_height << endl;
		break;
	case 'k':
		cout << cout_cl("\t\tType\t\t: ", 13) << bs[i].u.kbrd.type_keyb << endl;
		cout << cout_cl("\t\tWith ua\t\t: ", 13) << ysno(bs[i].u.kbrd.with_ua) << endl;
		break;
	case 'o':
		cout << cout_cl("\t\tType sensor\t: ", 13) << bs[i].u.mous.type_sensor << endl;
		cout << cout_cl("\t\tWith shnur\t: ", 13) << ysno(bs[i].u.mous.with_shnur) << endl;
		break;
	case 'a':
		cout << cout_cl("\t\tScan width\t: ", 13) << bs[i].u.scn.scan_width << endl;
		cout << cout_cl("\t\tScan height\t: ", 13) << bs[i].u.scn.scan_height << endl;
		break;
	}
	fullline('-', LightRed);
}

void main() {
	cout << fixed;
	cout.precision(1);
	int size = 0, menu = 1, size_tm = 0, type = 1;
	POINT tmtm;
	bool exit = false;
	char message[301] = { "Hello in main base!" }, filename[20] = { "my.txt" }, ttm[30];
	base *bs = nullptr, *tempp = nullptr;
	bs = synhronize(filename, bs, size);
	while (!exit) {
		cl();
		SetConsoleTextAttribute(hCon, (WORD)((15 << 4) | 0));
		cout << "Kurs: " << usd_to_grn << endl;
		SetConsoleTextAttribute(hCon, (WORD)((Black << 4) | LightGray));
		
		bool *mass = new bool[size];
		if (tempp != nullptr) {
			CoutNOAll(tempp, size_tm, type);
			tempp = nullptr;
			size_tm = 0;
			type = 1;
		}
		else CoutNOAll(bs, size, type);
		message_send(message);
		menus("Exit|Cout all of index|Add New Vehicle|Delete Items|Vybirka tovars|Set new curs|Sort", menu);
		switch (menu)
		{
			case 0:
			exit = true;
			break;
			case 1:
				for (int i = 0; i < size; i++)
				{
					mass[i] = false;
				}
				if (SelectItems(bs, size, mass)) {
					cl();
					for (int i = 0; i < size; i++)
					{
						if (mass[i]) {
							showpodrobno(bs, i);
						}
					}
				while (!yesno("<< Back (Yes or No): "));
				}else strcpy_s(message, 300, "| You in main menu |");
				break;
			case 2:
				while (true)
				{
					base tt = binput();
					bs = AddOneToMass(bs, size, tt);
					cl();
					if (!yesno("Continue inputing (Yes or No): ")) break;
				}
				break;
			case 3:
				for (int i = 0; i < size; i++)
				{
					mass[i] = false;
				}
				if (SelectItems(bs, size, mass)) {
					int i = 0;
					while (i < size)
					{
						if (mass[i]) {
							bs = DeleteOneToMass(bs, size, i);
							size++;
							mass = DeleteOneToMassI(mass, size, i);
						}
						else i++;
					}
					strcpy_s(message, 300, "| Deleting is ok |");
				}else strcpy_s(message, 300, "| You in main menu |");
				break;
			case 4:
				strcpy_s(message, 300, "| You in vybika menu |");
				menu = 1;
				while (!exit) {
					char smt = 0;
					cl();
					SetConsoleTextAttribute(hCon, (WORD)((15 << 4) | 0));
					cout << "Kurs: " << usd_to_grn << endl;
					SetConsoleTextAttribute(hCon, (WORD)((Black << 4) | LightGray));
					if (tempp != nullptr) {
						tmtm = pos_cur();
						if (yesno("Show podrobno of tovars (Yes or No):")) {
							clearToPos(tmtm);
							for (int i = 0; i < size_tm; i++)
							{
									showpodrobno(tempp, i);
							}
							while (!yesno("<< Back (Yes or No): "));
						}
						clearToPos(tmtm);
						CoutNOAll(tempp, size_tm, type);
						delete[] tempp;
						tempp = nullptr;
						size_tm = 0;
						type = 1;
					}
					else CoutNOAll(bs, size, type);
					message_send(message);
					cout << "Vybirka 1: " << endl;
					menus(" << Back|All|Printers|Computer blocks|Mouses|Keyboars|Monitors|Scaners", menu);
					switch (menu)
					{
					case 1:smt = 'e'; break;
					case 2:smt = 'p'; break;
					case 3:smt = 'c'; break;
					case 4:smt = 'o'; break;
					case 5:smt = 'k'; break;
					case 6:smt = 'm'; break;
					case 7:smt = 'a'; break;
					}
					switch (menu)
					{
					case 0:
						exit = true;
						strcpy_s(message, 300, "| You in main menu |");
						break;
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
					case 7:
						strcpy_s(message, 300, "| You in vybika menu 2 |");
						menu = 1;
						while (!exit)
						{
							char gpd = 0, name[30];
							float zminna;
							cl();
							SetConsoleTextAttribute(hCon, (WORD)((15 << 4) | 0));
							cout << "Kurs: " << usd_to_grn << endl;
							SetConsoleTextAttribute(hCon, (WORD)((Black << 4) | LightGray));
							CoutNOAll(bs, size, type);
							message_send(message);
							cout << "Vybirka 2: " << endl;
							menus(" << Back|Of width|Of height|Of kol in sclad|Of price USD", menu);
							switch (menu)
							{
							case 1:gpd = 'w'; strcpy_s(name, 29, "width"); break;
							case 2:gpd = 'h'; strcpy_s(name, 29, "height"); break;
							case 3:gpd = 'k'; strcpy_s(name, 29, "kol in base"); break;
							case 4:gpd = 'p'; strcpy_s(name, 29, "price"); break;
							}
							switch (menu)
							{
							case 0:
								exit = true;
								strcpy_s(message, 300, "| You in vybika menu |");
								break;
							case 1:
							case 2:
							case 3:
							case 4:
								cl();
								cout << "Input " << name << ": ";
								tmtm = pos_cur();
								do
								{
									clearToPos(tmtm);
									cin.getline(ttm, 29);
									zminna = onlynums(ttm);
								} while (zminna <= 0);
								strcpy_s(message, 300, "| You in vybika menu 3 |");
								menu = 1;
								while (!exit)
								{
									char punktss[100] = { " << Back|" };
									float main_zm;
									
									strcat_s(punktss, 99, ftoa(zminna));
									strcat_s(punktss, 99, " > ");
									strcat_s(punktss, 99, name);
									strcat_s(punktss, 99, "|");
									strcat_s(punktss, 99, ftoa(zminna));
									strcat_s(punktss, 99, " < ");
									strcat_s(punktss, 99, name);
									strcat_s(punktss, 99, "|");
									strcat_s(punktss, 99, ftoa(zminna));
									strcat_s(punktss, 99, " => ");
									strcat_s(punktss, 99, name);
									strcat_s(punktss, 99, "|");
									strcat_s(punktss, 99, ftoa(zminna));
									strcat_s(punktss, 99, " =< ");
									strcat_s(punktss, 99, name);
									strcat_s(punktss, 99, "|");
									strcat_s(punktss, 99, ftoa(zminna));
									strcat_s(punktss, 99, " = ");
									strcat_s(punktss, 99, name);
									cl();
									SetConsoleTextAttribute(hCon, (WORD)((15 << 4) | 0));
									cout << "Kurs: " << usd_to_grn << endl;
									SetConsoleTextAttribute(hCon, (WORD)((Black << 4) | LightGray));
									CoutNOAll(bs, size, type);
									message_send(message);
									cout << "Vybirka 3: " << endl;
									menus(punktss, menu);
									switch (menu)
									{
									case 0:
										exit = true;
										strcpy_s(message, 300, "| You in vybika menu 2 |");
										break;
									case 1:
									case 2:
									case 3:
									case 4:
									case 5:
										for (int i = 0; i < size; i++)
										{
											if ((bs[i].type == smt || smt == 'e')) {
												switch (gpd)
												{
												case 'w':
													main_zm = bs[i].width;
													break;
												case 'h':
													main_zm = bs[i].height;
													break;
												case 'p':
													main_zm = bs[i].buy;
													break;
												case 'k':
													main_zm = bs[i].kol;
													break;
												}
												switch (menu)
												{
												case 1:
													if (zminna > main_zm) {
														tempp = AddOneToMass(tempp, size_tm, bs[i]);
													}
													break;
												case 2:
													if (zminna < main_zm) {
														tempp = AddOneToMass(tempp, size_tm, bs[i]);
													}
													break;
												case 3:
													if (zminna >= main_zm) {
														tempp = AddOneToMass(tempp, size_tm, bs[i]);
													}
													break;
												case 4:
													if (zminna <= main_zm) {
														tempp = AddOneToMass(tempp, size_tm, bs[i]);
													}
													break;
												case 5:
													if (zminna == main_zm) {
														tempp = AddOneToMass(tempp, size_tm, bs[i]);
													}
													break;
												}
											}
										}
									if (tempp != nullptr) exit = true;
										break;
									}
								}
								if (tempp == nullptr) exit = false;
								menu = 1;
								break;

							}
						}
						exit = false;
						menu = 1;
						break;
					}
				}
				exit = false;
				menu = 1;

				break;
			case 5:
				cl();
				cout << "Input Kurs 1 USD to GRN: ";
				tmtm = pos_cur();
				do
				{
					clearToPos(tmtm);
					cin.getline(ttm, 29);
					usd_to_grn = onlynums(ttm);
				} while (usd_to_grn <= 0);
				strcpy_s(message, 300, "| Inputed new curs |");
				break;
			case 6:
				strcpy_s(message, 300, "| You in sort menu |");
				menu = 1;
				while (!exit)
				{
					char smt = 0;
					cl();
					SetConsoleTextAttribute(hCon, (WORD)((15 << 4) | 0));
					cout << "Kurs: " << usd_to_grn << endl;
					SetConsoleTextAttribute(hCon, (WORD)((Black << 4) | LightGray));
					if (tempp != nullptr) {
						tmtm = pos_cur();
						if (yesno("Show podrobno of tovars (Yes or No):")) {
							clearToPos(tmtm);
							for (int i = 0; i < size_tm; i++)
							{
								showpodrobno(tempp, i);
							}
							while (!yesno("<< Back (Yes or No): "));
						}
						clearToPos(tmtm);
						CoutNOAll(tempp, size_tm, type);
						delete[] tempp;
						tempp = nullptr;
						size_tm = 0;
						type = 1;
					}
					else CoutNOAll(bs, size, type);
					message_send(message);
					cout << "Sort: " << endl;
					menus(" << Back|All|Printers|Computer blocks|Mouses|Keyboars|Monitors|Scaners", menu);
					switch (menu)
					{
					case 1:smt = 'e'; break;
					case 2:smt = 'p'; break;
					case 3:smt = 'c'; break;
					case 4:smt = 'o'; break;
					case 5:smt = 'k'; break;
					case 6:smt = 'm'; break;
					case 7:smt = 'a'; break;
					}
					switch (menu)
					{
					case 0:
						strcpy_s(message, 300, "| You in main menu |");
						exit = true;
						break;
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
					case 7:
						tempp = copytos(bs, size, tempp, size_tm, smt);
						strcpy_s(message, 300, "| You in sort menu 2 |");
						menu = 1;
						while (!exit) {
							SetConsoleTextAttribute(hCon, (WORD)((15 << 4) | 0));
							cout << "Kurs: " << usd_to_grn << endl;
							SetConsoleTextAttribute(hCon, (WORD)((Black << 4) | LightGray));
							cl();
							CoutNOAll(tempp, size_tm, type);
							message_send(message);
							cout << "Sort: " << endl;
							menus(" << Back|To width|To height|To kol in sclad|To price USD", menu);

							switch (menu) {
							case 0:
								delete[] tempp;
								tempp = nullptr;
								size_tm = 0;
								type = 1;
							case 1:
								type = 2;
								for (int i = 0; i < size_tm - 1; i++)
									for (int j = size_tm - 1; j > i; j--)
										if (tempp[j].width < bs[j-1].width) swap(tempp[j], tempp[j - 1]);
								strcpy_s(message, 300, "| Sorted of width |");
							break;
							case 2:
								type = 2;
								for (int i = 0; i < size_tm - 1; i++)
									for (int j = size_tm - 1; j > i; j--)
										if (tempp[j].height < tempp[j - 1].height) swap(tempp[j], tempp[j - 1]);
								strcpy_s(message, 300, "| Sorted of Height |");
								break;
							case 3:
								type = 2;
								for (int i = 0; i < size_tm - 1; i++)
									for (int j = size_tm - 1; j > i; j--)
										if (tempp[j].kol < tempp[j - 1].kol) swap(tempp[j], tempp[j - 1]);
								strcpy_s(message, 300, "| Sorted of kol |");
								break;
							case 4:
								type = 2;
								for (int i = 0; i < size_tm - 1; i++)
									for (int j = size_tm - 1; j > i; j--)
										if (tempp[j].buy < tempp[j - 1].buy) swap(tempp[j], tempp[j - 1]);
								strcpy_s(message, 300, "| Sorted of price in USD |");
								break;
							}
							exit = true;
						}
						menu = 1;
						exit = false;
						break;

					}
					
				}
				exit = false;
				menu = 1;
				break;
		}
	}
	InputBToFile(filename, bs, size);
}
