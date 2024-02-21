/***
//// Last Build : date of submission
//// Compiler   : VS2022
//// Programmer :Lim You Wang
//// Capability : Implementing a variable size record.
//// Function   : add,search, delete, modify, display records
***/

/////////////     Includes    /////////////

#include <cstdlib> // system()
#include <conio.h> // getch()
#include <fstream>
#include <sys\stat.h> // stat(status of a file)
#include <iostream>
#include<string>
#include <regex> // Regular Expression Library
using namespace std;

/////////////     Data types    /////////////

struct Customer_Record // Customer record; is the structName
{
	//define all variable after this line
	//30th January 2024
	string FirstName;
	string LastName;
	int Age;
	string Nationality;
	string IdendificationCard;
	string PassportNumber;
	string Gender;
	string PhoneNumber;
	string EmailAddress;
	string DateOfRegistration;
	string RoomSize;
	string TypeOfBed;

	//Don't touch after this line
	bool deleted;
};

/////////////     Variable Declarations & Constants /////////////

#define CUSTOMER_FILE_NAME "Customer.txt" // name of the database file to store Customer informations

Customer_Record Customer; //variable declaration of Customer
char     choice; // for choice in menu
fstream* fs = NULL, * fs1 = NULL;// file streams for files : fs -> 'Customer', fs1 -> 'temp'
bool     deletion = false; // if any record has been deleted

/////////////     Function Prototypes    /////////////

void closeFile(fstream*); // closes a file with its pointer, then deletes the file pointer
bool isFileExist(const char*); // check if a file exists

// Function prototypes
bool isValidEmail(const string& email);
// ...

// Function to validate email address
bool isValidEmail(const string& email) {
    // Regular expression to validate email address
    const regex pattern(R"(([^@\s]+)@((?:[-a-z0-9]+\.)+[a-z]{2,}))");
    return regex_match(email, pattern);
}

