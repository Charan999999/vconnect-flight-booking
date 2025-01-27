#include<iostream>
#include<string>
#include<fstream>
#include"Node.h"
using namespace std;

class ReservedFlightPassenger {
public:
	ReservedFlightPassenger(){
		root = NULL;
	}
	ReservedFlighhtNode * insert(ReservedFlighhtNode * root,int Tn,int Pid,string n,string p,int fn,int sn){
		if (root == NULL)
		{
			root = new ReservedFlighhtNode();
			root->ticketNumber = Tn;
			root->Flightno = fn;
			root->seatno = sn;
			root->name = n;
			root->passengerid = Pid;
			root->phone = p;
			root->left = NULL;
			root->right = NULL;
		}
		else if (root->ticketNumber > Tn)
		{
			root->left = insert(root->left, Tn, Pid, n, p, fn, sn);
		}
		else if (root->ticketNumber < Tn)
		{
			root->right = insert(root->right, Tn, Pid, n, p, fn, sn);
		}
		return root;

	}
	void ReadFormDatastructure(){
		ifstream fin("Ticket.txt");
		if (!fin.is_open() )
		{
			cout << "Ticket File Missing\n";
		}
		else
		{
			int fn, tn, sn, pid; string n, p; char space;
			while (fin >> tn)
			{
				fin >> pid;
				fin.get(space);
				getline(fin, n, ' ');
				fin.get(space);
				getline(fin, p, ' ');
				fin >> fn;
				fin >> sn;
				if (root == NULL)
				{
					root = insert(root, tn, pid, n, p, fn, sn);
				}
				else
				{
					insert(root, tn, pid, n, p, fn, sn);
				}
			}
			fin.close();
			Inorder(root);
		}
	}
	void Inorder(ReservedFlighhtNode* root)
	{
		if (root == NULL)
		{
			return;
		}
		else {
			Inorder(root->left);
			cout << endl;
			cout << "Passenger Ticket No :" << root->ticketNumber << endl;
			cout << "Passenger Name :" << root->name << endl;
			cout << "Passenger Id :" << root->passengerid << endl;
			cout << "Passenger Phone Number :" << root->phone << endl;
			cout << "Passenger Flight nUmber: " << root->Flightno << endl;
			cout << "Passenger Seat No :" << root->seatno << endl;
			cout << endl;
			Inorder(root->right);
		}
	}

private:
	ReservedFlighhtNode *root;
};


class Airport {
public:
	Airport()
	{
		head = NULL;
	}
	~Airport()
	{
		delete head;
		head = NULL;
	}
	void showAirportinfo(int flight)
	{
		ifstream fin;
		fin.open("Airport.txt");
		char ignore;

		if (!fin)
		{
			cout << "Airport File is Missing" << endl;
		}
		else {
			AirportNode* temp = head;
			while (fin >> temp->flight)
			{
				if (flight == temp->flight)
				{
					fin >> ignore;
					getline(fin, temp->SourceairportName, ',');
					getline(fin, temp->DestinationairportName, ')');
					fin >> ignore;
					getline(fin, temp->Sourcecountry, ',');
					getline(fin, temp->Destinationcountry, ')');
					fin.ignore();
					getline(fin, temp->weatherCondition, ' ');
					getline(fin, temp->timeFromBeirut, '\n');

					cout << endl;
					cout << "*************Your Airport Information " << endl;
					cout << "FROM " << temp->SourceairportName << " to " << temp->DestinationairportName << endl;
					cout << "FROM " << temp->Sourcecountry << " to " << temp->Destinationcountry << endl;
					cout << "Weather Condition of That Country: " << temp->weatherCondition << endl;
					cout << "Journey Time: " << temp->timeFromBeirut << " Hours" << endl;
					cout << endl;
				}
				else {
					fin >> ignore;
					getline(fin, temp->SourceairportName, ',');
					getline(fin, temp->DestinationairportName, ' ');
					getline(fin, temp->Sourcecountry, ',');
					getline(fin, temp->Destinationcountry, ' ');
					getline(fin, temp->weatherCondition, ' ');
					getline(fin, temp->timeFromBeirut, '\n');
				}
			}

		}
	}
	
	void ReadFromDatabase(){
		ifstream fin("Airport.txt");
		if (!fin.is_open())
		{
			cout << "Airport file Missing!!!!!!!\n";
		}
		else
		{
			string SourceairportName, DestinationairportName, Sourcecountry, Destinationcountry, weatherCondition, timeFromBeirut;
			int flight;
			while (fin >> flight)
			{

				getline(fin, SourceairportName, ',');
				getline(fin, DestinationairportName, ')');
				getline(fin, Sourcecountry, ',');
				getline(fin, Destinationcountry, ' ');
				getline(fin, weatherCondition, ' ');
				getline(fin, timeFromBeirut, '\n');
				insert(flight, SourceairportName, DestinationairportName, Sourcecountry, Destinationcountry, weatherCondition, timeFromBeirut);
			}
			cout << "Airport Data read Successfully!!!!!!\n";
		}
	}
	void WriteInDatabase(){
		if (head == NULL)
		{
			cout << "AirPort Run time data not exist\n";
		}
		else
		{
			ofstream fout("Airport.txt");
			AirportNode* temp = head;
			while (temp != NULL)
			{
				fout << temp->flight  << temp->SourceairportName << "," << temp->DestinationairportName << ")" << temp->Sourcecountry << "," << temp->Destinationcountry << " " << temp->weatherCondition << " " << temp->timeFromBeirut << endl;
				temp = temp->next;
			}
			fout.close();
			cout << "Airport Data Write Successfully!!!!!!\n";
		}
	}

	void DisplayAllAirport(){
		AirportNode *temp = head;
		while (temp != NULL)
		{
			cout << endl;
			cout << "FROM " << temp->SourceairportName << " to " << temp->DestinationairportName << ")" << endl;
			cout << "FROM " << temp->Sourcecountry << " to " << temp->Destinationcountry << endl;
			cout << "Weather Condition of That Country: " << temp->weatherCondition << endl;
			cout << "Journey Time: " << temp->timeFromBeirut << " Hours" << endl;
			cout << endl;
			temp = temp->next;
		}

	}
	
