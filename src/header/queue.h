#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE 10

typedef struct {
    int data[MAX_QUEUE];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;  // Antrian kosong, front diatur ke -1
    q->rear = -1;   // Antrian kosong, rear diatur ke -1
}

void enqueue(Queue *q, int value) {
    if (q->rear == MAX_QUEUE - 1) {
        printf("Antrian penuh, tidak bisa menambahkan pasien!\n");
        return;
    }

    if (q->front == -1) {
        q->front = 0;  // Jika antrian kosong, atur front ke 0
    }

    q->rear++;  // Naikkan indeks rear
    q->data[q->rear] = value;  // Simpan elemen di posisi rear
}

// Menghapus elemen dari antrian (dequeue)
void dequeue(Queue *q, int *value) {
    if (q->front == -1) {
        printf("Antrian kosong, tidak ada pasien yang akan dilayani!\n");
        return;
    }

    *value = q->data[q->front];  // Ambil nilai elemen pertama antrian
    q->front++;  // Geser indeks front ke elemen berikutnya

    if (q->front > q->rear) {
        q->front = q->rear = -1;  // Reset antrian jika kosong
    }
}

#endif