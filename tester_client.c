/* arquivo tester_client.c cliente*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "passRepos.h"

int main(void){

	char username[50];
	char pwd[50];
	unsigned char pwdHash[65];
	unsigned char fileUsername[50];
	unsigned char filePwd[65];
	unsigned char fileString[117];

	printf("Testando\n\n");
	printf("informe o username: ");
	scanf("%s", username);
	printf("informe a senha: ");
	scanf("%s", pwd);;

	toHashPassword(pwd,pwdHash);

	FILE *f = fopen("tester_users.txt", "r");
	
	int flag = 0;
	while(fgets(fileString,sizeof(fileString),f))
	{

		int ret = sscanf(fileString, "%s\t%s", fileUsername, filePwd);
		
		if(strcmp(fileUsername, username) == 0 && strcmp(filePwd, pwdHash) == 0)
			flag++;	

	}

	if(flag == 1)
		printf("OK\n");
	else
		printf("FAIL\n");	

	fclose(f);

	return 0;
}
