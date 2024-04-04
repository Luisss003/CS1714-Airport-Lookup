#include <stdio.h>
#include "route-records.h"
#include <stdlib.h>
#include <string.h>
RouteRecord* createRecords(FILE* fileIn){
	int count = 0;
	char placeholder[100];	//Will tell fgets how many lines to read before running into newline
	int i = 0;
	int k=0;

	fgets(placeholder, 100, fileIn); //skips first line in csv
	while(fgets(placeholder, 100, fileIn)!= NULL){ //loops until fgets reaches EOF
		count++;	//keeps count on number of lines / items in csv
	} 
	
	RouteRecord* records = (RouteRecord*)malloc(count * sizeof(RouteRecord)); //creates pointer to dynamtically allocated array
	
	for(i = 0; i < count; i++){
		for(k = 0; k < 6; k++){
			records[i].passCount[k] = 0; //sets all passenger counts for every month in every element to 0
		}
	}

	rewind(fileIn); //rewinds pointer in file back to beginning

	return records; //returns pointer to array
}

int fillRecords(RouteRecord* r, FILE* fileIn){
	char buffer[100];
	int i = 0;
	int routeCount = 0;
	
	fgets(buffer,100,fileIn); //skips first of file stream
	
	while(fgets(buffer, 100, fileIn) != NULL){ //traverses stream until EOF
 		int passengers[6] = {0,0,0,0,0,0}; 
		char TEMPorig[4];	//these TEMP variables act to compare what the sscanf function scans to what is in the csv file
		char TEMPdestination[4];
		char TEMPCode[3];
        	int month;
		char trash[10];
		int pass;
   
		sscanf(buffer,"%d, %[^,], %[^,], %[^,],%[^,], %d", &month, TEMPorig, TEMPdestination, TEMPCode, trash, &pass);	//reads line, storing data
		passengers[month-1] += pass;
	
		int routeIdx = findAirlineRoute(r,routeCount, TEMPorig, TEMPdestination, TEMPCode, 0); //returns index if a match is found, and -1 (fake inex) if match is not found
		
		if(routeIdx >= 0){
			for(i = 0; i < 6;i++){
				r[routeIdx].passCount[i] += passengers[i];
			}	
		}
	
		else{
			strcpy(r[routeCount].origin,TEMPorig);
			strcpy(r[routeCount].destination,TEMPdestination);
			strcpy(r[routeCount].airlineCode, TEMPCode);
	
	
			for(i = 0; i< 6; i++){
				r[routeCount].passCount[i] += passengers[i];	
			}
			routeCount += 1;
		}
	
	
	}

	
	return routeCount; //number of items in newly filled array

}

int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx){ //DONE
	if(curIdx >= length){ //if the pointer (currIdx) reaches the end of the file, it will return -1. This means no match was found
		return -1;	
	} 
	if(strcmp(r[curIdx].origin,origin) == 0 && strcmp(r[curIdx].destination,destination) == 0 && strcmp(r[curIdx].airlineCode, airline) == 0){
		return curIdx; //here, the recursive function will keep calling to itself, incrementing curIdx until it reatches a match
	}

	return findAirlineRoute(r,length,origin,destination,airline,curIdx + 1);
}

void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st){
//takes user input and compares it to the array made. prints out every match
	int j = 0;
	int i = 0;
	int jan = 0;
	int feb = 0;
	int mar = 0;
	int apr = 0;
	int jun = 0;
	int jul = 0;
	int count = 0;
	int totalPassengers = 0;
	
	if(strcmp(key2,"@@@") != 0){ //This path means that key2 is not @@@, which means key2 holds a record value
		
		if(st == ROUTE){
			
			for(i = 0; i < length; i++){
				if(strcmp(key1, r[i].origin) == 0 && strcmp(key2, r[i].destination) == 0){
					count++;
					printf("%s (%s - %s) ", r[i].airlineCode, r[i].origin, r[i].destination);
					jan += r[i].passCount[0];
                                        feb += r[i].passCount[1];
                                        mar += r[i].passCount[2];
                                        apr += r[i].passCount[3];
                                        jun += r[i].passCount[4];
                                        jul += r[i].passCount[5];
					for(j = 0; j < 6; j++){
						totalPassengers += r[i].passCount[j];
					}
				}
					
			}
		}
	}
	else if(strcmp(key2, "@@@") == 0){ //Path if key2 is @@@, which means it was not required,(origin, dest, and airline code).
		switch(st){
			case 1:
				for(i = 0; i<length; i++){
					if(strcmp(key1, r[i].origin) == 0){
						count++;
						printf("%s (%s-%s) ",r[i].airlineCode, r[i].origin, r[i].destination);
						jan += r[i].passCount[0];
						feb += r[i].passCount[1];
						mar += r[i].passCount[2];
						apr += r[i].passCount[3];
						jun += r[i].passCount[4];
						jul += r[i].passCount[5];
	
						for(j=0; j< 6; j++){
							totalPassengers += r[i].passCount[j];
						}
					}	
				}
				break;

			case 2:
				for(i = 0; i< length; i++){
					if(strcmp(key1,r[i].destination) == 0){
						count++;
						printf("%s (%s-%s)", r[i].airlineCode, r[i].origin, r[i].destination);
						jan += r[i].passCount[0];
                                                feb += r[i].passCount[1];
                                                mar += r[i].passCount[2];
                                                apr += r[i].passCount[3];
                                                jun += r[i].passCount[4];
                                                jul += r[i].passCount[5];
						for(j=0; j< 6; j++){
                                                        totalPassengers += r[i].passCount[j];
                                                }

					}
				}
				break;
			case 3:
				for(i = 0; i< length; i++){
                                        if(strcmp(key1,r[i].airlineCode) == 0){
                                                count++;
						printf("%s (%s-%s)", r[i].airlineCode, r[i].origin, r[i].destination);
                                                jan += r[i].passCount[0];
                                                feb += r[i].passCount[1];
                                                mar += r[i].passCount[2];
                                                apr += r[i].passCount[3];
                                                jun += r[i].passCount[4];
                                                jul += r[i].passCount[5];
                                                for(j=0; j< 6; j++){
                                                        totalPassengers += r[i].passCount[j];
                                                }

                                        }
                                }
			break;
	
		}
	}
	printf("\n");
	printf("%d matches found were found.\n", count);
	printf("\nStatistics\nTotal passengers:	%d\n", totalPassengers);
	printf("Total Passengers in Month 1:	%d\nTotal Passengers in Month 2:	%d\nTotal Passengers in Month 3:	%d\nTotal Passengers in Month 4:	%d\nTotal Passengers in Month 5:	%d\nTotal Passengers in Month 6:	%d\n\n",jan,feb,mar,apr,jun,jul);

	int average = totalPassengers / 6; //computes average passengers for the 6 months
	printf("Average passengers per month: %d\n", average); //prints average
}

void printMenu(){ //function only prints out options. Does not compute or recieve input
	printf( "\n\n######### Airline Route Records Database MENU #########\n" );
	printf( "1. Search by Route\n" );
	printf( "2. Search by Origin Airport\n" );
	printf( "3. Search by Destination Airport\n" );
	printf( "4. Search by Airline\n" );
	printf( "5. Quit\n" );
	printf( "Enter your selection: " );
}


