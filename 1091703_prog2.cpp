#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
string dete[6] = { "li","beq","bne","add","addi","andi"};
string top[4] = { "SN","WN","ST","WT" };
string Rs[6] = { "R1","R2","R3","R4","R5","R6" };
int rs[6] = { 0 };
fstream op("郎.txt");
string S;
vector<string> s;
int c = 0;
vector<int> entry;
int* mis;
int** Top;
int** pre;
void LI(int x)
{
	vector<string> data;
	data.resize(1);
	op >> S;
	s[s.size() - 1] += " " + S;
	if (x == 0)
		return;
	int da = 0;
	for (int i = 0; i < S.size(); i++)
	{
		if (S[i] == ',')
		{
			data.resize(data.size() + 1);
			continue;
		}
		if (data.size() != 1)
		{
			da *= 10;
			da += S[i] - 48;
		}
		else
			data[data.size() - 1] += S[i];
	}
	for (int i = 0; i < data.size() - 1; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (data[i] == Rs[j])
			{
				rs[j] = da;	
				break;
			}
		}
	}
}
void co(int C, int *mis, int** pre, int** Top, int acl)
{
	cout << "Entyy: " << entry[c] << "         " << s[C]<<endl;
	cout << "(";
	char R[3] = { '0','0','0' };
	for (int i = 0; i < 3; i++)
		cout << pre[c][i];
	int p = 0;
	for (int i = 0; i < 3; i++)
	{
		p *= 2;
		p += pre[c][i];
	}
	for (int i = 0; i < 8; i++)
	{
		if (Top[c][i] == 0)
			cout << ", " << top[0];
		else if (Top[c][i] == 1)
			cout << ", " << top[1];
		else if (Top[c][i] == 2)
			cout << ", " << top[2];
		else if (Top[c][i] == 3)
			cout << ", " << top[3];
	}
	cout << ") ";
	if (Top[c][p] / 2 != 0)
		cout << "T ";
	else
		cout << "N ";
	if (acl == 1)
		cout << "T    ";
	else
		cout << "N    ";
	if (acl != Top[c][p] / 2)
		mis[c]++;
	cout << "misprediction: " << mis[c] << endl;
	if (acl == 1 && Top[c][p] != 3)
		Top[c][p]++;
	else
		if (Top[c][p] != 0)
			Top[c][p]--;
	for (int i = 0; i < 2; i++)
		pre[c][i] = pre[c][i + 1];
	pre[c][2] = acl;

	c++;
	if (c >= entry.size())
		c = 0;
}
int main()
{
	if (!op)
	{
		cout << "sorry, file can't open.";
		op.close();
		exit(0);
	}
	else
	{
		while (op >> S)
		{
			int x = 0;
			for(int i=0;i<6;i++)
			if (S == dete[i])
			{
				s.resize(s.size() + 1);
				s[s.size() - 1] += S;
				if (S == "li")
					x++;
				LI(x);
			}

		}
		op.close();
	}
	int en = 0;;
	cout << "块Entry (Entry > 0)\n";
	while (en <= 0 || en & 2 != 0)
		cin >> en;
	while (en / 2 > 0)
	{
		en /= 2;
		entry.resize(entry.size() + 1);
		if (en != 1)
			entry[entry.size() - 1] = en;
		else
			entry[entry.size() - 1] = 0;
	}
	Top = new int* [entry.size()]();   //魁–Ω计N/TΩ计
	mis = new int [entry.size()]();     //魁箇代ア毖Ω计
	pre = new int* [entry.size()]();     //魁–程玡计
	for (int i = 0; i < entry.size(); i++)
	{
		Top[i] = new int[8]();
		pre[i] = new int[3]();
	}
	for (int i = 0; i < 3; i++)
		co(i,mis,pre,Top,0);
	int lop = 3;
	for (; rs[3] != rs[2]; rs[3]++)
	{
		co(3, mis, pre, Top, 0);
		co(4, mis, pre, Top, 0);
		for (rs[4] = 0; rs[4] != rs[2]; rs[4]++)
		{
			co(5, mis, pre, Top, 0);
			rs[5] = (rs[3] + rs[4]) % 4;
			co(6, mis, pre, Top, 0);
			co(7, mis, pre, Top, 0);
			if (rs[5] == 0)
			{
				co(8, mis, pre, Top, 0);
				rs[1] += rs[4];
				co(9, mis, pre, Top, 0);
			}
			else
				co(8, mis, pre, Top, 1);
			co(10, mis, pre, Top, 0);
			co(11, mis, pre, Top, 1);
		}
		co(5, mis, pre, Top, 1);
		co(12, mis, pre, Top, 0);
		co(13, mis, pre, Top, 1);
	}
	co(3, mis, pre, Top, 1);
}
