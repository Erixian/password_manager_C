/* arquivo passRepos.h prototipos (header)*/

#include <stdio.h>

struct user{
	char username[50];
	char login_password[50];
};

void regis_user();

int usrNameValidation(char [], FILE*);

int loginValidation(char [], unsigned char[], FILE*);

void toHashPassword(const char *,unsigned char *);

void login();

