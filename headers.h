//Input: string in
//Output: Nothing
//Function: This function is the bulk of our shell. It makes a fork and parses the input to determine its main command. If the command is execvp-able, it does the command. Otherwise, we will redirect it elsewhere.
void execute(char* in);

//Input: string stripping
//Output: string stripping but without the multiple spaces
//Function: Strips off all excess spaces in stripping (in the front ["    ls"], in the middle ["ls     -l"], and in the back ["ls        "]).
char* stripper(char* stripping);

//Input: array of string s and string f
//Output: Nothing
//Function: Redirects for ">" (it changes the output).
void changeOutput(char *s[],char *f);

//Input: array of string s and string f
//Output: Nothing
//Function: Redirects for "<" (it changes the input).
void changeInput(char *s[],char *f);

//Input: string comStr and array of string exeCom
//Output: Nothing
//Function: Accomplishes the piping for our shell.
void piper(char *comStr, char *exeCom[]){
