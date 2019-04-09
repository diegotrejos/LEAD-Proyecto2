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
		
		Buzon(key_t key);
		//~Buzon();

		typedef struct msgbuf{
			long mType;
			char mText[MAX];
			char tag;
			int mensajeUtil;
		}buzonMensajes;
		
		buzonMensajes miBuzon;
		struct msqid_ds msgCtlBuf;
		
		void setMensaje(char* mensaje, int tamanoMensaje);
		void enviar(char* mensaje, long tipoMensaje, int tamanoMensaje);
		int recibir();
		void setMsqid();
		void sacarQueue();
};


#endif // BUZON_H
