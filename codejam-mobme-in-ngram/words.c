#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAXWORDSIZE 2048
#define PRINTSTART 100

void del_tmpfile() {
  unlink("mytmp");
}
int end_word(char ch)
{
  if(isalpha(ch))
    return 0;
  else
    return 1;
}
int add_word(char *curr_word,int size_word,FILE *tempfile)
{
  if(tempfile == NULL) {
    fprintf(stderr,"Invalid file\n");
    return 1;
  }
  curr_word[size_word] = '\0';
  fprintf(tempfile,"%s\n",curr_word);
  return 0;
}
int main(int argc,char *argv[])
{
  if( argc < 2 ) {
    fprintf(stderr,"Usage %s <input file>\n",argv[0]);
    exit(1);
  }
  FILE *inpfile,*tempfile;
  char ch;
  char curr_word[MAXWORDSIZE];
  unsigned int size_word = 0;
  if( (inpfile = fopen(argv[1],"r")) == NULL ) {
    fprintf(stderr,"Cannot open input file\n");
    exit(1);
  }
  if( (tempfile = fopen("mytmp","w")) == NULL ) {
    fprintf(stderr,"Cannot open temporary file\n");
    exit(1);
  }
  atexit(del_tmpfile);
  while( !feof(inpfile) ) {
    if( fread(&ch,1,1,inpfile) < 0 ) {
      fprintf(stderr,"Some error with file reading\n");
      exit(1);
    }
    if( end_word(ch) ) {
      if( size_word != 0 ) {
	if( add_word(curr_word,size_word,tempfile) != 0 ) {
	  fprintf(stderr,"Cannot add word to temporary file\n");
	  exit(1);
	}
	size_word = 0;
      }
    }
    else {
      curr_word[size_word] = ch;
      size_word++;
    }
  }
  fclose(tempfile);
  if( (tempfile = fopen("mytmp","r")) == NULL ) {
    fprintf(stderr,"Cannot open temporary file\n");
    exit(1);
  }
  char *buff=NULL;
  size_t len=0;
  ssize_t read;
  int read_lines = 0,i;
  while( ((read=getline(&buff,&len,tempfile)) != -1) && (read_lines < (PRINTSTART - 1)) ) {
    //printf("Word : %s",buff);
    free(buff);
    buff=NULL;
    read_lines++;
  }
  if( read == -1 ) {
    fprintf(stderr,"Error: Asked to start printing past end of number or words\n");
    exit(1);
  }
  char **trigram;
  if( (trigram = malloc(3 * sizeof(char **))) == NULL ) {
    fprintf(stderr,"Out of memory\n");
    exit(1);
  }
  for(i=0;i<3;i++) {
    if( (trigram[i] = malloc(MAXWORDSIZE)) == NULL ) {
      i--;
      while(i>=0) {
	free(trigram[i]);
      }
      free(trigram);
      fprintf(stderr,"Out of memory\n");
      exit(1);
    }
  }
  for(i=0;i<3;i++) {
    len = MAXWORDSIZE;
    if((read=getline(&trigram[i],&len,tempfile)) == -1) {
      fprintf(stderr,"\n\nOops! Not enough words to finsh the story\n");
      fprintf(stderr,"Try and earlier starting point\n");
      exit(1);
    }
    else {
      trigram[i][ strlen(trigram[i]) - 1 ] = '\0';
    }
  }
  for(i=0;i<67;i++) {
    if( i != 0 )
      printf(" ");
    printf("%s %s %s",trigram[0],trigram[1],trigram[2]);
    strcpy(trigram[0],trigram[1]);
    strcpy(trigram[1],trigram[2]);
    len=MAXWORDSIZE;
    if((read=getline(&trigram[2],&len,tempfile)) == -1) {
      fprintf(stderr,"\n\nOops! Not enough words to finsh the story\n");
      fprintf(stderr,"Try and earlier starting point\n");
      exit(1);
    }
    trigram[2][ strlen(trigram[2]) - 1 ] = '\0';
  }
  for( i = 0; i < 3; i++ ) {
  	free(trigram[i]);
  }
  free(trigram);
  return 0;
}
/*
int end_word(char ch) {
  switch(ch) {
  case ' ':
  case '\n':
  case ';':
  case '.':
  case '\r':
  case '\"':
      return 1;
  default:
    return 0;
  }
}
*/
