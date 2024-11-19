#include <iostream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

#define MAX_APPOINTMENTS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define NAME_LEN 50
#define SPECIALIZATION_LEN 50
#define GENDER_LEN 10
#define pfile "pdata.dat"
#define APfile "appdata.dat"
#define docfile "docdata.dat"
#define ACHfile "cityhospital.dat"

#define MAX_USERS 100
#define PATIENT_FILE "patient_M.dat"
#define USRNM_LEN 50
#define PSWD_LEN 20
#define NAME_LEN 50
#define GEN_LEN 6

#define CITY "fileCity.dat"
#define HOSPITAL "fileHospital.dat"
#define MAX_HOSPITAL 100
#define MAX_CITY 50
#define NAME_LENGTH 20
#define ADDRESS 50

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
    int hospitalID;
} Doctor;

typedef struct{
	int hospitalID;
	char hospitalName[NAME_LENGTH];
	char hospitalAddress[ADDRESS];
	int cityID;
}Hospital;

typedef struct{
	char cityName[NAME_LENGTH];
	int cityID;
}City;


int doctorCount = 0;
int presentDoctorID = -1;
Doctor doctors[MAX_USERS];

int patientCount = 0;
int presentPatinetID = -1;
patient patients[MAX_USERS];
char newUsername[50];
char newPassword[20] = {'0'};

int cityCount = 0;
int hospitalCount = 0;
Hospital hospitals[MAX_HOSPITAL];
City cities[MAX_CITY];


void patientMenu(char ch);
void patientOptions();
void loadPatients();
void register_patient();
void patient_details();
void get_patient();
void save_patient();
int login_patient();
void patientInformation(int id);
//addition

void doctorMenu(char ch, int id);
void registerDoctor();
void displayDoctor();
void saveDoctor();
void loadDoctors();
int doctorLogin();
void getDoctors();
void doctorInformation(int id);
//addition
void changeAppointment();
void doctorCancelAppointment();

void adminMenu(char ch);
void load_patients();
//addition
void cityHospital();

void setScreen();
void askForSecretPassword(char *k);

void loadCity();
void loadHospital();
void addCity();
void addHospital();
void displayCity();
void displayHospital();
void editCity();
void editHospital();
void saveCity();
void saveHospital();
void listCities();

int main() {

	setScreen();
	loadDoctors();
	loadPatients();
	loadCity();
	loadHospital();
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
	system("mode con COLS=700"); //This function with its parameters changes the console area/size.
	ShowWindow(GetConsoleWindow(),SW_MAXIMIZE); //This function maximizes the console to full screen.
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 	//These two lines are used to change the text and screen color of console.
    SetConsoleTextAttribute(hConsole,(1 << 4) | 15);
}

void registerDoctor(){
	Doctor newDoctor;
	cout << "User name: "; cin >> newDoctor.username;
	cout << "Password: "; cin >> newDoctor.password;
	cout << "Name: "; cin >> newDoctor.name;
	cout << "Specialization: "; cin >> newDoctor.specialization;
	cout << endl;
	displayHospital();
	cout << "\nHospital ID: "; cin >> newDoctor.hospitalID;
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
			<< setw(30) << "Specialization"
			<< setw(2) << "Hospital ID" << endl;
		cout << "_____________________________________________________________________________________________________________________________\n";
		for(int i = 0; i < doctorCount; i++)
					cout << setw(20) << doctors[i].docID 
						<< setw(20) << doctors[i].username 
						<< setw(20) << doctors[i].password 
						<< setw(20) << doctors[i].name 
						<< setw(30) << doctors[i].hospitalID
						<< setw(2) << doctors[i].specialization << endl;
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
	char passwordLogin[PASSWORD_LEN] = {'1'};
//	char passwordLogin[PASSWORD_LEN];
	cout << "\nEnter Username: "; cin >> usernameLogin;
	askForSecretPassword(passwordLogin);
	for(int i = 0; i < doctorCount; i++){
	if(strcmp(usernameLogin, doctors[i].username) == 0 && strcmp(passwordLogin, doctors[i].password) == 0){
//	if(strcmp(usernameLogin, doctors[i].username) == 0){
			presentDoctorID = doctors[i].docID;
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
    	cout << "\n\n_____________________________________________________________________________________________________________________________\n";
    	cout <<setw(20) <<"Patient ID" <<setw(20) <<"Username" <<setw(20) << "Password" <<setw(20) <<"Name" <<setw(20) << "Age" <<setw(20) << "Gender\n" << endl;
    	cout << "_____________________________________________________________________________________________________________________________\n";
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

void loadPatients(){

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
			presentPatinetID = patients[i].patientID;
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
				int fp = sizeof(patient)*i;
				file.seekg(fp);
				file.write(reinterpret_cast<char*>(&patients[i]), sizeof(patient));
				file.close();
			}
			else
				cout << "ERROR\n";
				
			break;
			return;
        }
    }
    cout << "Patient against given id not found!\n";
    getchar();
}

