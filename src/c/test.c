#include <stdio.h>
#include "header/load.h"
#include "header/user.h"
#include "header/penyakit.h"

int main(){
    UserList u;
    PenyakitList p;
    ObatList o;
    Obat_PenyakitList op;
    loadDataUser("file/user.csv", &u);
    loadDataPenyakit("file/penyakit.csv", &p);
    loadDataObat("file/obat.csv", &o);
    loadDataObatPenyakit("file/obat_penyakit.csv", &op);


    return 0;
}