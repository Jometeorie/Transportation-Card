/*
	该文件为一卡通系统的头文件，声明了包括一卡通和班车在内的
	所有函数。
*/
#include <iostream>
#include <string>
#ifndef TRANS_CARD_H_
#define TRANS_CARD_H_

using namespace std;

void start();

// The person who can hold the card
typedef struct Person
{
	string name;
	string profession;
	string work_place;
	string sex;
	int salary;
} Person;

typedef struct Time
{
	int hour;
	int minute;
} Time;

typedef struct Timetable
{
	//Time start_time;
	//Time end_time;
	Time *arrive_time;
	Time *leave_time;
	//int running_hour;
	//int running_minute;	//Overall running time
} Timetable;	//Schedule of buses

// Transportation Card: Base Class
class Card
{
protected:
	Person Owner; // The infornmation of the card's owner
	int card_id; // The id of the card
	int times; // Times that using this card
	int times_per_mon; // Times that using this card per month
	int cost; // Money required for each ride
	int extra_money; // Money rest in the card
	int valid_year, valid_month, valid_day;
	bool Frozen;
	template <typename T>
	friend void Load_One_Line(T & C, string file, int line);
public:
	Card();
	//Card(int year, int month, int day);
	virtual void Start(int year, int month, int day) {};
	Person Get_Owner_Infornmation() const { return Owner; };
	string Get_Owner_Name() const { return Owner.name; }
	int Get_Card_ID() const { return card_id; }
	int Get_Using_Times() const { return times; }
	int Get_Times_Per_Month() const { return times_per_mon; }
	int Get_Cost() const { return cost; }
	int Get_Extra_Money() const { return extra_money; }
	void Get_Vaild_Info(int & y, int & m, int & d) const;
	void Recharge(int n) { extra_money += n; }
	virtual bool Check_Money() const; // If extra money < 5 or extra money < 2, write some information
	bool Check_Valid_Date(int y, int m, int d) const;
	virtual void Show_Card() const;
	virtual void Fee_Deduction();
	void Check_Times();
	virtual ~Card() {}
	bool Check_ID(int ID) { return (ID == card_id); }
	virtual void Destroy();
	void Write_To_CSV(string file);
};

// Teacher's Card Class
class Teacher_Card : public Card
{
public:
	Teacher_Card() { card_id = 0; }
	virtual void Start(int year, int month, int day);
	virtual void Destroy();
};

// Student's Card Class
class Student_Card : public Card
{
private:
	string stu_id;
public:
	Student_Card() { card_id = 0; }
	virtual void Start(int year, int month, int day);
	virtual void Destroy();
};

// Restriction Card Class
class Restrict_Card : public Card
{
public:
	Restrict_Card() { card_id = 0; }
	virtual void Start(int year, int month, int day);
	virtual void Fee_Deduction();
	virtual void Show_Card() const;
	void Check_Times();
	virtual void Destroy();
};

// Temperory Card Class
class Temperory_Card : public Card
{
// private:
// 	bool Frozen;
public:
	Temperory_Card() { card_id = 0; }
	virtual void Start(int year, int month, int day);
	virtual void Destroy();
	void Freeze() { Frozen = true; }	// Freeze the temperory card
	bool IsFrozen(int year, int month, int day);
	void Thaw(int year, int month, int day);	// Thaw the temperory card
};

// Bus Class
class Bus
{
private:
	string license_number;	// License plate number
	string type;	// Type of the bus
	int max_passenger;	// Upper limit of the passengers
	int passenger_num;	// Number of passengers in the bus
	string driver_name;
	Timetable bustime;
	Timetable real_bustime;
	int stop_num;	// Number of bus stops
public:
	int times;	// This times that the bus running in one day
	Bus();
	string Get_Bus_Lincense() { return license_number; }
	void Start_Bus();
	bool IsLicense(const string license) { return (license_number == license); }
	int Get_Stop_Num() { return stop_num; }
	int IsMaxPassenger();
	void Record_Real_Time();
	void Show_Timeable();
	void Get_Runing_Info(double & proportion, double & start_rate, int *n1, int *n2);	
		// proportion of people and the rate of bus running on time
	void Get_Arr_Rate(double & arr_rate);	// The rate of bus arriving on time
	void Get_On_Bus(int n);
	void Write_To_CSV2(string file);
	void Random_Passengers();
	friend void Load_One_Line2(Bus & C, string file, int line);
	virtual ~Bus()
	{
		delete []bustime.arrive_time;
		delete []bustime.leave_time;
		delete []real_bustime.arrive_time;
		delete []real_bustime.leave_time;
	}
};

// Operations upon csv file
void Change_Value(string file, int lineNum, int rowNum, string content);	// Change the value of line lineNum, rowRowNum
string Get_Value(string file, int lineNum, int rowNum);	// Get the value of line lineNum, row rowNum
void Load();	// Get all information from csv files of card
void All_To_Csv();	// Write all information to csv files of card
void Load2();	// Get all information from csv files of bus
void All_To_Csv2();	// Write all information to csv files of bus

#endif