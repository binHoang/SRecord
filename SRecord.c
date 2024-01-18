/* 
Mock Project: In this project, we will develop an application which manipulates on files in S-Record format.
S-Record is a file format which was invented by the Motorola corporation in mid-1970s.
This format conveys binary information in ASCII text form for hexa-decimal value.
This file format is commonly used for flash memory programming in microcontrollers, EPROMs, EEPROMs, etc.
Your application will have following features:
- Form a sequence of integer values, which is input from keyboard by user, to S-Records then write
them to a new S-Record file.
Integer values are input by user are in decimal base and separated by Space character between 
them. For example: 45 204 190 77 23 53 186
- Convert 1-1 from a normal binary file to an S-Record file. The binary file contains only data, so 
the application will build S-Records whose Data field is data got from a portion in binary file.
- Convert binary data from a normal binary file to S-Records and add them to an existing S-Record file. 
(This feature is similar to the above feature, but it doesn’t create new S-Record file, it appends S-Records to an existing file).
- Check corruption for an S-Record file.
- The application must have appropriate menu so that user can use conveniently
--------------------------------------------------------------------------------------------
Date: January 16th, 2024.
Author: Hoang Nguyen An Binh.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MOCK_PROJECT_TRUE 1
#define MOCK_PROJECT_FALSE 0
#define MOCK_PROJECT_SIZE 256
#define MOCK_PROJECT_WRITEMODE "w"
#define MOCK_PROJECT_READMODE "r"
#define MOCK_PROJECT_APPENDEXMODE "a+"
#define MOCK_PROJECT_READBINARY "rb"


/* Function to get the file path
 + User will input manually the directory of folder, then user will input the file name only.
 + User don't need to input file format such ".srec" or ".bin", after choosing an option, the
 program will does it automatically.
 + After input the folder path and file name, the program will give user the full directory of file path.
 * Input: 
    + FileFormat: a string which has two values which are ".srec" or ".bin" depends on the selection of user.
 * Output:
    + sFilePath: a string which is the location of the file on the computer.
    Example of a filepath: D:\AnBinh\FPT\C_Module\MockProject\Code\AnBinh1.srec 
*/
char* GetTheFilePath(char *FileFormat)
{
    // input folder path
    char sFolderPath[50];
    printf("\n\nBrowse folder path: ");
    scanf("%s", &sFolderPath);
    getc(stdin);

    // input file name
    printf("\n\nFile name (File name only): ");
    char sFileName[50];
    scanf("%s", &sFileName);
    getc(stdin);
    strcat(sFileName, FileFormat);

    // concatenate folder path and file name into file path 
    int  i = 0, j = 0;
    char* sFilePath = NULL;
    sFilePath = malloc(100);

    // insert the folder path string in the file path 
    while(sFolderPath[j] != '\0')
    {
        sFilePath[i] = sFolderPath[j];
        i++;
        j++;
    }

    // insert the file name string in the file path after the folder path 
    sFilePath[i] = 0x5C;  // insert file separator
    i++;
    j=0;
    while(sFileName[j] != '\0')
    {
        sFilePath[i] = sFileName[j];
        i++;
        j++;
    }

    sFilePath[i] = 0;   // end of string

    return sFilePath;
}






/* Function to read input string from keyboard 
 + The initial variable string will have the size of 256 bytes, if the size of input from user exceeds 256,
 reallocate memory for sufficient memory to store the whole input string.
 + The method can be describe as:
    - Step 1: read 256s byte of the input from keyboard, store in sTemp, then concatenate the sTemp to the 
    output string.
    - Step 2: if the length of sTemp is equal 256, continue reading the input string, which mean go to Step 1, 
    else, exit the loop and return the output string.
 * Ouput: 
    + sOutput: the complete string after read from keyboard.
 */ 