	void insert(int flight, string SourceairportName, string DestinationairportName, string Sourcecountry, string Destinationcountry, string weatherCondition, string timeFromBeirut){
		AirportNode * temp = new AirportNode;
		temp->DestinationairportName = DestinationairportName;
		temp->Destinationcountry = Destinationcountry;
		temp->flight = flight;
		temp->SourceairportName = SourceairportName;
		temp->Sourcecountry = Sourcecountry;
		temp->weatherCondition = weatherCondition;
		temp->timeFromBeirut = timeFromBeirut;
		temp->next = NULL;
		if (head == NULL)
		{
			head = temp;
		}
		else
		{
			AirportNode *treverse = head;
			while (treverse->next != NULL)
			{
				treverse = treverse->next;
			}
			treverse->next = temp;
		}
	}



private:
	AirportNode * head;
};

class Planes {
public:
	Planes()
	{
		head == NULL;
	}

	~Planes()
	{
		delete head; head == NULL;
	}

	bool cancelseat(int seat, int flight)
	{
		ifstream fin;
		fin.open("Planes.txt");
		bool flag = false;
		bool flag1 = false;

		ofstream fout1;
		fout1.open("temp.txt", ios::app);

		if (!fin)
		{
			cout << "Planes File is Missing" << endl;
		}
		else {
			int planeId;
			int flightno;
			string planename;
			string seatno;
			int firstclassseat;
			int secondclassseat;
			while (fin >> planeId)
			{
				string ch;
				fin >> flightno;
				fin.ignore();
				if (flightno == flight)
				{
					getline(fin, planename, ':');
					fin >> firstclassseat;
					if (seat <= 10)
					{
						fout1 << planeId << " ";
						fout1 << flightno << " ";
						fout1 << planename << ": ";
						firstclassseat += 1;
						fout1 << firstclassseat << " ";
					}
					else {
						fout1 << planeId << " ";
						fout1 << flightno << " ";
						fout1 << planename << ": ";
						fout1 << firstclassseat << " ";
					}
					fin >> secondclassseat;
					if (seat <= 20 && seat > 10)
					{
						secondclassseat += 1;
						fout1 << secondclassseat << " ";
					}
					else {
						fout1 << secondclassseat << " ";
					}
					fin.ignore();
					int count = 0;
					count = secondclassseat + firstclassseat;
					char s;
					fin >> s;
					fout1 << "|";
					if (seat == 1)
					{
						fout1 << seat << "|";
						for (int i = 1; i < count; i++)
						{
							getline(fin, ch, '|');
							int v = stof(ch);
							fout1 << ch << "|";
						}
						flag = true;
					}
					else if (seat == 20)
					{
						for (int i = 1; i < count; i++)
						{
							getline(fin, ch, '|');
							int v = stof(ch);
							fout1 << ch << "|";
						}
						fout1 << seat << "|";
						flag = true;
					}
					else
					{
						int num = 0;
						for (int i = 1; i < count; i++)
						{
							getline(fin, ch, '|');
							int v = stof(ch);

							if (flag1 == false)
							{
								num = checkseat(seat, flight, v);
							}
							if (num + v == seat)
							{
								fout1 << ch << "|";
								fout1 << seat << "|";
								flag1 = true;
								flag = true;
							}
							else
							{
								fout1 << ch << "|";
							}
						}
					}
					fout1 << endl;
				}
				else {
					fout1 << planeId << " ";
					fout1 << flightno << " ";
					getline(fin, planename, ':');
					fout1 << planename << ": ";
					fin >> firstclassseat;
					fout1 << firstclassseat << " ";
					fin >> secondclassseat;
					fout1 << secondclassseat << " ";
					fin.ignore();
					getline(fin, seatno, '\n');
					fout1 << seatno << endl;
				}
			}
		}
		fin.close();
		fout1.close();

		remove("Planes.txt");
		rename("temp.txt", "Planes.txt");

		return flag;
	}

	int checkseat(int seat, int flight, int num)
	{
		int planeId;
		int flightno;
		string planename;
		string seatno;
		int firstclassseat;
		int secondclassseat;
		ifstream fin;
		fin.open("Planes.txt");
		bool flag = false;

		if (!fin)
		{
			cout << "Planes File is Missing" << endl;
		}
		else {
			while (fin >> planeId)
			{
				string ch;
				fin >> flightno;
				fin.ignore();
				if (flightno == flight)
				{
					getline(fin, planename, ':');
					fin >> firstclassseat;
					fin >> secondclassseat;
					fin.ignore();
					int count = 0;
					count = secondclassseat + firstclassseat;
					char s;
					fin >> s;
					for (int i = 0; i < count - 1; i++)
					{
						getline(fin, ch, '|');
						int v = stof(ch);

						if (v > num)
						{
							for (int s = seat; s >= 1; s--)
							{
								if (s > v)
								{
									if (s - v == seat)
									{
										flag = true;
										fin.close();
										return s;
										break;
									}
									else if (v + s == seat)
									{
										flag = true;
										fin.close();
										return s;
										break;
									}
								}
								else if (v > s)
								{
									if (v - s == seat)
									{
										flag = true;
										fin.close();
										return s;
										break;
									}
									else if (v + s == seat)
									{
										flag = true;
										fin.close();
										return s;
										break;
									}
								}
							}
						}
					}
				}
				else {
					getline(fin, planename, ':');
					fin >> firstclassseat;
					fin >> secondclassseat;
					fin.ignore();
					getline(fin, seatno, '\n');
				}
			}
		}
	}