/////////////     Main    /////////////
int main()
{
	while (true)
	{
		do ////// Menu //////
		{
			system("cls"); // clear screen

			cout << "\n    < Customer Database > \n\n";
			cout << "(1) Add     a new Record \n";
			cout << "(2) Search an existing Record\n";
			cout << "(3) Update an existing Record\n";
			cout << "(3) Delete an existing Record \n";
			cout << "(4) Display Records \n";
			cout << "(5) Exit \n\n";
			cout << " Enter a choice (1-5) : " << flush;
			choice = _getch();
		} while (choice < '1' || choice > '6'); // while we have no good(between 1 and 5), show menu again

		system("cls");

		// to modify, delete or display records, database file should exist, then we have some records           
		if (choice == '2' || choice == '3' || choice == '4' || choice == '5')
		{
			if (!isFileExist(CUSTOMER_FILE_NAME)) // if database file doesn't exist
			{
				cout << "\n Database file ('" << CUSTOMER_FILE_NAME << "') doesn't exist, then there are no records." << endl;
				system("pause");
				continue; // show the menu again
			}
		}

		switch (choice)
		{
			long long int recs_num; // number of records before the record for modifying(deletion)
			int id;

		case '1': ////// Add Record //////

			cout << "\n\t\t < Entering a new record > ";
			cout << "\n   Enter the following informations for the new record : ";
			//30th January 2024
			cout << endl;
			cout << "1)"<<"FirstName:";
			getline(cin, Customer.FirstName);//getline only for string data type

			cout << "2)"<<"LastName:";
			getline(cin, Customer.LastName);
			cout << "---------------------------------------------------------------------" << endl;

			cout <<"3)" << "Age:";
			cin >> Customer.Age;
			cout << "Age:" << Customer.Age << endl;
			cout << "---------------------------------------------------------------------" << endl;

			cout << "4)"<<"Nationality:";
			cout << "\n\ta.Malaysian"<<endl;
			cout << "\tb.Non-Malaysian"<< endl;
			cout << "Enter a choice:";
			cin >> Customer.Nationality;

			while ((Customer.Nationality != "a") && (Customer.Nationality != "b")) {
        		cout << "Please enter again!" << endl;
        		cout << "Enter a choice(a/b):";
        		cin >> Customer.Nationality;
    		}
    		if (Customer.Nationality == "a") {
        		Customer.Nationality = "Malaysian";
        		cout << "Nationality: Malaysian" << endl;
        		cout << "---------------------------------------------------------------------" << endl;
        		cout << "5)" << "IdendificationCard (Ex.000123-05-0012):";
        		cin >> Customer.IdendificationCard;
        		cout << "IdendificationCard:" << Customer.IdendificationCard << endl;
        		cout << "---------------------------------------------------------------------" << endl;
    		}
    		else if (Customer.Nationality == "b") {
        		Customer.Nationality = "Non-Malaysian";
        		cout << "Nationality: Non-Malaysian" << endl;
        		cout << "---------------------------------------------------------------------" << endl;
        		cout << "6)" << "PassportNumber (Ex.A123456789):";
        		cin >> Customer.PassportNumber;
        		cout << "PassportNumber:" << Customer.PassportNumber << endl;
        		cout << "---------------------------------------------------------------------" << endl;
    		}
			
			cout << "Nationality:" << Customer.Nationality << endl;
			cout << "---------------------------------------------------------------------" << endl;


			cout << "5)"<<"IdendificationCard"<<"(Ex.000123-05-0012):";
			cin >> Customer.IdendificationCard;
			cout << "IdendificationCard:" << Customer.IdendificationCard << endl;
			cout << "---------------------------------------------------------------------" << endl;

			cout << "6)" << "PassportNumber" << "(Ex.A123456789):";
			cin >> Customer.PassportNumber ;
			cout << "PassportNumber:" << Customer.PassportNumber << endl;
			cout << "---------------------------------------------------------------------" << endl;

			cout << "7)"<<"Gender:";
			cout << "\n\ta.Male" << endl;
			cout << "\tb.Female" << endl;
			cout << "Enter a choice:";
			cin >> Customer.Gender;
			while ((Customer.Gender != "a") && (Customer.Gender != "b"))
			{
				cout << "Please enter again!" << endl;
				cout << "Enter a choice(a/b):";
				cin >> Customer.Gender;
			}
			if (Customer.Gender=="a")
			{
				Customer.Gender="Male";
			}
			if (Customer.Gender =="b")
			{
				Customer.Gender="Female";
			}
			cout << "Gender:" << Customer.Gender << endl;
			cout << "---------------------------------------------------------------------" << endl;

			cout << "8)"<<"PhoneNumber:";
			cin >> Customer.PhoneNumber;
			cout << "PhoneNumber:" << Customer.PhoneNumber << endl;
			cout << "---------------------------------------------------------------------" << endl;

			cout << "9) EmailAddress:";
            cin >> Customer.EmailAddress;
                while (!isValidEmail(Customer.EmailAddress)) {
                    cout << "Invalid email address! Please enter a valid email address: ";
                    cin >> Customer.EmailAddress;
                }
            cout << "EmailAddress:" << Customer.EmailAddress << endl;

			cout << "10)"<<"DateOfRegistration(YYYY-MM-DD):";
			cin >> Customer.DateOfRegistration;
			cout << "DateOfRegistration:" << Customer.DateOfRegistration << endl;
			cout << "---------------------------------------------------------------------" << endl;

			cout << "11)" << "RoomSize:";
			cout << "\na.Small size";
			cout << "\nb.Normal size";
			cout << "\nc.Big Size" << endl;
			cout << "Enter a choice:";
			cin >> Customer.RoomSize;

			cout << "RoomSize:" << Customer.RoomSize << endl;
			cout << "---------------------------------------------------------------------" << endl;

			cout << "12)" << "TypeOfBed:";
			cout << "\na.Single Bed";
			cout << "\nb.2 Single Bed";
			cout << "\nc.Queen size Bed";
			cout << "\nd.2 Queen Size Bed";
			cout << "\ne.King Size Bed";
			cout << "\nf.2 King Size Bed";
			cout << "Enter a choice:";
			cin >> Customer.TypeOfBed;

			cout << "TypeOfBed:" << Customer.TypeOfBed << endl;


			//Don't touch after this line
			Customer.deleted = 0;

			fs = new fstream(CUSTOMER_FILE_NAME, ios::out | ios::app | ios::binary);

			if (!fs)
			{
				cout << "\n Can't open or create '" << CUSTOMER_FILE_NAME << "' file" << endl;
				system("pause");
				break;
			}

			fs->write((char*)&Customer, sizeof(Customer));

			closeFile(fs);

			cout << "\n Record added." << endl;
			system("pause");

			break;
/*
		case '2': ////// Search Record //////

		case '3': ////// Modify Record //////
		
			cout << "\n Enter Customer ID, that you want modify its informatin : ";
			cin >> id;

			fs = new fstream(CUSTOMER_FILE_NAME, ios::in | ios::out | ios::binary);

			if (!fs)
			{
				cout << "\n Can't open or create '" << CUSTOMER_FILE_NAME << "' file" << endl;
				system("pause");

				break;
			}

			recs_num = -1;

			while (fs->read((char*)&Customer, sizeof(Customer)))
			{
				recs_num++;

				if (Customer.ID == id && !Customer.deleted)
					break;
			}

			if (fs->eof()) // if (the record is not in the file || it's there but it's deleted)
			{
				cout << "\n Your specified Customer doesn't exist in file." << endl;
				closeFile(fs);
				system("pause");
				break;
			}


			cout << "\n   Enter new informations for this record : ";
			cout << "\n\n PAY_TYPE ( SALARIED : 0, HOURLY : 1 ) : ";
			cin >> Customer.PAY_TYPE;

			cout << "\n ID : ";
			cin >> Customer.ID;
			cout << "\n AGE : ";
			cin >> Customer.AGE;
			cout << "\n DEPT (one character) : ";
			cin >> Customer.DEPT;

			if (Customer.PAY_TYPE == SALARIED)
			{
				cout << "\n MONTHLY_RATE : ";
				cin >> Customer.MONTHLY_RATE;
				cout << "\n START_DATE : ";
				cin >> Customer.START_DATE;
			}

			if (Customer.PAY_TYPE == HOURLY)
			{
				cout << "\n RATE_PER_HOUR : ";
				cin >> Customer.RATE_PER_HOUR;
				cout << "\n REG_HOURS : ";
				cin >> Customer.REG_HOURS;
				cout << "\n OVERTIME_HOURS : ";
				cin >> Customer.OVERTIME_HOURS;
			}


			fs->seekp(sizeof(Customer) * recs_num, ios::beg); // go to the first of the record to be modified
			fs->write((char*)&Customer, sizeof(Customer));

			closeFile(fs);

			cout << "\n Record is modified." << endl;
			system("pause");

			break;


		case '4': ////// Delete Record //////

			cout << "\n Enter Customer's ID, for deletion : ";
			cin >> id;

			fs = new fstream(CUSTOMER_FILE_NAME, ios::in | ios::out | ios::binary);

			if (!fs)
			{
				cout << "\n Can't open or create '" << CUSTOMER_FILE_NAME << "' file." << endl;
				system("pause");
				break;
			}

			recs_num = -1;

			while (fs->read((char*)&Customer, sizeof(Customer)))
			{
				recs_num++;

				if (Customer.ID == id && !Customer.deleted) // if Customer deleted an Customer then added another one with the same ID in the same instance of program runs, deleted Customer is still there, then we should go through all the file
					break;
			}

			if (fs->eof()) // if (the record is not in the file || it's there but it's deleted)
			{
				cout << "\n Your specified Customer doesn't exist in database file." << endl;
				closeFile(fs);
				system("pause");
				break;
			}

			Customer.deleted = 1;

			fs->seekp(sizeof(Customer) * recs_num, ios::beg);
			fs->write((char*)&Customer, sizeof(Customer));

			closeFile(fs);

			deletion = true; // we have some deleted records

			cout << "\n Record is deleted." << endl;
			system("pause");

			break;


		case '4': // Display Records

			////// Print Salaried records...
			fs = new fstream(CUSTOMER_FILE_NAME, ios::in | ios::binary);

			if (!fs)
			{
				cout << "\n Can't open or create '" << CUSTOMER_FILE_NAME << "' file." << endl;
				system("pause");
				break;
			}

			// display column titles
			cout << "\n\t\t < Salaried >\n\n";
			cout << "ID\tAGE\tDEPT\tMONTHLY_RATE\tSTART_DATE\n"
				<< "-------------------------------------------------- \n";

			while (fs->read((char*)&Customer, sizeof(Customer))) // display records
			{
				if (Customer.PAY_TYPE == SALARIED && !Customer.deleted)
				{
					cout << Customer.ID << '\t';
					cout << Customer.AGE << '\t';
					cout << Customer.DEPT << '\t';
					cout << Customer.MONTHLY_RATE << "\t\t";
					cout << Customer.START_DATE << '\n';
				}
			}

			cout << "\n To see Hourly records, "; system("pause");

			closeFile(fs);

			////// Print Hourly records...                 
			system("cls");

			fs = new fstream(CUSTOMER_FILE_NAME, ios::in | ios::binary);

			if (!fs)
			{
				cout << "\n Can't open or create '" << CUSTOMER_FILE_NAME << "' file." << endl;
				system("pause");
				break;
			}

			cout << "\n\t\t\t < Hourly > \n\n";
			cout << "ID\tAGE\tDEPT\tRATE_PER_HOUR\tREG_HOURS\tOVERTIME_HOURS\n"
				<< "---------------------------------------------------------------------- \n";

			while (fs->read((char*)&Customer, sizeof(Customer_Record)))
			{
				if (Customer.PAY_TYPE == HOURLY && !Customer.deleted)
				{
					cout << Customer.ID << '\t';
					cout << Customer.AGE << '\t';
					cout << Customer.DEPT << '\t';
					cout << Customer.RATE_PER_HOUR << "\t\t";
					cout << Customer.REG_HOURS << "\t\t";
					cout << Customer.OVERTIME_HOURS << '\n';
				}
			}

			cout << "\n To see menu, "; system("pause");

			closeFile(fs);

			break;


*/
		case '6': // Exit

			if (deletion) // if there is any deletion, then update database file (create a new temp file that doesn't have deleted records, then remove the old database file and rename temp file to database file name)
			{
				cout << "\n Updating '" << CUSTOMER_FILE_NAME << "' File..." << endl;

				fs = new fstream(CUSTOMER_FILE_NAME, ios::in | ios::binary);
				if (!fs)
				{
					cout << "\n Can't open '" << CUSTOMER_FILE_NAME << "' file, then Updating is incomplete." << endl;
					system("pause");

					system("cls");
					return 1;
				}

				fs1 = new fstream("temp", ios::out | ios::binary);
				if (!fs1)
				{
					cout << "\n Can't create temp file, then Updating is incomplete." << endl;
					system("pause");

					closeFile(fs);
					system("cls");
					return 1;
				}

				// write nondeleted records to the temp file
				while (fs->read((char*)&Customer, sizeof(Customer)))
					if (!Customer.deleted)
						fs1->write((char*)&Customer, sizeof(Customer));

				closeFile(fs);
				closeFile(fs1);

				if (remove(CUSTOMER_FILE_NAME) == -1) // if there is an error
				{
					cout << "\n Can't delete '" << CUSTOMER_FILE_NAME << "' file, then Updating is incomplete." << endl;
					system("pause");

					system("cls");
					return 1;
				}


				struct stat st; // to check size of the temp file
				int res = stat("temp", &st);

				if (st.st_size == 0) // if all of records are deleted then the temp file size is zero                        
					remove("temp"); // we have no records, then no database file is needed, just delete the temp file
				else
					if (rename("temp", CUSTOMER_FILE_NAME))
					{
						cout << "\n Can't rename temp file, then Updating is incomplete." << endl;
						system("pause");

						system("cls");
						return 1;
					}

				cout << "\n Updating database file completed." << endl;
				system("pause");
			}

			system("cls");
			return 0;

			break;
		} // end 'switch'
	} // end 'while'

	return 0;
} // end 'main()'


/////////////     Function Definitions    /////////////

void closeFile(fstream* fs)
{
	fs->close(); // close the file
	delete fs;
	fs = NULL;
}


bool isFileExist(const char* file_name)
{
	struct stat st; // to check status of file
	int res = stat(file_name, &st);
	return (res == 0); // if file exists     
}
