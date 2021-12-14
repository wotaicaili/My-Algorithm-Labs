#include "FIB.h"
#include <cmath>
#include <string>
#include <iostream>
#include <climits>

using namespace std;
FibHeap *FibHeapMake()
//初始化一个空的FibHeap
{
    FibHeap *heap = NULL;
    heap = new FibHeap;
    return heap;
}

FibNode *FibNodeMake()
//初始化结点x
{
    FibNode *node = NULL;
    node = new FibNode;
    node->left = node->right = node;
    return node;
}

void RemoveNode(FibNode *node)
// 将node从双链表移除
{
    node->left->right = node->right;
    node->right->left = node->left;
}

void AddNode(FibNode *a, FibNode *b)
// 将双向链表b链接到双向链表a的后面
{
    a->left = b->left;
    b->left->right = a;
    a->right = b;
    b->left = a;
}

int InsertNode(FibHeap *heap, FibNode *node)
//结点node插入fibonacci heap中
{
    if (0 == heap->keyNum)
    {
        heap->min = node;
    }
    else
    {
        AddNode(node, heap->min);
        node->parent = NULL;
        if (node->key < heap->min->key)
        {
            heap->min = node;
        }
    }
    heap->keyNum++;
    return heap->keyNum;
}

int InsertKey(FibHeap *heap, int key)
//将值插入Fibonacci Heap
{
    FibNode *node = NULL;
    node = FibNodeMake();
    node->key = key;
    InsertNode(heap, node);
    return heap->keyNum;
}

void InsertKeys(FibHeap *heap, int keys[], int keyNum)
//将数组内值插入Fibonacci Heap
{
    for (int i = 0; i < keyNum; i++)
    {
        InsertKey(heap, keys[i]);
    }
}

int MINIMUM(FibHeap *heap)
{
    if (heap->min == NULL)
        cout << "!!!!" << endl;
    return heap->min->key;
}

FibNode *RemoveMin(FibHeap *heap)
//移除最小节点
{
    FibNode *min = heap->min;
    if (heap->min == min->right)
    {
        heap->min = NULL;
    }
    else
    {
        RemoveNode(min);
        heap->min = min->right;
    }
    min->left = min->right = min;
    return min;
}

void FibConsMake(FibHeap *heap)
//开辟FpConsolidate函数哈希所用空间
{
    int old = heap->maxDegree;
    heap->maxDegree = int(log(heap->keyNum * 1.0) / log(2.0)) + 1;
    if (old < heap->maxDegree)
    {
        heap->cons = (FibNode **)realloc(
            heap->cons, sizeof(FibHeap *) * (heap->maxDegree + 1));
        if (NULL == heap->cons)
        {
            puts("Out of Space!");
            exit(1);
        }
    }
}

void FibHeapLink(FibHeap *heap, FibNode *x, FibNode *y)
//将x根结点链接到y根结点
{
    RemoveNode(x);
    if (NULL == y->child)
    {
        y->child = x;
    }
    else
    {
        AddNode(x, y->child);
    }
    x->parent = y;
    y->degree++;
    x->marked = false;
}

//合并左右相同度数的二项树
void FibHeapConsolidate(FibHeap *heap)
{
    int D, d;
    FibNode *w = heap->min, *x = NULL, *y = NULL;
    FibConsMake(heap);
    D = heap->maxDegree + 1;
    for (int i = 0; i < D; i++)
    {
        *(heap->cons + i) = NULL;
    }
    while (NULL != heap->min)
    {
        x = RemoveMin(heap);
        d = x->degree;
        while (NULL != *(heap->cons + d))
        {
            y = *(heap->cons + d);
            if (x->key > y->key)
            {
                swap(x, y);
            }
            FibHeapLink(heap, y, x);
            *(heap->cons + d) = NULL;
            d++;
        }
        *(heap->cons + d) = x;
    }
    heap->min = NULL;
    for (int i = 0; i < D; i++)
    {
        if (*(heap->cons + i) != NULL)
        {
            if (NULL == heap->min)
            {
                heap->min = *(heap->cons + i);
            }
            else
            {
                AddNode(*(heap->cons + i), heap->min);
                if ((*(heap->cons + i))->key < heap->min->key)
                {
                    heap->min = *(heap->cons + i);
                }
            }
        }
    }
}

