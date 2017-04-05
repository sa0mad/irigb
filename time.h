
// Julian calender leap year test
extern unsigned int	leapyear(unsigned int year);

// Leapdays (since 1970 epoch)
extern unsigned int	leapdays(unsigned int year, unsigned int doy);

// Julian calender month from year and day of year
extern unsigned int	doy2month(unsigned int year, unsigned int doy);

// Julian calender month from year and day of month
extern unsigned int	doy2dom(unsigned int year, unsigned int doy);

// Convert into UNIX/POSIX epoch time, sec steps
extern unsigned long	epochtime(unsigned int year, unsigned int doy, unsigned int hour, unsigned int min, unsigned int sec);

// Convert into UNIX/POSIX epoch time, ns steps
extern unsigned long	epochtimens(unsigned int year, unsigned int doy, unsigned int hour, unsigned int min, unsigned int sec, unsigned int ns);
