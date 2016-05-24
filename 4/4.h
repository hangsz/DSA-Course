
#pragma once

#include <iostream>
#include <iomanip>
using namespace std;
struct node
{
	int address=-1;
	int data;
	int next = -1;

	inline node& operator=(node& );

	friend istream& operator>>(istream&, node& );
	friend ostream& operator<<(ostream&, node&);
	
};

node& node::operator=(node& nod){
	address = nod.address;
	data = nod.data;
	next = nod.next;
	return nod;
}
 istream& operator>>(istream& is, node& nod){
	 is >> nod.address >> nod.data >> nod.next;
	 return is;
}
 ostream& operator<<(ostream& os, node& nod){
	 os << setw(5) << setfill('0') << nod.address << ' ' << nod.data << ' ' << setw(5) << setfill('0')<< nod.next << endl;
	 return os;
 }