	bool searchseat(int flight, int seat)
	{
		int planeId;
		int flightno;
		string planename;
		string seatno;
		int firstclassseat;
		int secondclassseat;
		ifstream fin;
		fin.open("Planes.txt");
		bool flag = false;

		ofstream fout;
		fout.open("temp.txt", ios::app);

		if (!fin)
		{
			cout << "Planes File is Missing" << endl;
		}
		else {
			while (fin >> planeId)
			{
				string ch;
				fin >> flightno;
				fin.ignore();
				if (flightno == flight)
				{
					getline(fin, planename, ':');
					fin >> firstclassseat;
					if (seat <= 10)
					{
						fout << planeId << " ";
						fout << flightno << " ";
						fout << planename << ": ";
						firstclassseat -= 1;
						fout << firstclassseat << " ";
					}
					else {
						fout << planeId << " ";
						fout << flightno << " ";
						fout << planename << ": ";
						fout << firstclassseat << " ";
					}
					fin >> secondclassseat;
					if (seat <= 20 && seat > 10)
					{
						secondclassseat -= 1;
						fout << secondclassseat << " ";
					}
					else {
						fout << secondclassseat << " ";
					}
					fin.ignore();
					int count = 0;
					count = secondclassseat + firstclassseat + 1;
					char s;
					fin >> s;
					fout << "|";
					for (int i = 0; i < count; i++)
					{
						getline(fin, ch, '|');
						int v = stof(ch);
						if (v == seat)
						{
							flag = true;
						}
						else {
							fout << ch << "|";
						}
					}
					fout << endl;
				}
				else {
					fout << planeId << " ";
					fout << flightno << " ";
					getline(fin, planename, ':');
					fout << planename << ": ";
					fin >> firstclassseat;
					fout << firstclassseat << " ";
					fin >> secondclassseat;
					fout << secondclassseat << " ";
					fin.ignore();
					getline(fin, seatno, '\n');
					fout << seatno << endl;
				}
			}
		}
		fin.close();
		fout.close();

		remove("Planes.txt");
		rename("temp.txt", "Planes.txt");

		if (flag == true)
		{
			cout << endl;
			cout << "Seat Booked" << endl;
			cout << endl;
			return true;
		}
		else
		{
			cout << "Seat Already Booked" << endl;
			cout << "Select Any Other Seat" << endl;
			cout << endl;

			ifstream fin;
			fin.open("Planes.txt");

			ofstream fout;
			fout.open("temp.txt", ios::app);

			if (!fin)
			{
				cout << "Planes File is Missing" << endl;
			}
			else {
				while (fin >> planeId)
				{
					string ch;
					fin >> flightno;
					fin.ignore();
					if (flightno == flight)
					{
						getline(fin, planename, ':');
						fin >> firstclassseat;
						if (seat <= 10)
						{
							fout << planeId << " ";
							fout << flightno << " ";
							fout << planename << ": ";
							firstclassseat += 1;
							fout << firstclassseat << " ";
						}
						else {
							fout << planeId << " ";
							fout << flightno << " ";
							fout << planename << ": ";
							fout << firstclassseat << " ";
						}
						fin >> secondclassseat;
						if (seat <= 20 && seat > 10)
						{
							secondclassseat += 1;
							fout << secondclassseat << " ";
						}
						else {
							fout << secondclassseat << " ";
						}
						fin.ignore();
						int count = 0;
						count = secondclassseat + firstclassseat;
						char s;
						fin >> s;
						fout << "|";
						for (int i = 0; i < count; i++)
						{
							getline(fin, ch, '|');
							int v = stof(ch);
							if (v == seat)
							{
								flag = false;
							}
							else {
								fout << ch << "|";
							}
						}
						fout << endl;
					}
					else {
						fout << planeId << " ";
						fout << flightno << " ";
						getline(fin, planename, ':');
						fout << planename << ": ";
						fin >> firstclassseat;
						fout << firstclassseat << " ";
						fin >> secondclassseat;
						fout << secondclassseat << " ";
						fin.ignore();
						getline(fin, seatno, '\n');
						fout << seatno << endl;
					}
				}
			}
			fin.close();
			fout.close();

			remove("Planes.txt");
			rename("temp.txt", "Planes.txt");
			return false;
		}
	}

	void reserveseat(int flight)
	{
		ifstream fin;
		fin.open("Planes.txt");

		if (!fin)
		{
			cout << "Planes File is Missing" << endl;
		}
		else {
			int planeId;
			int flightno;
			string planename;
			string seatno;
			int firstclassseat;
			int secondclassseat;
			while (fin >> planeId)
			{
				fin >> flightno;
				fin.ignore();
				if (flightno == flight)
				{
					getline(fin, planename, ':');
					fin >> firstclassseat;
					fin >> secondclassseat;
					getline(fin, seatno, '\n');

					cout << "Plane Name: " << planename << endl;
					cout << "Total First Class Ticket: " << firstclassseat << endl;
					cout << "Total Second Class Ticket: " << secondclassseat << endl;
					cout << endl;
					cout << seatno;

					cout << endl;
				}
				else {
					getline(fin, planename, ':');
					fin >> firstclassseat;
					fin >> secondclassseat;
					fin.ignore();
					getline(fin, seatno, '\n');
				}
			}
		}
		fin.close();
	}

	void ReadFromDatabase()
	{
		ifstream fin("Planes.txt");
		if (fin.is_open())
		{
			int arr[20]; int size = 0;
			int fcs; int fn; int pi; string pn; string sn; int scs;
			while (fin >> pi)
			{
				fin >> fn;
				getline(fin, pn, ':');
				fin >> fcs >> scs;
				getline(fin, sn, '\n');
				insert(fcs, fn, pi, pn, sn, scs);
			}
			fin.close();
			cout << "Plane Data Read successfully!!!!!\n";
		}
		else
		{
			cout << "Plane File Missig Error\n";
		}
	}
	void WriteInDatabase(){
		if (head==NULL)
		{
			cout << "planes Run time data not exist\n";
		}
		else
		{
			ofstream fout("Planes.txt");
			PlaneNode * temp = head;
			while (temp !=NULL)
			{
				fout << temp->planeId << " " << temp->flightno << temp->planename << ": " << temp->firstclassseat << " " << temp->secondclassseat  << temp->seatno << endl;
				temp = temp->next;
			}
			fout.close();
			cout << "Plane Data Write Successfully!!!!!!\n";
		}
	}

	void insert(int fcs, int fn, int pi, string pn, string sn, int scs)
	{
		PlaneNode * temp = new PlaneNode();
		temp->firstclassseat = fcs;
		temp->flightno = fn;
		temp->planeId = pi;
		temp->planename = pn;
		temp->seatno = sn;
		temp->secondclassseat = scs;
		temp->next = NULL;
		if (head == NULL)
		{
			head = temp;
		}
		else
		{
			PlaneNode *p = head;
			while (p->next != NULL)
			{
				p = p->next;
			}
			p->next = temp;
		}
	}

	void display(){
		PlaneNode *p = head;
		while (p != NULL)
		{
			cout << p->planeId << " " << p->flightno << " " << p->planename << ": " << p->firstclassseat << " " << p->secondclassseat << p->seatno << endl;
			p = p->next;
		}
	}

private:
	PlaneNode * head;
};

