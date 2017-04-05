// Standard C includes
#include <stdio.h>

// Project includes
#include "tb.h"

// Module include
#include "time.h"

// Duplicate include test
#include "time.h"

// Test statistics variables
TB_VAR(time);

void	tb_leapyear()
{
	// Test 4 year rule
	TB_TEST_EXPECT_M_UINT(time,leapyear(1984),1,"1984 is leap year");
	TB_TEST_EXPECT_M_UINT(time,leapyear(1985),0,"1985 is not leap year");
	TB_TEST_EXPECT_M_UINT(time,leapyear(1986),0,"1986 is not leap year");
	TB_TEST_EXPECT_M_UINT(time,leapyear(1987),0,"1987 is not leap year");
	TB_TEST_EXPECT_M_UINT(time,leapyear(1988),1,"1988 is leap year");
	// Test 100 & 400 year rule
	TB_TEST_EXPECT_M_UINT(time,leapyear(1600),1,"1600 is leap year");
	TB_TEST_EXPECT_M_UINT(time,leapyear(1700),0,"1700 is not leap year");
	TB_TEST_EXPECT_M_UINT(time,leapyear(1800),0,"1800 is not leap year");
	TB_TEST_EXPECT_M_UINT(time,leapyear(1900),0,"1900 is not leap year");
	TB_TEST_EXPECT_M_UINT(time,leapyear(2000),1,"2000 is leap year");
}

void tb_leapdays()
{
	unsigned int i;
	unsigned int year;
	unsigned int leap_days = 0;
	for (year = 1970; year <= 2400; year++)
	{
		unsigned int leap_year = leapyear(year);
		unsigned int days = 365 + leap_year;
		for (i = 1; i <= days; i++)
		{
			// Insert on the 29th feb
			if ((leap_year == 1) && (i == 31+29))
				leap_days++;
			TB_TEST_EXPECT_M_UINT(time,leapdays(year,i),leap_days,"has x leapdays");
		}
	}
			     
}

void tb_doymonth()
{
	unsigned int i,j;

	// Test for 1970 - not a leap year
	for (i = 1; i <= 31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1970,i),1,"1 - Jan");
	for (j = i-1; i <= j+28; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1970,i),2,"2 - Feb");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1970,i),3,"3 - Mar");
	for (j = i-1; i <= j+30; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1970,i),4,"4 - Apr");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1970,i),5,"5 - May");
	for (j = i-1; i <= j+30; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1970,i),6,"6 - Jun");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1970,i),7,"7 - Jul");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1970,i),8,"8 - Aug");
	for (j = i-1; i <= j+30; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1970,i),9,"9 - Sep");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1970,i),10,"10 - Oct");
	for (j = i-1; i <= j+30; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1970,i),11,"11 - Nov");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1970,i),12,"12 - Dec");

	// Test for 1972 - not a leap year
	for (i = 1; i <= 31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1972,i),1,"1 - Jan");
	for (j = i-1; i <= j+29; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1972,i),2,"2 - Feb");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1972,i),3,"3 - Mar");
	for (j = i-1; i <= j+30; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1972,i),4,"4 - Apr");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1972,i),5,"5 - May");
	for (j = i-1; i <= j+30; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1972,i),6,"6 - Jun");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1972,i),7,"7 - Jul");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1972,i),8,"8 - Aug");
	for (j = i-1; i <= j+30; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1972,i),9,"9 - Sep");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1972,i),10,"10 - Oct");
	for (j = i-1; i <= j+30; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1972,i),11,"11 - Nov");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2month(1972,i),12,"12 - Dec");
}

void tb_doy2dom()
{
	unsigned int i,j;

	// Test for 1970 - not a leap year
	for (j = 0, i = 1; i <= 31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1970,i),i-j,"1 - Jan");
	for (j = i-1; i <= j+28; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1970,i),i-j,"2 - Feb");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1970,i),i-j,"3 - Mar");
	for (j = i-1; i <= j+30; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1970,i),i-j,"4 - Apr");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1970,i),i-j,"5 - May");
	for (j = i-1; i <= j+30; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1970,i),i-j,"6 - Jun");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1970,i),i-j,"7 - Jul");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1970,i),i-j,"8 - Aug");
	for (j = i-1; i <= j+30; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1970,i),i-j,"9 - Sep");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1970,i),i-j,"10 - Oct");
	for (j = i-1; i <= j+30; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1970,i),i-j,"11 - Nov");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1970,i),i-j,"12 - Dec");

	// Test for 1972 - not a leap year
	for (j = 0, i = 1; i <= 31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1972,i),i-j,"1 - Jan");
	for (j = i-1; i <= j+29; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1972,i),i-j,"2 - Feb");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1972,i),i-j,"3 - Mar");
	for (j = i-1; i <= j+30; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1972,i),i-j,"4 - Apr");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1972,i),i-j,"5 - May");
	for (j = i-1; i <= j+30; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1972,i),i-j,"6 - Jun");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1972,i),i-j,"7 - Jul");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1972,i),i-j,"8 - Aug");
	for (j = i-1; i <= j+30; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1972,i),i-j,"9 - Sep");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1972,i),i-j,"10 - Oct");
	for (j = i-1; i <= j+30; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1972,i),i-j,"11 - Nov");
	for (j = i-1; i <= j+31; i++)
		TB_TEST_EXPECT_M_UINT(time,doy2dom(1972,i),i-j,"12 - Dec");
}

