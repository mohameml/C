# Exercice 65 : 

## Énoncé de l'exercice :

**Mini-Shell avec Redirections**

Écrire un mini-shell simple capable d'exécuter la commande suivante :

```
cat < toto.txt | wc -l > tit.txt
```

Le mini-shell doit interpréter cette commande et la traiter correctement en utilisant des tubes (`|`) et des redirections (`<`, `>`). Voici les détails spécifiques à implémenter :

1. Le mini-shell doit prendre en charge la commande `cat < toto.txt` qui lit le contenu du fichier `toto.txt` et le transmet à la commande suivante via un tube.

2. La commande `wc -l` doit compter le nombre de lignes dans l'entrée qu'elle reçoit via le tube.

3. Le résultat de `wc -l` doit être redirigé vers le fichier `tit.txt`.

Le mini-shell doit être capable d'exécuter cette séquence de commandes en interne, en utilisant les appels système appropriés pour la gestion des tubes et des redirections.

# Indices :

- Utilisez les appels système tels que `fork`, `exec`, `pipe` et `dup2` pour créer et gérer les processus, les tubes et les redirections.
- Assurez-vous de gérer correctement la création, l'exécution et la fermeture des processus pour éviter des fuites de ressources.
- Prenez en compte les erreurs potentielles lors de l'exécution des commandes et signalez-les de manière appropriée.

- **la commande ``wc -l``:**

    - La commande `wc -l` compte le nombre de lignes dans une entrée donnée. 
    
    - Son fonctionnement dépend de la façon dont vous lui fournissez l'entrée. Voici quelques scénarios :

        1. **Sans Argument :**
        ```bash
        wc -l
        ```
        Dans ce cas, `wc -l` attend de l'entrée standard (stdin). Vous pouvez entrer des lignes manuellement, et lorsque vous appuyez sur Ctrl+D pour indiquer la fin de l'entrée, il affiche le nombre de lignes.

        2. **Avec un Fichier en Argument :**
        ```bash
        wc -l fichier.txt
        ```
        Ici, `wc -l` lit le contenu du fichier spécifié (`fichier.txt`) et affiche le nombre de lignes.

        3. **Via un Tube (`|`) :**
        ```bash
        cat fichier.txt | wc -l
        ```
        Dans ce cas, `cat` lit le contenu du fichier (`fichier.txt`) et le transmet à l'entrée standard de `wc -l` via un tube. `wc -l` compte ensuite le nombre de lignes dans cet input.

        4. **Redirection de Fichier :**
        ```bash
        wc -l < fichier.txt
        ```
        Ici, la redirection `<` fournit le contenu du fichier (`fichier.txt`) à l'entrée standard de `wc -l`. Il compte ensuite le nombre de lignes dans cet input.