class Offers {
public:
	Offers()
	{

	}
	~Offers()
	{

	}
	int giveoffer(string Type, int flight, string price)
	{
		ifstream fin;
		fin.open("Offers.txt");
		int x = 0;
		int DiscountAmount = 0;

		if (!fin)
		{
			cout << "Offers File is Missing" << endl;
		}
		else {
			int Price = stof(price);
			bool flag = false;
			if (!arr[0].size)
			{
				cout << "Offers List is empty Please read its dataStructre from DB\n";
				return -1e9;
			}
			else
			{
				int offerid;
				int flightno;
				string offertype;
				string price1;
				while (fin >> offerid)
				{
					fin >> flightno;
					if (flightno == flight)
					{
						fin.ignore();
						getline(fin, offertype, ' ');
						if (offertype == Type)
						{
							getline(fin, price1, '\n');
							int Amount = stof(price1);
							cout << "As a " << Type << " Customer " << " You will get a Discount of: " << Amount << endl;
							DiscountAmount = Price - Amount;
							flag = true;
						}
						else
						{
							getline(fin, price1, '\n');
						}
					}
					else
					{
						fin.ignore();
						getline(fin, offertype, ' ');
						getline(fin, price1, '\n');
					}
				}
			}
			fin.close();
			cout << endl;
			if (flag == true)
			{
				cout << "Amount to be Paid is: " << DiscountAmount << endl;
				return DiscountAmount;
			}
			cout << endl;
			if (flag == false)
			{
				cout << "No Discount found for this Flight For " << Type << " Customers" << endl;
				cout << endl;
				cout << "Amount to be Paid is: " << Price << endl;
				return Price;
			}
			cout << endl;
		}
	}
	void ReadFromDatabse(){
		ifstream fin;
		fin.open("offers.txt");
		bool flag = false;
		char ignore = '\0';

		if (!fin)
		{
			cout << "Offers File is Missing" << endl;
		}
		else
		{
			for (int i = 0; i < 14; i++)
			{
				fin >> arr[i].offerId;
				fin >> arr[i].FlightNum;
				fin.get(ignore);
				getline(fin, arr[i].OfferType, ' ');
				getline(fin, arr[i].amount, '\n');
				arr[i].size++;
			}

			cout << "Offer Data read Successfully!!!!!!!!\n";
		}
		fin.close();
	}
	void WriteInDatabase(){
		if (!arr[0].size)
		{
			cout << "Offers Runtime  data not exist\n";
		}
		else
		{
			ofstream fout("Offers.txt");
			for (int i = 0; i < 14; i++)
			{
				fout << arr[i].offerId << " " << arr[i].FlightNum << " " << arr[i].OfferType << " " << arr[i].amount << endl;
			}
			fout.close();
			cout << "Offer data write Successfully!!!!!\n";
		}
	}
	void viewAllOffers(){
		if (arr[0].size)
		{
			for (int i = 0; i < 10; i++)
			{
				cout << endl;
				cout << "Offer id :" << arr[i].offerId << endl;
				cout << "Offer Num :" << arr[i].FlightNum << endl;
				cout << "Offer type :" << arr[i].OfferType << endl;
				cout << "Price :" << arr[i].amount << endl;
				cout << endl;
			}
		}
		else
		{
			cout << "Offers List is empty Please read its dataStructre from DB\n";
		}
	}
private:
	OfferList arr[14];
};

