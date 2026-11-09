#include<stdio.h>
#include<stdlib.h>
#ifdef _WIN32
#include <Windows.h>
#endif
typedef int DataType;
struct Node {
    DataType data;        //数据域
    struct Node* next;    //指针域
};
typedef struct Node Node;
// 1. 初始化带头结点的单链表
Node* InitLinkList()
{
    Node* head = (Node*)malloc(sizeof(Node));
    if (head != NULL)
    {
        head->next = NULL;
    }
    return head;
}
// 2. 头插法建立单链表（插入一个节点）
int HeadInsert(Node* head, DataType data)
{
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL)
    {
        return 0;
    }
    p->data = data;
    p->next = head->next;
    head->next = p;
    return 1;
}
// 3. 尾插法建立单链表（插入一个节点）
int TailInsert(Node* head, DataType data)
{
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL)
    {
        return 0;
    }
    p->data = data;
    p->next = NULL;

    Node* r = head;
    while (r->next != NULL)
    {
        r = r->next;
    }
    r->next = p;
    return 1;
}
// 4. 判断链表是否为空，空返回1，非空返回0
int IsEmpty(Node* head)
{
    return head->next == NULL ? 1 : 0;
}
// 5. 计算链表长度
int GetLength(Node* head)
{
    Node* p = head->next;
    int len = 0;
    while (p != NULL)
    {
        len++;
        p = p->next;
    }
    return len;
}
// 6. 输出链表所有内容
void PrintLinkList(Node* head)
{
    Node* p = head->next;
    printf("链表元素：");
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Node* L = InitLinkList();
    // 头插测试
    printf("---头插法插入10、20---\n");
    HeadInsert(L, 10);
    HeadInsert(L, 20);
    PrintLinkList(L);
    printf("链表长度：%d\n", GetLength(L));
    if (IsEmpty(L))
        printf("链表状态：空\n");
    else
        printf("链表状态：非空\n\n");
    // 尾插测试
    printf("---尾插法插入30、40---\n");
    TailInsert(L, 30);
    TailInsert(L, 40);
    PrintLinkList(L);
    printf("链表长度：%d\n", GetLength(L));
    if (IsEmpty(L))
        printf("链表状态：空\n");
    else
        printf("链表状态：非空\n");
    return 0;
}