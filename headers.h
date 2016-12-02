//takes in an input (in) from main and returns nothing. This function is the bulk of our shell. It makes a fork and parses the input to determine its main command. If the command is execvp-able, it does the command. Otherwise, we will redirect it elsewhere.
void execute(char* in);

//takes in an string (stripping) and strips off all excess spaces (in front "    ls", in middle "ls     -l", in back "ls        "). Returns the nicely stripped string
char* stripper(char* stripping);

//Redirects for ">" (it changes the output)
void changeOutput(char *s[],char *f);

//Redirects for "<" (it changes the input)
void changeInput(char *s[],char *f);
