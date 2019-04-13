#include "Buzon.h"

Buzon::Buzon(key_t key)
{
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
	//std::cout << "Mi QID es " << qId << std::endl;
}


void Buzon::setMensaje(char* mensaje, int tamanoMensaje){ 	
	memcpy(miBuzon.mText, mensaje, tamanoMensaje);
	//std::cout << "Mensaje a enviar: \n" << mensaje << "\n
	//std::cout << "Ademas el tamaño del paq es: " << tamanoMensaje << std::endl;
}

void Buzon::recibir(long tipoMensaje){
	int size = msgrcv(qId, &miBuzon, sizeof (miBuzon.mText) + sizeof (int) + sizeof (long) + sizeof (char), tipoMensaje, 0);
	//int mensajeUtilBuzon = miBuzon.mensajeUtil;
	if (size == -1)
		perror("client: msgrcv failed:");
	else{
		//printf("client: Message received = %s\n", miBuzon.mText);
		//printf("Mensaje util = %d\n", mensajeUtilBuzon);	
	}
		
	
}

void Buzon::enviar(char* mensaje, long tipoMensaje, int tamanoMensaje){
	setMensaje(mensaje, tamanoMensaje);
	miBuzon.mType = tipoMensaje;
	miBuzon.mensajeUtil = tamanoMensaje;
	if (msgsnd(qId, &miBuzon, sizeof (miBuzon.mText) + sizeof (int) + sizeof (long) + sizeof (char), 0) == -1){
		perror("server: msgsnd failed:");
		exit(2);
   }else{
	   //std::cout << "Mensaje enviado" << std::endl;
   }
}

void Buzon::sacarQueue(){
	if (msgctl( qId, IPC_RMID, &msgCtlBuf ) == -1) {
		perror( "server: msgctl failed:" );
		exit(3);
   }
}
