# define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
char data[0x20000];
void sub_401000(BYTE* a1, BYTE* a2, int a3) {
    BYTE* v3; // eax
    unsigned int v4; // edx
    BYTE* v5; // edi
    BYTE* v6; // esi
    int i; // ecx
    unsigned int v10; // [esp+14h] [ebp+Ch]

    v3 = a2;
    v4 = *a1 + 256;
    v5 = a1 + 1;
    v10 = (unsigned int)&a2[a3];                  // 末尾
    if ((unsigned int)a2 < v10)
    {
        do
        {
            if (v4 == 1)
                v4 = (unsigned __int8)*v5++ + 256;
            if ((v4 & 1) != 0)
            {
                *v3++ = *v5++;
            }
            else
            {
                v6 = &v3[-(*(unsigned __int16*)v5 >> 4)];
                for (i = (*(WORD*)v5 & 0xF) + 2; i > 0; --i)
                    *v3++ = *v6++;
                v5 += 2;
            }
            v4 >>= 1;
        } while ((unsigned int)v3 < v10);
    }
}
int main() {
	BYTE key[256] = { 0x8B, 0xE5, 0x5D, 0xC3, 0xA1, 0xE0, 0x30, 0x44, 0x00, 0x85, 0xC0, 0x74, 0x09, 0x5F, 0x5E, 0x33, 0xC0, 0x5B, 0x8B, 0xE5, 0x5D, 0xC3, 0x8B, 0x45, 0x0C, 0x85, 0xC0, 0x75, 0x14, 0x8B, 0x55, 0xEC, 0x83, 0xC2, 0x20, 0x52, 0x6A, 0x00, 0xE8, 0xF5, 0x28, 0x01, 0x00, 0x83, 0xC4, 0x08, 0x89, 0x45, 0x0C, 0x8B, 0x45, 0xE4, 0x6A, 0x00, 0x6A, 0x00, 0x50, 0x53, 0xFF, 0x15, 0x34, 0xB1, 0x43, 0x00, 0x8B, 0x45, 0x10, 0x85, 0xC0, 0x74, 0x05, 0x8B, 0x4D, 0xEC, 0x89, 0x08, 0x8A, 0x45, 0xF0, 0x84, 0xC0, 0x75, 0x78, 0xA1, 0xE0, 0x30, 0x44, 0x00, 0x8B, 0x7D, 0xE8, 0x8B, 0x75, 0x0C, 0x85, 0xC0, 0x75, 0x44, 0x8B, 0x1D, 0xD0, 0xB0, 0x43, 0x00, 0x85, 0xFF, 0x76, 0x37, 0x81, 0xFF, 0x00, 0x00, 0x04, 0x00, 0x6A, 0x00, 0x76, 0x43, 0x8B, 0x45, 0xF8, 0x8D, 0x55, 0xFC, 0x52, 0x68, 0x00, 0x00, 0x04, 0x00, 0x56, 0x50, 0xFF, 0x15, 0x2C, 0xB1, 0x43, 0x00, 0x6A, 0x05, 0xFF, 0xD3, 0xA1, 0xE0, 0x30, 0x44, 0x00, 0x81, 0xEF, 0x00, 0x00, 0x04, 0x00, 0x81, 0xC6, 0x00, 0x00, 0x04, 0x00, 0x85, 0xC0, 0x74, 0xC5, 0x8B, 0x5D, 0xF8, 0x53, 0xE8, 0xF4, 0xFB, 0xFF, 0xFF, 0x8B, 0x45, 0x0C, 0x83, 0xC4, 0x04, 0x5F, 0x5E, 0x5B, 0x8B, 0xE5, 0x5D, 0xC3, 0x8B, 0x55, 0xF8, 0x8D, 0x4D, 0xFC, 0x51, 0x57, 0x56, 0x52, 0xFF, 0x15, 0x2C, 0xB1, 0x43, 0x00, 0xEB, 0xD8, 0x8B, 0x45, 0xE8, 0x83, 0xC0, 0x20, 0x50, 0x6A, 0x00, 0xE8, 0x47, 0x28, 0x01, 0x00, 0x8B, 0x7D, 0xE8, 0x89, 0x45, 0xF4, 0x8B, 0xF0, 0xA1, 0xE0, 0x30, 0x44, 0x00, 0x83, 0xC4, 0x08, 0x85, 0xC0, 0x75, 0x56, 0x8B, 0x1D, 0xD0, 0xB0, 0x43, 0x00, 0x85, 0xFF, 0x76, 0x49, 0x81, 0xFF, 0x00, 0x00, 0x04, 0x00, 0x6A, 0x00, 0x76 };
	FILE* in;
	in = fopen("D:\\N0zoM1z0\\Sec-Learning\\Reverse\\游戏逆向\\read.sav", "rb");
	fread(data, sizeof(char), sizeof(data), in);
	DWORD* dw_data = (DWORD*)data;
	DWORD v12 = dw_data[2];
	DWORD v26 = dw_data[3];
	for (int i = 0x10; i < 0x10 + v12; i++) {
		data[i] ^= key[(i - 0x10) & 0xFF];
	}
    DWORD v25 = dw_data[5];
    void* Block = malloc(v25);
    sub_401000((BYTE*)data + 24, (BYTE*)Block, v25);
    printf("+++++++++++++++++++++++++++++++++++++++++++++++");
    
    for (int i = 0; i < v25; i++) {
        BYTE c = *((BYTE*)Block + i);
    } // checked ✔️
    FILE* Stream = fopen("D:\\N0zoM1z0\\Sec-Learning\\Reverse\\游戏逆向\\SiglusCounter.txt", "wb");
    FILE* v4; // eax
    FILE* v5; // edi
    char* v6; // eax
    const char* v7; // edi
    char* v8; // eax
    FILE* v9; // eax
    FILE* v10; // edi
    void* v11; // esi
    int* v13; // esi
    const WCHAR* v14; // esi
    int* v15; // esi
    int v16; // ecx
    size_t v17; // eax
    int v19; // [esp-14h] [ebp-3A0h]
    char Buffer[304]; // [esp+Ch] [ebp-380h] BYREF
    CHAR MultiByteStr[260]; // [esp+13Ch] [ebp-250h] BYREF
    CHAR pszPath[304]; // [esp+240h] [ebp-14Ch] BYREF
    int v24; // [esp+374h] [ebp-18h]

    size_t v27; // [esp+380h] [ebp-Ch]
    size_t Size; // [esp+384h] [ebp-8h]

    if (Stream)
    {
        v13 = (int*)Block;
        v24 = 0;
        Size = 0;
        if (v26 > 0)
        {
            v25 = v26;
            do
            {
                v19 = *v13;
                v14 = (const WCHAR*)(v13 + 1);
                v26 = v19;
                MultiByteStr[WideCharToMultiByte(0x3A4u, 0, v14, v19, MultiByteStr, 256, 0, 0)] = 0;
                v15 = (int*)&v14[v26];
                v16 = *v15;
                v13 = v15 + 1;
                v26 = v16;
                if (v16)
                {
                    v17 = 0;
                    v27 = 0;
                    if (v16 > 0)
                    {
                        v27 = v16;
                        do
                        {
                            v17 += *(unsigned __int8*)v13;
                            v13 = (int*)((char*)v13 + 1);
                            --v27;
                        } while (v27);
                        v27 = v17;
                    }
                    Size += v17;
                    v24 += v16;
                    fprintf(
                        Stream,
                        "%6d/%6d   %3d.%d%%   %s\r\n",
                        v27,
                        v26,
                        (int)(1000 * v17) / v16 / 10,
                        (int)(1000 * v17) / v16 % 10,
                        MultiByteStr);
                }
                --v25;
            } while (v25);
        }
        free(Block);
        fprintf(
            Stream,
            "----------------------------------------\r\n%6d/%6d   %3d.%d%%   (ALL)\r\n",
            Size,
            v24,
            (int)(1000 * Size) / v24 / 10,
            (int)(1000 * Size) / v24 % 10);
        fclose(Stream);
    }
    ShellExecuteA(0, "open", "D:\\N0zoM1z0\\Sec-Learning\\Reverse\\游戏逆向\\SiglusCounter.txt", NULL,NULL, 1);
}