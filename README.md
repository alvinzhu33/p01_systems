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

##Unsuccessful Implements:
* Colors not differentiated for user input and command output.


##Limits:
* Piping is limited to a single pipe.
* Redirecting only accepts two arguments, aka ls > file, cat < file.
* You cannot pipe and redirect in the same command.

##Bugs:
* None currently found. Hope there aren't any ;(


##Function Headers:
Takes in an input (in) from main and returns nothing. This function is the bulk of our shell. It makes a fork and parses the input to determine its main command. If the command is execvp-able, it does the command. Otherwise, we will redirect it elsewhere.
	
	void execute(char* in);

Takes in an string (stripping) and strips off all excess spaces (in front "    ls", in middle "ls     -l", in back "ls        "). Returns the nicely stripped string

	char* stripper(char* stripping);

Redirects for ">" (it changes the output)

	void changeOutput(char *s[],char *f);

Redirects for "<" (it changes the input)

	void changeInput(char *s[],char *f);

