#include <iostream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

//#define MAX_USERS 2
#define MAX_APPOINTMENTS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define NAME_LEN 50
#define SPECIALIZATION_LEN 50
#define GENDER_LEN 10
#define pfile "pdata.dat"
#define APfile "appdata.dat"
#define docfile "docdata.dat"

#define MAX_USERS 100
#define PATIENT_FILE "patient_M.dat"
#define USRNM_LEN 50
#define PSWD_LEN 20
#define NAME_LEN 50
#define GEN_LEN 6

typedef struct {
    char username[USRNM_LEN];
    char password[PSWD_LEN];
    char name[NAME_LEN];
    int age;
    char phoneno[15];
    char gender[GEN_LEN];
    int patientID;
    int delete_p;
} patient;

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char name[NAME_LEN];
    char specialization[SPECIALIZATION_LEN];
    int docID;
} Doctor;

int doctorCount = 0;
Doctor doctors[MAX_USERS];

int patientCount = 0;
patient patients[MAX_USERS];
char newUsername[50];
char newPassword[20] = {'0'};

void patientMenu(char ch);
void patientOptions();
//void load_patients();
void register_patient();
void patient_details();
void get_patient();
void save_patient();
int login_patient();
//addition
void bookAppointment();
void patientCancelAppointment();

void doctorMenu(char ch, int id);
void registerDoctor();
void displayDoctor();
void saveDoctor();
//void loadDoctors();
int doctorLogin();
//addition
void changeAppointment();
void doctorCancelAppointment();

void adminMenu(char ch);
void loadDoctors();
void load_patients();
//addition
void addCityOrHospital();
void listCityOrHospital();
void listAppointmentRecords();

void setScreen();
void askForSecretPassword(char *k);

int main() {

	setScreen();
	loadDoctors();
    int id, ID;
    char ch, mainch;
    do {
		system("cls");
		cout << "\n\t\t____________________________________________________________________\n\n\n";
		cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
		cout << "\n\t\t_________________________    MAIN MENU    __________________________\n\n\n";
		cout << "																			\n\n";
		cout << "\t|Press 1 to Select Patient Menu	|" << endl;
		cout << "\t|Press 2 to Select Doctor Menu	|" << endl;
		cout << "\t|Press 3 to Select Admin menu		|" << endl;
		cout << "\t|Press 4 to EXIT			|" << endl;
		cout << "\n\t\t\t Please Pick a Menu: ";

        mainch = getche();
        cout << endl;
        
        switch (mainch) {
            case '1':
            	patientMenu(ch);
                break;
            case '2':
            	doctorMenu(ch, id);
				break;
            case '3':
            	adminMenu(ch);
              	break;
            case '4':
            	cout <<"Program exited";
            	exit(0);
            default:
                cout <<"\n\tInvalid choice!!"<< endl;
                cout <<"\tPress any key to Continue"; getch();
                break;
        }
    } while (mainch!='4');
    return 0;
}

void setScreen(){
	//This function with its parameters changes the console area/size.
	system("mode con COLS=700");
	//This function maximizes the console to full screen
	ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
	//These two lines are used to change the text and screen color of console.
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,(1 << 4) | 15);
}

void registerDoctor(){
	Doctor newDoctor;
	cout << "User name: "; cin >> newDoctor.username;
	cout << "Password: "; cin >> newDoctor.password;
	cout << "Name: "; cin >> newDoctor.name;
	cout << "Specialization: "; cin >> newDoctor.specialization;
	newDoctor.docID = doctorCount + 1;
	doctors[doctorCount] = newDoctor;
	doctorCount++;
	cout << "\nDoctor successfully saved!\n";
}

