#pragma once
#include <array>

namespace nfsMW
{
	constexpr wchar_t processName[] = L"speed.exe";
	constexpr char nos[] = "nos";
	constexpr char cash[] = "cash";
	constexpr std::array<uint64_t, 5> offsetsNos = { 0xC, 0x4, 0x74, 0x14, 0xAC };
	constexpr std::array<uint64_t, 2> offsetsCash = { 0x10, 0xB4 };
	constexpr uint64_t moduleBaseOffsetNos = 0x52D378;
	constexpr uint64_t moduleBaseOffsetCash = 0x51CF90;
}