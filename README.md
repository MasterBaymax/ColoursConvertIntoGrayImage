# ColoursConvertIntoGrayImage
Converting a color image into gray image
# Qestion
I have a **colored image**, and I want to convet into **gray image**. What can I do for it?
## original figure 
![flower.bmp](file:///J:/MyPC/CodingTest/ColoursConvertIntoGrayImage/flower.bmp)
## result's figure
![gray.bmp](file:///J:/MyPC/CodingTest/ColoursConvertIntoGrayImage/gray.bmp)
# Method
1. copy the header information into another image;
2. change the RGB color into same value
# Corel Code
1. tagHeader information
```
typedef struct tagHEADER
{
    char type[2];
    char dummy1[16];
    int width;
    int height;
    char dummy2[28];
}HEADER;

/*binary format biheight is positive:
 The fill sequence runs from the bottom left to the top right. */
 /* biCount is 24, color order is BGR */
typedef struct tagRGB
{
    unsigned char B;
    unsigned char G;
    unsigned char R;
}RGB;
```
2. obtain binary file header information and copy into the another file:
```
result = fread(&img_header, 1, sizeof(HEADER), pFile1);
    if(result != 54) {fputs("Reading error", stderr); exit(1);}
    result = fwrite(&img_header, 1, sizeof(HEADER), pFile2);
    if(result != 54) {fputs("Copy error", stderr); exit(2);}
```
3. change the color
```
for(i=0; i<img_header.width*img_header.height; i++)
        img_data[i].R = img_data[i].G = img_data[i].B;
```