class Ticket {
public:
	Ticket()
	{
		size = 0;

	}
	void updateticket(int Ticket, int seatnumber)
	{
		int ticket;
		int Id;
		string name;
		string phone;
		int flight;
		int seat;

		ifstream fin;
		fin.open("Ticket.txt");

		ofstream fout;
		fout.open("temp.txt", ios::app);

		if (!fin)
		{
			cout << "Ticket File is Missing" << endl;
		}
		else {
			while (fin >> ticket)
			{
				fout << ticket << " ";
				fin >> Id;
				fout << Id << " ";
				fin.ignore();
				getline(fin, name, ' ');
				fout << name << " ";
				getline(fin, phone, ' ');
				fout << phone << " ";
				fin >> flight;
				fout << flight << " ";
				fin >> seat;

				if (Ticket == ticket)
				{
					fout << seatnumber << endl;

					cout << "_____________________________________" << endl;
					cout << "Updated Ticket Generated" << endl;
					cout << "Ticket Number is: " << ticket << endl;
					cout << "Customer Id is: " << Id << endl;
					cout << "Customer Name is: " << name << endl;
					cout << "Customer Phone Number is: " << phone << endl;
					cout << "Flight Number is: " << flight << endl;
					cout << "New Seat Number is: " << seatnumber << endl;
					cout << "_______________________________________" << endl << endl;

				}
				else
				{
					fout << seat << endl;
				}
			}
		}

		fin.close();
		fout.close();

		remove("Ticket.txt");
		rename("temp.txt", "Ticket.txt");
	}
	void cancelticket(int ticket, int seat, int flight)
	{
		ifstream fin;
		fin.open("Ticket.txt");
		ofstream fout;
		fout.open("temp.txt", ios::app);
		if (!fin)
		{
			cout << "Ticket File Not Exists" << endl;
		}
		else
		{
			while (fin >> ticketNum)
			{
				if (ticketNum != ticket)
				{
					fin >> customerId;
					fin.ignore();
					getline(fin, name, ' ');
					getline(fin, Phone, ' ');
					fin >> flightno;
					fin >> seatnumber;

					fout << ticketNum << " " << customerId << " " << name << " " << Phone << " " << flightno << " " << seatnumber << endl;
				}
				else {
					fin >> customerId;
					fin.ignore();
					getline(fin, name, ' ');
					getline(fin, Phone, ' ');
					fin >> flightno;
					fin >> seatnumber;
				}
			}
		}
		fin.close();
		fout.close();

		remove("Ticket.txt");
		rename("temp.txt", "Ticket.txt");
	}
	bool check(int ticket, int seat, int flight)
	{
		ifstream fin;
		fin.open("Ticket.txt");
		bool flag = false;

		if (!fin)
		{
			cout << "Ticket File Not Exists" << endl;
		}
		else
		{
			while (fin >> ticketNum)
			{
				if (ticketNum == ticket)
				{
					fin >> customerId;
					fin.ignore();
					getline(fin, name, ' ');
					getline(fin, Phone, ' ');
					fin >> flightno;
					if (flightno == flight)
					{
						fin >> seatnumber;
						if (seatnumber == seat)
						{
							flag = true;
						}
					}
					else
					{
						fin >> seatnumber;
					}
				}
				else {
					fin >> customerId;
					fin.ignore();
					getline(fin, name, ' ');
					getline(fin, Phone, ' ');
					fin >> flightno;
					fin >> seatnumber;
				}
			}
		}
		fin.close();
		return flag;
	}
	void generateTicket(int ID, string name, string phone, int flight, int seatnumber)
	{
		ticketNum = 1;
		ifstream f("Ticket.txt"); 
		if (f.is_open())
		{
			string temp; int x;
			while (f>>x)
			{
				getline(f, temp, '\n');
			}
			ticketNum = ++x;
		}
		ofstream fout;
		fout.open("Ticket.txt", ios::app);

		if (!fout)
		{
			cout << "Ticket File Not Exists" << endl;
		}
		else
		{
			
			f.close();
			fout << ticketNum << " " << ID << " " << name << " " << phone << " " << flight << " " << seatnumber << endl;
			cout << "__________________________________________" << endl;
			cout << "   Ticket Generated" << endl;
			cout << "Ticket Number: " << ticketNum << endl;
			cout << "Flight Number: " << flight << endl;
			cout << "Customer Id: " << ID << endl;
			cout << "Name: " << name << endl;
			cout << "Phone: " << phone << endl;
			cout << "Seat Number: " << seatnumber << endl;
			cout << "__________________________________________" << endl << endl;
			cout << endl << endl;

		}
	}
	bool payment(int Discount)
	{
		int money;
		bool flag = false;
		do{
			cout << "~~~~~~~~~~~~~~~~~~~Enter Credit Card Details ~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			string accno;
			cin.ignore();
			cout << "Enter your Account Number: ";
			getline(cin, accno);
			int cvc;
			cout << "Enter your CVC code of Credit Card: ";
			cin >> cvc;
			cout << "Enter Date of Expiry: ";
			int date1;
			cin >> date1;
			cout << "Enter Amount to Pay for Ticket: ";
			cin >> money;
			if (money > Discount)
			{
				int bal;
				bal = money - Discount;
				cout << endl;
				cout << "Your Remaining Balance is: " << bal << endl;
				cout << "Sucessfully Amount Paid" << endl;
				cout << endl;
				flag = true;
			}
			else if (money < Discount)
			{
				cout << "Sorry!!!! Low Balance" << endl;
				cout << "Enter Again your details" << endl;
				cout << endl;
			}
			else if (money == Discount)
			{
				cout << endl;
				cout << "Sucessfully Amount Paid" << endl;
				cout << endl;
				flag = true;
			}
		} while (flag != true);
		return true;
	}
	void getDiscount(bool flag, string name, int ID, string phone, int flight, Airport &a, Offers &o, Planes &p)
	{
		bool flag2 = false;
		int choice = 0;
		char ignore;
		bool f = false;

		if (flag)
		{
			cout << "You are our OLD Customer Press 1 to Avail Special Discount: ";
			cin >> choice;
			ifstream fin;
			fin.open("Price.txt");
			if (!fin)
			{
				cout << "Price File Missing" << endl;
			}
			else {
				while (fin >> flightno)
				{
					getline(fin, planename, ':');
					fin >> ignore;
					getline(fin, sourcecity, ',');
					getline(fin, destinationcity, ')');
					if (flightno == flight)
					{
						fin >> newprice;
					}
					else
					{
						fin >> oldprice;
					}
				}
			}
			fin.close();
			if (choice == 1)
			{
				discount = o.giveoffer("Old", flight, newprice);
				p.reserveseat(flight);
				do {
					cout << "Enter Your Seat Number: ";
					cin >> seatnumber;
					flag2 = p.searchseat(flight, seatnumber);
				} while (flag2 != true);
				f = payment(discount);
				a.showAirportinfo(flight);
				generateTicket(ID, name, phone, flight, seatnumber);
			}
			else {
				cout << "Wrong Input" << endl;
			}
		}
		else
		{
			cout << "You are our NEW Customer Press 1 to Avail Discount: ";
			cin >> choice;

			if (choice == 1)
			{
				ifstream fin;
				fin.open("Price.txt");
				if (!fin)
				{
					cout << "Price File Missing" << endl;
				}
				else {
					while (fin >> flightno)
					{
						getline(fin, planename, ':');
						fin >> ignore;
						getline(fin, sourcecity, ',');
						getline(fin, destinationcity, ')');

						if (flightno == flight)
						{
							fin >> newprice;
						}
						else {
							fin >> oldprice;
						}
					}
				}
				fin.close();
				discount = o.giveoffer("New", flight, newprice);
				p.reserveseat(flight);
				do {
					cout << "Enter Your Seat Number: ";
					cin >> seatnumber;

					flag2 = p.searchseat(flight, seatnumber);
				} while (flag2 != true);
				f = payment(discount);
				a.showAirportinfo(flight);
				generateTicket(ID, name, phone, flight, seatnumber);
			}
			else {
				cout << "Wrong Input" << endl;
			}
		}
	}
	void ReadFromDatabase(){
		ifstream fin("Ticket.txt");
		if (fin.is_open())
		{
			int count = 0; char ch;
			while (fin >> arr[count].ticketNum)
			{

				fin >> arr[count].customerId;
				fin.get(ch);
				getline(fin, arr[count].name, ' ');
				getline(fin, arr[count].Phone, ' ');
				fin >> arr[count].flightno >> arr[count].seatnumber;
				count++;
				size++;
			}
			cout << "Ticket Data read successfully!!!!!!!\n";
		}
		else
		{
			cout << "Ticket file is Missing\n";
		}
	}
	void Display(){
		for (int i = 0; i < size; i++)
		{
			cout << arr[i].ticketNum << " " << arr[i].customerId << " " << arr[i].name << " " << arr[i].Phone << " " << arr[i].flightno << " " << arr[i].seatnumber << endl;
		}
	}
protected:
	string name, sourcecity, destinationcity, planename, Phone, tickettype, date, time;
	int customerId, flightno, seatnumber, discount;
	string newprice;
	string oldprice;
private:
	int ticketNum;
	TicketList arr[1000];
	int size;

};

