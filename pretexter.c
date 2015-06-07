#include<stdio.h>  //Standard I/O
#include<conio.h>  //getch() exit()
#include<string.h>  //String handling

void main( int argc, char *argv[] ) //For Command line arguments
{
FILE *f;  //Text file pointer
FILE *fh; //HTM Or HTML file pointer

char *ch; //String read from file at a time
char *http; //link + extra chars extracted from 'ch'

char *link_before; //Part Before link in 'http'
char *link; //Finally extracted 'link' ready to be used
char *link_after;  //Part after link in 'http'

char *txtfile; //[]="\\hacking.txt"; /*8+3=11 Character Naming*/
char *htmfile; //[]="\\hacking.htm";
char *ext;

int x=0; //Tmp integer holder
int c=0;  //Counts total no of links detected
int check=0; //FLAG to check links >0 - detected ==0 undetected
int j=0; //i=0; //loop variables

char *test[4]= {
	"http://",
	   "www.",
	    "://",
	 "mailto",
	   }; //Link in file is identified by these 'strings'

clrscr();

/*COMMAND LINE ARGUMENT EXTRACTION STARTS HERE*/
//------------------------------------------------

if (argc==1) //i.e No parameter entered.
   {
   printf("PreTexter V 1.0 By Bhupal Sapkota (BOS)\n");
   printf("----------------------------------------\n\n");
   printf("Syntax : pretext <filename.txt>\n");
   printf("Extension is not compulsory\n\n");
   printf("Enter Text File Name: ");
   scanf("%s",txtfile);
   }

   else
   {
   strcpy(txtfile,argv[1]);
   }

   ext=strchr(txtfile,'.');
   if (ext !=NULL && strcmp(ext,".txt")==0)
    {
    strncpy(htmfile,txtfile,ext-txtfile);
    htmfile[ext-txtfile]='\0';
    strcat(htmfile,".htm");

    }
    else
    {

    strcpy(htmfile,txtfile);
    strcat(txtfile,".txt");
    strcat(htmfile,".htm");
    strlwr(txtfile);
    strlwr(htmfile);
    //printf("\n\nPreTexter V 1.0 By Bhupal Sapkota (BOS)\n");
    //printf("----------------------------------------\n\n");
    //printf("Syntax : pretext <filename.txt>\n");
    //printf("Extension is not compulsory\n\n");
    //printf("Incorrect Textfile name.\n");getch();exit(1);
    }

/*COMMAND LINE ARGUMENT EXTRACTION ENDS HERE*/


if ((f=fopen(txtfile,"r"))==NULL)
     {
     printf("\nSorry, Error opening Text file! ");
     getch();
     exit(0);
     }

if((fh=fopen(htmfile,"w"))==NULL)
     {
     printf("\nSorry, Error creating HTML file! ");
     getch();
     exit(1);
     }

//HTML Coding Starts Form Here
fprintf(fh,"<html>\n<head>\n");

//Title of HTML page is extracted from first 30 characters of Text File
fgets(ch,30,f);

//ch[strlen(ch)+1]='\0';

fprintf(fh,"<title>%s...</title>\n");
fprintf(fh,"<script language=\"javascript\">\n function show() { window.status=\"Created with PreTexter V 1.0 By Bhupal Sapkota (PAL)\"} </script> ");
fprintf(fh,"</head>");
fprintf(fh,"\n<body>\n<pre>");
//fprintf(fh,"\n");

//Body of the HTML File
//fprintf(fh,"<body>");

rewind(f);

while (!feof(f)) //Loop to Read file
{

	fgets(ch,100,f); // Maxm link length is 100 characters

	for (j=0;j<4;j++)  //Since there are 3 test to identify  links this checks so
		{
		http=strstr(ch, test[j]);
		if ( http != NULL){check=1;break;}
		else check=0; //Don't break Ok
		}

	if (check==1)   /* Part Before link, link and part after link
			are separated from 'ch' in this part */
		{
		//If ch and http are equal then link_before doesn't exists
		if(strlen(http)!=strlen(ch) && strlen(ch) !=0)
			{
			x=http-ch;
			strncpy(link_before,ch,x);  // Before link part is  extracted from 'Ch' stringlink_before[x] = '\0';
			link_before[x] = '\0';
			}
		else strset(link_before,NULL);

		if( (link_after=strchr(http,' ')) != NULL )
			{
			x=link_after-http;
			strncpy(link,http,x);  // Link is  extracted from http string
			link[x] = '\0';
			}
		else  strcpy(link,http);

		/*The Extracted Parts of 'ch' are now formated with <pre> and <a>
		tag and written to html file*/

		if (strlen(link_before) !=0)
			{
			//********PRE************
			fprintf(fh,"%s",link_before); //Part Before Link
			//********PRE************
			}

		fprintf(fh,"<a href=\"%s\">%s</a target=\"_blank\">",link,link); //LINK IS CODED HERE

		if (strlen(link_after) !=0)
			{
			//********PRE************
			fprintf(fh,"%s",link_after); //Part After Link
			//********PRE************
			}

	c++;
}
else //check=0
{
	if(strlen(ch)!=0)
		{
	       //fprintf(fh,"\n");
		//********PRE************
		fprintf(fh,"%s",ch);  /*If 'ch' i.e line read from
						textfile doesn't contains
						Link this part will be printed */
		//********PRE************
		}
}

}//When eof reached

//END of HTMl File
//fprintf(fh,"\n");
fprintf(fh,"\n<center><a onmouseover=show() href=\"http://www.bhupalsapkota.com.np/index.php?wh=res\">Pal</a></center>\n</pre>\n</body>\n</html>");

fclose(f);
fclose(fh);  /*Files Are Closed */

printf("\n\n\n*Total %d links detected in %s\n\n", c,txtfile);
printf("%s Successfully Converted into %s\n",txtfile,htmfile);
printf("\n");
printf("\n");
printf("            PreTexter V 1.0 Developed By:\n");
printf("--------------------------------------------------------\n");
printf("\n");
printf(" 	      ** Bhupal Sapkota - Pal **\n");
printf("\n");
printf(" Bachelors in Computer Engineering, I-year, I-semester\n");
printf("    From: Tribhuwan University, Kathmandu, Nepal\n");
printf("\n");
printf("       Contact Mail Address: pals@bhupalsapkota.com.np\n");
printf("\n");
printf("              Permanent Address:\n");
printf("           -------------------------\n");
printf(" 	      Bhupal Sapkota\n");
printf("  Bharatpur Municipality -9, Sharadpur, Chitwan, Nepal\n");
printf("           -------------------------\n");
printf("\n");
printf("                Compiled Date:\n");
printf("Feb 17th 2008,A.D (2063-Falgun-5th,B.S., Nepali Date)\n");
printf("\n");
printf("                    || FREEWARE ||  \n");
printf("\n");
printf("--------------------------------------------------------\n");


getch();
} /*End of main function of Programme*/

/*
 Program By:
 --------------
 **Bhupal Sapkota**
 Bachelors in Computer Engineering, I-year, I-semester
 From: Tribhuwan University, Kathmandu, Nepal
 Contact Address: bhu1st@hotmail.com

 Permanent Address:
 -------------------
 Bhupal Sapkota
 Bharatpur Municipality -9, Sharadpur, Chitwan, Nepal
 -------------------
 Date : June 24th 2006,A.D (2063-Asad-10th,B.S., Nepali Date)
*/


