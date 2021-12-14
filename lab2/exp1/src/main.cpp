#include "function.cpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
using namespace std;
ifstream fin;
ofstream fresult, ftime;

int main()
{
    clock_t start, end;

    fin.open("../input/2_1_input.txt", ios::in);
    if (!fin.is_open())
    {
        std::cerr << "cannot open the file";
        exit(1);
    }
    fresult.open("../output/result.txt", ios::out);
    ftime.open("../output/time.txt", ios::out);

    int inheap1[100];
    int inheap2[200];
    int inheap3[200];
    int inheap4[300];
    while (!fin.eof())
    {
        // heap
        for (int i = 0; i <= 49; i++)
            fin >> inheap1[i];
        for (int i = 0; i <= 99; i++)
            fin >> inheap2[i];
        for (int i = 0; i <= 149; i++)
            fin >> inheap3[i];
        for (int i = 0; i <= 199; i++)
            fin >> inheap4[i];
    }
    // step1
    FibHeap *heap1, *heap2, *heap3, *heap4;
    heap1 = FibHeapMake();
    heap2 = FibHeapMake();
    heap3 = FibHeapMake();
    heap4 = FibHeapMake();
    InsertKeys(heap1, inheap1, 50);
    InsertKeys(heap2, inheap2, 100);
    InsertKeys(heap3, inheap3, 150);
    InsertKeys(heap4, inheap4, 200);

    // step2
    FibNode *x = NULL;
    start = clock();
    fresult << "H1:" << endl;
    fresult << InsertKey(heap1, 249) << " "
            << InsertKey(heap1, 830) << " ";
    fresult << MINIMUM(heap1) << " ";
    x = FibHeapSearch(heap1, 127);
    FibHeapDelete(heap1, x);
    fresult << heap1->keyNum << " ";
    x = FibHeapSearch(heap1, 141);
    FibHeapDelete(heap1, x);
    fresult << heap1->keyNum << " ";
    fresult << MINIMUM(heap1) << " ";
    x = FibHeapSearch(heap1, 75);
    FibHeapDecrease(heap1, x, 61);
    fresult << MINIMUM(heap1) << " ";
    x = FibHeapSearch(heap1, 198);
    FibHeapDecrease(heap1, x, 169);
    fresult << MINIMUM(heap1) << " ";
    x = ExtractMin(heap1);
    fresult << x->key << " ";
    x = ExtractMin(heap1);
    fresult << x->key << " " << endl;
    end = clock();
    ftime << long(end - start) / (CLOCKS_PER_SEC / 1000000) << "us" << endl;

    // step3
    start = clock();
    fresult << "H2: " << endl;
    fresult << InsertKey(heap2, 816) << " ";
    fresult << MINIMUM(heap2) << " ";
    fresult << InsertKey(heap2, 345) << " ";
    x = ExtractMin(heap2);
    fresult << x->key << " ";
    x = FibHeapSearch(heap2, 504);
    fresult << FibHeapDelete(heap2, x) << " ";
    x = FibHeapSearch(heap2, 203);
    fresult << FibHeapDelete(heap2, x) << " ";
    x = FibHeapSearch(heap2, 296);
    FibHeapDecrease(heap2, x, 87);
    fresult << MINIMUM(heap2) << " ";
    x = FibHeapSearch(heap2, 278);
    FibHeapDecrease(heap2, x, 258);
    fresult << MINIMUM(heap2) << " ";
    x = ExtractMin(heap2);
    fresult << x->key << endl;
    end = clock();
    ftime << long(end - start) / (CLOCKS_PER_SEC / 1000000) << "us" << endl;

    // step4
    start = clock();
    fresult << "H3: " << endl;
    x = ExtractMin(heap3);
    fresult << x->key << " ";
    fresult << MINIMUM(heap3) << " ";
    fresult << InsertKey(heap3, 262) << " ";
    x = ExtractMin(heap3);
    fresult << x->key << " ";
    fresult << InsertKey(heap3, 830) << " ";
    fresult << MINIMUM(heap3) << " ";
    x = FibHeapSearch(heap3, 134);
    fresult << FibHeapDelete(heap3, x) << " ";
    x = FibHeapSearch(heap3, 177);
    fresult << FibHeapDelete(heap3, x) << " ";
    x = FibHeapSearch(heap3, 617);
    FibHeapDecrease(heap3, x, 360);
    fresult << MINIMUM(heap3) << " ";
    x = FibHeapSearch(heap3, 889);
    FibHeapDecrease(heap3, x, 353);
    fresult << MINIMUM(heap3) << endl;
    end = clock();
    ftime << long(end - start) / (CLOCKS_PER_SEC / 1000000) << "us" << endl;

    // step5
    start = clock();
    fresult << "H4: " << endl;
    fresult << MINIMUM(heap4) << " ";
    x = FibHeapSearch(heap4, 708);
    fresult << FibHeapDelete(heap4, x) << " ";
    fresult << InsertKey(heap4, 281) << " ";
    fresult << InsertKey(heap4, 347) << " ";
    fresult << MINIMUM(heap4) << " ";
    x = FibHeapSearch(heap4, 415);
    fresult << FibHeapDelete(heap4, x) << " ";
    x = ExtractMin(heap4);
    fresult << x->key << " ";
    x = FibHeapSearch(heap4, 620);
    FibHeapDecrease(heap4, x, 354);
    fresult << MINIMUM(heap4) << " ";
    x = FibHeapSearch(heap4, 410);
    FibHeapDecrease(heap4, x, 80);
    fresult << MINIMUM(heap4) << " ";
    fresult << MINIMUM(heap4) << " ";
    x = ExtractMin(heap4);
    fresult << x->key << endl;
    end = clock();
    ftime << long(end - start) / (CLOCKS_PER_SEC / 1000000) << "us" << endl;

    // step6
    FibHeap *heap5 = FibHeapUnion(heap1, heap2);
    heap5 = FibHeapUnion(heap5, heap3);
    heap5 = FibHeapUnion(heap5, heap4);

    // step7
    start = clock();
    fresult << "H5: " << endl;
    x = ExtractMin(heap5);
    fresult << x->key << " ";
    fresult << MINIMUM(heap5) << " ";
    x = FibHeapSearch(heap5, 800);
    fresult << FibHeapDelete(heap5, x) << " ";
    fresult << InsertKey(heap5, 267) << " ";
    fresult << InsertKey(heap5, 351) << " ";
    x = ExtractMin(heap5);
    fresult << x->key << " ";
    x = FibHeapSearch(heap5, 478);
    FibHeapDecrease(heap5, x, 444);
    fresult << MINIMUM(heap5) << " ";
    x = FibHeapSearch(heap5, 559);
    FibHeapDecrease(heap5, x, 456);
    fresult << MINIMUM(heap5) << " ";
    x = FibHeapSearch(heap5, 929);
    fresult << FibHeapDelete(heap5, x) << endl;
    end = clock();
    ftime << long(end - start) / (CLOCKS_PER_SEC / 1000000) << "us" << endl;

    return 0;
}