void displayDoctor(){
	if (doctorCount == 0){
		cout << "\nNo doctors info available.\n";
		return;
	}
	else{
		cout << "\n\n_____________________________________________________________________________________________________________________________\n";
		cout << setw(20) << "DoctorId" 
			<< setw(20) << "Username" 
			<< setw(20) << "Password" 
			<< setw(20) << "Name" 
			<< setw(30) << "Specialization" << endl;
		cout << "_____________________________________________________________________________________________________________________________\n";
		for(int i = 0; i < doctorCount; i++)
					cout << setw(20) << doctors[i].docID 
						<< setw(20) << doctors[i].username 
						<< setw(20) << doctors[i].password 
						<< setw(20) << doctors[i].name 
						<< setw(30) << doctors[i].specialization << endl;
	}
}

void saveDoctor(){
	fstream file;
	file.open(docfile, ios::out | ios::app | ios::binary);
	
	if(file.is_open()){
		file.write(reinterpret_cast<char*>(&doctors[doctorCount - 1]), sizeof(Doctor));
		file.close();
	}
	else{
		cout << "\nERROR!\n";
	}
}

void loadDoctors(){
	fstream file;
	file.open(docfile, ios::in | ios::binary);

	int size = 0;
	file.seekg(0, ios::end);
	size = (int)file.tellg();
	file.seekg(0, ios::beg);
		
	while(file.tellg() < size){
		file.read(reinterpret_cast<char*>(&doctors[doctorCount]), sizeof(Doctor));
		doctorCount++;
	}
	file.close();
}

int doctorLogin(){
	char usernameLogin[USERNAME_LEN];
//	char passwordLogin[PASSWORD_LEN] = {'1'};
	char passwordLogin[PASSWORD_LEN];
	cout << "\nEnter Username: "; cin >> usernameLogin;
	askForSecretPassword(passwordLogin);
	for(int i = 0; i < doctorCount; i++){
//		if(strcmp(usernameLogin, doctors[i].username) == 0 && strcmp(passwordLogin, doctors[i].password) == 0){
	if(strcmp(usernameLogin, doctors[i].username) == 0){
			cout << "\nSuccessfully Logged in.";
			return doctors[i].docID;	
		}
	}
//	cout << "\nLogin failed!\nIncorrect username or password.";
	return -1;
}

void patientMenu(char ch){
	do {
		int id;
		system("cls");
		cout << "\n\t\t____________________________________________________________________\n\n\n";
		cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
        cout << "\n\t\t_________________________      Patient MENU      ___________________\n\n\n";
		cout << "\t|Press 1 to LOGIN as a Patient		|" << endl;
		cout << "\t|Press 2 to Register as Patient		|" << endl;
		cout << "\t|Press 3 Back to Main Menu		|" << endl;
		cout << "\n\t\t\t Please enter your choice: ";
        ch = getche();
        cout << endl;
        switch (ch) {
            case '1':
            	patientOptions();
                break;
            case '2': // register Pateient
            	register_patient();
            	save_patient();
				cout << "\tPress any key to Continue"; getch();
                break;
            case '3':
            	system("cls");
                break;
            default:
                cout <<"\n\tInvalid choice\n";
                cout <<"\tPress any key to Continue"; getch();
        }
    } while (ch != '3');
}

void register_patient(){
	
	if (patientCount >= MAX_USERS) {
        cout << "We can't register more patients. Sorry!\n";
        return;
    }
    
    patient newPatient;
    
    char username[USRNM_LEN];
    char password[PSWD_LEN];
    char name[NAME_LEN];
    int age;
    char phoneno[15];
    char gender[GEN_LEN];
    int patientID;
    
    cout << "\n\nEnter patient's username: "; cin >> newPatient.username;
	cout << "Enter patient's password: "; cin >> newPatient.password;
	cout << "Enter patient's name: "; cin >> newPatient.name;
	cout << "Enter patient's age: "; cin >> newPatient.age;
	cout << "Enter patient's phoneNo: "; cin >> newPatient.phoneno;
	cout << "Enter patient's gender (male/female/other): "; cin >> newPatient.gender;
    newPatient.patientID = patientCount + 1;
    newPatient.delete_p = 0;
    
    patients[patientCount++] = newPatient;
    cout << "Patient registered successfully! Patient ID: " << newPatient.patientID << "\n";
}

