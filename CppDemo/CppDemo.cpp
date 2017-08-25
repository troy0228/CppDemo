// CppDemo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include<cstdlib>
#include <windows.h>
#include <fstream>
using namespace std;
typedef double(*Func)();

int countRun = 0;//ͳ�Ƴ���ִ�д���
int countSuccess = 0;//ͳ�Ƴɹ����ô���

int _tmain(int argc, _TCHAR* argv[])
{
	LARGE_INTEGER freq;
	LARGE_INTEGER start;
	LARGE_INTEGER end;
	ofstream outfile;
	outfile.open("D:\\myFileCpp.txt");
loop:
	countRun++;
	///��ʼ����
	cout << "start " << countRun << " test..." << endl;

	QueryPerformanceFrequency(&freq);

	QueryPerformanceCounter(&start);

	HMODULE hDll = LoadLibrary(_T("D:\\documents\\Visual Studio 2013\\Projects\\nativeDLL\\x64\\Debug\\nativeDLL.dll"));
	if (hDll != NULL)
	{
		Func ntvMethod = (Func)GetProcAddress(hDll, "Java_bingcao_TestJNI_nativeMethod");
		if (ntvMethod != NULL)
		{
			countSuccess++;
			cout << ntvMethod() << endl;
			cout << "C++ success call dll" << endl;
		}
		FreeLibrary(hDll);
	}
	else
		cout << "Cannot load the DLLDemo!" << endl;

	QueryPerformanceCounter(&end);

	double druation = ((double)(end.QuadPart - start.QuadPart)) / ((double)freq.QuadPart);
	cout << "Program run druation: " << druation * 1000 << " ms." << endl << endl;
	outfile << druation * 1000 << endl;
	
	if (countRun < 10)
	{
		goto loop;
	}
	
	outfile.close();
	return 0;
}