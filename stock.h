# ifndef stockAccount_H
# define stockAccount_H

/*

Francis Reyes
Stocks + Bank Project

*/

#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <fstream>
#include <ctime>
#include <iomanip>
using namespace std;

#pragma warning(disable : 4996) //disable error

class stockAccount : public account {
public:
	stockAccount();
	void menu();
	// void stockPrice(string);
	void buyStock(string, int, double);
	void sellStock(string, int);
	bool stockExists(string symbol);
	void getRandPrice(string);
private:

};
# endif

stockAccount::stockAccount() {
	//cout << "MAKING DERIVE 2" << endl;
}

void stockAccount::menu() {
	bool flag = true;
	int selection = 0;
	char test[256];

	while (flag) {
		cout << "\nPlease select an option" << endl
			<< "\t1. Display current price for a stock symbol" << endl
			<< "\t2. Buy stock" << endl
			<< "\t3. Sell stock" << endl
			<< "\t4. Display current portfolio" << endl
			<< "\t5. Display transaction history" << endl
			<< "\t6. Return to previous menu" << endl;

		cout << "\tYour selection: ";

		cin.getline(test, 256);
		selection = atoi(test);
		cout << endl;

		switch (selection)
		{
		case 1:  //done
		{
			cout << "\nEnter the stock symbol you wish to check: ";
			char line[256];
			cin.getline(line, 256);
			string symbol(line);
			cout << endl;
			getRandPrice(symbol);
			break;
		}
		case 2: {
			cout << "\nEnter the stock symbol you wish to purchase: ";
			char line[256];
			cin.getline(line, 256);
			string symbol(line);
			if (stockExists(symbol) == false)
			{
				cout << "Cannot process transaction." << endl;
				break;
			}
			cout << "\nEnter the number of stocks you wish to purchase: ";
			double numShare = validInput(2);
			if (numShare == 0)
			{
				cout << "Cannot process transaction." << endl;
				break;
			}
			cout << "\nEnter the max price you are willing to pay for each stock: $";
			double price = validInput(1);
			if (price == 0)
			{
				cout << "Cannot process transaction." << endl;
				break;
			}
			if (price != 0 && numShare != 0)
			{
				buyStock(symbol, numShare, price);
			}
			break;
		}
		case 3:
		{
			cout << "\nEnter the stock symbol you wish to sell: ";
			char inputline[256];
			cin.getline(inputline, 256);
			string symbol(inputline);
			bool sExists = false;
			int stockloc = 0;
			for (int x = 0; x < P.size(); x++)
			{
				if (symbol == P[x].getName())
				{
					sExists = true;
					stockloc = x;
				}
			}
			if (sExists == true)
			{
				int currentStocks = 0;
				cout << "\nEnter the amount of stocks you wish to sell: ";
				double sellStocks = validInput(2);
				if (sellStocks != 0)
				{
					currentStocks = P[stockloc].getStocks();
					if (currentStocks - sellStocks >= 0)
					{
						//for loop to update current stocks
						for (int x = 0; x < P.size(); x++)
						{
							if (P[x].getName() == symbol)
							{
								P[x].addStocks(-sellStocks);
							}
						}
						//continue to function
						cout << "\nSold " << sellStocks << " stocks of " << symbol << " from the portfolio." << endl;
						sellStock(symbol, sellStocks);
					}
					else
					{
						cout << "Cannot process transaction." << endl;
					}
				}
				else
				{
					cout << "Cannot process transaction." << endl;
				}
			}
			else
			{
				cout << "Cannot process transaction." << endl;
			}
			break;
		}
		case 4:
			displayC();
			break;
		case 5:
			displayT();
			break;
		case 6:
			flag = false;
			break;
		default:
			cout << "\nInvalid input." << endl;
			break;
		}
	}
}


