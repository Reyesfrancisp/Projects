# ifndef bankAccount_H
# define bankAccount_H

/*

Francis Reyes
Stocks + Bank Project


*/

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <ctime>
#include <fstream>

using namespace std;

#pragma warning(disable : 4996) //disable error

class bankAccount : public account {
public:
	bankAccount();
	void menu();
	void Deposit(double);
	void Withdraw(double);
private:

};
# endif

bankAccount::bankAccount() {
	//cout << "MAKING DERIVE 1" << endl;
}

void bankAccount::menu() {
	bool flag = true;
	int selection;
	char test[256]; //comment line below and uncomment this one to use the getlines
	while (flag) {
		cout << "\nPlease select an option" << endl
			<< "\t1. View account balance" << endl
			<< "\t2. Deposit money" << endl
			<< "\t3. Withdraw money" << endl
			<< "\t4. Display transaction history" << endl
			<< "\t5. Return to previous menu" << endl;

		cout << "\tYour selection: ";

		cin.getline(test, 256);
		selection = stoi(test);
		cout << endl;
		//testing getline looking for spaces to read input file instead
		switch (selection) {
		case 1:
			displayC();
			break;
		case 2:
		{
			double amount, current;
			cout << "\nEnter the amount of money to be deposited: ";
			//check amount
			amount = validInput(1);
			if (amount == 0)
			{
				cout << "Invalid input." << endl;
				break;
			}

			current = amount + getBalance();
			setBalance(current);
			//bank transaction history
			Deposit(amount);
			cout << "\nDeposting $" << amount << " to the bank account" << endl;
			displayC();
			break;
		}
		case 3: {

			double amount, current;
			cout << "\nEnter the amount of money to be withdrawn: ";
			current = getBalance();
			amount = validInput(1);
			if (amount == 0)
			{
				cout << "Invalid input." << endl;
				break;
			}
			if (0 <= (current - amount))
			{
				setBalance(current - amount);
			}
			else
			{
				cout << "Invalid input." << endl;
				break;
			}
			//bank transaction history
			Withdraw(amount);
			cout << "\nWithdrawing $" << amount << " from the bank account" << endl;
			displayC();
			break;
		}
		case 4:
			displayB();
			break;
		case 5:
			flag = false;
			break;
		default:
			cout << "Invalid input.";
			break;
		}
	}
}

void bankAccount::Deposit(double amount) { //deposit function
	time_t now = time(0);
	tm *ltm = localtime(&now);
	char date[9];
	_strdate(date);
	//print to file info
	ofstream myfile;
	myfile.open("bank_transaction_history.txt", ios_base::app);
	myfile << "Deposit     $" << fixed << setprecision(2) << amount << "\t\t$" << fixed << setprecision(2)
		<< getBalance() << "\t" << date << "\t"
		<< setfill('0') << setw(2) << ltm->tm_hour << ":"
		<< setfill('0') << setw(2) << 1 + ltm->tm_min << ":"
		<< setfill('0') << setw(2) << 1 + ltm->tm_sec << endl;
	myfile.close();
}


void bankAccount::Withdraw(double amount) { //withdraw function
	time_t now = time(0);
	tm *ltm = localtime(&now);
	char date[9];
	_strdate(date);
	//print to file info
	ofstream myfile;
	myfile.open("bank_transaction_history.txt", ios_base::app);
	myfile << "Withdraw    $" << fixed << setprecision(2) << amount << "\t\t$" << fixed << setprecision(2)
		<< getBalance() << "\t" << date << "\t"
		<< setfill('0') << setw(2) << ltm->tm_hour << ":"
		<< setfill('0') << setw(2) << 1 + ltm->tm_min << ":"
		<< setfill('0') << setw(2) << 1 + ltm->tm_sec << endl;
	myfile.close();
}