static const Block blocks[] = {
  /*Icon*/    /*Command*/                 /*Update Interval*/    /*Update Signal*/
  { "",       "~/.local/bin/read-clock",   60,                    10 },
  { "",       "~/.local/bin/read-volume",  0 ,                    11 },
  { "",       "~/.local/bin/read-battery", 10,                    12 },
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
