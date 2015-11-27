/* File Format specification */

/*
This is the current version template

#define FileName "ViamFormat"
#define FileType "CMSDATA"
#define FileVersion "2.0.2"
#define FileSections 0
#define ChunkSize 1025 // size of each data chunk in byte size, can change when data structure is updated
*/


/*Header structure */

typedef struct FileFormat {

	char FileName[30];
	int FileSize;
	char FileType[10];
	char FileVersion[10];
	int FileSections;
	int ChunkSize;

}
FileFormat;


/* Data structure */

typedef struct Contact {

	char FirstName[256];
	char LastName[256];
	char Age[32];
	char PhoneNumber[200];
	char Address[25];
	char Title[256];

}
Contact;


        char ans;
		char input[20];
		char NameInput[20];
		int counter;
		int c = 0;
        bool found = false;
        struct Contact block;
