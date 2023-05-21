#include "registro.h"
#include <vector>


Registro _standard;
typedef struct bloco {
  unsigned long qtdRegistros = 0;
  Registro regs[650];
} Bloco;
