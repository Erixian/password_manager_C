/* arquivo tester_client.c cliente*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "passRepos.h"

int main(void){

	char username[50];
	char pwd[50];
	unsigned char pwdHash[65];

	printf("Testando\n\n");
	printf("informe o username: ");
	scanf("%s", username);
	printf("informe a senha: ");
	scanf("%s", pwd);

	printf("\n%s", username);
	printf("%s\n", pwd);

	toHashPassword(pwd,pwdHash);
	
	printf("%s", pwdHash);

	FILE *f = fopen("tester_users.txt", "a");
	if(f == NULL){
		printf("ERRO OPENNING FILE");
		exit(1);
	}
	else {
		fprintf(f, "%s\t", username);
		fprintf(f,"%s\n", pwdHash);

		fclose(f);	
	}
		

	return 0;
}
