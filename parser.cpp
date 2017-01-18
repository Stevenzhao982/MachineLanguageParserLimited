#include <iostream>
#include <fstream>
#include <limits.h>
using namespace std;

// Get the length of the word we are on for other function purposes.
int str_length(char * str)
{
	int length = 0;
	while (str[length] != '\0')
	{ 
		length++;
	}
	return length;
}

// Checks line for first character.
char firstNonWhitespaceChar(char* line)
{
    char firstChar;
    for (int i = 0; i < str_length(line); i++)
    {
        
        if (line[i] != ' ' && line[i] != '\t')
        {
            firstChar = line[i];
            break;
        }

    }
    return firstChar;
}

// Checks to see if our line is all white spaces, in which case it is a blank line.
// Checks to see if our line is all white spaces, in which case it is a blank line.
bool isBlankLine (char* line)
{
    bool blank = false;
    for (int i = 0; i < str_length(line); i++)
    {
        if (line[i] != ' ' && line[i] != '\t')
        {
            blank = false;
            break;
        }
        else 
        {
        blank = true;
        }

    }

if (str_length(line) == 0)
{
    blank = true;
}

    return blank;
}

// Splits a character array and prints out the pseudo substr1ngs
void subStr(char str[], int start, int end) // start = index to start substr1ng, end = index to end substr1ng (including that index element)
{
    if (start<=end)
    {
            for (int i = start; i <= end; i++)
            {
                cout << str[i];
            }
    }
}

// Converts our instruction to lower case for function strCmp
void  convertWord(char * word)
{
	for (int i = 0; i < str_length(word); i++)
	{
		if (word[i] >= 65 && word[i] <= 90) //condition of character is upercase
		{
			word[i] = word[i] + 32;	
		}
	}
}

// Converts our Operand numeral value in char form to int form
int strToInt(char * str){
    int length = str_length(str);
    bool minus = 0;
    double answer = 0;
    int val;
 
    if (str[0] == '-'){
            minus = 1;
        }
 
    if (minus){
        for (int i = 1; i < length; i++){
            int n = str[i] - '0';
            answer += n;
            answer *= 10;
 
            if (n > 9 || n < 0){
                return INT_MIN;
            }
 
        }
        if (answer/10 < INT_MIN || answer/10 > INT_MAX){
            cerr << "Error!" << endl;
            return INT_MIN;
        }
        else {
            val = answer;
        }
        return -(val/10);  
    }
    else{
        for (int i = 0; i < length; i++){
            int n = str[i] - '0';
            answer += n;
            answer *= 10;
 
            if (n > 9 || n < 0){
                return INT_MIN;
            }
        }
        if (answer/10 < INT_MIN || answer/10 > INT_MAX){
            cerr << "Error!" << endl;
            return INT_MIN;
        }
        else {
            val = answer;
        }
        return val/10;
    }
   
}

// Accepts a char array and splits it by white spaces or comma's then stores it by reference into another char array. When it splits and copies, it
// starts copying the 'line' characters into the 'word' array starting from when something that isnt a white space, end line, comma, or comment mark appears to
// when a white space or comma next appears. Everytime it copies from the line, it also replaces the copied values of the original line with white spaces so that
// we can reuse this function with the same line and another storage word to put another word section from line into this new storage that wasn't put into
// a word storage / char array already.
void split_Str (char* line, char* word)
{
    int j = 0;
    for (int i =0; i < str_length(line); i++)
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\0' && line[i] != ',')
        {
            while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0'  && line[i] != ',')
            {
                word [j] = line[i];
                line [i] = ' ';
                j++;
                i++;
            }

            if (line[i] == ' ' || line[i] == '\t' || line[i] == '\0' || line[i] == ',' )
            {
                break;
            }

        }
    }
}


// The problem with our split_Str function is that when we want to jump and we've run through the program, we'll jump back to empty lines because we
// emptied them when we took the words in them. Thus everytime we finish executing our split_Str function fora line (however many times) we must 
// refill the emptyline with the original version of the line. Essentially we need a function to first copy the line then run and split our line into
// words by split_Str then after that refill the line. We also need to completely empty the line incase we came across commas and skipped over them so...
// the correct order to do shit in is first copy the line, then split into sub words, then at the end empty the line and refill the line.
void copyLine (char* line, char* temp) // input line to copy into temp line
{
    for (int i = 0; i < str_length(line); i++)
    {
        temp[i] = line[i];
    }
}

void emptyLine (char*line)
{
    for (int i =0; i < str_length(line); i ++)
    {
        line[i] = ' ';
    }
}

void refillLine (char* line, char* temp) // input line to fill with previously copied temp line
{
    for (int i = 0; i < str_length(line); i++)
    {
        line[i] = temp[i];
    }
}


// Another problem with the split str1ng function is that even if two  commas follow each other, it won't give an error or anything, it'll split the line simply
// past the other comma. Thus we need to make a function that checks to see if (one) comma follows after a word/ split line properly.
// These two functions are kinda broken but we can make them work -> just as soon as one of these gets evaluated as false, the whole line of instruction will become invalid so it's all good.
// ALSO IMPORTANT: MUST CALL THESE FUNCTIONS IN A TRUTH STATEMENT IN CONJUNCTION WITH CORRECT NUMBER OF COMMAS IN OVERALL LINE FUNCTION, ITS IMPORTANT THAT 
// both truths must evaluate to true, as in (isnumberofcommascorrect == correctamount && iscommacorrect2/3operands == true)

bool isCommaCorrectTwoOperands (char* line) // This must be called right after spliting our opCode and before spliting for our first operand.
{

    // correct if after we split to get our operand we have ->   [space] [words/letters] [spaces] [comma] [space] [words/letters] [space]
    bool isCorrect = false;
    bool encounterChar = false;
    bool encounterSpaceAfterChar = false;
    int i = 0;

    if (firstNonWhitespaceChar(line) == ',')
    {   
        return isCorrect;
    }

    // 0 is at 48, 9 is at 57
    // A is at 65. Z is at 90
    // a is at 97, z is at 122
    // - is at 45

    while (line[i] != ',' && i<str_length(line))
    {
        if ( (line[i] >= 65 && line[i] <= 90) || (line[i] >= 97 && line[i] <= 122) || (line[i] >= 48 && line[i] <= 57) || line[i] == 45)
        {
            if (encounterSpaceAfterChar == true) // encounterspaceafter is set to true only if a word/letter was previously encountered, so if its true within this loop, 
                                                // it means we went from (possible space) (register/memory location) (space) (register/memory location) (comma) which is wrong
            {
                isCorrect = false;
                return isCorrect;
            }

            else
            {
                encounterChar = true;
            }
        }

        if (encounterChar == true && (line[i] == ' ' || line[i] == '\t'))
        {
            encounterSpaceAfterChar = true;
        }


        i ++;
    }


    if (line[i] == ',' && line[i+1] != ',' && line[i-1] != ',' && i<str_length(line))
        {
            isCorrect = true;
            return isCorrect;
        }

    else 
    {
        return false;
    }

}