char* InputString()
{
    /* sInput is the string to write in S-Record*/
    char* sOutput = NULL;
    /* sTemp is the support string in case the input exceed 256 byte */
    char sTemp[MOCK_PROJECT_SIZE];
    unsigned int iInputLen = 0, iTemplen = 0;

    sOutput = malloc(MOCK_PROJECT_SIZE);
    memset(sOutput, 0, sizeof(sOutput));
    printf("\n>>>> Input integer sequence: ");

    do {
        fgets(sTemp, MOCK_PROJECT_SIZE, stdin);
        iTemplen = strlen(sTemp);

        //check if user input invalid character.
        for (int i = 0; i < iTemplen; i++)
        {
            if ((sTemp[i] < 48) || (sTemp[i] > 58))
            {
                printf("\n\nThe input string has '%c' character which is invalid input!\n\n", (char)sTemp[i]);
                printf("Return to options for new S-Record\n\n\n");
                system("pause");
                return NULL;

            }
        }

        //if the part of string is ok, continue to add to Output string.
        sOutput = realloc(sOutput, iInputLen + iTemplen + 1);
        strcat(sOutput, sTemp);
        iInputLen += iTemplen;

        //if the length of sTemp is less than 255, mean that this part of string is the last from input.
        if (iTemplen < MOCK_PROJECT_SIZE-1)
        {
            break;
        }

        } while(MOCK_PROJECT_TRUE);


        sOutput[iInputLen-1] = 0;

        return sOutput;

}





/* Function to convert a number from 0 - 15 to char type in Hexadecimal form */
char ConvertToChar(int Num)
{
    switch (Num)
    {
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        case 10:
            return 'A';
        case 11:
            return 'B';
        case 12:
            return 'C';
        case 13:
            return 'D';
        case 14:
            return 'E';
        case 15:
            return 'F';
    }
}





/* Function to convert single charater to Hexadecimal value */
int ConvertToHex(char Ch)
{
    switch (Ch)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'A':
            return 10;
        case 'B':
            return 11;
        case 'C':
            return 12;
        case 'D':
            return 13;
        case 'E':
            return 14;
        case 'F':
            return 15;
    }
}





/* Function to compute the checksum byte from string of hexadecimal sequence
 + The method to calculate the check sum can be found at: https://en.wikipedia.org/wiki/SREC_(file_format)
 * Input: 
    + sHexString: the sequence of an record stored as string type.
 * Output: 
    + iCheckSum: the value of checksum stored as int type.
 */
int CheckSumCalculator(char *sHexString)
{
    // Sum up each hexa-pair from the string
    int iLength = strlen(sHexString);
    int iCheckSum;
    int iHexSum = 0;
    int iTemp1 = 0, iTemp2 = 0, iTemp3 = 0;
    // loop on the string to sum
    for(int i = 0; i < iLength; i++)
    {
        iTemp1 = ConvertToHex(sHexString[i++]);
        iTemp2 = ConvertToHex(sHexString[i]);
        iHexSum = iHexSum + (iTemp1 * 16) + iTemp2;
    }
    //convert sum to checksum by formula according to wiki
    // Checksum = 0xFF - (sum & 0xFF)
    iHexSum = iHexSum & 0xFF;
    iCheckSum = 0xFF - iHexSum;

    return iCheckSum;
}    





/* Function to check corruption
 + Read each line of record and call CheckSumCalculator() to compute the checksum of that record.
 + After compute checksum, compare the result to the last byte of record.
 + If one of record return false after comparison, tell user that SRecord file is broken.
 + Else if all passes, tell user that file is OK.
 * Input 
    + FileName: the directory of SRecord file.
 */
void CheckCorruption(char * FileName)
{
    system("cls"); //Clear screen
    printf("Checking corruption.....");

    FILE *fp;
    fp = fopen(FileName, MOCK_PROJECT_READMODE);
    // create a loop to read every single record
    int iIndex = 0;
    char *sSRecord;
    sSRecord = malloc(260);
    int sCheckSumPair = 0;
    int sCheckCorr = 0;
    char cIsCorrupt = 0;
    do
    {
        char c = fgetc(fp);       
        if (c == 'S')// ignore the Record start and Record type
        {
            c = fseek(fp, 1, SEEK_CUR);
            continue;
        } else if(c == 10) //if read '\n', do the checksum
        {
            //iIndex--;
            int iTemp1 = ConvertToHex(sSRecord[iIndex-2]);
            int iTemp2 =  ConvertToHex(sSRecord[iIndex-1]);
            sCheckSumPair = sCheckSumPair + iTemp1*16 + iTemp2;
            sSRecord[iIndex-2] = 0;
            sCheckCorr = CheckSumCalculator(sSRecord);

            if(sCheckSumPair != sCheckCorr)
            {
                printf("\n\nFile is corrupted!");
                printf("\n\nThe CheckSum in file -- the true CheckSum is %04X--%04X", sCheckSumPair, sCheckCorr);
                printf("\n\nOn the Record: '%s'", sSRecord);
                return;
            }
            else{
                iIndex = 0;
                sSRecord = realloc(sSRecord, 600);
                memset(sSRecord, 0, sizeof(sSRecord));
                sCheckSumPair = 0;
                sCheckCorr = 0;
                cIsCorrupt = 0;
            }
        }
        else
        {
            sSRecord[iIndex++] = c;
        }
        
         
        if(feof(fp))
        {
            break;
        }
    } while (MOCK_PROJECT_TRUE);

    printf("\n\nFile %s is OK!\n\n", FileName);
    system("pause");
}





