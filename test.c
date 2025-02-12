#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <openssl/sha.h>

struct user {
    char username[50];
    char login_password[50];
};

int regisValidation(char[], FILE *);
void toHashPassword(const char *, char *);

int main(void) {
    // Abrir o arquivo em modo de leitura e escrita
    FILE *f = fopen("users.txt", "a+");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    struct user User = {"marc", "123"};

    if (regisValidation(User.username, f) != 0) {
        printf("INVALID USERNAME\n");
    } else {
        // Escrever o nome de usuário no arquivo
        fprintf(f, "%s\t", User.username);

        // Gerar o hash da senha
        char hash_password[65];
        toHashPassword(User.login_password, hash_password);

        // Escrever o hash da senha no arquivo
        fprintf(f, "%s\n", hash_password);
        fclose(f);

        printf("\nRegistration complete!\n");
        sleep(2);
    }

    return 0;
}

void toHashPassword(const char *password, char *output_hash) {
    unsigned char hash[SHA256_DIGEST_LENGTH];

    // Gerar o hash da senha
    SHA256((unsigned char *)password, strlen(password), hash);

    // Converter o hash para formato hexadecimal
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output_hash + (i * 2), "%02x", hash[i]);
    }

    // Adicionar caractere nulo ao final
    output_hash[64] = '\0';
}

int regisValidation(char s[], FILE *f) {
    char aux[50];
    int cont = 0;

    rewind(f);  // Reiniciar o ponteiro do arquivo

    // Ler o nome de usuário do arquivo
    while (fscanf(f, "%s%*s", aux) == 1) {
        if (strcmp(s, aux) == 0)
            cont++;
    }

    return (cont > 0) ? 1 : 0;
}
