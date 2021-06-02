/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:06:13 by heleneherin       #+#    #+#             */
/*   Updated: 2021/06/02 17:42:43 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void haut(char *);
void bas();

int main(void)
{
     printf("Content-Type: text/html;\n\n");
     haut("Ma page en C !");

     printf("Hello World !");

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
