static const Block blocks[] = {
	/*Icon*/    /*Command*/    /*Update Interval*/    /*Update Signal*/
	{ "",       "clock.sh",    60,                    10 },
    { "",       "volume.sh",   0 ,                    11 },
    // { "",       "battery.sh",  10,                    12 },
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
