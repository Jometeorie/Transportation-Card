/*
	该文件定义了与一卡通功能相关的函数的实现，其中包含教师卡、学生卡、限制卡和暂时卡
	四种类型，均继承于Card类。
*/
#include <iostream>
#include <string>
#include <fstream>
#include "trans_card.h"
#define N 100

using namespace std;

extern int card_num; // number of cards in the system
extern int Teacher_card_num;
extern int Student_card_num;
extern int Restrict_card_num;
extern int Temperory_card_num;
extern Student_Card Student[N];
extern Teacher_Card Teacher[N];
extern Restrict_Card Restrict[N];
extern Temperory_Card Temperory[N];

// Time that the valid date can last
const int year_time = 1, month_time = 0, day_time = 0;

// The information of bus cards
Card::Card()
{
}

void Card::Get_Vaild_Info(int & y, int & m, int & d) const
{
	y = valid_year;
	m = valid_month;
	d = valid_day;
}

bool Card::Check_Money() const
{
	if(extra_money < 5 && extra_money >= 2)
		{
			cout << "Your balance is too low, please recharge in time." << endl;
			return true;
		}
	if(extra_money < 2)
		{
			cout << "You can't take the bus for the lack of balance." << endl;
			return false;
		}
	else
		return true;
}

bool Card::Check_Valid_Date(int y, int m, int d) const
{
	if(y > valid_year)
		return false;
	if(y == valid_year)
	{
		if(m > valid_month)
			return false;
		if(m == valid_month)
		{
			if (d > valid_day)
				return false;
			else
				return true;
		}
		else
			return true;
	}
	else
		return true;
}

void Card::Show_Card() const
{
	cout << "Owner's name: " << Owner.name << endl;
	cout << "Card ID: " << card_id << endl;
	cout << "profession: " << Owner.profession << endl;
	cout << "Working place: " << Owner.work_place << endl;
	cout << "Extra money: " << extra_money << endl;
	cout << "Valid date: " << "Year: " << valid_year << endl
	     << "            " << "Month: " << valid_month << endl
	     << "            " << "day: " << valid_day << endl;
}

void Card::Fee_Deduction()
{
	if(extra_money - cost < 0)
	{
		cout << "You haven't got enough money, please recharge first!" << endl;
		return;
	}
	times++;
	times_per_mon++;
	extra_money -= cost;
	cout << "Done!" << endl;
}

void Card::Destroy()
{
	Owner.name = Owner.profession = Owner.work_place = "Unknown";
	card_id = 0;
	card_num--;
}

void Card::Write_To_CSV(string file)
{
	ifstream inFile(file, ios::out);
	fstream outFile;
	outFile.open(file, ios::app);

	// Count lines.
	int lines = 0;
	string temp;
	while(getline(inFile, temp))
		lines++;

	outFile << lines << ',' 
			<< card_id << ',' 
			<< Owner.name << ','
			<< Owner.profession << ',' 
			<< Owner.work_place << ','
			<< Owner.sex << ',' 
			<< Owner.salary << ',' 
			<< times_per_mon << ',' 
			<< times << ',' 
			<< extra_money << ',' 
			<< valid_year << ','
			<< valid_month << ','
			<< valid_day << ','
			<< endl;
	outFile.close();
}

void Teacher_Card::Start(int year, int month, int day)
{
	fstream outFile;
	outFile.open("Restrict_Card.csv", ios::app);
	//extra_money = Get_Extra_Money();
	Owner = Get_Owner_Infornmation();
	int i;
	//Teacher[Teacher_card_num] = new Card;
	Owner.profession = "Teacher";
	cout << "Enter your name: ";
	cin >> Owner.name;
	cout << "Please enter you sex(Man, Woman or else: Unknown): ";
	cin >> Owner.sex;
	if(Owner.sex != "Man" && Owner.sex != "Woman")
		Owner.sex == "Unknown";
	cout << "Enter your work place: ";
	cin >> Owner.work_place;
	cout << "Enter your salary: ";
	cin >> Owner.salary;
	for(i = 0; Teacher[i].card_id != 0; i++);
	//card_id = to_string(100000 + Teacher_card_num);
	times = 0;
	times_per_mon = 0;
	cost = 0;
	extra_money = 0;
	valid_year = year + year_time;
	valid_month = month + month_time;
	valid_day = day + day_time;
	card_num++;
	Teacher_card_num++;
	card_id = 100000 + i;
	Teacher[i] = *this;
	cout << "Your ID number is " << card_id << ", "
	     << "Please remember." << endl;
	Write_To_CSV("Teacher_Card.csv");
}

