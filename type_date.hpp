// type_date.hpp -*- C++ -*-

// Copyleft (!C) 2012-2014 by Bear Dictionary.Some Rights Reserved.

// This file is part of the R.one's calendar package. 
 
// @file include/type_date.hpp.
//  See main file to know History Versions.
//  This is NOT a Standard C++ Library header.
#ifndef __cplusplus
#error [wc!这是为C++编写的头文件!请使用C++编译器编译!||wc!This headfile is written for C++!Please run this Program by gc++!]
#endif
#ifndef __rone_type_date__
#define __rone_type_date__

#include<iostream> 
#include<ctime>
#include<string>
#include<cstring>
#include<cstdlib>
#include"funcsup.hpp" //Functions Support lib

class type_date
{
  protected:
	long long y;
	short m,d;
  public:
	bool isLawful()const;

	inline type_date &fill();
	inline type_date &fill(long long num);
	inline type_date &fill(long long year,short month,short day=1);
	inline type_date &fill(tm tmTime);
	type_date &fill(std::string dateAtString);

	type_date() {fill();}
	type_date(long long num) {fill(num);}
	type_date(long long year,short month,short day=1) {fill(year,month,day);}
	type_date(tm tmTime) {fill(tmTime);}
	type_date(std::string dateAtString) {fill(dateAtString);}

	static type_date now();
	
	inline short getDay()const;
	
	//Operators overloading
	type_date &operator=(long long days);
	
	operator long long()const;
	
	inline type_date& operator++();
	inline type_date operator++(int);
	inline type_date& operator--();
	inline type_date operator--(int);
	inline type_date &operator+=(const long long days);
	inline type_date &operator-=(const long long days);
	inline bool operator==(const type_date &cdate)const;
	inline bool operator!=(const type_date &cdate)const;
	inline bool operator>(const type_date &cdate)const;
	inline bool operator>=(const type_date &cdate)const;
	inline bool operator<(const type_date &cdate)const;
	inline bool operator<=(const type_date &cdate)const;
	
	friend inline std::ostream &operator<<(std::ostream &out,const type_date &t);
	
  private:
  	void inc();
	void dec();
};

bool type_date::isLawful()const 
{
	if (y==0 || m>DAYS_PER_BIG_MONTH || m<1 || d<1) return 0;
    if (d>getMaxDay(y,m)) return 0;
    return 1;
}

inline type_date &type_date::fill() {y=m=d=1;return *this;}
inline type_date &type_date::fill(long long num) {*this=num;return *this;}
inline type_date &type_date::fill(long long year,short month,short day) {y=year;m=month;d=day;if (!isLawful()) fill();return *this;}
inline type_date &type_date::fill(tm tmTime) 
  {fill(tmTime.tm_year+DATE_DIFFERENCE,tmTime.tm_mon+1,tmTime.tm_mday);if (!isLawful()) fill();return *this;}
type_date &type_date::fill(std::string dateAtString)
{
	long long ans[3];
	memset(ans,0,sizeof(ans));
	short numWhereToWrite=0,numBegin=0;
	for (int i=1;i!=dateAtString.size() && numWhereToWrite!=3;i++)
	{
		if (isdigit(dateAtString[i])) 
		{
			if (!isdigit(dateAtString[i-1]))
				numBegin=i;
			if (i==dateAtString.size()-1)
				ans[numWhereToWrite++]=atoi(dateAtString.c_str()+numBegin);
		}
		else if (isdigit(dateAtString[i-1]))
			 	ans[numWhereToWrite++]=atoi(dateAtString.c_str()+numBegin);
	}
	fill(ans[0],ans[1],ans[2]);
	if (!isLawful()) fill();
	return *this;
}

type_date type_date::now()
{
	type_date tmp;
	time_t tmp_localtime;
	tmp_localtime=time(NULL);
	tmp.fill(*localtime(&tmp_localtime));
	if (!tmp.isLawful()) tmp.fill();
	return tmp;
}	

