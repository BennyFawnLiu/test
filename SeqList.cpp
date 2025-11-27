#include <iostream>
using namespace std;

// 顺序表的最大容量
#define MAXSIZE 100

// 自定义数据类型（这里用int举例，也可以是其他类型）
struct ElemType
{
    int value; // 数据域，存储整数
};

// 顺序表的结构定义
struct SqList
{
    ElemType *elem; // 指向存储元素的数组（动态分配）
    int length;     // 当前顺序表的实际长度
};

// 1. 初始化顺序表
bool InitList(SqList &L)
{
    // 动态分配内存
    L.elem = new ElemType[MAXSIZE];
    if (!L.elem) // 内存分配失败
        return false;
    L.length = 0; // 初始长度为0
    return true;
}

// 2. 销毁顺序表
void DestroyList(SqList &L)
{
    if (L.elem)
        delete[] L.elem; // 释放动态数组
    L.length = 0;
}

// 3. 插入元素（在第pos个位置插入元素e，pos从1开始）
bool ListInsert(SqList &L, int pos, ElemType e)
{
    // 检查位置合法性
    if (pos < 1 || pos > L.length + 1)
        return false;
    // 检查是否已满
    if (L.length >= MAXSIZE)
        return false;

    // 从后往前移动元素，腾出位置
    for (int i = L.length; i >= pos; i--)
        L.elem[i] = L.elem[i - 1];

    // 插入新元素
    L.elem[pos - 1] = e;
    L.length++; // 长度加1
    return true;
}

// 4. 删除元素（删除第pos个位置的元素，并用e返回其值）
bool ListDelete(SqList &L, int pos, ElemType &e)
{
    // 检查位置合法性
    if (pos < 1 || pos > L.length)
        return false;

    // 保存被删除的元素
    e = L.elem[pos - 1];

    // 从前往后移动元素，覆盖被删除位置
    for (int i = pos; i < L.length; i++)
        L.elem[i - 1] = L.elem[i];

    L.length--; // 长度减1
    return true;
}

// 5. 遍历顺序表
void TraverseList(SqList L)
{
    for (int i = 0; i < L.length; i++)
        cout << L.elem[i].value << " ";
    cout << endl;
}

int main()
{
    SqList L;

    // 初始化顺序表
    if (InitList(L))
        cout << "顺序表初始化成功！" << endl;

    // 插入元素
    ElemType e1 = {10}, e2 = {20}, e3 = {30};
    ListInsert(L, 1, e1); // 第1位插入10
    ListInsert(L, 2, e2); // 第2位插入20
    ListInsert(L, 3, e3); // 第3位插入30
    cout << "插入元素后：";
    TraverseList(L); // 输出：10 20 30

    // 删除元素
    ElemType del_e;
    ListDelete(L, 2, del_e); // 删除第2位元素
    cout << "删除第2位元素后:";
    TraverseList(L);                                   // 输出：10 30
    cout << "被删除的元素值：" << del_e.value << endl; // 输出：20

    // 销毁顺序表
    DestroyList(L);

    return 0;
}