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

void addProdtoBatch(QueueBatch *pQueueBatch)
{
    system("cls");
    QueueBatch queueBatchObj = *pQueueBatch;
    BatchNode *pBatchNodeFront;
    BatchNode *pBatchNodeNew;
    BatchNode *pBatchNodeWalk, *pBatchNodeLast;
    ProductNode *pProdNodeNew;
    char productNameInput[50];
    int distanceInput;
    // jumlah maximal produk dalam batch
    int maxQuotaBatch = 2;
    // input informasi barang
    printf("\nMasukkan Nama Barang : ");
    scanf(" %49[^\n]s ", productNameInput);
    printf("Masukkan Jarak Pengantaran Barang (KM): ");
    scanf("%d", &distanceInput);
    // Make new Product Node
    // ProductNode data structure = LinkedList
    pProdNodeNew = (ProductNode *)malloc(sizeof(ProductNode));
    // fill the ProductNode {name,distance,next} data
    // Inisiasi pada productnode yang baru
    pProdNodeNew->distance = distanceInput;
    strcpy(pProdNodeNew->productName, productNameInput);
    pProdNodeNew->next = NULL;
    // kondisi QueueBatch masih kosong
    if (queueBatchObj.count == 0)
    {
        // Membuat batch baru
        pBatchNodeNew = (BatchNode *)malloc(sizeof(BatchNode));
        //  update data batch
        pBatchNodeNew->pHeadProd = pProdNodeNew;
        pBatchNodeNew->next = NULL;
        // satu batch memilki beberapa node product
        pBatchNodeNew->count = 1;
        // struktur data batch = Queue
        // update data Batch Queue
        queueBatchObj.rear = pBatchNodeNew;
        queueBatchObj.front = pBatchNodeNew;
        queueBatchObj.count = 1;
        *pQueueBatch = queueBatchObj;
    }
    // Kondisi batch sudah dibuat || sudah ada data di dalamnya
    else
    {
        pBatchNodeLast = queueBatchObj.rear;
        // Kondisi batch belum terisi penuh
        if (pBatchNodeLast->count < maxQuotaBatch)
        {
            addProdNode(&pBatchNodeLast->pHeadProd, productNameInput, distanceInput);
            pBatchNodeLast->count++;
        }
        // Kondisi batch telah terisi penuh -> membuat batch baru
        else
        {
            // membuat node batch baru
            pBatchNodeNew = (BatchNode *)malloc(sizeof(BatchNode));
            pBatchNodeWalk = queueBatchObj.front;
            // mencari batch terakhir
            // set Queue batch
            pBatchNodeLast = queueBatchObj.rear;
            pBatchNodeLast->next = pBatchNodeNew;
            queueBatchObj.rear = pBatchNodeNew;
            queueBatchObj.count++;
            *pQueueBatch = queueBatchObj;
            // inisiasi data pada batch baru
            pBatchNodeNew->pHeadProd = pProdNodeNew;
            pBatchNodeNew->next = NULL;
            pBatchNodeNew->count = 1;
        }
    }
}

