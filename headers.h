//takes in an input (in) from main and returns nothing. This function is the bulk of our shell. It makes a fork and parses the input to determine its main command. If the command is execvp-able, it does the command. Otherwise, we will redirect it elsewhere.
void execute(char* in);