void stockAccount::buyStock(string symbol, int numShare, double sharePrice)
{
	double price;
	srand(time(NULL));
	int num = rand() % 4 + 1;
	string name = "stock" + to_string(num) + ".txt";
	ifstream file;
	file.open(name);
	string delim = "\t", line;
	vector <string> tokens;
	bool flag1 = false, flag2 = false, flag3 = false;
	while (getline(file, line))
	{
		if (line.substr(0, line.find(delim)) == symbol)
		{
			flag1 = true;
			for (int i = 0, x = 0; i < 3; i++) // making 3 tokens
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
			if (price <= sharePrice)
			{
				flag2 = true;
			}
			if (flag2 == true && numShare * price <= getBalance())
			{
				flag3 = true;
				setBalance((getBalance() - (numShare*price)));
			}
		}
	}
	file.close();
	time_t now = time(0);
	tm *ltm = localtime(&now);

	bool flag4 = false;
	if (flag1 == true && flag2 == true && flag3 == true)
	{
		cout << "\nBought " << numShare << " stocks of " << symbol << endl;
		Portfolio temp(symbol, numShare);
		//current portfolio checking
		for (int x = 0; x < P.size(); x++)
		{
			if (P[x].getName() == temp.getName())
			{
				P[x].addStocks(numShare);
				flag4 = true;
			}
		}
		if (flag4 == false)
		{
			P.push_back(temp);
		}
		//sort
		vectorSort();
		//print to file info
		ofstream myfile;
		myfile.open("stock_transaction_history.txt", ios_base::app);
		myfile << "Buy \t" << symbol << "\t" << numShare << "\t$" << fixed << setprecision(2) << price << "\t\t"
			<< setfill('0') << setw(2) << ltm->tm_hour << ":"
			<< setfill('0') << setw(2) << 1 + ltm->tm_min << ":"
			<< setfill('0') << setw(2) << 1 + ltm->tm_sec << endl;
		myfile.close();
		displayC(); //display
	}
	if (flag1 == false || flag2 == false || flag3 == false)
	{
		cout << "Cannot process transaction." << endl;
	}
	vector<string>().swap(tokens);
}

void stockAccount::sellStock(string symbol, int numShare) {

	double price;
	srand(time(NULL));
	int num = rand() % 4 + 1;
	string name = "stock" + to_string(num) + ".txt";
	ifstream file;
	file.open(name);
	string delim = "\t", line;
	vector <string> tokens;
	bool flag1 = false;
	while (getline(file, line))
	{
		if (line.substr(0, line.find(delim)) == symbol)
		{
			flag1 = true;
			for (int i = 0, x = 0; i < 3; i++) // making 3 tokens
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

			setBalance((getBalance() + (numShare*price)));
		}
	}
	file.close();
	time_t now = time(0);
	tm *ltm = localtime(&now);

	if (flag1 == true)
	{
		//sort
		vectorSort();
		//print to file info
		ofstream myfile;
		myfile.open("stock_transaction_history.txt", ios_base::app);
		myfile << "Sell\t" << symbol << "\t" << numShare << "\t$" << fixed << setprecision(2) << price << "\t\t"
			<< setfill('0') << setw(2) << ltm->tm_hour << ":"
			<< setfill('0') << setw(2) << 1 + ltm->tm_min << ":"
			<< setfill('0') << setw(2) << 1 + ltm->tm_sec << endl;
		myfile.close();

		displayC(); //display
	}
	else
	{
		cout << "Cannot process transaction." << endl;
	}
	vector<string>().swap(tokens);
}


bool stockAccount::stockExists(string symbol)
{
	int num = rand() % 4 + 1;
	string name = "stock" + to_string(num) + ".txt";
	ifstream file;
	file.open(name);
	string delim = "\t", line;

	bool flag = false;
	while (getline(file, line))
	{
		if (line.substr(0, line.find(delim)) == symbol)
		{
			flag = true;
		}
	}
	file.close();
	return flag;
}

void stockAccount::getRandPrice(string company)
{
	srand(time(NULL));
	int num = rand() % 4 + 1;
	string name = "stock" + to_string(num) + ".txt";
	ifstream file;
	file.open(name);
	string delim = "\t", line;
	vector <string> tokens;
	bool flag = false;
	while (getline(file, line))
	{
		if (line.substr(0, line.find(delim)) == company)
		{
			flag = true;
			for (int i = 0, x = 0; i < 3; i++) // making 3 tokens
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
		}
	}
	file.close();
	time_t now = time(0);
	tm *ltm = localtime(&now);
	if (flag == true)
	{
		char tab3[256];
		strcpy_s(tab3, tokens[2].c_str());
		double price = atof(tab3);

		cout << tokens[0] << "\t" << tokens[1] << "\t\t" << fixed << setprecision(2) << price << "\t"
			<< setfill('0') << setw(2) << ltm->tm_hour << ":"
			<< setfill('0') << setw(2) << 1 + ltm->tm_min << ":"
			<< setfill('0') << setw(2) << 1 + ltm->tm_sec << endl << endl;
	}
	else
	{
		cout << "Stock not found." << endl;
	}
	vector<string>().swap(tokens);
}