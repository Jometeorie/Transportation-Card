/*
	该文件实现向班车信息所存储的.csv文件中存储数据和读取数据的手段
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "trans_card.h"
#define N 100
 
using namespace std;

extern Bus bus[N];

void Load_One_Line2(Bus & C, string file, int line)
{
	C.license_number = Get_Value(file, line, 2);
	C.type = Get_Value(file, line, 3);
	C.max_passenger = stoi(Get_Value(file, line, 4));
	C.driver_name = Get_Value(file, line, 5);
	C.times = stoi(Get_Value(file, line, 6));
	C.stop_num = stoi(Get_Value(file, line, 7));
	C.bustime.arrive_time = new Time[C.times];
	C.bustime.leave_time = new Time[C.times];
	C.real_bustime.arrive_time = new Time[C.times];
	C.real_bustime.leave_time = new Time[C.times];
	for(int i = 0; i < C.times; i++)
	{
		C.bustime.arrive_time[i].hour = stoi(Get_Value(file, line, 4*i+8));
		C.bustime.arrive_time[i].minute = stoi(Get_Value(file, line, 4*i+9));
		C.bustime.leave_time[i].hour = stoi(Get_Value(file, line, 4*i+10));
		C.bustime.leave_time[i].minute = stoi(Get_Value(file, line, 4*i+11));
	}
}

void Load2()
{
	ifstream in;
	int total_line = 0;
	in.open("Bus.csv");
	char line1[1000] = {'\0'};	
	int i = 2;
	while(in.getline(line1, sizeof(line1)))
		total_line++;
	while(i <= total_line)
	{
		Load_One_Line2(bus[i-2], "Bus.csv", i);
		i++;
	}
	//Load_One_Line2(bus[i-2], "Bus.csv", i);
	in.close();	
}

void Write_Head2(string file)
{
	ifstream inFile(file, ios::out);
	fstream outFile;
	outFile.open(file, ios::out);

	outFile << "Num" << ','
			<< "License Number" << ','
			<< "Type" << ','
			<< "Max Passengers" << ','
			<< "Driver Name" << ','
			<< "Running Times" << ','
			<< "Stop Number" << ','
			<< "Arr1(hour)" << ','
			<< "Arr1(min)" << ','
			<< "Leave1(hour)" << ','
			<< "Leave1(min)" << ','
			<< "Arr2(hour)" << ','
			<< "Arr2(min)" << ','
			<< "Leave2(hour)" << ','
			<< "Leave2(min)" << ','
			<< "Arr3(hour)" << ','
			<< "Arr3(min)" << ','
			<< "Leave3(hour)" << ','
			<< "Leave3(min)" << ','		
			<< endl;
	outFile.close();
}

void All_To_Csv2()
{
	Write_Head2("Bus.csv");
	for(int i = 0; i < N; i++)
		if(bus[i].Get_Bus_Lincense().size())
			bus[i].Write_To_CSV2("bus.csv");
}