/* Function that write data existing S-Record file
 + Convert the array of integer to SRecord format.
 + The format of SRecord file is described at: https://en.wikipedia.org/wiki/SREC_(file_format)
 ++++ Write to next line of that S-Record file.
 * Input:
    + FileName: the directory of SRecord file.
    + A: array pf integer.
    + N: length of array A or the number of integers.
 */
void WriteToExistingSRecord(char * FileName, int A[], int N)
{
    system("cls"); //Clear screen
    FILE *fp;
    fp = fopen(FileName, MOCK_PROJECT_APPENDEXMODE);
    int iCount = 0;
    int iCountLine = 0;

    do
    {
        // Taking input single character at a time
        char c = fgetc(fp);
        iCount ++;
        if(c == 10)
        {
            iCountLine ++;
            continue;
        }
        // Checking for end of file
        if (feof(fp))
            break ;
    }  while(1);

    int iByteCount = 0;
    int iMaxByte = 0xFC;
    int iAddress = (iCount - iCountLine*10 - 26)/2;;
    int iCheckSum = 0;

    //If the list of integers can be written within a record
    if (N < iMaxByte) 
    {
        // get the data field of the record
        int iDataFieldSize = N * 2;
        char sDataField[iDataFieldSize];
        iByteCount = N + 3; //size of data field + 2 byte address + 1 byte checksum
        int iIndex = 0;

        for(int i = 0; i < N; i++)
        {
            // convert integer to hexa-pair string            
            sDataField[iIndex++] = ConvertToChar(A[i]/16);  //get the first digit of hexa pair
            sDataField[iIndex++] = ConvertToChar(A[i]%16);    //get the second digit of hexa pair
        }
        sDataField[iDataFieldSize] = 0;
        
        // get the check sum
        int iLength = iByteCount * 2;
        char CheckSumString[iLength];
        char sAddress[4], sByteCount[2];

        sprintf(sByteCount, "%02X", iByteCount);
        sprintf(sAddress, "%04X", iAddress);

        strcpy(CheckSumString, sByteCount);
        strcat(CheckSumString, sAddress);
        int i = 0;
        while(i < iDataFieldSize)
        {
            CheckSumString[6 + i] = sDataField[i];
            i++;
        }
        CheckSumString[iLength] = 0;

        iCheckSum = CheckSumCalculator(CheckSumString);
        // write a complete record.
        fprintf(fp, "%s%02X%04X%s%02X\n", "S1", iByteCount, iAddress, sDataField, iCheckSum);

        fclose(fp);
        //notify if complete writing data
        printf("\n\nSuccessfully written data in to %s\n\n", FileName);

        return;

    }

    // If the list of integers is too long and must to write for several records
    int iStart = 0;
    int iStop = iMaxByte;
    int iIndex = 0;
    int iRemain = N;
    iByteCount = iMaxByte + 3;
    int iDataFieldSize = iMaxByte*2;

    do
    {
        //printf("\n\n--%d--\n\n", iStop);
        char sDataField[iDataFieldSize];
        for (int i = iStart; i < iStop; i++)
        {
            // convert integer to hexa-pair string            
            sDataField[iIndex++] = ConvertToChar(A[i]/16);  //get the first digit of hexa pair
            sDataField[iIndex++] = ConvertToChar(A[i]%16);    //get the second digit of hexa pair
        }
        
        // get the check sum
        int iLength = iByteCount * 2;
        char CheckSumString[iLength];
        char sAddress[4], sByteCount[2];

        sprintf(sByteCount, "%02X", iByteCount);
        sprintf(sAddress, "%04X", iAddress);

        strcpy(CheckSumString, sByteCount);
        strcat(CheckSumString, sAddress);

        int i = 0;
        while(i < iDataFieldSize)
        {
            CheckSumString[6 + i] = sDataField[i];
            i++;
        }
        CheckSumString[iLength] = 0;
        iCheckSum = CheckSumCalculator(CheckSumString);
        sDataField[iIndex] = 0;

        // write a complete record.
        fprintf(fp, "%s%02X%04X%s%02X\n", "S1", iByteCount, iAddress, sDataField, iCheckSum);

        iAddress += iMaxByte;       // update address
        iRemain -= iMaxByte;        // update remain integer which haven't been written to SRecord
        iStart += iMaxByte;         //Move tho next integer on array to write in new loop
        iIndex = 0;

        if(iRemain <= 0)    // if no remain data to write, then exit the loop
        {
            break;
        }

        if (iRemain >= iMaxByte)
        {
            iDataFieldSize = iMaxByte*2;
            iByteCount = iMaxByte + 3;
            iStop += iMaxByte; // end range of array
            iLength = iByteCount * 2;
        }
        else{
            iDataFieldSize = iRemain*2;
            iByteCount = iRemain + 3;
            iStop += iRemain; //end range of array
            iLength = iByteCount * 2;
        }

    } while (MOCK_PROJECT_TRUE);

    fclose(fp);
    printf("\n\nSuccessfully written data in to %s\n\n", FileName);

}





