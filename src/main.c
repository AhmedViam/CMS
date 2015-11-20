/**
 *
 * Name       : CMS(Content Management System)
 * File       : main.c
 * Author     : Viam
 * Language   : C
 * Size       : 19.4 KB
 * Version    : 1.2.0(Base 1.0.0)
 * Role       : Add / Save / edit / delete contact details.
 * Bugs/Issue : Sanitize code partitions.
 *
 **/


#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 
#include <windows.h> 
#include <unistd.h> 
#include "Constants.h"
#define version 2.0.1



/*Get File size, accepts pointer to the file descriptor */

int FileSize(FILE * FileHandle) {

	int start = ftell(FileHandle);
	fseek(FileHandle, 0, SEEK_END);
	int size = ftell(FileHandle);
	fseek(FileHandle, start, SEEK_SET);
	return size;
}

/*Background,foreground and text color */

int aesthetic() {


	return 0;
}


/* Prototype declarations */

void AddMember(char * FirstName, char * LastName, char * Age, char * Address, char * PhoneNumber, char * Title);

void DeleteMember();

void EditMember();

void Search();

void View();

/* Add a new record to the struct */

void AddMember(char * FirstName, char * LastName, char * Age, char * Address, char * PhoneNumber, char * Title) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);

	struct Contact people;
	strcpy(people.FirstName, FirstName);
	strcpy(people.LastName, LastName);
	strcpy(people.Age, Age);
	strcpy(people.Address, Address);
	strcpy(people.PhoneNumber, PhoneNumber);
	strcpy(people.Title, Title);


	FILE * stropenr;
	FILE * stropenw;
	FILE * strcont;
	stropenr = fopen("CMSData.vf", "rb");
	struct FileFormat * update = malloc(sizeof(struct FileFormat));

	struct FileFormat * Headerwrite = malloc(sizeof(struct FileFormat));
	fread(Headerwrite, sizeof(FileFormat), 1, stropenr);


	strcpy(update - > FileName, "CustomFormat");
	update - > FileSize = 4;
	strcpy(update - > FileType, "CMSDATA");
	strcpy(update - > FileVersion, "3.0.2");
	update - > FileSections = (1 + Headerwrite - > FileSections); // Increment the section count identifier since a new record is added
	update - > ChunkSize = 43;

	struct Contact container[Headerwrite - > FileSections]; // To hold the existing array of structs found in the file.
	// Make sure the array size is correct, which can be extracted from
	// file header, or else range and byte size to extract data will be wrong
	strcont = fopen("CMSData.vf", "rb");
	fseek(strcont, sizeof(struct FileFormat), SEEK_SET); // Move the file descriptor to the correct position, next to file header section
	fread(container, sizeof(Contact), Headerwrite - > FileSections, strcont);

	fclose(strcont);
	fclose(stropenr);


	stropenw = fopen("CMSData.vf", "wb");
	fwrite(update, sizeof(struct FileFormat), 1, stropenw);
	fclose(stropenw);

	FILE * data;

	data = fopen("CMSData.vf", "ab+");
	fseek(data, sizeof(struct FileFormat), SEEK_SET);
	fwrite( & container, sizeof(container), 1, data);
	fwrite( & people, sizeof(people), 1, data);

	fclose(strcont);
	fclose(data);

}



/* Delete a specified record from the struct, need to shift the struct positions correctly */

