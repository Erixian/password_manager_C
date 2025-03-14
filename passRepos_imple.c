/* arquivo passRepos_imple.c implementação*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <openssl/sha.h>
#include "passRepos.h"


void regis_user(){
	
	struct user User;
	
	system("clear");
	printf("Enter a username:\t");
	scanf("%49s", User.username);
	printf("\nEnter a password:\t");
	scanf("%49s", User.login_password);//usar esse string para SHA
	
	
	FILE *f = fopen("users.txt", "r");//"r" garante que a leitura do arquivo comece na linha 0
	
	if(f == NULL)
	{
		printf("ERROR OPENING FILE");
		exit(1);
	}
	
	//VALIDATION FUNC
	if(usrNameValidation(User.username, f) != 0)
	{
		printf("\nINVALID USERNAME\n");
		sleep(2);
		system("clear");
		regis_user();
	}
	else
	{
		fclose(f); //fecha o arquivo aberto com "r"
		f = fopen("users.txt", "a");//aberto o arquivo novamente com "a", garantindo que as informações sejam registradas ao final do mesmo
		if (f == NULL) {
            printf("ERROR OPENING FILE");
            exit(0);
        }
		fprintf(f, "%s\t", User.username);
		
		unsigned char hashed_password[65];
		
		toHashPassword(User.login_password, hashed_password);
		
		fprintf(f, "%s\n", hashed_password);//alterar - printar apenas a hash da senha
		
		fclose(f);
		printf("\nRegistration complete!\n");
		sleep(2);
	}
}

int usrNameValidation(unsigned char s[],FILE *f){
	
	char aux[50];
	int cont = 0;
	
	while(fscanf(f, "%s%*s", aux) == 1)
	{
		if(strcmp(aux,s) == 0)
			cont++;
	}
	
	return (cont > 0) ? 1 : 0;
}

void toHashPassword(unsigned char *password, unsigned char *output_hash) {

	unsigned char hash[SHA256_DIGEST_LENGTH];
	
	SHA256((unsigned char *)password, strlen(password), hash);
	
	for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		sprintf(output_hash + (i * 2), "%02x", hash[i]);
	}
	
	output_hash[64] = '\0';
}


int loginValidation(char informed_usrname[], unsigned char informed_hashedpsw[]) {
	int flag = 0;
	//char file_string[116];
	char file_username[50];
	unsigned char file_pwd[65];

	char *fs = (char*) malloc(116 * sizeof(char));

	FILE *f = fopen("users.txt", "r");
	if (f == NULL) {
		printf("ERROR OPENING FILE");
		exit(1);
	}

	while(fgets(fs,116,f))
	{

		int ret = sscanf(fs, "%s\t%s", file_username, file_pwd);

		if(strcmp(file_username,informed_usrname) == 0 && strcmp(file_pwd, informed_hashedpsw) == 0)
			flag = 1;

	}

	/*printf("Read from file - Username: %s, Password: %s\n", file_username, file_pwd);
	printf("Informed - Username: %s, Password: %s\n", informed_usrname, informed_hashedpsw);
	sleep(20);*/

	fclose(f);
	free(fs);

	return flag ? 0 : 1;
}

void login(){

	struct user User;
	unsigned char hashedpsw[SHA256_DIGEST_LENGTH];

	system("clear");

	printf("Inform your username:\t");
	scanf("%s", User.username);
	printf("\nInform your password:\t");
	scanf("%s", User.login_password);

	toHashPassword(User.login_password, hashedpsw);

	/*printf("login informed username: %s", User.username);
	printf("login informed password %s", hashedpsw);*/

	if(loginValidation(User.username, hashedpsw) == 0)
	{
		printf("\nLogged!\n");
		sleep(2);
		exit(0);
	}
	else
	{	printf("\nFailed!\n");
		sleep(2);
		system("clear");
		login();
	}
}