void patient_details() {
    if (patientCount == 0){
        cout << "No registered patients found!\n";
        getchar();
    }
    else {
    	cout <<setw(20) <<"Patient ID" <<setw(20) <<"Username" <<setw(20) << "Password" <<setw(20) <<"Name" <<setw(20) << "Age" <<setw(20) << "Gender\n" << endl;
        for (int i = 0; i < patientCount; i++) {
            cout <<setw(20) << patients[i].patientID
				<<setw(20)	<< patients[i].username 
				<<setw(20)	<< patients[i].password
				<<setw(20)	<< patients[i].name 
				<<setw(20)	<< patients[i].age
				<<setw(20)	<< patients[i].gender	<< endl;
        }
        getchar();
    }
}

void save_patient() {

	fstream file;
	file.open(PATIENT_FILE, ios::out | ios::binary | ios::app );
	
	if(file.is_open())
	{
		file.write(reinterpret_cast<char*>(&patients[patientCount - 1]), sizeof(patient));
		file.close();
	}
	else
		cout << "ERROR\n";

}

void load_patients(){

	fstream file;
	file.open(PATIENT_FILE, ios::in | ios::binary);
	if(file.is_open())
	{
		int size = 0;
		file.seekg(0, ios::end);
		size = (int)file.tellg();
		file.seekg(0, ios::beg);
		while(file.tellg() < size){
			file.read(reinterpret_cast<char*>(&patients[patientCount]), sizeof(patient));
			patientCount++;
		}
		file.close();
	}
	else
		cout << "ERROR\n";	
}

int login_patient(){

	cout << "\nUsername: "; cin >> newUsername;
	askForSecretPassword(newPassword);
	
	for(int i = 0; i < patientCount; i++){
		if (strcmp(newUsername, patients[i].username) == 0 && strcmp(newPassword, patients[i].password) == 0){
			return 0;
		}
	}
	
	cout << "Not logged in! Invalid username or password.\n";
	getchar();
	return 1;
}

void askForSecretPassword(char *k){
	char ch;
	int i;
	cout << "Enter pass\n";
	ch = _getch();
	while(i != PSWD_LEN){
		if (ch == 13)
			break;
	  	*(k+i) = ch;
	  	cout << '*';
	  	ch = _getch();
	  	i++;
	}
}

void get_patient() {
    
	int patient_id;
	patient new_patient;
	char response;
	
	if(patientCount == 0){
		cout << "\nNo patients in the list to edit!\n";
		getchar();
		return;
	}
	
	cout << "\nEnter patient's id to edit: "; cin >> patient_id;
	for (int i = 0; i < patientCount; i++) {
		if (patients[i].patientID == patient_id ) {
            cout << "patient found: "<< patient_id <<endl ;
		    cout <<setw(20) <<"Patient ID" <<setw(20) <<"Username" <<setw(20) << "Password" <<setw(20) <<"Name" <<setw(20) << "Age" <<setw(20) << "Gender\n" << endl;
        	cout <<setw(20) << patients[i].patientID
				<<setw(20)	<< patients[i].username 
				<<setw(20)	<< patients[i].password
				<<setw(20)	<< patients[i].name 
				<<setw(20)	<< patients[i].age
				<<setw(20)	<< patients[i].gender	<< endl;
					
		    new_patient.patientID =  patients[i].patientID;
		    cout << "\n\nEnter patient's username: "; cin >> new_patient.username;
			cout << "Enter patient's password: "; cin >> new_patient.password;
			cout << "Enter patient's name: "; cin >> new_patient.name;
			cout << "Enter patient's age: "; cin >> new_patient.age;
			cout << "Enter patient's phoneNo: "; cin >> new_patient.phoneno;
			cout << "Enter patient's gender (male/female/other): "; cin >> new_patient.gender;
			
			cout << "\nAre you sure to update the patient (y/n)?: "; cin >> response;
			if(response == 'y' or response == 'Y')
				patients[i] = new_patient;
				
			fstream file;
			file.open(PATIENT_FILE, ios::out | ios::binary);
			
			if(file.is_open())
			{
				for(int j = 0; j < patientCount; j++){
					file.write(reinterpret_cast<char*>(&patients[j]), sizeof(patient));
				}
				file.close();
			}
			else
				cout << "ERROR\n";
				
//			break;
			return;
        }
    }
    cout << "Patient against given id not found!\n";
    getchar();
}

