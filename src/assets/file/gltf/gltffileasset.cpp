#include "gltffileasset.h"
#include "extern/cgltf/cgltf.h"
#include "assets/mesh/meshdata.h"
#include "assets/file/assetfiledata.h"

namespace uniassets
{
    AssetFileData* GLTFFileAsset::ImportFromFile(const TCHAR* path)
    {
        AssetFileData* asset = ucNew(AssetFileData);

        cgltf_options options;
        memset(&options, 0, sizeof(cgltf_options));
        cgltf_data* data = NULL;
        cgltf_result result = cgltf_parse_file(&options, path, &data);

        if (result == cgltf_result_success)
            result = cgltf_load_buffers(&options, data, path);

        if (result == cgltf_result_success)
            result = cgltf_validate(data);

        printf("Result: %d\n", result);

        if (result == cgltf_result_success)
        {
            printf("Type: %u\n", data->file_type);
            printf("Meshes: %u\n", (unsigned)data->meshes_count);
        }
        for (int i = 0; i < data->meshes_count; ++i)
        {
            cgltf_mesh* cgmesh = &(data->meshes[i]);
            
            if (cgmesh == nullptr)
            {
                continue;
            }

            for (int j = 0; j < cgmesh->primitives_count; ++j)
            {
                cgltf_primitive* primitive = &(cgmesh->primitives[j]);

                if (primitive == nullptr)
                {
                    continue;
                }

                MeshData* mesh = ucNew(MeshData);
                ucc::List<Vertex>& vertices = mesh->GetVertices();
                size_t vertexCount = 0;

                cgltf_accessor* indices = primitive->indices;
                if (indices)
                {
                    mesh->GetIndices().reserve(indices->count);
                    for (size_t i = 0; i < indices->count; ++i)
                    {
                        size_t index;
                        mesh->GetIndices().push_back(cgltf_accessor_read_index(indices, i));
                    }
                }

                for (int k = 0; k < primitive->attributes_count; ++k)
                {
                    cgltf_attribute* attribute = &(primitive->attributes[k]);
                    cgltf_accessor* accessor = attribute->data;
                    vertexCount = max(accessor->count, vertexCount);
                }

                vertices.resize(vertexCount);

                for (int k = 0; k < primitive->attributes_count; ++k)
                {
                    cgltf_attribute* attribute = &(primitive->attributes[k]);
                    cgltf_accessor* accessor = attribute->data;
                    cgltf_type accessor_type = accessor->type;
                    cgltf_component_type component_type = accessor->component_type;
                    cgltf_attribute_type attribute_type = attribute->type;
                    size_t element_size = 0;
                    switch (accessor_type)
                    {
                    case cgltf_type_invalid:
                        continue; // assert?
                        break;
                    case cgltf_type_scalar:
                        element_size = 1;
                        break;
                    case cgltf_type_vec2:
                        element_size = 2;
                        break;
                    case cgltf_type_vec3:
                        element_size = 3;
                    case cgltf_type_vec4:
                        element_size = 4;
                        break;
                    case cgltf_type_mat2:
                        element_size = 4;
                        break;
                    case cgltf_type_mat3:
                        element_size = 9;
                        break;
                    case cgltf_type_mat4:
                        element_size = 16;
                        break;
                    default:
                        continue; // assert?
                        break;
                    }
                    switch (attribute_type)
                    {
                    case cgltf_attribute_type_invalid:
                    {
                        break;
                    }
                    case cgltf_attribute_type_position:
                    {
                        for (int a = 0; a < accessor->count; ++a)
                        {
                            ucc::Vector4f::vector_type v;
                            cgltf_accessor_read_float(accessor, a, v.data, element_size);
                            v.data[3] = 1.0f;
                            vertices[a].position = ucc::Vector4f(v);
                        }
                        break;
                    }
                    case cgltf_attribute_type_normal:
                    {
                        for (int a = 0; a < accessor->count; ++a)
                        {
                            ucc::Vector4f::vector_type v;
                            cgltf_accessor_read_float(accessor, a, v.data, element_size);
                            vertices[a].normal = ucc::Vector4f(v);
                        }
                        break;
                    }
                    case cgltf_attribute_type_tangent:
                    {
                        break;
                    }
                    case cgltf_attribute_type_texcoord:
                    {
                        // for (int a = 0; a < accessor->count; ++a)
                        // {
                        //     ucc::Vector2f v;
                        //     cgltf_accessor_read_float(accessor, a, &v.x, element_size);
                        //     vertices[i].texcoord = ucc::Vector2f(v);
                        // }
                        break;
                    }
                    case cgltf_attribute_type_color:
                    {
                        break;
                    }
                    case cgltf_attribute_type_joints:
                    {
                        // for (int a = 0; a < accessor->count; ++a)
                        // {
                        //     cgltf_uint v[4];
                        //     cgltf_accessor_read_uint(accessor, a, v, element_size);
                        //     vertices[i].joints = ucc::Vector4uc{ (uint8_t)v[0], (uint8_t)v[1],(uint8_t)v[2], (uint8_t)v[3] };
                        // }
                        break;
                    }
                    case cgltf_attribute_type_weights:
                    {
                        // for (int a = 0; a < accessor->count; ++a)
                        // {
                        //     ucc::Vector4f::vector_type v;
                        //     cgltf_accessor_read_float(accessor, a, v.data, element_size);
                        //     vertices[i].weights = ucc::Vector4f(v);
                        // }
                        break;
                    }
                }

                asset->GetMeshes().push_back(mesh);
            }
            }
        }

        cgltf_free(data);

        return asset;
    }
}