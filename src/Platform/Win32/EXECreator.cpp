#include "EXECreator.h"

#include "WindowsHeaders.h"

#include "../../Buffer.h"

void EXECreator::CreateEXE(const CreateEXEInfo& createExeInfo)
{
	{
		DOS_Header dos_header;
		createExeInfo.OutputFile->write(reinterpret_cast<char*>(&dos_header), sizeof(DOS_Header));
	}
		
	PE_Header pe_header;
	pe_header.Characteristics = 0x0002;
	pe_header.MachineType = 0x8664;
	pe_header.NumberOfSections;
	pe_header.SizeOfOptionalHeader;
	createExeInfo.OutputFile->write(reinterpret_cast<char*>(&pe_header), sizeof(PE_Header));

	OptionalHeader optional_header;
	optional_header.AddressOfEntryPoint;
	optional_header.FileAlignment;
	optional_header.ImageBase;
	optional_header.ImageSize;
	optional_header.MajorSubsystemVersion;
	optional_header.MinorSubsystemVersion;
	optional_header.RequiredSubsystems;
	optional_header.SizeOfHeaders;
	optional_header.NumberOfRVAAndSizes;
	createExeInfo.OutputFile->write(reinterpret_cast<char*>(&optional_header), sizeof(optional_header));

	std::vector<ImageDataDirectory> data_directories;
	createExeInfo.OutputFile->write(reinterpret_cast<char*>(data_directories.data()), sizeof(ImageDataDirectory)* data_directories.size());

	std::vector<Section> sections;
	createExeInfo.OutputFile->write(reinterpret_cast<char*>(sections.data()), sizeof(Section)* sections.size());
	
	createExeInfo.OutputFile->write(reinterpret_cast<char*>(createExeInfo.Code->data()), createExeInfo.Code->size());

	//imports

	createExeInfo.OutputFile->write(reinterpret_cast<char*>(createExeInfo.Data->data()), createExeInfo.Data->size());
	
}
