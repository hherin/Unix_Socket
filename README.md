# UNIX_SOCKETT

Premiers pas vers la programmation Unix Socket.

[TUTORIEL](https://www.tutorialspoint.com/unix_sockets/index.htm)

[Select()](http://codingbison.com/c/c-sockets-select.html)

[Expect cmd](https://likegeeks.com/expect-command/)

## TABLE DES MATIERES
1. [Comment créer un processus client](#comment-créer-un-processus-client)

### Definition

Les sockets permettent la **communication entre deux processus** sur une ou plusieurs machines



2 des 4 types dont on va s'interesser:
- _Stream sockets_ : ils utilisent le protocole TCP pour le transport des données. La livraison est toujours garantie.
- _Datagram sockets_ : ils utilisent le protocole UDP. Il n'y a pas de connexion eentre le serveur et le client et la livraison n'est pas garantie.




## Comment créer un process client

- le client envoie une requete dans l'attente d'un retour du serveur.

   Créer un socket via le system call **socket()**

   Connecter le socket a l'adresse du serveur via **connect()**

   Envoyer la requête et recevoir les donner avec **read() write()**




## Comment créer un process serveur

- Le serveur recoit la requête du client, la traite puis rassemble toutes les informations. Envoie ces derniers au clients et enfin se rend disponible pour une nouvelle requête a traiter.

   Créer un socket via le system call **socket()**

   Lie le socket a une adresse : **bind()**. Dans le cas d'un socket serveur sur internet, l'adresse correspond au port de la machine hôte.

   Se met sur écoute pour une nouvelle connexion : **listen()**

   Accepte la connexion : **accept()**. le serveur est bloqué a cette étape tant que la connexion avec un client n'est pas faite.

   Envoie et recooid les données via les system call **read() write()**



Diagram des interactions Client-Serveur

![alt text](https://www.tutorialspoint.com/unix_sockets/images/socket_client_server.gif)



## Acces aux infos d'adressage et port

Diverses structures seront utilisées.

### :white_small_square: sockaddr - infos du socket


```C
struct sockaddr {
   unsigned short   sa_family;
   char             sa_data[14];
};
```

| Attribute | Values | Description |
| --- | --- | ---| 
|sa_family | AF_INET \| AF_UNIX \| AF_NS \| AF_IMPLINK | It represents an address family. In most of the Internet-based applications, we use AF_INET.
| sa_data | Protocol-specific Address | The content of the 14 bytes of protocol specific address are interpreted according to the type of address. For the Internet family, we will use port number IP address, which is represented by sockaddr_in structure defined below. |




### :white_small_square: sockaddr in - Une aide pour faire reference aux elements du socket


```C
struct sockaddr_in {
   short int            sin_family;
   unsigned short int   sin_port;
   struct in_addr       sin_addr;
   unsigned char        sin_zero[8];
};
```



| Attribute | Values | Description |
| --- | --- | ---| 
|sa_family | AF_INET \| AF_UNIX \| AF_NS \| AF_IMPLINK | It represents an address family. In most of the Internet-based applications, we use AF_INET.
| sin_port | Service Port | A 16-bit port number in Network Byte Order. |
| sin_addr | IP Address | A 32-bit IP address in Network Byte Order. |
| sin_zero | Not Used | You just set this value to NULL as this is not being used. |



### :white_small_square: in addr - Utilisé dans la structure au dessus


```C
struct in_addr {
   unsigned long s_addr;
};
```



| Attribute | Values | Description |
| --- | --- | ---| 
| s_addr | service port | A 32-bit IP address in Network Byte Order. |



### :white_small_square: hostent - Garde les infos de l'hôte.


```C
struct hostent {
   char *h_name; 
   char **h_aliases; 
   int h_addrtype;  
   int h_length;    
   char **h_addr_list
	
#define h_addr  h_addr_list[0]
};
```


| Attribute | Values | Description |
| --- | --- | ---| 
| h_name | ti.com etc. | It is the official name of the host. For example, tutorialspoint.com, google.com, etc. |
| h_aliases | TI | It holds a list of host name aliases. |
| h_addrtype | AF_INET | It contains the address family and in case of Internet based application, it will always be AF_INET. |
| h_length | 4 | It holds the length of the IP address, which is 4 for Internet Address. |
| h_addr_list | in_addr| For Internet addresses, the array of pointers h_addr_list[0], h_addr_list[1], and so on, are points to structure in_addr. |

>  h_addr is defined as h_addr_list\[0\] to keep backward compatibility.




### :white_small_square: Servent - Garde les informations reliées au service et ports associées



```C
struct servent {
   char  *s_name; 
   char  **s_aliases; 
   int   s_port;  
   char  *s_proto;
};
```


| Attribute | Values | Description |
| --- | --- | ---| 
| s_name | http | This is the official name of the service. For example, SMTP, FTP POP3, etc. |
| s_aliases | ALIAS | It holds the list of service aliases. Most of the time this will be set to NULL. |
| s_port | 80 | It will have associated port number. For example, for HTTP, this will be 80. |
| s_proto | TCP \/ UDP | It is set to the protocol used. Internet services are provided using either TCP or UDP. |


### TIPS

Ces structures sont une part integrante de tout _network program_. 

Elles sont passées par reference (pointeurs) aux fonctions avec leur tailles.



## Ports et Services

Quand un processus client cherche a se connecter au serveur, il doit avoir un moyen d'identifier celui-ci. 

Meme si le client connait l'adresse ip du serveur, il doit aussi avoir connaissance du port.

L'assignement des ports se situe dans le fichier /etc/services. => checker que le port ne soit pas assigné a un autre serveur.

[Plus de detail ici](https://www.tutorialspoint.com/unix_sockets/ports_and_services.htm)



## Fonction manipulation adresse IP

```C
inet_addr(const char *strptr);
```



Converti la chaine de caractère en une adresse IP a point standardisée : xxx.xxx.xxx.xxx

**Retour :** adresse 32-bit binary IPv4 en Network Byte Order (octet de gauche a droite) ou INADDR_NONE si erreur.



## Core Function

Focntions pour ecrire un client et serveur TCP




### :white_small_square: socket()

```C
#include <sys/types.h>
#include <sys/socket.h>

int socket (int family, int type, int protocol);
```


**Retour :** socket descriptor ou -1 si erreur


**Paramètre :**

_Family_ - specifie quel protocole est utilisée


| Family | Descrition |
| --- | --- |
| AF_INET | IPv4 protocoles |
| AF_INET6 | IPv6 protocoles |
| AF_LOCAL | Unix domain protocoles |
| AF_ROUTE | Routing Sockets |
| AF_KEY | Ket socket |


_Type_ - Spécifie quel type de socket on veut

| Type | Descripption |
| --- | --- |
| SOCK_STREAM | Stream socket |
| SOCK_DGRAM | Datagram socket |
| SOCK_SEQPACKET | Sequenced packet socket |
| SOCK_RAW | Raw socket |



_Protocole_ - utiliser un specifiaque protocole en dessous, ou 0 pour selectionner celui par defaut en fonction de la combinaison famille et type

| Protocole | Description |
| --- | --- |
| IPPROTO_TCP | TCP transport protocol |
| IPPROTO_UDP | UDP transport protocol| 
| IPPROTO_SCTP | SCTP transport protocol |




### :white_small_square: connect()


Utilisé par le TCP client pour se connecter au TCP serveur

```C
#include <sys/types.h>
#include <sys/socket.h>

int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
```


**Retour:** 0 si succes, -1 sinon

**Paramètre :**

- sockfd : socket descripteur

- serv_addr : pointeur sur struct sockaddr (IP et port)

- addrlen : sizeof(struct sockaddr)




### :white_small_square: bind()


Donne une address au socket

```C
#include <sys/types.h>
#include <sys/socket.h>

int bind(int sockfd, struct sockaddr *my_addr,int addrlen);
```



**Retour:** 0 si succes, sinon -1

**Parameters:**

- sockfd : socket descripteur

- my_addr : pointeur sur sockaddr (IP et port)

- addrlen : sizeof(struct sockaddr)



Si le port = 0, le système a donc choisi un port aleatoire et INADDR_ANY est set sur l'IP (=> assignement aleatoire adresse IP)

```C
server.sin_port = 0;  		     
server.sin_addr.s_addr = INADDR_ANY;
```




### :white_small_square: listen()


2 actions :
- converti le socket deconnecté en socket passif, le kernel doit donc acepter la prochane demande de connexion sur ce socket
- le second argument de la fonction specifie le nombre max de connection le kernel doit aligner sur ce socket



```C
#include <sys/types.h>
#include <sys/socket.h>

int listen(int sockfd,int backlog);
```

**Retour:** 0 si succes -1 sinon

**Parametres:** 
- sockfd : socket descripteur 
- backlog : nbr de connexion autorisée




### :white_small_square: accept()


Appelé par le server TCP, accepte la prochaine connexion dans la queue.

```C
#include <sys/types.h>
#include <sys/socket.h>

int accept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
```

**Retour:** positif descripteur si succes ou -1. Ce descripteur = socket descripteur du client vers lequel chaque operation ecriture-lecture seront opérées.

**Parameteres:**
- sockfd : socket descripteur 
- cliaddr : pointeur vers la struct sockaddr (IP + port)
- addrlen : sizeof(struct sockaddr)




### :white_small_square: send()


Utiliser pour envoyer des données a travers le stream socket. On peut aussi utiliser write() pour ecrire/envoyer 

```C
int send(int sockfd, const void *msg, int len, int flags);
```

**Retour:** le nombre d'0ctet envoyé ou -1

**Parametre:**
- sockfd : socket descripteur 
- msg : pointeur vers le msg qu'on veut envoyer
- len : taille du message
- flags : mis a 0




### :white_small_square: recv()


Utlisée pour recevoir les données. On peut utiliser read() pour lire/recevoir les données

```C
int recv(int sockfd, void *buf, int len, unsigned int flags);
```

**Retour:** nombre d'octet lu dans le buffer ou -1.

**Parametres:** 
- sockfd : socket descripteur 
- buf : buffer ou les info seront lu
- len :taille max du buffer
- flags : mis a 0




### :white_small_square: select()


Cette fonction indique quel descripteur de fichier est pret pour la lecture ou l'ecriture ou s'il y a une erreur.

A l'appel de cette fonction, un socket qui n'a pas de requete ne recevra pas immediatement les donnees d'un autre socket.


```
int select(int  nfds, fd_set  *readfds, fd_set  *writefds, fd_set *errorfds, struct timeval *timeout);
```

**Retour:** 0 si succes -1 sinon


https://www.tutorialspoint.com/unix_sockets/socket_helper_functions.htm
cgi info >> https://www.oreilly.com/library/view/cgi-programming-on/9781565921689/07_chapter-04.html
launching cgi with execve >> https://stackoverflow.com/questions/11498031/how-to-call-php-cgi-from-c