class customer {
public:
	customer()
	{
		root = NULL;
	}
	~customer()
	{
		delete root;
		root = NULL;
	}
	bool setdata(string name, int Id, string Phone, string dateofBirth, int FlightNumber)
	{
		bool f = SearchData(name);
		if (!f)
		{
			if (root == NULL)
			{
				root = create(root, name, Id, Phone, dateofBirth, FlightNumber);
			}
			create(root, name, Id, Phone, dateofBirth, FlightNumber);
			ofstream fout("Customer.txt", ios::app);
			fout << name << " ";
			fout << Id << " ";
			fout << Phone << " " << dateofBirth << " " << FlightNumber << endl;
			fout.close();
			return false;
		}
		else
		{
			cout << "Customer Already Exists" << endl;
			return true;
		}
	}
	string getdata()
	{
		string name;
		cout << "EnTer Name:"; cin >> name;
		Search(root, name);
	}
	void updateData(string name)
	{
		bool f = SearchData(name);
		if (f)
		{
			cout << endl;
			cout << "Customer Founded!!!!!!!" << endl;
			cout << endl;
			string Name; int Id; string Phone; string dateofBirth; int FlightNumber;
			cout << "Enter Name: ";
			cin >> Name;
			cout << "Enter ID: ";
			cin >> Id;
			cout << "Enter Phone Number: ";
			cin >> Phone;
			cout << "Enter Date of Birth: ";
			cin >> dateofBirth;
			cout << "Enter Number of Flights: ";
			cin >> FlightNumber;
			updatefromfile(name, Name, Id, Phone, dateofBirth, FlightNumber);

			cout << endl;
			cout << "Customer Data Updated Successfully!!!!!" << endl;
		}
		else
		{
			cout << "Customer Not Registered!!!! Invalid" << endl;
		}
	}
	bool SearchData(string name){
		ifstream fin;
		fin.open("Customer.txt");

		if (!fin)
		{
			cout << "Customer File is Missing" << endl;
		}
		else {
			string n, phone, dob, flights;
			char ignore;
			int id;  bool flag = false;
			while (fin >> n)
			{
				fin >> id;
				fin >> ignore;
				getline(fin, phone, ' ');
				getline(fin, dob, ' ');
				getline(fin, flights, '\n');


				if (n == name)
				{
					cout << "Name is: " << n << endl;
					cout << "Id is: " << id << endl;
					cout << "Phone Number is: " << phone << endl;
					cout << "Date of Birth is: " << dob << endl;
					cout << "Flight Number is: " << flights << endl;
					flag = true;
				}
			}
			fin.close();
			if (!flag)
			{
				cout << "Customer Not Found\n";
			}
			return flag;
		}
	}
	bool deletedata(string name)
	{
		ifstream fin; bool flag = false;
		fin.open("Customer.txt");
		if (!fin)
		{
			cout << "Customer File is Missing" << endl;
		}
		else {
			string n, t;
			ofstream fout("temp.txt");
			while (fin >> n){
				getline(fin, t, '\n');

				if (n == name)
				{
					flag = true;
				}
				else
				{
					fout << n << t << endl;
				}

			}
			fin.close();
			fout.close();
			if (flag)
			{
				remove("Customer.txt");
				rename("temp.txt", "Customer.txt");
			}

		}
		return flag;
	}
	void ShowAllCustomer(){
		cout << "|Press 1 for Display from DataBase\n";
		cout << "|Press 2 for Display from DataStructure\nSelect option :";
		int c; cin >> c;
		if (c == 1)
		{
			ifstream fin("Customer.txt");
			if (!fin)
			{
				cout << "Customer file  not missing\n";
			}
			else
			{
				string n, phone, dob, flights;
				char s;
				int id;  bool flag = false;

				cout << "Name    ID   Phone No.     DOB       FLight no.   \n";
				while (fin >> n){
					fin >> id;
					fin >> s;
					getline(fin, phone, ' ');
					getline(fin, dob, ' ');
					getline(fin, flights, '\n');
					cout << n << "  ";
					cout << id << "   ";
					cout << phone << "     ";
					cout << dob << "           ";
					cout << flights << "         " << endl;
				}
				fin.close();
			}
		}
		else if (c == 2)
		{
			cout << "Press 1 for view in Preorde \n";
			cout << "Press 2 for view in Inorder\n";
			cout << "Press 3 for view in Postorder\nSelect Option :"; int x; cin >> x;
			if (x == 1)
			{
				ofstream f;
				preorder(root,false,f);
			}
			else if (x == 2)
			{
				Inorder(root);
			}
			else if (x == 3)
			{
				postorder(root);
			}
			else
			{
				cout << "Wrong Input\n";

			}

		}
		else
		{
			cout << "Wrong Input\n";
		}
	}

	void ReadFromDatabase(){
		ifstream fin;
		fin.open("Customer.txt");
		if (!fin.is_open())
		{
			cout << "Customer file Missing!!!!!!!!\n";
		}
		else
		{
			string n, phone, dob;
			int flights;
			char ignore;
			int id;  bool flag = false;
			while (fin >> n)
			{
				fin >> id;
				fin.get(ignore);
				getline(fin, phone, ' ');
				getline(fin, dob, ' ');
				fin >> flights;
				if (root == NULL)
				{

					root = create(root, n, id, phone, dob, flights);
				}
				else
				{
					create(root, n, id, phone, dob, flights);
				}

			}
			cout << "Customer Data read Succesfully!!!!!\n";
		}
	}
	void WriteIndatabase(){
		if (root!=NULL)
		{
			ofstream fout("Customer.txt");
			preorder(root, true, fout);
			cout << "Customer data Write SuccessFully!!!!\n";
		}
		else
		{
			cout << "Customer Run time data not exist\n";
		}
	}
private:

