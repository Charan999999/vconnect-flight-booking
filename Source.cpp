#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "Header.h"
#include<windows.h>
#include<string>
#include<bits/stdc++.h>
using namespace std;



void FlightReservationMenu(Airport &a, Offers &o, Planes &p)
{
	customer obj;
	int choice = 0;
	Ticket t;
	while (1)
	{
		system("CLS");
		cout << "~~~~~~~~~~~~~~~~~~( RESERVATION SYSTEM )~~~~~~~~~~~~~~~~~\n";
		cout << "___________________________________________\n\n";
		cout << "|Press 1 for search for a destination" << endl;
		cout << "|Press 2 for Reserve Flight" << endl;
		cout << "|Press 3 for Cancel Reservation" << endl;
		cout << "|Press 4 for Change Reservation" << endl;
		cout << "|Press 5 for view All Reservation Passenger" << endl;
		cout << "|Press 6 for back" << endl;
		cout << "___________________________________________\n";

		cout << "Enter Your Choice: ";
		cin >> choice;
		if (choice == 1)
		{
			Flight f;
			string destination;
			cin.ignore();
			cout << "Enter Destination You want to Go: ";
			getline(cin, destination);
			cout << endl;
			bool flag = f.searchfromdestination(destination);
			cout << endl;
			if (!flag)
			{
				cout << endl;
				cout << "No Flight Available" << endl;
			}
			Sleep(1500);

		}
		else if (choice == 2)
		{
			bool flag = false;
			bool flag1 = false;
			int customerId = 0;
			string name;
			string phone;
			string DOB;
			int NoOfFlights = 0;
			cout << "Enter Name: ";
			cin >> name;
			cout << "Enter ID: ";
			cin >> customerId;
			cout << "Enter Phone Number: ";
			cin >> phone;
			cout << "Enter Date of Birth: ";
			cin >> DOB;
			do
			{
				ifstream fin;
				fin.open("Flight.txt");
				cout << "Enter Flight Number: ";
				cin >> NoOfFlights;

				int flight;
				string s;

				if (!fin)
				{
					cout << "Flight File is Missing" << endl;
				}
				else{
					while (fin >> flight)
					{
						getline(fin, s, '\n');

						if (flight == NoOfFlights)
						{
							flag1 = true;
						}
					}
				}
				if (flag1 == false)
				{
					cout << "No Flight Present!!!!!!" << endl;
					cout << "Please Enter Correct Flight Again!!!" << endl;
					cout << endl;
				}
				fin.close();
			} while (flag1 != true);

			if (flag1)
			{
				cout << endl;
				flag = obj.setdata(name, customerId, phone, DOB, NoOfFlights);
				cout << endl;
				if (flag)
				{
					t.getDiscount(flag, name, customerId, phone, NoOfFlights, a, o, p);
				}
				else {
					t.getDiscount(flag, name, customerId, phone, NoOfFlights, a, o, p);
				}
			}
			system("pause");
			cout << endl;
		}
		else if (choice == 3)
		{
			int ticket = 0;
			int seat = 0;
			int flight = 0;
			bool flag = false;
			do {
				cout << endl << endl;
				cout << "Enter Your Ticket Number: ";
				cin >> ticket;
				cout << "Enter your seat Number: ";
				cin >> seat;
				cout << "Enter your flight Number: ";
				cin >> flight;

				flag = t.check(ticket, seat, flight);

				if (flag == false)
				{
					cout << "Invalid Details" << endl;
					cout << "Enter Again" << endl;
				}
			} while (flag != true);

			t.cancelticket(ticket, seat, flight);
			bool flag1 = false;
			flag1 = p.cancelseat(seat, flight);

			if (flag1 == true)
			{
				cout << "*******************************************" << endl;
				cout << "\nTicket Cancelled Sucessfully" << endl;
				cout << endl;
			}
		}
		else if (choice == 4)
		{
			int ticket = 0;
			int seat = 0;
			int flight = 0;
			bool flag = false;
			do {
				cout << endl << endl;
				cout << "Enter Your Ticket Number: ";
				cin >> ticket;
				cout << "Enter your seat Number: ";
				cin >> seat;
				cout << "Enter your flight Number: ";
				cin >> flight;

				flag = t.check(ticket, seat, flight);

				if (flag == false)
				{
					cout << "Invalid Details" << endl;
					cout << "Enter Again" << endl;
				}
			} while (flag != true);

			bool flag1 = false;
			bool flag2 = false;
			flag1 = p.cancelseat(seat, flight);
			p.reserveseat(flight);
			if (flag1 == true)
			{
				do {
					cout << "Select Your New Seat Number: ";
					cin >> seat;

					flag2 = p.searchseat(flight, seat);
				} while (flag2 != true);

				if (flag2 == true)
				{
					t.updateticket(ticket, seat);
				}
			}
			system("pause");
		}
		else if (choice == 5)
		{
			ReservedFlightPassenger *r=new ReservedFlightPassenger;
			r->ReadFormDatastructure();
			delete r;
			system("pause");
		}
		else if (choice != 6)
		{
			cout << "Invalid Input!!!!!" << endl;
			Sleep(2000);

		}
		else {
			break;
		}
	}
}