void delivFail(QueueBatch *pQueueBatch, char productNameInput[50], int distanceInput)
{

    QueueBatch queueBatchObj = *pQueueBatch;
    BatchNode *pBatchNodeFront;
    BatchNode *pBatchNodeNew;
    BatchNode *pBatchNodeWalk, *pBatchNodeLast;
    ProductNode *pProdNodeNew;
    // jumlah maximal produk dalam batch
    int maxQuotaBatch = 2;
    // Make new Product Node
    // ProductNode data structure = LinkedList
    pProdNodeNew = (ProductNode *)malloc(sizeof(ProductNode));
    // fill the ProductNode {name,distance,next} data
    // Inisiasi pada productnode yang baru
    pProdNodeNew->distance = distanceInput;
    strcpy(pProdNodeNew->productName, productNameInput);
    pProdNodeNew->next = NULL;
    // kondisi QueueBatch masih kosong
    if (queueBatchObj.count == 0)
    {
        // Membuat batch baru
        pBatchNodeNew = (BatchNode *)malloc(sizeof(BatchNode));
        //  update data batch
        pBatchNodeNew->pHeadProd = pProdNodeNew;
        pBatchNodeNew->next = NULL;
        // satu batch memilki beberapa node product
        pBatchNodeNew->count = 1;
        // struktur data batch = Queue
        // update data Batch Queue
        queueBatchObj.rear = pBatchNodeNew;
        queueBatchObj.front = pBatchNodeNew;
        queueBatchObj.count = 1;
        *pQueueBatch = queueBatchObj;
    }
    // Kondisi batch sudah dibuat || sudah ada data di dalamnya
    else
    {
        pBatchNodeLast = queueBatchObj.rear;
        // Kondisi batch belum terisi penuh
        if (pBatchNodeLast->count < maxQuotaBatch)
        {
            addProdNode(&pBatchNodeLast->pHeadProd, productNameInput, distanceInput);
            pBatchNodeLast->count++;
        }
        // Kondisi batch telah terisi penuh -> membuat batch baru
        else
        {
            // membuat node batch baru
            pBatchNodeNew = (BatchNode *)malloc(sizeof(BatchNode));
            pBatchNodeWalk = queueBatchObj.front;
            // mencari batch terakhir
            // set Queue batch
            pBatchNodeLast = queueBatchObj.rear;
            pBatchNodeLast->next = pBatchNodeNew;
            queueBatchObj.rear = pBatchNodeNew;
            queueBatchObj.count++;
            *pQueueBatch = queueBatchObj;
            // inisiasi data pada batch baru
            pBatchNodeNew->pHeadProd = pProdNodeNew;
            pBatchNodeNew->next = NULL;
            pBatchNodeNew->count = 1;
        }
    }
}

void showBatch(QueueBatch *pQueueBatch)
{
    system("cls");
    QueueBatch queueBatch = *pQueueBatch;
    BatchNode *pBatchNodeCur = queueBatch.front;
    int i = 0;
    // kondisi batch kosong
    if (pQueueBatch->count == 0)
    {
        cout << " BATCH PENGIRIMAN KOSONG ";
    }
    // kondisi batch memiliki data
    else
    {
        cout << "BATCH PENGIRIMAN :";
        while (pBatchNodeCur != NULL)
        {
            cout << "\n\nkode batch ke " << ++i << ": " << pBatchNodeCur << "\n\n";
            ProductNode *pProductNodeHead = pBatchNodeCur->pHeadProd;
            ProductNode *pProdNodeWalk = pProductNodeHead;
            while (pProdNodeWalk != NULL)
            {
                cout << "\t==========================\n";
                cout << "\tNama Barang :" << pProdNodeWalk->productName << "\n";
                cout << "\tKode Barang :" << pProdNodeWalk << "\n";
                cout << "\tJarak Pengiriman :" << pProdNodeWalk->distance << " KM\n";
                cout << "\t==========================\n";
                pProdNodeWalk = pProdNodeWalk->next;
            }
            pBatchNodeCur = pBatchNodeCur->next;
        }
    }

    getch();
}

void showStackDeliv(StackDeliv *pStackDeliv)
{
    system("cls");
    ProductNode *pProdNodeWalk = pStackDeliv->top;
    int i = 0;
    if (pStackDeliv->count == 0)
    {
        cout << " STACK PENGIRIMAN KOSONG ";
    }
    else
    {
        cout << "STACK PENGIRIMAN : \n\n";
        while (pProdNodeWalk != NULL)
        {
            cout << "\t==========================\n";
            cout << "\tNama Barang :" << pProdNodeWalk->productName << "\n";
            cout << "\tKode Barang :" << pProdNodeWalk << "\n";
            cout << "\tJarak Pengiriman :" << pProdNodeWalk->distance << " KM\n";
            cout << "\t==========================\n";
            pProdNodeWalk = pProdNodeWalk->next;
        }
    }
    getch();
}

