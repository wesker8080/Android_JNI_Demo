
#ifndef ALGFUNC_H
#define ALGFUNC_H

//#include <android/log.h>
//�޸���־tag�е�ֵ
//#define LOG_TAG "JNI"
//��־��ʾ�ĵȼ�
//#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
//#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)


typedef struct _Process_result
{
	char strResult[32];
	int x;
	int y;
	int width;
	int height;
}Process_result;

char* imgToGrayARGB( char* buf, int w, int h);


#endif
