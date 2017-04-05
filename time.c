// Module include
#include "time.h"

// Julian calender leap year test
unsigned int	leapyear(unsigned int year)
{
	unsigned int leap = 0;
	if ((year % 4) == 0)
		leap = 1;
	if ((year % 100) == 0)
		leap = 0;
	if ((year % 400) == 0)
		leap = 1;
	return leap;
}

// Leapdays (since 1970 epoch)
unsigned int	leapdays(unsigned int year, unsigned int doy)
{
	unsigned int	days;
	if ((leapyear(year) == 1) && (doy <= 31+28))
		year--;
	days = (year-1970+2) / 4;
	days -= year / 100 - 15;
	days += year / 400;
	return days;
}

// Julian calender month from year and day of year
unsigned int	doy2month(unsigned int year, unsigned int doy)
{
	unsigned int leap;
	leap = leapyear(year);
	if (doy <= 31)
		return 1;
	doy -= 31;
	if (doy <= 28)
		return 2;
	if (leap == 1)
	{
		if (doy == 29)
			return 2;
		doy--;
	}
	doy -= 28;
	if (doy <= 31)
		return 3;
	doy -= 31;
	if (doy <= 30)
		return 4;
	doy -= 30;
	if (doy <= 31)
		return 5;
	doy -= 31;
	if (doy <= 30)
		return 6;
	doy -= 30;
	if (doy <= 31)
		return 7;
	doy -= 31;
	if (doy <= 31)
		return 8;
	doy -= 31;
	if (doy <= 30)
		return 9;
	doy -= 30;
	if (doy <= 31)
		return 10;
	doy -= 31;
	if (doy <= 30)
		return 11;
	doy -= 30;
	return 12;
}

// Julian calender month from year and day of month
unsigned int	doy2dom(unsigned int year, unsigned int doy)
{
	unsigned int leap;
	leap = leapyear(year);
	if (doy <= 31)
		return doy;
	doy -= 31;
	if (doy <= 28)
		return doy;
	if (leap == 1)
	{
		if (doy == 29)
			return doy;
		doy--;
	}
	doy -= 28;
	if (doy <= 31)
		return doy;
	doy -= 31;
	if (doy <= 30)
		return doy;
	doy -= 30;
	if (doy <= 31)
		return doy;
	doy -= 31;
	if (doy <= 30)
		return doy;
	doy -= 30;
	if (doy <= 31)
		return doy;
	doy -= 31;
	if (doy <= 31)
		return doy;
	doy -= 31;
	if (doy <= 30)
		return doy;
	doy -= 30;
	if (doy <= 31)
		return doy;
	doy -= 31;
	if (doy <= 30)
		return doy;
	doy -= 30;
	return doy;
}

// Convert into UNIX/POSIX epoch time, sec steps
unsigned long	epochtime(unsigned int year, unsigned int doy, unsigned int hour, unsigned int min, unsigned int sec)
{
	unsigned long	time;

	// Process years
	time = year-1970;

	// Process days
	time *= 365;
	time += leapdays(year, doy);
	time += doy-1;

	// Process hours
	time *= 24;
	time += hour;

	// Process min
	time *= 60;
	time += min;

	// Process sec
	time *= 60;
	time += sec;
	
	return time;
}

// Convert into UNIX/POSIX epoch time, ns steps
unsigned long	epochtimens(unsigned int year, unsigned int doy, unsigned int hour, unsigned int min, unsigned int sec, unsigned int ns)
{
	unsigned long	time;

	// Process seconds
	time = epochtime(year, doy, hour, min, sec);

	// Process nanoseconds
	time *= 1000000000L;
	time += ns;

	return time;
}