void patientOptions(){
	char ch;
	load_patients();
	int status = login_patient();
	if (status == 0){
		cout << "\nSuccessfully Logged in!\n"; getchar();
		do {
			system("cls");
			cout << "\n\t\t____________________________________________________________________\n\n\n";
			cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
            cout <<" \n\t\t               "<< newUsername <<" [1] successfully Logged In:\n\n";
			cout << "\n\t\t_________________________      Patient Optopns      ___________________\n\n\n";
    		cout << "\t|Press 1 to Book Appointment		|" << endl;
			cout << "\t|Press 2 Cancel appointment		|" << endl;
			cout << "\t|Press 3 to Logout	|" << endl;
			cout << "\n\t\t\t Please enter your choice: ";
            ch = getche();
            cout << endl;
            switch (ch) {
                case '1': // Book appointment
					cout << "\n\tEnter info to book Appointment by showing doctors detail\n";
					cout << "\tPress any key to Continue"; getch();
                    break;
                case '2': // Cancel appointment
					cout << "\n\tShow the list of appointments and get appointment id to cancel\n";
					cout << "\tPress any key to Continue"; getch();
                    break;
                case '3': // Log out
                    cout << "\n\tLogged out\n";
                    break;
                default:
                    cout << "\n\tInvalid choice!!\n";
                    cout << "\tPress any key to Continue"; getch();
            }
	    } while (ch != '3');
	}
	else{
        cout <<"\n\tLogin failed!\n";
        cout <<"\tPress any key to Continue"; getch();
	}
}

void doctorMenu(char ch, int id){
    do {
        system("cls");
		cout << "\n\t\t____________________________________________________________________\n\n\n";
		cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
        cout << "\n\t\t_________________________      Doctor MENU      ____________ _______\n\n\n";
		cout << "\t|Press 1 to LOGIN as a Doctor		|" << endl;
		cout << "\t|Press 2 to Register as Doctor		|" << endl;
		cout << "\t|Press 3 Back to Main Menu		|" << endl;
		cout << "\n\t\t\t Please enter your choice: ";

        ch = getche();
        cout << endl;
        switch (ch) {
            case '1':	//Login as a doctor
                id = doctorLogin();
                if (id > 0) {
                    cout <<"Login successful!\n";
                    do {
                        system("cls");
						cout << "\n\t\t____________________________________________________________________\n\n\n";
						cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
	                    cout <<" \n\t\t               doctor@gmail.com [1] successfully Logged In:\n\n";
						cout << "\n\t\t_________________________      Doctpr Options      ___________________\n\n\n";
	            		cout << "\t|Press 1 to View Appointment		|" << endl;
						cout << "\t|Press 2 to Logout	|" << endl;
						cout << "\n\t\t\t Please enter your choice: ";

                        ch = getche();
        				cout << endl;
                        switch (ch) {
                            case '1': // View Appointments
								cout <<"\n\tDisplay all the appoints for the dr who logged in:\n";
								cout <<"\tPress any key to Continue"; getch();
                                break;
                            case '2':
                                cout <<"\n\tLogged out\n";
                                break;
                            default:
                                cout <<"\n\tInvalid choice!!\n";
                                cout <<"\tPress any key to Continue"; getch();
                        }
                    } while (ch != '2');
                } else {
                    cout <<"\n\tLogin failed!\n";
                    cout <<"\tPress any key to Continue"; getch();
                }
                break;
            case '2':	//Register as a doctor
            	registerDoctor();
            	saveDoctor();
				cout << "\n\tGet docters info ad register\n";
				cout <<"\tPress any key to Continue"; getch();
                break;
            case '3':
            	system("cls");
                break;
            default:
                cout <<"\n\tInvalid choice\n";
                cout <<"\tPress any key to Continue"; getch();
        }
    } while (ch != '3');
}

