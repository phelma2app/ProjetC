#ifndef TYPE_LEXEME_H_
#define TYPE_LEXEME_H_

#define NON_DEFINI 0
#define AFFECTATION_END		NON_DEFINI+1
#define AFFECTATION_MAP		AFFECTATION_END+1
#define AFFECTATION_SIGNAL	AFFECTATION_MAP+1
#define AFFECTATION_VARIABLE	AFFECTATION_SIGNAL+1
#define ARCHITECTURE 		AFFECTATION_VARIABLE+1
#define ARCHITECTURE_BEGIN  	ARCHITECTURE+1
#define ARCHITECTURE_END 	ARCHITECTURE_BEGIN+1
#define ARCHITECTURE_ID 	ARCHITECTURE_END+1
#define ATTRIBUT		ARCHITECTURE_ID+1
#define ATTRIBUT_ID		ATTRIBUT+1
#define COMMENTAIRE 		ATTRIBUT_ID+1
#define COMPONENT		COMMENTAIRE+1
#define COMPONENT_END		COMPONENT+1
#define COMPONENT_ID		COMPONENT_END+1
#define CONDITION_LOGIC		COMPONENT_ID+1
#define CONDITION_SCALAR	CONDITION_LOGIC+1
#define ELSE			CONDITION_SCALAR+1
#define ELSIF			ELSE+1
#define END_OF_FILE		ELSIF+1
#define ENTITY 			END_OF_FILE+1
#define ENTITY_END 		ENTITY+1
#define ENTITY_ID 		ENTITY_END+1
#define GENERIC			ENTITY_ID+1
#define GENERIC_END		GENERIC+1
#define GENERIC_ID		GENERIC_END+1
#define GENERIC_ID_END		GENERIC_ID+1
#define GENERIC_TYPE		GENERIC_ID_END+1
#define IF			GENERIC_TYPE+1
#define IF_END			IF+1
#define IF_PARENTHESE_FER	IF_END+1
#define IF_PARENTHESE_OUV	IF_PARENTHESE_FER+1
#define LIBRARY 		IF_PARENTHESE_OUV+1
#define LIBRARY_END		LIBRARY+1
#define LIBRARY_ID		LIBRARY_END+1
#define MAP			LIBRARY_ID+1
#define MAP_END			MAP+1
#define MOT 			MAP_END+1			
#define NOMBRE 			MOT+1
#define OPERATOR_AFF		NOMBRE+1
#define OPERATOR_IF		OPERATOR_AFF+1
#define OPERATOR_SOURCE		OPERATOR_IF+1
#define PACKAGE			OPERATOR_SOURCE+1
#define PACKAGE_END		PACKAGE+1
#define PACKAGE_ID		PACKAGE_END+1
#define PROCESS			PACKAGE_ID+1
#define PROCESS_BEGIN   	PROCESS+1
#define PROCESS_END 		PROCESS_BEGIN+1
#define PROCESS_ID  		PROCESS_END+1
#define PROCESS_SENSIBILITY	PROCESS_ID+1
#define	PONCTUATION 		PROCESS_SENSIBILITY+1	
#define PORT			PONCTUATION+1
#define PORT_END 		PORT+1
#define PORT_ID 		PORT_END+1
#define PORT_ID_END 		PORT_ID+1
#define PORT_IN 		PORT_ID_END+1
#define PORT_INOUT 		PORT_IN+1
#define PORT_OUT 		PORT_INOUT+1
#define PORT_TYPE 		PORT_OUT+1
#define SIGNAL  		PORT_TYPE+1
#define SIGNAL_END    		SIGNAL+1
#define SIGNAL_ID		SIGNAL_END+1
#define SIGNAL_TYPE		SIGNAL_ID+1
#define THEN			SIGNAL_TYPE+1
#define TYPE_DECLARE		THEN+1
#define TYPE_DECLARE_END	TYPE_DECLARE+1
#define TYPE_DECLARE_ID		TYPE_DECLARE_END+1
#define TYPE_DECLARE_VAL	TYPE_DECLARE_ID+1
#define TYPE_VECTOR    		TYPE_DECLARE_VAL+1
#define TYPE_VECTOR_BEGIN  	TYPE_VECTOR+1
#define TYPE_VECTOR_END    	TYPE_VECTOR_BEGIN+1
#define TYPE_VECTOR_SENSE  	TYPE_VECTOR_END+1
#define USE			TYPE_VECTOR_SENSE+1
#define USE_END			USE+1
#define USE_ID			USE_END+1
#define VARIABLE		USE_ID+1
#define VARIABLE_END		VARIABLE+1
#define VARIABLE_ID		VARIABLE_END+1
#define VARIABLE_TYPE		VARIABLE_ID+1

#endif //TYPE_LEXEME_H_
