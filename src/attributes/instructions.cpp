#include <cstdint>
#include <cstring>
#include <string>
#include "instructions.h"
#include "../constants/CpTagConst.h"

void nop(Frame &frame)
{
    // Não fazer nada
}

void aconst_null(Frame &frame)
{
    frame.operand_stack.push(0);
}

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
    double d = 0.0;
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

void ldc_w(Frame &frame) {}

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
        memcpy(&in, &f, sizeof(float));
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
    frame.pc++;
    frame.operand_stack.push(frame.local_variables[(uint32_t)frame.code->code[frame.pc]]);
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
    frame.pc++;
    frame.operand_stack.push(frame.local_variables[(uint32_t)frame.code->code[frame.pc]]);
}

void aload(Frame &frame) {}

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
    frame.local_variables[(uint32_t)frame.code->code[frame.pc]] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.pc++;
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
    frame.local_variables[(uint32_t)frame.code->code[frame.pc]] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.pc++;
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
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(x + y);
}

void ladd(Frame &frame)
{
    uint64_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    x += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    uint64_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    y += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    x += y;
    uint32_t z = x >> 32;
    frame.operand_stack.push(z);
    frame.operand_stack.push(x);
}

void fadd(Frame &frame)
{
    float xf, yf;
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    memcpy(&xf, &x, sizeof(float));
    memcpy(&yf, &y, sizeof(float));
    xf += yf;
    memcpy(&x, &xf, sizeof(float));
    frame.operand_stack.push(x);
}

void dadd(Frame &frame)
{
    double xd, yd;
    uint64_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    x += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    uint64_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    y += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    memcpy(&xd, &x, sizeof(double));
    memcpy(&yd, &y, sizeof(double));
    xd += yd;
    memcpy(&x, &xd, sizeof(double));
    uint32_t z = x >> 32;
    frame.operand_stack.push(z);
    frame.operand_stack.push(x);
}

void isub(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(y - x);
}

void lsub(Frame &frame) {
    uint64_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    x += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    uint64_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    y += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    y -= x;
    uint32_t z = y >> 32;
    frame.operand_stack.push(z);
    frame.operand_stack.push(y);
}

void fsub(Frame &frame) {}
void dsub(Frame &frame) {}

void imul(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(x * y);
}

void lmul(Frame &frame) {
    uint64_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    x += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    uint64_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    y += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    y *= x;
    uint32_t z = y >> 32;
    frame.operand_stack.push(z);
    frame.operand_stack.push(y);
}

void fmul(Frame &frame) {}
void dmul(Frame &frame) {}

void idiv(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(y / x);
}

void ldiv(Frame &frame) {
    uint64_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    x += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    uint64_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    y += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    y /= x;
    uint32_t z = y >> 32;
    frame.operand_stack.push(z);
    frame.operand_stack.push(y);
}

void fdiv(Frame &frame) {}
void ddiv(Frame &frame) {}

void irem(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(y % x);
}

void lrem(Frame &frame) {
    uint64_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    x += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    uint64_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    y += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    y %= x;
    uint32_t z = y >> 32;
    frame.operand_stack.push(z);
    frame.operand_stack.push(y);
}

void frem(Frame &frame) {}
void drem(Frame &frame) {}

void ineg(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(x * -1);
}

void lneg(Frame &frame) {
    uint64_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    y += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    y *= -1;
    uint32_t z = y >> 32;
    frame.operand_stack.push(z);
    frame.operand_stack.push(y);
}

void fneg(Frame &frame) {}
void dneg(Frame &frame) {}

void ishl(Frame &frame)
{
    uint32_t x = frame.operand_stack.top() & 0x1F;
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(y << x);
}

void lshl(Frame &frame) {
    uint32_t y = frame.operand_stack.top() & 0x3F;
    frame.operand_stack.pop();
    uint64_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    x += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    x <<= y;

    uint32_t z = x >> 32;
    frame.operand_stack.push(z);
    frame.operand_stack.push(x);
}

void ishr(Frame &frame)
{
    uint64_t mask = 0;
    uint32_t x = frame.operand_stack.top() & 0x1F;
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    if ((y & 0x80000000) != 0)
        mask = mask_shift[x + 32];
    frame.operand_stack.push((y >> x) | mask);
}

