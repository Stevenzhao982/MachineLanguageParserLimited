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

// Splits a character array and prints out the pseudo substring.
void subStr(char str[], int start, int end) // start = index to start substring, end = index to end substring (including that index element)
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

// Accepts a char array and splits it by white spaces then stores it by reference into another char array. When it splits and copies, it
// starts copying the 'line' characters into the 'word' array starting from when something that isnt a white space end line or comment mark appears to
// when a white space next appears. Everytime it copies from the line, it also replaces the copied values of the original line with white spaces so that
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
// words by split_Str then after that refill the line. 
void copyLine (char* line, char* temp) // input line to copy into temp line
{
    for (int i = 0; i < str_length(line); i++)
    {
        temp[i] = line[i];
    }
}

void refillLine (char* line, char* temp) // input line to fill with previously copied temp line
{
    for (int i = 0; i < str_length(line); i++)
    {
        line[i] = temp[i];
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

void emptyLine (char*line)
{
    for (int i =0; i < str_length(line); i ++)
    {
        line[i] = ' ';
    }
}





///////////////////////////////////////////////////////////////////////////////////////////////////////
bool isCommaCorrectThreeOperands (char* line) 
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


///////////////////////////////////////////////////////////////////////////////////////////////////////







bool isCommaCorrectTwoOperands (char* line)
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

    while (line[i] != ',' && i<str_length(line))
    {
        if ( (line[i] >= 65 && line[i] <= 90) || (line[i] >= 97 && line[i] <= 122) || (line[i] >= 48 && line[i] <= 57) || line[i] == 45 )
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



int main ()
{
        char r1 [256] = "r1";
        char r2 [256] = "r2";
        char r3 [256] = "r3";
        char r4 [256] = "r4";
        char r5 [256] = "r5";
        char r6 [256] = "r6";
        char r7 [256] = "r7";
        char r8 [256] = "r8";
        char r9 [256] = "r9";
///////////////////////////////////////////////////////

char opCode [256] = {0};

char operand2 [256] = {0};
char operand3 [256] = {0};
char operand4 [256] = {0};
char oneline [256] = "  SDi     0, 2000         # i = 0";



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ADD Ri, Rj, Rk
cout << "0. " << oneline << endl;
split_Str(oneline, opCode);



char operand1 [256] = "[asd1]";

bool isOperand1AWord = false;
cout << endl;
cout << operand1[0] << endl;
cout << operand1[(str_length(operand1)-1)] << endl;
cout << (operand1[1] >= 97 && operand1[1] <= 122)  << endl;



   if (operand1[0] != '[' || operand1[(str_length(operand1) -1)] != ']' || !(operand1[1] >= 97 && operand1[1] <= 122) )
                {
                    cout << "SDF SDF ";
                    isOperand1AWord = false;
                }







/*
split_Str(oneline, opCode);

   if (strCmp(opCode, "add") == 1)
        {
            int commas = numberOfCommas(oneline); 
            split_Str(oneline, operand1);
            convertWord(operand1);
            
            if (isCommaCorrectThreeOperands(oneline) && commas == 2) // if the comment placements check out then...
            {
              

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
                            cerr << "Error on line " << totalLines << ": Invalid operand. " << endl;     
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
                    cerr << "Error on line " << totalLines << ": Invalid operand" << endl;
                }

            }
        
            else // if comma seperation is wrong...
            {
                cerr << "Error on line " << totalLines << ": Invalid operand seperation." << endl; 
            }

        }
 */  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
}









