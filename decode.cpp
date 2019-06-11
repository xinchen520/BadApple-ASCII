//Author: Xin Chen
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char img[90*68];
int pointer;
void ReadNextImg(unsigned char* data)
{
    int len =0;
    len|= data[pointer++];
    len|= (int)(data[pointer++]) << 8;
    //printf("len:%d\n", len);
    if(len&1)
    {
        printf("error");
        exit(-1);
    }
    for(int i =0;i<len/2;++i)
    {
        int pos = 0;
        pos|= data[pointer++];
        pos|= (int)(data[pointer++]) << 8;
        img[pos] = img[pos] == ' '? '0':' ';
    }
}
int main()
{
        memset(img,' ',sizeof(img));

    FILE* file = fopen("result.txt","rb");
    fseek(file,0, SEEK_END);
    int file_size = ftell(file);
    //printf("size:%d\n", file_size);
    unsigned char* data = new unsigned char[file_size];
    fseek(file,0, SEEK_SET);
    fread(data,1, file_size, file);
    int width = 40;
    int height =20;
    for(int i = 0; i< 6570;++i)
    {
        ReadNextImg(data);
        for(int y = 1;y<=height;++y)
        {
            float yf = (float)y / 20;
            int iy = yf * 68;
            for(int x= 1; x<=width;++x)
            {
                float xf = (float)x / width;
                int ix = xf * 90;
                putchar(img[iy*90 + ix]);
            }
            putchar('\n');
        }
        
        system("cls");
    }
    delete data;
    return 0;
}
