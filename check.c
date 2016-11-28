#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#include <string.h>
#endif

FILE* myOpen(const char*filename, const char*mode)
{
#ifdef _WIN32
    int new_Len1 = 0;
    int new_Len2 = 0;
    int fn_len_s = strlen(filename);
    int m_len_s  = strlen(mode);
    if(fn_len_s==0) 
		return NULL;
    if(m_len_s==0)
		return NULL;
    wchar_t path[MAX_PATH];
    wchar_t wmode[MAX_PATH];
    new_Len1 = MultiByteToWideChar(CP_UTF8, 0, filename, fn_len_s, path, fn_len_s);
    if(new_Len1>=MAX_PATH) return NULL;
    path[new_Len1] = L'\0';
    new_Len2 = MultiByteToWideChar(CP_UTF8, 0, mode, m_len_s, wmode, m_len_s);
    if(new_Len2>=MAX_PATH) return NULL;
    wmode[new_Len2] = L'\0';
    FILE *f = _wfopen(path, wmode);
    return f;
#else
    return fopen(filename, mode);
#endif
}

int main()
{
    const char* path = "Вася/κάτι εκεί/那裡的東西.txt";
    FILE* file = myOpen(path, "r");
    if(!file)
        printf("Ouch!, you don't support UTF-8 right :-P\n");
    else
    {
        char buffer[10000];
        fread(buffer, 1, 10000, file);
        fclose(file);
        printf("%s\n", buffer);
    }
    return 0;
}

