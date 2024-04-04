#ifndef ROUTE_RECORDS_H
#define ROUTE_RECORDS_H

typedef struct RouteRecord{

	char origin[4];
	char destination[4];
	char airlineCode[3];
	int passCount[6];

}RouteRecord;

typedef enum SearchType{
	ROUTE,
	ORIGIN,
	DESTINATION,
	AIRLINE,
} SearchType;

RouteRecord* createRecords(FILE*);
int fillRecords(RouteRecord*, FILE*);
int findAirlineRoute(RouteRecord*, int, const char*, const char*, const char*, int);
void searchRecords(RouteRecord*, int, const char*, const char*, SearchType);
void printMenu();

#endif 
