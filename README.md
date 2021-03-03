# UNIX_SOCKETT

Premiers pas vers la programmation Unix Socket.

[TUTORIEL](https://www.tutorialspoint.com/unix_sockets/index.htm)


### Definition

Les sockets permettent la **communication entre deux processus** sur une ou plusieurs machines



2 des 4 types dont on va s'interesser:
- _Stream sockets_ : ils utilisent le protocole TCP pour le transport des données. La livraison est toujours garantie.
- _Datagram sockets_ : ils utilisent le protocole UDP. Il n'y a pas de connexion eentre le serveur et le client et la livraison n'est pas garantie.




## :white_circle: Comment créer un process client

- le client envoie une requete dans l'attente d'un retour du serveur.

    :heavy_check_mark: Créer un socket via le system call **socket()**

    :heavy_check_mark: Connecter le socket a l'adresse du serveur via **connect()**

    :heavy_check_mark: Envoyer la requête et recevoir les donner avec **read() write**




## :white_circle: Comment créer un process serveur

- Le serveur recoit la requête du client, la traite puis rassemble toutes les informations. Envoie ces derniers au clients et enfin se rend disponible pour une nouvelle requête a traiter.

    :heavy_check_mark: Créer un socket via le system call **socket()**

    :heavy_check_mark: Lie le socket a une adresse : **bind()**. Dans le cas d'un socket serveur sur internet, l'adresse correspond au port de la machine hôte.

    :heavy_check_mark: Se met sur écoute pour une nouvelle connexion : **listen()**

    :heavy_check_mark: Accepte la connexion : **accept()**. le serveur est bloqué a cette étape tant que la connexion avec un client n'est pas faite.

    :heavy_check_mark: Envoie et recooid les données via les system call **read() write**



Diagram des interactions Client-Serveur

![alt text](https://www.tutorialspoint.com/unix_sockets/images/socket_client_server.gif)



## :white_circle: Acces aux infos d'adressage et port

Diverses structures seront utilisées.

### :white_small_square: sockaddr - infos du socket

```
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


```
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


```
struct in_addr {
   unsigned long s_addr;
};
```



| Attribute | Values | Description |
| --- | --- | ---| 
| s_addr | service port | A 32-bit IP address in Network Byte Order. |



### :white_small_square: hostent - Garde les infos de l'hôte.


```
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



```
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



## :white_circle: Ports et Services

Quand un processus client cherche a se connecter au serveur, il doit avoir un moyen d'identifier celui-ci. 

Meme si le client connait l'adresse ip du serveur, il doit aussi avoir connaissance du port.

L'assignement des ports se situe dans le fichier /etc/services. => checker que le port ne soit pas assigné a un autre serveur.

[Plus de detail ici](https://www.tutorialspoint.com/unix_sockets/ports_and_services.htm)



## :white_circle: Fonction manipulation adresse IP

```
inet_addr(const char *strptr);
```



Converti la chaine de caractère en une adresse IP a point standardisée : xxx.xxx.xxx.xxx

**Retour :** adresse 32-bit binary IPv4 en Network Byte Order (octet de gauche a droite) ou INADDR_NONE si erreur.



## :white_circle: Core Function

Focntions pour ecrire un client et serveur TCP


### socket()

```
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




### connect()

Utilisé par le TCP client pour se connecter au TCP serveur

```
#include <sys/types.h>
#include <sys/socket.h>

int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
```


**Retour:** 0 si succes, -1 sinon

**Paramètre :**

- sockfd : socket descripteur

- serv_addr : pointeur sur struct sockaddr (IP et port)

- addrlen : sizeof(struct sockaddr)


### bind()

Donne une address au socket

```
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

```
server.sin_port = 0;  		     
server.sin_addr.s_addr = INADDR_ANY;
```


### listen()

https://www.tutorialspoint.com/unix_sockets/socket_core_functions.htm