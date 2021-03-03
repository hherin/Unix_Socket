# UNIX_SOCKETT

Premiers pas vers la programmation Unix Socket.

[Tutoriel](https://www.tutorialspoint.com/unix_sockets/index.htm)


### Definition

Les sockets permettent la **communication entre deux processus** sur une ou plusieurs machines



2 des 4 types dont on va s'interesser:
- _Stream sockets_ : ils utilisent le protocole TCP pour le transport des données. La livraison est toujours garantie.
- _Datagram sockets_ : ils utilisent le protocole UDP. Il n'y a pas de connexion eentre le serveur et le client et la livraison n'est pas garantie.




## Comment créer un process client

- le client envoie une requete dans l'attente d'un retour du serveur.

    :heavy_check_mark: Créer un socket via le system call **socket()**

    :heavy_check_mark: Connecter le socket a l'adresse du serveur via **connect()**

    :heavy_check_mark: Envoyer la requête et recevoir les donner avec **read() write**




## Comment créer un process serveur

- Le serveur recoit la requête du client, la traite puis rassemble toutes les informations. Envoie ces derniers au clients et enfin se rend disponible pour une nouvelle requête a traiter.

    :heavy_check_mark: Créer un socket via le system call **socket()**

    :heavy_check_mark: Lie le socket a une adresse : **bind()**. Dans le cas d'un socket serveur sur internet, l'adresse correspond au port de la machine hôte.

    :heavy_check_mark: Se met sur écoute pour une nouvelle connexion : **listen()**

    :heavy_check_mark: Accepte la connexion : **accept()**. le serveur est bloqué a cette étape tant que la connexion avec un client n'est pas faite.

    :heavy_check_mark: Envoie et recooid les données via les system call **read() write**



Diagram des interactions Client-Serveur

![alt text](https://www.tutorialspoint.com/unix_sockets/images/socket_client_server.gif)



## Acces aux infos d'adressage et port

Diverses structures seront utilisées.

#### sockaddr - infos du socket

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