void DeleteMember() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

	FILE * ReadHeader;
	struct FileFormat * metadata = malloc(sizeof(struct FileFormat));
	ReadHeader = fopen("CMSData.vf", "rb");
	fread(metadata, sizeof(FileFormat), 1, ReadHeader);
	FILE * ReaderPointer;
	ReaderPointer = fopen("CMSData.vf", "rb");
	struct Contact people[metadata - > FileSections];
	int size = FileSize(ReadHeader);
	fclose(ReadHeader);

	printf("Type the FirstName of the contact you wish to delete.\n");
	fseek(ReaderPointer, sizeof(struct FileFormat), SEEK_SET); // data chunks begin right after header part
	fread(people, sizeof(block), metadata - > FileSections, ReaderPointer);
	scanf("%s", NameInput);


	for (counter = 0; counter < metadata - > FileSections; counter++) {
		if (strcmp(people[counter].FirstName, NameInput) == 0) {
			printf("Below is the user found\n");
			printf("\n%s | %s | %s | %s | %s | %s \n", people[counter].FirstName, people[counter].LastName, people[counter].Age, people[counter].Address, people[counter].PhoneNumber, people[counter].Title);
			found = true;
			//printf("Press P to comfirm deletion\n");
			//scanf("%s", input);
			system("pause");
			printf("Deleting %s", people[counter].FirstName);
			Sleep(400);

			/*Shift the selected struct position within the array of structs,
					  get the correct index and shift the remaining structs forward.
					 	*/
			//if (strcmp(input, "P") == 0) {
			for (c = counter; c < metadata - > FileSections; c++) {
				people[c] = people[c + 1];
				//}

				FILE * output;

				output = fopen("CMSData.vf", "wb");
				strcpy(metadata - > FileName, "CustomFormat");
				metadata - > FileSize = size;
				strcpy(metadata - > FileVersion, "3.0.2");
				strcpy(metadata - > FileType, "CMSDATA");
				metadata - > FileSections = metadata - > FileSections - 1; // Decrement the section count since a record has been deleted
				metadata - > ChunkSize = 1025;

				fwrite(metadata, sizeof(struct FileFormat), 1, output);
				fclose(output);
				output = fopen("CMSData.vf", "ab");
				fwrite(people, sizeof(struct Contact), (metadata - > FileSections), output);
				fclose(output);
				return;

			}
		} else {
			found = false;
		}
		found = false;
	}
	found = false;
	if (found = true) {
		printf("No users by the name %s found\n", NameInput);
		system("pause");
	}
}

/* Edit a record from the struct, need to load a copy of the struct with malloc, then edit and patch over */

