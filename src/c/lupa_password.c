#include <stdio.h>
#include <string.h>

#include "user.h"
#include "boolean.h"

#define MAX_SIZE 100

/* MAP */
int size = 0;
char keys[MAX_SIZE][100];
int values[MAX_SIZE];

void insertToMap(char key[]) {
    /* Masukin masing masing char dari key ke map */
    if (size == 0) {
        strcpy(keys[size], key);
        values[size] = 1;
        size++;
    } else {
        if (strcmp(keys[size - 1], key) == 0) {
            values[size - 1]++;
        } else {
            strcpy(keys[size], key);
            values[size] = 1;
            size++;
        }
    }
}

char* RunLengthEncoding(char username[]) {
    /* Generate RLE dari username */
    for (int i = 0; i < strlen(username); i++) {
        char key[2] = {username[i], '\0'};
        insertToMap(key);
    }

    static char rle[1000] = "";
    rle[0] = '\0';
    for (int i = 0; i < size; i++) {
        if (values[i] > 1) {
            char temp[100];
            sprintf(temp, "%d", values[i]);
            strcat(rle, temp);
        }
        strncat(rle, keys[i], 1);
    }
    return rle;
}

void lupa_password(UserList *list) {
    printf("=== GANTI PASSWORD ===\n");

    char username[100];
    char kode_unik[100];
    printf("Username: ");
    scanf("%s", username);
    printf("Kode Unik: ");
    scanf("%s", kode_unik);

    if (isUsernameExist(*list, username)) {
        User *user = findUser(list, username);
        if (strcmp(kode_unik, RunLengthEncoding(username)) == 0) {
            char new_password[100];
            
            printf("Halo %s %s, silakan daftarkan ulang password anda!\n", roleToStr(user->role), username);
            printf("Password baru: ");
            scanf("%s", new_password);
            SetNewPassword(list, username, new_password);
        } else {
            printf("Kode unik salah!\n");
        }
    } else {
        printf("Username tidak terdaftar!\n");
    }
    printf("\n");
}