/* arquivo passRepos_client.c cliente*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "passRepos.h"

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
			case 3:	printf("See you!\n");
					exit(0);
			default: printf("\nInvalid option!\n");
					 sleep(1.5);
		}
	}
	

	return 0;
}
