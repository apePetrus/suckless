//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		                                            /*Update Interval*/	    /*Update Signal*/
	{ "",        "date '+%d/%b/%Y (%a) %I:%M%p'"                           , 60,                     10 },
    { "",        "amixer sget Master | awk -F'[][]' '/Left:/ { print $2 }'", 0 ,                     10 },
    { "",        "acpi | awk '{print $4}' | sed s/,//"                     , 10,                     21 },
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
