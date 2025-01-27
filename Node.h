#include<iostream>
using namespace std;

struct ReservedFlighhtNode {
	int ticketNumber;
	int passengerid;
	string name;
	string phone;
	int Flightno;
	int seatno;
	ReservedFlighhtNode *left, *right;
	ReservedFlighhtNode(){
		ticketNumber = 0;
		passengerid = 0;
		Flightno = seatno = 0;
		left = right = 0;
	}
};

struct CustomerNode {
	int customerId;
	string name;
	string phone;
	string DOB;
	int NoOfFlights;
	CustomerNode* left = NULL;
	CustomerNode* right = NULL;
};

struct FlightNode {
	string Plane;
	string sourcecity;
	string destinationcity;
	string dayz;
	string time;
	int flightno;
	FlightNode * next;
	FlightNode * pre;
};

struct AirportNode {
	string SourceairportName;
	string DestinationairportName;
	string Sourcecountry;
	string Destinationcountry;
	string weatherCondition;
	string timeFromBeirut;
	int flight;
	AirportNode * next;
};

struct OfferList {
	int offerId;
	int FlightNum;
	int DiscountAmount;
	string OfferType;
	string amount;
	int size;
	OfferList()
	{
		offerId = 0;
		FlightNum = 0;
		DiscountAmount = 0;
		size = 0;
	}


};

struct PlaneNode {
	int planeId;
	int flightno;
	string planename;
	string seatno;
	int firstclassseat;
	int secondclassseat;
	PlaneNode *next;
	PlaneNode()
	{
		planeId = 0;
		flightno = 0;
		firstclassseat = secondclassseat = 0;
		next = NULL;
	}
};

struct TicketList {
	int ticketNum;
	int seatnumber;
	int flightno;
	int customerId;
	string name;
	string Phone;
	TicketList()
	{
		ticketNum = seatnumber = flightno = customerId = 0;
	}
};

