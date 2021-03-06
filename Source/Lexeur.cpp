#include "../Header/Lexeur.h"

using namespace std;

//Permet d'ouvrir un fichier VHDL et d'en découper les differents lexemes
bool vhdlcomp(string libraryname, string sourcename, list<Lexeme*>& list_lex)
{
	//Ouverture du fichier
	ifstream fichier(sourcename.c_str(), ios::in);  // on ouvre en lecture
	if(!fichier)  // si l'ouverture n'a pas fonctionnee
	{
		cerr << "Impossible d'ouvrir le fichier " << sourcename << " !" << endl;
		return true;
	}

	//Traitement du fichier
	int n_ligne=1;
	do
	{
		string buffer ="";
		buffer = read_line(fichier);	//on lit une ligne en y ajoutant des espaces
		//cout << "Stock_Lexeme : ligne n" << n_ligne << endl;  //pour test
		if(stock_lexemes(buffer,n_ligne,list_lex))		//on stocke
        {
            cerr << "!!Mot mal orthographie ligne " << n_ligne << "!!" << endl;
            return true;
        }
		n_ligne++;
	}while(!fichier.eof());

	Lexeme* endFile = new Lexeme("\0",n_ligne,END_OF_FILE); //Lexeme special pour detecter la fin du fichier
	list_lex.push_back(endFile);

    //Affichage
    cout << "-- Lexemes separes--" << endl;
	print_lex(list_lex);

	//cout << endl <<  "Nombre de lignes dans le fichier : " << n_ligne-1 << endl;		//pour test
	return false;
}

//Permet d'afficher une liste entière de Lexemes
void print_lex(const list<Lexeme*>& list_lex)
{
	list<Lexeme*>::iterator itr;
	for(itr=list_lex.begin();itr!=list_lex.end();itr++)
	{
		cout << **itr;
	}
}

//Fonction pour stocker chaque lexeme d'une ligne dans une liste, avec leur numero de ligne
//Pre-condition : les lexemes doivent etre separes avec des espaces
bool stock_lexemes(string buffer, int ligne, list<Lexeme*>& Lex_VHDL)
{
	char* ch_buff;	//Buffer
	ch_buff = strtok(&buffer[0]," ");       //Selection du 1er Lexeme
	int ligne_com=0;
	bool is_com=false;
	while(ch_buff!=NULL||ch_buff!='\0')
	{
		//cout << "." << ch_buff << "." << endl;	//pour test
		Lexeme *lex_buff = new Lexeme(ch_buff,ligne,0);

		if(verif(*lex_buff,&is_com,&ligne_com))     //Verification orthographique de chaque Lexeme
        {
 			cout << "Erreur lexicale detectee" << endl;
			return true;
        }

		Lex_VHDL.push_back(lex_buff);   //Stockage du lexeme verifie
		ch_buff = strtok(NULL," ");     //Selection du lexeme suivant
	}

	return false;
}

//Fonction pour lire une ligne dans un fichier et lui ajouter des espaces entre les caracteres
//Retourne la ligne lue et formatee
string read_line(ifstream& fichier)
{
	//Recuperation de la ligne
	string buffer="";
	getline(fichier, buffer);	//traitement d'une ligne a chaque boucle
	buffer+="\n"; //on rajoute un espace pour bien etre sur de separer la fin de la ligne du debut de la ligne suivante
	//cout << buffer << endl;	//pour test

	//Reformatage de la ligne
	minus_string(buffer);		//Caracteres passes en minuscule

	return add_space_on_string(buffer, buffer.length());
}

//Fonction pour ajouter des espaces sur un string
//Retourne un nouveau string reformate
string add_space_on_string(string str, int length)
{
	int i=0;		//increment pour str
	char temp[length*2];	//pour la recopie : dans le pire cas, on ajoute un espace entre chaque caractere, donc length*2
	int j=0;		//increment pour temp

	while(str[i]!='\0')	//boucle tant qu'on n'est pas arrive a la fin du string
	{
		if(str[i]=='	'||str[i]=='\n')	// la tabulation et le saut de ligne sont traites comme un espace "classique"
		{
			str[i]=' ';
		}

		if(j==0)	// Premier caractere recopie : le premier caractere non-espace
		{
			if(!(str[i]==' '))
			{
				temp[j]=str[i];
				j++;

				if(is_ponctuation2char(str[i],str[i+1]))	//Si le lexeme est une ponctuation a 2 chars : on recopie le 2e caractere
				{
					i++;
					temp[j]=str[i];
					j++;
				}

				if(is_ponctuation(str[i])&&(str[i+1]!=' '))	//Si ponctuation & pas d'espace apres : on rajoute un espace si on est pas Ã  la fin de la chaÃ®ne
				{
					if(str[i+1]!='\0')
					{
						temp[j]=' ';
						j++;
					}
				}
			}
		}
		else		// Caracteres suivants
		{
			if(is_ponctuation(str[i]))	//si ponctuation
			{
				//Recopie du premier caractere

				if(temp[j-1]==' ')	//si on a recopie un espace auparavent, on ne recopie que la ponctuation
				{
					temp[j]=str[i];
					j++;
				}
				else			//sinon, on ajoute un espace avant
				{
					temp[j]=' ';
					j++;
					temp[j]=str[i];
					j++;
				}

				//Tests : rajouter un espace ? Recopier un deuxieme caractere ?

				if(is_ponctuation2char(str[i], str[i+1]))	//si les 2 ponctuations qui se suivent sont une affectation ou un commentaire, on recopie directement le caractere suivant
				{
					i++;		//caractere suivant
					temp[j]=str[i]; //on recopie
					j++;
				}

				if((str[i+1]!=' ')&&(str[i+1]!='\0')) // si le caractere suivant le lexeme n'est pas un espace ou une fin de chaine, on en rajoute un
				{
					cout << "On rajoute un espace" << endl;
					temp[j]=' ';
					j++;
				}
			}
			else	//si pas ponctuation
			{
			    //si on a deja  stocke un espace precedemment, on ne rentre pas dans le if
				if(!(str[i]==' '&&temp[j-1]==' '))	//dans tous les autres cas, on recopie
				{
					temp[j]=str[i];
					j++;
				}
			}
		}
		i++;	//on passe a la recopie du caractere suivant
	}
	temp[j]='\0';	//sortie de la boucle = fin de chaine, on le signale dans temp

	//cout << "Chaine stockee :" << temp << endl;		//Pour le test
	str = temp;
	return str;
}