	CustomerNode * root;
	CustomerNode* Search(CustomerNode* root, string name)
	{
		if (root == NULL)
		{
			cout << "ROot is NULL" << endl;
			return root;
		}
		else  if (root->name == name)
		{
			cout << "customer Name :" << root->name << endl;
			cout << "Customer Id :" << root->customerId << endl;
			cout << "Customer Flight nUmber: " << root->NoOfFlights << endl;
			cout << "Customer Phone Number :" << root->phone << endl;
			cout << "Customer Date Of Birth :" << root->DOB << endl;

			return root;
		}
		else if (root->name > name)
		{
			root->left = Search(root->left, name);
		}
		else if (root->name < name)
		{
			root->right = Search(root->right, name);
		}
	}
	CustomerNode* create(CustomerNode* root, string name, int Id, string Phone, string dateofBirth, int FlightNumber)
	{
		if (root == NULL)
		{
			root = new CustomerNode;
			root->name = name;
			root->DOB = dateofBirth;
			root->NoOfFlights = FlightNumber;
			root->phone = Phone;
			root->customerId = Id;
			root->left = NULL;
			root->right = NULL;
		}
		else if (root->customerId > Id)
		{
			root->left = create(root->left, name, Id, Phone, dateofBirth, FlightNumber);
		}
		else if (root->customerId < Id)
		{
			root->right = create(root->right, name, Id, Phone, dateofBirth, FlightNumber);
		}
		return root;
	}
	void Inorder(CustomerNode* root)
	{
		if (root == NULL)
		{
			return;
		}
		else {
			Inorder(root->left);
			cout << endl;
			cout << "customer Name :" << root->name << endl;
			cout << "Customer Id :" << root->customerId << endl;
			cout << "Customer Phone Number :" << root->phone << endl;
			cout << "Customer Flight nUmber: " << root->NoOfFlights << endl;
			cout << "Customer Date Of Birth :" << root->DOB << endl;
			cout << endl;
			Inorder(root->right);
		}
	}
	void postorder(CustomerNode* root)
	{
		if (root == NULL)
		{
			return;
		}
		else {
			postorder(root->left);
			postorder(root->right);
			cout << endl;
			cout << "customer Name :" << root->name << endl;
			cout << "Customer Id :" << root->customerId << endl;
			cout << "Customer Phone Number :" << root->phone << endl;
			cout << "Customer Flight nUmber: " << root->NoOfFlights << endl;
			cout << "Customer Date Of Birth :" << root->DOB << endl;
			cout << endl;
		}
	}
	void preorder(CustomerNode* root,bool flag,ofstream &fout)
	{
		if (!flag)
		{
			if (root == NULL)
			{
				return;
			}
			else {
				cout << endl;
				cout << "customer Name :" << root->name << endl;
				cout << "Customer Id :" << root->customerId << endl;
				cout << "Customer Phone Number :" << root->phone << endl;
				cout << "Customer Flight nUmber: " << root->NoOfFlights << endl;
				cout << "Customer Date Of Birth :" << root->DOB << endl;
				cout << endl;
				preorder(root->left,false,fout);
				preorder(root->right,false,fout);

			}
		}
		else
		{
			if (root==NULL)
			{
				return;
			}
			else
			{

				fout << root->name << " ";
				fout << root->customerId << " ";
				fout << root->phone << " " << root->DOB<< " " << root->NoOfFlights<< endl;
				preorder(root->left, true, fout);
				preorder(root->right, true, fout);

			}
		}
	}
	void updatefromfile(string name, string Name, int Id, string Phone, string dateofBirth, int FlightNumber)
	{
		ifstream fin;
		fin.open("Customer.txt");

		if (!fin)
		{
			cout << "Customer File is Missing" << endl;
		}
		else {
			string n, t; bool flag = false;
			ofstream fout("temp.txt");
			while (fin >> n){
				getline(fin, t, '\n');

				if (n == name)
				{
					fout << Name << " ";
					fout << Id << " ";
					fout << Phone << " " << dateofBirth << " " << FlightNumber << endl;
					flag = true;
				}
				else
				{
					fout << n << t << endl;
				}

			}
			fin.close();
			fout.close();
			if (flag)
			{
				remove("Customer.txt");
				rename("temp.txt", "Customer.txt");
			}

		}
	}
};

