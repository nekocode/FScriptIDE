#include <Windows.h>

int main()
{
	HWND hwnd;
	if(hwnd=FindWindow(L"Notepad++",NULL))
	{
		PostMessage(hwnd,WM_SYSKEYDOWN,VK_F6,0);
	}
	if(hwnd=FindWindow(L"fs",NULL),hwnd==0)
	{
		int i2=0;
		wchar_t szbufPath[MAX_PATH];
		wchar_t CurrentPath[MAX_PATH];
		GetModuleFileName(NULL,CurrentPath,MAX_PATH);
		GetLongPathName(szbufPath,CurrentPath,MAX_PATH);
		for(int i=wcslen(CurrentPath);i>=0;i--)
		{
			if(CurrentPath[i]=='\\')
				i2++;
			if(i2==2)
			{
				CurrentPath[i+1]='d';
				CurrentPath[i+2]='x';
				CurrentPath[i+3]='t';
				CurrentPath[i+4]='e';
				CurrentPath[i+5]='s';
				CurrentPath[i+6]='t';
				CurrentPath[i+7]='.';
				CurrentPath[i+8]='e';
				CurrentPath[i+9]='x';
				CurrentPath[i+10]='e';
				CurrentPath[i+11]='\0';
				break;
			}
		}

		ShellExecute(NULL,L"open",CurrentPath,NULL,L"",SW_SHOWNORMAL);
	}
	return 0;
}