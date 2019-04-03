#ifndef BUZON_H
#define BUZON_H
#include <sys/msg.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#define MAX 128

class Buzon{
	public:
		int qId;
		key_t key;
		
		Buzon(int tipoMensaje, key_t key);
		~Buzon(){};

		typedef struct msgbuf{
			int mType;
			char mText[128];
		}buzonMensajes;
		
		buzonMensajes miBuzon;
		struct msqid_ds msgCtlBuf;
		
		void setMensaje(char* mensaje);
		void enviar(char* mensaje);
		void recibir();
		void setMsqid();
		void sacarQueue();
};


#endif // BUZON_H
