#pragma once

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

struct DOS_Header
{
	const char Magic[2] = { 'M', 'Z' };
	
	uint16 LastSize = 0;
	uint16 BlockCount = 0;
	uint16 RelocCount = 0;
	uint16 HDRSize = 0;
	uint16 MinAlloc = 0;
	uint16 MaxAllloc = 0;
	uint16 SS = 0;
	uint16 SP = 0;
	uint16 CheckSum = 0;
	uint16 IP = 0;
	uint16 CS = 0;
	uint16 RelocPos = 0;
	uint16 Noverlay = 0;
	uint16 Reserved1[4] = { 0 };
	uint16 OEMId = 0;
	uint16 OEMInfo = 0;
	uint16 Reserved2[10] = { 0 };

	uint32 OffsetToPEHeader = 64;
};

struct PE_Header
{
	const char Magic[4] = { 'P', 'E', 0, 0 };
	/**
	 * \brief 0x8664 for AMD64.
	 */
	uint16 MachineType = 0;
	/**
	 * \brief The number of sections. This indicates the size of the section table, which immediately follows the headers.
	 */
	uint16 NumberOfSections = 0;
	uint32 TimeDateStamp = 0;
	/**
	 * \brief Not important for the loader.
	 */
	uint32 PointerToSymbolTable = 0;
	/**
	 * \brief Not important for the loader.
	 */
	uint32 NumberOfSymbols = 0;
	/**
	 * \brief The delta between the top of the Optional header and the start of the section table
	 */
	uint16 SizeOfOptionalHeader = 0;
	/**
	 * \brief Flags for image. 0x2 IMAGE_FILE_EXECUTABLE_IMAGE is required when Code is executed.
	 */
	uint16 Characteristics = 0;
};

/**
 * \brief https://docs.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-image_optional_header64
 */
struct OptionalHeader
{
	/**
	 * \brief Specifies the exact format of OptionalHeader. 0x10b for PE32(32 bit). 0x20b for PE32+(64 bit).
	 */
	const uint16 PEType = 0x20b;
	/**
	 * \brief Not important, can be 0. If LinkerVersion < 2.5, Microsoft AppLocker might wrongly report is not a valid Win32 application. (Exception from HRESULT: 0x800700C1) for no apparent reason. Changing these fields might fix the problem.
	 */
	uint8 MajorLinkerVersion = 0;
	/**
	 * \brief Not important, can be 0. If LinkerVersion < 2.5, Microsoft AppLocker might wrongly report is not a valid Win32 application. (Exception from HRESULT: 0x800700C1) for no apparent reason. Changing these fields might fix the problem.
	 */
	uint8 MinorLinkerVersion = 0;
	/**
	 * \brief Not important, can be 0.
	 */
	uint32 SizeOfCode = 0;
	/**
	 * \brief Not important, can be 0.
	 */
	uint32 SizeOfInitializedData = 0;
	/**
	 * \brief Not important, can be 0.
	 */
	uint32 SizeOfUnInitializedData = 0;
	/**
	 * \brief Under Windows 8, AddressOfEntryPoint is not allowed to be smaller than SizeOfHeaders, except if it's null.
	 */
	uint32 AddressOfEntryPoint = 0;
	/**
	 * \brief Not important, can be 0.
	 */
	uint32 BaseOfCode = 0;
	/**
	 * \brief Not important, can be 0.
	 */
	uint32 BaseOfData = 0;
	/**
	 * \brief Is a multiple of 10000h. Can be any value as long as ImageBase + 'SizeOfImage' < 80000000h. ImageBase can't collide with ntdll.dll or kernel32.
	 */
	uint64 ImageBase = 0;
	/**
	 * \brief Power of 2.
	 */
	uint32 SectionAlignment = 0;
	/**
	 * \brief Power of 2.
	 */
	uint32 FileAlignment = 0;
	/**
	 * \brief Not important, can be 0.
	 */
	uint16 MajorOperatingSystemVersion = 0;
	/**
	 * \brief Not important, can be 0.
	 */
	uint16 MinorOperatingSystemVersion = 0;
	/**
	 * \brief Not important, can be 0.
	 */
	uint16 MajorImageVersion = 0;
	/**
	 * \brief Not important, can be 0.
	 */
	uint16 MinorImageVersion = 0;
	/**
	 * \brief Has to be at least 3.10
	 */
	uint16 MajorSubsystemVersion = 0;
	/**
	 * \brief Has to be at least 3.10
	 */
	uint16 MinorSubsystemVersion = 0;
	const uint32 Win32Version = 0;
	/**
	 * \brief Normally equal the total virtual size of all sections + headers. The size of the image, in bytes, including all headers. Must be a multiple of SectionAlignment.
	 */
	uint32 ImageSize = 0;
	/**
	 * \brief Can be extended to the whole file, and sometimes be smaller than the header itself.
	 * The combined size of the following items, rounded to a multiple of the value specified in the FileAlignment member.
	 e_lfanew member of IMAGE_DOS_HEADER
		*4 byte signature
		*size of IMAGE_FILE_HEADER
		*size of optional header
		*size of all section headers
	 */
	uint32 SizeOfHeaders = 0;
	/**
	 * \brief Required for drivers only.
	 */
	uint32 CheckSum = 0;
	/**
	 * \brief Flags for subsystems.
	 */
	uint16 RequiredSubsystems = 0;
	uint16 DLLCharacteristics = 0;
	/**
	 * \brief Can be zero, but not any value.
	 */
	uint64 StackReserve = 0;
	/**
	 * \brief Can be zero, but not any value.
	 */
	uint64 StackCommit = 0;
	/**
	 * \brief Can be zero, but not any value.
	 */
	uint64 HeapReserve = 0;
	/**
	 * \brief Can be zero, but not any value.
	 */
	uint64 HeapCommit = 0;
	/**
	 * \brief This member is obsolete.
	 */
	const uint32 LoaderFlags = 0;
	/**
	 * \brief The number of directory entries in the remainder of the optional header. Each entry describes a location and size.
	 */
	uint32 NumberOfRVAAndSizes = 0;
};

