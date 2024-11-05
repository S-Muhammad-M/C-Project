#include <iostream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

#define MAX_USERS 2
#define MAX_APPOINTMENTS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define NAME_LEN 50
#define SPECIALIZATION_LEN 50
#define GENDER_LEN 10
#define pfile "pdata.dat"
#define APfile "appdata.dat"
#define docfile "docdata.dat"

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char name[NAME_LEN];
    char specialization[SPECIALIZATION_LEN];
    int docID;
} Doctor;

int doctorCount = 0;
Doctor doctors[MAX_USERS];

void setScreen();
void registerDoctor();
void displayDoctor();
void saveDoctor();
void loadDoctors();
int doctorLogin();
//string askForSecretPassword();
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
                do {
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
                            id = 1;
                            if (id >= 0) {
                                do {
									system("cls");
									cout << "\n\t\t____________________________________________________________________\n\n\n";
									cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
				                    cout <<" \n\t\t               muhammadmahmoodsyed@gmail.com [1] successfully Logged In:\n\n";
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
                            } else {
                                cout <<"Login failed!\n";
                            }
                            break;
                        case '2': // register Pateient
							cout << "\n\tGet info to regster the patient\n";
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
                break;
            case '2':
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
                break;
            case '3':
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
									cout << "\t|Press 7 to Logout	|" << endl;																	
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
//											cout << "\n\tShow or save list of all Doctors in text file\n";
											cout <<"\tPress any key to Continue"; getch();
                                            break;
                                        case '7': //Logout
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

void askForSecretPassword(char *k){
	char ch;
	int i;
	cout << "Enter pass\n";
	ch = _getch();
	while(i != PASSWORD_LEN){
		if (ch == 13)
			break;
	  	*(k+i) = ch;
	  	cout << '*';
	  	ch = _getch();
	  	i++;
	}
}

