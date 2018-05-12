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

HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;
int GetBufferChars()
{
	GetConsoleScreenBufferInfo(hCon, &csbInfo);
	return csbInfo.srWindow.Right;

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
				cout << " ";
			}
		}
		else if (current_pos.y == pos.y) {
			gotoxy(pos.x, current_pos.y);
			if (current_pos.x != pos.x) for (int i = 0; i < GetBufferChars() - pos.x; i++)
			{
				cout << " ";
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
	char ttm[30];
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

	cout << "Input price in dollars: ";
	pos_curr = pos_cur();
	do
	{
		clearToPos(pos_curr);
		cin.getline(ttm, 29);
		temp.buy_dollars = onlynums(ttm);
	} while (temp.buy_dollars < 1);

	cout << "Input price in grn: ";
	pos_curr = pos_cur();
	do
	{
		clearToPos(pos_curr);
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
void cout_cl(const char* out, int font = LightGray, int back = Black) {
	SetConsoleTextAttribute(hCon, (WORD)((back << 4) | font));
	cout << out;
	SetConsoleTextAttribute(hCon, (WORD)((Black << 4) | LightGray));
}
void coutNoAllcolor(int i,char * name, int kol, int width, int height, int buy_dollars, int buy_grn, int promiz_kol) {
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
	cout << setw(6) << buy_dollars;
	cout_cl("|", promiz_kol);
	cout << setw(6) << buy_grn;
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
	cout << setw(6) << "USD";
	cout_cl("|", colorr);
	cout << setw(6) << "GRN";
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
			coutNoAllcolor(i, bs[i].name, bs[i].kol, bs[i].width, bs[i].height, bs[i].buy_dollars, bs[i].buy_grn, color_row);
			fullline('-', color_line);
		}

	}
}
void CoutNOAll(base * bs, const int size) {
	const int color_items = 15, color_line = 4, color_row = 12;
	coutnoallone(bs, size, 'p', "PRINTERS", color_items, color_line, color_row);
	cout << endl;
	coutnoallone(bs, size, 'c', "COMPUTER BLOCKS", color_items, color_line, color_row);
	cout << endl;
	coutnoallone(bs, size, 'm', "MONITORS", color_items, color_line, color_row);
	cout << endl;
	coutnoallone(bs, size, 'k', "KEYBOARDS", color_items, color_line, color_row);
	cout << endl;
	coutnoallone(bs, size, 'o', "MOUSES", color_items, color_line, color_row);
	cout << endl;
	coutnoallone(bs, size, 'a', "SCANERS", color_items, color_line, color_row);
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
			coutNoAllcolor(i, bs[i].name, bs[i].kol, bs[i].width, bs[i].height, bs[i].buy_dollars, bs[i].buy_grn, color_row);
			fullline('-', color_line);
		}
	}
	else
	{
		fullline('-', color_items);
		cout << setiosflags(ios::left);
		punks(color_items);
		fullline('-', color_items);
		for (int i = 0; i < size; i++)
		{
			coutNoAllcolor(i, bs[i].name, bs[i].kol, bs[i].width, bs[i].height, bs[i].buy_dollars, bs[i].buy_grn, color_row);
			fullline('-', color_line);
		}
	}
}

int SelectItems(base *bs, const int size, bool *masstoseind) {
	char act, message[301] = { "" }, options[301] = { "BACK : B, OK : O" };
	int ch = 0, start = 0, finish = 13, item = 0;
	bool reload = true, exit = false, reload_back = false;
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
					cout << "*";
				}
			
			}
			gotoxy(0, 29);
			cout << options << message;
			message[0] = '\0';
		}
		if (strlen(message)) {
			gotoxy(0, 29);
			cout << options << message;
			message[0] = '\0';
		}
		else {
			gotoxy(0, 29);
			int _chars = GetBufferChars();
			for (int i = 0; i < _chars; i++)
			{
				cout << ' ';
			}
			gotoxy(0, 29);
			cout << options;
		}
		if (item > 0 && item < finish - 1) {
			gotoxy(0, 3 + ((item - 1 - start) * 2));
			cout << " ";
			gotoxy(0, 3 + ((item + 1 - start) * 2));
			cout << " ";
		}
		else
		if (item == 0) {
			gotoxy(0, 3 + ((item + 1 - start) * 2));
			cout << " ";
		}
		else
		if (item == finish-1) {
			gotoxy(0, 3 + ((item - 1 - start) * 2));
			cout << " ";
		}
		
		gotoxy(0, 3 + ((item - start) * 2));
		cout << ">";
		while (ch != 13 && ch != 80 && ch != 72 && ch != -87 && ch != -23)
		{
			act = _getch();
			ch = static_cast<int>(act);//привожу к соответствующему коду
			switch (ch)
			{
			case 80: // вниз
				if (item < size - 1) item++; 
				else ch = 0;
				if (item+1 > finish && finish < size && ch != 0) {
					finish++;
					start++;
					reload = true;
				}
				break;
			case 72: // вверх
				if (item > 0) item--;
				else ch = 0;
				if (item < start && start > 0 && ch != 0) {
					finish--;
					start--;
					reload = true;
				}
				break;
			case -87:
				exit = true;
				break;
			case -23:
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
			}
		}
	}
	return 0;
}
void main() {
	
	int size = 0, menu = 1;
	bool exit = false, *mass = new bool[size];
	char message[301] = { "Hello in main base!" }, filename[20] = { "my.txt" };
	base *bs = nullptr;
	bs = synhronize(filename, bs, size);
	while (!exit) {
		cl();
		CoutNOAll(bs, size);
		message_send(message);
		menus("Exit|Cout all of index|Add New Vehicle", menu);
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
							fullline('-', LightRed);
							cout << "Index\t: " << i + 1 << endl;
							cout << "\tType: ";
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
							cout << "\tName\t: " << bs[i].name << endl;
							cout << "\tHow many\t: " << bs[i].kol << endl;
							cout << "\tWidth\t: " << bs[i].width << endl;
							cout << "\tHeigth\t: " << bs[i].height << endl;
							cout << "\tBut in GRN\t: " << bs[i].buy_dollars << endl;
							cout << "\tBut in USD\t: " << bs[i].buy_grn << endl;
							
						}
					}
				while (!yesno("<< Back (Yes or No): "));
				}else strcpy_s(message, 300, " | You in main menu |");
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
		}
	}
	InputBToFile(filename, bs, size);
}
