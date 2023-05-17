#include "registro.cc"
typedef struct bloco {
  unsigned long qtdRegistros;
  int id_bloco;
  Registro dados[4096];
} Bloco;
