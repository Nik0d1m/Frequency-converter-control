#include "port.h";
#include <iostream>;

int main()
{
	Port a;
	a.open(L"COM6");
	a.setting();

	char data[] = "I am't furryeb";  // строка для передачи
	DWORD dwSize = sizeof(data);   // размер этой строки
	//LPDWORD dwBytesWritten;    // тут будет количество собственно переданных байт
	std::cout << dwSize << " Bytes in string. " << std::endl;

	a.write(data, dwSize);
	a.ReadCOM();

}
