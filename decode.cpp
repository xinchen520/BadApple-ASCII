//Author: Xin Chen
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
using namespace std;
const int default_width = 40;
const int default_height = 20;
char img[90*68];
int pointer;
void GetTerminalSize(int* w, int* h)
{
    winsize size;
    if(isatty(STDOUT_FILENO) == 0)
    {
        *w = default_width;
        *h = default_height;
    }
    else{
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        *w = size.ws_col;
        *h = size.ws_row;
    }
}
void ReadNextImg(unsigned char* data)
{
    int len =0;
    len|= data[pointer++];
    len|= (int)(data[pointer++]) << 8;
    //("len:%d\n", len);
    if(len&1)
    {
        ("error");
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
    timespec time_spec;
    time_spec.tv_sec = 0;
    time_spec.tv_nsec = 30000000;
    FILE* file = fopen("result.txt","rb");
    fseek(file,0, SEEK_END);
    int file_size = ftell(file);
    unsigned char* data = new unsigned char[file_size];
    fseek(file,0, SEEK_SET);
    fread(data,1, file_size, file);
    int width ;
    int height;
    GetTerminalSize(&width, &height);
    width *=1;
    height-=1;
    printf("Your terminal size is %d x %d\n",width, height);
    printf("BadApple!!ASCII!!\nAuthor:Xin Chen\nPress 'Enter' to Start.");
    getchar();
    char* screen_buffer = new char[width * height];
    for(int i = 0; i< 6570;++i)
    {
        
        ReadNextImg(data);
        for(int y = 1;y<=height;++y)
        {
            float yf = (float)y / height;
            int iy = std::max(yf * 68.0f -1.0f, 0.0f);
            for(int x= 1; x<=width;++x)
            {
                float xf = (float)x / width;
                int ix = std::max(xf * 90.0f -1.0f, 0.0f);
                screen_buffer[(y-1)*width + x-1] =img[iy*90 + ix]; 
            }
        }
        write(STDOUT_FILENO, screen_buffer, width*height);

        nanosleep(&time_spec, NULL);
        write(STDOUT_FILENO, "\033c", sizeof("\033c"));

    }
    delete data;
    return 0;
}
