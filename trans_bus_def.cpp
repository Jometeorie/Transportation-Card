/*
	该文件定义了与班车功能相关的函数的实现
*/
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "trans_card.h"
#define M 100

using namespace std;

extern int bus_num;
extern Bus bus[M];

// The information of buses

Bus::Bus()
{}

void Bus::Start_Bus()
{
	cout << "License number: ";
	cin >> license_number;
	cout << "Type: ";
	cin >> type;
	cout << "The maximum of passengers: ";
	cin >> max_passenger;
	passenger_num = 0;
	cout << "Drive's name: ";
  	cin >> driver_name;
	cout << "Times that suppose to run in a day: ";
	cin >> times;
	cout << "Number bus stops: ";
	cin >> stop_num;
	bustime.arrive_time = new Time[times];
	bustime.leave_time = new Time[times];
	real_bustime.arrive_time = new Time[times];
	real_bustime.leave_time = new Time[times];
	for(int i = 0; i < times; i++)
	{
	   	cout << "arriving Time " << i + 1 << ": (hour and minute)";
	   	cin >> bustime.arrive_time[i].hour >> bustime.arrive_time[i].minute;
	   	cout << "leaving Time " << i + 1 << ": (hour and minute)";
	   	cin >> bustime.leave_time[i].hour >> bustime.leave_time[i].minute;
	}
	bus_num++;
}

int Bus::IsMaxPassenger()
{
	if(passenger_num > max_passenger)
	{
		cout << "The maximum number of the bus is reached, please take the next bus." << endl;
		return 1;
	}
	else
		return 0;
}

void Bus::Record_Real_Time()
{
	for(int i = 0; i < times; i++)
	{
		cout << "Enter the real time arriving at time " << i + 1 << ": ";
		cin >> real_bustime.arrive_time[i].hour;
		cin >> real_bustime.arrive_time[i].minute;
		cout << "Enter the real time leaving time " << i + 1 << ": ";
		cin >> real_bustime.leave_time[i].hour;
		cin >> real_bustime.leave_time[i].minute;
	}
}

void Bus::Show_Timeable()
{
	cout << "Bus ID: " << license_number << endl;
	for(int i = 0; i < times; i++)
	{
		cout << "Time " << i + 1 << ": " << endl;
		cout << "arriving at " << bustime.arrive_time[i].hour << ": " 
		     << bustime.arrive_time[i].minute << endl;
		cout << "leaving at " << bustime.leave_time[i].hour << ": " 
		     << bustime.leave_time[i].minute << endl;
		cout << endl;
	}
}

void Bus::Get_Runing_Info(double & proportion, double & start_rate, int *n1, int *n2)
{
	int sum = 0, temp = 0;
	for(int i = 0; i < times; i++)
	{
		sum += (n1[i] - n2[i]);
		if(bustime.leave_time[i].hour * 60 + bustime.leave_time[i].minute
		   >= real_bustime.leave_time[i].hour * 60 + real_bustime.leave_time[i].minute)
			temp++;
	}
	proportion = (double)sum / (double)(times * max_passenger);
	start_rate = (double)temp / (double)times;
}

void Bus::Get_Arr_Rate(double & arr_rate)
{
	int temp = 0;
	for(int i = 0; i < times; i++)
	{
		if(bustime.arrive_time[i].hour * 60 + bustime.arrive_time[i].minute
		   >= real_bustime.arrive_time[i].hour * 60 + real_bustime.arrive_time[i].minute)
			temp++;
	}
	arr_rate = (double)temp / (double)times;
}

void Bus::Get_On_Bus(int n)
{
	passenger_num += n;
	if(IsMaxPassenger())
	{
		passenger_num = max_passenger;
	}
}

void Bus::Write_To_CSV2(string file)
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
			<< license_number << ','
			<< type << ','
			<< max_passenger << ','
			<< driver_name << ','
			<< times << ','
			<< stop_num << ',';
	for(int i = 0; i < times; i++)
	{
		outFile << bustime.arrive_time[i].hour << ','
				<< bustime.arrive_time[i].minute << ','
				<< bustime.leave_time[i].hour << ','
				<< bustime.leave_time[i].minute << ',';
	}
	outFile << endl;

	outFile.close();	
}

void Bus::Random_Passengers()
{
	srand((int)time(NULL));
	passenger_num = 0;
	int get_on_bus = 0, get_off_bus = 0;
	for(int i = 0; i < stop_num; i++)
	{
		get_on_bus = rand() % (max_passenger - passenger_num + 1);
		get_off_bus = rand() % (passenger_num + 1);
		if(i == stop_num-1)
		{
			get_on_bus = 0;
			get_off_bus = passenger_num;
		}
		passenger_num = passenger_num + get_on_bus - get_off_bus;
		cout << "Stop " << i+1 << ": ";
		if(get_on_bus > 1)
			cout << get_on_bus << " passengers get on the bus and ";
		else
			cout << get_on_bus << " passenger gets on the bus and ";
		if(get_off_bus > 1)
			cout << get_off_bus << " passengers get off the bus. ";
		else
			cout << get_off_bus << " passenger gets off the bus. ";
		cout << endl;
		if(passenger_num > 1)
			cout << "        Now there are " << passenger_num << " passengers on the bus" << endl;
		else
			cout << "        Now there is " << passenger_num << " passenger on the bus" << endl;
		cout << "        Proportion of passengers: ";
		cout << (double)passenger_num / (double)max_passenger << endl;
	}
}