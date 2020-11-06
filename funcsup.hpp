// Functions support -*- C++ -*-

// Copyleft (!C) 2012-2014 by Bear Dictionary.Some Rights Reserved.

// This file is part of the R.one's calendar package. 
 
// @file include/funcsup.hpp.
//  See main file to know Versions.
//  This is NOT a Standard C++ Library header.
#ifndef __cplusplus
#error [wc!这是为C++编写的头文件!请使用C++编译器编译!||wc!This headfile is written for C++!Please run this Program by gc++!]
#endif
#ifndef __rone_func_sup__
#define __rone_func_sup__

const int DAYS_IN_400_YEARS=146097;
const int DAYS_IN_100_YEARS=36524;
const int DAYS_IN_4_YEARS=1461;

const int DATE_DIFFERENCE=1900;
const int DAYS_PER_NORMAL_YEAR=365;
const int DAYS_PER_LEAP_YEAR=366;
const int DAYS_PER_WEEK=7;
const int DAYS_PER_BIG_MONTH=31;
const int MONTHS_PER_YEAR=12;

const int MAX_HOUR_NUM=23;
const int MAX_MIN_NUM=59;
const int MAX_SEC_NUM=59;
const int SECS_PER_DAY=86400;
const int SECS_PER_HOUR=3600;
const int SECS_PER_MIN=60;
    
short getMaxDay(const int y)
{
	if (y==0) return 0;
	if ((y%4==0 && y%100!=0) || y%400==0)
	             return 366;
	             return 365;
}

short getMaxDay(const int y,const int m)
{
	if (y==0 || m>12 || m<1) return 0;
	switch(m){
	      case 1:
		  case 3:
		  case 5:
		  case 7:
		  case 8:
		  case 10:
		  case 12: return 31;break;
	      case 4:
		  case 6:
		  case 9:
		  case 11: return 30;break;
	      case 2: if ((y%4==0 && y%100!=0) || y%400==0)
	                return 29;
	                return 28; break;
	         }
}
#else
#ifdef testing
#pragma message ("funcsup.hpp was included again.")
#endif
#endif
