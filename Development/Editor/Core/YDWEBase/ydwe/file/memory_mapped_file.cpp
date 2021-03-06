#include <ydwe/file/memory_mapped_file.h>
#include <ydwe/file/file_handle.h>
#include <ydwe/file/file_mapping_handle.h>
#include <ydwe/exception/windows_exception.h>

_BASE_BEGIN namespace file {

	memory_mapped_file::memory_mapped_file(const wchar_t* file_name)
		: cb_(0)
		, memory_(NULL)
	{
		open(file_name, 0, 0);
	}

	memory_mapped_file::memory_mapped_file(const wchar_t* file_name, uint64_t offset, size_t request_size)
		: cb_(0)
		, memory_(nullptr)
	{
		open(file_name, offset, request_size);
	}

	memory_mapped_file::~memory_mapped_file() 
	{
		if (memory_)
		{
			::UnmapViewOfFile(memory_);
		}
	}


	void const* memory_mapped_file::memory() const
	{
		return memory_;
	}

	size_t memory_mapped_file::size() const
	{
		return cb_;
	}


	void memory_mapped_file::open(const wchar_t* file_name, uint64_t offset, size_t request_size)
	{
		file_handle file_(file_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, NULL);

		uint64_t file_size    =   file_.get_size();
		uint64_t map_size     =   offset + request_size;

		if (map_size < offset)
		{
			throw windows_exception("requested region exceeds the available address space", ERROR_INVALID_PARAMETER);
		}

		if (offset > file_size)
		{
			if(0 == request_size)
			{
				throw windows_exception("region out of range", ERROR_INVALID_PARAMETER);
			}
		}
		else if(0 == request_size)
		{
#ifdef _WIN64
			request_size = file_size - offset;
#else
			uint64_t request_size2 = file_size - offset;
			if (request_size2 > static_cast<uint64_t>(0xFFFFFFFF))
			{
				throw windows_exception("region size too large", ERROR_NOT_ENOUGH_MEMORY);
			}
			request_size =   static_cast<size_t>(request_size2);
#endif
			map_size     =   offset + request_size;
		}

		if (0 == request_size)
		{
			memory_    =   nullptr;
			cb_        =   0;
			return ;
		}

		file_mapping_handle map_(file_, NULL, PAGE_READONLY, map_size, NULL);

		memory_    =   map_.create_view(FILE_MAP_READ, offset, request_size);
		cb_        =   request_size;
	}
}}