void patientInformation(int id){
	for(int i = 0; i < patientCount; i++){
		if(id == patients[i].patientID){
			cout << "\n\tPatient ID: " << patients[i].patientID;
			cout << "\n\tPatinet Username: " << patients[i].username;
			cout << "\n\tPatient password: " << patients[i].password;
			cout << "\n\tPatinet Name: " << patients[i].name;
			cout << "\n\tPatient phoneNo: " << patients[i].phoneno;
			cout << "\n\tPatinet age: " << patients[i].age;
			cout << "\n\tPatinet Gender: " << patients[i].gender;
			
			patient newPatient;
		    
		    newPatient.patientID = patients[i].patientID;
		    cout << "\n\nEnter patient's username: "; cin >> newPatient.username;
			cout << "Enter patient's password: "; cin >> newPatient.password;
			cout << "Enter patient's name: "; cin >> newPatient.name;
			cout << "Enter patient's age: "; cin >> newPatient.age;
			cout << "Enter patient's phoneNo: "; cin >> newPatient.phoneno;
			cout << "Enter patient's gender (male/female/other): "; cin >> newPatient.gender;
			patients[i] = newPatient;
			
			fstream file;
			file.open(PATIENT_FILE, ios::out | ios::binary);
			
			if(file.is_open())
			{
				int fp = sizeof(patient)*i;
				file.seekg(fp);
				file.write(reinterpret_cast<char*>(&patients[i]), sizeof(patient));
				file.close();
			}
			else
				cout << "ERROR\n";
			
			cout << "\nInformation changed!\n";
			getchar();
			break;
		}
	}
}

