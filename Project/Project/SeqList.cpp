#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <Windows.h>
#endif

#define INIT_SIZE 12
#define INCREMENT 1

typedef int ElemType;

typedef struct {
    ElemType* elem;
    int length;
    int listsize;
} SqList;

// 1. 初始化动态顺序表
int InitList_sq(SqList* L)
{
    L->elem = (ElemType*)malloc(INIT_SIZE * sizeof(ElemType));
    if (!L->elem)
        return 0;   // 分配失败
    L->length = 0;
    L->listsize = INIT_SIZE;
    return 1;
}

// 扩容函数（插入空间不足时调用）
int IncreaseSize(SqList* L)
{
    ElemType* newbase = (ElemType*)realloc(L->elem, (L->listsize + INCREMENT) * sizeof(ElemType));
    if (!newbase)
        return 0;
    L->elem = newbase;
    L->listsize += INCREMENT;
    return 1;
}

// 2. 创建顺序表，输入n个元素
int CreateList(SqList* L, int n)
{
    if (n < 0)
        return 0;
    // 空间不够先扩容
    while (L->listsize < n)
    {
        if (!IncreaseSize(L))
            return 0;
    }
    printf("请输入%d个元素：", n);
    int i;
    for (i = 0; i < n; i++)
    {
        scanf_s("%d", &L->elem[i]);
    }
    L->length = n;
    return 1;
}

// 3. 判断是否为空：空返回1，非空返回0
int IsEmpty(SqList* L)
{
    return L->length == 0;
}

// 4. 获取顺序表长度
int SqList_length(SqList* L)
{
    return L->length;
}

// 5. 打印顺序表
void PrintList(SqList* L)
{
    if (L->length == 0)
    {
        printf("顺序表为空!\n");
        return;
    }
    int i;
    for (i = 0; i < L->length; i++)
    {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
}

// 6. 获取指定位置元素（下标从0开始）
int SqList_Position(SqList* L, int position, int* e)
{
    if (position < 0 || position >= L->length)
        return 0;
    *e = L->elem[position];
    return 1;
}

// 7.1 顺序查找，返回下标；找不到返回-1
int SqList_Check1(SqList* L, int value)
{
    int i = 0;
    while (i < L->length && L->elem[i] != value)
    {
        i++;
    }
    if (i < L->length && L->elem[i] == value)
        return i;
    else
        return -1;
}

// 7.2 二分查找（前提：表内元素升序有序，返回下标，找不到-1）
int SqList_Check2(SqList* L, int value)
{
    int low = 0, high = L->length - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (L->elem[mid] == value)
            return mid;
        else if (L->elem[mid] < value)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// 8. 在pos下标前插入x（下标0开始）
int SqList_Insert(SqList* L, int pos, ElemType x)
{
    if (pos < 0 || pos > L->length)
        return 0;
    if (L->length >= L->listsize)
    {
        if (!IncreaseSize(L))
            return 0;
    }
    // 元素后移
    int i;
    for (i = L->length; i > pos; i--)
    {
        L->elem[i] = L->elem[i - 1];
    }
    L->elem[pos] = x;
    L->length++;
    return 1;
}

// 9. 删除指定下标pos的元素
int SqList_DelPos(SqList* L, int pos, ElemType* e)
{
    if (pos < 0 || pos >= L->length)
        return 0;
    *e = L->elem[pos];
    int i;
    for (i = pos; i < L->length - 1; i++)
    {
        L->elem[i] = L->elem[i + 1];
    }
    L->length--;
    return 1;
}

//10. 删除所有等于value的元素
void SqList_DelAllVal(SqList* L, int value)
{
    int j = 0;
    int i;
    for (i = 0; i < L->length; i++)
    {
        if (L->elem[i] != value)
        {
            L->elem[j++] = L->elem[i];
        }
    }
    L->length = j;
}

// 释放动态内存（重要！防止内存泄漏）
void DestroyList(SqList* L)
{
    free(L->elem);
    L->elem = NULL;
    L->length = 0;
    L->listsize = 0;
}

// 主函数测试菜单
int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    SqList L;
    if (!InitList_sq(&L))
    {
        printf("顺序表初始化失败\n");
        return 1;
    }

    int op, n, pos, x, e, val, res;
    while (1)
    {
        printf("\n====动态顺序表菜单====\n");
        printf("1.创建顺序表  2.判空  3.求长度  4.打印\n");
        printf("5.按下标取元素 6.顺序查找 7.二分查找\n");
        printf("8.插入元素    9.按下标删除 10.删除全部等值 0.退出\n");
        printf("请选择：");
        if (scanf_s("%d", &op) != 1)
        {
            printf("输入无效，请输入数字\n");
            while (getchar() != '\n' && !feof(stdin))
            {
            }
            continue;
        }
        switch (op)
        {
        case 1:
            printf("输入元素个数：");
            scanf_s("%d", &n);
            if (CreateList(&L, n))
                printf("创建成功\n");
            else
                printf("创建失败\n");
            break;
        case 2:
            if (IsEmpty(&L))
                printf("顺序表为空\n");
            else
                printf("顺序表非空\n");
            break;
        case 3:
            printf("长度 = %d\n", SqList_length(&L));
            break;
        case 4:
            PrintList(&L);
            break;
        case 5:
            printf("输入下标：");
            scanf_s("%d", &pos);
            if (SqList_Position(&L, pos, &e))
                printf("该下标元素：%d\n", e);
            else
                printf("下标非法\n");
            break;
        case 6:
            printf("查找值：");
            scanf_s("%d", &val);
            res = SqList_Check1(&L, val);
            if (res != -1)
                printf("顺序查找：下标%d\n", res);
            else
                printf("未找到\n");
            break;
        case 7:
            printf("查找值：");
            scanf_s("%d", &val);
            res = SqList_Check2(&L, val);
            if (res != -1)
                printf("二分查找：下标%d\n", res);
            else
                printf("未找到或表无序\n");
            break;
        case 8:
            printf("插入下标、插入值：");
            scanf_s("%d%d", &pos, &x);
            if (SqList_Insert(&L, pos, x))
                printf("插入成功\n");
            else
                printf("插入失败\n");
            break;
        case 9:
            printf("删除下标：");
            scanf_s("%d", &pos);
            if (SqList_DelPos(&L, pos, &e))
                printf("删除元素：%d\n", e);
            else
                printf("删除失败\n");
            break;
        case 10:
            printf("删除所有等于：");
            scanf_s("%d", &val);
            SqList_DelAllVal(&L, val);
            printf("已清理所有%d\n", val);
            break;
        case 0:
            DestroyList(&L);
            printf("程序退出，内存释放完毕\n");
            return 0;
        }
    }
}