void CustomerMenu(customer &c)
{
	int choice = 0;
	do {
		system("CLS");

		cout << "~~~~~~~~~~~~~~~~~~( CUSTOMER SYSTEM )~~~~~~~~~~~~~~~~~\n";
		cout << "___________________________________________\n\n";
		cout << "|Press 1 for Add Customer" << endl;
		cout << "|Press 2 for Update Customer info" << endl;
		cout << "|Press 3 for Delete Customer" << endl;
		cout << "|Press 4 for Search Customer Profile" << endl;
		cout << "|Press 5 for View All Customer Data" << endl;
		cout << "|Press 6 for Exit From Customer" << endl;
		cout << "___________________________________________\n";

		cout << "Enter Your Choice: ";
		cin >> choice;
		if (choice == 1)
		{
			int customerId = 0;
			string name;
			string phone;
			string DOB;
			int NoOfFlights = 0;
			cout << "Enter Name: ";
			cin >> name;
			cout << "Enter ID: ";
			cin >> customerId;
			cout << "Enter Phone Number: ";
			cin >> phone;
			cout << "Enter Date of Birth: ";
			cin >> DOB;
			cout << "Enter Number of Flights: ";
			cin >> NoOfFlights;
			c.setdata(name, customerId, phone, DOB, NoOfFlights);
			cout << endl;
			system("pause");
		}
		else if (choice == 2)
		{
			string name;
			cout << "Enter Name You want to update: ";
			cin >> name;
			c.updateData(name);

			cout << endl;
			system("pause");
		}
		else if (choice == 3)
		{
			string name;
			cout << "Enter Customer Name You want to Delete: ";
			cin >> name;
			bool x = c.deletedata(name);
			if (!x)
			{
				cout << "\nCustomer Not found\n";

			}
			else
			{
				cout << "\nDelete Successfully\n";
			}
			system("pause");

		}
		else if (choice == 4)
		{
			cout << "Enter name for Search :"; string n; cin >> n;
			cout << endl;
			c.SearchData(n);
			cout << endl << endl;
			system("pause");

		}
		else if (choice == 5)
		{
			c.ShowAllCustomer();
			system("pause");

		}
		else if (choice != 6)
		{
			cout << "Invalid Input!!!!!!" << endl;
			Sleep(1000);
			system("pause");
		}
		else
		{
			break;
		}
	} while (true);
}

