MAKEFILE
CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: server bibaccess

server: server.c
	$(CC) $(CFLAGS) -o server server.c

bibaccess: bibaccess.c
	$(CC) $(CFLAGS) -o bibaccess bibaccess.c
l
clean:
	rm -f server bibaccess

test: all
	# Lancio dei 5 server con database diversi e numero variabile di thread worker
	for w in 1 2 3 4 5; do \
		./server name_bib$$w bib$$w.txt $$w & \
	done
	sleep 1

	# Lancio dei client in gruppi di 5, con un'attesa di 1 secondo fra ogni gruppo
	for i in {1..40}; do \
		./client & \
		if (( $$i % 5 == 0 )); then \
			sleep 1; \
		fi \
	done

	sleep 1

	# Invio SIGINT al server
	pkill -SIGINT server

	# Attesa di 10 secondi prima di lanciare lo script bibaccess sui file di log
	sleep 10

	# Esecuzione dello script bibaccess sui file di log
	./bibaccess --query name_bib1.log name_bib2.log name_bib3.log name_bib4.log name_bib5.log
	./bibaccess --loan name_bib1.log name_bib2.log name_bib3.log name_bib4.log name_bib5.log

Salva questo codice in un file chiamato makefile (senza estensione) nella stessa directory dei tuoi sorgenti del server, del client e dello script bibaccess.c.

Il makefile ha quattro target: all, server, bibaccess, e clean. Il target test è stato aggiunto per eseguire il ciclo completo di test come descritto.






