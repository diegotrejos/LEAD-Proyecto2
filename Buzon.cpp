#include "Buzon.h"

Buzon::Buzon(int tipoMensaje, key_t key)
{
	miBuzon.mType = tipoMensaje;
	this->key = key;
	setMsqid();
}

Buzon::~Buzon()
{
	msgctl(qId,0,IPC_RMID);
}

void Buzon::setMsqid(){
	if ((qId = msgget( key, IPC_CREAT | 0666 )) == -1) {
		perror( "server: Failed to create message queue:" );
		exit(1);
   }
	std::cout << "Mi QID es " << qId << std::endl;
}


void Buzon::setMensaje(char* mensaje){ 	
	strcpy(miBuzon.mText, mensaje);
	std::cout << "Mensaje a enviar: " << mensaje << std::endl;
}

void Buzon::recibir(){
	if (msgrcv(qId, &miBuzon, MAX, 0, 0) == -1)
		perror("client: msgrcv failed:");
   else
		printf("client: Message received = %s\n", miBuzon.mText);
}

void Buzon::enviar(char* mensaje){
	setMensaje(mensaje);
	if (msgsnd(qId, &miBuzon, /*sizeof miBuzon.mText*/MAX, IPC_NOWAIT) == -1){
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
