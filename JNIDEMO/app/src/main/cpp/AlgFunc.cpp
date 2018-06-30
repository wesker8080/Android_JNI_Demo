#include <stdio.h>
#include <stdlib.h>

#include "AlgFunc.h"
#include "logUtils.h"


char* imgToGrayARGB( char* buf, int w, int h) {
    LOGI("==imgToGray byte==");

    char * cbuf;
    cbuf = buf; // 获取数组元素

    int alpha = 0xFF; // 不透明值
    unsigned int i, color;
    unsigned int red, green, blue;
    for (i = 0; i < h*w*4; i+=4) {
        	red = (unsigned char)cbuf[i+0]; // 获得red值
            green = (unsigned char)cbuf[i+1]; // 获得green值
    		blue = (unsigned char)cbuf[i+2]; // 获得blue值

    		//查看几个颜色值
            if(i<10){
            	LOGI("argb[%d]=(%d,%d,%d,%d)",i,cbuf[i+3],red,green,blue);
            }
            color = (red * 38 + green * 75 + blue * 15) >> 7; // 灰度算法（16位运算下7位精度）

//            color = (red * 299 + green * 587 + blue * 114 + 500) / 1000; // 灰度算法（缩放1000倍来实现整数运算算法）效果相同

            red = green = blue = color; // 以灰度值来设置rgb

//            red=0;//可以分别清0，测试颜色分量对应关系
//            green=0;
//            blue=0;
            //LOGD("color is :%d",color); 不能随便打log啊，这里的log会耗资源的。容易造成anr
            cbuf[i+3]=alpha;
            cbuf[i+2]=blue;
            cbuf[i+1]=green;
            cbuf[i+0]=red;

    }
    LOGI("==imgToGray byte complete==");

    return buf;
}


