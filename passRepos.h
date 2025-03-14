/* arquivo passRepos.h prototipos (header)*/

#include <stdio.h>

struct user{
	char username[50];
	unsigned char login_password[50];
};

void regis_user();

int usrNameValidation(unsigned char [], FILE*);

int loginValidation(char [], unsigned char[]);

void toHashPassword(unsigned char *,unsigned char *);

void login();