inline short type_date::getDay()const 
{
	if (!isLawful()) return 0;
	long long days=*this;
	int ans;
	if (days>0) 
	{
		ans=days%DAYS_PER_WEEK;
		return (ans==0 ? 7:ans);
	}
	if (days<0)
	{
		ans=(DAYS_PER_WEEK+1)-((-days)%DAYS_PER_WEEK);
		return (ans==8 ? 1:ans);
	}
}

type_date &type_date::operator=(long long days)
{
	fill();
	if (days==0) return *this;
	short tmp_compadd=DAYS_PER_NORMAL_YEAR;
	long long tmp_lesstimes;
	y=1;
    if (days>0)
    {
      if ((days-1)>DAYS_IN_400_YEARS) 
	  {
	  	days--; 
	  	tmp_lesstimes=days/DAYS_IN_400_YEARS;
	  	days%=DAYS_IN_400_YEARS;
		y+=tmp_lesstimes*400;
		days++;
	  }
	  if ((days-1)>DAYS_IN_100_YEARS) 
	  {
	  	days--; 
	  	tmp_lesstimes=days/DAYS_IN_100_YEARS;
	  	days%=DAYS_IN_100_YEARS;
		y+=tmp_lesstimes*100;
		days++;
	  }
	  if ((days-1)>DAYS_IN_4_YEARS) 
	  {
	  	days--; 
	  	tmp_lesstimes=days/DAYS_IN_4_YEARS;
	  	days%=DAYS_IN_4_YEARS;
		y+=tmp_lesstimes*4;
		days++;
	  }
      m=1;
	  while (days>tmp_compadd)
      {
          y++;
          days-=tmp_compadd;
          tmp_compadd=getMaxDay(y);
      }
      tmp_compadd=DAYS_PER_BIG_MONTH;
      while (days>tmp_compadd)
      {
          m++;
          days-=tmp_compadd;
          tmp_compadd=getMaxDay(y,m);
      }
      d=days;
    }
    else
    {
      m=MONTHS_PER_YEAR;
      days=-days;
      if ((days-1)>DAYS_IN_400_YEARS) 
	  {
	  	days--; 
	  	tmp_lesstimes=days/DAYS_IN_400_YEARS;
	  	days%=DAYS_IN_400_YEARS;
		y+=tmp_lesstimes*400;
		days++;
	  }
	  if ((days-1)>DAYS_IN_100_YEARS) 
	  {
	  	days--; 
	  	tmp_lesstimes=days/DAYS_IN_100_YEARS;
	  	days%=DAYS_IN_100_YEARS;
		y+=tmp_lesstimes*100;
		days++;
	  }
	  if ((days-1)>DAYS_IN_4_YEARS) 
	  {
	  	days--; 
	  	tmp_lesstimes=days/DAYS_IN_4_YEARS;
	  	days%=DAYS_IN_4_YEARS;
		y+=tmp_lesstimes*4;
		days++;
	  }
	  while (days>tmp_compadd)
      {
          y++;
          days-=tmp_compadd;
          tmp_compadd=getMaxDay(y);
      }
      tmp_compadd=DAYS_PER_BIG_MONTH;
      while (days>tmp_compadd)
      {
          m--;
          days-=tmp_compadd;
          tmp_compadd=getMaxDay(y,m);
      }
      d=tmp_compadd-days+1;
      y*=-1;
    }    	
    if (!isLawful()) fill();
	return *this;	
}

