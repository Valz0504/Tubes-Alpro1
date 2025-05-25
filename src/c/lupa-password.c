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
    // reset keys values
    size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        keys[i][0] = '\0';
        values[i] = 0;
    }

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
        printf(YELLOW "Loh!? kan kamu udah login, kok malah lupa password?\n\n" RESET);
    } else {
        printf(CYAN BOLD "=== GANTI PASSWORD ===\n" RESET);
    
        char username[100];
        char kode_unik[100];
        printf(YELLOW "Username: " RESET);
        scanf("%s", username);
        printf(YELLOW "Kode Unik: " RESET);
        scanf("%s", kode_unik);
    
        if (isUsernameExist(*list, username)) {
            User *user = findUser(list, username);
            if (strcmp(kode_unik, RunLengthEncoding(username)) == 0) {
                char new_password[100];
                
                printf(GREEN "Halo %s %s, silakan daftarkan ulang password anda!\n" RESET, roleToStr(user->role), username);
                printf(YELLOW "Password baru: " RESET);
                scanf("%s", new_password);
                SetNewPassword(list, username, new_password);
                printf(GREEN "Password berhasil diubah!\n\n" RESET);
            } else {
                printf(RED "Kode unik salah!\n");
            }
        } else {
            printf(RED "Username tidak terdaftar!\n");
        }
        printf("\n");
    }
}