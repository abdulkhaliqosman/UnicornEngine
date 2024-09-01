#include "gltffileasset.h"
#include "extern/cgltf/cgltf.h"
#include "extern/stb_image/stb_image.h"
#include "assets/mesh/meshasset.h"
#include "assets/material/materialasset.h"
#include "assets/texture/textureasset.h"
#include "assets/file/assetfiledata.h"

namespace uniassets
{
    class GLTFFileAssetInternal
    {
    public:
        static MeshAsset* ImportMeshPrimitive(cgltf_primitive* primitive);
        static MaterialAsset* ImportMaterial(const cgltf_material& material);
        static TextureAsset* ImportTexture(const cgltf_texture& texture);
    };

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
                MeshAsset* meshasset = GLTFFileAssetInternal::ImportMeshPrimitive(primitive);
                asset->GetMeshes().push_back(meshasset);
            }
        }

        for (int i = 0; i < data->materials_count; ++i)
        {
            const cgltf_material* cgmat = &(data->materials[i]);

            if (cgmat == nullptr)
            {
                continue;
            }

            MaterialAsset* material = GLTFFileAssetInternal::ImportMaterial(*cgmat);
            asset->GetMaterials().push_back(material);
        }

        cgltf_free(data);

        return asset;
    }

    MeshAsset* GLTFFileAssetInternal::ImportMeshPrimitive(cgltf_primitive* primitive)
    {
        MeshAsset* mesh = ucNew(MeshAsset);
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
                break;
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
                for (int a = 0; a < accessor->count; ++a)
                {
                    ucc::Vector2f v;
                    cgltf_accessor_read_float(accessor, a, &v.x, element_size);
                    vertices[a].texcoord = ucc::Vector2f(v);
                }
                break;
            }
            case cgltf_attribute_type_color:
            {
                break;
            }
            case cgltf_attribute_type_joints:
            {
                for (int a = 0; a < accessor->count; ++a)
                {
                    cgltf_uint v[4];
                    cgltf_accessor_read_uint(accessor, a, v, element_size);
                    vertices[a].joints = ucc::Vector4u8{ (uint8_t)v[0], (uint8_t)v[1],(uint8_t)v[2], (uint8_t)v[3] };
                }
                break;
            }
            case cgltf_attribute_type_weights:
            {
                for (int a = 0; a < accessor->count; ++a)
                {
                    ucc::Vector4f::vector_type v;
                    cgltf_accessor_read_float(accessor, a, v.data, element_size);
                    vertices[a].weights = ucc::Vector4f(v);
                }
                break;
            }
            }
        }

        return mesh;
    }

    MaterialAsset* GLTFFileAssetInternal::ImportMaterial(const cgltf_material& cgmat)
    {
        MaterialAsset* material = ucNew(MaterialAsset);
        if (cgmat.has_pbr_metallic_roughness)
        {
            auto baseTexView = cgmat.pbr_metallic_roughness.base_color_texture;
            if (baseTexView.texture)
            {
                material->m_BaseColor = ImportTexture(*baseTexView.texture);
            }

            auto roughTexView = cgmat.pbr_metallic_roughness.metallic_roughness_texture;
            if (roughTexView.texture)
            {
                material->m_Roughness = ImportTexture(*roughTexView.texture);
            }
        }
        return material;
    }

    TextureAsset* GLTFFileAssetInternal::ImportTexture(const cgltf_texture& cgtexture)
    {
        TextureAsset* texture = ucNew(TextureAsset);
        cgltf_image* cgImage = cgtexture.image;
        cgltf_buffer_view* bufferView = cgImage->buffer_view;

        unsigned char* data = (unsigned char*)(bufferView->buffer->data) + bufferView->offset;
        cgltf_size len = bufferView->size;
        int x, y, channels;

        stbi_uc* result = stbi_load_from_memory(data, len, &x, &y, &channels, 4);
        texture->width = x;
        texture->height = y;
        texture->channels = channels;
        texture->req_channels = 4;
        texture->buffer = result;

        return texture;
    }
}