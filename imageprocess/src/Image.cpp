#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <algorithm> 

Image::Image(const char* filename){
    if(read(filename)) {
        printf("Read %s\n", filename);
        size = w*h*channels;
    }
    else{
        printf("Failed to read %s\n",filename);
    }
}


Image::Image(int w, int h, int channels): w(w), h(h), channels(channels) {
    size = w*h*channels;
    data = new uint8_t[size];
}
Image::Image(const Image& img): Image(img.w,img.h,img.channels) {
    memcpy(data,img.data,img.size);
}
Image::~Image(){
    stbi_image_free(data);
}

bool Image::read(const char* filename){
    data = stbi_load(filename, &w, &h, &channels, 0);
    // return data != NULL;
    if (data == nullptr) {
        printf("Failed to load image %s\n", filename);
        return false;
    }
    printf("Read %s\n", filename);
    return true;
}
bool Image::write(const char* filename){
    ImageType type =getFileType(filename);
    int success;
    switch (type)
    {
    case PNG:
        success = stbi_write_png(filename, w, h, channels, data, w*channels);
        break;
    case BMP:
        success = stbi_write_bmp(filename,  w, h, channels, data);
        break;
    case JPG:
        success = stbi_write_jpg(filename,  w, h, channels, data, 100);
        break;
    case TGA:
        success = stbi_write_tga(filename, w, h, channels, data);
        break;
    }
    if (success) {
        printf("Successfully wrote image to %s\n", filename);
    } else {
        printf("Failed to write image to %s\n", filename);
    }
    return success != 0;
}

ImageType Image::getFileType(const char* filename){
    const char* ext = strchr(filename,'.');
    if(ext != nullptr){
        if(strcmp(ext, ".png")==0){
            return PNG;
        }
        else if(strcmp(ext, ".jpg")==0){
            return JPG;
        }
        else if(strcmp(ext, ".bmp")==0){
            return BMP;
        }
        else if(strcmp(ext, ".tga")==0){
            return TGA;
        }
    }
    return PNG;
}

void Image::convertToGrayscale() {
    if (channels == 3) {
        for (int i = 0; i < size; i += channels) {
            uint8_t gray = static_cast<uint8_t>((data[i] + data[i + 1] + data[i + 2]) / 3);
            data[i] = data[i + 1] = data[i + 2] = gray;
        }
    }
}

void Image::adjustBrightness(int factor) {
    for (int i = 0; i < size; ++i) {
        int newValue = static_cast<int>(data[i]) + factor;
        data[i] = static_cast<uint8_t>(std::clamp(newValue, 0, 255));
    }
}

void Image::invertColors() {
    for (int i = 0; i < size; ++i) {
        data[i] = 255 - data[i];
    }
}

void Image::crop(int x, int y, int newWidth, int newHeight) {
    // Check if the cropping parameters are valid
    if (x >= 0 && y >= 0 && x + newWidth <= w && y + newHeight <= h) {
        // Create a new array for the cropped image
        uint8_t* croppedData = new uint8_t[newWidth * newHeight * channels];
        for (int i = 0; i < newHeight; ++i) {
            for (int j = 0; j < newWidth; ++j) {
                int sourceIndex = ((y + i) * w + x + j) * channels;
                int destIndex = (i * newWidth + j) * channels;
                memcpy(&croppedData[destIndex], &data[sourceIndex], channels);
            }
        }
        // Update image properties
        delete[] data;
        data = croppedData;
        w = newWidth;
        h = newHeight;
        size = w * h * channels;
    }
}

void Image::rotate90Degrees() {
    // Assuming the image is initially in row-major order
    uint8_t* rotatedData = new uint8_t[size];
    int rotatedWidth = h;
    int rotatedHeight = w;
    int rotatedSize = rotatedWidth * rotatedHeight * channels;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int sourceIndex = (i * w + j) * channels;
            int destIndex = ((w - 1 - j) * rotatedWidth + i) * channels;

            // Check if destination index is within bounds
            if (destIndex >= 0 && destIndex < rotatedSize) {
                memcpy(&rotatedData[destIndex], &data[sourceIndex], channels);
            }
        }
    }

    // Update image properties
    delete[] data;
    data = rotatedData;
    w = rotatedWidth;
    h = rotatedHeight;
    size = rotatedSize;
}
