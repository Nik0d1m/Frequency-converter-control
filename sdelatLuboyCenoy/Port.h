#pragma once

#include <Windows.h>
#include <iostream>;

class Port
{
private:
	HANDLE hSerial;
public:

	Port();
	~Port();
	void open(LPCTSTR sPortName)
	{
		setlocale(LC_ALL, "RUS");
		hSerial = ::CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (hSerial == INVALID_HANDLE_VALUE)
		{
			if (GetLastError() == ERROR_FILE_NOT_FOUND)
			{
				std::cout << "последовательный порт не существует.\n";
			}
			std::cout << "произошла кака€-то друга€ ошибка.\n";
		}
		else
		{
			std::cout << "ѕорт открыт\n";
		}
	}

	void setting()
	{
		DCB dcbSerialParams = { 0 };
		dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
		if (!GetCommState(hSerial, &dcbSerialParams))
		{
			std::cerr << "ќшибка при получении состо€ни€ последовательного порта." << std::endl; // ќшибка при получении состо€ни€ последовательного порта.
		}
		else
		{
			dcbSerialParams.BaudRate = CBR_9600; // установите нужную скорость передачи
			dcbSerialParams.ByteSize = 8;
			dcbSerialParams.StopBits = ONESTOPBIT;
			dcbSerialParams.Parity = NOPARITY;
			if (!SetCommState(hSerial, &dcbSerialParams))
			{
				std::cerr << "ќшибка при настройке состо€ни€ последовательного порта." << std::endl; // 
			}
			else
			{
				std::cout << "ѕоследовательный порт успешно открыт." << std::endl; // 
			}
		}
	}

	void write(LPCVOID data,  DWORD dwSize)
	{
		BOOL iRet = WriteFile(hSerial, data, dwSize, NULL, NULL);
		std::cout << iRet;
	}

	void ReadCOM()
	{
		DWORD iSize;
		char sReceivedChar;
		while (true)
		{
			ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);  // получаем 1 байт
			if (iSize > 0)   // если что-то прин€то, выводим
				std::cout << sReceivedChar;
		}
	}
};

Port::Port()
{
}

Port::~Port()
{
}

