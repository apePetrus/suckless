static const Block blocks[] = {
  /*Icon*/    /*Command*/    /*Update Interval*/    /*Update Signal*/
  { "",       "readclock",   60,                    10 },
  { "",       "readvolume",  0 ,                    11 },
  { "",       "readbattery", 10,                    12 },
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