void FlightMenu(Flight &f)
{
	int choice = 0;
	while (1)
	{
		system("CLS");
		cout << "~~~~~~~~~~~~~~~~~~( FLIGHT SYSTEM )~~~~~~~~~~~~~~~~~\n";
		cout << "_________________________________________\n\n";
		cout << "|Press 1 for Add Flight" << endl;
		cout << "|Press 2 for Update Flight" << endl;
		cout << "|Press 3 for Delete Flight" << endl;
		cout << "|Press 4 for View Flight" << endl;
		cout << "|Press 5 for Exit from Flight\n";
		cout<<"____________________________________________\nSelect Option:" << endl; cin >> choice;
		if (choice == 1)
		{
			string sourcecity; string destinationcity; string dayz; string time; string Plane; int flightno;

			cout << "Enter Flight Number: ";
			cin >> flightno;
			cin.ignore();
			cout << "Enter Plane: ";
			getline(cin, Plane);
			cout << "Enter Source City: ";
			getline(cin, sourcecity);
			cout << "Enter Destination City: ";
			getline(cin, destinationcity);
			cout << "Enter Dayz: ";
			cin.ignore();
			getline(cin, dayz);
			cout << "Enter Time: ";
			cin >> time;
			cout << endl;
			bool flag = f.add(Plane, sourcecity, destinationcity, dayz, time, flightno, true);
			if (flag)
			{
				cout << "Flight Added SUccessfully\n";
			}
			else
			{
				cout << "Flight Not Found\n";
			}
			system("pause");
		}
		else if (choice == 2)
		{
			int flightno;
			cout << "Enter Flight Number to search for Update: ";
			cin >> flightno;
			bool flag = f.update(flightno);
			if (flag)
			{
				cout << "Flight Updated SUccessfully\n";
			}
			else
			{
				cout << "Flight Not Found\n";
			}
			system("pause");
		}
		else if (choice == 3)
		{
			int flightno;
			cout << "Enter Flight Number to search for Delete: ";
			cin >> flightno;
			bool flag = f.deleted(flightno);
			if (flag)
			{
				cout << "Flight deleted SUccessfully\n";
			}
			else
			{
				cout << "Flight Not Found\n";
			}
			system("pause");

		}
		else if (choice == 4)
		{
			cout << endl;
			f.view();
			cout << endl;
			system("pause");

		}
		else if (choice != 5)
		{
			cout << "Invalid Number!!!!!!" << endl;
			Sleep(1500);
		}
		else
		{
			break;
		}
	}
}

void welcome()
{
	ifstream ifs("welcome.txt");
	string Lines = "";
	if (ifs)
	{

		while (ifs.good())
		{
			string TempLine;
			getline(ifs, TempLine);
			TempLine += "\n";

			Lines += TempLine;
		}

		cout << Lines;
	}
	cout << "\n";
	ifs.close();
	cout << "\t\t\t\t\t~~~~~~~~~~~~~~~~~~~( TO FLIGHT RESERVATION SYSTEM )~~~~~~~~~~~~~~~~~~~\n\n";

}

void exitArt()
{
	ifstream ifs("exit art.txt");
	string Lines = " ";
	if (ifs)
	{
		while (ifs.good())
		{
			string TempLine;
			getline(ifs, TempLine);
			TempLine += "\n";

			Lines += TempLine;
		}

		cout << Lines;

	}
	cout << "\n\t  \t\t\t\t\t\t\t";
	ifs.close();
	exit(0);
}

void systemmenu(Flight &f, customer &c, Airport &a, Offers &o, Planes &p, Ticket &t)
{
	int choice = 0;
	while (true)
	{
		system("CLS");
		welcome();
		cout << "______________________________________________\n\n";
		cout << " |Press 1 for Flight Reservation" << endl;
		cout << " |Press 2 for Customer" << endl;
		cout << " |Press 3 for Flight" << endl;
		cout << " |Press 4 for Setup System Data" << endl;
		cout << " |Press 5 for Saved Datain text Files" << endl;
		cout << " |Press 6 for Exit" << endl;
		cout << "______________________________________________\n";

		cout << "Select Option :"; cin >> choice;
		if (choice == 1)
		{
			FlightReservationMenu(a, o, p);
		}
		else if (choice == 2)
		{
			CustomerMenu(c);
		}
		else if (choice == 3)
		{
			FlightMenu(f);
		}
		else if (choice == 4)
		{
			f.ReadFromDatabase();
			c.ReadFromDatabase();
			a.ReadFromDatabase();
			o.ReadFromDatabse();
			p.ReadFromDatabase();
			t.ReadFromDatabase();
			Sleep(1500);

		}
		else if (choice == 5)
		{
			f.WriteInDatabase();
			c.WriteIndatabase();
			o.WriteInDatabase();
			p.WriteInDatabase();
			a.WriteInDatabase();
			Sleep(1500);

		}
		else if (choice != 6)
		{
			cout << "invalid Enter !!!!!!\n";
			Sleep(1000);
			system("CLS");

			cout << "\nSelect the correct Option\n";
		}
		else
		{
			system("CLS");
			exitArt();

			break;
		}
	}
}

int main()
{

	Airport a;
	Flight f;
	customer c;
	Ticket t;
	Planes p;
	Offers o;
	systemmenu(f, c, a, o, p, t);


}