void lshr(Frame &frame) {
    uint64_t mask = 0;
    uint32_t x = frame.operand_stack.top() & 0x3F;
    frame.operand_stack.pop();
    uint64_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    y += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    if ((y & 0x8000000000000000) != 0)
        mask = mask_shift[x];
    y = (y >> x) | mask;
    uint32_t z = y >> 32;
    frame.operand_stack.push(z);
    frame.operand_stack.push(y);
}

void iushr(Frame &frame) {}
void lushr(Frame &frame) {}

void iand(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(x & y);
}

void land(Frame &frame) {
    uint64_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    x += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    uint64_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    y += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    y &= x;
    uint32_t z = y >> 32;
    frame.operand_stack.push(z);
    frame.operand_stack.push(y);
}

void ior(Frame &frame) {}
void lor(Frame &frame) {}
void ixor(Frame &frame) {}
void lxor(Frame &frame) {}
void iinc(Frame &frame) {}

void i2l(Frame &frame)
{
    long x = (int)frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(x >> 32);
    frame.operand_stack.push(x);
}

void i2f(Frame &frame)
{
    float x = (int)frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y;
    memcpy(&y, &x, sizeof(float));
    frame.operand_stack.push(y);
}

void i2d(Frame &frame)
{
    double x = (int)frame.operand_stack.top();
    frame.operand_stack.pop();
    uint64_t y;
    memcpy(&y, &x, sizeof(double));
    frame.operand_stack.push(y >> 32);
    frame.operand_stack.push(y);
}

void l2i(Frame &frame) {}

void l2f(Frame &frame) {
    long long x = frame.operand_stack.top();
    frame.operand_stack.pop();
    x += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    float y = x;
    uint32_t z;
    memcpy(&z, &y, sizeof(float));
    frame.operand_stack.push(z);
}

void l2d(Frame &frame) {
    long long x = frame.operand_stack.top();
    frame.operand_stack.pop();
    x += ((uint64_t)frame.operand_stack.top() << 32);
    frame.operand_stack.pop();
    double y = x;
    uint64_t z;
    memcpy(&z, &y, sizeof(double));
    frame.operand_stack.push(z >> 32);
    frame.operand_stack.push(z);
}

void f2i(Frame &frame) {}
void f2l(Frame &frame) {}
void f2d(Frame &frame) {}
void d2i(Frame &frame) {}
void d2l(Frame &frame) {}
void d2f(Frame &frame) {}

void i2b(Frame &frame)
{
    uint32_t x = frame.operand_stack.top() & 0x000000FF;
    if ((x & 0x00000080) == 0x00000080)
        x |= 0xFFFFFF00;
    frame.operand_stack.pop();
    frame.operand_stack.push(x);
}

void i2c(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(x & 0x0000FFFF);
}

void i2s(Frame &frame) {}
void lcmp(Frame &frame) {}
void fcmpl(Frame &frame) {}
void fcmpg(Frame &frame) {}
void dcmpl(Frame &frame) {}
void dcmpg(Frame &frame) {}
void ifeq(Frame &frame) {}
void ifne(Frame &frame) {}
void iflt(Frame &frame) {}
void ifge(Frame &frame) {}
void ifgt(Frame &frame) {}
void ifle(Frame &frame) {}
void if_icmpeq(Frame &frame) {}
void if_icmpne(Frame &frame) {}
void if_icmplt(Frame &frame) {}
void if_icmpge(Frame &frame) {}
void if_icmpgt(Frame &frame) {}
void if_icmple(Frame &frame) {}
void if_acmpeq(Frame &frame) {}
void if_acmpne(Frame &frame) {}
void c_goto(Frame &frame) {}
void jsr(Frame &frame) {}
void ret(Frame &frame) {}
void tableswitch(Frame &frame) {}
void lookupswitch(Frame &frame) {}
void ireturn(Frame &frame) {}
void lreturn(Frame &frame) {}
void freturn(Frame &frame) {}
void dreturn(Frame &frame) {}
void areturn(Frame &frame) {}

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
            printf("%lld\n", (b << 32) + a);
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
            uint32_t a = frame.operand_stack.top();
            frame.operand_stack.pop();
            uint64_t b = frame.operand_stack.top();
            frame.operand_stack.pop();
            b = (b << 32) + a;
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
void wide(Frame &frame) {}
void multianewarray(Frame &frame) {}
void ifnull(Frame &frame) {}
void ifnonnull(Frame &frame) {}
void goto_w(Frame &frame) {}
void jsr_w(Frame &frame) {}