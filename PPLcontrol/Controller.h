#pragma once

#include "RTCore.h"
#include "OffsetFinder.h"
#include "Utils.h"

typedef struct _CTRL_PROCESS_ENTRY
{
	ULONG_PTR KernelAddress;
	DWORD Pid;
	WORD ProtectionLevel;
	WORD SignerType;
} CTRL_PROCESS_ENTRY, *PCTRL_PROCESS_ENTRY;

typedef struct _CTRL_PROCESS_INFO
{
	DWORD NumberOfEntries;
	CTRL_PROCESS_ENTRY Entries[ANYSIZE_ARRAY];
} CTRL_PROCESS_INFO, *PCTRL_PROCESS_INFO;

class Controller
{
public:
	Controller();
	Controller(RTCore* rtc, OffsetFinder* of);
	BOOL ListProtectedProcesses();
	BOOL GetProcessProtection(DWORD Pid);
	BOOL SetProcessProtection(DWORD Pid, LPCWSTR ProtectionLevel, LPCWSTR SignerType);
	BOOL ProtectProcess(DWORD Pid, LPCWSTR ProtectionLevel, LPCWSTR SignerType);
	BOOL UnprotectProcess(DWORD Pid);

private:
	RTCore* _rtc;
	OffsetFinder* _of;

private:
	BOOL GetInitialSystemProcessAddress(PULONG_PTR Addr);
	BOOL GetProcessKernelAddress(DWORD Pid, PULONG_PTR Addr);
	BOOL GetProcessList(PCTRL_PROCESS_INFO *List);
	BOOL GetProcessProtection(ULONG_PTR Addr, PUCHAR Protection);
	BOOL SetProcessProtection(ULONG_PTR Addr, UCHAR Protection);
};