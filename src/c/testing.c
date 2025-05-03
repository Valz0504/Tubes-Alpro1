#include <stdio.h>
#include "header/user.h"

int main() {
    UserList list_user;
    CreateListDin(&list_user, 3);

    User user1;
    CreateUser(&list_user, &user1, "emilio", "justin", 1);
    AddUser(&list_user, user1);
    User user2;
    CreateUser(&list_user, &user2, "keisha", "sakura", 2);
    AddUser(&list_user, user2);
    User user3;
    CreateUser(&list_user, &user3, "bob", "sakura", 2);
    AddUser(&list_user, user3);
    User user4;
    CreateUser(&list_user, &user4, "yay", "sakura", 2);
    AddUser(&list_user, user4);

    User current_user;
    boolean isLogin = FALSE;
    login(&list_user, &current_user, &isLogin);

    for (int i = 0; i < list_user.Neff; i++) {
        printf("name: %s, pass: %s, role: %s\n", list_user.data[i].username, list_user.data[i].password, roleToStr(list_user.data[i].role));
    }
    printf("neff: %d, capacity: %d\n", list_user.Neff, list_user.capacity);
    return 0;   
}

