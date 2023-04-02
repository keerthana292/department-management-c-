#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<windows.h>
#include<unistd.h>
using namespace std;

class Department{
    private:
        // Variables for employee details
        char name[30];
        char id[5];
        char deloc[10];
        int age;
        int experience;

        // Utility functions
        void waitForEnter(void){
            cout<<"\n\n\n Press enter to go back \n\n";
            cin.get();
            cin.get();
        }

        // Functions to perform desired actions
        void listDepartment(void){ //To list total employees with Name, Id and Designation
            system("cls");
            FILE *file;
            file= fopen("data.txt", "r");
            cout<<"\n\t      List of Department\n";
            cout<<"\n NAME        |     ID     |     DELOC\n";
            while(fscanf(file, "%s %s %s %d %d", &name[0], &id[0] , &deloc[0],&age, &experience)!= EOF)
                cout<<"\n"<<name<<"\t\t"<<id<<"\t\t"<<deloc;
            fclose(file);
            waitForEnter();
        }

        void showDetails(void){ //Displays all details according to Employee's id
            system("cls");
            FILE *file;
            char checkId[5];
            cout<<"\n\nEnter Department ID: ";
            cin>>checkId;
            file= fopen("data.txt", "r");
            while(fscanf(file, "%s %s %s %d %d", &name[0], &id[0] , &deloc[0], &age, &experience)!=EOF)
                if(strcmp(checkId,id)==0){
                	cout<<"\n---------------------";
                    cout<<"\nName: "<<name;
                    cout<<"\n---------------------";
                    cout<<"\nId: "<<id;
                    cout<<"\n---------------------";
                    cout<<"\ndeloc: "<<deloc;
                    cout<<"\n---------------------";
                    cout<<"\nAge: "<<age;
                    cout<<"\n---------------------";
                    cout<<"\nExperience: "<<experience;
                    cout<<"\n---------------------";
                }
            fclose(file);
            waitForEnter();
        }

        void editExisting(void){ //edits deloc of an dept
            system("cls");
            char checkId[5];
            cout<<"\nEnterDepartment id: ";
            cin>>checkId;
            char newdeloc;
            cout<<"\n-----------------------------";
            cout<<"\nEnter new deloc: ";
            cin>>newdeloc;
            FILE *file, *tempfile;
            file= fopen("data.txt", "r");
            tempfile= fopen("temp.txt", "w");
            while(fscanf(file, "%s %s %s %d %d", &name[0], &id[0] , &deloc[0], &age, &experience)!=EOF){
                if(strcmp(checkId, id)==0)
                    fprintf(tempfile, "%s %s %s %d %d \n", name, id, newdeloc, age, experience );
                else
                    fprintf(tempfile, "%s %s %s %d %d \n", name, id, deloc, age, experience );
            }
            fclose(file);
            fclose(tempfile);
            int isRemoved= remove("data.txt");
            int isRenamed= rename("temp.txt", "data.txt");
            waitForEnter();
        }

        void addNewDepartment(void){ //adding records
            system("cls");
            cout<<"\n Enter Name : ";
            cin>>name;
            cout<<"\n Enter Department ID [max 4 digits]: ";
            cin>>id;
            cout<<"\n Enter deloc: ";
            cin>>deloc;
            cout<<"\n Enter Age: ";
            cin>>age;
            cout<<"\n Enter Experience: ";
            cin>>experience;
            cout<<"\n----------------------------------------";

            char ch;
            cout<<"\nEnter 'y' to save above information\n";
            cin>>ch;
            if(ch=='y'){
                FILE  *file;
                file= fopen("data.txt","a");
                fprintf(file, "%s %s %s  %d %d \n", name, id, deloc , age,experience );
                fclose(file);
                cout<<"\nNew Department has been added to database\n";
            }
            else
                addNewDepartment();
            waitForEnter();
        }

        void deleteDepartmentDetails(void){ //removing records
            system("cls");
            char checkId[5];
            cout<<"\n----------------------------------";
            cout<<"\nEnter department Id To Remove: ";
            cin>>checkId;
            char ch;
            cout<<"----------------------------------";
            cout<<"\n\n\n\n\nCONFIRMATION\nEnter 'y' To Confirm Deletion \n";
            cin>>ch;
            if(ch=='y'){
                FILE *file, *tempfile;
                file= fopen("data.txt", "r");
                tempfile= fopen("temp.txt", "w");
                while(fscanf(file, "%s %s %s %d %d", &name[0], &id[0] , &deloc[0], &age, &experience)!=EOF)
                    if(strcmp(checkId, id)!=0)
                        fprintf(tempfile, "%s %s %s %d %d \n", name, id, deloc, age, experience );
                fclose(file);
                fclose(tempfile);
                int isRemoved= remove("data.txt");
                int isRenamed= rename("temp.txt", "data.txt");
                cout<<"\nRemoved Successfully\n";
                waitForEnter();
            }
            else
                deleteDepartmentDetails();
        }


    public:
        // Function to serve as end point
        void options(void){ //menu
        int login(); //login declaration
                login();//login screen
            while(true){
                system("cls");
                
                // Options to choose an action
                cout<<"\n\t\t\t>>>> DEPARTMENT MANAGEMENT SYSTEM<<<<";
                cout<<"\n";
                cout<<"\n\t   1:   display  List ";
                cout<<"\n\t   2:   display individual Details";
                cout<<"\n\t   3:   edit Details";
                cout<<"\n\t   4:   To Add New dept Details";
                cout<<"\n\t   5:   To Remove an dept Details";
                cout<<"\n\t   0:   To Exit     ";
                cout<<"\n\n\t\t\t   Please Enter Your Choice: ";

                // Taking the action input
                int ch;
                cin>>ch;
                // Calling relevant function as per choice
                switch (ch) {
                    case 0:
                    	system("CLS");
                        cout<<"\n\nDEPARTMENT MANAGEMENT SYSTEM \n\n Brought To You By code-projects.org\n\n ";
                        Sleep(10);
                        return;
                    case 1:
                        listDepartment();
                        break;
                    case 2:
                        showDetails();
                        break;
                    case 3:
                        editExisting();
                        break;
                    case 4:
                        addNewDepartment();
                        break;
                    case 5:
                        deleteDepartmentDetails();
                        break;
                    default:
                        cout<<"\n Sorry! I don't understand that! \n";
                        break;
                }

            }
        }

};

int main(){
    // Call the options function
    Department dept;
    dept.options();
    return 0;
}

int login(){ //login procedure
   string pass ="";
   char ch;
   cout <<"\n\n\n\n\t\t\t\t\tEMPLOYEE MANAGEMENT SYSTEM";
   cout <<"\n\n\n\n\n\t\t\t\t\tEnter Your Password :";
   ch = _getch();
   while(ch != 13){//character 13 is enter
      pass.push_back(ch);
      cout << '*';
      ch = _getch();
   }
   if(pass == "admin")
   {
   	cout<<"\n\n\n\t\t\t\t\tLOADING \n\t\t\t\t\t";
   	for(int a=1;a<8;a++) // Change 'a<?' to how many * you want
	{
		Sleep(100);
		cout << "...";
	}
      cout << "\n\n\n\t\t\t\t\tAccess Granted!! \n\n\n";
      
      system("PAUSE");
      system("CLS");
   }else{
      cout << "\nAccess Aborted...\n";
      login();
   }
}

