#include<iostream>
#include<string.h>
using namespace std;
#define MAX 3

class Employee
{
  int id;
  char name[20];
  int salary;
  static int count;
  public:
  	void Add_employee(int id,char *name,int salary)
  	{
  		this->id=id;
  		strcpy(this->name,name);
  		this->salary=salary;
  		count++;
  	}
  	void Display_employee()
  	{
  		cout<<" "<<this->id<<"\t"<<this->name<<"\t"<<this->salary<<endl;
  	}
  	void Search_employee(Employee E[]);
  	void Srt_employee(Employee E[]);
  	 void Delete_employee(Employee E[]);
};
int Employee::count=0;
void Employee::Search_employee(Employee E[])
{
	int id;
	char name[20];
	int salary;
	int choice=0;
		cout<<"========Menu for searching========"<<endl;
		cout<<"1 .By id\t 2.By name \t 3. By slary"<<endl;
		cout<<"Enter your choice"<<endl;
		cin>>choice;
		switch(choice)
		{
		case 1:
		 cout<<"Enter the id for searching employee : ";
   	     cin>>id;
   	     for(int i=0;i<count;i++)
   	     {
   	     	if(E[i].id==id)
   	     	{
   	     		E[i].Display_employee();
   	     		break;
   	     	}
   	     }
		break;
		case 2:
		 cout<<"Enter the name for searching employee : ";
   	     cin>>name;
   	      for(int i=0;i<count;i++)
   	     {
   	     	int che=strcmp(E[i].name,name);
   	     	if(!che)
   	     	{
   	     		E[i].Display_employee();
   	     		break;
   	     	}
   	     }
		break;
		case 3:
		 cout<<"Enter the salary for searching employee : ";
   	     cin>>salary;
   	      for(int i=0;i<count;i++)
   	     {
   	     	if(E[i].salary==salary)
   	     	{
   	     		E[i].Display_employee();
   	     		break;
   	     	}
   	     }
		 break;
		}
}
void Employee::Srt_employee(Employee E[])
{
	cout<<"========Menu for sorting========="<<endl;
	cout<<" 1.By id\t2.By name \t3 By salary"<<endl;
	cout<<"Enter your choice for sorting data : ";
	int choice=0;
	cin>>choice;
	switch(choice)
	{
		case 1:
		    for(int i=0;i<count;i++)
		    {
              for(int j=0;j<count-i-1;j++) 
            {
               if(E[j].id>E[j+1].id)
               {
               	Employee temp=E[j];
               	E[j]=E[j+1];
                E[j+1]=temp;
               }
             } 
     		}
		break;
		case 2:
		for(int i=0;i<count;i++)
		    {
              for(int j=0;j<count-1-i;j++) 
            {
               if(strcmp(E[j].name,E[j+1].name)>0)
               {
               	Employee temp=E[j];
               	E[j]=E[j+1];
                E[j+1]=temp;
            }
            }
        }
		break;
		case 3:
				for(int i=0;i<count;i++)
		    {
              for(int j=0;j<count-i-1;j++) 
            {
               if(E[j].salary>E[j+1].salary)
               {
               	Employee temp=E[j];
               	E[j]=E[j+1];
                E[j+1]=temp;
            }
            }
        }
		break;
	}

}
void Employee::Delete_employee(Employee E[])
{
	int id,salary;
	char name[20];
	cout<<"========Menu for deleting========"<<endl;
	cout<<" 1.By id\t2.By name \t3 By salary"<<endl;
	cout<<"Enter your choice for sorting data"<<endl;
	int choice=0;
	cin>>choice;
	switch(choice)
	{
		case 1:
		cout<<"Enter id for delete object\n";
		cin>>id;
		for(int i=0;i<count;i++)

		{
			if(E[i].id==id)
			{
				for(int j=i+1;j<count;j++)
				{
                  E[j-1]=E[j];
				}
				count--;
				break;
			}
		}
		break;
		case 2:
		cout<<"Enter name for delete object\n";
		cin>>name;
		for(int i=0;i<count;i++)

		{
			if(!strcmp(E[i].name,name))
			{
				for(int j=i+1;j<count;j++)
				{
                  E[j-1]=E[j];
				}
				count--;
				break;
			}
		}
		break;
		case 3:
		cout<<"Enter salary for delete object\n";
		cin>>salary;
		for(int i=0;i<count;i++)

		{
			if(E[i].salary==salary)
			{
				for(int j=i+1;j<count;j++)
				{
                  E[j-1]=E[j];
				}
				count--;
				break;
			}
		}
		break;
	}
}
int main()
{
	Employee E[MAX];
	int id,salary,choice=0,size,flag=0;
	char name[20];
    cout<<"Enter the total number of object : ";
    cin>>size;
   while(choice<9)
   {
   	cout<<"=========Menu in main function=========\n";
   	cout<<" 1 Add an employee 2.Display all employee 3.Search an employee \n" 
   	" 4.Sort the Employee 5.Delete the employee 6.Add a unoque function\n";
   	cout<<"Enter your choice in main function \n";
   	cin>>choice;
   	switch(choice)
   	{
   		case 1:
   		for(int i=0;i<size;i++)
   		{
         cout<<"Enter the id of employee "<<i+1<<" : ";
     	 cin>>id;
         cout<<"Enter the name of employee "<<i+1<<" : ";
   	     cin>>name;//cin.getline(name,19);
   	     cout<<"Enter the salary of employee "<<i+1<<" : ";
   	     cin>>salary;
         E[i].Add_employee(id,name,salary);
         }
         flag=1;
   		break;
   		case 2:
   		      if(!flag)
   		      {
   		       cout<<" No employee added\n" ;  
   		      }
   		      else
   		      {
   		         cout<<"Display all employee\n Id\tName\tSalary\n";
   		         for(int i=0;i<size;i++)
	            { 
		          E[i].Display_employee();
	            } 
   		      }
   		break;
   		case 3:
          Search_employee(E);
   		break;
   		 case 4:
   		   	Srt_employee(E);
   		 break;
   		  case 5:
   		  Delete_employee(E);
   	}
   }
		
	
	return 0;
}