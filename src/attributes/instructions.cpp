#include <cstdint>
#include <cstring>
#include "instructions.h"

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

void sipush(Frame &frame) {
    frame.pc++;
    frame.operand_stack.push((((uint32_t)frame.code->code[frame.pc]) << 8) + frame.code->code[frame.pc + 1]);
    frame.pc++;
}

void ldc(Frame &frame) {}
void ldc_w(Frame &frame) {}
void ldc2_w(Frame &frame) {}

void iload(Frame &frame) {
    frame.pc++;
    frame.operand_stack.push(frame.local_variables[(uint32_t)frame.code->code[frame.pc]]);
}

void lload(Frame &frame) {
    frame.pc++;
    frame.operand_stack.push(frame.local_variables[(uint32_t)frame.code->code[frame.pc]]);
    frame.pc++;
    frame.operand_stack.push(frame.local_variables[(uint32_t)frame.code->code[frame.pc]]);
}

void fload(Frame &frame) {
    frame.pc++;
    frame.operand_stack.push(frame.local_variables[(uint32_t)frame.code->code[frame.pc]]);
}

void dload(Frame &frame) {
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

void lload_0(Frame &frame) {
    frame.operand_stack.push(frame.local_variables[0]);
    frame.operand_stack.push(frame.local_variables[1]);
}

void lload_1(Frame &frame) {
    frame.operand_stack.push(frame.local_variables[1]);
    frame.operand_stack.push(frame.local_variables[2]);
}

void lload_2(Frame &frame) {
    frame.operand_stack.push(frame.local_variables[2]);
    frame.operand_stack.push(frame.local_variables[3]);
}

void lload_3(Frame &frame) {
    frame.operand_stack.push(frame.local_variables[3]);
    frame.operand_stack.push(frame.local_variables[4]);
}

void fload_0(Frame &frame) {
    frame.operand_stack.push(frame.local_variables[0]);
}

void fload_1(Frame &frame) {
    frame.operand_stack.push(frame.local_variables[1]);
}

void fload_2(Frame &frame) {
    frame.operand_stack.push(frame.local_variables[2]);
}

void fload_3(Frame &frame) {
    frame.operand_stack.push(frame.local_variables[3]);
}

void dload_0(Frame &frame) {
    frame.operand_stack.push(frame.local_variables[0]);
    frame.operand_stack.push(frame.local_variables[1]);
}

void dload_1(Frame &frame) {
    frame.operand_stack.push(frame.local_variables[1]);
    frame.operand_stack.push(frame.local_variables[2]);
}

void dload_2(Frame &frame) {
    frame.operand_stack.push(frame.local_variables[2]);
    frame.operand_stack.push(frame.local_variables[3]);
}

void dload_3(Frame &frame) {
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

void istore(Frame &frame) {
    frame.pc++;
    frame.local_variables[(uint32_t)frame.code->code[frame.pc]] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void lstore(Frame &frame) {
    frame.pc++;
    frame.local_variables[(uint32_t)frame.code->code[frame.pc]] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.pc++;
    frame.local_variables[(uint32_t)frame.code->code[frame.pc]] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void fstore(Frame &frame) {
    frame.pc++;
    frame.local_variables[(uint32_t)frame.code->code[frame.pc]] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void dstore(Frame &frame) {
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

void lstore_0(Frame &frame) {
    frame.local_variables[0] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[1] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void lstore_1(Frame &frame) {
    frame.local_variables[1] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[2] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void lstore_2(Frame &frame) {
    frame.local_variables[2] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[3] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void lstore_3(Frame &frame) {
    frame.local_variables[3] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[4] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void fstore_0(Frame &frame) {
    frame.local_variables[0] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void fstore_1(Frame &frame) {
    frame.local_variables[1] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void fstore_2(Frame &frame) {
    frame.local_variables[2] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void fstore_3(Frame &frame) {
    frame.local_variables[3] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void dstore_0(Frame &frame) {
    frame.local_variables[0] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[1] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void dstore_1(Frame &frame) {
    frame.local_variables[1] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[2] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void dstore_2(Frame &frame) {
    frame.local_variables[2] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[3] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void dstore_3(Frame &frame) {
    frame.local_variables[3] = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.local_variables[4] = frame.operand_stack.top();
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

void pop(Frame &frame) {
    frame.operand_stack.pop();
}

void pop2(Frame &frame) {
    frame.operand_stack.pop();
    frame.operand_stack.pop();
}

void dup(Frame &frame) {
    frame.operand_stack.push(frame.operand_stack.top());
}

void dup_x1(Frame &frame) {
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(x);
    frame.operand_stack.push(y);
    frame.operand_stack.push(x);
}

void dup_x2(Frame &frame) {
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

void dup2(Frame &frame) {
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.push(x);
    frame.operand_stack.push(y);
    frame.operand_stack.push(x);
}

void dup2_x1(Frame &frame) {
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

void dup2_x2(Frame &frame) {
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

void swap(Frame &frame) {
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

void ladd(Frame &frame) {}
void fadd(Frame &frame) {}
void dadd(Frame &frame) {}

void isub(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(x - y);
}

void lsub(Frame &frame) {}
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

void lmul(Frame &frame) {}
void fmul(Frame &frame) {}
void dmul(Frame &frame) {}

void idiv(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(x / y);
}

void ldiv(Frame &frame) {}
void fdiv(Frame &frame) {}
void ddiv(Frame &frame) {}

void irem(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(x % y);
}

void lrem(Frame &frame) {}
void frem(Frame &frame) {}
void drem(Frame &frame) {}

void ineg(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    frame.operand_stack.push(~x);
}

void lneg(Frame &frame) {}
void fneg(Frame &frame) {}
void dneg(Frame &frame) {}

void ishl(Frame &frame)
{
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top() & 0x1F;
    frame.operand_stack.pop();
    frame.operand_stack.push(x << y);
}

void lshl(Frame &frame) {}

void ishr(Frame &frame)
{
    // ToDo: Verificar
    uint32_t x = frame.operand_stack.top();
    frame.operand_stack.pop();
    uint32_t y = frame.operand_stack.top() & 0x1F;
    frame.operand_stack.pop();
    frame.operand_stack.push(x >> y);
}

void lshr(Frame &frame) {}
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

void land(Frame &frame) {}
void ior(Frame &frame) {}
void lor(Frame &frame) {}
void ixor(Frame &frame) {}
void lxor(Frame &frame) {}
void iinc(Frame &frame) {}
void i2l(Frame &frame) {}
void i2f(Frame &frame) {}
void i2d(Frame &frame) {}
void l2i(Frame &frame) {}
void l2f(Frame &frame) {}
void l2d(Frame &frame) {}
void f2i(Frame &frame) {}
void f2l(Frame &frame) {}
void f2d(Frame &frame) {}
void d2i(Frame &frame) {}
void d2l(Frame &frame) {}
void d2f(Frame &frame) {}
void i2b(Frame &frame) {}
void i2c(Frame &frame) {}
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
void c_return(Frame &frame) {}
void getstatic(Frame &frame) {}
void putstatic(Frame &frame) {}
void getfield(Frame &frame) {}
void putfield(Frame &frame) {}
void invokevirtual(Frame &frame) {}
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