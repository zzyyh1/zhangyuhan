#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <string>
using namespace std;
//初始化栈结构体//
typedef wchar_t DataType;
struct LinkStackNode
{
	DataType data;
	LinkStackNode* next;
};
//初始化空栈//
void InitStack(LinkStackNode*& top)
{
	top = NULL;
}
//判断栈是否为空//
bool IsEmpty(LinkStackNode* top)
{
	return top == NULL;
}
//入栈//
void Push(LinkStackNode*& top, DataType x)
{
	LinkStackNode* newNode = new LinkStackNode;
	newNode->data = x;
	newNode->next = top;
	top = newNode;
}
//出栈//
bool Pop(LinkStackNode*& top, DataType& x)
{
	if (IsEmpty(top))
	{
		return false;
	}

	LinkStackNode* node = top;
	x = node->data;
	top = node->next;
	delete node;
	return true;
}

//获取栈顶元素//
bool GetTop(LinkStackNode* top, DataType& x)
{
	if (IsEmpty(top))
	{
		return false;
	}

	x = top->data;
	return true;
}

//释放栈中所有结点//
void ClearStack(LinkStackNode*& top)
{
	DataType x;
	while (Pop(top, x))
	{
	}
}

//判断括号字符串是否有效//
bool IsValidBrackets(const wstring& brackets)
{
	LinkStackNode* top;
	InitStack(top);

	for (wchar_t bracket : brackets)
	{
		if (bracket == '(' || bracket == '{' || bracket == '[')
		{
			Push(top, bracket);
		}
		else if (bracket == ')' || bracket == '}' || bracket == ']')
		{
			DataType leftBracket;
			if (!Pop(top, leftBracket))
			{
				return false;
			}

			if ((leftBracket == '(' && bracket != ')') ||
				(leftBracket == '{' && bracket != '}') ||
				(leftBracket == '[' && bracket != ']'))
			{
				ClearStack(top);
				return false;
			}
		}
		else
		{
			ClearStack(top);
			return false;
		}
	}

	bool valid = IsEmpty(top);
	ClearStack(top);
	return valid;
}

//主函数//
int main()
{
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);

	wstring brackets;

	wcout << L"请输入第一个括号字符串：";
	wcin >> brackets;
	wcout << brackets << (IsValidBrackets(brackets) ? L" 是有效字符串" : L" 不是有效字符串") << endl;

	wcout << L"请输入第二个括号字符串：";
	wcin >> brackets;
	wcout << brackets << (IsValidBrackets(brackets) ? L" 是有效字符串" : L" 不是有效字符串") << endl;

	return 0;
}