void tb_epochtime()
{
	TB_TEST_EXPECT_M_ULONG(time,epochtime(1970,1,0,0,0),0UL,"1970-01-01T00:00:00");
	TB_TEST_EXPECT_M_ULONG(time,epochtime(1970,1,0,0,1),1UL,"1970-01-01T00:00:01");
	TB_TEST_EXPECT_M_ULONG(time,epochtime(1970,1,0,1,0),60UL,"1970-01-01T00:01:00");
	TB_TEST_EXPECT_M_ULONG(time,epochtime(1970,1,1,0,0),3600UL,"1970-01-01T01:00:00");
	TB_TEST_EXPECT_M_ULONG(time,epochtime(1970,2,0,0,0),86400UL,"1970-01-02T00:00:00");
	TB_TEST_EXPECT_M_ULONG(time,epochtime(1972,1,0,0,0),2UL*365*86400UL,"1972-01-01T00:00:00");
	TB_TEST_EXPECT_M_ULONG(time,epochtime(1972,1,0,0,1),2UL*365*86400UL+1UL,"1972-01-01T00:00:01");
	TB_TEST_EXPECT_M_ULONG(time,epochtime(1972,1,0,1,0),2UL*365*86400UL+60UL,"1972-01-01T00:01:00");
	TB_TEST_EXPECT_M_ULONG(time,epochtime(1972,1,1,0,0),2UL*365*86400UL+3600UL,"1972-01-01T01:00:00");
	TB_TEST_EXPECT_M_ULONG(time,epochtime(1972,2,0,0,0),2UL*365*86400UL+86400UL,"1972-01-02T00:00:00");
}

void tb_epochtimens()
{
	TB_TEST_EXPECT_M_ULONG(time,epochtimens(1970,1,0,0,0,0),0UL,"1970-01-01T00:00:00");
	TB_TEST_EXPECT_M_ULONG(time,epochtimens(1970,1,0,0,1,0),1000000000UL,"1970-01-01T00:00:01");
	TB_TEST_EXPECT_M_ULONG(time,epochtimens(1970,1,0,1,0,0),60000000000UL,"1970-01-01T00:01:00");
	TB_TEST_EXPECT_M_ULONG(time,epochtimens(1970,1,1,0,0,0),3600000000000UL,"1970-01-01T01:00:00");
	TB_TEST_EXPECT_M_ULONG(time,epochtimens(1970,2,0,0,0,0),86400000000000UL,"1970-01-02T00:00:00");
	TB_TEST_EXPECT_M_ULONG(time,epochtimens(1972,1,0,0,0,0),2UL*365*86400000000000UL,"1972-01-01T00:00:00");
	TB_TEST_EXPECT_M_ULONG(time,epochtimens(1972,1,0,0,1,0),2UL*365*86400000000000UL+1000000000UL,"1972-01-01T00:00:01");
	TB_TEST_EXPECT_M_ULONG(time,epochtimens(1972,1,0,1,0,0),2UL*365*86400000000000UL+60000000000UL,"1972-01-01T00:01:00");
	TB_TEST_EXPECT_M_ULONG(time,epochtimens(1972,1,1,0,0,0),2UL*365*86400000000000UL+3600000000000UL,"1972-01-01T01:00:00");
	TB_TEST_EXPECT_M_ULONG(time,epochtimens(1972,2,0,0,0,0),2UL*365*86400000000000UL+86400000000000UL,"1972-01-02T00:00:00");
}

int main()
{
	TB_VAR_RESET(time);
	printf("Testbench for time library\n");
	tb_leapyear();
	tb_leapdays();
	tb_doymonth();
	tb_doy2dom();
	tb_epochtime();
	tb_epochtimens();
	printf("Tests %3i Fails %i\n", time_tb_tests, time_tb_fails);
	if (time_tb_fails != 0)
	{
		printf("ERROR: FAIL!\n");
		return -1;
	}
	printf("PASS!\n");
	return 0;
}