type_date::operator long long()const 
{
	if (!isLawful()) return 0;
	long long tmp_y=y;
	short tmp_m=m,tmp_d=d;
	long long ans=0,tmp_lesstimes=0;
	if (tmp_y>0)
	{
	  if ((tmp_y-1)>400)
	  {
	  	tmp_y--;
	  	tmp_lesstimes=tmp_y/400;
	  	tmp_y%=400;
		ans+=tmp_lesstimes*DAYS_IN_400_YEARS;
		tmp_y++;
	  }
	  if ((tmp_y-1)>100) 
	  {
	  	tmp_y--;
	  	tmp_lesstimes=tmp_y/100;
	  	tmp_y%=100;
		ans+=tmp_lesstimes*DAYS_IN_100_YEARS;
		tmp_y++;
	  }
	  if ((tmp_y-1)>4) 
	  {
	  	tmp_y--;
	  	tmp_lesstimes=tmp_y/4;
	  	tmp_y%=4;
		ans+=tmp_lesstimes*DAYS_IN_4_YEARS;
		tmp_y++;
	  }
      for (long long i=1;i!=tmp_y;i++)
        ans+=getMaxDay(i);
      for (short i=1;i!=tmp_m;i++)
        ans+=getMaxDay(tmp_y,i);
      ans=ans+tmp_d;
    }
    else
    {
      tmp_y*=-1;
      if ((tmp_y-1)>400)
	  {
	  	tmp_y--;
	  	tmp_lesstimes=tmp_y/400;
	  	tmp_y%=400;
		ans+=tmp_lesstimes*DAYS_IN_400_YEARS;
		tmp_y++;
	  }
	  if ((tmp_y-1)>100) 
	  {
	  	tmp_y--;
	  	tmp_lesstimes=tmp_y/100;
	  	tmp_y%=100;
		ans+=tmp_lesstimes*DAYS_IN_100_YEARS;
		tmp_y++;
	  }
	  if ((tmp_y-1)>4) 
	  {
	  	tmp_y--;
	  	tmp_lesstimes=tmp_y/4;
	  	tmp_y%=4;
		ans+=tmp_lesstimes*DAYS_IN_4_YEARS;
		tmp_y++;
	  }
      for (long long i=tmp_y-1;i!=0;i--)
        ans+=getMaxDay(i);
      for (short i=MONTHS_PER_YEAR;i!=tmp_m-1;i--)
        ans+=getMaxDay(tmp_y,i);   
      ans=-(ans-tmp_d+1);
    }
	return ans;
}

inline type_date &type_date::operator++()
{
	inc();
	return *this; 
}

inline type_date type_date::operator++(int)
{
	type_date tmp=*this;
	inc();
	return tmp;
}

inline type_date &type_date::operator--()
{
	dec();
	return *this;
}

inline type_date type_date::operator--(int)
{
	type_date tmp=*this;
	dec();
	return tmp;
}

inline type_date &type_date::operator+=(const long long days)
{
	*this=*this+days;
	return *this;
} 

inline type_date &type_date::operator-=(const long long days)
{
	*this=*this-days;
	return *this;
} 

inline bool type_date::operator==(const type_date &cdate)const
{
	if (y==cdate.y&&m==cdate.m&&d==cdate.d) return 1;
	return 0;
}

inline bool type_date::operator!=(const type_date &cdate)const
{
	return !(cdate==*this);
}

inline bool type_date::operator>(const type_date &cdate)const
{
	if (y!=cdate.y) return (y>cdate.y);
	if (m!=cdate.m) return (m>cdate.m);
	if (d!=cdate.d) return (d>cdate.d);
	return 0;
}

inline bool type_date::operator>=(const type_date &cdate)const
{
	return (*this==cdate||*this>cdate);
}

inline bool type_date::operator<(const type_date &cdate)const
{
	return (cdate>*this);
}

inline bool type_date::operator<=(const type_date &cdate)const
{
	return (cdate>=*this);
}

inline void type_date::inc()
{
	if (d==getMaxDay(y,m))
		if (m==12) y++,m=d=1;
		else m++,d=1;
	else d++;
	if (y==0) y=1;
	return;  
}

inline void type_date::dec()
{
	if (d==1)
		if (m==1) y--,m=12,d=31;
		else {m--;d=getMaxDay(y,m);}
	else d--;
	if (y==0) y=-1;
	return;
}

inline std::ostream &operator<<(std::ostream &out,const type_date &t)
{
	out<<t.y<<"年"<<t.m<<"月"<<t.d<<"日"; return out;
}

#else
#ifdef testing
#pragma message ("type_date.hpp was included again.")
#endif
#endif
