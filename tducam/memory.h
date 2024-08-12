
#include <windows.h>
#include <stdio.h>

HWND hWin = NULL;
DWORD pid = NULL;
DWORD old = NULL;
DWORD oldsafe = NULL;
HANDLE hProcess = NULL;

HANDLE hProcessSafe = NULL;

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
const DWORD accessflag = PROCESS_ALL_ACCESS;//PROCESS_VM_READ || PROCESS_VM_WRITE;
bool didfs = false;
DWORD fsresult = 0;

HWND GetWindowHandle(DWORD tPID)
{
	//Get first window handle
	HWND res = FindWindow(NULL,NULL);
	DWORD mPID = NULL;
	while(res != 0)
	{
		if(!GetParent(res))
		{
			GetWindowThreadProcessId(res,&mPID);
			if (mPID == tPID)
				return res;
		}
		res = GetWindow(res, GW_HWNDNEXT);
	}

	return 0;
}

void GetID(char * name)
{
	hWin = ::FindWindowA(name, NULL);
	::GetWindowThreadProcessId(hWin, &pid);

	if (hWin == 0) didfs = false;

}

char * GetString( DWORD address, DWORD length)
{
	char * result = new char[length];
	hProcess = ::OpenProcess(accessflag, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, length, PAGE_EXECUTE_READWRITE, &old);
	::ReadProcessMemory(hProcess, (LPVOID)address, result, length, 0);
	::CloseHandle(hProcess);
	return result;
}

void SetString(DWORD address, char * value)
{
	DWORD length = strlen(value);
	hProcess = ::OpenProcess(accessflag, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, length, PAGE_EXECUTE_READWRITE, &old);
	::WriteProcessMemory(hProcess, (LPVOID)address, value, length, 0);
	::CloseHandle(hProcess);
}

float GetFloat(DWORD address)
{
	float result = NULL;
	hProcess = ::OpenProcess(accessflag, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, 4, PAGE_EXECUTE_READWRITE, &old);
	::ReadProcessMemory(hProcess, (LPVOID)address, &result, 4, 0);
	::CloseHandle(hProcess);
	return result;
}
void SetFloat(DWORD address, float value)
{
	hProcess = ::OpenProcess(accessflag, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, 4, PAGE_EXECUTE_READWRITE, &old);
	::WriteProcessMemory(hProcess, (LPVOID)address, &value, 4, 0);
	::CloseHandle(hProcess);
}
void OpenProcessSafe()
{
	hProcessSafe = ::OpenProcess(accessflag, FALSE, (DWORD)pid);
}
void CloseProcessSafe()
{
	::CloseHandle(hProcessSafe);
}
void SetFloatSafe(DWORD address, float value)
{
	::VirtualProtectEx(hProcessSafe, (LPVOID)address, 4, PAGE_EXECUTE_READWRITE, &oldsafe);
	::WriteProcessMemory(hProcessSafe, (LPVOID)address, &value, 4, 0);
}
BYTE GetByte(DWORD address)
{
	BYTE result = NULL;
	hProcess = ::OpenProcess(accessflag, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, 1, PAGE_EXECUTE_READWRITE, &old);
	::ReadProcessMemory(hProcess, (LPVOID)address, &result, 1, 0);
	::CloseHandle(hProcess);
	return result;
}
void GetBytes(DWORD address, BYTE * value, DWORD length)
{
	hProcess = ::OpenProcess(accessflag, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, length, PAGE_EXECUTE_READWRITE, &old);
	::ReadProcessMemory(hProcess, (LPVOID)address, value, length, 0);
	::CloseHandle(hProcess);
}
void SetByte(DWORD address, BYTE value)
{
	hProcess = ::OpenProcess(accessflag, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, 1, PAGE_EXECUTE_READWRITE, &old);
	::WriteProcessMemory(hProcess, (LPVOID)address, &value, 1, 0);
	::CloseHandle(hProcess);
}
void SetByteSafe(DWORD address, BYTE value)
{
	::VirtualProtectEx(hProcessSafe, (LPVOID)address, 1, PAGE_EXECUTE_READWRITE, &oldsafe);
	::WriteProcessMemory(hProcessSafe, (LPVOID)address, &value, 1, 0);
}
void SetBytes(DWORD address, BYTE * value, DWORD length)
{
	hProcess = ::OpenProcess(accessflag, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, length,PAGE_EXECUTE_READWRITE, &old);
	::WriteProcessMemory(hProcess, (LPVOID)address, value, length, 0);
	::CloseHandle(hProcess);
}
void SetBytesSafe(DWORD address, BYTE * value, DWORD length)
{
	::VirtualProtectEx(hProcessSafe, (LPVOID)address, length,PAGE_EXECUTE_READWRITE, &oldsafe);
	::WriteProcessMemory(hProcessSafe, (LPVOID)address, value, length, 0);
}
DWORD GetLong(DWORD address)
{
	DWORD result = NULL;
	hProcess = ::OpenProcess(accessflag, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, 4, PAGE_EXECUTE_READWRITE, &old);
	::ReadProcessMemory(hProcess, (LPVOID)address, &result, 4, 0);
	::CloseHandle(hProcess);
	return result;
}	
DWORD GetLongSafe(DWORD address)
{
	DWORD result = NULL;
	::VirtualProtectEx(hProcessSafe, (LPVOID)address, 4, PAGE_EXECUTE_READWRITE, &oldsafe);
	::ReadProcessMemory(hProcessSafe, (LPVOID)address, &result, 4, 0);
	return result;
}	
void SetLong(DWORD address, DWORD value)
{
	hProcess = ::OpenProcess(accessflag, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, 4, PAGE_EXECUTE_READWRITE, &old);
	::WriteProcessMemory(hProcess, (LPVOID)address, &value, 4, 0);
	::CloseHandle(hProcess);
}

