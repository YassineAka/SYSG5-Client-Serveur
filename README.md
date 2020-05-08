Le repertoire Client situé dans le repertoire SYSG5-Proj contient les fichier relative à la machine jouant le rôle de client, et vice versa pour le repertoire Serveur.

Coté serveur, le makefile compile le fichier serveur.

La désactivation du firewall et la mise à jour du fichier ~/.bashrc est desormais automatisée.

Les différents appels systèmes sont expliqués juste après le schéma dans le rapport.










REMARQUES :

-J'ai tenté de rendre la demande du nombre de commandes au client interctive notamment grâce à la méthode getLastLinesInHistory qui me permet d'avoir le nombre de commandes totale (dans le cas ou je chargeai tout l'historique sans passer par le read dans un script). Ensuite en ayant le nombre de commandes totale, je demandais interactivement au client le nombre de commandes qu'il voulait . Je faisais ensuite un calcul simple soit le nombre de commandes totale - le nombre de commande voulu par le client ce qui me donnait un nombre "n" . J'avancais ensuite dans le fichier history.txt (ou se trouve l'historique) de n lignes. mais le souci c'est que j'ai une erreur de type segmentation fault. Je suis resté 2h30 devant ce problème sans solution.

-Lors de la connexion d'un client la première commande exécuté ne fonctionne pas toujours

-quand le client entre un nombre de commandes trop grand , la lecture/ecriture coté serveur se passe mal.

-malgré les jours acharchés et les 15h de travail non stop jeudi, je me suis enormément amusé et je ne regrette absolument pas d'avoir choisi les sockets. Etant donné que je n'avais jamais utilisé cela et je ne connaissas que très peu le langage c, j'ai beaucoup appris avec le projet.
