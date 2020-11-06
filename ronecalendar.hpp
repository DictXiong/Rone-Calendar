// (About) R.one's calendar -*- C++ -*-

/**
 * Copyleft (!C) 2012-2014 by Bear Dictionary.Some Rights Reserved.
 * 
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyleft notice appear in all copies and that
 * both that copyleft notice and this permission notice appear in 
 * supporting documentation.
 * 
 * E-Address<http://www.cnblogs.com/Bear-Dictionary/>,
 * E-Mail<18080959029@qq.com>.
 * 
 * Function-getMaxDay(Overloaded),
 * Class-type_date(Tdate),Class-type_time(Ttime) within this package.
 */
 
 // This file is the main file of the R.one's calendar package.
 
 /** @file include/ronecalendar.hpp,Version<20141108R>.
 *  History Version:<20140920><20140831><20140716><20140715><20140714>,<1.00>,<BETA>.
 *  This is NOT a Standard C++ Library header.
 */
#ifndef __cplusplus
#error [wc!这是为C++编写的头文件!请使用C++编译器编译!||wc!This headfile is written for C++!Please run this Program by gc++!]
#endif
#ifndef __rone_calendar__
#define __rone_calendar__

class type_date;
class type_time; 

#include"type_date.hpp" //class-type_date within
#include"type_time.hpp" //class-type_time within

typedef type_date Tdate;
typedef type_time Ttime;
 
#ifdef testing
#include"testtools.hpp"
#endif

#endif
