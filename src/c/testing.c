#include <stdio.h>
#include "user.h"

int main() {
    UserList list_user;
    CreateListDin(&list_user, 3);

    Set list_nama_user;
    initSet(&list_nama_user, 3);

    User user1;
    CreateUser(&list_user, &user1, "emilio", "justin", 1);
    insertSet(&list_nama_user, "emilio");
    AddUser(&list_user, user1);
    User user2;
    CreateUser(&list_user, &user2, "peter", "gru", 0);
    insertSet(&list_nama_user, "peter");
    AddUser(&list_user, user2);
    User user3;
    CreateUser(&list_user, &user3, "bob", "steve", 0);
    insertSet(&list_nama_user, "bob");
    AddUser(&list_user, user3);
    User user4;
    CreateUser(&list_user, &user4, "yay", "wow", 2);
    insertSet(&list_nama_user, "yay");
    AddUser(&list_user, user4);

    registerPasien(&list_user, &list_nama_user);
    // lupa_password(&list_user);

    User current_user;
    boolean isLogin = FALSE;
    logout(&current_user, &isLogin);
    login(&list_user, &current_user, &isLogin);
    logout(&current_user, &isLogin);
    printf("\n");
    for (int i = 0; i < list_user.Neff; i++) {
        printf("name: %s, pass: %s, role: %s\n", list_user.data[i].username, list_user.data[i].password, roleToStr(list_user.data[i].role));
    }
    printf("neff: %d, capacity: %d\n\n", list_user.Neff, list_user.capacity);

    for (int i = 0; i < list_nama_user.size; i++) {
        printf("nama_unik: %s\n", list_nama_user.unique_username[i]);
    }

    return 0;   
}

