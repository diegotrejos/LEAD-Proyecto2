#include "Buzon.h"

Buzon::Buzon(key_t key)
{
	this->key = key;
	setMsqid();
}

/*Buzon::~Buzon()
{
	msgctl(qId,0,IPC_RMID);
}*/

void Buzon::setMsqid(){
	if ((qId = msgget( key, IPC_CREAT | 0666 )) == -1) {
		perror( "server: Failed to create message queue:" );
		exit(1);
   }
	std::cout << "Mi QID es " << qId << std::endl;
}


void Buzon::setMensaje(char* mensaje){ 	
	size_t size = strlen(mensaje);
	memcpy(miBuzon.mText, mensaje, size);
	std::cout << "Mensaje a enviar: \n" << mensaje << "\nAdemas el tamaño del paq es: " << size << std::endl;
}

int Buzon::recibir(){
	int size = msgrcv(qId, &miBuzon, sizeof (miBuzon.mText), 0, 0) ;
	if (size == -1)
		perror("client: msgrcv failed:");
	else
		printf("client: Message received = %s\n", miBuzon.mText);	
	return size;
}

void Buzon::enviar(char* mensaje, long tipoMensaje){
	setMensaje(mensaje);
	miBuzon.mType = tipoMensaje;
	if (msgsnd(qId, &miBuzon, sizeof (miBuzon.mText), IPC_NOWAIT) == -1){
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
