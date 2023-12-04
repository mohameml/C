# Énoncé de l'exercice : Gestion de dépôts et retraits d'un compte bancaire en multi-threading



**Contexte :**

Vous êtes en charge du développement d'une application de gestion bancaire concurrente en utilisant la programmation multi-threading. L'objectif est de simuler les opérations de dépôt et de retrait sur un compte bancaire.

**Description :**

1. **Compte bancaire :**
   - Le compte bancaire a un solde initial de 0.
   - Les opérations de dépôt et de retrait doivent être effectuées de manière à éviter les conflits de données lorsqu'elles sont effectuées simultanément par plusieurs threads.

2. **Opérations :**
   - **Dépôt :** Un thread doit pouvoir déposer une certaine somme d'argent sur le compte bancaire.
   - **Retrait :** Un thread doit pouvoir retirer une certaine somme d'argent du compte bancaire.

3. **Contraintes :**
   - Un retrait ne peut être effectué que si le solde du compte le permet.
   - Les opérations de dépôt et de retrait doivent être effectuées de manière atomique pour éviter les problèmes de concurrence.



