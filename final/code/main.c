#include "header.h"

int main (int argc, char **argv){
  FILE *entradas, *aux, *saida;
  char entrada[100], name[20], arq[20];
  int i, count = 0, currentLine = 0, init, divisao;
  char* str;

  omp_set_num_threads(1);

  int rank, size, tag = 0;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if(rank==0){
    system("rm rank* saida.txt");
  }
  MPI_Barrier(MPI_COMM_WORLD);

  entradas = fopen("chaves.txt", "r");
  while(fgets(entrada, sizeof(entrada), entradas) != NULL) {
    count++;
  }
  
  divisao = (int)(count / size);
  if(!divisao){
    divisao++;
  }
  init = rank * divisao;

  if(count < size && rank > count-1){
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
  }

  rewind(entradas);
  #pragma omp parallel for shared(currentLine)
  for (currentLine=0;currentLine<count;currentLine++){
    fscanf(entradas, "%s\n", entrada);
    if(currentLine >= init){
      if(currentLine >= divisao+init && rank != size-1){
        continue;
      }
      for(i = 1; i <= MAX; i++){
        testaSenhas(i, entrada, rank);
        if (flag){
          flag--;
          break;
        }
      }
    }
  }

  MPI_Barrier(MPI_COMM_WORLD);

  if(rank == 0){
    saida = fopen("saida.txt", "a");
    
    for(i=0; i < min(count, size); i++){
      strcpy(name, "rank");
      sprintf(arq, "%d", i);
      strcat(name, arq);
      strcat(name,".txt");
      aux = fopen(name, "r");
      while(fscanf(aux, "%s\n", entrada) != EOF){
        fprintf(saida, "%s\n", entrada);
      }
      fclose(aux);
    }
    fclose(saida);
  }

  fclose(entradas);
  MPI_Finalize();
  return 0;
}

void testaSenhas(int tam, char* entrada, int rank){
  char alfabeto[] = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char salt[] = "Xy";
  char str[100], name[20] = "rank", aux[20];
  int* seq;
  int i, j, n, k;
  char* meuCrypt;
  FILE* saida;
  struct crypt_data cd;

  seq = (int *) calloc( (tam+1), sizeof(int)) ;
  n = strlen(alfabeto);
  while ( seq[tam] == 0 ) { 
    for ( i = 0; i < n; i++ ) {
      for ( j = 0, k = tam-1; j < tam; j++ ) {
        str[k] = alfabeto[seq[j]] ;
        k-- ;
      }

      str[tam] = 0 ;
      meuCrypt = crypt_r(str, salt, &cd);
      
      if(strcmp(meuCrypt, entrada) == 0){
        printf("Sou o %d e achei a senha do %s -------------------> %s\n", rank, entrada, str);
        sprintf(aux, "%d", rank);
        strcat(name, aux);
        strcat(name,".txt");
        saida = fopen(name, "a");
        fprintf(saida, "%s\n", str);
        fclose(saida);
        flag++;
      }
      seq[0]++ ;
    }

    for ( i = 0; i < tam; i++ ) {
      if ( seq[i] == n ) {
        seq[i] = 0 ;
        seq[i+1]++ ;
      }
    }
    if (flag){
      break;
    }
  }
}