/* Function write to SRecord
 + Convert the array of integer to SRecord format.
 + The format of SRecord file is described at: https://en.wikipedia.org/wiki/SREC_(file_format)
 ++++ Write from the start in the new blank S-Record file.
 * Input:
    + FileName: the directory of SRecord file.
    + A: array pf integer.
    + N: length of array A or the number of integers.
*/
void WriteToNewSRecord(char * FileName, int A[], int N)
{
    // open S-Record file
    FILE *fp;

    fp = fopen(FileName, MOCK_PROJECT_WRITEMODE);
    int iByteCount = 0;
    int iMaxByte = 0xFC;
    int iAddress = 0;
    int iCheckSum = 0;

    // write header record
    fprintf(fp, "%s","S00E00004D6F636B50726F6A656374");
    iCheckSum = CheckSumCalculator("0E00004D6F636B50726F6A656374");
    fprintf(fp, "%02X\n", iCheckSum);

    //If the list of integers can be written within a record
    if (N < iMaxByte) 
    {
        // get the data field of the record
        int iDataFieldSize = N * 2;
        char sDataField[iDataFieldSize];
        iByteCount = N + 3; //size of data field + 2 byte address + 1 byte checksum
        int iIndex = 0;

        for(int i = 0; i < N; i++)
        {
            // convert integer to hexa-pair string            
            sDataField[iIndex++] = ConvertToChar(A[i]/16);  //get the first digit of hexa pair
            sDataField[iIndex++] = ConvertToChar(A[i]%16);    //get the second digit of hexa pair
        }
        sDataField[iDataFieldSize] = 0;
        
        // get the check sum
        int iLength = iByteCount * 2;
        char CheckSumString[iLength];
        char sAddress[4], sByteCount[2];

        sprintf(sByteCount, "%02X", iByteCount);
        sprintf(sAddress, "%04X", iAddress);

        strcpy(CheckSumString, sByteCount);
        strcat(CheckSumString, sAddress);
        int i = 0;
        while(i < iDataFieldSize)
        {
            CheckSumString[6 + i] = sDataField[i];
            i++;
        }
        CheckSumString[iLength] = 0;

        iCheckSum = CheckSumCalculator(CheckSumString);
        // write a complete record.
        fprintf(fp, "%s%02X%04X%s%02X\n", "S1", iByteCount, iAddress, sDataField, iCheckSum);

        fclose(fp);
        //notify if complete writing data
        printf("\n\nSuccessfully written data in to %s\n\n", FileName);

        return;

    }

    // If the list of integers is too long and must to write for several records
    int iStart = 0;
    int iStop = iMaxByte;
    int iIndex = 0;
    int iRemain = N;
    iByteCount = iMaxByte + 3;
    int iDataFieldSize = iMaxByte*2;

    do
    {
        //printf("\n\n--%d--\n\n", iStop);
        char sDataField[iDataFieldSize];
        for (int i = iStart; i < iStop; i++)
        {
            // convert integer to hexa-pair string            
            sDataField[iIndex++] = ConvertToChar(A[i]/16);  //get the first digit of hexa pair
            sDataField[iIndex++] = ConvertToChar(A[i]%16);    //get the second digit of hexa pair
        }
        
        // get the check sum
        int iLength = iByteCount * 2;
        char CheckSumString[iLength];
        char sAddress[4], sByteCount[2];

        sprintf(sByteCount, "%02X", iByteCount);
        sprintf(sAddress, "%04X", iAddress);

        strcpy(CheckSumString, sByteCount);
        strcat(CheckSumString, sAddress);

        int i = 0;
        while(i < iDataFieldSize)
        {
            CheckSumString[6 + i] = sDataField[i];
            i++;
        }
        CheckSumString[iLength] = 0;
        iCheckSum = CheckSumCalculator(CheckSumString);
        sDataField[iIndex] = 0;

        // write a complete record.
        fprintf(fp, "%s%02X%04X%s%02X\n", "S1", iByteCount, iAddress, sDataField, iCheckSum);

        iAddress += iMaxByte;       // update address
        iRemain -= iMaxByte;        // update remain integer which haven't been written to SRecord
        iStart += iMaxByte;         //Move tho next integer on array to write in new loop
        iIndex = 0;

        if(iRemain <= 0)    // if no remain data to write, then exit the loop
        {
            break;
        }

        if (iRemain >= iMaxByte)
        {
            iDataFieldSize = iMaxByte*2;
            iByteCount = iMaxByte + 3;
            iStop += iMaxByte; // end range of array
            iLength = iByteCount * 2;
        }
        else{
            iDataFieldSize = iRemain*2;
            iByteCount = iRemain + 3;
            iStop += iRemain; //end range of array
            iLength = iByteCount * 2;
        }

    } while (MOCK_PROJECT_TRUE);

    fclose(fp);
    printf("\n\nSuccessfully written data in to %s\n\n", FileName);

}





