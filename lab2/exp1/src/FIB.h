//斐波那契结点
struct FibNode
{
    int key;         // 关键字(键值)
    int degree;      // 度数
    FibNode *left;   // 左兄弟
    FibNode *right;  // 右兄弟
    FibNode *child;  // 第一个孩子节点
    FibNode *parent; // 父节点
    bool marked;     // 是否被删除第一个孩子
};

//斐波那契堆
struct FibHeap
{
    int keyNum;     //堆中结点个数
    int maxDegree;  //最大度
    FibNode *min;   //最小堆，根结点
    FibNode **cons; //指向最大度的内存区域
};
//初始化一个空的FibHeap
FibHeap *FibHeapMake();

//初始化一个空的FibNode
FibNode *FibNodeMake();

// 将node从双链表移除
void RemoveNode(FibNode *node);

// 将双向链表b链接到双向链表a的后面
void AddNode(FibNode *a, FibNode *b);

//结点node插入FibHeap中
int InsertNode(FibHeap *heap, FibNode *node);

//将值插入FibHeap
int InsertKey(FibHeap *heap, int key);

//将数组内值插入Fibonacci Heap
void InsertKeys(FibHeap *heap, int keys[], int keyNum);

//返回 heap最小值
int MINIMUM(FibHeap *heap);

//移除最小结点
FibNode *RemoveMin(FibHeap *heap);

//开辟FpConsolidate函数哈希所用空间
void FibConsMake(FibHeap *heap);

//将x根结点链接到y根结点
void FibHeapLink(FibHeap *heap, FibNode *x, FibNode *y);

//合并左右相同度数的二项树
void FibHeapConsolidate(FibHeap *heap);

//抽取最小结点
FibNode *ExtractMin(FibHeap *heap);

//修改度数
void renewDegree(FibNode *parent, int degree);

//切断x与父节点y之间的链接，使x成为一个根
void FibHeapCut(FibHeap *heap, FibNode *x, FibNode *y);

//级联剪切
void CascadingCut(FibHeap *heap, FibNode *y);

//减小一个关键字
void FibHeapDecrease(FibHeap *heap, FibNode *x, int key);

//删除结点
int FibHeapDelete(FibHeap *heap, FibNode *x);

//递归搜索
FibNode *FibNodeSearch(FibNode *x, int key);

//堆内搜索关键字
FibNode *FibHeapSearch(FibHeap *heap, int key);

//销毁堆
void FibHeapDestory(FibHeap *heap);

//合并堆
FibHeap *FibHeapUnion(FibHeap *heap1, FibHeap *heap2);
