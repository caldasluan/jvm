#include <cstdint>
#include <cstring>
#include <string>
#include <cmath>
#include "instructions.h"
#include "../constants/CpTagConst.h"

int get_int(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    return x;
}

long long get_long(Frame &frame)
{
    uint64_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    x += (uint64_t)frame.operand_stack.top() << 32;
    frame.operand_stack.pop();
    return x;
}

float get_float(Frame &frame)
{
    float xf;
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    memcpy(&xf, &x, sizeof(float));
    return xf;
}

double get_double(Frame &frame)
{
    double xd;
    uint64_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    x += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    memcpy(&xd, &x, sizeof(double));
    return xd;
}

// Início das instruções

void nop(Frame &frame)
{
    // Não fazer nada
}

void aconst_null(Frame &frame) {}

void iconst_m1(Frame &frame)
{
    frame.operand_stack.push(-1);
}

void iconst_0(Frame &frame)
{
    frame.operand_stack.push(0);
}

void iconst_1(Frame &frame)
{
    frame.operand_stack.push(1);
}

void iconst_2(Frame &frame)
{
    frame.operand_stack.push(2);
}

void iconst_3(Frame &frame)
{
    frame.operand_stack.push(3);
}

void iconst_4(Frame &frame)
{
    frame.operand_stack.push(4);
}

void iconst_5(Frame &frame)
{
    frame.operand_stack.push(5);
}

void lconst_0(Frame &frame)
{
    frame.operand_stack.push(0);
    frame.operand_stack.push(0);
}

void lconst_1(Frame &frame)
{
    frame.operand_stack.push(0);
    frame.operand_stack.push(1);
}

void fconst_0(Frame &frame)
{
    float f = 0.0;
    uint32_t u;
    memcpy(&u, &f, sizeof(float));
    frame.operand_stack.push(u);
}

void fconst_1(Frame &frame)
{
    float f = 1.0;
    uint32_t u;
    memcpy(&u, &f, sizeof(float));
    frame.operand_stack.push(u);
}

void fconst_2(Frame &frame)
{
    float f = 2.0;
    uint32_t u;
    memcpy(&u, &f, sizeof(float));
    frame.operand_stack.push(u);
}

void dconst_0(Frame &frame)
{
    double d = 0.0;
    uint64_t u;
    memcpy(&u, &d, sizeof(double));

    frame.operand_stack.push(u >> 32);
    frame.operand_stack.push(u);
}

void dconst_1(Frame &frame)
{
    double d = 1.0;
    uint64_t u;
    memcpy(&u, &d, sizeof(double));

    frame.operand_stack.push(u >> 32);
    frame.operand_stack.push(u);
}

void bipush(Frame &frame)
{
    frame.pc++;
    frame.operand_stack.push((uint32_t)frame.code->code[frame.pc]);
}

void sipush(Frame &frame)
{
    frame.pc++;
    frame.operand_stack.push((((uint32_t)frame.code->code[frame.pc]) << 8) + (uint8_t)frame.code->code[frame.pc + 1]);
    frame.pc++;
}

// ToDo falta String
void ldc(Frame &frame)
{
    frame.pc++;
    uint8_t x = frame.code->code[frame.pc] - 1;
    uint8_t tag = frame.class_file->constant_pool[x].tag;
    if (tag == CpTagConst::CONSTANT_Integer)
    {
        frame.operand_stack.push(frame.class_file->constant_pool[x].get_int());
    }
    else if (tag == CpTagConst::CONSTANT_Float)
    {
        uint32_t in;
        float f = frame.class_file->constant_pool[x].get_float();
        memcpy(&in, &f, sizeof(float));
        frame.operand_stack.push(in);
    }
}

// ToDo falta String
void ldc_w(Frame &frame)
{
    uint8_t x = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    uint8_t tag = frame.class_file->constant_pool[x].tag;
    if (tag == CpTagConst::CONSTANT_Integer)
    {
        frame.operand_stack.push(frame.class_file->constant_pool[x].get_int());
    }
    else if (tag == CpTagConst::CONSTANT_Float)
    {
        uint32_t in;
        float f = frame.class_file->constant_pool[x].get_float();
        memcpy(&in, &f, sizeof(float));
        frame.operand_stack.push(in);
    }
}

