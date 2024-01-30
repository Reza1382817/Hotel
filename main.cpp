#include <iostream>
#include<string.h>
#include <iomanip>
#include <ctime>
using namespace std;

class Customer
{
private:
	string name;	   			 //CUSTOMER FULL NAME
	string national_code;				//CONTACT NUMBER
	int days=0;	    			//DURATION OF STAY
	double bill=0;				//BILL AMT
	int booking_id;				//BOOKING ID
	int room;					//ROOM NO
	int situation;
public:
	Customer()
{
		days=0;
		bill=0;
		booking_id=0;
		situation=0;
		room=0;
}
	void accept();				//ACCEPT CUSTOMER DETAILS
	void displayCust();				//DISPLAY CUSTOMER DETAILS
	friend class room;
	friend class Hotel;
};

void Customer::accept()		     //accepting details of customer
{
	cout<<"Enter customer name: ";
	getline(cin, name);
	getline(cin, name);
	flag:
	cout<<"Enter national_code number: ";
	cin>>national_code;
}

void Customer::displayCust()		   //displaying details of customers
{
	cout<<endl<<"\t"<<booking_id<<"\t";
	cout<<"||\t"<<name<<"\t";
	cout<<"||\t"<<national_code<<"\t";
	cout<<"||\t"<<room<<"\t\t";
	if(situation==1)
    {
        cout<<"||\tACTIVE\t"<<endl;
    }
	else{
            cout<<"||\tCHECKED OUT\t"<<endl;
    }
}

class Room
{
private:
	int roomNumber;			//ROOM NUMBER
	double rent;			//DAILY RENT OF ROOM
	int situation=0;			//ROOM IS BOOKED OR NOT

public:
	friend class Hotel;
	void acceptroom(int rno);		//ADD ROOMS TO HOTEL DATABASE
	void displayRoom();		        //DISPLAY ROOMS
	Room()					        //DEFAULT CONSTRUCTOR
	{
		roomNumber=0;
		rent=0;
		situation=0;
	}
};

void Room::acceptroom(int rnu)		//ACCEPTING ALL ROOM DETAILS
{
	roomNumber=rnu;	//ROOM NUMBER
	cout<<"Daily Rent(between 0 and 1000): ";
	cin>>rent;
	while(rent<0 || rent>1000)
	{
		cout<<"Please enter correct number: ";
		cin>>rent;
	}
	situation=0;	//BOOKING Situation OF THE ROOM
	cout<<"\nRoom added successfully"<<endl;
}

void Room::displayRoom()
{
	cout<<"     "<<roomNumber<<"     \t\t||\t"<<rent<<"\t\t||\t";
	if(situation==0)
    {
        cout<<"available";
    }

	 else{
        cout<<"Unavailable\t\t";
    }
	cout<<endl;
}

class Hotel
{
	Room a[100];			    //array of rooms
	Customer c[100];			//array of customers
	int nroom=0;                 //number of rooms
	int ncust=0;	          //number of customers
	int total=0;
public:
	void addRooms();
	void CheckIn();
	void availability();
	void CheckOut();
	void Summary();
	void Total();
};

void Hotel::addRooms()
{
	int rnu;
	cout<<"Enter number of rooms: ";
	cin>>nroom;		       //accepting number
	while(nroom<=0)
	{
		cout<<"Please enter valid number: ";
		cin>>nroom;
	}
	for(int i=0 ; i<nroom ; i++)
	{
		cout<<endl<<"ROOM "<<(i+1);
		flag:
		cout<<endl<<"Enter room number : ";
		cin>>rnu;
		if(rnu<=0)
		{
			cout<<endl<<"please enter valid number: ";
			goto flag;
		}
		for(int j=0; j<nroom;j++)
		{
			if(a[j].roomNumber==rnu)
			{
				cout<<"This number is repetitive"<<endl;
				goto flag;
			}
		}
		a[i].acceptroom(rnu);		//calling function
	}
}

void Hotel::availability()
{
	if(nroom==0)
    {
		cout<<"Please add rooms."<<endl;
		return;
	}
	cout<<"The list of all available rooms:"<<endl<<endl;
	cout<<" Room Number\t\t||\tRent\t\t||\tAvailability"<<endl<<endl;
	for(int i=0;i<nroom;i++)
	{
		a[i].displayRoom();	  //displaying details of room
	}
}

void Hotel::CheckIn()		//check in of a customer
{
	if(nroom==0)
	{
		cout<<"Please add rooms"<<endl;
		return;
	}
	int i, rnu;

		c[ncust].booking_id=ncust+1;	//allocating customer id to the customer
		flag:
		int flag1=0;
		cout<<"Enter room number: ";
		cin>>rnu;
		for(i=0;i<nroom; i++){
			if(rnu==a[i].roomNumber)
			{
				flag1=1;
				break;
			}
		}
		if(flag1==0){
			cout<<"Invalid room number. Please Enter again\n";
			goto flag;
		}
		if(a[i].situation==0)
		{
			string st;
			cout<<"Room available."<<endl;
			a[i].displayRoom();
			c[ncust].accept();		       //accepting details of customer
			cout<<"Enter number of days of stay: ";
			cin>>c[ncust].days;
			c[ncust].bill = c[ncust].days*a[i].rent;
			cout<<"Your total bill will be: "<<c[ncust].bill;
			cout<<endl<<endl<<"write yes to continue? ";
			cin>> st;
			if(st=="yes")
			{
				cout<<endl<<endl<<"Complete.Thank you"<<endl;
				cout<<"--------------------------------------------------------------"<<endl;
				cout<<"Booking Id: "<<c[ncust].booking_id<<endl<<"Name: "<<c[ncust].name<<endl<<"Room number: "<<rnu<<endl<<"Reserve date: ";
				time_t my_time = time(NULL);
				printf("%s", ctime(&my_time));
				a[i].situation=1;		    //changing room situation to booked
				c[ncust].room=rnu;		   //allocating room to customer
				c[ncust].situation=1;
				ncust++;
			}
			else
			{
				goto flag;
			}
		}
		else
		{
			cout<<"Room Occupied. Please choose another room."<<endl;
		}

}