void adminMenu(char ch){
    cout <<"Entered as an admin\n";
    do {
    	system("cls");
		cout << "\n\t\t____________________________________________________________________\n\n\n";
		cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
        cout << "\n\t\t_________________________      Admin MENU      ____________________\n\n\n";
		cout << "\t|Press 1 to LOGIN as an Admin		|" << endl;
		cout << "\t|Press 2 Back to Main Menu		|" << endl;
		cout << "\n\t\t\t Please enter your choice: ";
        ch = getche();
        cout << endl;
        switch (ch) {
            case '1':
                if (1 == 1) {
                    do {
                    	system("cls");
                    	cout << "\n\t\t____________________________________________________________________\n\n\n";
						cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
	                    cout <<" \n\t\t               Successfully Logged In as ADMIN\n\n";
						cout << "\n\t\t_________________________      Admin Options      ___________________\n\n\n";
	            		cout << "\t|Press 1 to Register a patient	|" << endl;
	            		cout << "\t|Press 2 to Register a Doctor	|" << endl;
	            		cout << "\t|Press 3 to Book an appointment	|" << endl;
						cout << "\t|Press 4 to list Appointments Record	|" << endl;	
	            		cout << "\t|Press 5 to list Patients Record	|" << endl;
						cout << "\t|Press 6 to list Doctors Record	|" << endl;	
						cout << "\t|Press 7 to add city OR hospital	|" << endl;
						cout << "\t|Press 8 to list cities and hospitals	|" << endl;
						cout << "\t|Press 9 to Logout	|" << endl;																	
						cout << "\n\t\t\t Please enter your choice: ";

                        ch = getche();
        				cout << endl;;
                        switch (ch) {
                            case '1': // Register a patient
								cout << "\n\tRegistere a Patient:\n";
								cout <<"\tPress any key to Continue"; getch();
                                break;
                            case '2': // Register a doctor
                            	registerDoctor();
                            	saveDoctor();
								cout << "\n\tRegister a doctor\n";
								cout <<"\tPress any key to Continue"; getch();
                                break;
                            case '3': //Book an appointment
								cout << "\n\tEnter info to book Appointment by showing doctors detail\n";
								cout <<"\tPress any key to Continue"; getch();
                                break;
                            case '4': //Appointments Record
								cout << "\n\tShow all appointment Detail\n";
								cout <<"\tPress any key to Continue"; getch();
                                break;
                            case '5': //Patients Record
								cout << "\n\tSave list of pateients all patiients\n";
								cout <<"\tPress any key to Continue"; getch();
                                break;
                            case '6': //Doctors Record
                            	displayDoctor();
//								cout << "\n\tShow or save list of all Doctors in text file\n";
								cout <<"\tPress any key to Continue"; getch();
                                break;
                            case '7': //Add city or hospital
                                cout <<"\n\tAdd city or hospital\n";
                                cout <<"\tPress any key to Continue"; getch();
                                break;
                            case '8': //List cities or hospitals
                                cout <<"\n\tList cities or hospitals\n";
                                cout <<"\tPress any key to Continue"; getch();
                                break;                                
                            case '9': //Logout
                                cout <<"\n\tLogged out\n";
                                cout <<"\tPress any key to Continue"; getch();
                                break;
                            default:
                                cout <<"\n\tInvalid choice!!\n";
                                cout <<"\tPress any key to Continue"; getch();
                        }
                    } while (ch != '7');
                } else {
                    cout <<"Login Failed!\n";
                }
                break;
            case '2':
            	system("cls");
                break;
            default:
                cout <<"\n\tInvalid choice\n";
                cout <<"\tPress any key to Continue"; getch();
        }
    } while (ch != '2');
}