bool isCommaCorrectThreeOperands (char* line) // Must be executed in a check in conjunction with #commas == 2 only after the first str_split once the opcode is gone but before the first operand split
{
    bool isCorrect = false;
    bool encounterChar = false;
    bool encounterSpaceAfterChar = false;
    int i = 0;
    
    if (firstNonWhitespaceChar(line) == ',')
    {
        return isCorrect;
    }

    // 0 is at 48, 9 is at 57
    // A is at 65. Z is at 90
    // a is at 97, z is at 122
    // what is allowable:   "  [spaces]  [words/letters] [spaces] [comma]  [spaces] [words/letters] [spaces] [comma] [spaces] [words/letters] [spaces]"

    while (line[i] != ',' && i<str_length(line))
    {
        if ( (line[i] >= 65 && line[i] <= 90) || (line[i] >= 97 && line[i] <= 122) || (line[i] >= 48 && line[i] <= 57) )
        {
            if (encounterSpaceAfterChar == true) // encounterspaceafter is set to true only if a word/letter was previously encountered, so if its true within this loop, 
                                                // it means we went from (possible space) (register/memory location) (space) (register/memory location) (comma) which is wrong
            {
                isCorrect = false;
                return isCorrect;
            }

            else
            {
                encounterChar = true;
            }
        }

        if (encounterChar == true && (line[i] == ' ' || line[i] == '\t'))
        {
            encounterSpaceAfterChar = true;
        }


        i ++;
    }


    i++; // incremement i since our while loop ended at an i where line[i] = ',';

    
    if (encounterChar == true && line[i] != ',')
    {
        encounterChar = false;
        encounterSpaceAfterChar = false;

        
        while (line[i] != ',' && i<str_length(line))
        {
            if ( (line[i] >= 65 && line[i] <= 90) || (line[i] >= 97 && line[i] <= 122) || (line[i] >= 48 && line[i] <= 57) )
            {
                
                if (encounterSpaceAfterChar == true) // executes only if we are at a word and have already ran into a word followed by spaces -> meaning a comma is missing
                {
                    isCorrect = false;
                   
                    return isCorrect;
                }

                else
                {
                   
                    encounterChar = true;
                }
            }

            if (encounterChar == true && (line[i] == ' ' || line[i] == '\t')) // executes only if we run into a blank space and we previously already ran into a word
            {   
                encounterSpaceAfterChar = true;
            }

            i++;
        }

        if (line[i] == ',' && line[i+1] != ',' && line[i-1] != ',' && i<str_length(line))
        {
            isCorrect = true;
            return isCorrect;
        }

    }

    else 
    {
        isCorrect = false;
        return isCorrect;
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Compare an instruction word wise to lower case versions of the correct and acceptable instructions.
int strCmp(char word1[], char word2[])
{
    convertWord(word1);
    convertWord(word2); 
    int a = 0;
 
    while (word1[a] != '\0' || word2[a] != '\0'){
        if (word1[a] == word2[a]){
            a++;
        }
        else if (word1[a] < word2[a]){
            return 0;
        }
        else if (word1[a] > word2[a]){
            return 0;
        }
    }
 
    if (str_length(word1) == str_length(word2)){
        return 1;
    }
    else if (str_length(word1) > str_length(word2)){
        return 0;
    }
    else {
        return 0;
    }
}

int numberOfCommas (char *line)
{
    int comma = 0;
    for (int i =0; i < str_length(line); i++)
    {
        if (line[i] == ',')
        comma++;

        if (line[i] == '#')
        {
            break;
        }
    }
    return comma;
}

///////////////////////////////////////////////// W H E R E    T H E     C A N C E R    H A P P E N S ////////////////////////////////////////////
int main(int argc, char *argv[])
{
	// Define our input/output files and open them
	char fileName[50];
	fstream inFile;
	fstream outFile;
	inFile.open(argv[1]);
	outFile.open("output.txt");



	// Define a counter for the valid instruction line we are on (starts from what code directive declared) - also count number of code directives since we can only have one.
	int Code = 0;
    int CodeDirectiveCount = 0;
    // Define our data and check to see if code overlaps (as in PC) - also count number of data directives since we can only have one.
    int Data = 0;
    int DataDirectiveCount =0;
	// Counter for the number of arithmetic (add, sub, mul, div) instructions executed.
	int ALU = 0;
	// Counter for the total number of instructions executed (including store/load, jump, arithmetic)
	int instructions = 0;
	// Counter for the number of load and store instructions executed.
	int loadStore = 0;
	// Counter for the number of compare and jump instructions executed.
	int compareJump = 0;
    // Counter for our total number of lines including comments and blank lines.
    int totalLines = 0;
    // Counter for our total number of blank lines and comment lines.
    int blankOrCommentLines = 0;
    // Counter for code directive comparison (code directive must come before any other opcode or label decleration/detection aside from data decleraetion.
    int instructionOrLabelOrCodeDirectiveExecuteOrder = 0;
    // Truth variable for whether a code directive has been declared or not
    bool isThereCodeDirective = false;
  


	// initial error checking for arguments in command line
	// Program should only run with 2 arguments on command line - the program.exe and the textfile we want to use for input.
	if(argc != 2) 
	{
		cerr << "Error. Incorrect number of arguments passed in command line." << endl;
		return -1;
	}

	// If file cannot be opened - output an error. (proper input should be -> program.exe input.txt)
	if (inFile.fail()) 
	{
		cerr << "Error opening file." << endl;
		return -1;
	}


    // Shit we need to use in the actual looping 
	const int MAXLINE = 256; // Arbitrarily huge number for our strs to specify our str sizes.
    char labels [256][MAXLINE] = {0};
    char oneline[257]; // Char array to hold our lines.
    oneline[256] = '\0';// null terminate each oneline with a null termination.

    // Main while loop - everything happens in here
    while (inFile)
    {
        inFile.getline(oneline, MAXLINE);
        totalLines++;
        cout << totalLines << ". ";
       


    //////////////////////////////////////////////////// l o o p  while still in file/ still have next line ///////////////////////////////////////////
    


     // Check if line is blank line.
    if ( isBlankLine(oneline))
    {
       cout << "This is a blank line. " << endl;
       blankOrCommentLines++; 
    }


    // Check if line starts as a comment -> implies whole line is comment
    else if (firstNonWhitespaceChar(oneline) == '#')
    {
       cout << "This is a comment line. " << endl;
       blankOrCommentLines++;
    }



    // If it isn't a blank line and it isn't only a comment line, we have to do our main operand bullshit in this
    else if (!isBlankLine(oneline) && firstNonWhitespaceChar(oneline) != '#')
    {
       
       
     
        
       

        // We can only have 3 operands & one op code at max, and they must come sequentially. The first must also not be a number, so we can define 4 char arrays 
        // to hold them. We must then split our line to words and fill them. Declare them intiially as empty so that if we perhaps only get 3 words/ fill 3
        // we can eliminate the possibility of the instruction being one that requires 4 parameters. This way we may also ignore anything after the last
        // operand SO LONG AS IT BEGINS WITH A # - anything else is an error (e.g. Add 2, 3, 4, sdfsdffd is invalid), (e.g. Add 2,3,4 #sdf is valid)
        // These defined variables below may store different things depending on the case.
        char opCode [MAXLINE] = {0}; 
        char operand1 [MAXLINE] = {0};
        char operand2 [MAXLINE] = {0};
        char operand3 [MAXLINE] = {0};
        char operand4 [MAXLINE] = {0};
        char tempLine[MAXLINE] = {0}; // For refilling our emptied line when we split our line into words and empty the line. 

        // Comparison shit so we don't get a bunch of depreciated warnings when debugging and shit
        char r1 [256] = "r1";
        char r2 [256] = "r2";
        char r3 [256] = "r3";
        char r4 [256] = "r4";
        char r5 [256] = "r5";
        char r6 [256] = "r6";
        char r7 [256] = "r7";
        char r8 [256] = "r8";
        char r9 [256] = "r9";

        // Copy our line to reload at the very end after splitting and erasing 
        copyLine(oneline, tempLine);

        // Now split by our 4 possible elements (op code, operand 1- 3)
        // By our cases, if our first op code thing is a label/directive, this will mean that one of the next subsequent element will be filled so if 
        // in that case operand 2 and operand 3 are empty but 1 and opcode are valid, we can copy op and operand1 into code, or data, or jump label, etc.
        // Essentially, we'll define our PC constant as what code specifies it as, then as we go on meeting valid instructions, we'll increment code
        // and ensure through a check case that it doesn't overlap with data.
        // As well, after you split the line the required number of times based on number of operations, if nextchar evaluates something after the last split that isn't a whitespace, newline, termination, or #, then the line is wrong
        split_Str(oneline,opCode);
        
        // Convert all our words to lower case first for easier and efficient comparisons.
        convertWord(opCode);

        
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////// D I S R U P T I V E   S T A T E   M A C H I N E ////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        


        //////////////////////////// start of ld case /////////////////////
        if (strCmp(opCode, "ld") == 1)
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            if (numberOfCommas(oneline) == 1 && isCommaCorrectTwoOperands(oneline)) // if the comment placements check out then...
            {
                split_Str(oneline, operand1);
                convertWord(operand1);
                bool isOperand1ANumber = true; 

                for (int i = 0; i < str_length(operand1); i++)
                {
                    if (operand1[i] < 48 || operand1[i] > 57)
                    {
                        isOperand1ANumber = false;
                        break;
                    }
                }


                if (isOperand1ANumber == true) // Operand1 is a valid number memory adress
                {
                    split_Str(oneline, operand2);
                    convertWord(operand2); // should contain an R? register value
                    
                    // If operand2 is a valid register
                    if ( (strCmp(operand2, r1) == 1) || (strCmp(operand2, r2) == 1) || (strCmp(operand2, r3) == 1) || (strCmp(operand2, r4) == 1) || (strCmp(operand2, r5) == 1) || (strCmp(operand2, r6) == 1) || (strCmp(operand2, r7) == 1) || (strCmp(operand2, r8) == 1) || (strCmp(operand2, r9) == 1) )
                    {
                        split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand3 if all is well

                        if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                        {
                             cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                        }

                        else
                        {
                            // Code to do the ld instruction
                            loadStore++;     
                        }

                    }
                    else
                    {
                        cerr << "Error on line " << totalLines << ": Invalid operand. " ;
                    }
                }


                else if (isOperand1ANumber == false) // Operand1 is not a number memory adress
                {
                    // First check to see if operand1 is even valid
                    if ( (strCmp(operand1, r1) == 1) || (strCmp(operand1, r2) == 1) || (strCmp(operand1, r3) == 1) || (strCmp(operand1, r4) == 1) || (strCmp(operand1, r5) == 1) || (strCmp(operand1, r6) == 1) || (strCmp(operand1, r7) == 1) || (strCmp(operand1, r8) == 1) || (strCmp(operand1, r9) == 1) )
                    {
                        split_Str(oneline, operand2);
                        convertWord(operand2); // should contain an R? register value

                        // If operand1 is valid then check for whether operand2 is valid
                        if ( (strCmp(operand2, r1) == 1) || (strCmp(operand2, r2) == 1) || (strCmp(operand2, r3) == 1) || (strCmp(operand2, r4) == 1) || (strCmp(operand2, r5) == 1) || (strCmp(operand2, r6) == 1) || (strCmp(operand2, r7) == 1) || (strCmp(operand2, r8) == 1) || (strCmp(operand2, r9) == 1) )
                        {
                            split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand3 if all is well

                            if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                            {
                                cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                            }

                            else
                            {
                            // Code to do the ld instruction
                            loadStore++;
                            }
                         
                        }

                        else
                        {
                            cerr << "Error on line " << totalLines << ": Invalid operand. " ;
                        }
                    }

                    else
                    {
                        cerr << "Error on line " << totalLines << ": Invalid operand. " ;
                    }
                }
                

            }
           
           else 
           {
             cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand." ; 
           }

        }
        /////////////////////////// end of ld case /////////////////////



        ////////////////////////// start of ldi case ///////////////////
        else if (strCmp(opCode, "ldi") == 1)
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            
            if (numberOfCommas(oneline) == 1 && isCommaCorrectTwoOperands(oneline)) // if the comment placements check out then...
            {
                split_Str(oneline, operand1);
                convertWord(operand1);
                bool isOperand1ANumber = true; 

                for (int i = 0; i < str_length(operand1); i++)
                {
                    if (operand1[i] < 48 || operand1[i] > 57)
                    {
                        isOperand1ANumber = false;
                        break;
                    }
                }

                if (isOperand1ANumber == true) // Operand1 is a valid number memory address
                {
                    split_Str(oneline, operand2);
                    convertWord(operand2); // should contain an R? register value
                    // If operand2 is a valid register
                    if ( (strCmp(operand2, r1) == 1) || (strCmp(operand2, r2) == 1) || (strCmp(operand2, r3) == 1) || (strCmp(operand2, r4) == 1) || (strCmp(operand2, r5) == 1) || (strCmp(operand2, r6) == 1) || (strCmp(operand2, r7) == 1) || (strCmp(operand2, r8) == 1) || (strCmp(operand2, r9) == 1) )
                    {
                        split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand3 if all is well

                        if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#') // if operand3 is not empty and not a comment
                        {
                             cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                        }

                        else
                        {
                            // Code to do the ldi instruction
                            loadStore++;     
                        }

                    }

                   
                    else // If operand2 is not a valid operand
                    {
                        cerr << """Error on line " << totalLines << ": Invalid operand." ;
                    }
                }
           
                else if  (isOperand1ANumber == false) // Operand1 is not a valid number memory address
                {
                     cerr << "Error on line " << totalLines << ": Invalid operand." ;
                }

            }

            else 
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand." ; 
            }
        }
        ////////////////////////// end of ldi case /////////////////////



        ///////////////////////// start of sd case ////////////////////
        else if (strCmp(opCode, "sd") == 1)
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            
            if (numberOfCommas(oneline) == 1 && isCommaCorrectTwoOperands(oneline)) // if the comment placements check out then...
            {
                split_Str(oneline, operand1);
                convertWord(operand1);

                if ( ((strCmp(operand1, r1) == 1) || (strCmp(operand1, r2) == 1) || (strCmp(operand1, r3) == 1) || (strCmp(operand1, r4) == 1) || (strCmp(operand1, r5) == 1) || (strCmp(operand1, r6) == 1) || (strCmp(operand1, r7) == 1) || (strCmp(operand1, r8) == 1) || (strCmp(operand1, r9) == 1) )) // Operand1 is a register
                {
                    bool isOperand2ANumber = true; 
                    split_Str(oneline, operand2);
                    convertWord(operand2);


                    for (int i = 0; i < str_length(operand2); i++)
                    {
                        if (operand2[i] < 48 || operand2[i] > 57)
                        {
                            isOperand2ANumber = false;
                            break;
                        }
                    }


                    if (isOperand2ANumber == false) // in this case operand 2 should be a registor of r?
                    {
                        if ( ((strCmp(operand2, r1) == 1) || (strCmp(operand2, r2) == 1) || (strCmp(operand2, r3) == 1) || (strCmp(operand2, r4) == 1) || (strCmp(operand2, r5) == 1) || (strCmp(operand2, r6) == 1) || (strCmp(operand2, r7) == 1) || (strCmp(operand2, r8) == 1) || (strCmp(operand2, r9) == 1) ))
                        {
                            split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand3 if all is well (or it can be an operand 3 of a comment)

                            if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                            {
                               cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                            }

                            else
                            {
                                // carry out the sd instructions here
                                loadStore++;
                            }
                        }

                        else
                        {
                            cerr << "Error on line " << totalLines << ": Invalid operand. " ;   
                        }
                    }

                  
                    else if (isOperand2ANumber == true) // in this case operand 2 is a pure number
                    {
                        split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand3 if all is well (or it can be an operand 3 of a comment)

                        if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                        {
                            cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                        }
                        else
                        {
                            // carry out the sd instructions here
                            loadStore++;
                        }
                    }

                }

                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand" ;
                }

            }
        
            else // if comma seperation is wrong...
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand." ;  
            }

        }
        ///////////////////////// end of sd case ///////////////////////




        ///////////////////////// start of sdi case ////////////////////
        else if (strCmp(opCode, "sdi") == 1)
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            
            if (numberOfCommas(oneline) == 1 && isCommaCorrectTwoOperands(oneline)) // if the comment placements check out then...
            {
                split_Str(oneline, operand1);
                convertWord(operand1);
                bool isOperand1ANumber = true; 
                

                for (int i = 0; i < str_length(operand1); i++)
                {
                    if ((operand1[i] < 48 || operand1[i] > 57) && operand1[i] != 45) // ensures that the first operand which is a number integer may be negative
                    {
                        isOperand1ANumber = false;
                        break;
                    }
                }


                if (isOperand1ANumber == true) // Operand1 is a number memory adress
                {
                    split_Str(oneline, operand2);
                    convertWord(operand2); // should contain an R? register value
                    bool isOperand2ANumber = true; 
    
                    for (int i = 0; i < str_length(operand2); i++)
                    {
                        if (operand2[i] < 48 || operand2[i] > 57)
                        {
                            isOperand2ANumber = false;
                            break;
                        }
                    }


                    if (isOperand2ANumber == true)
                    {
                        split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand3 if all is well

                        if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                        {
                            cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                        }

                        else
                        {
                            // Code to do the sdi instruction
                            loadStore++;     
                        }
                    }


                    else if (isOperand2ANumber == false)
                    {
                        if ( (strCmp(operand2, r1) == 1) || (strCmp(operand2, r2) == 1) || (strCmp(operand2, r3) == 1) || (strCmp(operand2, r4) == 1) || (strCmp(operand2, r5) == 1) || (strCmp(operand2, r6) == 1) || (strCmp(operand2, r7) == 1) || (strCmp(operand2, r8) == 1) || (strCmp(operand2, r9) == 1) )
                        {
                            split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand3 if all is well

                            if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                            {
                                cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                            }

                            else
                            {
                                // Code to do the sdi instruction
                                loadStore++;     
                            }
                        }

                        else
                        {
                            cerr << "Error on line " << totalLines << ": Invalid operand.";
                        }
                    }
                }

                else if (isOperand1ANumber == false ) // Operand1 is not a number memory adress
                {
                    
                    cerr << "Error on line " << totalLines << ": Invalid operand.";
                                     
                }
            }
           

            else 
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand." ;
            }

            
        }
        ///////////////////////// end of sdi case /////////////////////////
        





        //////////////////////// start of add case ////////////////////////
        else if (strCmp(opCode, "add") == 1) //ADD Ri, Rj, Rk
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            
            if (isCommaCorrectThreeOperands(oneline) && commas == 2) // if the comment placements check out then...
            {

                split_Str(oneline, operand1);
                convertWord(operand1);

                if ( ((strCmp(operand1, r1) == 1) || (strCmp(operand1, r2) == 1) || (strCmp(operand1, r3) == 1) || (strCmp(operand1, r4) == 1) || (strCmp(operand1, r5) == 1) || (strCmp(operand1, r6) == 1) || (strCmp(operand1, r7) == 1) || (strCmp(operand1, r8) == 1) || (strCmp(operand1, r9) == 1) )) // Operand1 is a register
                {
                    split_Str(oneline, operand2);
                    convertWord(operand2);

                        if ( ((strCmp(operand2, r1) == 1) || (strCmp(operand2, r2) == 1) || (strCmp(operand2, r3) == 1) || (strCmp(operand2, r4) == 1) || (strCmp(operand2, r5) == 1) || (strCmp(operand2, r6) == 1) || (strCmp(operand2, r7) == 1) || (strCmp(operand2, r8) == 1) || (strCmp(operand2, r9) == 1) ))
                        {   
                            split_Str(oneline, operand3);
                            convertWord(operand3);

                            if ( ((strCmp(operand3, r1) == 1) || (strCmp(operand3, r2) == 1) || (strCmp(operand3, r3) == 1) || (strCmp(operand3, r4) == 1) || (strCmp(operand3, r5) == 1) || (strCmp(operand3, r6) == 1) || (strCmp(operand3, r7) == 1) || (strCmp(operand3, r8) == 1) || (strCmp(operand3, r9) == 1) ))
                            {
                                split_Str(oneline, operand4); // Now we split our line again - there should be  an empty operand4 if all is well (or it can be an operand 4 of a comment)

                                if (str_length(operand4) != 0 && firstNonWhitespaceChar(operand4) != '#')
                                {
                                    cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                                }

                                else
                                {
                                    // carry out the add instructions here
                                    ALU++;
                                }
                            }
                            
                            else
                            {
                                cerr << "Error on line " << totalLines << ": Invalid operand. " ;  
                            }

                        }

                        else
                        {
                            cerr << "Error on line " << totalLines << ": Invalid operand. " ;     
                        }
                        
                }

                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand" ;
                }

                
            }
        
            else // if comma seperation is wrong...
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand." ; 
            }

        }
        /////////////////////// end of add case ///////////////////////////







        /////////////////////// start of addi case ///////////////////////////
        else if (strCmp(opCode, "addi") == 1) //ADDi Ri, nnnn, Rj
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            
            if (isCommaCorrectThreeOperands(oneline) && commas == 2) // if the comment placements check out then...
            {

                split_Str(oneline, operand1);
                convertWord(operand1);

                if ( ((strCmp(operand1, r1) == 1) || (strCmp(operand1, r2) == 1) || (strCmp(operand1, r3) == 1) || (strCmp(operand1, r4) == 1) || (strCmp(operand1, r5) == 1) || (strCmp(operand1, r6) == 1) || (strCmp(operand1, r7) == 1) || (strCmp(operand1, r8) == 1) || (strCmp(operand1, r9) == 1) )) // Operand1 is a register
                {
                    split_Str(oneline, operand2);
                    convertWord(operand2);
                    bool isOperand2ANumber = true; ///
    
                    for (int i = 0; i < str_length(operand2); i++)
                    {
                        if (operand2[i] < 48 || operand2[i] > 57)
                        {
                            isOperand2ANumber = false;
                            break;
                        }
                    }


                    if (isOperand2ANumber == true)
                    {   
                        split_Str(oneline, operand3);
                        convertWord(operand3);

                            if ( ((strCmp(operand3, r1) == 1) || (strCmp(operand3, r2) == 1) || (strCmp(operand3, r3) == 1) || (strCmp(operand3, r4) == 1) || (strCmp(operand3, r5) == 1) || (strCmp(operand3, r6) == 1) || (strCmp(operand3, r7) == 1) || (strCmp(operand3, r8) == 1) || (strCmp(operand3, r9) == 1) ))
                            {
                                split_Str(oneline, operand4); // Now we split our line again - there should be  an empty operand4 if all is well (or it can be an operand 4 of a comment)

                                if (str_length(operand4) != 0 && firstNonWhitespaceChar(operand4) != '#')
                                {
                                    cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                                }

                                else
                                {
                                    // carry out the addi instructions here
                                    ALU++;
                                }
                            }
                            
                            else
                            {
                                cerr << "Error on line " << totalLines << ": Invalid operand. " ;     
                            }

                    }

                    else
                    {
                        cerr << "Error on line " << totalLines << ": Invalid operand. " ;   
                    }
                        
                }

                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand" ;
                }

                
            }
        
            else // if comma seperation is wrong...
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand." ;
            }

        }
        /////////////////////// end of addi case ///////////////////////////





        /////////////////////// start of sub case //////////////////////////
        else if (strCmp(opCode, "sub") == 1) //SUB Ri, Rj, Rk 
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            
            if (isCommaCorrectThreeOperands(oneline) && commas == 2) // if the comment placements check out then...
            {

                split_Str(oneline, operand1);
                convertWord(operand1);

                if ( ((strCmp(operand1, r1) == 1) || (strCmp(operand1, r2) == 1) || (strCmp(operand1, r3) == 1) || (strCmp(operand1, r4) == 1) || (strCmp(operand1, r5) == 1) || (strCmp(operand1, r6) == 1) || (strCmp(operand1, r7) == 1) || (strCmp(operand1, r8) == 1) || (strCmp(operand1, r9) == 1) )) // Operand1 is a register
                {
                    split_Str(oneline, operand2);
                    convertWord(operand2);

                        if ( ((strCmp(operand2, r1) == 1) || (strCmp(operand2, r2) == 1) || (strCmp(operand2, r3) == 1) || (strCmp(operand2, r4) == 1) || (strCmp(operand2, r5) == 1) || (strCmp(operand2, r6) == 1) || (strCmp(operand2, r7) == 1) || (strCmp(operand2, r8) == 1) || (strCmp(operand2, r9) == 1) ))
                        {   
                            split_Str(oneline, operand3);
                            convertWord(operand3);

                            if ( ((strCmp(operand3, r1) == 1) || (strCmp(operand3, r2) == 1) || (strCmp(operand3, r3) == 1) || (strCmp(operand3, r4) == 1) || (strCmp(operand3, r5) == 1) || (strCmp(operand3, r6) == 1) || (strCmp(operand3, r7) == 1) || (strCmp(operand3, r8) == 1) || (strCmp(operand3, r9) == 1) ))
                            {
                                split_Str(oneline, operand4); // Now we split our line again - there should be  an empty operand4 if all is well (or it can be an operand 4 of a comment)

                                if (str_length(operand4) != 0 && firstNonWhitespaceChar(operand4) != '#')
                                {
                                    cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                                }

                                else
                                {
                                    // carry out the sub instructions here
                                    ALU++;
                                }
                            }
                            
                            else
                            {
                                cerr << "Error on line " << totalLines << ": Invalid operand. " ;    
                            }

                        }

                        else
                        {
                            cerr << "Error on line " << totalLines << ": Invalid operand. " ;  
                        }
                        
                }

                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand" ;
                }

                
            }
        
            else // if comma seperation is wrong...
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand." ;  
            }

        }
        /////////////////////// end of sub case ////////////////////////////







        /////////////////////// start of subi case //////////////////////////
        else if (strCmp(opCode, "subi") == 1) //SUBi Ri, nnnn, Rj
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            
            if (isCommaCorrectThreeOperands(oneline) && commas == 2) // if the comment placements check out then...
            {

                split_Str(oneline, operand1);
                convertWord(operand1);

                if ( ((strCmp(operand1, r1) == 1) || (strCmp(operand1, r2) == 1) || (strCmp(operand1, r3) == 1) || (strCmp(operand1, r4) == 1) || (strCmp(operand1, r5) == 1) || (strCmp(operand1, r6) == 1) || (strCmp(operand1, r7) == 1) || (strCmp(operand1, r8) == 1) || (strCmp(operand1, r9) == 1) )) // Operand1 is a register
                {
                    split_Str(oneline, operand2);
                    convertWord(operand2);
                    bool isOperand2ANumber = true; 
    
                    for (int i = 0; i < str_length(operand2); i++)
                    {
                        if (operand2[i] < 48 || operand2[i] > 57)
                        {
                            isOperand2ANumber = false;
                            break;
                        }
                    }


                    if (isOperand2ANumber == true)
                    {   
                        split_Str(oneline, operand3);
                        convertWord(operand3);

                            if ( ((strCmp(operand3, r1) == 1) || (strCmp(operand3, r2) == 1) || (strCmp(operand3, r3) == 1) || (strCmp(operand3, r4) == 1) || (strCmp(operand3, r5) == 1) || (strCmp(operand3, r6) == 1) || (strCmp(operand3, r7) == 1) || (strCmp(operand3, r8) == 1) || (strCmp(operand3, r9) == 1) ))
                            {
                                split_Str(oneline, operand4); // Now we split our line again - there should be  an empty operand4 if all is well (or it can be an operand 4 of a comment)

                                if (str_length(operand4) != 0 && firstNonWhitespaceChar(operand4) != '#')
                                {
                                    cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                                }

                                else
                                {
                                    // carry out the subi instructions here
                                    ALU++;
                                }
                            }
                            
                            else
                            {
                                cerr << "Error on line " << totalLines << ": Invalid operand. " ;     
                            }

                    }

                    else
                    {
                        cerr << "Error on line " << totalLines << ": Invalid operand. " ;  
                    }
                        
                }

                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand" ;
                }

                
            }
        
            else // if comma seperation is wrong...
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand." ; 
            }

        }
        /////////////////////// end of subi case ////////////////////////////





        /////////////////////// start of mul case ///////////////////////////
        else if (strCmp(opCode, "mul") == 1) //MUL Ri, Rj, Rk
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            
            if (isCommaCorrectThreeOperands(oneline) && commas == 2) // if the comment placements check out then...
            {

                split_Str(oneline, operand1);
                convertWord(operand1);

                if ( ((strCmp(operand1, r1) == 1) || (strCmp(operand1, r2) == 1) || (strCmp(operand1, r3) == 1) || (strCmp(operand1, r4) == 1) || (strCmp(operand1, r5) == 1) || (strCmp(operand1, r6) == 1) || (strCmp(operand1, r7) == 1) || (strCmp(operand1, r8) == 1) || (strCmp(operand1, r9) == 1) )) // Operand1 is a register
                {
                    split_Str(oneline, operand2);
                    convertWord(operand2);

                        if ( ((strCmp(operand2, r1) == 1) || (strCmp(operand2, r2) == 1) || (strCmp(operand2, r3) == 1) || (strCmp(operand2, r4) == 1) || (strCmp(operand2, r5) == 1) || (strCmp(operand2, r6) == 1) || (strCmp(operand2, r7) == 1) || (strCmp(operand2, r8) == 1) || (strCmp(operand2, r9) == 1) ))
                        {   
                            split_Str(oneline, operand3);
                            convertWord(operand3);

                            if ( ((strCmp(operand3, r1) == 1) || (strCmp(operand3, r2) == 1) || (strCmp(operand3, r3) == 1) || (strCmp(operand3, r4) == 1) || (strCmp(operand3, r5) == 1) || (strCmp(operand3, r6) == 1) || (strCmp(operand3, r7) == 1) || (strCmp(operand3, r8) == 1) || (strCmp(operand3, r9) == 1) ))
                            {
                                split_Str(oneline, operand4); // Now we split our line again - there should be  an empty operand4 if all is well (or it can be an operand 4 of a comment)

                                if (str_length(operand4) != 0 && firstNonWhitespaceChar(operand4) != '#')
                                {
                                    cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                                }

                                else
                                {
                                    // carry out the mul instructions here
                                    ALU++;
                                }
                            }
                            
                            else
                            {
                                cerr << "Error on line " << totalLines << ": Invalid operand. " ;   
                            }

                        }

                        else
                        {
                            cerr << "Error on line " << totalLines << ": Invalid operand. " ;   
                        }
                        
                }

                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand" ;
                }

                
            }
        
            else // if comma seperation is wrong...
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand." ; 
            }

        }
        /////////////////////// end of mul case /////////////////////////////
       




        /////////////////////// start of muli case //////////////////////////
        else if (strCmp(opCode, "muli") == 1) //MULi Ri, nnnn, Rj
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            
            if (isCommaCorrectThreeOperands(oneline) && commas == 2) // if the comment placements check out then...
            {

                split_Str(oneline, operand1);
                convertWord(operand1);

                if ( ((strCmp(operand1, r1) == 1) || (strCmp(operand1, r2) == 1) || (strCmp(operand1, r3) == 1) || (strCmp(operand1, r4) == 1) || (strCmp(operand1, r5) == 1) || (strCmp(operand1, r6) == 1) || (strCmp(operand1, r7) == 1) || (strCmp(operand1, r8) == 1) || (strCmp(operand1, r9) == 1) )) // Operand1 is a register
                {
                    split_Str(oneline, operand2);
                    convertWord(operand2);
                    bool isOperand2ANumber = true; ///
    
                    for (int i = 0; i < str_length(operand2); i++)
                    {
                        if (operand2[i] < 48 || operand2[i] > 57)
                        {
                            isOperand2ANumber = false;
                            break;
                        }
                    }


                    if (isOperand2ANumber == true)
                    {   
                        split_Str(oneline, operand3);
                        convertWord(operand3);

                            if ( ((strCmp(operand3, r1) == 1) || (strCmp(operand3, r2) == 1) || (strCmp(operand3, r3) == 1) || (strCmp(operand3, r4) == 1) || (strCmp(operand3, r5) == 1) || (strCmp(operand3, r6) == 1) || (strCmp(operand3, r7) == 1) || (strCmp(operand3, r8) == 1) || (strCmp(operand3, r9) == 1) ))
                            {
                                split_Str(oneline, operand4); // Now we split our line again - there should be  an empty operand4 if all is well (or it can be an operand 4 of a comment)

                                if (str_length(operand4) != 0 && firstNonWhitespaceChar(operand4) != '#')
                                {
                                    cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                                }

                                else
                                {
                                    // carry out the muli instructions here
                                    ALU++;
                                }
                            }
                            
                            else
                            {
                                cerr << "Error on line " << totalLines << ": Invalid operand. " ;    
                            }

                    }

                    else
                    {
                        cerr << "Error on line " << totalLines << ": Invalid operand. " ;   
                    }
                        
                }

                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand" ;
                }

                
            }
        
            else // if comma seperation is wrong...
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand." ; 
            }

        }
        /////////////////////// end of muli case ////////////////////////////

       



        ////////////////////// start of div case ////////////////////////////
        else if (strCmp(opCode, "div") == 1) //DIV Ri, Rj, Rk
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            
            if (isCommaCorrectThreeOperands(oneline) && commas == 2) // if the comment placements check out then...
            {

                split_Str(oneline, operand1);
                convertWord(operand1);

                if ( ((strCmp(operand1, r1) == 1) || (strCmp(operand1, r2) == 1) || (strCmp(operand1, r3) == 1) || (strCmp(operand1, r4) == 1) || (strCmp(operand1, r5) == 1) || (strCmp(operand1, r6) == 1) || (strCmp(operand1, r7) == 1) || (strCmp(operand1, r8) == 1) || (strCmp(operand1, r9) == 1) )) // Operand1 is a register
                {
                    split_Str(oneline, operand2);
                    convertWord(operand2);

                        if ( ((strCmp(operand2, r1) == 1) || (strCmp(operand2, r2) == 1) || (strCmp(operand2, r3) == 1) || (strCmp(operand2, r4) == 1) || (strCmp(operand2, r5) == 1) || (strCmp(operand2, r6) == 1) || (strCmp(operand2, r7) == 1) || (strCmp(operand2, r8) == 1) || (strCmp(operand2, r9) == 1) ))
                        {   
                            split_Str(oneline, operand3);
                            convertWord(operand3);

                            if ( ((strCmp(operand3, r1) == 1) || (strCmp(operand3, r2) == 1) || (strCmp(operand3, r3) == 1) || (strCmp(operand3, r4) == 1) || (strCmp(operand3, r5) == 1) || (strCmp(operand3, r6) == 1) || (strCmp(operand3, r7) == 1) || (strCmp(operand3, r8) == 1) || (strCmp(operand3, r9) == 1) ))
                            {
                                split_Str(oneline, operand4); // Now we split our line again - there should be  an empty operand4 if all is well (or it can be an operand 4 of a comment)

                                if (str_length(operand4) != 0 && firstNonWhitespaceChar(operand4) != '#')
                                {
                                    cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                                }

                                else
                                {
                                    // carry out the div instructions here
                                    ALU++;
                                }
                            }
                            
                            else
                            {
                                cerr << "Error on line " << totalLines << ": Invalid operand. " ;    
                            }

                        }

                        else
                        {
                            cerr << "Error on line " << totalLines << ": Invalid operand. " ;    
                        }
                        
                }

                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand" ;
                }

                
            }
        
            else // if comma seperation is wrong...
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand." ;
            }

        }
        ////////////////////// end of div case ////////////////////////////
        




        /////////////////////// start of divi case /////////////////////////
        else if (strCmp(opCode, "divi") == 1) //DIVI Ri, nnnn, Rj
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            
            if (isCommaCorrectThreeOperands(oneline) && commas == 2) // if the comment placements check out then...
            {

                split_Str(oneline, operand1);
                convertWord(operand1);

                if ( ((strCmp(operand1, r1) == 1) || (strCmp(operand1, r2) == 1) || (strCmp(operand1, r3) == 1) || (strCmp(operand1, r4) == 1) || (strCmp(operand1, r5) == 1) || (strCmp(operand1, r6) == 1) || (strCmp(operand1, r7) == 1) || (strCmp(operand1, r8) == 1) || (strCmp(operand1, r9) == 1) )) // Operand1 is a register
                {
                    split_Str(oneline, operand2);
                    convertWord(operand2);
                    bool isOperand2ANumber = true; 
    
                    for (int i = 0; i < str_length(operand2); i++)
                    {
                        if (operand2[i] < 48 || operand2[i] > 57)
                        {
                            isOperand2ANumber = false;
                            break;
                        }
                    }


                    if (isOperand2ANumber == true)
                    {   
                        split_Str(oneline, operand3);
                        convertWord(operand3);

                            if ( ((strCmp(operand3, r1) == 1) || (strCmp(operand3, r2) == 1) || (strCmp(operand3, r3) == 1) || (strCmp(operand3, r4) == 1) || (strCmp(operand3, r5) == 1) || (strCmp(operand3, r6) == 1) || (strCmp(operand3, r7) == 1) || (strCmp(operand3, r8) == 1) || (strCmp(operand3, r9) == 1) ))
                            {
                                split_Str(oneline, operand4); // Now we split our line again - there should be  an empty operand4 if all is well (or it can be an operand 4 of a comment)

                                if (str_length(operand4) != 0 && firstNonWhitespaceChar(operand4) != '#')
                                {
                                    cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                                }

                                else
                                {
                                    // carry out the muli instructions here
                                    ALU++;
                                }
                            }
                            
                            else
                            {
                                cerr << "Error on line " << totalLines << ": Invalid operand. " ; 
                            }

                    }

                    else
                    {
                        cerr << "Error on line " << totalLines << ": Invalid operand. " ;     
                    }
                        
                }

                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand" ;
                }

                
            }
        
            else // if comma seperation is wrong...
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand." ;
            }

        }
        ///////////////////////// end of divi case /////////////////////////

    


        //////////////////////// start of jmp case //////////////////////////
        else if (strCmp(opCode, "jmp") == 1) //JMP <nnnn> <- the nnnn can either be a memory address of all numbers, or it can be a word with letters or numbers only enclosed in [] 
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            if ( firstNonWhitespaceChar(oneline) == '[' ||   (firstNonWhitespaceChar(oneline) > 47 && firstNonWhitespaceChar(oneline) < 58) )
            {
                bool isOperand1ANumber = true; 
                bool isOperand1AWord = true;
                split_Str(oneline, operand1);
                convertWord(operand1);

                for (int i = 0; i < str_length(operand1); i++)
                {
                    if (operand1[i] < 48 || operand1[i] > 57)
                    {
                        isOperand1ANumber = false;
                        break;
                    }
                }


                if (isOperand1ANumber == true) // implies that operand1 is indeed a pure number
                {
                    split_Str(oneline, operand2); // Now we split our line again - there should be  an empty operand4 if all is well (or it can be an operand 4 of a comment)

                    if (str_length(operand2) != 0 && firstNonWhitespaceChar(operand2) != '#')
                    {
                        cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                    }

                    else
                    {
                        // carry out the jmp instructions here
                        compareJump++;
                    }
                }



                for (int i = 1; i < (str_length(operand1) -2); i++)
                {
                    if (  !(((operand1[i] >= 48 && operand1[i] <= 57) || (operand1[i] >= 97 && operand1[i] <= 122) ) && (operand1[(str_length(operand1) - 1)] == ']')  && (operand1[0] == '[') ) ) // if at any point the label we're jumping to isn't a number or letter
                                                                                                                                                                                                   // and the last element is not a ']' then it will not be a letter.
                    {
                        isOperand1AWord = false;
                        break; 
                    }
                }


                if (operand1[0] != '[' || operand1[(str_length(operand1) -1)] != ']' || !(operand1[1] >= 97 && operand1[1] <= 122) )
                {
                    isOperand1AWord = false;
                }


                if (isOperand1AWord == true)
                {
                    split_Str(oneline, operand2); // Now we split our line again - there should be  an empty operand4 if all is well (or it can be an operand 4 of a comment)

                    if (str_length(operand2) != 0 && firstNonWhitespaceChar(operand2) != '#')
                    {
                        cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                    }

                    else
                    {
                        // carry out the jmp instructions here
                        compareJump++;
                    }
                }


                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand." ; 
                }

            }

            
            else 
            {
                cerr << "Error on line " << totalLines << ": Invalid operand." ;
            }
        }
        //////////////////////// end of jmp case ////////////////////////////
       





        //////////////////////// start of jz case ///////////////////////////
        else if (strCmp(opCode, "jz") == 1) ////JZ Ri, <nnnn>
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            
            if (numberOfCommas(oneline) == 1 && isCommaCorrectTwoOperands(oneline)) // if the comment placements check out then...
            {
                split_Str(oneline, operand1);
                convertWord(operand1);

                if ( ((strCmp(operand1, r1) == 1) || (strCmp(operand1, r2) == 1) || (strCmp(operand1, r3) == 1) || (strCmp(operand1, r4) == 1) || (strCmp(operand1, r5) == 1) || (strCmp(operand1, r6) == 1) || (strCmp(operand1, r7) == 1) || (strCmp(operand1, r8) == 1) || (strCmp(operand1, r9) == 1) ))
                {
                    split_Str(oneline, operand2);
                    convertWord(operand2);
                    if ( firstNonWhitespaceChar(operand2) == '[' || (firstNonWhitespaceChar(operand2) > 47 && firstNonWhitespaceChar(operand2) < 58) )
                    {
                        bool isOperand2ANumber = true; 
                        bool isOperand2AWord = true;
                       

                        for (int i = 0; i < (str_length(operand2)); i++)
                        {
                            if (! ((operand2[i] >= 48 && operand2[i] <= 57) ))    
                            {
                                isOperand2ANumber = false;
                                break;
                            }
                        }


                        if (isOperand2ANumber == true) // implies that operand2 is indeed a pure number
                        {
                            split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand3 if all is well (or it can be an operand 3 of a comment)

                            if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                            {
                                cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                            }

                            else
                            {
                                // carry out the jz instructions here
                                compareJump++;
                            }
                        }



                        for (int i = 1; i < (str_length(operand2) -2); i++)
                        {
                            if (  !(((operand2[i] >= 48 && operand2[i] <= 57) || (operand2[i] >= 97 && operand2[i] <= 122) ) && (operand2[(str_length(operand2) - 1)] == ']')  && (operand2[0] == '[') ) ) // if at any point the label we're jumping to isn't a number or letter
                                                                                                                                                                                                           // and the last element is not a ']' then it will not be a letter.
                            {
                                isOperand2AWord = false;
                                break; 
                            }
                        } 


                        if (operand2[0] != '[' || operand2[(str_length(operand2) -1)] != ']' || !(operand2[1] >= 97 && operand2[1] <= 122) )
                        {
                            isOperand2AWord = false;
                        }


                        if (isOperand2AWord == true)
                        {
                            split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand4 if all is well (or it can be an operand 4 of a comment)

                            if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                            {
                                cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                            }

                            else
                            {
                                // carry out the jz instructions here
                                compareJump++;
                            }
                        }


                        else if (isOperand2AWord == false && isOperand2ANumber == false)
                        {
                            cerr << "Error on line " << totalLines << ": Invalid operand." ; 
                        }

                    }

                    else 
                    {
                        cerr << "Error on line " << totalLines << ": Invalid operand.";
                    }
                }
            
                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand." ;
                }
            }     

            else 
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand." ; 
            }
        }
        //////////////////////// end of jz case /////////////////////////////
        






        //////////////////////// start of jnz case /////////////////////////
        else if (strCmp(opCode, "jnz") == 1) 
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            
            if (numberOfCommas(oneline) == 1 && isCommaCorrectTwoOperands(oneline)) // if the comment placements check out then...
            {
                split_Str(oneline, operand1);
                convertWord(operand1);

                if ( ((strCmp(operand1, r1) == 1) || (strCmp(operand1, r2) == 1) || (strCmp(operand1, r3) == 1) || (strCmp(operand1, r4) == 1) || (strCmp(operand1, r5) == 1) || (strCmp(operand1, r6) == 1) || (strCmp(operand1, r7) == 1) || (strCmp(operand1, r8) == 1) || (strCmp(operand1, r9) == 1) ))
                {
                    split_Str(oneline, operand2);
                    convertWord(operand2);
                    if ( firstNonWhitespaceChar(operand2) == '[' || (firstNonWhitespaceChar(operand2) > 47 && firstNonWhitespaceChar(operand2) < 58) )
                    {
                        bool isOperand2ANumber = true; 
                        bool isOperand2AWord = true;
                       

                        for (int i = 0; i < (str_length(operand2)); i++)
                        {
                            if (! ((operand2[i] >= 48 && operand2[i] <= 57) ))    
                            {
                                isOperand2ANumber = false;
                                break;
                            }
                        }


                        if (isOperand2ANumber == true) // implies that operand2 is indeed a pure number
                        {
                            split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand3 if all is well (or it can be an operand 3 of a comment)

                            if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                            {
                                cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                            }

                            else
                            {
                                // carry out the jnz instructions here
                                compareJump++;
                            }
                        }



                        for (int i = 1; i < (str_length(operand2) -2); i++)
                        {
                            if (  !(((operand2[i] >= 48 && operand2[i] <= 57) || (operand2[i] >= 97 && operand2[i] <= 122) ) && (operand2[(str_length(operand2) - 1)] == ']')  && (operand2[0] == '[') ) ) // if at any point the label we're jumping to isn't a number or letter
                                                                                                                                                                                                           // and the last element is not a ']' then it will not be a letter.
                            {
                                isOperand2AWord = false;
                                break; 
                            }
                        } 


                        if (operand2[0] != '[' || operand2[(str_length(operand2) -1)] != ']' || !(operand2[1] >= 97 && operand2[1] <= 122) )
                        {
                            isOperand2AWord = false;
                        }


                        if (isOperand2AWord == true)
                        {
                            split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand4 if all is well (or it can be an operand 4 of a comment)

                            if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                            {
                                cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                            }

                            else
                            {
                                // carry out the jnz instructions here
                                compareJump++;
                            }
                        }


                        else if (isOperand2AWord == false && isOperand2ANumber == false)
                        {
                            cerr << "Error on line " << totalLines << ": Invalid operand." ; 
                        }

                    }

                    else 
                    {
                        cerr << "Error on line " << totalLines << ": Invalid operand.";
                    }
                }
            
                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand." ;
                }
            }     

            else 
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand."; 
            }
        }
        //////////////////////// end of jnz case ///////////////////////////
        





        //////////////////////// start of jgz case /////////////////////////
        else if (strCmp(opCode, "jgz") == 1) 
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            if (numberOfCommas(oneline) == 1 && isCommaCorrectTwoOperands(oneline)) // if the comment placements check out then...
            {
                split_Str(oneline, operand1);
                convertWord(operand1);

                if ( ((strCmp(operand1, r1) == 1) || (strCmp(operand1, r2) == 1) || (strCmp(operand1, r3) == 1) || (strCmp(operand1, r4) == 1) || (strCmp(operand1, r5) == 1) || (strCmp(operand1, r6) == 1) || (strCmp(operand1, r7) == 1) || (strCmp(operand1, r8) == 1) || (strCmp(operand1, r9) == 1) ))
                {
                    split_Str(oneline, operand2);
                    convertWord(operand2);
                    if ( firstNonWhitespaceChar(operand2) == '[' || (firstNonWhitespaceChar(operand2) > 47 && firstNonWhitespaceChar(operand2) < 58) )
                    {
                        bool isOperand2ANumber = true; 
                        bool isOperand2AWord = true;
                       

                        for (int i = 0; i < (str_length(operand2)); i++)
                        {
                            if (! ((operand2[i] >= 48 && operand2[i] <= 57) ))    
                            {
                                isOperand2ANumber = false;
                                break;
                            }
                        }


                        if (isOperand2ANumber == true) // implies that operand2 is indeed a pure number
                        {
                            split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand3 if all is well (or it can be an operand 3 of a comment)

                            if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                            {
                                cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                            }

                            else
                            {
                                // carry out the jgz instructions here
                                compareJump++;
                            }
                        }



                        for (int i = 1; i < (str_length(operand2) -2); i++)
                        {
                            if (  !(((operand2[i] >= 48 && operand2[i] <= 57) || (operand2[i] >= 97 && operand2[i] <= 122) ) && (operand2[(str_length(operand2) - 1)] == ']')  && (operand2[0] == '[') ) ) // if at any point the label we're jumping to isn't a number or letter
                                                                                                                                                                                                           // and the last element is not a ']' then it will not be a letter.
                            {
                                isOperand2AWord = false;
                                break; 
                            }
                        } 


                        if (operand2[0] != '[' || operand2[(str_length(operand2) -1)] != ']' || !(operand2[1] >= 97 && operand2[1] <= 122) )
                        {
                            isOperand2AWord = false;
                        }


                        if (isOperand2AWord == true)
                        {
                            split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand4 if all is well (or it can be an operand 4 of a comment)

                            if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                            {
                                cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                            }

                            else
                            {
                                // carry out the jgz instructions here
                                compareJump++;
                            }
                        }


                        else if (isOperand2AWord == false && isOperand2ANumber == false)
                        {
                            cerr << "Error on line " << totalLines << ": Invalid operand." ; 
                        }

                    }

                    else 
                    {
                        cerr << "Error on line " << totalLines << ": Invalid operand.";
                    }
                }
            
                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand." ;
                }
            }     

            else 
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand." ;  
            }
        }
        //////////////////////// end of jgz case ///////////////////////////
         






        //////////////////////// start of jgez case /////////////////////////
        else if (strCmp(opCode, "jgez") == 1) 
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            
            if (numberOfCommas(oneline) == 1 && isCommaCorrectTwoOperands(oneline)) // if the comment placements check out then...
            {
                split_Str(oneline, operand1);
                convertWord(operand1);

                if ( ((strCmp(operand1, r1) == 1) || (strCmp(operand1, r2) == 1) || (strCmp(operand1, r3) == 1) || (strCmp(operand1, r4) == 1) || (strCmp(operand1, r5) == 1) || (strCmp(operand1, r6) == 1) || (strCmp(operand1, r7) == 1) || (strCmp(operand1, r8) == 1) || (strCmp(operand1, r9) == 1) ))
                {
                    split_Str(oneline, operand2);
                    convertWord(operand2);
                 
                    if ( firstNonWhitespaceChar(operand2) == '[' || (firstNonWhitespaceChar(operand2) > 47 && firstNonWhitespaceChar(operand2) < 58) )
                    {
                        bool isOperand2ANumber = true; 
                        bool isOperand2AWord = true;
                       

                        for (int i = 0; i < (str_length(operand2)); i++)
                        {
                            if (! ((operand2[i] >= 48 && operand2[i] <= 57) ))    
                            {
                                isOperand2ANumber = false;
                                break;
                            }
                        }


                        if (isOperand2ANumber == true) // implies that operand2 is indeed a pure number
                        {
                            split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand3 if all is well (or it can be an operand 3 of a comment)

                            if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                            {
                                cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                            }

                            else
                            {
                                // carry out the jgez instructions here
                                compareJump++;
                            }
                        }



                        for (int i = 1; i < (str_length(operand2) -2); i++)
                        {
                            if (  !(((operand2[i] >= 48 && operand2[i] <= 57) || (operand2[i] >= 97 && operand2[i] <= 122) ) && (operand2[(str_length(operand2) - 1)] == ']')  && (operand2[0] == '[') ) ) // if at any point the label we're jumping to isn't a number or letter
                                                                                                                                                                                                           // and the last element is not a ']' then it will not be a letter.
                            {
                                isOperand2AWord = false;
                                break; 
                            }
                        } 


                        if (operand2[0] != '[' || operand2[(str_length(operand2) -1)] != ']' || !(operand2[1] >= 97 && operand2[1] <= 122) )
                        {
                            isOperand2AWord = false;
                        }


                        if (isOperand2AWord == true)
                        {
                            split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand4 if all is well (or it can be an operand 4 of a comment)

                            if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                            {
                                cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                            }

                            else
                            {
                                // carry out the jgez instructions here
                                compareJump++;
                            }
                        }


                        else if (isOperand2AWord == false && isOperand2ANumber == false)
                        {
                            cerr << "Error on line " << totalLines << ": Invalid operand." ; 
                        }

                    }

                    else 
                    {
                        cerr << "Error on line " << totalLines << ": Invalid operand.";
                    }
                }
            
                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand." ;
                }
            }     

            else 
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand." ; 
            }
        }
        //////////////////////// end of jgez case ///////////////////////////


        



        //////////////////////// start of jlz case /////////////////////////
        else if (strCmp(opCode, "jlz") == 1) 
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            
            if (numberOfCommas(oneline) == 1 && isCommaCorrectTwoOperands(oneline)) // if the comment placements check out then...
            {
                split_Str(oneline, operand1);
                convertWord(operand1);

                if ( ((strCmp(operand1, r1) == 1) || (strCmp(operand1, r2) == 1) || (strCmp(operand1, r3) == 1) || (strCmp(operand1, r4) == 1) || (strCmp(operand1, r5) == 1) || (strCmp(operand1, r6) == 1) || (strCmp(operand1, r7) == 1) || (strCmp(operand1, r8) == 1) || (strCmp(operand1, r9) == 1) ))
                {
                    split_Str(oneline, operand2);
                    convertWord(operand2);
                    if ( firstNonWhitespaceChar(operand2) == '[' || (firstNonWhitespaceChar(operand2) > 47 && firstNonWhitespaceChar(operand2) < 58) )
                    {
                        bool isOperand2ANumber = true; 
                        bool isOperand2AWord = true;
                       

                        for (int i = 0; i < (str_length(operand2)); i++)
                        {
                            if (! ((operand2[i] >= 48 && operand2[i] <= 57) ))    
                            {
                                isOperand2ANumber = false;
                                break;
                            }
                        }


                        if (isOperand2ANumber == true) // implies that operand2 is indeed a pure number
                        {
                            split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand3 if all is well (or it can be an operand 3 of a comment)

                            if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                            {
                                cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                            }

                            else
                            {
                                // carry out the jlz instructions here
                                compareJump++;
                            }
                        }



                        for (int i = 1; i < (str_length(operand2) -2); i++)
                        {
                            if (  !(((operand2[i] >= 48 && operand2[i] <= 57) || (operand2[i] >= 97 && operand2[i] <= 122) ) && (operand2[(str_length(operand2) - 1)] == ']')  && (operand2[0] == '[') ) ) // if at any point the label we're jumping to isn't a number or letter
                                                                                                                                                                                                           // and the last element is not a ']' then it will not be a letter.
                            {
                                isOperand2AWord = false;
                                break; 
                            }
                        } 


                        if (operand2[0] != '[' || operand2[(str_length(operand2) -1)] != ']' || !(operand2[1] >= 97 && operand2[1] <= 122) )
                        {
                            isOperand2AWord = false;
                        }


                        if (isOperand2AWord == true)
                        {
                            split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand4 if all is well (or it can be an operand 4 of a comment)

                            if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                            {
                                cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                            }

                            else
                            {
                                // carry out the jlz instructions here
                                compareJump++;
                            }
                        }


                        else if (isOperand2AWord == false && isOperand2ANumber == false)
                        {
                            cerr << "Error on line " << totalLines << ": Invalid operand." ;
                        }

                    }

                    else 
                    {
                        cerr << "Error on line " << totalLines << ": Invalid operand.";
                    }
                }
            
                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand." ;
                }
            }     

            else 
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand.";
            }
        }
        //////////////////////// end of jlz case ///////////////////////////






        //////////////////////// start of jlez case /////////////////////////
        else if (strCmp(opCode, "jlez") == 1) // JLEZ Ri, <nnnn>
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            int commas = numberOfCommas(oneline); 
            
            if (numberOfCommas(oneline) == 1 && isCommaCorrectTwoOperands(oneline)) // if the comment placements check out then...
            {
                split_Str(oneline, operand1);
                convertWord(operand1);

                if ( ((strCmp(operand1, r1) == 1) || (strCmp(operand1, r2) == 1) || (strCmp(operand1, r3) == 1) || (strCmp(operand1, r4) == 1) || (strCmp(operand1, r5) == 1) || (strCmp(operand1, r6) == 1) || (strCmp(operand1, r7) == 1) || (strCmp(operand1, r8) == 1) || (strCmp(operand1, r9) == 1) ))
                {
                    split_Str(oneline, operand2);
                    convertWord(operand2);
                    if ( firstNonWhitespaceChar(operand2) == '[' || (firstNonWhitespaceChar(operand2) > 47 && firstNonWhitespaceChar(operand2) < 58) )
                    {
                        bool isOperand2ANumber = true; 
                        bool isOperand2AWord = true;
                       

                        for (int i = 0; i < (str_length(operand2)); i++)
                        {
                            if (! ((operand2[i] >= 48 && operand2[i] <= 57) ))    
                            {
                                isOperand2ANumber = false;
                                break;
                            }
                        }


                        if (isOperand2ANumber == true) // implies that operand2 is indeed a pure number
                        {
                            split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand3 if all is well (or it can be an operand 3 of a comment)

                            if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                            {
                                cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                            }

                            else
                            {
                                // carry out the jlez instructions here
                                compareJump++;
                            }
                        }



                        for (int i = 1; i < (str_length(operand2) -2); i++)
                        {
                            if (  !(((operand2[i] >= 48 && operand2[i] <= 57) || (operand2[i] >= 97 && operand2[i] <= 122) ) && (operand2[(str_length(operand2) - 1)] == ']')  && (operand2[0] == '[') ) ) // if at any point the label we're jumping to isn't a number or letter
                                                                                                                                                                                                           // and the last element is not a ']' then it will not be a letter.
                            {
                                isOperand2AWord = false;
                                break; 
                            }
                        } 


                        if (operand2[0] != '[' || operand2[(str_length(operand2) -1)] != ']' || !(operand2[1] >= 97 && operand2[1] <= 122) )
                        {
                            isOperand2AWord = false;
                        }


                        if (isOperand2AWord == true)
                        {
                            split_Str(oneline, operand3); // Now we split our line again - there should be  an empty operand4 if all is well (or it can be an operand 4 of a comment)

                            if (str_length(operand3) != 0 && firstNonWhitespaceChar(operand3) != '#')
                            {
                                cerr << "Error on line " << totalLines << ": Extra data (or invalid / extra operand) after instruction.";
                            }

                            else
                            {
                                // carry out the jlez instructions here
                                compareJump++;
                            }
                        }


                        else if (isOperand2AWord == false && isOperand2ANumber == false)
                        {
                            cerr << "Error on line " << totalLines << ": Invalid operand. (or extra data - but not really)";
                        }

                    }

                    else 
                    {
                        cerr << "Error on line " << totalLines << ": Invalid operand.";
                    }
                }
            
                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand. (or extra data - but not really)";
                }
            }     

            else 
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation or missing operand. (or extra data - but not really)"; 
            }
        }
        //////////////////////// end of jlez case ///////////////////////////



        //////////////////////// start of code case /////////////////////////
        else if (strCmp(opCode, "code:") == 1) 
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            isThereCodeDirective = true;
            if (CodeDirectiveCount == 0)
            {
                int commas = numberOfCommas(oneline);
                split_Str(oneline, operand1); //for this instruction, data must be a number, and if it isn't then we have an error.
                bool isOperand1ANumber = true;

                for (int i = 0; i < str_length(operand1); i++)
                {
                    if (operand1[i] < 48 || operand1[i] > 57 )
                    {
                        isOperand1ANumber = false;
                        break;
                    }
                }

                if (isOperand1ANumber == true && commas == 0 && CodeDirectiveCount == 0)
                {
                    CodeDirectiveCount++;
                    Code = strToInt(operand1);
                }

                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand or extra operand or invalid seperation.";
                }
            }

            else if (CodeDirectiveCount != 0)
            {
                cerr << "Error on line " << totalLines << ": duplicate directive detected.";
            }
        }
        //////////////////////// end of code case ///////////////////////////

          



        //////////////////////// start of data case /////////////////////////
        else if (strCmp(opCode, "data:") == 1) 
        {
            if (DataDirectiveCount == 0)
            {

                int commas = numberOfCommas(oneline);
                split_Str(oneline, operand1); //for this instruction, data must be a number, and if it isn't then we have an error.
                bool isOperand1ANumber = true;

                for (int i = 0; i < str_length(operand1); i++)
                {
                    if (operand1[i] < 48 || operand1[i] > 57 )
                    {
                        isOperand1ANumber = false;
                        break;
                    }
                }

                if (isOperand1ANumber == true && commas == 0 && DataDirectiveCount == 0)
                {
                    DataDirectiveCount++;
                    Data = strToInt(operand1);
                }

                else 
                {
                    cerr << "Error on line " << totalLines << ": Invalid operand or extra operand or invalid seperation.";
                }
            }

            else if (DataDirectiveCount != 0)
            {
                cerr << "Error on line " << totalLines << ": duplicate directive detected.";
            }
        }
        //////////////////////// end of data case ///////////////////////////

         


        //////////////////////// start of code for labels ///////////////////
        else 
        {
            instructionOrLabelOrCodeDirectiveExecuteOrder++;
            bool isOpCodeAValidWord = true;

            split_Str(oneline, operand2);


            if (str_length(operand2) != 0 && firstNonWhitespaceChar(operand2) != '#') 
            {
                cerr << "Error on line " << totalLines << ": invalid opcode / duplicate / extra operand after instruction.";
            }

            else
            {
                if (!(opCode[0] >= 97 && opCode[0] <= 122) || opCode[str_length(opCode) -1] != ':')
                {
                    isOpCodeAValidWord = false;
                }
                

                for (int i = 1; i < (str_length(opCode) -1); i++) // beginning is assumed to be a letter and last element should be a ':'
                {
                    if (!(opCode[i] >= 97 && opCode[i] <= 122) && !(opCode[i] >=48 && opCode[i] <= 57) )
                    {
                        isOpCodeAValidWord = false;
                        break;
                    }
                }


                bool duplicate = false;
                for (int i = 0; i < totalLines; i++)     // for loop to compare current label with previous labels
                    {
                        if (strCmp(opCode, labels[i]) == 1)
                        {
                            duplicate = true;
                            isOpCodeAValidWord = false;
                            cerr << "Error on line " << totalLines << ": duplicate opcode found.";
                            break;
                        }
                    }

                if (isOpCodeAValidWord == true) // this means a label is here that's valid
                {
                    emptyLine(oneline);
                    refillLine(oneline, tempLine);
                    split_Str(oneline, opCode);

                    for (int i =0; i < str_length(opCode); i++) // Stores our valid label in a 2d char array for use or comparison 
                    {
                        labels[totalLines][i] = opCode[i];
                    }
                    
                    cout << opCode << " " << (Code + ALU + loadStore + compareJump);
                }

                else if (isOpCodeAValidWord == false && duplicate== false)
                {
                    cerr << "Error on line " << totalLines << ": invalid opcode.";
                }
            }

        }
        //////////////////////// end of code for labels /////////////////////
        






        //////////////////////// if code does not come before opcodes or labels ////////////////////////////////////////////////
        if (instructionOrLabelOrCodeDirectiveExecuteOrder == 1 && isThereCodeDirective == false)
        {
            cerr << "Error on line " << totalLines << ": code directive missing / invalid placement / does not come first before opcodes or labels.";
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






        // Reset our line back to what it was like before we parsed and extracted information from it.
        emptyLine(oneline);
        refillLine(oneline, tempLine);
        cout << endl;
        
    }
    // cout << oneline << endl;   
}



/////////////////////////////////////////////////////////  W H E R E    W E   A R E   C U R E D    ////////////////////////////////////////////////////////
instructions = loadStore + ALU + compareJump;
Code = Code + ALU + compareJump + loadStore;


// If our valid instructions from code base overlaps with our data we must output an error.
if (Code >= Data && Data != 0) // Data we initiailize at 0 and if they don't specify it, but do specify Code, assume overlap doesn't need to be considered.
{
    cerr << "Error : code overlaps with data - invalid operation." << endl;
}




// Output our results for the counters -> notice for some we did -1, this because our shit counts an extra line -> last line that is a blank line
cout << "Total number of lines is = " << totalLines  << endl;
cout << "Total number of blank lines/ comment lines is = " << blankOrCommentLines  << endl;
cout << "Total number of assembly instructions: " << instructions << endl;
cout << "Total number of loadStore instructions:" << loadStore << endl;
cout << "Total number of ALU instructions: " << ALU << endl;
cout << "Total number of compareJump instructions: " << compareJump << endl;
cout << "Our code is at: " << Code << endl;
cout << "Our data is at: " << Data << endl;


// Write to output final - should be the answer to the operations
/*int a = 0;
outFile << a; */

// Close our shit before we finish the program
inFile.close();
outFile.close();


return 0;
}
