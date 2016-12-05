# p01_systems
by Alvin Zhu, Karen Huang, and Billy Wong

##Successful Implements:
* Continuously forks and executes commands.
* Parses multiple commands on the same line using ";".
* Exit is functional.
* Redirections are functional for both "<" and ">".
* Pipes are functional.
* Always shows current working directory.
* Pretty colors for easier read.
* Multiple spaces are stripped out (something like "          ls      -l     " works).
* Prints picture of horse-thing if first word is unicorn, pegasus, magic, or pretty.


##Unsuccessful Implements:
* Colors not differentiated for user input and command output.


##Limits:
* Piping is limited to a single pipe.
* Redirecting only accepts two arguments, aka ls > file, cat < file.
* You cannot pipe and redirect in the same command.

##Bugs:
* None currently found. Hopefully there's nothing to swat...


##Files and Function Headers:

####void execute(char* in);
* Input: string in
* Output: Nothing
* Function: This function is the bulk of our shell. It makes a fork and parses the input to determine its main command. If the command is execvp-able, it does the command. Otherwise, we will redirect it elsewhere.

####int main();
* Input: Nothing
* Output: 0 (Nothing)
* Function: Prints the current working directory in blue and receives user input.

####char* stripper(char* stripping);
* Input: string stripping
* Output: string stripping but without the multiple spaces
* Function: Strips off all excess spaces in stripping (in the front ["    ls"], in the middle ["ls     -l"], and in the back ["ls        "]).

####void changeOutput(char *s[],char *f);
* Input: array of strings s and string f
* Output: Nothing
* Function: Redirects for ">" (it changes the output).

####void changeInput(char *s[],char *f);
* Input: array of strings s and string f
* Output: Nothing
* Function: Redirects for "<" (it changes the input).

####void piper(char *s[],char *f);
* Input: array of strings s and string f
* Output: Nothing
* Function: Accomplishes the piping for our shell.