void Hotel::Total()
{
    for(int n=0 ;n<ncust ; n++ ){
        total = total + c[n].bill ;
    }
}

void Hotel::CheckOut()
{
	int rnu, i, k;
	cout<<"Enter room number: ";
	cin>>rnu;
	for(k=0;k<nroom; k++){
		if(rnu==a[k].roomNumber)
		{
			break;
		}
	}
	if(a[k].situation==0)
	{
		cout<<"Invalid."<<endl;
	}
	for(i=0;i<ncust;i++)	//checking details of customer
	{
		if(c[i].room==rnu)
		{
			cout<<"CHECKING OUT."<<endl;
			c[i].displayCust();
			cout<<"Your total bill is "<<c[i].bill<<endl;
			cout<<"Hence, Your total bill is: "<<c[ncust].bill;
			cout<<endl<<endl<<"Thank you! Visit Again :)"<<endl;
			a[k].situation=0;	//changing situation
			c[i].situation=0;	//checked out
			break;
		}
	}
}

void Hotel::Summary()		//printing details of all customers
{
	if(nroom==0)
	{
		cout<<"No customers as yet."<<endl;
		return;
	}
	cout<<"Guest Summary:"<<endl<<endl;
	cout<<"\tId\t";
	cout<<"||\tName\t";
	cout<<"||\tnational_code\t";
	cout<<"||\tRoom number\t";
	cout<<"||\tSituatin"<<endl;
	for(int i=0;i<ncust;i++)
	{
		c[i].displayCust();
	}
}

int main()
{
	Hotel AMIRKABIR;
	char ch;
	cout<<endl<<"====================================================================== WELCOME TO AMIR KABIR HOTEL =====================================================================";
	do
	{
		cout<<endl<<"========================================================================================================================================================================";
		cout<<endl<<"\t\t\t\t\t\t\t\t\t"
				    "MENU:\n\t\t\t\t\t\t\t\t\t"
			    	"1.OPERATE AS ADMIN\n\t\t\t\t\t\t\t\t\t"
			    	"2.OPERATE AS CUSTOMER\n\t\t\t\t\t\t\t\t\t"
			    	"3.EXIT\n\t\t\t\t\t\t\t\t\t"
			    	"Enter your choice: ";
		cin>>ch;
		switch(ch)
		{
		case '1':
		    char ch1;
		    do{
		cout<<endl<<"========================================================================================================================================================================";
                cout<<endl<<"\t\t\t\t\t\t\t\t\t"
				            "MENU:\n\t\t\t\t\t\t\t\t\t"
				            "1.Add Rooms\n\t\t\t\t\t\t\t\t\t"
				            "2.Guest Summary\n\t\t\t\t\t\t\t\t\t"
                            "3.Total Bill\n\t\t\t\t\t\t\t\t\t"
                            "4.Go back to Main Menu\n\t\t\t\t\t\t\t\t\t"
				            "Enter your choice: ";
			cin>>ch1;
				switch(ch1)
				{
				case '1':
					cout<<"Add database of rooms in the hotel:"<<endl;
			        AMIRKABIR.addRooms();
			        cout<<"Database updated. Going back to main menu."<<endl;
					break;
				case '2':
                    AMIRKABIR.Summary();
					break;
				case '3':
				    AMIRKABIR.Total();
					break;
                case '4':
					break;
				default:
					cout<<"Invalid Choice."<<endl;
					break;
				}
			}while(ch1!='4');
			break;

		case '2':
			char ch2;
			do{
		cout<<endl<<"========================================================================================================================================================================";
				cout<<"\n\t\t\t\t\t\t\t\t\t"
                      "Menu:\n\t\t\t\t\t\t\t\t\t"
                      "1.Check Availability of rooms.\n\t\t\t\t\t\t\t\t\t"
                      "2.Check In\n\t\t\t\t\t\t\t\t\t"
                      "3.Checkout.\n\t\t\t\t\t\t\t\t\t"
                      "4.Go back to Main Menu.\n\t\t\t\t\t\t\t\t\t"
                      "Enter your choice: ";
				cin>>ch2;
				switch(ch2)
				{
				case '1':
					AMIRKABIR.availability();
					break;
				case '2':
					AMIRKABIR.CheckIn();
					break;
				case '3':
					AMIRKABIR.CheckOut();
					break;
				case '4':
					break;
				default:
					cout<<"Invalid Choice."<<endl;
					break;
				}
			}while(ch2!='4');
			break;
		case '3':
			cout<<"Thank you!";
			exit(0);
		default:
			cout<<"Invalid Choice."<<endl;
			break;
		}
	}while(ch!='3');
	return 0;
}
