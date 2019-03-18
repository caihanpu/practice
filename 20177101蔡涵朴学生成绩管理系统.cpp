// StudentGradeSystem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "malloc.h"
#include <iostream>
#include <fstream>
 
using namespace std;


typedef struct Course{
 
	char name_c[12];
	float grade;
}Course;//定义课程

typedef struct Student{
 
	char name_s[12];
	int sno;
	Course cou[3];
}Student;//学生信息

//输入学生信息的函数
void InputStudentInformation( Student * &Stu,int num){//num为学生数量,返回一个学生数组首地址
        Stu=new Student[num];
		for(int i=0;i<num;i++)
		{
			cout<<"Please imput The student "<<i+1<<" 's name and number"<<endl;
		    cin>>Stu[i].name_s>>Stu[i].sno;
			for(int j=0;j<3;j++)
			{
				cout<<"Please imput The student "<<i+1<<" 's course "<<j+1<<" 's grade"<<endl;
				cin>>Stu[i].cou[j].grade;
				if(j==0) 
					strcpy(Stu[i].cou[j].name_c,"Chinese");
				else if(j==1)
					strcpy(Stu[i].cou[j].name_c,"Math");
				else if(j==2)
					strcpy(Stu[i].cou[j].name_c,"English");

			}
		}
	
 }

 //输出学生情况
 void Print(Student * stu)
 {
	 Student *p=stu;
	  if(!p)//如果数组为空
	 {
		 cout<<"error"<<endl;
         return;
	 }
	 
	 cout<<"\t学生\t学号\t语文成绩\t数学成绩\t英语成绩"<<endl;
	 for(;p;p++)
	 {
		 cout<<"\t"<<p->name_s<<"\t"<<p->sno;
			 for(int i=0;i<3;i++)
				 cout<<"\t"<<p->cou[i].grade;
	     cout<<endl;
		 
	 }
 }


 //计算某科目平均分
 int CountAverage(Student * stu,int nameofcourse)
 {
     Student *p=stu;
	 if(!p)//如果数组为空
	 {
		 cout<<"error"<<endl;
         return 0;
	 }
	 int ave=0;
	 for(;p;p++)
		 ave+=p->cou[nameofcourse].grade;
	
	 cout<<"The average grade is "<<ave<<endl;
	  return ave;
 }

 //快速排序算法
  void Inorder(Student * stu,int nameofcourse,int low,int high)
  {
	 if(!stu)//如果数组为空
	 {
		 cout<<"error"<<endl;
         return ;
	 }
	 int first=low;
	 int last=high;
	 int key=stu[first].cou[nameofcourse].grade;
	  
	 while(first<last)
	 {
		 while(first<last&&stu[last].cou[nameofcourse].grade>=key)
			 last--;
		 stu[last].cou[nameofcourse].grade=stu[first].cou[nameofcourse].grade;
		 while(first<last&&stu[first].cou[nameofcourse].grade<=key)
			 first++;
		 stu[first].cou[nameofcourse].grade=stu[last].cou[nameofcourse].grade;
		 
	   
	 }
     stu[first].cou[nameofcourse].grade = key;//枢轴记录到位
     Inorder(stu,nameofcourse,low, first-1);
     Inorder(stu,nameofcourse,first+1, high);
    
  }

  //存入文件
void Save(Student *stu,char* pathName)//创建txt文件
{
 ofstream fout(pathName);
 if (fout)  // 如果创建成功
	 {
	     fout<<"\t学生\t学号\t语文成绩\t数学成绩\t英语成绩"<<endl;
         for (Student *p=stu;p;p++)
		 {
             fout<<"\t"<<p->name_s<<"\t"<<p->sno;
			 for(int j=0;j<3;j++)
				 fout<<"\t"<<p->cou[j].grade;
	     fout<<endl;
		 }
  
       fout.close();  // 执行完操作后关闭文件句柄
	 }
 
}

 
 
//打印界面
void ShowTheScreen()
{
    int order=0;
	int number_of_students=0;
	static Student * students;//全局变量，储存学生信息的数组
	int numberofcourse=0;
    char * Pathname=new char[20];


    printf("\nWelcome to the StudentGradeSystem\n");
	printf("1.Input              2.Count average\n");
    printf("3.Inorder             4.Save\n");
	printf("input your order\n");
	cin>>order;
	while(!(order>=1&&order<=4))
	{ 
	     printf("data error!\n");
		 cin>>order;
	
	}
	switch(order)
	{
	    case(1):
			cout<<"How many students you want to record?"<<endl;
			cin>>number_of_students;
			InputStudentInformation(students,number_of_students);
			//Print(students);
			break;
		case(2):
			cout<<"Which average grade of course you want to count?"<<endl;
            cout<<"1.Chinese"<<endl<<"2.Math"<<endl<<"3.English"<<endl;
			cout<<"choose the number"<<endl;
			cin>>numberofcourse;
			CountAverage(students,numberofcourse);

			break;
		case(3):
			cout<<"Which average grade of course you want to inorder?"<<endl;
            cout<<"1.Chinese"<<endl<<"2.Math"<<endl<<"3.English"<<endl;
			cout<<"choose the number"<<endl;
			cin>>numberofcourse;
			Inorder(students,numberofcourse,0,number_of_students-1);
			cout<<students;
			break;
		case(4):
			cout<<"input the path you want"<<endl;
			cin>>Pathname;
			Save(students,Pathname);
			break;
	}

         
}

 //主函数，打印主界面
int main(int argc, char* argv[])
{   while(1)
	ShowTheScreen();
	return 0;
}
