#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESULT_ERROR (-1)

struct header{
    char name[200];
    //FILE *fp;
    long size;
    long archiveSize;
};

long getsize(char* filename){
  FILE *f = fopen(filename, "r");
   
  if(f == NULL) {
     return RESULT_ERROR;
  }
  if(fseek(f, 0, SEEK_END) < 0) {
     fclose(f);
     return RESULT_ERROR;
  }
  long length = ftell(f);
  fclose(f);
  return length;
}
void append2(char *archive, char *file) {
  FILE* fp;
  FILE* arc;
  char buf[256];
  int offset;
  struct header fheader;
  struct header storeheader;
  struct header newheader;
  
  strcpy(fheader.name, file);

  arc = fopen(archive, "ar+");
  if(arc == NULL) {
    perror("couldn't open archive");
  }
  while(fread(&storeheader, sizeof(struct header), 1, arc) >= 1) {
    if(!strcmp(storeheader.name, file)) {
      printf("file exists\n");
      strcpy(newheader.name, file);
      exit(0);
    }
    offset = storeheader.size;
    fseek(arc, offset, SEEK_CUR);
  }
  fp = fopen(file, "r");
  if(fp == NULL) {
    perror("Error: File\n");
  }
  fseek(fp, 0, SEEK_END);
  fheader.size = ftell(fp);
  fheader.archiveSize = fheader.archiveSize + getsize(file);
  rewind(fp);

  fwrite(&fheader, sizeof(struct header), 1, arc);
  fread(buf, fheader.size, 1, fp);
  fwrite(buf, fheader.size, 1, arc);

  printf("File entered of size: %d\n", fheader.size);


  fclose(fp);
  fclose(arc);
}

void removeFile2(char *archive, char *file) {
  FILE *arc;
  FILE *newarc;
  int offset;
  struct header tempheader;
  int arcSize;

  arc = fopen(archive, "rb+");
  if(arc == NULL) {
    perror("Error: Archive\n");
  }
  newarc = fopen("temp", "rb+");
  //newarc = fopen("temp", "arb+");
  if(newarc == NULL) {
    perror("Error: New Archive\n");
  }

  while(fread(&tempheader, sizeof(struct header), 1, arc) >= 1) {
    offset = tempheader.size;
    if(!strcmp(tempheader.name, file)) {
      printf("File exists\n");
      fseek(arc, offset, SEEK_CUR);
    }
    else {
      char buf[tempheader.size + 1];
      arcSize = tempheader.size + arcSize;
      fwrite(&tempheader, sizeof(struct header), 1, newarc);
      fread(buf, offset, 1, arc);
      fwrite(buf, offset, 1, newarc);
    }
  }
  printf("size: %d\n", tempheader.archiveSize);

  fclose(arc);
  fclose(newarc);
    newarc = fopen("temp", "rb+");
  if(newarc == NULL) {
    perror("Error: Archive\n");
  }
  arc = fopen(archive, "wb+");
  //newarc = fopen("temp", "arb+");
  if(arc == NULL) {
    perror("Error: New Archive\n");
  }

  while(fread(&tempheader, sizeof(struct header), 1, newarc) >= 1) {
    offset = tempheader.size;
      char buf[tempheader.size + 1];
      fwrite(&tempheader, sizeof(struct header), 1, arc);
      fread(buf, offset, 1, newarc);
      fwrite(buf, offset, 1, arc);
  }
  fclose(arc);
  fclose(newarc);
}

void readFlag(char *archive, char *file) {
  FILE* fp;
  FILE* arc;
  char buf[256];
  int offset;
  struct header fheader;
  struct header otherheader;
  struct header myheader;
  strcpy(fheader.name, file);

  printf("List of files in archive \n");
  arc = fopen(archive, "ar+");
  if(arc == NULL) {
    perror("Archive unable to open");
  }
  while(fread(&otherheader, sizeof(struct header), 1, arc) >= 1) {
    printf("\t%s %d \n", otherheader.name, otherheader.size);
    offset = otherheader.size;
    fseek(arc, offset, SEEK_CUR);
  }
  fclose(arc);
}

int main(int argc, char* argv[]) {
  char buffer[100] = " ";
  struct header myheader;

  
  int aFlag = 0;
  int rFlag = 0;
  int lFlag = 0;
  int eFlag = 0;
  char* archive = argv[2];
  char* file = argv[3];

  if(argc < 3) {
    printf("Too few arguments.\n");
    return(-1);
  }

  if(strcmp(argv[1], "-a") == 0) {
    append2(argv[2], argv[3]);
    myheader.archiveSize = myheader.archiveSize + getsize(argv[3]);
    //argv[0], argv[1], argv[2], argv[3]
    // ./stuffy -a mystuffyarchive somefile
    // stuffy adds the file somefile to the mystuffyarchive archive file.
   }
  if(strcmp(argv[1], "-r") == 0) {
    removeFile2(argv[2], argv[3]);
    myheader.archiveSize = myheader.archiveSize - getsize(argv[3]);
    printf("Archive size after removal %ld\n", myheader.archiveSize);

    // ./stuffy -r mystuffyarchive somefile
    //  somefile should be removed from mystuffyarchive
      rFlag = 1;

    }
  if(strcmp(argv[1], "-l") == 0) {
     readFlag(argv[2], "temp.txt");
    // ./stuffy-l mystuffyarchive
    // stuffy should list the names and sizes (in bytes) of the files stored in the
      lFlag = 1;
    }

  if(strcmp(argv[1], "-e") == 0) {
     int ch;
     //redirect(argv[2], argv[3], argv[5]);
        FILE *f;
   	char s;
	f=fopen(argv[3],"r");
   	while((s=fgetc(f))!=EOF) {
      		fprintf(stdout, &s);
   	}
   	fclose(f);   
    //argv[0] argv[1] argv[2] argv[3] argv[4] argv[5]
    // ./stuffy -e mystuffyarchive somefile > someotherfile
    // stuffy should extract data of the named file from the archive to stdout, which is then redirected to someotherfile
      eFlag = 1;
    }
  
  //execl("/bin/sh", "/bin/sh", "-c", buffer, 0);
  
  return 0;
}
