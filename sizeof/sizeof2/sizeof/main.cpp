#include "stdio.h"
#include <memory>
// ��Ĭ�ϵ�����£�Ϊ�˷���Խṹ����Ԫ�صķ����������
// 1.���ṹ���ڵ�Ԫ�صĳ��ȶ�С�ڴ�������λ����ʱ�򣬱��Խṹ�������Ԫ��Ϊ���뵥λ��
// 2.����ṹ���ڴ��ڳ��ȴ��ڴ�����λ����Ԫ�أ����Դ�����λ����Ϊ���뵥λ��
typedef struct { // ���뵥λ��4��4 + 4 + 4 = 12
    char a;     // 1 byte
    int b;      // 4 bytes
    short c;    // 2 bytes
    char d;     // 1 byte
}struct_a;

typedef struct { // ���뵥λ��4��4 + 4 + 4 = 12
    char a;           // 1 byte
    char _pad0[3];    // padding to put 'b' on 4-byte boundary
    int b;            // 4 bytes
    short c;          // 2 bytes
    char d;           // 1 byte
    char _pad1[1];    // padding to make sizeof(x_) multiple of 4
}struct_b;

//struct_xǿ�� ģ1 ����.
# pragma pack (1)
typedef struct { // ���뵥λ��1��1 + 4 + 2 = 7
    char a;    // 1 byte
    int b;     // 4 bytes
    short c;   // 2 bytes
}struct_c;
# pragma pack ()

//struct_x��ǿ�� ģ2 ����.
# pragma pack (2) 
typedef struct { // ���뵥λ��2��2 + 4 + 2 = 8
    char a;    // 1 byte
    int b;     // 4 bytes
    short c;   // 2 bytes
}struct_d;
# pragma pack ()

//struct_x��ǿ�� ģ8����.
# pragma pack (8)
typedef struct { // ���뵥λ��4��4 + 4 + 4 = 12
    char a;    // 1 byte
    int b;     // 4 bytes
    short c;   // 2 bytes
}struct_e;
# pragma pack ()

typedef struct { // ���뵥λ��2��2 + 2 + 2 = 6
    char a;
    short b;
    char c;
}struct_f;

typedef struct { // ���뵥λ��2��2 + 2 = 4
    char a;
    char c;
    short b;
}struct_g;

typedef struct { // ���뵥λ��4��4 + 4 + 4 = 12
    char b;
    int a;
    short c;
}struct_h;

typedef struct { 
    unsigned char incon: 8;   /* inconռ�õ��ֽڵ�0~7��8λ */ 
    unsigned char txcolor: 4; /* txcolorռ�ø��ֽڵ�0~3λ��4λ */ 
    unsigned char bgcolor: 3; /* bgcolorռ�ø��ֽڵ�4~6λ��3λ */ 
    unsigned char blink: 1;   /* blinkռ�ø��ֽڵĵ�7λ */ 
}struct_i;  

typedef struct {  // �����ṹ��Ҫ��2��sizeof��unsigned short��������
    unsigned short   incon: 8; 
    unsigned short   txcolor: 4;
    unsigned short   bgcolor: 3;
    unsigned short   blink: 1;
}struct_j;  

typedef struct { // �����ṹ��Ҫ��4��sizeof��unsigned int��������
    unsigned int   incon: 8; 
    unsigned int   txcolor: 4;
    unsigned int   bgcolor: 3;
    unsigned int  blink: 1;
}struct_k;  

typedef struct { // �����ṹ��Ҫ��4��sizeof��unsigned int��������
    unsigned   incon: 8; 
    unsigned   txcolor: 4;
    unsigned   bgcolor: 3;
    unsigned   blink: 1;
}struct_l;  

class CLASS_A { // ���뵥λ��1��1 + 0 = 1
    char x;
    void func();
};

class CLASS_B { // ���뵥λ��4��4 + 4 = 8
    char x;
    virtual void func();
};

class CLASS_C { // ���뵥λ��4��4 + 4 = 8
    char x;
    char y;
    virtual void func();
};

class CLASS_D{ // ���뵥λ��4��4 + 4 + 4 + 4 = 16
    char x;
    char* z;
    char y;
    virtual void func();
};

