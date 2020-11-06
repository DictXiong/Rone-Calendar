// type_time.hpp -*- C++ -*-

// Copyleft (!C) 2012-2014 by Bear Dictionary.Some Rights Reserved.

// This file is part of the R.one's calendar package. 
 
// @file include/type_time.hpp.
//  See main file to know History Versions.
//  This is NOT a Standard C++ Library header.
#ifndef __cplusplus
#error [wc!这是为C++编写的头文件!请使用C++编译器编译!||wc!This headfile is written for C++!Please run this Program by gc++!]
#endif
#ifndef __rone_type_time__
#define __rone_type_time__

#include<ctime>
#include<string>
#include<cstring>
#include<stdlib.h>
#include"type_date.hpp"
#include"funcsup.hpp"

class type_time: public type_date
{
  public:

	long long y;
	short m,d,h,min,s;
	
	bool isLawful()const
	{
		if (y==0 || m>DAYS_PER_BIG_MONTH || m<1 || d<1) return 0;
	    if (d>getMaxDay(y,m)) return 0;
		if (h>MAX_HOUR_NUM || h<0) return 0;
		if (min>MAX_MIN_NUM || min<0) return 0;
		if (s>MAX_SEC_NUM || s<0) return 0;
		return 1;
	}

	type_time &fill() {y=m=d=h=min=s=0;return *this;}
	type_time &fill(long long secs)
	{
		fill();
		type_date tmp_date;
		long long days;
		if (secs>=0) {days=(secs/SECS_PER_DAY)+1;secs%=SECS_PER_DAY;}
		if (secs<0) {days=(secs/SECS_PER_DAY)-1;secs=-secs;secs%=SECS_PER_DAY;secs=SECS_PER_DAY-secs;}
		tmp_date=days;
		*this=tmp_date;
		h=secs/SECS_PER_HOUR;
		secs%=SECS_PER_HOUR;
		min=secs/SECS_PER_MIN;
		secs%=SECS_PER_MIN;
		s=secs;
		if (!isLawful()) fill();
		return *this;
	}
	type_time &fill(long long year,short month,short day=1,short hour=0,short minute=0,short second=0)
	  {y=year;m=month;d=day;h=hour;min=minute;s=second;return *this;}
	type_time &fill(tm tmTime)
	{
		fill(tmTime.tm_year+DATE_DIFFERENCE,tmTime.tm_mon+1,tmTime.tm_mday,tmTime.tm_hour,tmTime.tm_min,tmTime.tm_sec);
		return *this;
	}
	type_time &fill(type_date cdate,short hour=0,short minute=0,short second=0)
	{
		*this=cdate;
		h=hour;
		min=minute;
		s=second;
		return *this;
	}
	type_time &fill(std::string timeAtString)
	{
		long long ans[6];
		memset(ans,0,sizeof(ans));
		short numWhereToWrite=0,numBegin=0;
		for (int i=1;i!=timeAtString.size() && numWhereToWrite!=6;i++)
		{
			if (isdigit(timeAtString[i])) 
			{
				if (!isdigit(timeAtString[i-1]))
					numBegin=i;
				if (i==timeAtString.size()-1)
					ans[numWhereToWrite++]=atoi(timeAtString.c_str()+numBegin);
			}
			else if (isdigit(timeAtString[i-1]))
				 	ans[numWhereToWrite++]=atoi(timeAtString.c_str()+numBegin);
		}
		fill(ans[0],ans[1],ans[2],ans[3],ans[4],ans[5]);
		return *this;
	}

    type_time() {fill();}
	type_time(long long num) {fill(num);}
	type_time(long long year,short month,short day=1,short hour=0,short minute=0,short second=0)
	{fill(year,month,day,hour,minute,second);}
	type_time(tm tmTime) {fill(tmTime);} 
	type_time(type_date cdate,short hour=0,short minute=0,short second=0) {fill(cdate,hour,minute,second);}
	type_time(std::string timeAtString) {fill(timeAtString);}

	type_time &now()
	{
		fill();
		time_t tmp_localtime;
		tmp_localtime=time(NULL);
		fill(*localtime(&tmp_localtime));
		return *this;
	}	
	long long toSecs()const
	{
		type_date tmp_date;
		if (!isLawful()) return 0;
		long long ans;
		tmp_date=*this;
		if (y>0) return ((tmp_date-1)*SECS_PER_DAY+h*SECS_PER_HOUR+min*SECS_PER_MIN+s);
		  else return -(-(tmp_date+1)*SECS_PER_DAY+h*SECS_PER_HOUR+min*SECS_PER_MIN+s);
	}
	//Operators overloading
	operator type_date()const
	{
		type_date ans;
		if (!isLawful()) {ans.fill();return ans;}
		ans.fill(y,m,d);
		return ans;
	}
	
	type_time &operator=(type_date cdate)
	{
		fill();
		y=cdate.y;
		m=cdate.m;
		d=cdate.d;
		if (!isLawful()) fill();
		return *this;
	}
	
	bool operator==(const type_time ptime)const
	{
		if (y==ptime.y&&m==ptime.m&&d==ptime.d&&h==ptime.h&&min==ptime.min&&s==ptime.s) return 1;
		return 0;
	}
	
	bool operator!=(const type_time ptime)const
	{
		return !(ptime==*this);
	}
	
	bool operator>(const type_time ptime)const
	{
		if (y!=ptime.y) return (y>ptime.y);
		if (m!=ptime.m) return (m>ptime.m);
		if (d!=ptime.d) return (d>ptime.d);
		if (h!=ptime.h) return (h>ptime.h);
		if (min!=ptime.min) return (min>ptime.min);
		if (s!=ptime.s) return (s>ptime.s);
		return 0;
	}
	
	bool operator>=(const type_time ptime)const
	{
		return (*this==ptime||*this>ptime);
	}
	
	bool operator<(const type_time ptime)const
	{
		return (ptime>*this);
	}
	
	bool operator<=(const type_time ptime)const
	{
		return (ptime>=*this);
	}
	
};
#else
#ifdef testing
#pragma message ("type_time.hpp was included again.")
#endif
#endif
