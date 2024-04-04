#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "route-records.h"

int main( int argc, char *argv[] )
{
    
	FILE* fileIn = NULL; 
	int i = 0;    
	if(argc != 2){ //if command line arguements is not 2, it returns an error. These two should be the .out and .csv file
		printf("ERROR: Missing file name and ended the program\n");
	}
	printf("Opening %s...", argv[1]); //visual confirmation process of opening file
	fileIn = fopen(argv[1],"r+");

	if(fileIn == NULL){
		printf("Couldn't open file\n");	
	}
   
	RouteRecord* arr = createRecords(fileIn);	//reading throguh given file stream, and allocating memory based on number of entrise in csv
 
    	int numItems = fillRecords(arr,fileIn); //fillRecords will fill the empty array, and return the number of entries in the new array record
	int size = numItems; //size variable for use in for loop
	printf("\nUnique routes operated by airines: %d\n\n", numItems);
	fclose(fileIn); //prevents memory leaks

	for(i = 0; i <1; i++){
    		printMenu();
    		int choice;
		scanf("%d", &choice);
		char KEY1[4];
		char KEY2[4] = "@@@"; //@@@ allows for searchRecords to ignore or use key2 with an if statement
    		switch(choice){
			case 1:	//branch if user choses route
				printf("Enter origin: ");
				scanf("%s", KEY1);
				printf("Enter  destination: "); 
				scanf("%s", KEY2);
				printf("Searching by route...\n");
				searchRecords(arr,size,KEY1,KEY2,0);
				printf("\n");		
				i--;
				break;
			case 2: //branch if user choses origin
				printf("Enter origin: "); 
				scanf("%s", KEY1);
				printf("Searching by origin...\n");
				searchRecords(arr,size,KEY1,KEY2,1);
				printf("\n");
				i--;
				break;
			case 3: //branch if user choses destination
				printf("Enter destination: ");
				scanf("%s", KEY1);
				printf("Searching by destination...\n");
				searchRecords(arr,size,KEY1,KEY2,2);
				printf("\n");
				i--;				
				break;	
			case 4:	//branch if user choses airline
				printf("Enter airline: ");
				scanf("%s", KEY1);
				printf("Searching by airline...\n");
				searchRecords(arr,size,KEY1,KEY2,3);
				printf("\n");
				i--;
				break;
			case 5:
				printf("Good-bye!\n");
				free(arr);
				break;
    			default: //branch if user does not chose a valid option
				printf("Invalid choice");
				while(getchar() != '\n');
				i--;
				break;							
		}			
    }
    return 0;
}