void ldc2_w(Frame &frame)
{
    frame.pc++;
    uint16_t x = ((frame.code->code[frame.pc] << 8) | frame.code->code[frame.pc + 1] - 1);
    frame.pc++;
    uint8_t tag = frame.class_file->constant_pool[x].tag;
    if (tag == CpTagConst::CONSTANT_Long)
    {
        uint64_t ll = frame.class_file->constant_pool[x].get_long();
        frame.operand_stack.push(ll >> 32);
        frame.operand_stack.push(ll);
    }
    else if (tag == CpTagConst::CONSTANT_Double)
    {
        uint64_t in;
        double f = frame.class_file->constant_pool[x].get_double();
        memcpy(&in, &f, sizeof(double));
        frame.operand_stack.push(in >> 32);
        frame.operand_stack.push(in);
    }
}

void iload(Frame &frame)
{
    frame.pc++;
    frame.operand_stack.push(frame.local_variables[(uint32_t)frame.code->code[frame.pc]]);
}

void lload(Frame &frame)
{
    frame.pc++;
    frame.operand_stack.push(frame.local_variables[(uint32_t)frame.code->code[frame.pc]]);
    frame.operand_stack.push(frame.local_variables[(uint32_t)frame.code->code[frame.pc] + 1]);
}

void fload(Frame &frame)
{
    frame.pc++;
    frame.operand_stack.push(frame.local_variables[(uint32_t)frame.code->code[frame.pc]]);
}

void dload(Frame &frame)
{
    frame.pc++;
    frame.operand_stack.push(frame.local_variables[(uint32_t)frame.code->code[frame.pc]]);
    frame.operand_stack.push(frame.local_variables[(uint32_t)frame.code->code[frame.pc] + 1]);
}

void aload(Frame &frame)
{
    
}

void iload_0(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[0]);
}

void iload_1(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[1]);
}

void iload_2(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[2]);
}

void iload_3(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[3]);
}

void lload_0(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[0]);
    frame.operand_stack.push(frame.local_variables[1]);
}

void lload_1(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[1]);
    frame.operand_stack.push(frame.local_variables[2]);
}

void lload_2(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[2]);
    frame.operand_stack.push(frame.local_variables[3]);
}

void lload_3(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[3]);
    frame.operand_stack.push(frame.local_variables[4]);
}

void fload_0(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[0]);
}

void fload_1(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[1]);
}

void fload_2(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[2]);
}

void fload_3(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[3]);
}

void dload_0(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[0]);
    frame.operand_stack.push(frame.local_variables[1]);
}

void dload_1(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[1]);
    frame.operand_stack.push(frame.local_variables[2]);
}

void dload_2(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[2]);
    frame.operand_stack.push(frame.local_variables[3]);
}

void dload_3(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[3]);
    frame.operand_stack.push(frame.local_variables[4]);
}

void aload_0(Frame &frame) {}
void aload_1(Frame &frame) {}
void aload_2(Frame &frame) {}
void aload_3(Frame &frame) {}
void iaload(Frame &frame) {}
void laload(Frame &frame) {}
void faload(Frame &frame) {}
void daload(Frame &frame) {}
void aaload(Frame &frame) {}
void baload(Frame &frame) {}
void caload(Frame &frame) {}
void saload(Frame &frame) {}