void Teacher_Card::Destroy()
{
	Owner.name = Owner.profession = Owner.work_place = "Unknown";
	card_id = 0;
	card_num--;
	Teacher_card_num--;	
}

void Student_Card::Start(int year, int month, int day)
{
	int i;
	//Student[Student_card_num] = new Card;
	Owner.profession = "Student";
	cout << "Enter your name: ";
	cin >> Owner.name;
	cout << "Please enter you sex(Man, Woman or else: Unknown): ";
	cin >> Owner.sex;
	if(Owner.sex != "Man" && Owner.sex != "Woman")
		Owner.sex == "Unknown";
	cout << "Enter your work place: ";
	cin >> Owner.work_place;
	Owner.salary = 0;
	cout << "Enter your student ID: ";
	cin >> stu_id;
	for(i = 0; Student[i].card_id != 0; i++);
	//card_id = to_string(200000 + Student_card_num);
	times = 0;
	times_per_mon = 0;
	cost = 2;
	extra_money = 0;
	valid_year = year + year_time;
	valid_month = month + month_time;
	valid_day = day + day_time;
	card_num++;
	Student_card_num++;
	card_id = 200000 + i;
	Student[i] = *this;
	cout << "Your ID number is " << card_id << ", "
	     << "Please remember." << endl;
	Write_To_CSV("Student_Card.csv");
}

void Student_Card::Destroy()
{
	Owner.name = Owner.profession = Owner.work_place = "Unknown";
	card_id = 0;
	card_num--;
	Student_card_num--;
}

void Restrict_Card::Start(int year, int month, int day)
{
	int i;
	//Restrict[Restrict_card_num] = new Card;
	cout << "Enter your profession: ";
	cin >> Owner.profession;
	cout << "Enter your name: ";
	cin >> Owner.name;
	cout << "Please enter you sex(Man, Woman or else: Unknown): ";
	cin >> Owner.sex;
	if(Owner.sex != "Man" && Owner.sex != "Woman")
		Owner.sex == "Unknown";
	cout << "Enter your work place: ";
	cin >> Owner.work_place;
	cout << "Enter your salary: ";
	cin >> Owner.salary;
	for(i = 0; Restrict[i].card_id != 0; i++);
	//card_id = to_string(300000 + Restrict_card_num);
	times = 0;
	times_per_mon = 0;
	cost = 2;
	extra_money = 0;
	valid_year = year + year_time;
	valid_month = month + month_time;
	valid_day = day + day_time;
	card_num++;
	Restrict_card_num++;
	card_id = 300000 + i;
	Restrict[i] = *this;
	cout << "Your ID number is " << card_id << ", "
	     << "Please remember." << endl;
	Write_To_CSV("Restrict_Card.csv");
}

void Restrict_Card::Fee_Deduction()
{
	if(times_per_mon < 20)
		extra_money -= 0;
	else
	{
		if(extra_money - cost < 0)
		{
			cout << "You haven't got enough money, please recharge first!" << endl;
			return;
		}
		extra_money -= cost;
	}
	cout << "Time " << times << ", Done!" << endl;
	if(times_per_mon == 20)
		cout << "This is the last time you can take the bus for free!" << endl;
	times++;
	times_per_mon++;
}

