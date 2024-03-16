#include "fbxfileasset.h"
#include "assets/file/assetfiledata.h"

// based on this info https://code.blender.org/2013/08/fbx-binary-file-format-specification/

#define MY_PRINTF printf

namespace uniassets
{
    struct FBXFileHeader
    {
        char kaydara[21] = { 0 };
        char magic[2] = { 0 };
        uint32_t version = 0;

        void Deserialize(ucc::FileSystem& file)
        {
            file.ReadBytes(kaydara, 21);
            file.ReadBytes(magic, 2);
            file.ReadUInt32(version);

            MY_PRINTF("File Header\n");
            MY_PRINTF("%s\n", kaydara);
            MY_PRINTF("%X %02X\n", magic[0], magic[1]);
            MY_PRINTF("Version: %d\n", version);
            MY_PRINTF("\n");
        }
    };

    class PropertyRecordFormat
    {
    public:
        enum class TypeCode
        {
            Uninitialized = 0x0000,
            Bool = 0x0001,
            Int16 = 0x0002,
            Int32 = 0x0004,
            Int64 = 0x0008,
            Float = 0x0014,
            Double = 0x0018,
            BoolArray = 0x0101,
            Int32Array = 0x0104,
            FloatArray = 0x0114,
            DoubleArray = 0x0118,
            Int64Array = 0x0108,
            String = 0x0201,
            RawBinary = 0x0401
        };

        PropertyRecordFormat()
        {

        }

        ~PropertyRecordFormat()
        {
            if (IsArrayType())
            {
                if (m_Array.data) delete[] m_Array.data;
            }
            else if (m_TypeCode == TypeCode::RawBinary)
            {
                if (m_RawBinary.data) delete[] m_RawBinary.data;
            }
            else if (m_TypeCode == TypeCode::String)
            {
                if (m_String.data) delete[] m_String.data;
            }
        }

        void Deserialize(ucc::FileSystem& file)
        {
            char typeCode;
            file.ReadBytes(&typeCode, 1);
            switch (typeCode)
            {
            case 'Y':
            {
                m_TypeCode = TypeCode::Int16;
                file.ReadInt16(m_Int16);
                // MY_PRINTF("\"Int16\": %d", m_Int16);
                break;
            }
            case 'C':
            {
                m_TypeCode = TypeCode::Bool;
                file.ReadUInt8(m_Bool);
                // MY_PRINTF("\"Bool\": %d", m_Bool);
                break;
            }
            case 'I':
            {
                m_TypeCode = TypeCode::Int32;
                file.ReadInt32(m_Int32);
                // MY_PRINTF("\"Int32\": %d", m_Int32);
                break;
            }
            case 'F':
            {
                m_TypeCode = TypeCode::Float;
                file.ReadFloat(m_Float);
                // MY_PRINTF("\"Float\": %f", m_Float);
                break;
            }
            case 'D':
            {
                m_TypeCode = TypeCode::Double;
                file.ReadDouble(m_Double);
                // MY_PRINTF("\"Double\": %f", m_Double);
                break;
            }
            case 'L':
            {
                m_TypeCode = TypeCode::Int64;
                file.ReadInt64(m_Int64);
                // MY_PRINTF("\"Int64\": %lld", m_Int64);
                break;
            }
            case 'f': { m_TypeCode = TypeCode::FloatArray; break; }
            case 'd': { m_TypeCode = TypeCode::DoubleArray; break; }
            case 'l': { m_TypeCode = TypeCode::Int64Array; break; }
            case 'i': { m_TypeCode = TypeCode::Int32Array; break; }
            case 'b': { m_TypeCode = TypeCode::BoolArray; break; }
            case 'S':
            {
                m_TypeCode = TypeCode::String;
                file.ReadUInt32(m_String.length);
                m_String.data = new char[(size_t)m_String.length + 1];
                file.ReadBytes(m_String.data, m_String.length);
                m_String.data[m_String.length] = 0;

                // MY_PRINTF("\"String\": %s", m_String.data);

                break;
            }
            case 'R':
            {
                m_TypeCode = TypeCode::RawBinary;
                file.ReadUInt32(m_RawBinary.length);
                m_RawBinary.data = new uint8_t[m_RawBinary.length];
                file.ReadBytes(m_RawBinary.data, m_RawBinary.length);

                // MY_PRINTF("\"RawBinary (length)\": %d", m_RawBinary.length);
                // for (uint32_t i = 0; i < m_RawBinary.length; ++i)
                // {
                // 	MY_PRINTF(L"%02X ", m_RawBinary.data[i]);
                // }

                MY_PRINTF("\n");
                break;
            }
            }

            if (IsArrayType())
            {
                file.ReadUInt32(m_Array.length);
                file.ReadUInt32(m_Array.encoding);
                file.ReadUInt32(m_Array.compressedLength);

                // MY_PRINTF("\"Array (length)\": %d", m_Array.length);

                size_t sz = size_t(m_Array.length) * ElementSize();
                size_t readLength = m_Array.encoding ? m_Array.compressedLength : sz;

                uint8_t* buffer = new uint8_t[sz];
                file.ReadBytes(buffer, readLength);
            }
        }

        bool IsArrayType() const
        {
            return static_cast<int>(m_TypeCode) & 0x0100;
        }

        bool IsFloatType() const
        {
            return static_cast<int>(m_TypeCode) & 0x00F0;
        }

        int ElementSize() const
        {
            return static_cast<int>(m_TypeCode) & 0x000F;
        }

    private:
        TypeCode m_TypeCode = TypeCode::Uninitialized;

        struct FbxArray
        {
            uint32_t length;
            uint32_t encoding;
            uint32_t compressedLength;
            void* data = nullptr;
        };