class Flight {
public:
	Flight()
	{
		head = NULL;
	}
	~Flight()
	{
		delete head;
	}
	bool add(string Plane, string sourcecity, string destinationcity, string dayz, string time, int flightno, bool flag)
	{
		if (head == NULL)
		{
			FlightNode * temp = new FlightNode;
			temp->sourcecity = sourcecity;
			temp->destinationcity = destinationcity;
			temp->dayz = dayz;
			temp->Plane = Plane;
			temp->flightno = flightno;
			temp->time = time;
			temp->next = NULL;
			temp->pre = NULL;
			head = temp;
		}
		else
		{
			FlightNode * temp = new FlightNode;
			temp->sourcecity = sourcecity;
			temp->destinationcity = destinationcity;
			temp->dayz = dayz;
			temp->Plane = Plane;
			temp->time = time;
			temp->flightno = flightno;
			temp->next = NULL;
			temp->pre = NULL;
			FlightNode * treverse = head;
			while (treverse->next != NULL)
			{
				treverse = treverse->next;
			}
			treverse->next = temp;
			temp->pre = treverse;
		}
		if (flag)
		{
			insertinDB(Plane, sourcecity, destinationcity, dayz, time, flightno);

		}
		return true;
	}
	bool update(int Fn)
	{

		FlightNode *temp = head;
		if (head != NULL)
		{
			while (temp != NULL)
			{
				if (temp->flightno == Fn)
				{
					cout << "Enter Flight Number: ";
					cin >> temp->flightno;
					cin.ignore();
					cout << "Enter Plane: ";
					getline(cin, temp->Plane);
					cout << "Enter Source City: ";
					getline(cin, temp->sourcecity);
					cout << "Enter Destination City: ";
					getline(cin, temp->destinationcity);
					cout << "Enter Dayz: ";
					getline(cin, temp->dayz);
					cout << "Enter Time: ";
					cin >> temp->time;
					cout << endl;
					break;
				}
				temp = temp->next;
			}
			return updateinDB(temp->Plane, temp->sourcecity, temp->destinationcity, temp->dayz, temp->time, temp->flightno);
		}
		else
		{
			cout << "No data Exist in Data Structure\n";
		}
	}
	bool deleted(int Fn)
	{
		FlightNode *temp = head;
		while (temp != NULL)
		{
			if (temp->flightno == Fn)
			{
				FlightNode *pre, *next = NULL;
				pre = temp->pre;
				next = temp->next;
				temp->next = temp->pre = NULL;
				pre->next = next;
				next->pre = pre;
				free(temp);
			}
		}
		return   deleteinDB(Fn);

	}
	void view(){
		cout << "|Press 1 for view from DataBase \n";
		cout << "|Press 2 for view from Data structure \n"; int c;
		cout << "Select option :"; cin >> c;
		if (c == 1)
		{
			ifstream fin("flight.txt");
			if (!fin)
			{
				cout << "Flight File missing\n";
			}
			else
			{
				char ch; int count = 0;
				while (fin.get(ch))
				{
					cout << ch;
				}
				fin.close();
			}
		}
		else if (c == 2)
		{
			if (head == NULL)
			{
				cout << "No Data exist in Data Structure\n";
			}
			else
			{
				FlightNode * treverse = head;
				while (treverse != NULL)
				{
					cout << treverse->flightno << " " << treverse->Plane << " (" << treverse->sourcecity << "," << treverse->destinationcity << ") " << treverse->dayz << " @" << treverse->time << endl;
					treverse = treverse->next;
				}
			}
		}
		else
		{
			cout << "Wrong Input !!!\n";
		}



	}
	bool searchfromdestination(string dest)
	{
		ifstream fin;
		fin.open("Flight.txt");
		bool flag = false;
		char ignore;
		int id;
		string plane;
		string source;
		string destination;
		string day;
		string t;

		if (!fin)
		{
			cout << "Flight File Not Exists" << endl;
		}
		else {

			while (fin >> id)
			{
				getline(fin, plane, ':');
				fin >> ignore;
				getline(fin, source, ',');
				getline(fin, destination, ')');
				fin.get(ignore);
				getline(fin, day, '@');
				getline(fin, t, '\n');

				if (destination == dest)
				{
					cout << id << " " << plane << ": (" << source << "," << destination << ") " << day << " @" << t << endl;
					flag = true;
				}
			}
		}
		fin.close();
		cout << endl;
		if (flag == true)
		{
			string price;
			ifstream fin1;
			fin1.open("Price.txt");
			if (!fin1)
			{
				cout << "Price File Missing" << endl;
			}
			else {
				while (fin1 >> id)
				{
					getline(fin1, plane, ':');
					fin >> ignore;
					fin >> ignore;
					getline(fin1, source, ',');
					getline(fin1, destination, ')');

					if (destination == dest)
					{
						fin1 >> price;
						cout << "Ticket From " << source << " To " << destination << ") is: " << price << endl;
					}
				}
			}
			fin1.close();
		}

		cout << endl;
		return flag;
	}
	void ReadFromDatabase(){
		ifstream fin("Flight.txt");
		if (!fin.is_open())
		{
			cout << "Flight File missing\n";
		}
		else
		{
			char ignore;
			int id;
			string plane;
			string source;
			string destination;
			string day;
			string t;

			while (fin >> id)
			{

				getline(fin, plane, ':');
				fin >> ignore;
				getline(fin, source, ',');
				getline(fin, destination, ')');
				fin.get(ignore);
				getline(fin, day, '@');
				getline(fin, t, '\n');
				add(plane, source, destination, day, t, id, false);
			}
			cout << "Flight data Read successfully!!!!\n";
		}
	}
	void WriteInDatabase(){
		if (head!=NULL)
		{
			ofstream fout("Flight.txt");
			FlightNode * temp = head;
			FlightNode * treverse = head;
			while (treverse != NULL)
			{

				fout << treverse->flightno << treverse->Plane << ": (" << treverse->sourcecity << "," << treverse->destinationcity << ") " << treverse->dayz << "@" << treverse->time << endl;
				treverse = treverse->next;
			}
			fout.close();
			cout << "flight Data write Successfully\n";
		}
		else
		{
			cout << "Flight Run Time Data not exits\n";
		}
	}
private:
	FlightNode* head;
	bool search(int fn)
	{
		ifstream fin;
		fin.open("Flight.txt");

		if (!fin)
		{
			cout << "Flight File is Missing" << endl;
		}
		else {
			int n;
			string temp;
			bool flag = false;
			while (fin >> n)
			{
				getline(fin, temp, '\n');

				if (n == fn)
				{
					flag = true;
				}
			}
			fin.close();
			return flag;
		}
	}
	void insertinDB(string Plane, string sourcecity, string destinationcity, string dayz, string time, int flightno){
		ofstream fout("Flight.txt", ios::app);
		fout << flightno << " " << Plane << ": (" << sourcecity << "," << destinationcity << ") " << dayz << " @" << time << endl;
		fout.close();
	}
	bool deleteinDB(int Fn){
		bool flag = search(Fn);
		if (!flag)
		{
			cout << "Flight Number is Invalid" << endl;
			return false;
		}
		else
		{
			ifstream fin;
			fin.open("Flight.txt");

			ofstream fout;
			fout.open("temp.txt");
			char ignore;
			int id;
			string plane;
			string source;
			string destination;
			string day;
			string t;

			if (!fin)
			{
				cout << "Flight Files is Invalid" << endl;
			}
			else {
				while (fin >> id)
				{
					getline(fin, plane, ':');
					fin >> ignore;
					getline(fin, source, ',');
					getline(fin, destination, ')');
					fin.get(ignore);
					getline(fin, day, '@');
					getline(fin, t, '\n');

					if (id != Fn)
					{
						fout << id << plane << ": (" << source << "," << destination << ") " << day << "@" << t << endl;

					}
				}
				fin.close();
				fout.close();

				remove("Flight.txt");
				rename("temp.txt", "Flight.txt");
			}
			return true;
		}
	}
	bool updateinDB(string Pl, string sc, string dc, string dyz, string tim, int Fn){

		ifstream fin;
		fin.open("Flight.txt");

		ofstream fout;
		fout.open("temp.txt");
		char ignore;
		int id;
		string plane;
		string source;
		string destination;
		string day;
		string t;

		if (!fin)
		{
			cout << "Flight Files is Invalid" << endl;
		}
		else {
			while (fin >> id)
			{
				getline(fin, plane, ':');
				fin >> ignore;
				getline(fin, source, ',');
				getline(fin, destination, ')');
				fin.get(ignore);
				getline(fin, day, '@');
				getline(fin, t, '\n');

				if (id == Fn)
				{
					id = Fn;
					plane = Pl;
					destination = dc;
					source = sc;
					day = dyz;
					t = tim;
					cout << endl;

					fout << id << " " << plane << ": (" << source << "," << destination << ") " << day << " @" << t << endl;
				}
				else {
					fout << id << plane << ": (" << source << "," << destination << ") " << day << "@" << t << endl;
				}
			}
			fin.close();
			fout.close();
			remove("Flight.txt");
			rename("temp.txt", "Flight.txt");
		}
		return true;
	}
};
