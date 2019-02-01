/*
	该文件为一卡通系统的主运行函数，其中包含一个main函数和一个Start函数。
	Start函数用来创建一个用户友好型的菜单窗口，让用户可以通过键盘输入相关操作。
*/
#include <iostream>
#include <string>
#include "trans_card.h"
#define N 100
#define M 100

using namespace std;
int card_num = 0; // number of cards in the system
int Teacher_card_num = 0;
int Student_card_num = 0;
int Restrict_card_num = 0;
int Temperory_card_num = 0;
Student_Card Student[N];
Teacher_Card Teacher[N];
Restrict_Card Restrict[N];
Temperory_Card Temperory[N];

int bus_num = 0;
Bus bus[M];

void start();

int main()
{
	Load();
	Load2();
	start();

	return 0;
}

void start()
{
	Card C;
	Teacher_Card T;
	Student_Card S;
	Restrict_Card R;
	Temperory_Card TC;
	Bus B;
	string temp1, temp2, temp3;
	int n1[100], n2[100];

	cout << "Enter the date today: ";
	int year = 0, month = 0, day = 0;
	while(month < 1 || month > 12 || day < 1 || day > 30)
		cin >> year >> month >> day;

	while(1)
	{	
		cout << "What do you want to do(0 to quit)?" << endl;
		cout << "1.Card Business    2.Bus Business    3.Start again" << endl;
		cin >> temp1;
		if(temp1 == "1")
		{
			cout << "1.Create    2.Log in    3.Log out" << endl;
			cin >> temp2;
			if(temp2 == "1")
			{
				cout << "What card do you want to get?" << endl;
				cout << "1.Teacher Card    2.Student Card    3.Restrict Card    "
				     << "4.Temperory Card" << endl;
				cin >> temp3;
				if(temp3 == "1")				
					T.Start(year, month, day);
				else if(temp3 == "2")
					S.Start(year, month, day);
				else if(temp3 == "3")
					R.Start(year, month, day);
				else if(temp3 == "4")
					TC.Start(year, month, day);
			}
			else if(temp2 == "2")
			{
				int ID;
				int i, j;
				cout <<  "what is your card ID?" << endl;
				cin >> ID;
				int check = 0;
				for(i = 0; i < N; i++)
				{
					if(Teacher[i].Check_ID(ID))
						{C = Teacher[i]; check = 1; j = i;}
					if(Student[i].Check_ID(ID))
						{C = Student[i]; check = 2; j = i;}
					if(Restrict[i].Check_ID(ID))
						{C = Restrict[i]; check = 3; j = i;}
					if(Temperory[i].Check_ID(ID))
						{C = Temperory[i]; check = 4; j = i;}
				}
				if(!check)
				{
					cout << "Not found!" << endl;
					continue;
				}
				//cin.clear();

				cout << "Welcome! " << C.Get_Owner_Name() << "!" << endl;
				while(1)
				{
					cout << "What do you wan to do?(0 to quit)" << endl;
					cout << "1.Inquire    2.Recharge    3.Take a bus" << endl;
					cin >> temp3;
					if(temp3 == "1")
					{
						C.Show_Card();
					}
					else if(temp3 == "2")
					{
						int money;
						cout << "How much money you wish to recharge?" << endl;
						cin >> money;
						//C.Recharge(money);
						if(check == 1) {Teacher[j].Recharge(money); C = Teacher[j];}
						if(check == 2) {Student[j].Recharge(money); C = Student[j];}
						if(check == 3) {Restrict[j].Recharge(money); C = Restrict[j];}
						if(check == 4)
						{
							if(Temperory[j].IsFrozen(year, month, day))
							{
								cout << "Your card has been frozen!" << endl;
								Temperory[j].Thaw(year, month, day);
								C = Temperory[j];
								continue;
							}
							else
								{Temperory[j].Recharge(money); C = Temperory[j];}
						}
						cout << "Done!" << endl;
					}
					else if(temp3 == "3")
					{
						if(check == 1) {Teacher[j].Fee_Deduction(); C = Teacher[j];}
						if(check == 2) {Student[j].Fee_Deduction(); C = Student[j];}
						if(check == 3) {Restrict[j].Fee_Deduction(); C = Restrict[j];}
						if(check == 4)
						{
							if(Temperory[j].IsFrozen(year, month, day))
							{
								cout << "Your card has been frozen!" << endl; 
								Temperory[j].Thaw(year, month, day);
								C = Temperory[j];
								continue;
							}
							else
								{Temperory[j].Fee_Deduction(); C = Temperory[j];}
						}												
					}
					else
					{
						cout << "Bye!" << endl;
						break;
					}
				}
			}

			else if(temp2 == "3")
			{
				int i, j;
				int ID;
				cout << "Please enter your card ID: " << endl;
				cin >> ID;
				int check = 0;
				for(i = 0; i < N; i++)
				{
					if(Teacher[i].Check_ID(ID))
						{C = Teacher[i]; check = 1; j = i;}
					if(Student[i].Check_ID(ID))
						{C = Student[i]; check = 2; j = i;}
					if(Restrict[i].Check_ID(ID))
						{C = Restrict[i]; check = 3; j = i;}
					if(Temperory[i].Check_ID(ID))
						if(Temperory[j].IsFrozen(year, month, day))
						{
							cout << "Your card has been frozen!" << endl; 
							Temperory[j].Thaw(year, month, day);
							C = Temperory[j];
							break;
						}
						else
							{C = Temperory[i]; check = 4; j = i;}
				}
				if(!check)
					break;
				if(C.Get_Extra_Money())
				{
					cout << "You have " << C.Get_Extra_Money() << "Yuan left, "
					     << "Are you sure to sign out you card?(Y to continue)" << endl;
					string temp;
					cin >> temp;
					if(temp != "Y")
						break;
				}
				C.Destroy();
				if(check == 1) Teacher[j].Destroy();
				if(check == 2) Student[j].Destroy();
				if(check == 3) Restrict[j].Destroy();
				if(check == 4) Temperory[j].Destroy();
				cout << "Your card has already been signed out!" << endl;
			}
		}

		else if(temp1 == "2")
		{
			int i = 0;
			cout << "Create a new bus    2.Log in an old bus(0 to back)" << endl;
			cin >> temp2;
			if(temp2 == "1")
			{
				B.Start_Bus();
				bus[bus_num] = B;
			}
			if(temp2 == "2")
			{
				string license;
				cout << "Please enter the bus license number: (0 to quit)";
				cin >> license;
				if(license == "0")
					break;
				cout << "Hello, this is Bus " << license 
					 << ", What do you want to do?" << endl;
				while(1)
				{					
					int check = 0;					
					for(i = 0; i < M; i++)
						if(bus[i].IsLicense(license))
						{
							B = bus[i];
							check = 1;
						}
					if(check == 0)
					{
						cout << "Not found!" << endl;
						break;
					}
					if(check == 1)
					{

						cout << "1.Show timetable    2.Record real time    3.Record passengers"
						     << "    4.Running information    5.Randomly passengers" << endl;
						cin >> temp3;
						if(temp3 == "1")
							B.Show_Timeable();
						else if(temp3 == "2")
							B.Record_Real_Time();
						else if(temp3 == "3")
						{
							for(i = 0; i < B.Get_Stop_Num(); i++)
							{
								cout << "Stop " << i + 1 << ": " << endl;
								cout << "How many passengers get on the bus and get out of the bus: ";
								cin >> n1[i] >> n2[i];
								B.Get_On_Bus(n1[i]-n2[i]);
								B.IsMaxPassenger();
								cout << "Done!" << endl;
								continue;
							}
						}
						else if(temp3 == "4")
						{
							double proportion, start_rate;
							B.Get_Runing_Info(proportion, start_rate, n1, n2);
							//cout << "Proportion of passengers: " << proportion << endl;
							cout << "The rate arriving on time: " << start_rate << endl;
						}
						else if(temp3 == "5")
							B.Random_Passengers();
						else
							break;
					}
				}
			}
		}

		else if(temp1 == "3")
		{
			All_To_Csv();
			All_To_Csv2();
			cout << "Enter the date today: ";
			//int year = 0, month = 0, day = 0;
			cin >> year >> month >> day;
			while(month < 1 || month > 12 || day < 1 || day > 30)
				cin >> year >> month >> day;			
		}

		else if(temp1 == "0")
			break;
		else
		{
			cout << "Wrong input, please enter again." << endl;
			continue;
		}
	}
}