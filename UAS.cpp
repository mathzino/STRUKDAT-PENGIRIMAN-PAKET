#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

struct ProductNode
{
    int distance;
    char productName[50];
    struct ProductNode *next;
};

struct StackDeliv
{
    int count;
    struct ProductNode *top;
};

struct BatchNode
{
    int count;
    struct BatchNode *next;
    struct ProductNode *pHeadProd;
};

struct QueueBatch
{
    int count;
    struct BatchNode *front;
    struct BatchNode *rear;
};

//  lIST fUNCTION DECLARATION
QueueBatch createQueue();
StackDeliv createStack();
void addProdNode(ProductNode **pHeadProd, char productNameInput[50], int distanceInput);
void addProdtoBatch(QueueBatch *pQueueBatch);
void showBatch(QueueBatch *pQueueBatch);
void showStackDeliv(StackDeliv *pStackDeliv);
void sendBatch(QueueBatch *pQueueBatch, StackDeliv *pStackDeliv);
void sendCust(StackDeliv *pStackDeliv, ProductNode **pHistoryHead, QueueBatch *pQueueBatch);
void showHistoryDeliver(ProductNode **pHistoryHead);
void showStatusProduct();

int main()
{
    char selectMenu;
    QueueBatch queueBatchObj;
    QueueBatch *pQueueBatch;
    ProductNode *pProductHead;
    ProductNode *pHistoryHead = NULL;
    StackDeliv StackDelivObj;
    StackDeliv *pStackDeliv;
    pProductHead = NULL;
    queueBatchObj = createQueue();
    pQueueBatch = &queueBatchObj;
    StackDelivObj = createStack();
    pStackDeliv = &StackDelivObj;
    do
    {
        system("cls");
        printf(" PROGRAM PENGIRIRMAN PAKET  \n\n");
        printf("1. TAMBAH << MEMBUAT QUEUE BATCH PENGIRIMAN & MEMASUKKAN PRODUK DALAM BATCH>>\n");
        printf("2. KIRIM PRODUK << MEMINDAHKAN BATCH  KE STACK PENGIRIMAN >> \n");
        printf("3. PENGIRIMAN PRODUK SELESAI << MEMASUKKAN PRODUK DALAM LIST HISTORY >>\n");
        printf("4. SHOW BATCH << MENCETAK INFORMASI DALAM BATCH PENGIRIMAN >>\n");
        printf("5. SHOW STACK PENGIRIMAN << MENCETAK INFORMASI PRODUK APA SAJA DALAM PROSES PENGIRIMAN >> \n");
        printf("6. SHOW HISTORY << MENCETAK SEMUA PRODUK YANG TELAH DIKIRIM >> \n");
        // printf("7. DELETE PRODUCT FROM BATCH << MENGHAPUS PRODUCT DALAM BATCH >> \n");
        printf("PRESS [q] UNTUK KELUAR DARI PROGRAM\n");
        printf("\n");
        printf("\n");
        fflush(stdin);
        printf("Masukkan Pilihan Program : ");
        scanf(" %c", &selectMenu);
        if (selectMenu == '1')
        {
            addProdtoBatch(pQueueBatch);
        }
        else if (selectMenu == '2')
        {
            sendBatch(pQueueBatch, pStackDeliv);
        }
        else if (selectMenu == '3')
        {
            sendCust(pStackDeliv, &pHistoryHead, pQueueBatch);
        }
        else if (selectMenu == '4')
        {
            showBatch(pQueueBatch);
            getch();
        }
        else if (selectMenu == '5')
        {
            showStackDeliv(pStackDeliv);
            getch();
        }
        else if (selectMenu == '6')
        {
            showHistoryDeliver(&pHistoryHead);
        }

    } while (selectMenu != 'q');
}

QueueBatch createQueue()
{
    QueueBatch batch;
    batch.count = 0;
    batch.front = NULL;
    batch.rear = NULL;
    return batch;
};

StackDeliv createStack()
{
    StackDeliv stack;
    stack.count = 0;
    stack.top = NULL;
    return stack;
};

void addProdNode(ProductNode **pHeadProd, char productNameInput[50], int distanceInput)
{
    ProductNode *pProdNodeCur = *pHeadProd;
    ProductNode *pProdNodePre = pProdNodeCur;
    ProductNode *pProdNodeNew = (ProductNode *)malloc(sizeof(ProductNode));

    pProdNodeNew->distance = distanceInput;
    strcpy(pProdNodeNew->productName, productNameInput);

    while (pProdNodeCur->next != NULL && pProdNodeCur->distance <= distanceInput)
    {
        pProdNodePre = pProdNodeCur;
        pProdNodeCur = pProdNodeCur->next;
    }

    // kondisi awal
    if (pProdNodePre == pProdNodeCur)
    {
        if (pProdNodeCur->distance <= distanceInput)
        {
            pProdNodeNew->next = pProdNodeCur->next;
            pProdNodeCur->next = pProdNodeNew;
        }
        else
        {
            *pHeadProd = pProdNodeNew;
            pProdNodeNew->next = pProdNodeCur;
        }
    }
    // condition for last node
    // kondisi saat tidak ada kontainer selanjutnya
    else if (pProdNodeCur->next == NULL)
    {

        if (pProdNodeCur->distance <= distanceInput)
        {
            pProdNodeCur->next = pProdNodeNew;
            pProdNodeNew->next = NULL;
        }
        else
        {
            pProdNodePre->next = pProdNodeNew;
            pProdNodeNew->next = pProdNodeCur;
        }
    }
    // kondisi saat data_berat lebih ringan dari berat pCur (di tengah)
    else
    {
        pProdNodePre->next = pProdNodeNew;
        pProdNodeNew->next = pProdNodeCur;
    }
}