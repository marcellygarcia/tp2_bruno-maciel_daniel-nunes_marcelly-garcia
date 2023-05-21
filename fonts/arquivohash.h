#include <iostream>
#include <fstream>
#include "registro.h"
using namespace std;

bool cria_arquivo();
bool insere_no_arquivo(string filePath);
//Imprime os registros gravados no arquivo de dados
void le_arquivo ();
void findrec (unsigned long kid);