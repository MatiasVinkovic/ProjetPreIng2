# ProjetPreIng2

CECI EST LE MANUEL OFFICIEL DE NOTRE PROJET CY-TRUCKS
(toute recréation de ce projet sans notre marque n'est pas notre création et nous n'y sommes pas associés)

Bienvenue dans le projet de Ahmed, Timothée, et Matias, 3 bogoss.

Ce projet vous permettra de traiter le fichier data.csv d'une manière que vous n'avez jamais vue auparavant. Nous avons 5 options principales parmi lesquelles vous pouvez choisir : option -d1, -d2, -l, -t et -s.

Vous aurez besoin de télécharger les packages suivant : 
            - imagemagick (sudo apt install imagemagick)
            - gnuplot (sudo apt install gnuplot)            

voici les fonctionnalités de chaque fonction :

  “option -d1” : Après l’exécution de cette fonction, vous obtiendrez un graphe avec les conducteurs avec le plus de trajets.
  "option -d2” : Après l’exécution de cette fonction, vous obtiendrez un graphe avec les conducteurs avec les distances les plus parcourues. 
  “option -l” : Après l’exécution de cette fonction, vous obtiendrez un graphe qui affiche les 10 trajets les plus longs.
  “option -t” : Après l’exécution de cette fonction, vous obtiendrez un graphe affichant les 10 villes les plus traversées.
  “option -s” : Après l’exécution de cette fonction, vous obtiendrez un graphe affichant les distances minimales, maximales et moyennes des étapes, et ce, pour chaque trajet. 

Vous vous demandez probablement “que doit-je entrer sur le terminal pour obtenir ces résultats?”. Voici la commande à écrire dans votre terminal pour lancer le programme (ne pas oublier bien se placer dans le dossier qui contient le fichier script.sh en utilisant la commande cd etc...) : 

bash script.sh data.csv -d1 -d2 -l -s -t   (WARNING : cette commande ne marche que pour un fichier .csv)

P.S. : Vous avez la liberté d'exécuter les commandes individuellement selon vos besoins. Pour ce faire, utilisez la syntaxe suivante : "bash script.sh data.csv [...]" en spécifiant les options souhaitées.

Une fois la commande exécutée, un dossier nommé "images" sera automatiquement créé, contenant tous les graphiques générés. Il vous suffira ensuite d'ouvrir ce dossier pour visualiser les graphiques selon vos besoins.

Nous vous souhaitons un bon moment avec notre projet et nous vous remercions d'avoir pris le temps de lire ceci.

XOXO


Voici les temps observées sur le pc de l'école, salle 309 cauchy : 
d1 -> 6 secondes (parfois 8 lors du premier lancement)
d2 -> 3 secondes 
l -> 7 secondes
s -> 11 secondes
t -> 27 secondes
(cf dossier demo)

XOXO n°2
