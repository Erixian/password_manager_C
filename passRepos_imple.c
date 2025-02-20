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
            exit(1);
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

int usrNameValidation(char s[],FILE *f){
	
	char aux[50];
	int cont = 0;
	
	while(fscanf(f, "%s%*s", aux) == 1)
	{
		if(strcmp(aux,s) == 0)
			cont++;
	}
	
	return (cont > 0) ? 1 : 0;
}

void toHashPassword(const char *password, unsigned char *output_hash) {

	unsigned char hash[SHA256_DIGEST_LENGTH];
	
	SHA256((unsigned char *)password, strlen(password), hash);
	
	for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		sprintf(output_hash + (i * 2), "%02x", hash[i]);
	}
	
	output_hash[64] = '\0';
}


int loginValidation(char usrname[], unsigned char informed_hashedpsw[], FILE* f) {

	int flag = 0;
	char usrname_buffer[49];
	char from_file_hashedpsw[SHA256_DIGEST_LENGTH];
	
	rewind(f);
	
	if(f == NULL)
	{
		printf("ERROR OPENING FILE");
		exit(1);
	}
	
	while(fscanf(f, "%s%s", usrname_buffer,informed_hashedpsw) == 2)
	{
		if(usrNameValidation(usrname,f) == 0){
			fread(from_file_hashedpsw, 1, SHA256_DIGEST_LENGTH, f);
			if(memcmp(informed_hashedpsw, from_file_hashedpsw, SHA256_DIGEST_LENGTH) == 0)
				return 0;
		}	
	}

	fgetc(f);

	return 1;

}

void login(){
	
	char username[49];
	unsigned char psw[49];
	unsigned char hashedpsw[SHA256_DIGEST_LENGTH];


	printf("Inform your username:\t\n");
	scanf("%s", username);
	printf("Inform your password:\t\n");
	scanf("%s", psw);

	toHashPassword(psw, hashedpsw);

	FILE *f = fopen("users.txt", "r");//"r" garante que a leitura do arquivo comece na linha 0
	
	if(f == NULL)
	{
		printf("ERROR OPENING FILE");
		exit(1);
	}



	if(loginValidation(username, hashedpsw, f) == 0)
	{
		printf("\nLogged!\n");
		sleep(2);
		system("clear");
	}
	else
	{	printf("\nFailed!\n");
		sleep(2);
		system("clear");
		login();
	}
	fclose(f);

}