class CLASS_E { // ���뵥λ��1��1 + 1 = 2
    char x;
    CLASS_A a;
    void func();
};

class CLASS_F { // ���뵥λ��4��4 + 4 = 8
    char x;
    int y;
};

class CLASS_G { // ���뵥λ��4��4 + 8 = 12
    char x;
    CLASS_F f;
    void func();
};

class CLASS_H { // ���뵥λ��4��4 + 4 = 8
    char x;
    CLASS_F* f;
    void func();
};

class CLASS_I { // ���뵥λ��4��4 + 4 = 8
    char x;
    virtual void func();
    virtual void func1();
};

struct S { // ���뵥λ��4��4 + 4 + 8 = 16
    int    i;   // size 4
    short  j;   // size 2
    double k;   // size 8
};

#pragma pack(2)
struct T { // ���뵥λ��2��4 + 2 + 8 = 14
    int    i;
    short  j;
    double k;
};
# pragma pack ()

#define NAMEOF(x) #x
#define PRINT_SIZEOF(x) do { printf("sizeof(%s)=%d\n", NAMEOF(x), sizeof(x)); } while(0)
int main()
{
    PRINT_SIZEOF(struct_a);
    PRINT_SIZEOF(struct_b);
    PRINT_SIZEOF(struct_c);
    PRINT_SIZEOF(struct_d);
    PRINT_SIZEOF(struct_e);
    PRINT_SIZEOF(struct_f);
    PRINT_SIZEOF(struct_g);
    PRINT_SIZEOF(struct_h);
    PRINT_SIZEOF(struct_i);
    PRINT_SIZEOF(struct_j);
    PRINT_SIZEOF(struct_k);
    PRINT_SIZEOF(struct_l);
    PRINT_SIZEOF(CLASS_A);
    PRINT_SIZEOF(CLASS_B);
    PRINT_SIZEOF(CLASS_C);
    PRINT_SIZEOF(CLASS_D);
    PRINT_SIZEOF(CLASS_E);
    PRINT_SIZEOF(CLASS_F);
    PRINT_SIZEOF(CLASS_G);
    PRINT_SIZEOF(CLASS_H);
    PRINT_SIZEOF(CLASS_I);

    PRINT_SIZEOF(S);
    PRINT_SIZEOF(T);

    // typedef struct { 
    //	unsigned char incon: 8;   /* inconռ�õ��ֽڵ�0~7��8λ */ 
    //	unsigned char txcolor: 4; /* txcolorռ�ø��ֽڵ�0~3λ��4λ */ 
    //	unsigned char bgcolor: 3; /* bgcolorռ�ø��ֽڵ�4~6λ��3λ */ 
    //	unsigned char blink: 1;   /* blinkռ�ø��ֽڵĵ�7λ */ 
    // }struct_i; 
    struct_i a;
    memset(&a,  0, sizeof(a)); // �������ֽ���ÿһλ��Ϊ0
    memset(&a, -1, sizeof(a)); // �������ֽ���ÿһλ��Ϊ1
    a.incon   = 0;
    a.txcolor = 0;
    a.bgcolor = 0;
    a.blink   = 0;
    // FEA0 0000 0000 :00
    // FEA1 0000 0000 :00

    // FEA0 1111 1111 :ff
    // FEA1 1111 1111 :ff

    // FEA0 0000 0000 :00
    // FEA1 1111 1111 :ff

    // FEA0 0000 0000 :00
    // FEA1 1111 0000 :f0

    // FEA0 0000 0000 :00
    // FEA1 1000 0000 :80

    // FEA0 0000 0000 :00
    // FEA1 0000 0000 :00

    memset(&a, -1, sizeof(a)); // �������ֽ���ÿһλ��Ϊ1
    a.incon   = 1;
    a.txcolor = 1;
    a.bgcolor = 1;
    a.blink   = 1;
    // FEA0 1111 1111 :ff
    // FEA1 1111 1111 :ff

    // FEA0 0000 0001 :01
    // FEA1 1111 1111 :ff

    // FEA0 0000 0001 :01
    // FEA1 1111 0001 :f1

    // FEA0 0000 0001 :01
    // FEA1 1001 0001 :91

    // FEA0 0000 0001 :01
    // FEA1 1001 0001 :91
    return 0;
}