void EditMember() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	FILE * ReadHeader;
	struct FileFormat * metadata = malloc(sizeof(struct FileFormat));
	ReadHeader = fopen("CMSData.vf", "rb");
	fread(metadata, sizeof(FileFormat), 1, ReadHeader);
	FILE * ReaderPointer;
	ReaderPointer = fopen("CMSData.vf", "rb");
	struct Contact people[metadata - > FileSections];
	int size = FileSize(ReadHeader);
	fclose(ReadHeader);

	printf("Type the FirstName of the contact you wish to Edit.\n");
	fseek(ReaderPointer, sizeof(struct FileFormat), SEEK_SET); // data chunks begin right after header part
	fread(people, sizeof(block), metadata - > FileSections, ReaderPointer);
	scanf("%s", NameInput);

	for (counter = 0; counter < metadata - > FileSections; counter++) {
		if (strcmp(people[counter].FirstName, NameInput) == 0) {
			printf("Below is the user found\n");
			printf("\n%s | %s | %s | %s | %s | %s \n", people[counter].FirstName, people[counter].LastName, people[counter].Age, people[counter].Address, people[counter].PhoneNumber, people[counter].Title);
			found = true;
			system("pause");
			system("cls");


			printf("1. To edit FirtName enter F\n2. To edit LastName enter L\n3. To edit Age enter A\n4. To edit Address type AD\n5. To edit Number type N\n6. To edit Title press T\n7. To exit press X\n");
			scanf("%s", input);
			if (strcmp(input, "F") == 0) {
				printf("Enter the new FirstName\n");
				scanf("%s", input);
				printf("Changed First name from %s to %s\n", people[counter].FirstName, input);
				system("pause");
				strcpy(people[counter].FirstName, input);
				printf("Editing completed %d\n", counter);


				FILE * output;

				output = fopen("CMSData.vf", "wb");
				strcpy(metadata - > FileName, "CustomFormat");
				metadata - > FileSize = size;
				strcpy(metadata - > FileVersion, "3.0.2");
				strcpy(metadata - > FileType, "CMSDATA");
				//metadata->FileSections = metadata->FileSections - 1; // Decrement the section count since a record has been deleted
				metadata - > ChunkSize = 1025;

				fwrite(metadata, sizeof(struct FileFormat), 1, output);
				fclose(output);
				output = fopen("CMSData.vf", "ab");
				fwrite(people, sizeof(struct Contact), (metadata - > FileSections), output);
				fclose(output);
				return;
			}

			if (strcmp(input, "L") == 0) {
				printf("Enter the new LastName\n");
				scanf("%s", input);
				printf("Changed Last name name from %s to %s\n", people[counter].LastName, input);
				system("pause");
				strcpy(people[counter].LastName, input);
				printf("Editing completed %d\n", counter);


				FILE * output;

				output = fopen("CMSData.vf", "wb");
				strcpy(metadata - > FileName, "CustomFormat");
				metadata - > FileSize = size;
				strcpy(metadata - > FileVersion, "3.0.2");
				strcpy(metadata - > FileType, "CMSDATA");
				//metadata->FileSections = metadata->FileSections - 1; // Decrement the section count since a record has been deleted
				metadata - > ChunkSize = 1025;

				fwrite(metadata, sizeof(struct FileFormat), 1, output);
				fclose(output);
				output = fopen("CMSData.vf", "ab");
				fwrite(people, sizeof(struct Contact), (metadata - > FileSections), output);
				fclose(output);
				return;
			}

			if (strcmp(input, "N") == 0) {
				printf("Enter the new PhoneNumber\n");
				scanf("%s", input);
				printf("Changed PhoneNumber from %s to %s\n", people[counter].PhoneNumber, input);
				system("pause");
				strcpy(people[counter].PhoneNumber, input);
				printf("Editing completed %d\n", counter);


				FILE * output;

				output = fopen("CMSData.vf", "wb");
				strcpy(metadata - > FileName, "CustomFormat");
				metadata - > FileSize = size;
				strcpy(metadata - > FileVersion, "3.0.2");
				strcpy(metadata - > FileType, "CMSDATA");
				//metadata->FileSections = metadata->FileSections - 1; // Decrement the section count since a record has been deleted
				metadata - > ChunkSize = 1025;

				fwrite(metadata, sizeof(struct FileFormat), 1, output);
				fclose(output);
				output = fopen("CMSData.vf", "ab");
				fwrite(people, sizeof(struct Contact), (metadata - > FileSections), output);
				fclose(output);
				return;
			}


			if (strcmp(input, "T") == 0) {
				printf("Enter the new Title\n");
				scanf("%s", input);
				printf("Changed Title from %s to %s\n", people[counter].Title, input);
				system("pause");
				strcpy(people[counter].Title, input);
				printf("Editing completed %d\n", counter);


				FILE * output;

				output = fopen("CMSData.vf", "wb");
				strcpy(metadata - > FileName, "CustomFormat");
				metadata - > FileSize = size;
				strcpy(metadata - > FileVersion, "3.0.2");
				strcpy(metadata - > FileType, "CMSDATA");
				//metadata->FileSections = metadata->FileSections - 1; // Decrement the section count since a record has been deleted
				metadata - > ChunkSize = 1025;

				fwrite(metadata, sizeof(struct FileFormat), 1, output);
				fclose(output);
				output = fopen("CMSData.vf", "ab");
				fwrite(people, sizeof(struct Contact), (metadata - > FileSections), output);
				fclose(output);
				return;
			}


			if (strcmp(input, "AD") == 0) {
				printf("Enter the new Address\n");
				scanf("%s", input);
				printf("Changed Address from %s to %s\n", people[counter].Address, input);
				system("pause");
				strcpy(people[counter].Address, input);
				printf("Editing completed %d\n", counter);


				FILE * output;

				output = fopen("CMSData.vf", "wb");
				strcpy(metadata - > FileName, "CustomFormat");
				metadata - > FileSize = size;
				strcpy(metadata - > FileVersion, "3.0.2");
				strcpy(metadata - > FileType, "CMSDATA");
				//metadata->FileSections = metadata->FileSections - 1; // Decrement the section count since a record has been deleted
				metadata - > ChunkSize = 1025;

				fwrite(metadata, sizeof(struct FileFormat), 1, output);
				fclose(output);
				output = fopen("CMSData.vf", "ab");
				fwrite(people, sizeof(struct Contact), (metadata - > FileSections), output);
				fclose(output);
				return;
			}


			if (strcmp(input, "A") == 0) {
				printf("Enter the new Age\n");
				scanf("%s", input);
				printf("Changed Age from %s to %s\n", people[counter].Age, input);
				system("pause");
				strcpy(people[counter].Age, input);
				printf("Editing completed %d\n", counter);


				FILE * output;

				output = fopen("CMSData.vf", "wb");
				strcpy(metadata - > FileName, "CustomFormat");
				metadata - > FileSize = size;
				strcpy(metadata - > FileVersion, "3.0.2");
				strcpy(metadata - > FileType, "CMSDATA");
				//metadata->FileSections = metadata->FileSections - 1; // Decrement the section count since a record has been deleted
				metadata - > ChunkSize = 1025;

				fwrite(metadata, sizeof(struct FileFormat), 1, output);
				fclose(output);
				output = fopen("CMSData.vf", "ab");
				fwrite(people, sizeof(struct Contact), (metadata - > FileSections), output);
				fclose(output);
				return;

			}
			if (strcmp(input, "X") == 0) {
				printf("Exiting...");
				Sleep(600);
				break;
				return;
			}

			printf("Wrong input\n");
		} else {
			printf("Could not find a match");
			Sleep(900);
			return;
		}

	}

}

