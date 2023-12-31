#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>
#include <signal.h>
#include <pthread.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <errno.h>
#include "server.h"
#define UNIX_PATH_MAX 256
#include "list.h"
#include "collector.h"

#define MAX_FIELD 10
#define MAX_FIELD_LENGHT 100 
#define MAX_RECORD 100

// definizione della struttura dati per i record

struct Record{
char field_name[MAX_FIELD][MAX_FIELD_LENGTH];
char field_value[MAX_FIELD][MAX_FIELD_LENGTH];
int num_fields;
int prestito: // darà 0 se il volume non è in prestito altrimenti indica la data di scadenza del prestito; 

// creiamo una struttura condivisa per i record dei volumi

struct DatiCondivisi{     // qua definiao la struttura dati principale 
struct Record records[MAX_RECORDS]; // all'interno della struttura c'è un array di strutture chiamato record 
int num_records; // questa tiene traccia dei record presenti memorizzati nella struttura
pthread_mutex_t mutex; // un mutex è un meccanismo di sincronizzazione per getir l'accesso concorrente a risorse condivise da parte di più thread. Con questa possiamo utilizzare questa struttura in un ambiente multithreaded per garantire la sincronizzazione dei record. 


// creiamo una funzione che ci serve per inizializzare la struttura condivisa 
//la funzione accetta due argomenti: un puntatore ad una struttura ed una struttura
void intDatiCondivisi( struct DatiCondivisi* dati_condivisi, struct Record record){ 
pthread_mutex_lock(&(dati_condivisi-> mutex)); // questo è usato per ottenere il blocco esclusivo della mutex quindi se altri thread cercano di acquisire la stessa mutex dovranno attendere 
if(dati_condivisi-> num_records< MAX_RECORDS){  
dati_condivisi->records[dati_condivisi->num_records] = record;
        dati_condivisi->num_records++; // viene incrementato per tenere traccia del nuovo record 
    }
    pthread_mutex_unlock(&(dati_condivisi->mutex)); //sblocca la mutex quindi altri thread possono accederci in modo condiviso 
}


//funzione per gestire la richiesta del client 
void handleRequest(struct DatiCondivisi* dati_condvisi, int client_socket){}


// Funzione eseguita dai thread worker
void* workerThread(void* arg) {
    struct DatiCondivisi* dati_condivisi = (struct DatiCondivisi*)arg;
      int t = ((DatiCondivisi*)arg)->tempo_di_invio;
      llist *l=((DatiCondivisi*)arg)->l;
    int lenght_tail_list=((DatiCondivisi*)arg)->lenght_tail_list;
    char *data;
    }
    
for(int i=0;i<lenght_tail_list; ++i) {
if(termina == 0){ // inserisco tutto tranquillamente   //estraggo una alla volta i data dalla lista e li inserisco in modo concorrente in q
           data=l->opzione;
            //printf("DATA [%d]: %s\n\n",i,data);
            sleep(t/1000);
            if (push(q, data) == -1) {
                fprintf(stderr, "Errore: push\n");
                free(data);
                pthread_exit(NULL);
            }
            //elimino primo elemento dalla lista
            delete_head_lista_piena(&l,data); //libero la lista piano piano
        }
        else{ //è arrivato un segnale come sigint, smetto di inserire i dati e faccio finire quelli che erano in coda
            sleep(1);
            push(q,"STOP");
        }
        //printf("Producer %d pushed <%d>\n", myid, i);
    }
    return NULL;
    }
    
    
    
    
 // Funzione per gestire i segnali SIGINT e SIGTERM
void signalHandler(int signum) {   
        while(1) {
        int sig;
        int r = sigwait(set, &sig);
        if (r != 0) {
            errno = r;
            perror("FATAL ERROR 'sigwait'");
            return NULL;
        }

        switch(sig) {
            case SIGINT:
            case SIGTERM:
           default:
                return NULL;
        }
    }
    return NULL;

}


    // main 
    
    
    int main(int argc, char* argv[]) {
 FILE* fp;
    char record_str[MAX_FIELD_LENGTH];
    struct Record record;

    // Apriamo il file record.txt in lettura
    fp = fopen("record.txt", "r");
    if (fp == NULL) {
        printf("Impossibile aprire il file record.txt\n");
        return 1;
    }

    // Leggiamo il file riga per riga e analizziamo i record
    while (fgets(record_str, MAX_FIELD_LENGTH, fp) != NULL) {
        // Rimuoviamo il carattere di newline alla fine del record
        size_t len = strlen(record_str);
        if (len > 0 && record_str[len - 1] == '\n') {
            record_str[len - 1] = '\0';
        }

        // Analizziamo il record e otteniamo la struttura "Record"
        record = parseRecord(record_str);
        
    
    // codice server(?)
