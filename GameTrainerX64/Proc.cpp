#include "Proc.h"

DWORD GetProcId(const LPCWSTR &procName) {

	DWORD procId = 0;
	HANDLE hProcSnap;

	// take a snapshot of all processes in the system.
	// returns INVALID_HANDLE_VALUE if it fails
	// exit if it fails
	hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (hProcSnap == INVALID_HANDLE_VALUE) {
		std::cerr << "CreateToolhelp32Snapshot (of processes) failed.\n";
		return FALSE;
	}
	
	PROCESSENTRY32 procEntry32; // set the size of structure before using it!
	procEntry32.dwSize = sizeof(procEntry32);

	// retrieve information about the first process.
	// returns 0 if it fails
	// exit if it fails
	if (!Process32First(hProcSnap, &procEntry32)) {
		std::cerr << "Process32First failed.\n";
		CloseHandle(hProcSnap);
		return FALSE;
	}
	
	// search for the right process
	do {
		// compare the current process name with our given process name
		// returns 0 if its identical
		// then stores the process id and breaks out of the loop
		if (!_wcsicmp(procEntry32.szExeFile, procName)) {
			// use std::wcout because procEntry32.szExeFile returns a WCHAR (wchar_t)
			std::wcout << "Found Process: " << procEntry32.szExeFile << std::endl;
			procId = procEntry32.th32ProcessID;
			break;
		}

	} while (Process32Next(hProcSnap, &procEntry32));

	CloseHandle(hProcSnap);
	return procId;

}

uint64_t GetModuleBaseAddress(DWORD &procId, const LPCWSTR &modName) {

	uint64_t modBaseAddress = 0x0;
	HANDLE hModSnap;

	// take a snapshot of all modules in the process.
	// returns INVALID_HANDLE_VALUE if it fails
	// exit if it fails
	hModSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hModSnap == INVALID_HANDLE_VALUE) {
		std::cerr << "CreateToolhelp32Snapshot (of modules) failed.\n";
		return FALSE;
	}
	
	MODULEENTRY32 modEntry32; // set the size of structure before using it!
	modEntry32.dwSize = sizeof(modEntry32);

	// retrieve information about the first module.
	// returns 0 if it fails
	// exit if it fails
	if (!Module32First(hModSnap, &modEntry32)) {
		std::cerr << "Module32First failed.\n";
		CloseHandle(hModSnap);
		return FALSE;
	}

	// search for the right module
	do {
		// compare the current module name with our given module name
		// returns 0 if its identical
		// then stores the moudle base address and breaks out of the loop
		if (!_wcsicmp(modEntry32.szModule, modName)) {
			// use std::wcout because procEntry32.szExeFile returns a WCHAR (wchar_t)
			std::wcout << "Found Module: " << modEntry32.szModule << std::endl;
			modBaseAddress = reinterpret_cast<uint64_t>(modEntry32.modBaseAddr);
			break;
		}

	} while (Module32Next(hModSnap, &modEntry32));

	CloseHandle(hModSnap);
	return modBaseAddress;
}

uint64_t GetDynamicMemoryAddress(HANDLE &hProc, uint64_t &baseAddress, std::vector<uint64_t> &offsets) {

	uint64_t address = baseAddress;

	for (auto offset : offsets) {
		ReadProcessMemory(hProc, LPCVOID(address), &address, sizeof(baseAddress), NULL);
		address += offset;
	}

	return address;
}
