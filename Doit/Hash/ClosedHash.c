#include "ClosedHash.h"
#include "Member.h"
#include <stdio.h>
#include <stdlib.h>

static int hash(int key, int size)
{
    return key % size;
}

static int rehash(int key, int size)
{
    return (key + 1) % size;
}

static void SetBucket(Bucket* n, const Member* x, Status stat)
{
    n->data = *x;
    n->stat = stat;
}

int Initialize(ClosedHash* h, int size)
{
    int i;
    if ((h->table = calloc(size, sizeof(Bucket))) == NULL)
    {
        h->size = 0;
        return 0;
    }
    h->size = size;
    for (i = 0; i < size; ++i)
        h->table[i].stat = Empty;
    return 1;
}

Bucket* Search(const ClosedHash* h, const Member* x)
{
    int i;
    int key = hash(x->no, h->size);
    Bucket* p = &h->table[key];
    // ���ϴ� ���� ã�� ������ ���ؽø� �ݺ��Ѵ�.
    for (i = 0; p->stat != Empty && i < h->size; ++i)
    {
        if (p->stat == Occupied && p->data.no == x->no)
            return p;
        key = rehash(key, h->size);  // ���ؽ�
        p = &h->table[key];
    }
    return NULL;
}

int Add(ClosedHash* h, const Member* x)
{
    int i;
    int key = hash(x->no, h->size);
    Bucket* p = &h->table[key];
    if (Search(h, x)) // �� Ű�� �̹� ��ϵ�
        return 1;
    for (i = 0; i < h->size; ++i)
    {
        // �ش� ��Ŷ�� ����ְų� �������?
        if (p->stat == Empty || p->stat == Deleted)
        {
            SetBucket(p, x, Occupied); // �ش� ��Ŷ�� ����
            return 0;
        }
        key = rehash(key, h->size);  // ���ؽ�
        p = &h->table[key];
    }
    
    return 2; // �ؽ� ���̺��� ���� ��
}

int Remove(ClosedHash* h, const Member* x)
{
    Bucket* p = Search(h, x);
    if (p == NULL)
        return 1;
    p->stat = Deleted; // ������ �ǹ�
    return 0;
}

void Dump(const ClosedHash* h)
{
    int i;
    for (i = 0; i < h->size; ++i)
    {
        printf("%02d : ", i);
        switch (h->table[i].stat)
        {
        case Occupied:
            printf("%d(%s)\n", h->table[i].data.no, h->table[i].data.name);
            break;

        case Empty:
            printf("-- �̵�� --\n");
            break;

        case Deleted:
            printf("-- ���� ��ħ --\n");
            break;
        }
    }
}

void Clear(ClosedHash* h)
{
    int i;
    for (i = 0; i < h->size; ++i)
        h->table[i].stat = Empty;
}

void Terminate(ClosedHash* h)
{
    Clear(h);
    free(h->table);
    h->size = 0;
}