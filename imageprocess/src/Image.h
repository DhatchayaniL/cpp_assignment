#include <stdint.h>
#include<cstdio>

enum ImageType{
    PNG, JPG, BMP, TGA
};

struct Image{
    uint8_t* data = NULL;
    size_t size = 0;
    int w;
    int h;
    int channels;

    Image(const char* filename);
    Image(int w, int h, int channels);
    Image(const Image& img);
    ~Image();
    void convertToGrayscale();
    void adjustBrightness(int factor);
    void invertColors();
    void crop(int x, int y, int newWidth, int newHeight);
    void rotate90Degrees();

    bool read(const char* filename);
    bool write(const char* filename);
    ImageType getFileType(const char* filename);
    
};