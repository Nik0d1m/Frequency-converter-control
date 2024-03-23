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
				std::cout << "���������������� ���� �� ����������.\n";
			}
			std::cout << "��������� �����-�� ������ ������.\n";
		}
		else
		{
			std::cout << "���� ������\n";
		}
	}

	void setting()
	{
		DCB dcbSerialParams = { 0 };
		dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
		if (!GetCommState(hSerial, &dcbSerialParams))
		{
			std::cerr << "������ ��� ��������� ��������� ����������������� �����." << std::endl; // ������ ��� ��������� ��������� ����������������� �����.
		}
		else
		{
			dcbSerialParams.BaudRate = CBR_9600; // ���������� ������ �������� ��������
			dcbSerialParams.ByteSize = 8;
			dcbSerialParams.StopBits = ONESTOPBIT;
			dcbSerialParams.Parity = NOPARITY;
			if (!SetCommState(hSerial, &dcbSerialParams))
			{
				std::cerr << "������ ��� ��������� ��������� ����������������� �����." << std::endl; // 
			}
			else
			{
				std::cout << "���������������� ���� ������� ������." << std::endl; // 
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
			ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);  // �������� 1 ����
			if (iSize > 0)   // ���� ���-�� �������, �������
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

