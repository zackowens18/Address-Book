/*
Name: Zack Owens 
Lab #7
Date: 3/27/2019
Description: This program creates an array of contacts and dynamically allocates memory for this array.This program allows 
you add, delete, and list all contacts. Saves the data on a text file on your computer.
*/
 struct contact{
   char fname[10];   
   char lname[10];
   char PNumber[11];
};
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
struct contact addContact();
void delCont(int number,struct contact *con);
void printCont(int num_con,struct contact *cont);
void sort_first(struct contact *cont,int Ncont);
void sort_last(int num_con,struct contact *cont);
void find_number(struct contact *cont,int ncont);
int main()
{
	
	struct contact *list;
	int input = -1;
	int Number_contacts = 0;
	srand(time(NULL));
	while(input != 0){
	printf("Phone Book Application\n1) Add friend\n2) Delete friend\n3) Show phone book\n4) Sort by First Name\n5) Sort by Last Name\n6) Find Number by Name\n7) Retrun Random Contact\n8) Delete All Contacts\n9) Save contacts to a file\n10) Load contacts from a file\n0) Exit Program\n");
	scanf("%d",&input);
	if(input==0){
		return 0;
	}
	if(input==1){
		if(Number_contacts <= 0){
			list = (struct contact*) malloc (sizeof(struct contact)); //memory allocation for the first contact only
		}
		else{
			list = realloc(list,(Number_contacts+1) * sizeof(struct contact)); //resize for each contact individually
			if(list == NULL){
			printf("Out of Memory"); // checks for memory problem 
			return 0;
			}
		}
		list[Number_contacts] = addContact(); // function promps user for data and placess in into the next available
		Number_contacts++; 
		
	}
		
	if(input == 2){ // deletion option
		
		delCont(Number_contacts,list);
		Number_contacts--;
		printf("%d",Number_contacts);
	}
	
	if(input ==3){ //prints the contacts that are valid 
		printCont(Number_contacts,list);
	}
	if(input == 4){ // sort by first name
		sort_first(list,Number_contacts);
	}
	if(input == 5){
		sort_last(Number_contacts,list);
	}
	if(input == 6){ // Return searches for name to get phone number 
		find_number(list,Number_contacts);	
	}
	if(input == 7){// Return a random phone number
		int random = rand() % Number_contacts;
		printf("%s %s %s\n",list[random].lname,list[random].fname,list[random].PNumber);	
	}
	if (input == 8){ //delete all contacts at one
		free(list);
		Number_contacts = 0;
	}
	if (input == 9){ // code that saves data to a file
		if(Number_contacts >0){
			int answerIsGood = 0;
			char FilePathName[30];
			printf("Name a file path to save data to(use a double slash for all slashes and .dat at the end) or leave blank for default path\n");
			scanf("%s",&FilePathName);
			FILE *pWrite;
			pWrite = fopen(FilePathName,"w");
			if(pWrite == NULL){
				pWrite = fopen("contact.dat","w");
				printf("Default used\n");
			}
			
			if(pWrite==NULL){
				printf("File Cannot be created or reached.\n");
			}else{
				int i;
				for(i=0;i<Number_contacts;i++){
					fprintf(pWrite,"%s %s %s ",list[i].fname,list[i].lname,list[i].PNumber);
					//printf("%s%s%s",list[i].fname,list[i].lname,list[i].PNumber);
			 }
			}
			fclose(pWrite);

				
		}else{
			printf("No Contacts to Save.\n");
		}
	}
	if (input == 10){
		printf("Name a file path that holds a data file\n");
		FILE *pRead;
		char FilePathRead[25];
		scanf("%s",&FilePathRead);
		pRead= fopen(FilePathRead,"r");
		if(pRead == NULL){
			printf("NULL");
			pRead = fopen("contact.dat","r"); // puts path to default 
			if(pRead == NULL){
				printf("Cannot open file");
			}else{
				//printf("working");
				while (!feof(pRead)) { // adds contacts to current session 
					if(Number_contacts <= 0){
						list = (struct contact*) malloc (sizeof(struct contact));
					}else{
						list = realloc(list,(Number_contacts+1) * sizeof(struct contact));
					}
					Number_contacts++;
					struct contact temp;

					fscanf(pRead,"%s %s %s ",&temp.fname,&temp.lname,&temp.PNumber); 
					
					list[Number_contacts-1] = temp;
					
					
				}
			}
		}else{ // does the same thing as above but for if user inputs correctly 
			//printf("working correctly");
			while (!feof(pRead)) {
			if(Number_contacts <= 0){
						list = (struct contact*) malloc (sizeof(struct contact));
					}else{
						list = realloc(list,(Number_contacts+1) * sizeof(struct contact));
					}
					Number_contacts++;
					struct contact temp;

					fscanf(pRead,"%s %s %s ",&temp.fname,&temp.lname,&temp.PNumber); 
					
					list[Number_contacts-1] = temp;
				
			}
		}
		fclose(pRead);
	}
	}	
	
}
struct contact addContact(){
			struct contact clist;
			//printf("Memory Allocated\n");
			printf("Enter first name:\n"); //promps user for data 
			scanf("%s",clist.fname);
			printf("Enter last name:\n");
			scanf("%s",&clist.lname);
			printf("Enter Phone Number:(include dashes)\n");
			scanf("%s",&clist.PNumber);
			//printf("%s %s %s",clist.lname,clist.fname,clist.PNumber);
			return clist;
			
		
		
}
void delCont(int number,struct contact *con){
		printf("Select a conact to delete(starting at 1):\n");
		int input2;
		int valid = 0;
		if(number>0){ //prints no contacts to be deleted of there is contacts 
		
		while(valid != 1) // makes sure user input is valid 
		{
			scanf("%d",&input2);
			if(input2>0 && input2<(number+1))
			{
				valid =1;	
			}
			else
			{
				printf("Please Enter a valid contact number:\n");
			}
		}
		input2--;
		
		int c;
		for(c=input2+1;c<number;c++){ // moves all contacts up one from deleated contact
			con[c-1] = con[c];
		
		}
		number--;
		con = realloc(con,(number) * sizeof(struct contact)); // deleates last part of array so memory is saved
		
		}
		else{
			printf("no conacts to deleate.");//prints no contacts to delete if there are no contacts 
		}
	
}
void printCont(int num_con,struct contact *cont){
		int i;
		printf("\n");
		for(i=0;i<num_con;i++){
			if(cont[i].fname!=NULL && cont[i].lname!=NULL&& cont[i].PNumber!=NULL){
			printf("%d:%s %s\n%s\n\n",i+1,cont[i].fname,cont[i].lname,cont[i].PNumber);
			}
		}
}
void sort_first(struct contact *cont,int Ncont){
	int i;
	int t;
	for(i = 0; i<Ncont-1;i++){
		for(t=i+1;t<Ncont;t++){
			if(strcmp(cont[i].fname, cont[t].fname) > 0){
				struct contact c = cont[i];
				cont[i] = cont[t];
				cont[t] = c;
				
			}
		}
	}
	
}
void sort_last(int num_con,struct contact *cont){
	int i;
	int t;
	for(i = 0; i<num_con-1;i++){
		for(t=i+1;t<num_con;t++){
			if(strcmp(cont[i].lname, cont[t].lname) > 0){
				struct contact c = cont[i];
				cont[i] = cont[t];
				cont[t] = c;
				
			}
		}
	}
}
void find_number(struct contact *cont,int ncont){
	char first[10];
	char last[10];
	struct contact answer;
	printf("Enter first Name of Contact:\n");
	scanf("%s",first);
	printf("Enter last Name of Contact\n");
	scanf("%s",last);
	int found =0;
	int i = ncont;
	for(i;i>=0;i--){
		if(strcmp(cont[i].lname,last) == 0 && strcmp(cont[i].fname,first)==0){
			answer = cont[i];
			found++;
			break;
		}
	}
	if(found == 1){
		printf("%s\n",answer.PNumber);
	}
	else{
		printf("Contact not found\n");
	}
}




