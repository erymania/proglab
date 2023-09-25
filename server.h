#ifndef _SERVER_H_
#define _SERVER_H_

#include "myutil.h"
#include "queue.h"
#include "hashtable.h"


/*STRUTTURE DATI*/

// struttura dati argomento worker 
struct arg{
  queue_t *q;
  hashtable_t *hasht;
};

//struttura dati argomento bworker 
struct barg {
 list_t *l;
  queue_t *q;

}

// funzioni che uso nel server 
void intDatiCondivisi( struct DatiCondivisi* dati_condivisi, struct Record record)
void handleRequest(struct DatiCondivisi* dati_condvisi, int client_socket)
void* workerThread(void* arg)
void signalHandler(int signum)
