//parses the input file into Process and event
#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
	char id[20];
	char state[20];
	char queue[20];
} Process;


int main()
{
	int i;
	char* rch;
	char str[200];
	char LineInFile[40][300];
	int lineP, lineQ;
	char* sch;
	char tokenizedLine[10][10];

	FILE* fp1;
	FILE* fp2;
	fp1 = fopen("inp1.txt", "r");			//open the original input file
	fp2 = fopen("inp1_parsed.txt", "w");	//output the Process ID and event to another file. 
	//You can store in variables instead of printing to file
	//int first = 0;
	Process processes[19];
	int temp_i[3];
	int temp_count = 0;

	char* printer_q = (char*)malloc(10 * sizeof(char));
	char* disk_q = (char*)malloc(10 * sizeof(char));
	char* kb_q = (char*)malloc(10 * sizeof(char));

	strcpy(disk_q, "");						// initialize memory location for queues
	strcpy(printer_q, "");
	strcpy(kb_q, "");


	printf("Started parsing...\n");

	//get the first line
	if (fgets(str, sizeof(str), fp1) != NULL) {
		//Remove the 'end' and print into write file
		char character = ' ';
		char* ptr = strrchr(str, character);
		*ptr = '\0';
		fprintf(fp2, "%s\n\n", str);
	}

	//get the initial process ID and its state from the first line
	char* token = strtok(str, " ");
	int j = 0;
	while (token != NULL && j < 20) {
		if (j % 2 == 0) {
			//processes[i / 2].id = atoi(token);
			strcpy(processes[j / 2].id, token);
		}
		else {
			strcpy(processes[j / 2].state, token);
		}
		strcpy(processes[j / 2].queue, "");
		token = strtok(NULL, " ");
		j++;
	}

	//printf("%d ", j / 2);
	/*
	for (int j = 0; j < i / 2; j++) {
		fprintf(fp2, "Process %d: id = %s, state = %s\n", j, processes[j].id, processes[j].state);
	}
	*/
	lineP = 0;
	i = 0;

	while (fgets(str, sizeof(str), fp1) != NULL) {
		fprintf(fp2, "%s", str);
		size_t n = j / 2;
		lineP = 0;
		rch = strtok(str, ":;.");					// use strtok to break up the line by : or . or ; This would separate each line into the different events
		while (rch != NULL)
		{
			strcpy(LineInFile[lineP], rch);			//copy the events into an array of strings
			lineP++;								//keep track of how many events are in that line
			rch = strtok(NULL, ":;.");				//needed for strtok to continue in the while loop
		}
		for (i = 1; i < lineP - 1; i++)
		{
			lineQ = 0;
			sch = strtok(LineInFile[i], " ");
			while (sch != NULL)
			{
				strcpy(tokenizedLine[lineQ], sch);		//use strtok to break up each line into separate words and put the words in the array of strings
				lineQ++;								//count number of valid elements
				sch = strtok(NULL, " ");
			}
			
			/* //Test
			fprintf(fp2, "%s ", processes[1].id);
			fprintf(fp2, "%s ", tokenizedLine[0]);
			
			for (int a = 0; a < n; a++) {
				if (strcmp(tokenizedLine[0], processes[a].id) == 0) {
					printf("True\n");
				}
			strcat(processes[0].state, "/Suspend*");
			fprintf(fp2, "%s\n", processes[0].state);
			}*/
			
			
			//tokenizedLine has the event separated by spaces (e.g. Time slice for P7 expires)
			if (strcmp(tokenizedLine[1], "requests") == 0)						//Process requests an I/O device
			{
				//fprintf(fp2, "%s %s \n", tokenizedLine[0], tokenizedLine[1]);
				//fprintf(fp2, "%s %s %s ", tokenizedLine[0], tokenizedLine[1], tokenizedLine[3]);
				for (int a = 0; a < n; a++) {
					if (strcmp(tokenizedLine[0], processes[a].id) == 0) {
						strcpy(processes[a].state, "Blocked*");
						//fprintf(fp2, "%s ", processes[a].state);
					}
				}
				//temp_count++;
			}
			else if (strcmp(tokenizedLine[2], "dispatched") == 0) {
				for (int a = 0; a < n; a++) {
					if (strcmp(tokenizedLine[0], processes[a].id) == 0) {
						strcpy(processes[a].state, "Running*");
					}
				}
				if (strcmp(tokenizedLine[3], "disk") == 0) {
					
				}
			}
			else if (strcmp(tokenizedLine[4], "expires") == 0) {
				for (int a = 0; a < n; a++) {
					if (strcmp(tokenizedLine[3], processes[a].id) == 0) {
						strcpy(processes[a].state, "Ready*");
					}
				}
			}
			else if (strcmp(tokenizedLine[3], "out") == 0) {
				for (int a = 0; a < n; a++) {
					if (strcmp(tokenizedLine[0], processes[a].id) == 0) {
						strcat(processes[a].state, "/Suspend*");
					}
				}
			}
			else if (strcmp(tokenizedLine[2], "terminated") == 0) {
				for (int a = 0; a < n; a++) {
					if (strcmp(tokenizedLine[0], processes[a].id) == 0) {
						strcpy(processes[a].state, "Exit*");
					}
				}
			}
		}
		for (int a = 0; a < n; a++) {
			fprintf(fp2, "%s %s ", processes[a].id, processes[a].state);
		}

		fprintf(fp2, "\n");
	}


	printf("Parsing complete\n\n");
	fclose(fp1);
	fclose(fp2);

	return 0;
}
