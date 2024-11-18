# define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
using namespace std;

void Unpack_1(UINT8 a1,BYTE* a2,BYTE* a3,DWORD fileLen) {
	
}
int Unpack_2(UINT8 a1, BYTE* a2, BYTE* a3,DWORD fileLen) {
    /*
    */
    int result; // eax
    char v4; // cf
    char v5; // cl
    int v6; // esi
    BYTE* v7; // esi
    BYTE* v8; // edi
    BYTE* v9; // [esp-4h] [ebp-4h]
    DWORD cnt = 0;
    DWORD id1 = 0, id2 = 0; // id1: edi  id2:esi
    fileLen -= 0xD;
    DWORD flag = 0;
    while (TRUE) {
        if (!flag) {
            a1 = a3[id2];
            ++id2;
            flag = 7;
        }
        else {
            flag--;
        }
        if (id2 >= fileLen)break;
        if(id1 == 0x10038)
            printf("[+] a1: %x   id1: %x\n", a1,id1);
        v4 = a1 & 1;
        a1 >>= 1;
        if (v4) {
            //
         
            for (int i = 0; i < 3; i++) {
                a2[id1 + i] = a3[id2 + i];
            }
            a2[id1 + 3] = 0;
            id1 += 4;
            id2 += 3;
        } // checked
        else {
            int WORD_a3 = *(WORD*)((BYTE*)a3 + id2);
            v5 = (WORD_a3 & 0xF) + 1;
            v6 = (id1 - (4 * (WORD_a3 >> 4))); // !!! 这里不能用WORD！！！ ... 要int 。。。
            //cnt += 1;
            //printf("v6: %x  id1: %x\n", v6,id1);
            //if (cnt > 3)return;
            //return;
            do {
                for (int i = 0; i < 4; i++) {
                    a2[id1 + i] = a2[v6 + i];
                }
                id1 += 4;
                v6 += 4;
                v5--;

            } while (v5);
            id2 += 2;

        }
    }
    return id1; // .... 开始手贱写成id2了...
}
DWORD dword_404337, dword_404333, dword_40433F, dword_404343;
void Trans2BMP_1() {

}
int Trans2BMP_2(LPCVOID dword_40434B,LPCVOID lpBuffer) {
    int v2; // ebx
    int v3; // edi
    __int16 v4; // cx
    __int16 v5; // cx
    __int16 v6; // ax
    __int16 v7; // dx
    int result; // eax
    int v9; // [esp-6h] [ebp-6h]
    __int16 v10; // [esp-2h] [ebp-2h]


    BYTE* v0 = (BYTE*)dword_40434B;
    BYTE* v1 = (BYTE*)lpBuffer;
    *(WORD*)lpBuffer = 0x4D42;
    *(DWORD*)(v1 + 2) = dword_404343 + 54;
    *(DWORD*)(v1 + 6) = 0;
    *(DWORD*)(v1 + 10) = 54;
    *(DWORD*)(v1 + 14) = 40;
    v2 = dword_404337;
    *(DWORD*)(v1 + 18) = dword_404333;
    *(DWORD*)(v1 + 22) = v2;
    *((WORD*)v1 + 13) = 1;
    *((WORD*)v1 + 14) = 24;
    *(DWORD*)(v1 + 30) = 0;
    *(DWORD*)(v1 + 34) = 0;
    *(DWORD*)(v1 + 38) = 0;
    *(DWORD*)(v1 + 42) = 0;
    *(DWORD*)(v1 + 46) = 0;
    *(DWORD*)(v1 + 50) = 0;
    v3 = (v2 - 1) * dword_40433F + 54;
    v4 = dword_404337;
    int idx_0 = 0;

    do {
        v10 = v4;
        v9 = v3;
        v5 = dword_404333;

        do {
            /*printf("v3: %x\n", v3);
            return 1;*/

            v1[v3] = v0[idx_0];
            v1[v3 + 1] = v0[idx_0 + 1];
            v1[v3 + 2] = v0[idx_0 + 2];
            idx_0 += 4;
            v3 += 3;
            --v5;
        } while (v5);
        v3 = v9 - dword_40433F;
        //if (v3 == 0x36)break;
        v4 = v10 - 1;
    } while (v10 != 1);

    result = dword_404337 * dword_40433F + 54;
    return result;
}
void Unpack_G00(const CHAR* FileName) {
    HANDLE hFile = CreateFileA(FileName, GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,       
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("[-] Error in CreateFileA!\n");
        return;
    }
    DWORD dwFileSize = GetFileSize(hFile, NULL);
    BYTE* buffer = (BYTE*)malloc(dwFileSize*2);
    ZeroMemory(buffer, dwFileSize);
    DWORD dwBytesToRead = dwFileSize;
    ReadFile(hFile, buffer, dwBytesToRead, &dwBytesToRead, NULL);
    printf("[+] BytesRead: %x\n", dwBytesToRead);
    LPCVOID lpBuffer = buffer;
    if (!(*(BYTE*)lpBuffer)) {
        DWORD fileLen;
        fileLen = *(DWORD*)((BYTE*)lpBuffer + 5) + 5;
        printf("[+] fileLen: %x\n", fileLen);
        BYTE* newBuf = (BYTE*)malloc(fileLen*2);
        DWORD dwUnpackSize = Unpack_2(*((BYTE*)lpBuffer + 0xD), newBuf, (BYTE*)((BYTE*)(lpBuffer) + 0xD), fileLen);
        FILE* out = fopen("D:\\N0zoM1z0\\Sec-Learning\\Reverse\\游戏逆向\\EXP\\g00cnv1\\etract", "wb");
        fwrite(newBuf, sizeof(BYTE), dwUnpackSize, out);
        printf("[+] Unpack Done!\n");
        // 9310000
        dword_404337 = *(unsigned __int16*)((char*)lpBuffer + 3);
        dword_404333 = *(unsigned __int16*)((char*)lpBuffer + 1);
        dword_40433F = (3 * dword_404333 + 3) & 0xFFFFFFFC;
        dword_404343 = dword_404337 * dword_40433F;
        LPCVOID pBMPBuffer = (BYTE*)malloc((16 * dword_404337 * dword_40433F + 54) + 1);

        DWORD dw_bmpSize = Trans2BMP_2(newBuf, pBMPBuffer);
        out = fopen("D:\\N0zoM1z0\\Sec-Learning\\Reverse\\游戏逆向\\EXP\\g00cnv1\\extract.bmp", "wb");
        fwrite(pBMPBuffer, sizeof(BYTE), dw_bmpSize, out);
        printf("[+] Transfer to BMP file done!\n");

    }
    else {

    }

}
int main() {
    Unpack_G00("D:\\N0zoM1z0\\Sec-Learning\\Reverse\\游戏逆向\\Rewrite\\g00\\FGSZ01B.g00");

}