void sendBatch(QueueBatch *pQueueBatch, StackDeliv *pStackDeliv)
{
    // ProductNode * pProductWalk = pQueueBatch->front->pHeadProd;
    // KONDISI TERDAPAT BATCH
    if (pQueueBatch->count > 0)
    {
        // MEMINDAHKAN BATCH KE STACK PENGIRIMAN
        pStackDeliv->top = pQueueBatch->front->pHeadProd;
        pStackDeliv->count = pQueueBatch->front->count;
        pQueueBatch->front = pQueueBatch->front->next;
        pQueueBatch->count--;
    }
    // KONDISI BELUM ADA BATCH PRODUK SAMA SEKALI
    else
    {
        cout << "belum ada batch sama sekali";
        getch();
    }
}

void sendCust(StackDeliv *pStackDeliv, ProductNode **pHistoryHead, QueueBatch *pQueueBatch)
{
    ProductNode *pProductNodeCur, *pHistoryNew, *pProdFailDeliv;
    pHistoryNew = *pHistoryHead;
    char isSuccess;
    // KONDISI STACK SUDAH MEMILIKI DATA
    if (pStackDeliv->count != 0)
    {
        // CEK PRODUK BERHASIL DIKIRIM
        printf("Produk di terima pembeli('y'/'Y') : ");
        scanf(" %c", &isSuccess);
        if (isSuccess == 'y' || isSuccess == 'Y')
        {
            // KONDISI HISTORY MASIH BELUM MEMILIKI DATA
            // MEMINDAHKAN DATA PROD DARI STACK PENGIRIMAN KE HISTORY PRODUK YANG TELAH DIKIRIMKAN
            if (*pHistoryHead == NULL)
            {
                pHistoryNew = pStackDeliv->top;
                pStackDeliv->top = pStackDeliv->top->next;
                pHistoryNew->next = NULL;
                *pHistoryHead = pHistoryNew;
            }
            // KONDISI HISTORY SUDAH MEMILIKI DATA DI DALAMNYA
            else
            {
                ProductNode *pHistoryWalk = *pHistoryHead;
                while (pHistoryWalk->next != NULL)
                {
                    pHistoryWalk = pHistoryWalk->next;
                }
                pHistoryWalk->next = pStackDeliv->top;
                pStackDeliv->top = pStackDeliv->top->next;
                pHistoryWalk->next->next = NULL;
            }
            pStackDeliv->count--;
        }
        else
        {
            pProdFailDeliv = pStackDeliv->top;
            pStackDeliv->top=pStackDeliv->top->next;
            delivFail(pQueueBatch, pProdFailDeliv->productName, pProdFailDeliv->distance);
            printf("PRODUK DIMASUKKAN KE DALAM BATCH PENGIRIMAN\n");
            getch();
        }
    }
    else
    {
        printf("STACK PENGIRIMAN MASIH KOSONG");
        getch();
    }
}

void showHistoryDeliver(ProductNode **pHistoryHead)
{
    system("cls");
    ProductNode *pHistoryWalk = *pHistoryHead;
    if (pHistoryWalk == NULL)
    {
        cout << "BELUM ADA PENGIRIMAN YANG SUKSES ";
    }
    else
    {
        cout << "PRODUK YANG BERHASIL DIKIRIM\n\n";
        while (pHistoryWalk != NULL)
        {
            cout << "\t==========================\n";
            cout << "\tKode Barang :" << pHistoryWalk << "\n";
            cout << "\tNama Barang :" << pHistoryWalk->productName << "\n";
            cout << "\tJarak Pengiriman :" << pHistoryWalk->distance << " KM\n";
            cout << "\t==========================\n";
            pHistoryWalk = pHistoryWalk->next;
        }
    }

    getch();
}