/* Search the binary file for a specified record from the stored struct */

void Search() {


	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	FILE * ReadHeader;
	struct FileFormat * metadata = malloc(sizeof(struct FileFormat));
	ReadHeader = fopen("CMSData.vf", "rb");
	fread(metadata, sizeof(FileFormat), 1, ReadHeader);
	FILE * ReaderPointer;
	ReaderPointer = fopen("CMSData.vf", "rb");
	struct Contact people[metadata - > FileSections];
	int size = FileSize(ReadHeader);
	fclose(ReadHeader);

	printf("Type the FirstName of the contact\n");
	scanf("%s", NameInput);
	fseek(ReaderPointer, sizeof(struct FileFormat), SEEK_SET);
	fread(people, sizeof(block), metadata - > FileSections, ReaderPointer);

	/* Access the struct data with the correct offset with relation to section count */
	for (counter = 0; counter < metadata - > FileSections; counter++) {
		if (strcmp(people[counter].FirstName, NameInput) == 0) {
			printf("\n%s | %s | %s | %s | %s | %s \n", people[counter].FirstName, people[counter].LastName, people[counter].Age, people[counter].Address, people[counter].PhoneNumber, people[counter].Title);
			found = true;
			system("pause");
			return;
		} else {
			found = false;
		}
	}
	if (found = TRUE) {
		printf("No users found\n");
		Sleep(600);
	}




}

/* View the complete list of structs from the binary file */
 
void View() {


	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);

	FILE * ReadHeader;
	struct FileFormat * metadata = malloc(sizeof(struct FileFormat));
	ReadHeader = fopen("CMSData.vf", "rb");
	fread(metadata, sizeof(FileFormat), 1, ReadHeader);
	FILE * ReaderPointer;
	ReaderPointer = fopen("CMSData.vf", "rb");
	struct Contact people[metadata - > FileSections];
	int size = FileSize(ReadHeader);
	fclose(ReadHeader);


	if (metadata - > FileSections != 0) {
		printf("Retrieving contact list ...\n");
		fseek(ReaderPointer, sizeof(struct FileFormat), SEEK_SET);
		fread(people, sizeof(block), metadata - > FileSections, ReaderPointer);
		for (counter = 0; counter < metadata - > FileSections; counter++) {
			printf("\n%s | %s | %s | %s | %s | %s \n", people[counter].FirstName, people[counter].LastName, people[counter].Age, people[counter].Address, people[counter].PhoneNumber, people[counter].Title);
			found = true;

		}
		//printf("Press any key to continue \n");
		printf("\n");
		system("pause");
	} else {
		printf("No records found");
	}
	Sleep(600);

}



/* Entry point */



