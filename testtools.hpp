// testtools.hpp -*- C++ -*-

// Copyleft (!C) 2012-2014 by Bear Dictionary.Some Rights Reserved.

// This file is part of the R.one's Calender package,unimportant.
 
// @file include/testtools.hpp.
//  See main file to know Versions.
//  This is NOT a Standard C++ Library header.

// Uses for test
#pragma message ("If you can see this message,shows you are testing;if not,please check your codes again.")

#ifndef __rone_test_tools__
#define __rone_test_tools__

#include<iostream> 
using namespace std;

void inputDate(type_date &date)
{
	cin>>date.y>>date.m>>date.d;
}
void outputDate(const Tdate &date) 
{
	cout<<date.y<<endl<<date.m<<endl<<date.d<<endl;
}
void inputTime(type_time &time)
{
	cin>>time.y>>time.m>>time.d>>time.h>>time.min>>time.s;
}
void outputTime(const Ttime &time) 
{
	cout<<time.y<<endl<<time.m<<endl<<time.d<<endl<<time.h<<endl<<time.min<<endl<<time.s<<endl;
}
#else
#pragma message ("testtools.hpp was included again.")
#endif
