// 项目名称：简单的通讯管理系统
#include<stdio.h>
#include<cstring>
#include<iostream>
#include<new>
#include<stdexcept>
#include<string>
#include<windows.h>
using namespace std;
struct Contact
{
	char name[20];// 姓名
	char phone[12];// 电话
	struct Birthday
	{
		int year;
		int month;
		int day;
	}birthday;
	int age;
};

void PrintContact(const Contact& contact)
{
	cout << "姓名：" << contact.name << endl
		<< "电话：" << contact.phone << endl
		<< "生日：" << contact.birthday.year << " - "
		<< contact.birthday.month << "-" << contact.birthday.day << endl
		<< "年龄：" << contact.age << endl;
}

bool IsValidDate(int year, int month, int day)
{
	if (year < 1 || month < 1 || month > 12 || day < 1)
	{
		return false;
	}

	const bool isLeapYear = year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
	const int daysInMonth[] = { 31, isLeapYear ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	return day <= daysInMonth[month - 1];
}

// 通讯录节点
struct Node
{
	Contact data;
	Node* next;
};

/* 初始化 */
Node* Initlist()
{
	Node* head = new (nothrow) Node;
	if (head == NULL)
	{
		return NULL;
	}
	head->next = NULL;
	return head;
}

// 头插法创建通讯录
bool CreatAddressBookHead(Node* head, Contact data)
{
	if (head == NULL)
	{
		cout << "通讯录未初始化！" << endl;
		return false;
	}
	Node* node = new (nothrow) Node;
	if (node == NULL)
	{
		cout << "内存分配失败！" << endl;
		return false;
	}
	node->data = data;
	node->next = head->next;
	head->next = node;
	return true;
}

// 尾插法创建通讯录
bool CreatAddressBookTail(Node* head, Contact data)
{
	if (head == NULL)
	{
		cout << "通讯录未初始化！" << endl;
		return false;
	}
	Node* node = new (nothrow) Node;
	if (node == NULL)
	{
		cout << "内存分配失败！" << endl;
		return false;
	}
	node->data = data;
	node->next = NULL;
	Node* p = head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = node;
	return true;
}

// 打印通讯录
bool PrintAddressBook(Node* head)
{
	if (head == NULL)
	{
		cout << "通讯录未初始化！" << endl;
		return false;
	}
	Node* p = head->next;
	if (p == NULL)
	{
		cout << "通讯录为空！" << endl;
		return false;
	}
	int position = 0;
	while (p != NULL)
	{
		cout << "\n第" << position << " 位联系人：" << endl;
		PrintContact(p->data);
		p = p->next;
		++position;
	}
	cout << "共" << position << " 位联系人。" << endl;
	return true;
}

// 查找联系人
bool FindContact(Node* head, const char* name)
{
	if (head == NULL || name == NULL || name[0] == '\0')
	{
		cout << "查找条件无效！" << endl;
		return false;
	}
	Node* p = head->next;
	while (p != NULL)
	{
		if (strcmp(p->data.name, name) == 0)
		{
			PrintContact(p->data);
			return true;
		}
		p = p->next;
	}
	cout << "未找到联系人！" << endl;
	return false;
}

// 修改联系人
bool ModifyContact(Node* head, const char* name, Contact newData)
{
	if (head == NULL || name == NULL || name[0] == '\0')
	{
		cout << "修改条件无效！" << endl;
		return false;
	}
	Node* p = head->next;
	while (p != NULL)
	{
		if (strcmp(p->data.name, name) == 0)
		{
			p->data = newData;
			cout << "修改成功！" << endl;
			return true;
		}
		p = p->next;
	}
	cout << "未找到联系人！" << endl;
	return false;
}

// 指定位置插入联系人
bool InsertContactAtPosition(Node* head, int position, Contact data)
{
	if (head == NULL || position < 0)
	{
		cout << "位置无效！" << endl;
		return false;
	}
	Node* p = head;
	for (int i = 0; i < position && p != NULL; i++)
	{
		p = p->next;
	}
	if (p == NULL)
	{
		cout << "位置无效！" << endl;
		return false;
	}
	Node* node = new (nothrow) Node;
	if (node == NULL)
	{
		cout << "内存分配失败！" << endl;
		return false;
	}
	node->data = data;
	node->next = p->next;
	p->next = node;
	return true;
}

// 删除联系人
bool DeleteContact(Node* head, const char* name)
{
	if (head == NULL || name == NULL || name[0] == '\0')
	{
		cout << "删除条件无效！" << endl;
		return false;
	}
	Node* p = head;
	while (p->next != NULL)
	{
		if (strcmp(p->next->data.name, name) == 0)
		{
			Node* temp = p->next;
			p->next = temp->next;
			delete temp;
			cout << "删除成功！" << endl;
			return true;
		}
		p = p->next;
	}
	cout << "未找到联系人！" << endl;
	return false;
}

// 释放通讯录
void FreeAddressBook(Node* head)
{
	Node* p = head;
	while (p != NULL)
	{
		Node* temp = p;
		p = p->next;
		delete temp;
	}
}

bool ReadInteger(const char* prompt, int& value)
{
	while (true)
	{
		cout << prompt;
		string line;
		if (!getline(cin, line))
		{
			return false;
		}
		try
		{
			size_t parsed = 0;
			int input = stoi(line, &parsed);
			if (parsed == line.size())
			{
				value = input;
				return true;
			}
		}
		catch (const invalid_argument&)
		{
		}
		catch (const out_of_range&)
		{
		}
		cout << "请输入有效整数。" << endl;
	}
}

bool ReadText(const char* prompt, char* buffer, size_t capacity)
{
	if (prompt == NULL || buffer == NULL || capacity < 2)
	{
		return false;
	}
	while (true)
	{
		cout << prompt;
		string text;
		if (!getline(cin, text))
		{
			return false;
		}
		if (!text.empty() && text.size() < capacity)
		{
			memcpy(buffer, text.c_str(), text.size() + 1);
			return true;
		}
		cout << "内容不能为空，且长度不能超过 " << capacity - 1 << " 个字节。" << endl;
	}
}

bool ReadContact(Contact& contact)
{
	if (!ReadText("姓名：", contact.name, sizeof(contact.name)) ||
		!ReadText("电话：", contact.phone, sizeof(contact.phone)) ||
		!ReadInteger("出生年份：", contact.birthday.year) ||
		!ReadInteger("出生月份：", contact.birthday.month) ||
		!ReadInteger("出生日期：", contact.birthday.day) ||
		!ReadInteger("年龄：", contact.age))
	{
		return false;
	}
	if (!IsValidDate(contact.birthday.year, contact.birthday.month, contact.birthday.day) ||
		contact.age < 0 || contact.age > 150)
	{
		cout << "生日或年龄不合法，请重新操作。" << endl;
		return false;
	}
	return true;
}

// 主函数
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	Node* head = Initlist();
	if (head == NULL)
	{
		cout << "初始化失败！" << endl;
		return 1;
	}

	bool running = true;
	while (running)
	{
		cout << "\n===== 通讯录管理系统 =====\n"
			<< "1. 添加联系人\n"
			<< "2. 显示所有联系人\n"
			<< "3. 查找联系人\n"
			<< "4. 修改联系人\n"
			<< "5. 删除联系人\n"
			<< "6. 按位置插入联系人\n"
			<< "0. 退出系统\n";
		int choice;
		if (!ReadInteger("请选择操作：", choice))
		{
			break;
		}

		char name[20]{};
		Contact contact{};
		switch (choice)
		{
		case 1:
			if (ReadContact(contact))
			{
				CreatAddressBookTail(head, contact);
			}
			break;
		case 2:
			PrintAddressBook(head);
			break;
		case 3:
			if (ReadText("请输入要查找的姓名：", name, sizeof(name)))
			{
				FindContact(head, name);
			}
			break;
		case 4:
			if (ReadText("请输入要修改的联系人姓名：", name, sizeof(name)) && ReadContact(contact))
			{
				ModifyContact(head, name, contact);
			}
			break;
		case 5:
			if (ReadText("请输入要删除的联系人姓名：", name, sizeof(name)))
			{
				DeleteContact(head, name);
			}
			break;
		case 6:
		{
			int position;
			if (!ReadInteger("请输入插入位置（从 0 开始）：", position))
			{
				running = false;
				break;
			}
			if (ReadContact(contact))
			{
				InsertContactAtPosition(head, position, contact);
			}
			break;
		}
		case 0:
			running = false;
			break;
		default:
			cout << "无效选项，请重新选择。" << endl;
			break;
		}
	}

	FreeAddressBook(head);
	cout << "通讯录已关闭。" << endl;
	return 0;
}