void istore(Frame &frame)
{
    frame.pc++;
    frame.local_variables[(uint32_t)frame.code->code[frame.pc]] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void lstore(Frame &frame)
{
    frame.pc++;
    frame.local_variables[(uint32_t)frame.code->code[frame.pc] + 1] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[(uint32_t)frame.code->code[frame.pc]] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void fstore(Frame &frame)
{
    frame.pc++;
    frame.local_variables[(uint32_t)frame.code->code[frame.pc]] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void dstore(Frame &frame)
{
    frame.pc++;
    frame.local_variables[(uint32_t)frame.code->code[frame.pc] + 1] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[(uint32_t)frame.code->code[frame.pc]] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void astore(Frame &frame) {}

void istore_0(Frame &frame)
{
    frame.local_variables[0] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void istore_1(Frame &frame)
{
    frame.local_variables[1] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void istore_2(Frame &frame)
{
    frame.local_variables[2] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void istore_3(Frame &frame)
{
    frame.local_variables[1] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void lstore_0(Frame &frame)
{
    frame.local_variables[1] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[0] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void lstore_1(Frame &frame)
{
    frame.local_variables[2] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[1] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void lstore_2(Frame &frame)
{
    frame.local_variables[3] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[2] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void lstore_3(Frame &frame)
{
    frame.local_variables[4] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[3] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void fstore_0(Frame &frame)
{
    frame.local_variables[0] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void fstore_1(Frame &frame)
{
    frame.local_variables[1] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void fstore_2(Frame &frame)
{
    frame.local_variables[2] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void fstore_3(Frame &frame)
{
    frame.local_variables[3] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void dstore_0(Frame &frame)
{
    frame.local_variables[1] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[0] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void dstore_1(Frame &frame)
{
    frame.local_variables[2] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[1] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void dstore_2(Frame &frame)
{
    frame.local_variables[3] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[2] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void dstore_3(Frame &frame)
{
    frame.local_variables[4] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[3] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void astore_0(Frame &frame) {}
void astore_1(Frame &frame) {}
void astore_2(Frame &frame) {}
void astore_3(Frame &frame) {}
void iastore(Frame &frame) {}
void lastore(Frame &frame) {}
void fastore(Frame &frame) {}
void dastore(Frame &frame) {}
void aastore(Frame &frame) {}
void bastore(Frame &frame) {}
void castore(Frame &frame) {}
void sastore(Frame &frame) {}

void pop(Frame &frame)
{
    frame.operand_stack.pop();
}

void pop2(Frame &frame)
{
    frame.operand_stack.pop();
    frame.operand_stack.pop();
}

void dup(Frame &frame)
{
    frame.operand_stack.push(frame.operand_stack.top());
}

void dup_x1(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(x);
    frame.operand_stack.push(y);
    frame.operand_stack.push(x);
}

void dup_x2(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t z = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(x);
    frame.operand_stack.push(z);
    frame.operand_stack.push(y);
    frame.operand_stack.push(x);
}

void dup2(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.push(x);
    frame.operand_stack.push(y);
    frame.operand_stack.push(x);
}

void dup2_x1(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t z = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(y);
    frame.operand_stack.push(x);
    frame.operand_stack.push(z);
    frame.operand_stack.push(y);
    frame.operand_stack.push(x);
}

void dup2_x2(Frame &frame)
{
    uint32_t w = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t z = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(x);
    frame.operand_stack.push(w);
    frame.operand_stack.push(z);
    frame.operand_stack.push(y);
    frame.operand_stack.push(x);
    frame.operand_stack.push(w);
}

void swap(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(x);
    frame.operand_stack.push(y);
}

void iadd(Frame &frame)
{
    frame.operand_stack.push(get_int(frame) + get_int(frame));
}

void ladd(Frame &frame)
{
    long long x = get_long(frame);
    long long y = get_long(frame);
    x += y;
    frame.operand_stack.push(x >> 32);
    frame.operand_stack.push(x);
}

void fadd(Frame &frame)
{
    uint32_t x;
    float xf = get_float(frame);
    float yf = get_float(frame);
    xf += yf;
    memcpy(&x, &xf, sizeof(float));
    frame.operand_stack.push(x);
}

void dadd(Frame &frame)
{
    double xd = get_double(frame);
    double yd = get_double(frame);
    uint64_t x;
    xd += yd;
    memcpy(&x, &xd, sizeof(double));
    frame.operand_stack.push(x >> 32);
    frame.operand_stack.push(x);
}

void isub(Frame &frame)
{
    int x = get_int(frame);
    int y = get_int(frame);
    frame.operand_stack.push(y - x);
}

void lsub(Frame &frame)
{
    long long x = get_long(frame);
    long long y = get_long(frame);
    y -= x;
    frame.operand_stack.push(y >> 32);
    frame.operand_stack.push(y);
}

void fsub(Frame &frame)
{
    float xf = get_float(frame);
    float yf = get_float(frame);
    uint32_t x;
    yf -= xf;
    memcpy(&x, &yf, sizeof(float));
    frame.operand_stack.push(x);
}

void dsub(Frame &frame)
{
    double xd = get_double(frame);
    double yd = get_double(frame);
    uint64_t x;
    yd -= xd;
    memcpy(&x, &yd, sizeof(double));
    frame.operand_stack.push(x >> 32);
    frame.operand_stack.push(x);
}

void imul(Frame &frame)
{
    int x = get_int(frame);
    int y = get_int(frame);
    frame.operand_stack.push(x * y);
}

void lmul(Frame &frame)
{
    long long x = get_long(frame);
    long long y = get_long(frame);
    y *= x;
    frame.operand_stack.push(y >> 32);
    frame.operand_stack.push(y);
}

void fmul(Frame &frame)
{
    float xf = get_float(frame);
    float yf = get_float(frame);
    uint32_t x;
    yf *= xf;
    memcpy(&x, &yf, sizeof(float));
    frame.operand_stack.push(x);
}

void dmul(Frame &frame)
{
    double xd = get_double(frame);
    double yd = get_double(frame);
    uint64_t x;
    yd *= xd;
    memcpy(&x, &yd, sizeof(double));
    frame.operand_stack.push(x >> 32);
    frame.operand_stack.push(x);
}

void idiv(Frame &frame)
{
    int x = get_int(frame);
    int y = get_int(frame);
    frame.operand_stack.push(y / x);
}

void ldiv(Frame &frame)
{
    long long x = get_long(frame);
    long long y = get_long(frame);
    y /= x;
    frame.operand_stack.push(y >> 32);
    frame.operand_stack.push(y);
}

void fdiv(Frame &frame)
{
    float xf = get_float(frame);
    float yf = get_float(frame);
    uint32_t x;
    yf /= xf;
    memcpy(&x, &yf, sizeof(float));
    frame.operand_stack.push(x);
}

void ddiv(Frame &frame)
{
    double xd = get_double(frame);
    double yd = get_double(frame);
    uint64_t x;
    yd /= xd;
    memcpy(&x, &yd, sizeof(double));
    frame.operand_stack.push(x >> 32);
    frame.operand_stack.push(x);
}

void irem(Frame &frame)
{
    int x = get_int(frame);
    int y = get_int(frame);
    frame.operand_stack.push(y % x);
}

void lrem(Frame &frame)
{
    long long x = get_long(frame);
    long long y = get_long(frame);
    y %= x;
    frame.operand_stack.push(y >> 32);
    frame.operand_stack.push(y);
}

void frem(Frame &frame)
{
    float xf = get_float(frame);
    float yf = get_float(frame);
    uint32_t x;
    yf = fmod(yf, xf);
    memcpy(&x, &yf, sizeof(float));
    frame.operand_stack.push(x);
}

void drem(Frame &frame)
{
    double xd = get_double(frame);
    double yd = get_double(frame);
    uint64_t x;
    yd = fmod(yd, xd);
    memcpy(&x, &yd, sizeof(double));
    frame.operand_stack.push(x >> 32);
    frame.operand_stack.push(x);
}

void ineg(Frame &frame)
{
    frame.operand_stack.push(get_int(frame) * -1);
}

void lneg(Frame &frame)
{
    long long y = get_long(frame);
    y *= -1;
    frame.operand_stack.push(y >> 32);
    frame.operand_stack.push(y);
}

void fneg(Frame &frame)
{
    float xf = get_float(frame);
    uint32_t x;
    xf *= -1;
    memcpy(&x, &xf, sizeof(float));
    frame.operand_stack.push(x);
}

void dneg(Frame &frame)
{
    double xd = get_double(frame);
    uint64_t x;
    xd *= -1;
    memcpy(&x, &xd, sizeof(double));
    frame.operand_stack.push(x >> 32);
    frame.operand_stack.push(x);
}

void ishl(Frame &frame)
{
    int x = get_int(frame) & 0x1F;
    int y = get_int(frame);
    frame.operand_stack.push(y << x);
}

void lshl(Frame &frame)
{
    int y = get_int(frame) & 0x3F;
    long long x = get_long(frame);
    x <<= y;
    frame.operand_stack.push(x >> 32);
    frame.operand_stack.push(x);
}

void ishr(Frame &frame)
{
    uint64_t mask = 0;
    int x = get_int(frame) & 0x1F;
    int y = get_int(frame);
    if ((y & 0x80000000) != 0)
        mask = mask_shift[x + 32];
    frame.operand_stack.push((y >> x) | mask);
}

void lshr(Frame &frame)
{
    uint64_t mask = 0;
    int x = get_int(frame) & 0x3F;
    long long y = get_long(frame);
    if ((y & 0x8000000000000000) != 0)
        mask = mask_shift[x];
    y = (y >> x) | mask;
    frame.operand_stack.push(y >> 32);
    frame.operand_stack.push(y);
}

void iushr(Frame &frame) {
    
    int x = get_int(frame) & 0x1F;
    int y = get_int(frame);
    uint64_t mask = ~mask_shift[x + 32];
    frame.operand_stack.push((y >> x) & mask);
}

void lushr(Frame &frame) {
    int x = get_int(frame) & 0x3F;
    long long y = get_long(frame);
    uint64_t mask = ~mask_shift[x];
    y = (y >> x) | mask;
    frame.operand_stack.push(y >> 32);
    frame.operand_stack.push(y);
}

void iand(Frame &frame)
{
    int x = get_int(frame);
    int y = get_int(frame);
    frame.operand_stack.push(x & y);
}

void land(Frame &frame)
{
    long long x = get_long(frame);
    long long y = get_long(frame);
    y &= x;
    frame.operand_stack.push(y >> 32);
    frame.operand_stack.push(y);
}

void ior(Frame &frame)
{
    int x = get_int(frame);
    int y = get_int(frame);
    frame.operand_stack.push(x | y);
}

void lor(Frame &frame)
{
    long long x = get_long(frame);
    long long y = get_long(frame);
    y |= x;
    frame.operand_stack.push(y >> 32);
    frame.operand_stack.push(y);
}

void ixor(Frame &frame)
{
    int x = get_int(frame);
    int y = get_int(frame);
    frame.operand_stack.push(x ^ y);
}

void lxor(Frame &frame)
{
    long long x = get_long(frame);
    long long y = get_long(frame);
    y ^= x;
    frame.operand_stack.push(y >> 32);
    frame.operand_stack.push(y);
}

void iinc(Frame &frame)
{
    uint16_t index = frame.code->code[++frame.pc];
    int32_t add = (int32_t)(frame.code->code[++frame.pc]);
    frame.local_variables[index] = (int32_t)(frame.local_variables[index]) + add;
}

void i2l(Frame &frame)
{
    long x = get_int(frame);
    frame.operand_stack.push(x >> 32);
    frame.operand_stack.push(x);
}

void i2f(Frame &frame)
{
    float x = get_int(frame);
    uint32_t y;
    memcpy(&y, &x, sizeof(float));
    frame.operand_stack.push(y);
}

void i2d(Frame &frame)
{
    double x = get_int(frame);
    uint64_t y;
    memcpy(&y, &x, sizeof(double));
    frame.operand_stack.push(y >> 32);
    frame.operand_stack.push(y);
}

void l2i(Frame &frame) {
    frame.operand_stack.push((int)get_long(frame));
}

void l2f(Frame &frame)
{
    long long x = get_long(frame);
    float y = x;
    uint32_t z;
    memcpy(&z, &y, sizeof(float));
    frame.operand_stack.push(z);
}

void l2d(Frame &frame)
{
    long long x = get_long(frame);
    double y = x;
    uint64_t z;
    memcpy(&z, &y, sizeof(double));
    frame.operand_stack.push(z >> 32);
    frame.operand_stack.push(z);
}

void f2i(Frame &frame)
{
    int x = get_float(frame);
    frame.operand_stack.push(x);
}

void f2l(Frame &frame)
{
    long long y = get_float(frame);
    frame.operand_stack.push(y >> 32);
    frame.operand_stack.push(y);
}

void f2d(Frame &frame)
{
    double d = get_float(frame);
    uint64_t y;
    memcpy(&y, &d, sizeof(double));
    frame.operand_stack.push(y >> 32);
    frame.operand_stack.push(y);
}

void d2i(Frame &frame)
{
    frame.operand_stack.push((int)get_double(frame));
}

void d2l(Frame &frame)
{
    long long ll = get_double(frame);
    frame.operand_stack.push(ll >> 32);
    frame.operand_stack.push(ll);
}

void d2f(Frame &frame)
{
    float f = get_double(frame);
    uint32_t z;
    memcpy(&z, &f, sizeof(float));
    frame.operand_stack.push(z);
}

void i2b(Frame &frame)
{
    uint32_t x = get_int(frame) & 0x000000FF;
    if ((x & 0x00000080) == 0x00000080)
        x |= 0xFFFFFF00;
    frame.operand_stack.push(x);
}

void i2c(Frame &frame)
{
    frame.operand_stack.push(get_int(frame) & 0x0000FFFF);
}

void i2s(Frame &frame) {
    frame.operand_stack.push(get_int(frame) & 0x0000FFFF);
}

void lcmp(Frame &frame)
{
    long long x = get_long(frame);
    long long y = get_long(frame);
    frame.operand_stack.push(y > x ? 1 : y < x ? -1 : 0);
}

// Todo tratar NaN
void fcmpl(Frame &frame)
{
    float fval2 = get_float(frame);
    float fval1 = get_float(frame);
    frame.operand_stack.push(fval1 > fval2 ? 1 : fval1 < fval2 ? -1 : 0);
}

// Todo tratar NaN
void fcmpg(Frame &frame)
{
    float fval2 = get_float(frame);
    float fval1 = get_float(frame);
    frame.operand_stack.push(fval1 > fval2 ? 1 : fval1 < fval2 ? -1 : 0);
}

// Todo tratar NaN
void dcmpl(Frame &frame)
{
    double val2 = get_double(frame);
    double val1 = get_double(frame);
    frame.operand_stack.push(val1 > val2 ? 1 : val1 < val2 ? -1 : 0);
}

// Todo tratar NaN
void dcmpg(Frame &frame)
{
    double val2 = get_double(frame);
    double val1 = get_double(frame);
    frame.operand_stack.push(val1 > val2 ? 1 : val1 < val2 ? -1 : 0);
}

void ifeq(Frame &frame)
{
    if (get_int(frame) == 0)
    {
        frame.pc += (((uint16_t)frame.code->code[frame.pc + 1] << 8) | (uint16_t)frame.code->code[frame.pc + 2]) - 1;
    }
    else
    {
        frame.pc += 2;
    }
}

void ifne(Frame &frame)
{
    if (get_int(frame) != 0)
    {
        frame.pc += (((uint16_t)frame.code->code[frame.pc + 1] << 8) | (uint16_t)frame.code->code[frame.pc + 2]) - 1;
    }
    else
    {
        frame.pc += 2;
    }
}

void iflt(Frame &frame)
{
    if (get_int(frame) < 0)
    {
        frame.pc += (((uint16_t)frame.code->code[frame.pc + 1] << 8) | (uint16_t)frame.code->code[frame.pc + 2]) - 1;
    }
    else
    {
        frame.pc += 2;
    }
}

void ifge(Frame &frame)
{
    if (get_int(frame) >= 0)
    {
        frame.pc += (((uint16_t)frame.code->code[frame.pc + 1] << 8) | (uint16_t)frame.code->code[frame.pc + 2]) - 1;
    }
    else
    {
        frame.pc += 2;
    }
}

void ifgt(Frame &frame)
{
    if (get_int(frame) > 0)
    {
        frame.pc += (((uint16_t)frame.code->code[frame.pc + 1] << 8) | (uint16_t)frame.code->code[frame.pc + 2]) - 1;
    }
    else
    {
        frame.pc += 2;
    }
}

void ifle(Frame &frame)
{
    if (get_int(frame) <= 0)
    {
        frame.pc += (((uint16_t)frame.code->code[frame.pc + 1] << 8) | (uint16_t)frame.code->code[frame.pc + 2]) - 1;
    }
    else
    {
        frame.pc += 2;
    }
}

void if_icmpeq(Frame &frame)
{   
    int32_t x = get_int(frame);
    int32_t y = get_int(frame);
    int32_t offset = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    if(y == x)
    {
        frame.pc += offset - 3;
    }
}

void if_icmpne(Frame &frame)
{
    int32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    int32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    int32_t offset = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    if(y != x)
    {
        frame.pc += offset - 3;
    }
}

void if_icmplt(Frame &frame)
{
    int32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    int32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    int32_t offset = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    if(y < x)
    {
        frame.pc += offset - 3;
    }
}

void if_icmpge(Frame &frame)
{
    int32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    int32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    int32_t offset = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    if(y >= x)
    {
        frame.pc += offset - 3;
    }
}

void if_icmpgt(Frame &frame)
{
    int32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    int32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    int32_t offset = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    if(y > x)
    {
        frame.pc += offset - 3;
    }
}

void if_icmple(Frame &frame)
{
    int32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    int32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    int32_t offset = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    if(y <= x)
    {
        frame.pc += offset - 3;
    }
}

void if_acmpeq(Frame &frame) {}
void if_acmpne(Frame &frame) {}

void c_goto(Frame &frame)
{
    frame.pc += (int32_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]) - 3;
}

void jsr(Frame &frame)
{
    int32_t offset = ((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
    frame.operand_stack.push(frame.pc + 1);
    frame.pc += offset - 3;
}

void ret(Frame &frame)
{
    frame.pc = frame.local_variables[frame.code->code[++frame.pc]] - 1;
}

// TODO switchs
void tableswitch(Frame &frame) {}
void lookupswitch(Frame &frame) {}

void ireturn(Frame &frame)
{
    frame.ret_words = 1;
    frame.pc = frame.code->code_length;
}

void lreturn(Frame &frame)
{
    frame.ret_words = 2;
    frame.pc = frame.code->code_length;
}

void freturn(Frame &frame)
{
    frame.ret_words = 1;
    frame.pc = frame.code->code_length;
}

void dreturn(Frame &frame)
{
    frame.ret_words = 2;
    frame.pc = frame.code->code_length;
}

void areturn(Frame &frame)
{
    frame.ret_words = 1;
    frame.pc = frame.code->code_length;
}

void c_return(Frame &frame)
{
    frame.pc = frame.code->code_length;
}

// ToDo implementar
void getstatic(Frame &frame)
{
    frame.pc++;
    frame.pc++;
}

void putstatic(Frame &frame) {}
void getfield(Frame &frame) {}
void putfield(Frame &frame) {}

// ToDo terminar método, corrigir char
void invokevirtual(Frame &frame)
{
    frame.pc++;
    uint16_t x = ((uint16_t)frame.code->code[frame.pc]) << 8;
    frame.pc++;
    x += (uint16_t)frame.code->code[frame.pc];
    std::string class_name = frame.class_file->get_string_constant_pool(x);
    std::string method_name = frame.class_file->get_string_constant_pool(x, 1);
    std::string method_desc = frame.class_file->get_string_constant_pool(x, 2);

    // Simulação do println
    if (class_name.compare("java/io/PrintStream") == 0 && method_name.compare("println") == 0)
    {
        if (method_desc.compare("(C)V") == 0)
        {
            printf("%c\n", frame.operand_stack.top());
            frame.operand_stack.pop();
        }
        else if (method_desc.compare("(I)V") == 0)
        {
            printf("%d\n", frame.operand_stack.top());
            frame.operand_stack.pop();
        }
        else if (method_desc.compare("(J)V") == 0)
        {
            uint32_t a = frame.operand_stack.top();
            frame.operand_stack.pop();
            uint64_t b = frame.operand_stack.top();
            frame.operand_stack.pop();
            printf("%lld\n", (b << 32) + (long long)a);
        }
        else if (method_desc.compare("(F)V") == 0)
        {
            uint32_t a = frame.operand_stack.top();
            frame.operand_stack.pop();
            float f;
            memcpy(&f, &a, sizeof(float));
            printf("%f\n", f);
        }
        else if (method_desc.compare("(D)V") == 0)
        {
            uint64_t a = frame.operand_stack.top();
            frame.operand_stack.pop();
            uint64_t b = frame.operand_stack.top();
            frame.operand_stack.pop();
            b = (b << 32) | a;
            double d;
            memcpy(&d, &b, sizeof(double));
            printf("%lf\n", d);
        }
    }
}

void invokespecial(Frame &frame) {}
void invokestatic(Frame &frame) {}
void invokeinterface(Frame &frame) {}
void invokedynamic(Frame &frame) {}
void c_new(Frame &frame) {}
void newarray(Frame &frame) {}
void anewarray(Frame &frame) {}
void arraylength(Frame &frame) {}
void athrow(Frame &frame) {}
void checkcast(Frame &frame) {}
void instanceof (Frame & frame) {}
void monitorenter(Frame &frame) {}
void monitorexit(Frame &frame) {}

void wide(Frame &frame)
{
    uint8_t opcode = frame.code->code[++frame.pc];
    if(opcode == 0x84)
    {
        uint16_t index = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
        int32_t add = (int32_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
        frame.local_variables[index] = (int32_t)(frame.local_variables[index]) + add;
    }
    else if(opcode == 0x16 || opcode == 0x18)
    {
        uint16_t index = (uint16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
        frame.operand_stack.push(frame.local_variables[index]);
        frame.operand_stack.push(frame.local_variables[index + 1]);
    }
    else if(opcode == 0x15 || opcode == 0x17 || opcode == 0x19)
    {
        uint16_t index = (uint16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
        frame.operand_stack.push(frame.local_variables[index]);
    }
    else if(opcode == 0x37 || opcode == 0x39)
    {
        uint16_t index = (uint16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
        frame.local_variables[index + 1] = frame.operand_stack.top();
        frame.operand_stack.pop();
        frame.local_variables[index] = frame.operand_stack.top();
        frame.operand_stack.pop();
    }
    else if(opcode == 0xa9)
    {
        uint16_t index = (uint16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
        frame.pc = frame.local_variables[index] - 1;
    }
    else
    {
        uint16_t index = (uint16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
        frame.local_variables[index] = frame.operand_stack.top();
        frame.operand_stack.pop();
    }
    
}

void multianewarray(Frame &frame) {}
void ifnull(Frame &frame) {}
void ifnonnull(Frame &frame) {}

void goto_w(Frame &frame)
{
    frame.pc += (int32_t)((frame.code->code[++frame.pc] << 24) | (frame.code->code[++frame.pc] << 16) | (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
    frame.pc -= 5;
}
void jsr_w(Frame &frame)
{
    int32_t offset = ((frame.code->code[++frame.pc] << 24) | (frame.code->code[++frame.pc] << 16) | (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
    frame.operand_stack.push(frame.pc + 1);
    frame.pc += offset - 5;
}