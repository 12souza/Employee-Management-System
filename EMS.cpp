/*######################################################################################################################################################
  ######################################################################################################################################################
  ######################################################################################################################################################
  #############                                                                                                                                #########
  #############   This is an employee management system created by Mark Souza for for the Computer Science 115 on study.com                    #########
  #############   for the Computer Science 115 on study.com.  I can be reached at mrsouza12@hotmail.com if there are any concerns of this work #########
  #############   Login using the credentials listed in employees.txt..  This will have various roles where the employee will have menus that  #########
  #############   match specifications.  Here are some of the ID's and what they are for.. all the passwords are 'arkansas' for the sake of    #########
  #############   of the assignment:                                                                                                           #########
  #############                       Employee ID 23948 - HR Analyst                                                                           #########
  #############                       Employee ID 23542 - Manager                                                                              #########
  #############                       Employee ID 18467 - Employee                                                                             #########
  #############                                                                                                                                #########
  ######################################################################################################################################################
  ######################################################################################################################################################
  ######################################################################################################################################################*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
#define employees "employees.txt"

int loginStatus = 0; //0 for regular employee, 1 for management, 2 for HR

//function i found online to make replacing characters in strings much easier
bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}
 //function i wrote just to make it where I did not have to loop through a bunch of strings with repeated code
string lower(string toConvert){
    for(int i = 0; i < size(toConvert); i++){
        toConvert[i] = tolower(toConvert[i]);
    }
    return toConvert;
}

class Employee{
    int employeeID;
    string name; //will store the name of the employee
    int salary; //will store the salary of the employee in integer form
    string hireDate; //will have the hire date of the employee
    string title; //will have the titel/position the employee holds
    string termDate; // termination date.. will set to Active if no termination date
    string username; //username for login
    string password; //password for login
    //functions all defined at the bottom
    public:
        void ShowEmployeeRecord();
        void GetEmployeeRecord();
        void AddEmployeeRecord();
        void SearchEmployeeRecord();
        string SearchEmployeeID(string searchkey);
        void RemoveEmployeeRecord();
        void Login();
        void EditSalary();

}aEmployee;

//Menu class that will hold the options available at menu for the human resources department.  Options can easily be changed.
class Menu{
    private: //private variables that do not need to be known outside of this class..
        string title = "\n## Select from the list below what action you would like to take.. ##\n";
        string option1 = " Add Employee";
        string option2 = " Remove Employee";
        string option3 = " Employee Lookup";
        string option4 = " Edit Employee Salary";
        string option5 = " LogOut";
        string option6 = " Exit";
    //functions that will be used by other menus
    public:
        void drawMenu(); //defined below
        //we will use this menu for when some sort of HR Analyst logs in
        void drawHRMenu(){

            string padding(title.length()-2, '#'); //set up padding for a decent aesthetic
            cout << "\n\n"<<padding << title << padding << "\n\n(1)" << option1 //add in the cout telling HR to enter details
                                                << "\n(2)" << option2
                                                << "\n(3)" << option3
                                                << "\n(4)" << option4
                                                << "\n(5)" << option5
                                                << "\n(6)" << option6 << "\n\n";
            string schoice;
            int choice;

            getline(cin, schoice);
            choice = stoi(schoice); //had to convert cuz cin>> was giving me issues for whatever reason

            switch(choice){
                case 1:
                    aEmployee.AddEmployeeRecord();
                case 2:
                    aEmployee.RemoveEmployeeRecord();
                case 3:
                    aEmployee.SearchEmployeeRecord();
                case 4:
                    aEmployee.EditSalary();
                case 5:
                    aEmployee.Login();
                case 6:
                    exit(3);
                
            }
        }
        //We will use this menu for when some sort of Manager logs in
        void drawManagerMenu(){
            string padding(title.length()-2, '#'); //set up padding for a decent aesthetic
            cout << "\n\n"<<padding << title << padding << "\n\n(1)" << option3 
                                                                    << "\n(2)" << option5
                                                                    << "\n(3)" << option6 << "\n\n";
            string schoice;
            int choice;

            getline(cin, schoice);
            choice = stoi(schoice); //had to convert cuz cin>> was giving me issues for whatever reason
            //switch/case for the manager menu that will choose the correct option
            switch(choice){
                case 1:
                    aEmployee.SearchEmployeeRecord();
                case 2:
                    aEmployee.Login();
                case 3:
                    exit(3);
            }
        }
        //We will use this menu for when anyone that is not a Manager or an HR Analyst logs in
        void drawEmployeeMenu(){
            string padding(title.length()-2, '#'); //set up padding for a decent aesthetic
            cout << "\n\n"<<padding << title << padding << "\n\n(1)" << option5 
                                                                    << "\n(2)" << option6 << "\n\n";
            string schoice;
            int choice;

            getline(cin, schoice);
            choice = stoi(schoice); //had to convert cuz cin>> was giving me issues for whatever reason

            switch(choice){
                case 1:
                    aEmployee.Login();
                case 2:
                    exit(3);
            }
        }
}menu;//alias for class for ease of use

//deprecated, left in the code just in case I find use for it.
class LoginPrompt{
    string username;
    string password;
    
    public:
        //void Login();
        string SearchUsername(string searchkey);
        
}login;

int main(){
    aEmployee.Login();
    return 0;
}

//function created to input the details and save to a file so that it can be read and retrieved later.
void Employee :: AddEmployeeRecord(){
    ofstream file(employees, ios::binary|ios::app);

    if(!file){

        cout<<"Error Loading Doc!!  Check directory for filename";
        return;  
    }
    //input values for adding a new employee record
    string ssalary;
    cout << "\n\nEnter Employee Name\n";
    getline(cin, name);
    cout << "Enter Employee Hire Date\n";
    getline(cin, hireDate);
    cout << "Enter Employee Title\n";
    getline(cin, title);
    cout << "Enter Employee Salary\n";
    getline(cin, ssalary);
    salary = stoi(ssalary);
    cout << "Enter Employee Username\n";
    getline(cin, username);
    cout << "Enter Employee Password\n";
    getline(cin, password);
    
    srand(time(0));
    employeeID = (100000 + rand() % 999999); //develops a 6 digit employee number at random

    file << "\n\n";
    file << "Employee ID: " << employeeID << "\n";
    file << "Employee Name: " << name << "\n";
    file << "Employee Hire Date: " << hireDate << "\n";
    file << "Employee Title: " << title << "\n";
    file << "Employee Salary: " << salary << "\n";
    file << "Employee Username: " << username << "\n";
    file << "Employee Password: " << password; //writing to file

    file.close(); //close file
    menu.drawMenu();
}

//function for showing the employee record.  Can be used upon employee login.. manager search or HR search
void Employee :: ShowEmployeeRecord(){
    string msg = "Employee successfully added! Here are the details for review...";
    string padding(msg.length(), '#');
    cout<<"\n"<<padding<<"\n\n";
    //cout<<msg<<endl;
    cout<<"Employee ID:            "<< employeeID<<endl;
    cout<<"Employee Name:          "<< name<<endl;
    cout<<"Employee Hire Date:     "<< hireDate<<endl;
    cout<<"Employee Title:         "<< title<<endl;
    cout<<"Employee salary:        "<< salary<<endl;
    cout<<"\n"<<padding<<"\n\n";
}

//Lot of stuff going on here.  This will find a substring of each line to see if there is a match.  It will then parse out the eID, name, hire date, salary, and their title
void Employee :: SearchEmployeeRecord(){
    fstream file(employees, ios::binary|ios::in|ios::out);
    string ssalary;
    string sID;
    string mystring;
    string lineID;
    string lineName;
    string lineHireDate;
    string lineTitle;
    string lineSalary;
    string dummystring;
    int i = 1;
    int j = 0;
    bool itemFound = false;
    string searchkey;
    cout << "Employee to search.. \n"; //enter key to search
    getline(cin, searchkey);
    string lsearchkey = lower(searchkey);
    while( getline (file,mystring)){
        
        //each time we are at the first line, we want to save the line to parse with the eID as we are searching by name.
        if(i == 1){
            lineID = mystring;
        }
        string lmystring = lower(mystring);
        cout<<lsearchkey<<lmystring;
        //we have found a line!
        if(lmystring.find(lsearchkey) != string::npos){
            
            lineName = mystring; //save the line to mystream and set itemFound to true!
            itemFound = true;

        }
        else{
            i++;
            //with item set to true, and with j at 0.. we can now save the rest of the lines
            if(itemFound){ 
                
                if(j == 0){
                    lineHireDate = mystring;
                }
                else if(j == 1){
                    lineTitle = mystring;
                }
                else if(j == 2){
                    lineSalary = mystring;
                    break; //break from the loop since we have found our employee and no longer need to be in loop.  Later iterations can account for more than 1 result.
                }
                j++;
            }
            //every time we hit the 9th line, we know that we are starting at a new record, so we will set i back to 1
            if(i % 9 == 0){
                i = 1;
            }
        }
    }
    //store the parsed values into the class variables.  notice with eID and salary we have to do some conversion.
    sID = lineID.substr(13);
    employeeID = stoi(sID);
    name = lineName.substr(15);
    hireDate = lineHireDate.substr(20);
    title = lineTitle.substr(16);
    ssalary = lineSalary.substr(17);
    salary = stoi(ssalary);

    aEmployee.ShowEmployeeRecord(); //show the employee of record.
    do 
    {
    cout << '\n' << "Press a key to continue...";
    } while (cin.get() != '\n');
    menu.drawMenu();
}

void Employee::Login(){
    string username;
    string iPassword;
    string password;
    cout << "What is your Employee ID? Type 'quit' to exit program...\n";
    getline(cin, username);
    string lowerUsername = lower(username);
    if(lowerUsername == "quit"){ //comparing lower to the username/ID as well as a lower of quit to see if they want to quit.. if they do type quit itll exit.  QuIT will also work.
        exit(3);
    }
    password = aEmployee.SearchEmployeeID(username);
    cout<< "Password?\n";
    getline(cin, iPassword);
    while(iPassword != password){
        cout<<"Incorrect password, try again..."<<endl;
        getline(cin, iPassword);
    }
    //if we successfully login
    if(iPassword == password){
        cout << "Successful Login!  Here is your Employee Record";
        aEmployee.ShowEmployeeRecord(); //show employees own record
        if(title == "HR Analyst"){ //if HR analyst, draw the menu for HR analyst
            loginStatus = 2; //Sentinal switch to track which menu to draw
            menu.drawMenu();
        }
        else if(title == "Manager"){ //if Manager, draw the menu for HR analyst
            loginStatus = 1;
            menu.drawMenu();
        }
        else{
            loginStatus = 0; //All other employees just get to see their own record and a menu asking them to logout/exit
            menu.drawMenu();
        }
    }

}

void Menu::drawMenu(){
    if(loginStatus == 0){menu.drawEmployeeMenu();}
    else if (loginStatus == 1){menu.drawManagerMenu();}
    else if (loginStatus == 2){menu.drawHRMenu();}
}

//deprecated, left in the code just in case I find use for it.
string LoginPrompt::SearchUsername(string searchkey){
    fstream file(employees, ios::binary|ios::in|ios::out);
    string mystring;
    string lineName;
    string linePW;
    string password;
    bool itemFound = false;
    //int j = 0;
    while( getline (file,mystring)){

        //we have found a line!
        if(itemFound){
            linePW = mystring;
            break;
        }
        if(mystring.find(searchkey) != string::npos){
            lineName = mystring; //save the line to mystream and set itemFound to true!
            itemFound = true;
        }
    }
    password = linePW.substr(19);
    
    if(itemFound == false){
        cout << "username was not found, try again..";
        aEmployee.Login();
    }
    return password;

}
//function used to remove an employee from the record.  
void Employee::RemoveEmployeeRecord(){
    string sID;
    vector<string> keepLines;
    cout<<"\nEnter ID of employee to remove from database.. \n";
    getline(cin, sID);
    fstream file(employees, ios::binary|ios::in|ios::out);
    ofstream tFile("tempFile.txt"); //create a new file called tempFile.. we will use this to write the values from employees.txt - the entry to be removed.
    string mystring;
    bool itemFound = false;
    int j = 0;
    //find the ID
    while( getline (file,mystring)){
        if(mystring.find(sID) != string::npos){
            itemFound = true;
        }
        if(itemFound){
            if(j<=6){
                j++;
            }
            else if(j>6){
                itemFound = false;
            }
        }
        else if(!itemFound){
            keepLines.push_back(mystring); //push into the vector
        }
    
    }
    //spit out lines from vector to the tempfile
    cout<<size(keepLines)<<endl;
    for(int i = 0; i < size(keepLines); i++){
        tFile<<keepLines[i]<<endl;
    }
    //close the files so they can be deleted/renamed
    file.close();
    tFile.close();
    //out with the old, in with the new..
    remove("employees.txt"); 
    rename("tempFile.txt", "employees.txt");

    menu.drawMenu();

}
//function used to edit the salary..
void Employee::EditSalary(){
    string sID;
    string ssalary;
    string newSalary;
    int salaryIndex;
    vector<string> employeeLines;
    fstream file(employees, ios::binary|ios::in|ios::out);
    ofstream tFile("tempFile.txt");
    string mystring;
    bool itemFound = false;
    int j = 0;
    int i = 0;
    cout<<"What is the ID of the employee for the salary edit?";
    getline(cin, sID);

    while( getline (file,mystring)){
        employeeLines.push_back(mystring);
        if(itemFound){
            j++;
            if(j==4){
                cout<<mystring<<endl;
                ssalary = mystring.substr(17);
                salaryIndex = i;
            }
        }
        if(mystring.find(sID) != string::npos){
            cout<<"Item found!"<<endl;
            itemFound = true;
        }
        i++;
    }
    cout<<"What shall the salary be changed to?"<<endl;
    getline(cin, newSalary);
    replace(employeeLines[salaryIndex], ssalary, newSalary); //replace the current salary with old salary at the vector
    
    //put lines into tempfile
    for(int i = 0; i < size(employeeLines); i++){
        tFile<<employeeLines[i]<<endl;
    }
    //close files to delete/rename
    file.close();
    tFile.close();
    //out with the old, in with the new
    remove("employees.txt");
    rename("tempFile.txt", "employees.txt");
    
    menu.drawMenu();
}

string Employee::SearchEmployeeID(string searchkey){
    //cout<<searchkey<<endl;
    fstream file(employees, ios::binary|ios::in|ios::out);
    string mystring;
    string ssalary;
    string sID = searchkey;
    string lineName;
    string lineID;
    string lineHireDate;
    string lineTitle;
    string lineSalary;
    string linePW;
    string password;
    string lineUser;
    bool itemFound = false;
    int j = 0;
    while( getline (file,mystring)){
        //cout<<mystring;
        if (itemFound && (j <= 5)){
           if(j == 0){name = mystring.substr(15);}
           else if(j == 1){hireDate = mystring.substr(20);} 
           else if(j == 2){title = mystring.substr(16);} 
           else if(j == 3){ssalary = mystring.substr(17);}  
           else if(j == 4){lineUser = mystring;}
           else if(j == 5){password = mystring.substr(19);}
           j++;  
        }
        if(mystring.find(searchkey) != string::npos){
            lineID = mystring; //save the line to mystream and set itemFound to true!
            itemFound = true;
        }
        
        
        
    }

    if(!ssalary.empty()){salary = stoi(ssalary);}
    if(!sID.empty()){employeeID = stoi(sID);}

    if(itemFound == false){
        //LoginPrompt a;
        cout << "User ID was not found, try again..";
        aEmployee.Login();
    }
    return password;//, sID, name, hireDate, title, ssalary;
}