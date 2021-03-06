#include <slk/reader/IniReader.hpp>
#include <slk/reader/CommonReader.hpp>

namespace slk
{
	void IniReader::Read(buffer_reader& reader, IniTable& table)
	{
		reader::utility::ini_read(reader, table);
	}
}