//抽取最小结点
FibNode *ExtractMin(FibHeap *heap)
{
    FibNode *x = NULL, *z = heap->min;
    if (z != NULL)
    {
        while (NULL != z->child)
        {
            x = z->child;
            RemoveNode(x);
            if (x->right == x)
            {
                z->child = NULL;
            }
            else
            {
                z->child = x->right;
            }
            AddNode(x, z);
            x->parent = NULL;
        }
        RemoveNode(z);
        if (z->right == z)
        {
            heap->min = NULL;
        }
        else
        {
            heap->min = z->right;
            FibHeapConsolidate(heap);
        }
        heap->keyNum--;
    }
    return z;
}

//修改度数
void renewDegree(FibNode *parent, int degree)
{
    parent->degree -= degree;
    if (parent->parent != NULL)
    {
        renewDegree(parent->parent, degree);
    }
}

//切断x与父节点y之间的链接，使x成为一个根
void FibHeapCut(FibHeap *heap, FibNode *x, FibNode *y)
{
    RemoveNode(x);
    renewDegree(y, x->degree);
    if (x == x->right)
    {
        y->child = NULL;
    }
    else
    {
        y->child = x->right;
    }
    x->parent = NULL;
    x->left = x->right = x;
    x->marked = false;
    AddNode(x, heap->min);
}

//级联剪切
void CascadingCut(FibHeap *heap, FibNode *y)
{
    FibNode *z = y->parent;
    if (NULL != z)
    {
        if (y->marked == false)
        {
            y->marked = true;
        }
        else
        {
            FibHeapCut(heap, y, z);
            CascadingCut(heap, z);
        }
    }
}

//减小一个关键字
void FibHeapDecrease(FibHeap *heap, FibNode *x, int key)
{
    FibNode *y = x->parent;
    if (x->key < key)
    {
        puts("new key is greater than current key!");
        exit(1);
    }
    x->key = key;

    if (NULL != y && x->key < y->key)
    {
        //级联剪切操作
        FibHeapCut(heap, x, y);
        CascadingCut(heap, y);
    }
    if (x->key < heap->min->key)
    {
        heap->min = x;
    }
}

//删除结点
int FibHeapDelete(FibHeap *heap, FibNode *x)
{
    FibHeapDecrease(heap, x, INT_MIN);
    ExtractMin(heap);
    return heap->keyNum;
}

//被FibHeapSearch调用
FibNode *FibNodeSearch(FibNode *x, int key)
{
    FibNode *w = x, *y = NULL;
    if (x != NULL)
    {
        do
        {
            if (w->key == key)
            {
                y = w;
                break;
            }
            else if (NULL != (y = FibNodeSearch(w->child, key)))
            {
                break;
            }
            w = w->right;
        } while (w != x);
    }
    return y;
}

//堆内搜索关键字
FibNode *FibHeapSearch(FibHeap *heap, int key)
{
    return FibNodeSearch(heap->min, key);
}

//被FibHeapDestory调用
void FibNodeDestory(FibNode *x)
{
    FibNode *p = x, *q = NULL;
    while (p != NULL)
    {
        FibNodeDestory(p->child);
        q = p;
        if (p->left == x)
        {
            p = NULL;
        }
        else
        {
            p = p->left;
        }
        free(q->right);
    }
}

//销毁堆
void FibHeapDestory(FibHeap *heap)
{
    FibNodeDestory(heap->min);
    free(heap);
    heap = NULL;
}

//合并堆
FibHeap *FibHeapUnion(FibHeap *heap1, FibHeap *heap2)
{
    FibHeap *tmp;
    if (heap1 == NULL)
    {
        return heap2;
    }
    if (heap2 == NULL)
    {
        return heap1;
    }
    if (heap2->maxDegree > heap1->maxDegree)
    {
        tmp = heap1;
        heap1 = heap2;
        heap2 = tmp;
    }
    if (heap1->min == NULL)
    {
        heap1->min = heap2->min;
        heap1->keyNum = heap2->keyNum;
        free(heap2->cons);
        free(heap2);
    }
    else if (heap2->min == NULL)
    {
        free(heap2->cons);
        free(heap2);
    }
    else
    {
        AddNode(heap1->min, heap2->min);
        if (heap1->min->key > heap2->min->key)
        {
            heap1->min = heap2->min;
        }
        heap1->keyNum += heap2->keyNum;
        free(heap2->cons);
        free(heap2);
    }
    return heap1;
}