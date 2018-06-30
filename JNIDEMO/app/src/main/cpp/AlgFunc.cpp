#include <stdio.h>
#include <stdlib.h>

#include "AlgFunc.h"
#include "logUtils.h"


char* imgToGrayARGB( char* buf, int w, int h) {
    LOGI("==imgToGray byte==");

    char * cbuf;
    cbuf = buf; // ��ȡ����Ԫ��

    int alpha = 0xFF; // ��͸��ֵ
    unsigned int i, color;
    unsigned int red, green, blue;
    for (i = 0; i < h*w*4; i+=4) {
        	red = (unsigned char)cbuf[i+0]; // ���redֵ
            green = (unsigned char)cbuf[i+1]; // ���greenֵ
    		blue = (unsigned char)cbuf[i+2]; // ���blueֵ

    		//�鿴������ɫֵ
            if(i<10){
            	LOGI("argb[%d]=(%d,%d,%d,%d)",i,cbuf[i+3],red,green,blue);
            }
            color = (red * 38 + green * 75 + blue * 15) >> 7; // �Ҷ��㷨��16λ������7λ���ȣ�

//            color = (red * 299 + green * 587 + blue * 114 + 500) / 1000; // �Ҷ��㷨������1000����ʵ�����������㷨��Ч����ͬ

            red = green = blue = color; // �ԻҶ�ֵ������rgb

//            red=0;//���Էֱ���0��������ɫ������Ӧ��ϵ
//            green=0;
//            blue=0;
            //LOGD("color is :%d",color); ��������log���������log�����Դ�ġ��������anr
            cbuf[i+3]=alpha;
            cbuf[i+2]=blue;
            cbuf[i+1]=green;
            cbuf[i+0]=red;

    }
    LOGI("==imgToGray byte complete==");

    return buf;
}


