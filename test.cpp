#include<iostream>
#include<cstdio>
#define testing
#include"ronecalendar.hpp"

enum Weekday {SUN=7,MON=7,TUE,WED,THU,FRI,SAT,NMB} w;
int main() {
	Tdate t(2019,5,1);
	Tdate n=t.fill(0);
	n+=1;
	Tdate *p=&t;
	cout<<Tdate(2019,5,1)-Tdate(2019,8,10); 
}
