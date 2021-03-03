# UNIX_SOCKETT

Premiers pas vers la programmation Unix Socket.

[Tutoriel](https://www.tutorialspoint.com/unix_sockets/index.htm)


### Definition

Les sockets permettent la **communication entre deux processus** sur une ou plusieurs machines



2 des 4 types dont on va s'interesser:
- _Stream sockets_ : ils utilisent le protocole TCP pour le transport des données. La livraison est toujours garantie.
- _Datagram sockets_ : ils utilisent le protocole UDP. Il n'y a pas de connexion eentre le serveur et le client et la livraison n'est pas garantie.




### Comment créer un process client

- le client envoie une requete dans l'attente d'un retour du serveur.

    :arrow_forward: Créer un socket via le system call **socket()**


    :arrow_forward: Connecter le socket a l'adresse du serveur via **connect()**


    :arrow_forward: Envoyer la requête et recevoir les donner avec **read() write**




### Comment créer un process serveur

- Le serveur recoit la requête du client, la traite puis rassemble toutes les informations. Envoie ces derniers au clients et enfin se rend disponible pour une nouvelle requête a traiter.

    :arrow_forward: Créer un socket via le system call **socket()**


    :arrow_forward: Lie le socket a une adresse : **bind()**. Dans le cas d'un socket serveur sur internet, l'adresse correspond au port de la machine hôte.


    :arrow_forward: Se met sur écoute pour une nouvelle connexion : **listen()**


    :arrow_forward: Accepte la connexion : **accept()**. le serveur est bloqué a cette étape tant que la connexion avec un client n'est pas faite.

    
    :arrow_forward: Envoie et recooid les données via les system call **read() write**



Diagram des interactions Client-Serveur

![alt text](https://www.tutorialspoint.com/unix_sockets/images/socket_client_server.gif)