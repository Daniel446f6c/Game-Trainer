#pragma once
#include <Windows.h> // ReadProcessMemory() , WriteProcessMemory()
#include <TlHelp32.h> // CreateToolhelp32Snapshot() , PROCESSENTRY32 , MODULEENTRY32
#include <string> // _wcsicmp()
#include <vector> // std::vector<>
#include <map> // std::map<>
#include <iostream> // standard input output stream
#include <array> // std::array<>

// Get the Process Identifier
// return: 0 if not found
DWORD GetProcId(const LPCWSTR &procName);

// Get a Modules Base Address
// return: 0 if not found
uint64_t GetModuleBaseAddress(DWORD &procId, const LPCWSTR &moduleName);

// Get a Address from Base Address + Offsets
uint64_t GetDynamicMemoryAddress(HANDLE &hProc, uint64_t &baseAddress, std::vector<uint64_t> &offsets);


// Data-Struct to save a process's ID, Name, Base Adresses of Modules
struct ProcInfo
{
	DWORD id = 0;
	HANDLE handle = nullptr;
	uint64_t moduleBaseAddress = 0;
	const wchar_t* name = L"";
	const wchar_t* moduleName = L"";
	std::map<std::string, uint64_t> Addresses;
};
