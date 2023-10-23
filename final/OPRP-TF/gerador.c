#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MAX 8
#define MAX_SALT 1
#define MAX_PROB 15
#define MAX_ALFABETO 64

int main(int argc, char *argv[])
{
	char w[] = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char *salt[] = {"Xy"};
	char password[MAX+1];
	char *pwd;
	int numPalavras;
	int i, j;
	char c;
    FILE *senhas;
    FILE *chaves;
    int size;
    int sizes[] = {1, 1, 2, 2, 2, 3, 3, 3, 1, 2, 3, 1, 2, 3, 3}; //chaves podem ser até 

	int s = 0;

    if (argc != 2) {
        printf("Deve informar %s e o numero de palavras que devem ser geradas\n", argv[0]);
        exit(1);
    }

	numPalavras = atoi(argv[1]);
	
	srand(time(NULL));

    senhas = fopen("senhas.txt", "w");
    chaves = fopen("chaves.txt", "w");

	for (i = 1; i <= numPalavras; i++) {
        size = rand()%MAX_PROB;
        size = sizes[size];
			for (j = 0; j < size; j++) {
				c = w[rand()%MAX_ALFABETO];
				password[j] = c;
			}
			password[j] = '\0';
			s = rand()%MAX_SALT;
			pwd = crypt(password, salt[s]);
			fprintf(senhas, "%d %s\n", size, password);
			fprintf(chaves, "%s\n", pwd);
	}
    fclose(chaves);
    fclose(senhas);
    return 0;
}
