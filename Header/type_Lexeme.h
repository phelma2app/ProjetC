#ifndef TYPE_LEXEME_H_
#define TYPE_LEXEME_H_

#define NON_DEFINI 0
#define ARCHITECTURE 	NON_DEFINI+1
#define ARCHITECTURE_BEGIN  ARCHITECTURE+1
#define ARCHITECTURE_END 	ARCHITECTURE_BEGIN+1
#define ARCHITECTURE_ID ARCHITECTURE_END+1
#define COMMENTAIRE 	ARCHITECTURE_ID+1
#define ENTITY 		COMMENTAIRE+1
#define ENTITY_END 	ENTITY+1
#define ENTITY_ID 	ENTITY_END+1
#define LIBRARY 	ENTITY_ID+1
#define LIBRARY_END	LIBRARY+1
#define LIBRARY_ID	LIBRARY_END+1
#define MOT 		LIBRARY_ID+1
#define NOMBRE 		MOT+1
#define PROCESS NOMBRE+1
#define PROCESS_BEGIN   PROCESS+1
#define PROCESS_END PROCESS_BEGIN+1
#define PROCESS_ID  PROCESS_END+1
#define	PONCTUATION 	NOMBRE+1
#define PORT		PONCTUATION+1
#define PORT_END 	PORT+1
#define PORT_ID 	PORT_END+1
#define PORT_ID_END 	PORT_ID+1
#define PORT_IN 	PORT_ID_END+1
#define PORT_INOUT 	PORT_IN+1
#define PORT_OUT 	PORT_INOUT+1
#define PORT_TYPE 	PORT_OUT+1
#define PORT_VECTOR    PORT_TYPE+1
#define PORT_VECTOR_BEGIN  PORT_VECTOR+1
#define PORT_VECTOR_END    PORT_VECTOR_BEGIN+1
#define PORT_VECTOR_SENSE  PORT_VECTOR_END+1
#define SENSIBILITY_SIGNAL  PORT_VECTOR_SENSE+1
#define SIGNAL  SENSIBILITY_SIGNAL+1
#define USE		SIGNAL+1
#define USE_END		USE+1
#define USE_ID		USE_END+1

#endif //TYPE_LEXEME_H_