struct Section
{
	char Name[8] = { 0 };
	/**
	 * \brief This section indicates the size of the section in memory.
	 */
	uint32 VirtualSize = 0;
	/**
	 * \brief The RVA of the section in memory. Using VirtualAddress and VirtualSize info. we can obtain the RVA of the next section, assuming that the memory alignment property is set to default. The address of the first byte of the section when loaded into memory, relative to the image base. For object files, this is the address of the first byte before relocation is applied.
	 */
	uint32 VirtualAddress = 0;
	/**
	 * \brief The size of the section (for object files) or the size of the initialized Data on disk (for image files). For executable images, this must be a multiple of FileAlignment from the optional header. If this is less than VirtualSize, the remainder of the section is zero-filled. Because the SizeOfRawData field is rounded but the VirtualSize field is not, it is possible for SizeOfRawData to be greater than VirtualSize as well. When a section contains only uninitialized Data, this field should be zero.
	 */
	uint32 SizeOfRawData = 0;
	/**
	 * \brief The file pointer to the first page of the section within the COFF file. For executable images, this must be a multiple of FileAlignment from the optional header. For object files, the value should be aligned on a 4-byte boundary for best performance. When a section contains only uninitialized Data, this field should be zero.
	 */
	uint32 PointerToRawData = 0;
	/**
	 * \brief A file pointer to the beginning of the relocation entries for the section. If there are no relocations, this value is zero.
	 */
	uint32 FilePointerToRelocationEntries = 0;
	/**
	 * \brief A file pointer to the beginning of the line-number entries for the section. If there are no COFF line numbers, this value is zero.
	 */
	uint32 PointerToLineNumbers = 0;
	/**
	 * \brief The number of relocation entries for the section. This value is zero for executable images.
	 */
	uint16 NumberOfRelocations = 0;
	/**
	 * \brief The number of line-number entries for the section. This value should be zero for an image because COFF debugging information is deprecated.
	 */
	uint16 NumberOfLineNumbers = 0;
	/**
	 * \brief The characteristics of the image. The following values are defined.
	 */
	uint32 Characteristics = 0;
};

struct ImageDataDirectory
{
	/**
	 * \brief The relative virtual address of the table.
	 */
	uint32 VirtualAddress = 0;
	/**
	 * \brief The size of the table, in bytes.
	 */
	uint32 Size = 0;
};