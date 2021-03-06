#pragma once

#include <slk/utility/buffer.h>
#include <slk/utility/object_id.h>
#include <slk/table/ObjTable.hpp>

namespace slk
{
	class ObjReader
	{
	public:
		template <class ObjTableT>
		static void Read(buffer_reader& reader, ObjTableT& table)
		{
			reader.read<W3OHeader>();
			ReadOriginalTable(reader, table);
			ReadCustomTable(reader, table);
		}

	private:
		struct W3OHeader
		{
			uint32_t nVersion;
		};

		template <class ObjTableT>
		static void ReadOriginalTable(buffer_reader& reader, ObjTableT& table)
		{
			// Original objects table
			uint32_t nOriginalTableCount = reader.read<uint32_t>();
			for (uint32_t i = 0; i < nOriginalTableCount; ++i)
			{
				// Original Id
				object_id OriginalObjectId(reader.read<uint32_t>(), object_id::not_swap_t());
				// New id, always be 0
				object_id NewObjectId(reader.read<uint32_t>(), object_id::not_swap_t());

				assert (OriginalObjectId.vaild());

				if (NewObjectId != 0)
				{
					throw ydwe::exception("Object in original table has incorrect id(Not 0).");
				}

				ObjSingle<ObjTableT::table_type>& obj = table[OriginalObjectId];
				obj.SetId(OriginalObjectId);
				obj.SetBaseId(OriginalObjectId);

				ReadModData<ObjTableT::table_type>(reader, obj);
			}
		}

		template <class ObjTableT>
		static void ReadCustomTable(buffer_reader& reader, ObjTableT& table)
		{
			// Custom objects table
			uint32_t nCustomTableCount = reader.read<uint32_t>();
			for (uint32_t i = 0; i < nCustomTableCount; ++i)
			{
				// Original Id
				object_id OriginalObjectId(reader.read<uint32_t>(), object_id::not_swap_t());
				// New id
				object_id NewObjectId(reader.read<uint32_t>(), object_id::not_swap_t());

				assert (OriginalObjectId.vaild());
				assert (NewObjectId.vaild());

				ObjSingle<ObjTableT::table_type>& obj = table[NewObjectId];
				obj.SetId(NewObjectId);
				obj.SetBaseId(OriginalObjectId);

				ReadModData<ObjTableT::table_type>(reader, obj);
			}
		}

		template <OBJECT_PARSER_OPTION Option>
		static void ReadModData(buffer_reader& reader, ObjSingle<Option>& obj);
	};

}
