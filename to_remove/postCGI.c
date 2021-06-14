#include <stdio.h>
#include <stdlib.h> // Ne pas oublier pour getenv()
#include <string.h>
#include <unistd.h>

void haut(char *);
void bas();

int main(int ac, char**av, char**env)
{
     char montexte[80] = "";
	 char* contentlength = getenv("CONTENT-LENGTH");
	int size;
      if (contentlength)
          size = atoi(contentlength);
     else 
          size = 9;

     printf("Content-Type: text/html;\n\n");
     haut("Ma page en C !");
   //  if(fscanf(stdin, "data=%80[^&]s", montexte) < 0)
   int n = read(0, montexte, size);
	 if (n < 1)
          printf("<p>Le formulaire a été mal rempli !</p>");
     else
          printf("Voici ce que vous avez écrit : -%s-", montexte);
     bas();
     return 0;
}

/* On sépare le squelette HTML du reste du code */
void haut(char *title) {
     printf("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"fr\" >\n\t<head>");
     printf("\t\t<title>%s</title>", title);
     printf("\t\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n\t</head>\n\t<body>");
}

void bas() {
     printf("\t</body>\n</html>");
}
