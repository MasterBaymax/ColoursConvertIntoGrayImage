#include <stdio.h>
#include <stdlib.h>
#pragma pack(1)

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

HEADER img_header;
long img_size;
RGB *img_data;

int main()
{
    FILE *pFile1, *pFile2;
    int i;
    size_t result;

    pFile1 = fopen("flower.bmp", "rb");
    pFile2 = fopen("gray.bmp", "wb");
    if(pFile1==NULL || pFile2==NULL) {fputs("File error",stderr); exit(0);}

    /* There has two steps to implement gray image:
       first,copy the header information into another image;
       second, change the RGB color into same pixel.
     */

    //obtain binary file header information and copy into the another file:
    result = fread(&img_header, 1, sizeof(HEADER), pFile1);
    if(result != 54) {fputs("Reading error", stderr); exit(1);}
    result = fwrite(&img_header, 1, sizeof(HEADER), pFile2);
    if(result != 54) {fputs("Copy error", stderr); exit(2);}

    //print the type "BM" and bitmap width and height
    printf("%c%c %d %d\n", img_header.type[0],
                           img_header.type[1],
                           img_header.width,
                           img_header.height);

    //acquire the RGB value from binary format and change the color value:
    img_size = sizeof(RGB)*img_header.width*img_header.height;
    printf("the size of img_size:%ld\n", img_size);

    img_data = (RGB *)malloc(img_size);
    fread(img_data, 1, img_size, pFile1);

    //R=G=B color image will change the image into gray
    for(i=0; i<img_header.width*img_header.height; i++)
        img_data[i].R = img_data[i].G = img_data[i].B;
    fwrite(img_data, 1, img_size, pFile2);

    printf("%d,%d,%d",img_data[0].R, img_data[0].G, img_data[0].B);
    printf("%d,%d,%d",img_data[1].R, img_data[1].G, img_data[1].B);

    /* the whole file is now loaded in the pFile2 that changes the color into gray */

    //terminate
    fclose(pFile1);
    fclose(pFile2);
    free(img_data);
    return 0;
}