BYTE   * HexToBytes(char * value,  DWORD * length)
{

	int abytecount = strlen(value)/2;

	BYTE * byteArray = new BYTE[abytecount];

	char * separator;

	char token[4];

	for (int bx = 0; bx < abytecount; bx ++)
	{		
		token[0] = value[bx*2 +0];
		token[1] = value[bx*2 +1];
		token[2] = 0x58;
		token[3] = 0;
		int i = (BYTE)strtol( (char *)token, &separator, 16);
		byteArray[bx] = (BYTE) i;
	}

	
	*length =  abytecount; 
	
	return byteArray;
}

void SetHex(DWORD address, char * value)
{
	DWORD length = 0;
	BYTE * result = HexToBytes(value,&length);
	
	hProcess = ::OpenProcess(accessflag, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, length, PAGE_EXECUTE_READWRITE, &old);
	::WriteProcessMemory(hProcess, (LPVOID)address, result, length, 0);
	::CloseHandle(hProcess);
	delete[] result;
}

void SetCall(DWORD address, DWORD calladdress )
{
	DWORD endaddress = address + 5;
	DWORD waddress = calladdress - endaddress;
	
	BYTE * bytearray = new BYTE[5];
	bytearray[0] = 0xE8;
	memcpy(bytearray+1,&waddress,4);
	
	SetBytes(address, bytearray,5);

	delete[] bytearray;
}
void SetJump(DWORD address, DWORD calladdress )
{
	DWORD endaddress = address + 5;
	DWORD waddress = calladdress - endaddress;
	
	BYTE * bytearray = new BYTE[5];
	bytearray[0] = 0xE9;
	memcpy(bytearray+1,&waddress,4);
	
	SetBytes(address, bytearray,5);

	delete[] bytearray;
}
DWORD memmem(char * buf, char * pattern, DWORD buflen, DWORD len)
{
	DWORD i, j;
	char * bf = buf;
	char * pt = pattern;
	if (len > buflen) return 0;
	for (i = 0; i <= (buflen - len); ++i)
	{
		for (j = 0; j < len; ++j)
		{
			if (pt[j] != bf[i + j]){
				break;}
		}
		if (j == len) {
			return (i);}
	}

	return 0;
}

BOOL EnableTokenPrivilege(LPTSTR privilege)

{

     HANDLE         hToken;

    TOKEN_PRIVILEGES tp;

     DWORD   dwSize;             



    ZeroMemory(&tp, sizeof(tp));

    tp.PrivilegeCount = 1;



     if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken))

        return false;

   

    if(!LookupPrivilegeValue(NULL, privilege, &tp.Privileges[0].Luid))

    {

        CloseHandle(hToken);

        return false;

    }

   

    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;



    if(!AdjustTokenPrivileges(hToken, FALSE, &tp, 0, NULL, &dwSize))

    {

        CloseHandle(hToken);

        return false;

    }



    CloseHandle(hToken);

    return true;

}

DWORD FutureScan(void)
{
	//variables
	const DWORD startoffset = 0x400000;
	const DWORD endoffset = 0xf00000;
	const DWORD length = endoffset - startoffset;

	//check if we scanned already
	if(didfs==true) return fsresult;
	didfs = true;

	char searchkey[] = {(char)0x8B, (char)0x88, (char)0x20, (char)0x04, (char)0x00, (char)0x00, (char)0x8B, (char)0x81, (char)0xE8, 
						(char)0x02, (char)0x00, (char)0x00, (char)0x83, (char)0xC0, (char)0xFA, (char)0x83, (char)0xF8, (char)0x27};
	
	char * cbuffer = new char[length];




	//load buffer
	EnableTokenPrivilege(SE_DEBUG_NAME);
	hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (DWORD*)startoffset, length, PAGE_EXECUTE_READWRITE, &old);
	DWORD bcopy=0;
	::ReadProcessMemory(hProcess,(DWORD*)startoffset, cbuffer, length, &bcopy);

	::CloseHandle(hProcess);

	//scan
	fsresult = memmem(cbuffer, searchkey, length, 18)+startoffset-4;

	//delete buffer
	delete[] cbuffer;

	//the offset we need is written here
	return fsresult;

}




void SaveAll(char * arr)
{
	//fstream ofs;
	//ofs.open(" ");
	//ofs.write((char*)arr,512);

}