/* Function to convert binary to SRecord
 + Read the data in binary file and store each byte of the data as an element of integer array.
 + Depend on the choice of user, after read the binary file, program will call WriteToExistingSRecord()
 or WriteToNewSRecord()
 * Input:
    + FileName: the directory of SRecord file.
    + WriteMode: if true calls WriteToNewSRecord(), else callsWriteToExistingSRecord().
 */
void BinaryToSRecord(char * FileName, int WriteMode)
{
    // get the name of binary file
    char *sFileFormat = ".bin";
    printf("\n\nOpen binary file.");
    char *sFilePath = GetTheFilePath(sFileFormat);
    
    system("cls"); //Clear screen
    printf("\n\nS-Record file path: %s", FileName);
    printf("\n\nBinary file path: %s\n", sFilePath);
    printf("--------------------------------------------------------------------------------------");

    // open binary file
    FILE *fp;
    fp = fopen(sFilePath, MOCK_PROJECT_READBINARY);
    // read data in binary file and store in 'sDataField'
    char sBuffer[100];
    int iLength = 0;
    int *iDataField = malloc(1);
    do
    {
        char c = fgetc(fp);
        if(feof(fp))
        {
            break;
        }
        iDataField = realloc(iDataField, iLength + 1);
        iDataField[iLength] = (int)c;
        iLength ++;
    } while (1);

    fclose(fp);

    if (WriteMode == MOCK_PROJECT_TRUE)
    {
        WriteToNewSRecord(FileName, iDataField, iLength);
    }
    else{
        WriteToExistingSRecord(FileName, iDataField, iLength);
    }
    
    system("pause");
}





/* Function to convert integer to SRecord
 + Read the integer sequence which is the string returned from InputString(), then extract each number
 of the string, which sre separated by Space character and store in array of integer.
 + Call WriteToNewSRecord() to write the data to new S-Record file.
 * Input:
    + FileName: the directory of SRecord file.
 */
void IntegerToSRecord(char * FileName)
{
    system("cls"); //Clear screen
    printf("\n\nS-Record file path: %s\n", FileName);
    printf("--------------------------------------------------------------------------------------");

    // Input string of integer
    char *sIntegerSequence= InputString();
    if (sIntegerSequence == NULL)
    {
        return;
    }

    printf("\n\nSuccessfully input sequence:'%s'.\n\n", sIntegerSequence);
    int iStrLength = strlen(sIntegerSequence) - 1;

    // Extract the string to list of integer
    int iNum = 0;    
    int iSig = 1;
    int digit;
    int iNumOfInt = 0;
    // loop to count the number of integer
    for(int i = 0; i <= iStrLength; i++)
    {
        if (sIntegerSequence[i] == 32)
        {
            iNumOfInt ++;
        }
    }
    iNumOfInt++; // count the first integer

    // initialize array of ints
    int aListOfInt[iNumOfInt]; 
    int iTemp = iNumOfInt-1;
    // loop from the tail of string to the head
    while(iStrLength >= 0)
    {
        if (sIntegerSequence[iStrLength] == 32)
        {
            aListOfInt[iTemp] = iNum;
            iTemp --;
            iNum = 0;
            iSig = 1;
            iStrLength--;
            continue;
        }

        digit = (int)(sIntegerSequence[iStrLength] - 48);
        iNum = iNum + iSig*digit;
        iSig = iSig*10;
        iStrLength--;   
    }
    // get the first integer to the list
    aListOfInt[iTemp] = iNum;

    WriteToNewSRecord(FileName, aListOfInt, iNumOfInt);

    system("pause");
    
}




