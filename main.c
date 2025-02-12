#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <openssl/sha.h>

struct user{
	char username[50];
	char login_password[50];
};

void regis_user();

int usrNameValidation(char [], FILE*);

void loginValidation();

void toHashPassword(const char *, char *);

int main(void){

	int resp = 0;
	
	while(1)
	{
		system("clear");
		printf("*******************\n");
		printf("PASSWORD REPOSITORY\n");
		printf("*******************\n");
		printf("1 - Login\n");
		printf("2 - Register\n");
		printf("3 - Exit\n");
		printf("Choose a option: ");
		scanf("%d", &resp);
		
		switch(resp)
		{
			case 1: login();
				break;
			case 2: regis_user();
				break;
			case 3:	printf("See you!");
					exit(0);
			default: printf("\nInvalid option!\n");
					 sleep(1.5);
		}
	}
	

	return 0;
}

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
		
		hashed_password[65];
		
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

	usigned char hash[SHA256_DIGEST_LENGTH];
	
	SHA256((unsigned char *)password, strlen(password), hash);
	
	for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		sprintf(output_hash + (i * 2), "%02x", hash[i]);
	}
	
	output_hash[64] = '\0'
}