int main() {

	aesthetic();

	int width = 60;
	int widths = 40;
	int length = sizeof("Welcome to CMS Dashboard") - 1;
	int pad = (length >= width) ? 0 : (width - length) / 2;
	int pads = (length >= widths) ? 0 : (widths - length) / 2;

	FILE * ReadPointer;

	struct FileFormat * init = malloc(sizeof(struct FileFormat)); // Initial memory space to write file header
	ReadPointer = fopen("CMSData.vf", "rb");
	int size = FileSize(ReadPointer);


	if (access("CMSData.vf", F_OK) != -1) {

		struct FileFormat * Header = malloc(sizeof(struct FileFormat)); // Read meta data from file header
		fread(Header, sizeof(FileFormat), 1, ReadPointer);

		printf("%*.*s%s\n", pad, pad, " ", "CMS Data repository is being loaded");
		Sleep(2000);
		printf("%*.*sRepository size %d bytes version %s Number of records %d \n", pads, pads, " ", size, Header - > FileVersion, Header - > FileSections);
		fclose(ReadPointer);

	} else {

		ReadPointer = fopen("CMSData.vf", "wb");
		strcpy(init - > FileName, "CustomFormat");
		strcpy(init - > FileVersion, "2.0.2");
		strcpy(init - > FileType, "CMSDATA");
		init - > FileSections = 0;
		init - > ChunkSize = 1025;

		printf("CMSData file not found...\n");
		Sleep(3000);
		printf("Creating data repository\n");
		Sleep(2000);
		fwrite(init, sizeof(struct FileFormat), 1, ReadPointer);
		fclose(ReadPointer);

		fflush(stdin);
		fflush(stdout);
	}





	do {

		system("cls");
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		ReadPointer = fopen("CMSData.vf", "rb");
		struct FileFormat * Header = malloc(sizeof(struct FileFormat));
		fread(Header, sizeof(FileFormat), 1, ReadPointer);
		printf("%*.*sRepository size %d bytes version %s Number of records %d \n", pads, pads, " ", FileSize(ReadPointer), Header - > FileVersion, Header - > FileSections);
		fclose(ReadPointer);



		printf("For Record related press R for Adding a record press A\n");
		scanf("%s", & input);
		//if (strcmp(input, "R") == 0) {
		system("cls");

		FILE * ReadHeader;
		struct FileFormat * metadata = malloc(sizeof(struct FileFormat));
		ReadHeader = fopen("CMSData.vf", "rb");
		fread(metadata, sizeof(FileFormat), 1, ReadHeader);
		fclose(ReadHeader);

		int c = 0;
		bool found = false;
		struct Contact block;

		FILE * ReaderPointer;
		ReaderPointer = fopen("CMSData.vf", "rb");
		struct Contact people[metadata - > FileSections];





		if (strcmp(input, "R") == 0) {
			printf("\nWelcome to CMS Dashboard\n");
			printf("What would you like to do?\n\n1. To view all contacts press V\n2. To search for a contact press S\n3. To delete a contact press D\n4. To edit a record press E\n");
			scanf("%s", & ans);
			switch (ans) {


				case 'S':
					{
						Search();
						break;
					}

				case 'V':
					{
						View();
						break;
					}

				case 'D':
					{
						DeleteMember();
						break;
					}

				case 'E':
					{
						EditMember();
						break;

					}
				default:
					printf("\nWrong input\n");
					Sleep(600);
					break;
			}

		}

		if (strcmp(input, "A") == 0) {

			struct Contact people;

			printf("Person 's First Name: ");

			scanf("%s", people.FirstName);

			printf("Person's Last Name: ");
			scanf("%s", people.LastName);

			printf("Person's Age: ");
			scanf("%s", people.Age);

			printf("Person's Address: ");
			scanf("%s", people.Address);

			printf("Person's PhoneNumber: ");
			scanf("%s", people.PhoneNumber);

			printf("Person's Title: ");
			scanf("%s", people.Title);

			AddMember(people.FirstName, people.LastName, people.Age, people.Address, people.PhoneNumber, people.Title);
			printf("New record added\n");
			Sleep(1000);
		}








		/*Just to read the file header for debug purposes */

		if (strcmp(input, "O") == 0) {

			FILE * file;
			struct FileFormat * Header = malloc(sizeof(struct FileFormat));
			file = fopen("CMSData.vf", "rb");
			if (file != NULL) {
				fread(Header, sizeof(FileFormat), 1, file);
				fclose(file);
			}
			printf("%s %d %s %d %d\n", Header - > FileName, Header - > FileSize, Header - > FileType, Header - > FileSections, Header - > ChunkSize);
			Sleep(2000);
			/* add edit routine here */
		}



	} while (true);
	//printf("Unknown input! exiting...");
	return 0;



}
