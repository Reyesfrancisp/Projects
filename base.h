# ifndef account_H
# define account_H

/*

Francis Reyes
Stocks + Bank Project

*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

#pragma warning(disable : 4996) //disable error

void currentDisplay(int stock, double price, double total, string symb, string name);
const int name_width = 28;
const int symbol_width = 8;
const int int_width = 10;
const int dbl_width = 12;

class Portfolio { //takes place of current portfolio text file if stocks were to persist throughout multiple uses
private:
	string cname;
	int stocks;
public:
	Portfolio(string, int);
	string getName();
	int getStocks();
	void addStocks(int);
	friend bool sortByName(const Portfolio &, const Portfolio &);
};

Portfolio::Portfolio(string s = " ", int y = 0)
{
	cname = s;
	stocks = y;
}

string Portfolio::getName()
{
	return cname;
}

int Portfolio::getStocks()
{
	return stocks;
}
void Portfolio::addStocks(int s)
{
	stocks += s;
}

vector <Portfolio> P;

class account {
public:
	account();
	double getBalance();
	void setBalance(double);
	void displayT();
	void displayB();
	void displayC();
private:
};
# endif

account::account() {
	//	cout << "MAKING account" << endl;
}

double account::getBalance() //returns the balance variable
{
	ifstream file("cashbalance.txt");
	string line;
	file >> line;
	file.close();
	double balance = stof(line);
	return balance;
}

void account::setBalance(double num) //allows manipulation of the cashbalance text, to update it with the amount needed
{
	string line = to_string(num);
	remove("cashbalance.txt");
	ofstream myfile;
	myfile.open("cashbalance.txt", ios_base::app);
	myfile << line;
	myfile.close();
}

void account::displayC() //current vector display function
{
	cout << "\nCash Balance = $" << fixed << setprecision(2) << getBalance() << endl << endl;

	if (P.size() > 0)
	{
		cout << "Symbol\tCompany Name\t\t\tNumber\t Price      Total" << endl;
	}

	srand(time(NULL));
	int num = rand() % 4 + 1;
	string name = "stock" + to_string(num) + ".txt";
	ifstream file;
	string delim = "\t", line;
	vector <string> tokens;
	double totalSum = 0, price = 0;
	for (int x = 0; x < P.size(); x++)
	{
		file.open(name);
		while (getline(file, line))
		{
			if (line.substr(0, line.find(delim)) == P[x].getName())
			{
				for (int i = 0; i < 3; i++) // making 3 tokens
				{

					if (i == 2)
					{ // handling newline character
						line = line.substr(line.rfind(delim) + 1,
							string::npos);
						line.resize(line.length() - 1); // remove newline
						tokens.push_back(line);
					}
					tokens.push_back(line.substr(0, line.find(delim)));
					line = line.substr(line.find(delim) + 1, string::npos);
				}
				char tab3[256];
				strcpy_s(tab3, tokens[2].c_str());
				price = atof(tab3);
				file.close();
				int stock = 0;
				string symb, name;
				name = tokens[1];
				symb = tokens[0];
				stock = P[x].getStocks();
				double total = 0;
				total = price * P[x].getStocks();
				totalSum += total;
				currentDisplay(stock, price, total, symb, name); //pass amount of stocks/price/ price*stocks + 2 strings for the company name and symbol
				vector<string>().swap(tokens);
			}
		}
	}
	cout << "\nTotal portfolio value: $" << fixed << setprecision(2) << getBalance() + totalSum << endl;
}

void currentDisplay(int stock, double price, double total, string symb, string name)
{
	cout << setfill(' ') << setw(8) << left << symb << setw(32) << left << name << setw(9) << left << stock <<
		"$" << setw(10) << left << fixed << setprecision(2) << price << left << "$" << left << fixed << setprecision(2) << total << '\n';
}

void account::displayT() //reads from stock history and displays it
{
	cout << "\nThe current cash balance is: $" << fixed << setprecision(2) << getBalance() << endl << endl;
	cout << "Action\tSymbol\tShares\tPrice\t\tTime" << endl;
	ifstream file("stock_transaction_history.txt");
	string line;
	while (getline(file, line))
		cout << line << endl;
	file.close();
}

void account::displayB() //reads from bank history and displays it
{
	cout << "\nThe current cash balance is: $" << fixed << setprecision(2) << getBalance() << endl << endl;
	cout << "Action      Amount\t\tCash Balance\tDate\t\tTime\n";
	ifstream file("bank_transaction_history.txt");
	string line;
	while (getline(file, line))
		cout << line << endl;
	file.close();
}

double validInput(int check) // 1 for double, 2 for int
{
	double num = 0;
	int stocknum = 0;
	char test[256];
	if (check == 1)
	{
		//double number checker
		cin.getline(test, 256);
		num = atof(test);
		if (num < 0)
		{
			return 0; // return 0 in case of error
		}
		return num; //return case 1
	}

	if (check == 2)//int number checker
	{
		cin.getline(test, 256);
		stocknum = atoi(test);
		if (stocknum < 0) // checks for positive number
		{
			return 0; // return 0 in case of error
		}
	}
	return stocknum; //return case 2
}

//sort functions below for vector

bool sortByName(const Portfolio &l, const Portfolio &r) { return l.cname < r.cname; }

void vectorSort()
{
	for (int x = 0; x < P.size(); x++)
	{
		if (P[x].getStocks() == 0)
		{
			P.erase((P.begin() + x));
			x = 0;
		}
	}
	sort(P.begin(), P.end(), sortByName);

}