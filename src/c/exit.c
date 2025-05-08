#include <stdio.h>
#include "header/user.h"
#include "header/boolean.h"


void RemoveUser(UserList *l, User *user){
    int index = 0;
    while(strcmp(l->data[index].username, user->username) != 0){
        index += 1;
    }
    for (int i = index; i < l->Neff; i++){
        if(i == l->Neff){
            l->data[i] = NULL;
        }
        else{
            l->data[i] = l->data[i+1];
        }
    }
}


void exit(User *current_user, UserList *current_user, boolean *isLogin){
    char x;
    do {
        printf("Apakah Anda mau melakukan penyimpanan file yang sudah diubah? (y/n) ");
        scanf("%c", &x);
        toLower(&x);
    } while (x != "y" && x != "n");
    if(x == "n"){
        RemoveUser(&l, *current_user);
    }
    // x == "y" ga ada soalnya belum ada Save()
    *isLogin = false;
}