void patientOptions(){
	char ch;
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
			cout << "\t|Press 2 to Cancel appointment	|" << endl;
			cout << "\t|Press 3 to edit Information		|" << endl;
			cout << "\t|Press 4 to Logout				|" << endl;
			cout << "\n\t\t\t Please enter your choice: ";
            ch = getche();
            cout << endl;
            switch (ch) {
                case '1':
					cout << "\n\tEnter info to book Appointment by showing doctors detail\n";
					cout << "\tPress any key to Continue"; getch();
                    break;
                case '2':
					cout << "\n\tShow the list of appointments and get appointment id to cancel\n";
					cout << "\tPress any key to Continue"; getch();
                    break;
                case '3':
                    cout << "\n\tEditing information:\n";
                    patientInformation(presentPatinetID);
                    break;
                case '4':
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
            case '1':
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
						cout << "\t|Press 2 to Edit Information		|" << endl;
						cout << "\t|Press 3 to Logout				|" << endl;
						cout << "\n\t\t\t Please enter your choice: ";

                        ch = getche();
        				cout << endl;
                        switch (ch) {
                            case '1': 
								cout <<"\n\tDisplay all the appoints for the dr who logged in:\n";
								cout <<"\tPress any key to Continue"; getch();
                                break;
                            case '2':
                            	doctorInformation(presentDoctorID);
                            	break;
                            case '3':
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
            case '2':
            	registerDoctor();
            	saveDoctor();
				cout << "\n\tGet docters info ad register\n";
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

void getDoctors(){
	
	int doctorID;
	Doctor newDoctor;
	char response;
	
	if(doctorCount == 0){
		cout << "\nNo patients in the list to edit!\n";
		getchar();
		return;
	}
	
	cout << "\nEnter doctor's id to edit: "; cin >> doctorID;
	for (int i = 0; i < doctorCount; i++) {
		if (doctors[i].docID == doctorID) {
            cout << "patient found: "<< doctorID <<endl ;
			cout << "\n\n_____________________________________________________________________________________________________________________________\n";
			cout << setw(20) << "DoctorId" 
				<< setw(20) << "Username" 
				<< setw(20) << "Password" 
				<< setw(20) << "Name" 
				<< setw(30) << "Specialization"
				<< setw(2) << "Hospital ID" << endl;
			cout << "_____________________________________________________________________________________________________________________________\n";
			cout << setw(20) << doctors[i].docID 
				<< setw(20) << doctors[i].username 
				<< setw(20) << doctors[i].password 
				<< setw(20) << doctors[i].name 
				<< setw(30) << doctors[i].specialization
				<< setw(2) << doctors[i].hospitalID << endl;
			
			cout << "\nNew Record:\n";
			cout << "Username: "; cin >> newDoctor.username;
			cout << "Password: "; cin >> newDoctor.password;
			cout << "Name: "; cin >> newDoctor.name;
			cout << "Specialization: "; cin >> newDoctor.specialization;
			cout << endl;
			displayHospital();
			cout << endl;
			cout << "Hospital ID: "; cin >> newDoctor.hospitalID;
			
			cout << "\nAre you sure to update the patient (y/n)?: "; cin >> response;
			if(response == 'y' or response == 'Y')
				doctors[i] = newDoctor;
				
			fstream file;
			file.open(docfile, ios::out | ios::binary);
			
			if(file.is_open())
			{
				int fp = sizeof(Doctor)*i;
				file.seekg(fp);
				file.write(reinterpret_cast<char*>(&doctors[i]), sizeof(Doctor));
				file.close();
			}
			else
				cout << "ERROR\n";
				
			break;
			return;
        }
    }
    cout << "Patient against given id not found!\n";
    getchar();
	
}

void doctorInformation(int id){
	for(int i = 0; i < doctorCount; i++){
		if(id == doctors[i].docID){
			cout << "\n\tDoctor ID: " << doctors[i].docID;
			cout << "\n\tDoctor Username: " << doctors[i].username;
			cout << "\n\tDoctor password: " << doctors[i].password;
			cout << "\n\tDoctor Name: " << doctors[i].name;
			cout << "\n\tDoctor Specialization: " << doctors[i].specialization;
			cout << "\n\tHospital ID: " << doctors[i].hospitalID;
			
			Doctor newDoctor;
		    cout << "\nNew information:\n";
		    newDoctor.docID = doctors[i].docID;
		    cout << "Username: "; cin >> newDoctor.username;
			cout << "Password: "; cin >> newDoctor.password;
			cout << "Name: "; cin >> newDoctor.name;
			cout << "Specialization: "; cin >> newDoctor.specialization;
			cout << endl;
			displayHospital();
			cout << endl;
			cout << "Hospital ID: "; cin >> newDoctor.hospitalID;
			doctors[i] = newDoctor;
			
			fstream file;
			file.open(docfile, ios::out | ios::binary);
			
			if(file.is_open())
			{
				int fp = sizeof(Doctor)*i;
				file.seekg(fp);
				file.write(reinterpret_cast<char*>(&doctors[i]), sizeof(Doctor));
				cout << "\nInformation changed!\n";
				file.close();
			}
			else
				cout << "ERROR\n";
			getchar();
			break;
		}
	}
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
	            		cout << "\t|Press 1 to Patient Management	|" << endl;
	            		cout << "\t|Press 2 to Doctor Management	|" << endl;
	            		cout << "\t|Press 3 to Appointment Management	|" << endl;
						cout << "\t|Press 4 to city and hospital Management	|" << endl;
						cout << "\t|Press 5 to Logout	|" << endl;																	
						cout << "\n\t\t\t Please enter your choice: ";

                        ch = getche();
        				cout << endl;;
                        switch (ch) {
                            case '1':
								cout << "\n\tPatient Management:\n";
								cout << "\n\tPress 1 for register patient "
									<< "\n\tPress 2 for listing all patients information"
									<< "\n\tPress 3 for specific patinet information"
									<< "\n\tPress 4 for editing patient record"
									<< "\n\n\tEnter choice no: ";
								ch = getche();
								switch (ch){
									case '1':
										register_patient();
										save_patient();
										patient_details();
										break;
									case '2':
										patient_details();
										break;
									case '3':
										cout << "\n\tSpecific patinet information\n";
										int newID;
										cout << "Enter patient ID: "; cin >> newID;
										for(int i = 0; i < patientCount; i++){
											if(newID == patients[i].patientID){
												cout << "\n\tPatient ID: " << patients[i].patientID;
												cout << "\n\tPatinet Username: " << patients[i].username;
												cout << "\n\tPatient password: " << patients[i].password;
												cout << "\n\tPatinet Name: " << patients[i].name;
												cout << "\n\tPatient phoneNo: " << patients[i].phoneno;
												cout << "\n\tPatinet Gender: " << patients[i].gender;		
												break;
											}
										}
										break;
									case '4':
										cout << "\n\tEditing doctors information\n";
										get_patient();
										break;
									default:
										cout << "\nInvalid option!\n";
								}
											
								cout <<"\tPress any key to Continue"; getch();
                                break;
                            case '2':
								cout << "\n\tDoctor Management:\n";
								cout << "\n\tPress 1 for register doctor "
									<< "\n\tPress 2 for listing all doctors information"
									<< "\n\tPress 3 for specific doctor information"
									<< "\n\tPress 4 for editing doctor record"
									<< "\n\n\tEnter choice no: ";
								ch = getche();
								switch (ch){
									case '1':
										registerDoctor();
										saveDoctor();
										break;
									case '2':
										displayDoctor();
										break;
									case '3':
										cout << "\n\tSpecific doctor information\n";
										int newID;
										cout << "Enter doctor ID: "; cin >> newID;
										for(int i = 0; i < doctorCount; i++){
											if(newID == doctors[i].docID){
												cout << "\n\tDoctor ID: " << doctors[i].docID;
												cout << "\n\tDoctor Username: " << doctors[i].username;
												cout << "\n\tDoctor password: " << doctors[i].password;
												cout << "\n\tDoctor Name: " << doctors[i].name;
												cout << "\n\tDoctor Specialization: " << doctors[i].specialization;		
												break;
											}
										}
										break;
									case '4':
										cout << "\n\tEdit doctor information\n";
										getDoctors();
										break;
									default:
										cout << "\nInvalid option!\n";
								}
								cout <<"\tPress any key to Continue"; getch();
                                break;
                            case '3':
								cout << "\n\tAppointment Management:\n";
								cout << "\n\tPress 1 to list patient appointments"
									<< "\n\tPress 2 for list doctors appointments"
									<< "\n\tPress 3 for editing patients appointment"
									<< "\n\tPress 4 for editing doctor appointment"
									<< "\n\n\tEnter choice no: ";
								ch = getche();
								switch (ch){
									case '1':
										cout << "\nlist patient appointments\n";
										break;
									case '2':
										cout << "\nlist doctors appointments\n";
										break;
									case '3':
										cout << "\nediting patients appointment\n";
										break;
									case '4':
										cout << "\nediting doctor appointment\n";
										break;
									default:
										cout << "\nInvalid option!\n";
								}
								
								cout <<"\tPress any key to Continue"; getch();
                                break;
                            case '4': //City Hospital
								cout << "\n\tCity and hospital\n";
								cityHospital();
								cout <<"\tPress any key to Continue"; getch();
                                break;                             
                            case '5': //Logout
                            	ch = '7';
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

//City Hospital ------------

void cityHospital(){
	char choice;
	int num = 0;
	do{
		system("cls");
		cout << "\n\t\tAdding City/Hospital Menu\n";
		cout << "\n\tPress 1 to enter city"
			 <<	"\n\tPress 2 to enter hospital"
			 << "\n\tPress 3 to display city"
			 <<	"\n\tPress 4 to display hospital"
			 << "\n\tPress 5 to edit city"
			 <<	"\n\tPress 6 to edit hospital"
			 << "\n\tPress 7 to exit"
			 << "\n\n\tEnter choice: ";
		choice = getche();
			 
		switch(choice){
			case '1':
				cout << "\n\n\tCity Input\n";
				addCity();
				saveCity();
				break;
			case '2':
				cout << "\n\n\tHospital Input\n";
				addHospital();
				saveHospital();
				break;
			case '3':
				cout << "\n\n\tCity display\n";
				displayCity();			
				break;
			case '4':
				cout << "\n\n\tHospital display\n";
				displayHospital();
				break;
			case '5':
				cout << "\n\n\tEditing cities\n";
				editCity();
				break;
			case '6':
				cout << "\n\n\tEditing hospitals\n";
				displayHospital();
				editHospital();
				break;
			case '7':
				num = 1;
				break;
			default:
				cout << "\nInvalid Input\n";
		}
		getchar();
		getchar();
	}while(num == 0);
}

void loadCity(){
	fstream file;
	file.open(CITY, ios::in | ios::binary);
	cityCount = 0;
	
	if(file.is_open()){
		int size = 0;
		file.seekg(0, ios::end);
		size = (int)file.tellg();
		file.seekg(0, ios::beg);
		while(file.tellg() < size){
			file.read(reinterpret_cast<char*>(&cities[cityCount]), sizeof(City));
			cityCount++;
		}
		file.close();
	}
	else
		cout << "\nERROR!\n";
}

void loadHospital(){
	fstream file;
	file.open(HOSPITAL, ios::in | ios::binary);
	
	hospitalCount = 0;
	if(file.is_open()){
		int size = 0;
		file.seekg(0, ios::end);
		size = (int)file.tellg();
		file.seekg(0, ios::beg);
		while(file.tellg() < size){
			file.read(reinterpret_cast<char*>(&hospitals[hospitalCount]), sizeof(Hospital));
			hospitalCount++;
		}
		file.close();
	}
	else
		cout << "\nERROR!\n";
}

void addCity(){
	City newCity;
	cout << "\tAdd city name: "; cin >> newCity.cityName;
	newCity.cityID = cityCount + 1;
	cities[cityCount++] = newCity;
	cout << "\nCity successfully saved! City ID: " << cityCount;
}

void addHospital(){
	Hospital newHospital;
	cout << "\tAdd hospital name: "; cin >> newHospital.hospitalName;
	cout << "\tAdd hospital address: "; cin >> newHospital.hospitalAddress;
	cout << endl;
	displayCity();
	cout << endl;
	cout << "\tAdd city id: "; cin >> newHospital.cityID;
	newHospital.hospitalID = hospitalCount + 1;
	hospitals[hospitalCount++] = newHospital;
	cout << "\n\tHospital successfully saved! Hospital ID: " << hospitalCount;
}

void displayHospital(){
	if (hospitalCount == 0){
        cout << "\tNo registered hospitals found!\n";
        getchar();
    }
    else {
    	cout << endl;
    	cout <<setw(20) <<"Hospital ID" <<setw(20) <<"Hospital Name" <<setw(50) << "Address" <<setw(20) <<"City ID" << endl;
        for (int i = 0; i < hospitalCount; i++) {
            cout <<setw(20) << hospitals[i].hospitalID
				<<setw(20)	<< hospitals[i].hospitalName 
				<<setw(50)	<< hospitals[i].hospitalAddress
				<<setw(20)	<< hospitals[i].cityID	<< endl;
        }
    }
}

void displayCity(){
	if (cityCount == 0){
        cout << "\tNo cities found!\n";
        getchar();
    }
    else {
    	cout << endl;
    	cout <<setw(20) <<"City ID" <<setw(20) <<"City Name" << endl;
        for (int i = 0; i < cityCount; i++) {
            cout <<setw(20) << cities[i].cityID
				<<setw(20)	<< cities[i].cityName << endl;
        }
    }
}

void editCity(){
	
	listCities();
	
	int newID;
	cout << "\n\tEnter city ID: "; cin >> newID;
	
	fstream file;
	file.open(CITY, ios::in | ios::out | ios::binary);
	
	if(file.is_open()){
		for(int i = 0; i < cityCount; i++){
			if(newID == cities[i].cityID){
				cout << "\n\tNew City name: "; cin >> cities[i].cityName;
				int fp = sizeof(City)*i;
				file.seekg(fp);
				
				file.write(reinterpret_cast<char*>(&cities[i]), sizeof(City));
				file.close();
				cout << "\n\tCity data changed!\n";
				break;
			}
		}
	}
	else
		cout << "\nERROR!\n";
}

void editHospital(){
	
	int newID;
	cout << "\n\tEnter hospital ID: "; cin >> newID;
	
	fstream file;
	file.open(HOSPITAL, ios::in | ios::out | ios::binary);
	
	if(file.is_open()){
		for(int i = 0; i < hospitalCount; i++){
			if(newID == hospitals[i].hospitalID){
				cout << "\n\tNew hospital name: "; cin >> hospitals[i].hospitalName;
				cout << "\n\tNew hospital address: "; cin >> hospitals[i].hospitalAddress;
				listCities();
				cout << "\n\tNew City ID: "; cin >> hospitals[i].cityID;
				int fp = sizeof(Hospital)*i;
				file.seekg(fp);
				
				file.write(reinterpret_cast<char*>(&hospitals[i]), sizeof(Hospital));
				file.close();
				cout << "\n\tHospital data changed!\n";
				break;
			}
		}
	}
	else
		cout << "\nERROR!\n";
}

void saveCity(){
	fstream file;
	file.open(CITY, ios::out | ios::binary | ios::app);
	
	if(file.is_open()){
		file.write(reinterpret_cast<char*>(&cities[cityCount - 1]),sizeof(City));
		file.close();
	}
	else{
		cout << "\n\tERROR!\n";
	}
}

void saveHospital(){
	fstream file;
	file.open(HOSPITAL, ios::out | ios::binary | ios::app);
	
	if(file.is_open()){
		file.write(reinterpret_cast<char*>(&hospitals[hospitalCount - 1]),sizeof(Hospital));
		file.close();
	}
	else{
		cout << "\n\tERROR!\n";
	}
}

void listCities(){
	int j = 0;
	for(int i = 0; i < cityCount; i++){
		cout << setw(12) << "ID: " << cities[i].cityID << " | Name: " << setw(20) << cities[i].cityName;
		j++;
		if(j == 3){
			cout << endl;
			j = 0;
		}
		else
			cout << "   ||";
	}
}

