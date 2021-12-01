#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Cell {
public:
	string DataCell;
	int wCoord;
	int hCoord;
	Cell(string _DataCell = "w", int _wCoord = 13, int _hCoord = 13) {
		DataCell = _DataCell;
		wCoord = _wCoord;
		hCoord = _hCoord;
	}
	Cell& operator= (const Cell& cell)
	{
		DataCell = cell.DataCell;
		wCoord = cell.wCoord;
		hCoord = cell.hCoord;
		return *this;
	}
	void SetEmptyCell() {
		flagE = true;
	}
	void SetIntCell() {
		flagI = true;
		flagR = false;
	}
	void SetStrCell() {
		flagS = true;
	}
	void SetRefCell() {
		flagR = true;
	}
	bool IsEmptyCell() {
		return (flagE == true);
	}
	bool IsIntCell() {
		return (flagI == true);
	}
	bool IsStrCell() {
		return (flagS == true);
	}
	bool IsRefCell() {
		return (flagR == true);
	}
	string flag() {
		if (flagE == true) { return "EmptyCell"; }
		if (flagI == true) { return "IntegerCell"; }
		if (flagS == true) { return "StringCell"; }
		if (flagR == true) { return "RefCell"; }
	}
	void SetRef() {
		string s2;
		char ch = DataCell[1];
		hRef = (int)(ch)-65;
		for (int i = 2; i < DataCell.size(); i++) {
			s2 += DataCell[i];
		}
		wRef = stoi(s2)-1;
	}
	int GetRefX() {
		return wRef;
	}
	int GetRefY() {
		return hRef;
	}
private:
	bool flagE,flagI,flagS,flagR = false;
	int wRef, hRef;
};


class Table {
public:
	Table(int _wCoord, int _hCoord) {
		for (int i = 0; i < _wCoord; i++) {
			tempTable.clear();
			for (int j = 0; j < _hCoord; j++) {
				tempTable.push_back(Cell());
			}
			vTable.push_back(tempTable);
		}
		sizeY = vTable[0].size();
		sizeX = vTable.size();
	}
	void changeCell(string _string, int _wCoord, int _hCoord) {
		vTable[_wCoord][_hCoord] = Cell(_string, _wCoord, _hCoord);
	}
	string stringCell(int _w, int _h) {
		return vTable[_w][_h].DataCell;
	}
	int sizeTableX() {
		return sizeX;
	}
	int sizeTableY() {
		return sizeY;
	}
	string sizeTable() {
		string a = to_string(sizeX) + "x" + to_string(sizeY);
		return a;
	}

	string flag(int x,int y) {
		return vTable[x][y].flag();
		cout << vTable[x][y].DataCell.size();
	}
	string GetRef(int x, int y) {
		if (vTable[x][y].IsRefCell()) {
			string a = "[";
			a += to_string(vTable[x][y].GetRefX());
			a += ",";
			a += to_string(vTable[x][y].GetRefY());
			a += "]";
			return a;
		}
		else return "#notRef";
	}
	void flagging() {
		for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {
				if (vTable[i][j].DataCell.empty()) { vTable[i][j].SetEmptyCell(); }
				else
					switch (vTable[i][j].DataCell[0])
					{
					case 39:
						vTable[i][j].SetStrCell();
						break;
					case '=':
						vTable[i][j].SetRefCell();
						break;
					default:
						vTable[i][j].SetIntCell();
						break;
					
					}
			}
		}
	}
		void calculate() {
			bool IsCalc = true;
			int count = 0;
			for (int i = 0; i < sizeX; i++) {
				for (int j = 0; j < sizeY; j++) {
					if (vTable[i][j].IsStrCell()) {
						string a;
						for (int k = 0; k < vTable[i][j].DataCell.size()-1; k++) {
							a+=vTable[i][j].DataCell[k + 1];
						}
						vTable[i][j].DataCell = a;
						a.clear();
					}
					if (vTable[i][j].IsRefCell()) {
						vTable[i][j].SetRef();
						count++;
					}
				}
			}
			while (count > 0) {
				for (int i = 0; i < sizeX; i++) {
					for (int j = 0; j < sizeY; j++) {
						if (vTable[i][j].IsRefCell()) {
							if (!vTable[vTable[i][j].GetRefX()][vTable[i][j].GetRefY()].IsRefCell()) {
								vTable[i][j].DataCell = vTable[vTable[i][j].GetRefX()][vTable[i][j].GetRefY()].DataCell;
								vTable[i][j].SetIntCell();
								count--;
							} if (i == vTable[i][j].GetRefX() && j == vTable[i][j].GetRefY()) {
								vTable[i][j].DataCell = "#error";
								count--;
								vTable[i][j].SetIntCell();
							} if (vTable[i][j].GetRefX() > sizeX || vTable[i][j].GetRefY() > sizeY) {
								vTable[i][j].DataCell = "#error";
								count--;
							} if (vTable[vTable[i][j].GetRefX()][vTable[i][j].GetRefY()].GetRefX() == i && vTable[vTable[i][j].GetRefX()][vTable[i][j].GetRefY()].GetRefY() == j) {
								vTable[i][j].DataCell = "#error";
								count--;
						}

						}
					}
				}
			}
	}

private:
	int sizeX, sizeY;
	vector<Cell> tempTable;
	vector<vector<Cell>> vTable;
};

int main()
{
	int wTable, hTable;
	cin >> wTable >> hTable;
	string tempstr;
	char ch = 0;
	Table mTable(wTable, hTable);
	for (int index = 0; index < wTable; index++) {
		for (int jndex = 0; jndex < hTable; jndex++) {
			while (true) {
				cin.clear();
				cin.get(ch);
				if (ch != 10) {
					if (ch != '\t') {
						tempstr += ch;
					}
					else break;
				}
				cin.clear();
			};
			mTable.changeCell(tempstr, index, jndex);
			tempstr.clear();
		}
	}
	mTable.flagging();
	mTable.calculate();
	for (int i = 0; i < mTable.sizeTableX(); i++) {
		for (int j = 0; j < mTable.sizeTableY(); j++) {
			cout << mTable.stringCell(i, j) << "\t";
		}
		cout << "\n";
	}
}