void Restrict_Card::Show_Card() const
{
	cout << "Owner's name: " << Owner.name << endl;
	cout << "Card ID: " << card_id << endl;
	cout << "profession: " << Owner.profession << endl;
	cout << "Working place: " << Owner.work_place << endl;
	cout << "Extra money: " << extra_money << endl;
	cout << "Valid date: " << "Year: " << valid_year << endl
	     << "            " << "Month: " << valid_month << endl
	     << "            " << "day: " << valid_day << endl;

	cout << "You have taken " << times_per_mon 
	     << " times this month." << endl;
	if(20 == times_per_mon)
		cout << "This is the last chance you can take for free this month!"
	         << endl;
	if(21 == times_per_mon)
		cout << "It is not for free this time!" << endl;
}

void Restrict_Card::Destroy()
{
	Owner.name = Owner.profession = Owner.work_place = "Unknown";
	card_id = 0;
	card_num--;
	Restrict_card_num--;
}

void Temperory_Card::Destroy()
{
	Owner.name = Owner.profession = Owner.work_place = "Unknown";
	card_id = 0;
	card_num--;
	Temperory_card_num--;
}

void Temperory_Card::Start(int year, int month, int day)
{
	int i;
	//Temperory[Temperory_Card] = new Card;
	cout << "Enter your profession: ";
	cin >> Owner.profession;
	cout << "Enter your name: ";
	cin >> Owner.name;
	cout << "Please enter you sex(Man, Woman or else: Unknown): ";
	cin >> Owner.sex;
	if(Owner.sex != "Man" && Owner.sex != "Woman")
		Owner.sex == "Unknown";
	cout << "Enter your work place: ";
	cin >> Owner.work_place;
	cout << "Enter your salary: ";
	cin >> Owner.salary;
	for(int t = 0; t < Teacher_card_num; t++)
		if(Teacher[t].Get_Owner_Name() == Get_Owner_Name())
		{
			cout << "You have already got a Teacher Card!" << endl;
			Destroy();
			return;
		}
	for(int t = 0; t < Student_card_num; t++)
		if(Student[t].Get_Owner_Name() == Get_Owner_Name())
		{
			cout << "You have already got a Student Card!" << endl;
			Destroy();
			return;
		}
	for(int t = 0; t < Restrict_card_num; t++)
		if(Restrict[t].Get_Owner_Name() == Get_Owner_Name())
		{
			cout << "You have already got a Restrict Card!" << endl;
			Destroy();
			return;
		}
	for(i = 0; Temperory[i].card_id != 0; i++);
	times = 0;
	times_per_mon = 0;
	cost = 2;
	extra_money = 0;
	valid_year = year + year_time;
	valid_month = month + month_time;
	valid_day = day + day_time;
	card_num++;
	Temperory_card_num++;
	card_id = 400000 + i;
	Temperory[i] = *this;
	cout << "Your ID number is " << card_id << ", "
	     << "Please remember." << endl;
	Frozen = false;
	Write_To_CSV("Temperory_Card.csv");
}

bool Temperory_Card::IsFrozen(int year, int month, int day)
{
	if (!Check_Valid_Date(year, month, day))
		return true;
	else
		return false;
}

void Temperory_Card::Thaw(int year, int month, int day)
{
	cout << "Do you want to thaw your card now?(Y or N)" << endl;
	string check;
	while(check != "Y" && check != "N")
		cin >> check;
	if(check == "Y")
	{
		string tempname = "Unknown";
		cout << "Confirm your name: ";
		cin >> tempname;
		while(tempname != Owner.name)
		{
			cout << "Wrong name! Please enter your origin name again: ";
			cin >> tempname;
		}
		cout << "Enter your profession now: ";
		cin >> Owner.profession;
		cout << "Enter your work place now: ";
		cin >> Owner.work_place;
		cout << "Enter your salary now: ";
		cin >> Owner.salary;
		valid_year = year + year_time;
		valid_month = month + month_time;
		valid_day = day + day_time;
		cout << "Done!" << endl;
	}
	else if(check == "N")
	{
		cout << "Bye!" << endl;
	}
}