#include "DDSFileLoader.h"
#include <fstream>
#include <iostream>
#include <cassert>

// These code is from a website, read it afterwards: 

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

namespace
{
    GLuint LoadDDS(const char * filename)
    {


        std::ifstream file(filename, std::ios::in | std::ios::binary);
        if (!file) 
        {
            assert(false);
            std::cout << "Error::loadDDs, could not open:"
                << filename << "for read." << std::endl;
            return 0;
        }

        char filecode[4];
        file.read(filecode, 4);
        if (strncmp(filecode, "DDS ", 4) != 0) {
            std::cout << "Error::loadDDs, format is not dds :"
                << filename << std::endl;
            file.close();
            return 0;
        }

        char header[124];
        file.read(header, 124);

        unsigned int height = *(unsigned int*)&(header[8]);
        unsigned int width = *(unsigned int*)&(header[12]);
        unsigned int linearSize = *(unsigned int*)&(header[16]);
        unsigned int mipMapCount = *(unsigned int*)&(header[24]);
        unsigned int fourCC = *(unsigned int*)&(header[80]);


        char * buffer = NULL;
        unsigned int bufsize;
        bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
        buffer = new char[bufsize];
        file.read(buffer, bufsize);

        file.close();

        unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
        unsigned int format;
        switch (fourCC)
        {
        case FOURCC_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            delete[] buffer;
            return 0;
        }

        // Create one OpenGL texture
        GLuint textureID;
        glGenTextures(1, &textureID);

        // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, textureID);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
        unsigned int offset = 0;

        for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
        {
            unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
            glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
                0, size, buffer + offset);

            offset += size;
            width /= 2;
            height /= 2;

            // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
            if (width < 1) width = 1;
            if (height < 1) height = 1;

        }

        delete[] buffer;

        return textureID;
    }

}

GLuint DDSFileLoader::Read(const char * path)
{
    return LoadDDS(path);
}
