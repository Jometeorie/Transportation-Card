/*
	该文件实现向四种学生卡所存储的.csv文件中存储数据和读取数据的手段
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "trans_card.h"
#define N 100
 
using namespace std;

extern Student_Card Student[N];
extern Teacher_Card Teacher[N];
extern Restrict_Card Restrict[N];
extern Temperory_Card Temperory[N];
// extern Bus bus[N];
 
string charToStr(char * contentChar)
{
	string tempStr;
	for(int i = 0; contentChar[i] != '\0'; i++)
	{
		tempStr += contentChar[i];
	}
	return tempStr;
}

void Change_Value(string file, int lineNum, int rowNum, string content)
{
	ifstream in;
	char line[1000] = {'\0'};
	in.open(file);	
	int i = 0;
	string tempStr;
	while(in.getline(line, sizeof(line)))
	{
		i++;
		if(lineNum != i)
		{
			tempStr += charToStr(line);
		}
		else
		{
			int flag = 1;
			int temp1 = 0;
			int temp2 = 0;
			int len;
			char s1[1000] = {'\0'};
			char s2[1000] = {'\0'};
			for(len = 0; line[len] != '\0'; len++);
			for(int j = 0; line[j] != '\0'; j ++)
			{
				if(line[j] == ',')
				{
					flag++;
					if(flag == rowNum)
						temp1 = j;
					if(flag == rowNum + 1)
						temp2 = j;
				}
			}
			for(int j = 0; j <= temp1; j++)
				s1[j] = line[j];
			for(int j = temp2; j < len; j++)
				s2[j-temp2] = line[j];
			tempStr += charToStr(s1) + content + charToStr(s2);
			cout << tempStr;
		}
		tempStr += '\n';
	}
	in.close();
	ofstream out;
	out.open(file);
	out.flush();
	out << tempStr;
	out.close();
}

string Get_Value(string file, int lineNum, int rowNum)
{
	ifstream in;
	char line[1000] = {'\0'};
	in.open(file);	
	int i = 0;
	while(in.getline(line, sizeof(line)))
	{
		i++;
		if(lineNum == i)
		{
			int flag = 1;
			int temp1 = 0;
			int temp2 = 0;
			int len;
			char s[1000] = {'\0'};
			for(len = 0; line[len] != '\0'; len++);
			for(int j = 0; line[j] != '\0'; j ++)
			{
				if(line[j] == ',')
				{
					flag++;
					if(flag == rowNum)
						temp1 = j;
					if(flag == rowNum + 1)
						temp2 = j;
				}
			}
			for(int j = temp1 + 1; j < temp2; j++)
				s[j-temp1-1] = line[j];
			in.close();
			return charToStr(s);
		}
	}
}

template <typename T>
void Load_One_Line(T & C, string file, int line)
{
	C.card_id = stoi(Get_Value(file, line, 2));
	C.Owner.name = Get_Value(file, line, 3);
	C.Owner.profession = Get_Value(file, line, 4);
	C.Owner.work_place = Get_Value(file, line, 5);
	C.Owner.sex = Get_Value(file, line, 6);
	C.Owner.salary = stoi(Get_Value(file, line, 7));
	C.times_per_mon = stoi(Get_Value(file, line, 8));
	C.times = stoi(Get_Value(file, line, 9));
	C.extra_money = stoi(Get_Value(file, line, 10));
	C.valid_year = stoi(Get_Value(file, line, 11));
	C.valid_month = stoi(Get_Value(file, line, 12));
	C.valid_day = stoi(Get_Value(file, line, 13));
	// cout << C.Owner.name << endl;
};

void Load()
{
	ifstream in;
	int total_line = 0;
	in.open("Teacher_Card.csv");
	char line1[1000] = {'\0'};	
	int i = 2;
	while(in.getline(line1, sizeof(line1)))
		total_line++;
	while(i <= total_line)
	{
		Load_One_Line(Teacher[i-2], "Teacher_Card.csv", i);
		i++;
	}
	in.close();

	in.open("Student_Card.csv");
	char line2[1000] = {'\0'};	
	i = 2;
	total_line = 0;
	while(in.getline(line2, sizeof(line2)))
		total_line++;
	while(i <= total_line)
	{
		Load_One_Line(Student[i-2], "Student_Card.csv", i);
		i++;
	}
	in.close();

	in.open("Restrict_Card.csv");
	char line3[1000] = {'\0'};	
	i = 2;
	total_line = 0;
	while(in.getline(line3, sizeof(line3)))
		total_line++;
	while(i <= total_line)
	{
		Load_One_Line(Restrict[i-2], "Restrict_Card.csv", i);
		i++;
	}
	in.close();

	in.open("Temperory_Card.csv");
	char line4[1000] = {'\0'};	
	i = 2;
	total_line = 0;
	while(in.getline(line4, sizeof(line4)))
		total_line++;
	while(i <= total_line)
	{
		Load_One_Line(Temperory[i-2], "Temperory_Card.csv", i);
		i++;
	}
	in.close();
}

void Write_Head(string file)
{
	ifstream inFile(file, ios::out);
	fstream outFile;
	outFile.open(file, ios::out);

	outFile << "Num" << ','
			<< "Card ID" << ','
			<< "Name" << ','
			<< "Profession" << ','
			<< "Work Place" << ','
			<< "Sex" << ','
			<< "Salary" << ','
			<< "Times Per Month" << ','
			<< "Times" << ','
			<< "Extra Money" << ','
			<< "Valid Year" << ','
			<< "Valid Month" << ','
			<< "Valid Day" << ','
			<< endl;
	outFile.close();
}

void All_To_Csv()
{
	Write_Head("Teacher_Card.csv");
	Write_Head("Student_Card.csv");
	Write_Head("Restrict_Card.csv");
	Write_Head("Temperory_Card.csv");

	for(int i = 0; i < N; i++)
	{
		if(Teacher[i].Get_Owner_Name().size())
			Teacher[i].Write_To_CSV("Teacher_Card.csv");
		if(Student[i].Get_Owner_Name().size())
			Student[i].Write_To_CSV("Student_Card.csv");
		if(Restrict[i].Get_Owner_Name().size())
			Restrict[i].Write_To_CSV("Restrict_Card.csv");
		if(Temperory[i].Get_Owner_Name().size())
			Temperory[i].Write_To_CSV("Temperory_Card.csv");
	}
}