/* Function to help user choose option */
void OptionInterfaceIfOpenNewFile(char * FileName)
{
    do
    {
        system("cls"); //Clear screen
        printf("\n\nFile path: %s\n\n", FileName);
        printf("--------------------------------------------------------------------------------------");
        printf("\nChoose option to do with new S-Record.\n");
        printf(">> Press 'i': write data to S-Record after input a sequence of integers from keyboard.\n");
        printf(">> Press 'b': write data to S-Record from a binary file.\n");
        printf(">> Press 'c' to close S-Record.\n\n");
        printf(">>>> Input an option above: ");
        char cKey;
        scanf("%c", &cKey);
        getc(stdin);

        // take action with corresponding input
        switch (cKey)
        {
            case 'i':
                IntegerToSRecord(FileName);
                break;
            case 'b':
                BinaryToSRecord(FileName, MOCK_PROJECT_TRUE);
                break;
            case 'c':
                return;
            default:
                printf("\n\nInvalid Option, go back to options!\n\n");
                system("pause");           
        }
    } while(MOCK_PROJECT_TRUE);

}




/*Function to open existing S-Record file */
void OptionInterfaceIfOpenExistingFile(char * FileName)
{
    do
    {
        system("cls"); //Clear screen
        printf("\n\nFile path: %s\n\n", FileName);
        printf("--------------------------------------------------------------------------------------");
        printf("\nChoose option to do with existing S-Record.\n");
        printf(">> Press 's': check corruption for S-Record file.\n");
        printf(">> Press 'b': write data to S-Record from a binary file.\n");
        printf(">> Press 'c' to close S-Record.\n\n");
        printf(">>>> Input an option above: ");
        char cKey;
        scanf("%c", &cKey);
        getc(stdin);

        // take action with corresponding input
        switch (cKey)
        {
            case 's':
                CheckCorruption(FileName);
                break;
            case 'b':
                BinaryToSRecord(FileName, MOCK_PROJECT_FALSE);
                break;
            case 'c':
                return;
            default:
                printf("\n\nInvalid Option, go back to options!\n\n");
                system("pause");           
        }
    } while(MOCK_PROJECT_TRUE);

}




/* main function */
int main()
{
    char cQuit; // flag to stop the program
    do
    {    
        system("cls"); //Clear screen
        cQuit = 0; // reinitialize flag
        // show the list of options
        printf("\n\n           S-RECORD\n\n");
        printf("Menu\n");
        printf(">> Press 'n' to create new S-Record.\n");
        printf(">> Press 'o' to open a S-Record file.\n");
        printf(">> Press 'q' to quit program.\n\n");
        printf(">>>> Input one option above: ");
        char cKey;
        scanf("%c", &cKey);
        getc(stdin);
        char *sFilePath;

        // take action with corresponding input
        switch (cKey)
        {
            case 'n':
                system("cls"); //Clear screen
                // create new SRecord to open
                printf("---- CREATE NEW S-RECORD FILE---");
                sFilePath = GetTheFilePath(".srec");
                // choose option to do with this new file
                OptionInterfaceIfOpenNewFile(sFilePath);
                break;
            case 'o':
                system("cls"); //Clear screen
                // open SRecord to open
                printf("---- OPEN EXISTING S-RECORD FILE---");
                sFilePath = GetTheFilePath(".srec");
                // choose option to do with this new file
                OptionInterfaceIfOpenExistingFile(sFilePath);
                break;
            case 'q':
                printf("\n\nAre you sure to quit (y/n)? ");
                scanf("%c", &cQuit);
                getc(stdin);
                if (cQuit == 'y')
                {
                    return 0;
                }
                else if (cQuit == 'n')
                {
                    continue;
                }
                else{
                    printf("\n\nInvalid Option, go back to main program!\n\n");
                    system("pause");
                }
                break;
            default:
                printf("\n\nInvalid Option, go back to main program!\n\n");
                system("pause");
        }
    } while (MOCK_PROJECT_TRUE);
    return 0;
}