        struct FbxString
        {
            uint32_t length;
            char* data = nullptr;
        };

        struct FbxRawBinary
        {
            uint32_t length;
            uint8_t* data = nullptr;
        };

        union
        {
            uint8_t m_Bool;
            int16_t m_Int16;
            int32_t m_Int32;
            int64_t m_Int64;
            float m_Float;
            double m_Double;
            FbxArray m_Array;
            FbxString m_String;
            FbxRawBinary m_RawBinary;
            uint8_t m_Struct[sizeof(FbxArray)] = { 0 };
        };
    };

    struct NodeRecordFormat
    {
        struct Header
        {
            void Deserialize(ucc::FileSystem& file, uint32_t version)
            {
                if (version < 7500)
                {
                    // BEFORE VERSION 7500 (some comment underneath by some nice person)
                    // ---------------------------------------------------------------------
                    // | Size(Bytes)  | Data Type | Name
                    // | 4	          | Uint32	  | EndOffset
                    // | 4	          | Uint32	  | NumProperties
                    // | 4	          | Uint32	  | PropertyListLen
                    // | 1	          | Uint8t	  | NameLen
                    // ---------------------------------------------------------------------
                    uint32_t eo = 0, np = 0, pll = 0;

                    file.ReadUInt32(eo);
                    file.ReadUInt32(np);
                    file.ReadUInt32(pll);

                    endOffset = eo; numProperties = np; propertyListLen = pll;
                }
                else // (version >= 7500)
                {
                    // CHANGED IN VERSION 7500 (some comment underneath by some nice person)
                    // ---------------------------------------------------------------------
                    // | Size(Bytes)  | Data Type | Name
                    // | 8	          | Uint64	  | EndOffset
                    // | 8	          | Uint64	  | NumProperties
                    // | 8	          | Uint64	  | PropertyListLen
                    // | 1	          | Uint8t	  | NameLen
                    // ---------------------------------------------------------------------
                    file.ReadUInt64(endOffset);
                    file.ReadUInt64(numProperties);
                    file.ReadUInt64(propertyListLen);
                }
                file.ReadBytes(reinterpret_cast<char*>(&nameLen), 1);
                file.ReadBytes(name, nameLen);
                name[nameLen + 1] = 0;

                // MY_PRINTF("\"%s {%lld} [%lld]\":\n", name, endOffset, numProperties);
            }

            uint64_t endOffset = 0;
            uint64_t numProperties = 0;
            uint64_t propertyListLen = 0;
            unsigned char nameLen = 0;
            char name[257] = { 0 };
        };

        void Deserialize(ucc::FileSystem& file, uint32_t version)
        {
            // ---------------------------------------------------------------------
            // | Size(Bytes)  | Data Type | Name
            // | 4	          | Uint32	  | EndOffset
            // | 4	          | Uint32	  | NumProperties
            // | 4	          | Uint32	  | PropertyListLen
            // | 1	          | Uint8t	  | NameLen
            // | NameLen	  | char	  | Name
            // | ?            | ?         | Property[n], for n in 0 : PropertyListLen
            // | Optional	  | 		  | 
            // | ?            | ?         | NestedList
            // | 13	          | uint8[]	  | NULL - record
            // ---------------------------------------------------------------------


            m_Header.Deserialize(file, version);

            // MY_PRINTF("{\n");
            if (m_Header.endOffset != 0 && m_Header.endOffset < file.GetSize())
            {
                for (unsigned int i = 0; i < m_Header.numProperties; ++i)
                {
                    PropertyRecordFormat* childProperty = ucNew(PropertyRecordFormat);
                    m_Properties.push_back(childProperty);
                    childProperty->Deserialize(file);
                    // MY_PRINTF(",\n");
                }
                while (file.GetOffset() < m_Header.endOffset)
                {
                    NodeRecordFormat* childNode = ucNew(NodeRecordFormat);
                    m_ChildNodes.push_back(childNode);
                    childNode->Deserialize(file, version);
                }
            }
            // MY_PRINTF("},\n");
        }

        Header m_Header;
        ucc::List<NodeRecordFormat*> m_ChildNodes;
        ucc::List<PropertyRecordFormat*> m_Properties;
    };

    struct FBXFile
    {
        FBXFileHeader m_Header;
        ucc::List<NodeRecordFormat*> m_Nodes;

        void Deserialize(ucc::FileSystem& file)
        {
            // 27 bytes header
            m_Header.Deserialize(file);
            while (file.GetOffset() < file.GetSize())
            {
                NodeRecordFormat* nodeRecord = ucNew(NodeRecordFormat);
                m_Nodes.push_back(nodeRecord);
                nodeRecord->Deserialize(file, m_Header.version);

                // FBX files always end with a null node with endoffset set to 0
                if (nodeRecord->m_Header.endOffset == 0)
                {
                    break;
                }
            }

            // there is a mysterious footer here
        }

        AssetFileData* CreateAssetFileData()
        {

            AssetFileData* result = ucNew(AssetFileData);

        }
    };




        

    
    
    


    AssetFileData* FBXFileAsset::ImportFromFile(const TCHAR* path)
    {
        TCHAR cwd[512];
        
        GetCurrentDirectory(512, cwd);
        MY_PRINTF("cwd: %s \n", cwd);

        ucc::FileSystem file;
        MY_PRINTF("opening file %s: \n", path);
        file.OpenFile(path);

        MY_PRINTF("file size: %d: \n", file.GetSize());

        FBXFile fbxFile;
        fbxFile.Deserialize(file);
        AssetFileData* result = fbxFile.CreateAssetFileData();
        return result;
    }
}