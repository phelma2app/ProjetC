#ifndef LEXEUR_H_
#define LEXEUR_H_

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"
#include "Lexeme.h"
#include "Verification_orthographe_ajout_etiquette.h"

using namespace std;

string read_line(ifstream& fichier);
string add_space_on_string(string str, int length);
void stock_lexemes(string buffer, int ligne, list<Lexeme*>& Lex_VHDL);
int vhdlcomp(string libraryname, string sourcename, list<Lexeme*>& list_lex);

#endif //LEXEUR_H_
