#include <stdio.h>
#include <string.h>

#include "../header/user.h"

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

void SetNewPassword(UserList *l, char username[], char pass[]) {
    for (int i = 0; i < l->Neff; i++) {
        if (strcmp(l->data[i].username, username) == 0) {
            strcpy(l->data[i].password, pass);
        }
    }
}

void lupa_password(UserList *list, boolean *isLogin) {
    if (*isLogin) {
        printf("Loh!? kan kamu udah login, kok malah lupa password?\n\n");
    } else {
        printf("=== GANTI PASSWORD ===\n");
    
        char username[100];
        char kode_unik[100];
        printf("Username: ");
        scanf(" %[^\n]s", username);
        printf("Kode Unik: ");
        scanf(" %[^\n]s", kode_unik);
    
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
}