#include "port.h";
#include <iostream>;

int main()
{
	Port a;
	a.open(L"COM6");
	a.setting();

	char data[] = "I am't furryeb";  // ������ ��� ��������
	DWORD dwSize = sizeof(data);   // ������ ���� ������
	//LPDWORD dwBytesWritten;    // ��� ����� ���������� ���������� ���������� ����
	std::cout << dwSize << " Bytes in string. " << std::endl;

	a.write(data, dwSize);
	a.ReadCOM();

}
