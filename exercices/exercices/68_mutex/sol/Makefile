

all : run 




# ----------------------------- Test gestion compte bancaire ----------------------------- 
compileTestBanque :

	gcc -Wall -Wextra -g gestionBanque.c -o  bin/gestionBanque


runTestgestionCompte : compileTestBanque 
	./bin/gestionBanque


# ----------------------------- Test RDV --- ----------------------------- 

compileTestRDV :

	gcc -Wall -Wextra -g exo_RDV.c -o  bin/exo_RDV


runTestRDV: compileTestRDV
	./bin/exo_RDV



clean :
	rm -r ./bin/*