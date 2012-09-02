#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void usage(char *argv[]) {
  fprintf(stderr,"Usage: %s [<input time>]\n",argv[0]);
  fprintf(stderr,"Example : %s 2:43pm\n",argv[0]);
  exit(1);
}
void print_minutes(int min)
{
  switch(min)
    {
    case 5: printf(" five past");break;
    case 10: printf(" ten past");break;
    case 15: printf(" quarter past");break;
    case 20: printf(" twenty past");break;
    case 25: printf(" twenty five past");break;
    case 30: printf(" half past");break;
    case 35: printf(" twenty five to");break;
    case 40: printf(" twenty to");break;
    case 45: printf(" quarter to");break;
    case 50: printf(" ten to");break;
    case 55: printf(" five to");break;
    }
}
void print_hours(int twentyfour)
{
  switch(twentyfour)
    {
    case 0:printf(" midnight");break;
    case 1:printf(" one in the morning");break;
    case 2:printf(" two in the morning");break;
    case 3:printf(" three in the morning");break;
    case 4:printf(" four in the morning");break;
    case 5:printf(" five in the morning");break;
    case 6:printf(" six in the morning");break;
    case 7:printf(" seven in the morning");break;
    case 8:printf(" eight in the morning");break;
    case 9:printf(" nine in the morning");break;
    case 10:printf(" ten in the morning");break;
    case 11:printf(" eleven in the morning");break;
    case 12:printf(" noon");break;
    case 13:printf(" one in the afternoon");break;
    case 14:printf(" two in the afternoon");break;
    case 15:printf(" three in the afternoon");break;
    case 16:printf(" four in the evening");break;
    case 17:printf(" five in the evening");break;
    case 18:printf(" six in the evening");break;
    case 19:printf(" seven in the evening");break;
    case 20:printf(" eight at night");break;
    case 21:printf(" nine at night");break;
    case 22:printf(" ten at night");break;
    case 23:printf(" eleven at night");break;
    }
}
int main(int argc,char *argv[])
{
  char *colon;
  int hours,minutes,temp_minutes,temp_hours,am,twentyfour;
  if(argc > 2) {
    usage(argv);
  }
  if(argc == 2) {
    colon = strstr(argv[1],":");
    if(colon == NULL) {
      fprintf(stderr,"Invalid time format on command line\n");
      usage(argv);
    }
    sscanf(argv[1],"%d",&temp_hours);
    sscanf(colon + 1,"%d",&temp_minutes);
    if( (strstr(argv[1],"am") != NULL) || (strstr(argv[1],"AM") != NULL) ) {
      am = 1;
    }
    else if( (strstr(argv[1],"pm") != NULL) || (strstr(argv[1],"PM") != NULL) ) {
      am = 0;
    }
    else
      usage(argv);
  }
  else {
    /* Nothng passed from command line. Use sytem time. */
    time_t timep = time(NULL);
    struct tm *curr_time = gmtime(&timep);
    temp_minutes = curr_time->tm_min;
    temp_hours = curr_time->tm_hour;
    if(temp_hours > 12) {
     am = 0;
     temp_hours-=12;
     }
    else {
     am = 1;
     }
  }
  minutes = (temp_minutes/5) * 5;
  if( (temp_minutes%5) > 2 ) {
    minutes += 5;
  }
  if(minutes > 30) {
    hours = temp_hours + 1;
    if( hours == 13 )
      hours = 1;
    if( hours ==  12 ) {
      if ( am == 1 )
	am = 0;
      else
	am = 1;
    }
  }
  else {
    hours = temp_hours;
  }
  printf("Time is");
  if((temp_minutes < minutes) && (temp_hours == hours)){
    printf(" almost");
  }
  else if((temp_minutes > minutes) && (temp_hours == hours)){
    printf(" about");
  }
  else if((temp_minutes > minutes) && (temp_hours != hours)) {
    printf(" almost");
  }
  else if((temp_minutes < minutes) && (temp_hours != hours)) {
    printf(" around");
  }
  else if(temp_minutes == minutes){
    printf(" exactly");
  }
  print_minutes(minutes);
  if( am == 0 ) {
    if( hours == 12 )
      twentyfour = 12;
    else
      twentyfour = hours + 12;
  }
  else {
    if( hours == 12 )
      twentyfour = 0;
    else
      twentyfour = hours;
  }
  print_hours(twentyfour);
  printf("\n");
  return 0;
}
