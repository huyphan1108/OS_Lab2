//parses the input file into Process and event
#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct processState {
	char state;
};

struct processState process[19];

int main()
{
	int i;
	char* rch;
	char str[200];
	char LineInFile[40][300];
	int lineP, lineQ, wordQ;
	char* sch;
	char tokenizedLine[10][10];
	char processID[10][10];
	char* token;


	FILE* fp1;
	FILE* fp2;
	fp1 = fopen("inp1.txt", "r");			//open the original input file
	fp2 = fopen("inp1_parsed.txt", "w");	//output the Process ID and event to another file. 
	//You can store in variables instead of printing to file

	lineP = 0;
	i = 0;

	printf("Started parsing...\n");

	//copy first line of the original file to the new filefile
	if (fgets(str, sizeof(str), fp1) != NULL)
	{
		//Removing the 'end'
		//const char character[2] = " ";
		char character = ' ';
		char* ptr = strrchr(str, character);
		*ptr = '\0';
		//printf("%s", str);
		fprintf(fp2, "%s\n", str);
		
		token = strtok(str, " ");
		size_t j = 0;
		while (token != NULL) {
		//while (str[j] != '\0') {
			printf("%s", token);
			
			strcpy(processID[0], token);
			//fprintf("%s ", processID[0]);
			token = strtok(NULL, " ");
		}
	}

		

	//parse each remaining line into Process event
	//while loop with fgets reads each line
	while (fgets(str, sizeof(str), fp1) != NULL)
	{
		//print event for each line
		//printf("%s \n", str);
		fprintf(fp2, "\n%s", str);

		lineP = 0;
		rch = strtok(str, ":;.");					// use strtok to break up the line by : or . or ; This would separate each line into the different events
		while (rch != NULL)
		{
			strcpy(LineInFile[lineP], rch);			//copy the events into an array of strings
			lineP++;								//keep track of how many events are in that line
			rch = strtok(NULL, ":;.");				//needed for strtok to continue in the while loop
		}

		//for each event (e.g. Time slice for P7 expires) pull out process number and event
		for (i = 1; i < lineP - 1; i++)
		{
			lineQ = 0;
			sch = strtok(LineInFile[i], " ");
			
			
			while (sch != NULL)
			{
				strcpy(tokenizedLine[lineQ], sch);		//use strtok to break up each line into separate words and put the words in the array of strings
				lineQ++;								//count number of valid elements
				//printf("%d", lineQ);
				sch = strtok(NULL, " ");
				//printf("%s", tokenizedLine[lineQ]);
			}
			
			

			//tokenizedLine has the event separated by spaces (e.g. Time slice for P7 expires)
			if (strcmp(tokenizedLine[1], "requests") == 0)						//Process requests an I/O device
			{
				//fprintf(fp2, "%s %s ", tokenizedLine[0], tokenizedLine[1]);
				fprintf(fp2, "%s %s %s ", tokenizedLine[0], tokenizedLine[1], tokenizedLine[3]);
				
			}
			else if ((strcmp(tokenizedLine[2], "dispatched") == 0))				//Process is dispatched
			{
				fprintf(fp2, "%s %s ", tokenizedLine[0], tokenizedLine[2]);
			}
			else if (strcmp(tokenizedLine[0], "Time") == 0)						//Process has timed off
			{
				fprintf(fp2, "%s %s ", tokenizedLine[3], tokenizedLine[4]);
			}
			else if (strcmp(tokenizedLine[3], "out") == 0)						//Process is swapped out
			{
				fprintf(fp2, "%s %s ", tokenizedLine[0], tokenizedLine[3]);
			}
			else if (strcmp(tokenizedLine[3], "in") == 0)						//Process is swapped in
			{
				fprintf(fp2, "%s %s ", tokenizedLine[0], tokenizedLine[3]);
			}
			else if (strcmp(tokenizedLine[1], "interrupt") == 0)				//An interrupt has occured
			{
				fprintf(fp2, "%s %s ", tokenizedLine[4], tokenizedLine[1]);
			}
			else																//Process has been terminated
			{
				fprintf(fp2, "%s %s ", tokenizedLine[0], tokenizedLine[2]);
			}

			/*
			if (strcmp(tokenizedLine[3], "disk") == 0) {
				fprintf(fp2, "disk queue: %s\n", tokenizedLine[0]);
			} 
			if (strcmp(tokenizedLine[3], "printer") == 0) {
				fprintf(fp2, "printer queue: %s\n", tokenizedLine[0]);
			}
			if (strcmp(tokenizedLine[3], "keyboard") == 0) {
				fprintf(fp2, "keyboard queue: %s\n", tokenizedLine[0]);
			}*/

		}
		fprintf(fp2, "\n");
	}

	printf("Parsing complete\n\n");

	fclose(fp1);
	fclose(fp2);

	return 0;
}