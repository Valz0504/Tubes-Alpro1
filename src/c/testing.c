#include <stdio.h>
#include <string.h>
#include "header/matrix.h"
#include "header/queue.h"


int main() {
    Matrix rs;
    CreateMatrix(2, 3, &rs);

    strcpy(rs.data[0][0].nama_dokter, "dr. A");
    strcpy(rs.data[0][1].nama_dokter, "dr. B");
    strcpy(rs.data[0][2].nama_dokter, "dr. C");
    strcpy(rs.data[1][0].nama_dokter, "dr. D");
    strcpy(rs.data[1][1].nama_dokter, "dr. E");
    strcpy(rs.data[1][2].nama_dokter, "dr. F");

    denahRumahSakit(rs);
    return 0;
}