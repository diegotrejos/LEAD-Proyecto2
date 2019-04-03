#include "Buzon.h"

Buzon::Buzon(int tipoMensaje, key_t key)
{
	miBuzon.mType = tipoMensaje;
	this->key = key;
	setMsqid();
}

void Buzon::setMsqid(){
	
	if (qId = (msgget( key, IPC_CREAT | 0666 )) == -1) {
      perror( "server: Failed to create message queue:" );
      exit(1);
   }
}


void Buzon::setMensaje(char* mensaje){ 	
	strcpy(miBuzon.mText, mensaje);
}

void Buzon::recibir(){
	std::cout << "Mi QID es " << qId << std::endl;
	if (msgrcv(qId, &miBuzon, sizeof miBuzon.mText, 1, 0 ) == -1)
      perror("client: msgrcv failed:");
   else
      printf("client: Message received = %s\n", miBuzon.mText);
}

void Buzon::enviar(char* mensaje){
	std::cout << "Mi QID es " << qId << std::endl;
	setMensaje(mensaje);
	if (msgsnd(qId, &miBuzon, sizeof miBuzon.mText, 0) == -1){
      perror("server: msgsnd failed:");
      exit(2);
   }else{
	   std::cout << "Mensaje enviado" << std::endl;
   }
}

void Buzon::sacarQueue(){
	if (msgctl( qId, IPC_RMID, &msgCtlBuf ) == -1) {
      perror( "server: msgctl failed:" );
      exit(3);
   }
}
