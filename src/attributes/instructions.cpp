#include <algorithm>
#include <cstdint>
#include <cstring>
#include <string>
#include <cmath>
#include "instructions.h"
#include "../constants/CpTagConst.h"
#include "../model/Runtime.h"
#include "../module/ExecModule.h"

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

uint32_t gera_multiarray(int size_dim[], Runtime &runtime, uint32_t size, uint32_t dimensions)
{
    if (dimensions > 0)
    {
        array_t *ar = new array_t;
        ar->size = 4;
        ar->lenght = size_dim[dimensions];
        ar->bytes = new uint8_t[ar->lenght * 4]{0};

        for (int i = 0; i < ar->lenght; i++)
        {
            uint32_t reference = gera_multiarray(size_dim, runtime, size, dimensions - 1);
            ar->bytes[i * 4] = reference >> 24;
            ar->bytes[i * 4 + 1] = reference >> 16;
            ar->bytes[i * 4 + 2] = reference >> 8;
            ar->bytes[i * 4 + 3] = reference;
        }

        runtime.instances.push_back((uint8_t *)ar);

        return runtime.instances.size() - 1;
    }
    else
    {
        array_t *ar = new array_t;
        ar->size = size;
        ar->lenght = size_dim[dimensions];
        ar->bytes = new uint8_t[ar->lenght * size]{0};

        runtime.instances.push_back((uint8_t *)ar);

        return runtime.instances.size() - 1;
    }
}

// Início das instruções

void nop(Frame &frame) {} // Não fazer nada

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
    double d = 1.0;
    uint64_t u;
    memcpy(&u, &d, sizeof(double));

    frame.operand_stack.push(u >> 32);
    frame.operand_stack.push(u);
}

void bipush(Frame &frame)
{
    frame.pc++;
    frame.operand_stack.push((int8_t)frame.code->code[frame.pc]);
}

void sipush(Frame &frame)
{
    frame.pc++;
    frame.operand_stack.push((((uint32_t)frame.code->code[frame.pc]) << 8) + (uint8_t)frame.code->code[frame.pc + 1]);
    frame.pc++;
}

void ldc(Frame &frame)
{
    frame.pc++;
    uint8_t x = frame.code->code[frame.pc] - 1;
    uint8_t tag = frame.class_info->class_file->constant_pool[x].tag;
    if (tag == CpTagConst::CONSTANT_Integer)
    {
        frame.operand_stack.push(frame.class_info->class_file->constant_pool[x].get_int());
    }
    else if (tag == CpTagConst::CONSTANT_Float)
    {
        uint32_t in;
        float f = frame.class_info->class_file->constant_pool[x].get_float();
        memcpy(&in, &f, sizeof(float));
        frame.operand_stack.push(in);
    }
    else if (tag == CpTagConst::CONSTANT_String)
    {
        std::string ss = frame.class_info->class_file->get_string_constant_pool(x + 1);
        uint8_t *caracters = new uint8_t[ss.length() + 1]{0};
        for (int i = 0; i < ss.length() + 1; i++)
        {
            caracters[i] = ss.c_str()[i];
        }
        Runtime &runtime = Runtime::getInstance();
        frame.operand_stack.push(runtime.instances.size());
        runtime.instances.push_back(caracters);
    }
}

void ldc_w(Frame &frame)
{
    uint8_t x = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc] - 1;
    uint8_t tag = frame.class_info->class_file->constant_pool[x].tag;
    if (tag == CpTagConst::CONSTANT_Integer)
    {
        frame.operand_stack.push(frame.class_info->class_file->constant_pool[x].get_int());
    }
    else if (tag == CpTagConst::CONSTANT_Float)
    {
        uint32_t in;
        float f = frame.class_info->class_file->constant_pool[x].get_float();
        memcpy(&in, &f, sizeof(float));
        frame.operand_stack.push(in);
    }
    else if (tag == CpTagConst::CONSTANT_String)
    {
        std::string ss = frame.class_info->class_file->get_string_constant_pool(x + 1);
        uint8_t *caracters = new uint8_t[ss.length() + 1]{0};
        for (int i = 0; i < ss.length() + 1; i++)
        {
            caracters[i] = ss.c_str()[i];
        }
        Runtime &runtime = Runtime::getInstance();
        frame.operand_stack.push(runtime.instances.size());
        runtime.instances.push_back(caracters);
    }
}

void ldc2_w(Frame &frame)
{
    frame.pc++;
    uint16_t x = ((frame.code->code[frame.pc] << 8) | frame.code->code[frame.pc + 1] - 1);
    frame.pc++;
    uint8_t tag = frame.class_info->class_file->constant_pool[x].tag;
    if (tag == CpTagConst::CONSTANT_Long)
    {
        uint64_t ll = frame.class_info->class_file->constant_pool[x].get_long();
        frame.operand_stack.push(ll >> 32);
        frame.operand_stack.push(ll);
    }
    else if (tag == CpTagConst::CONSTANT_Double)
    {
        uint64_t in;
        double f = frame.class_info->class_file->constant_pool[x].get_double();
        memcpy(&in, &f, sizeof(double));
        frame.operand_stack.push(in >> 32);
        frame.operand_stack.push(in);
    }
}

void iload(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[(uint32_t)frame.code->code[++frame.pc]]);
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
    frame.operand_stack.push(frame.local_variables[frame.code->code[++frame.pc]]);
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

void aload_0(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[0]);
}

void aload_1(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[1]);
}

void aload_2(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[2]);
}

void aload_3(Frame &frame)
{
    frame.operand_stack.push(frame.local_variables[3]);
}

void iaload(Frame &frame)
{
    int index = get_int(frame);
    int reference = get_int(frame);

    Runtime &runtime = Runtime::getInstance();
    uint8_t *vetor = ((array_t *)runtime.instances[reference])->bytes;
    uint32_t size = ((array_t *)runtime.instances[reference])->size;

    frame.operand_stack.push((((uint32_t)vetor[index * size]) << 24) |
                             (((uint32_t)vetor[index * size + 1]) << 16) |
                             (((uint32_t)vetor[index * size + 2]) << 8) |
                             ((uint32_t)vetor[index * size + 3]));
}

void laload(Frame &frame)
{
    int index = get_int(frame);
    int reference = get_int(frame);

    Runtime &runtime = Runtime::getInstance();
    uint8_t *vetor = ((array_t *)runtime.instances[reference])->bytes;
    uint32_t size = ((array_t *)runtime.instances[reference])->size;

    frame.operand_stack.push((((uint32_t)vetor[index * size]) << 24) |
                             (((uint32_t)vetor[index * size + 1]) << 16) |
                             (((uint32_t)vetor[index * size + 2]) << 8) |
                             ((uint32_t)vetor[index * size + 3]));
    frame.operand_stack.push((((uint32_t)vetor[index * size + 4]) << 24) |
                             (((uint32_t)vetor[index * size + 5]) << 16) |
                             (((uint32_t)vetor[index * size + 6]) << 8) |
                             ((uint32_t)vetor[index * size + 7]));
}

void faload(Frame &frame)
{
    int index = get_int(frame);
    int reference = get_int(frame);

    Runtime &runtime = Runtime::getInstance();
    uint8_t *vetor = ((array_t *)runtime.instances[reference])->bytes;
    uint32_t size = ((array_t *)runtime.instances[reference])->size;

    frame.operand_stack.push((((uint32_t)vetor[index * size]) << 24) |
                             (((uint32_t)vetor[index * size + 1]) << 16) |
                             (((uint32_t)vetor[index * size + 2]) << 8) |
                             ((uint32_t)vetor[index * size + 3]));
}

void daload(Frame &frame)
{
    int index = get_int(frame);
    int reference = get_int(frame);

    Runtime &runtime = Runtime::getInstance();
    uint8_t *vetor = ((array_t *)runtime.instances[reference])->bytes;
    uint32_t size = ((array_t *)runtime.instances[reference])->size;

    frame.operand_stack.push((((uint32_t)vetor[index * size]) << 24) |
                             (((uint32_t)vetor[index * size + 1]) << 16) |
                             (((uint32_t)vetor[index * size + 2]) << 8) |
                             ((uint32_t)vetor[index * size + 3]));
    frame.operand_stack.push((((uint32_t)vetor[index * size + 4]) << 24) |
                             (((uint32_t)vetor[index * size + 5]) << 16) |
                             (((uint32_t)vetor[index * size + 6]) << 8) |
                             ((uint32_t)vetor[index * size + 7]));
}

void aaload(Frame &frame)
{
    int index = get_int(frame);
    int reference = get_int(frame);

    Runtime &runtime = Runtime::getInstance();
    uint8_t *vetor = ((array_t *)runtime.instances[reference])->bytes;
    uint32_t size = ((array_t *)runtime.instances[reference])->size;

    frame.operand_stack.push((((uint32_t)vetor[index * size]) << 24) |
                             (((uint32_t)vetor[index * size + 1]) << 16) |
                             (((uint32_t)vetor[index * size + 2]) << 8) |
                             ((uint32_t)vetor[index * size + 3]));
}

void baload(Frame &frame)
{
    int index = get_int(frame);
    int reference = get_int(frame);

    Runtime &runtime = Runtime::getInstance();
    uint8_t *vetor = ((array_t *)runtime.instances[reference])->bytes;
    uint32_t size = ((array_t *)runtime.instances[reference])->size;

    frame.operand_stack.push((int32_t)(int8_t)vetor[index * size]);
}

void caload(Frame &frame)
{
    int index = get_int(frame);
    int reference = get_int(frame);

    Runtime &runtime = Runtime::getInstance();
    uint8_t *vetor = ((array_t *)runtime.instances[reference])->bytes;
    uint32_t size = ((array_t *)runtime.instances[reference])->size;

    frame.operand_stack.push(vetor[index * size]);
}

void saload(Frame &frame)
{
    int index = get_int(frame);
    int reference = get_int(frame);

    Runtime &runtime = Runtime::getInstance();
    uint8_t *vetor = ((array_t *)runtime.instances[reference])->bytes;
    uint32_t size = ((array_t *)runtime.instances[reference])->size;

    frame.operand_stack.push((((int32_t)(int8_t)vetor[index * size]) << 8) |
                             ((uint32_t)vetor[index * size + 1]));
}

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

void astore(Frame &frame)
{
    frame.local_variables[frame.code->code[++frame.pc]] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

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
    frame.local_variables[3] = frame.operand_stack.top();
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

void astore_0(Frame &frame)
{
    frame.local_variables[0] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void astore_1(Frame &frame)
{
    frame.local_variables[1] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void astore_2(Frame &frame)
{
    frame.local_variables[2] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void astore_3(Frame &frame)
{
    frame.local_variables[3] = frame.operand_stack.top();
    frame.operand_stack.pop();
}

void iastore(Frame &frame)
{
    int value = get_int(frame);
    int index = get_int(frame);
    int reference = get_int(frame);

    Runtime &runtime = Runtime::getInstance();
    uint8_t *vetor = ((array_t *)runtime.instances[reference])->bytes;
    uint32_t size = ((array_t *)runtime.instances[reference])->size;

    vetor[index * size] = value >> 24;
    vetor[index * size + 1] = value >> 16;
    vetor[index * size + 2] = value >> 8;
    vetor[index * size + 3] = value;
}

void lastore(Frame &frame)
{
    long long value = get_long(frame);
    int index = get_int(frame);
    int reference = get_int(frame);

    Runtime &runtime = Runtime::getInstance();
    uint8_t *vetor = ((array_t *)runtime.instances[reference])->bytes;
    uint32_t size = ((array_t *)runtime.instances[reference])->size;

    vetor[index * size] = value >> 56;
    vetor[index * size + 1] = value >> 48;
    vetor[index * size + 2] = value >> 40;
    vetor[index * size + 3] = value >> 32;
    vetor[index * size + 4] = value >> 24;
    vetor[index * size + 5] = value >> 16;
    vetor[index * size + 6] = value >> 8;
    vetor[index * size + 7] = value;
}

void fastore(Frame &frame)
{
    int value = get_int(frame);
    int index = get_int(frame);
    int reference = get_int(frame);

    Runtime &runtime = Runtime::getInstance();
    uint8_t *vetor = ((array_t *)runtime.instances[reference])->bytes;
    uint32_t size = ((array_t *)runtime.instances[reference])->size;

    vetor[index * size] = value >> 24;
    vetor[index * size + 1] = value >> 16;
    vetor[index * size + 2] = value >> 8;
    vetor[index * size + 3] = value;
}

void dastore(Frame &frame)
{
    long long value = get_long(frame);
    int index = get_int(frame);
    int reference = get_int(frame);

    Runtime &runtime = Runtime::getInstance();
    uint8_t *vetor = ((array_t *)runtime.instances[reference])->bytes;
    uint32_t size = ((array_t *)runtime.instances[reference])->size;

    vetor[index * size] = value >> 56;
    vetor[index * size + 1] = value >> 48;
    vetor[index * size + 2] = value >> 40;
    vetor[index * size + 3] = value >> 32;
    vetor[index * size + 4] = value >> 24;
    vetor[index * size + 5] = value >> 16;
    vetor[index * size + 6] = value >> 8;
    vetor[index * size + 7] = value;
}

void aastore(Frame &frame)
{
    int value = get_int(frame);
    int index = get_int(frame);
    int reference = get_int(frame);

    Runtime &runtime = Runtime::getInstance();
    uint8_t *vetor = ((array_t *)runtime.instances[reference])->bytes;
    uint32_t size = ((array_t *)runtime.instances[reference])->size;

    vetor[index * size] = value >> 24;
    vetor[index * size + 1] = value >> 16;
    vetor[index * size + 2] = value >> 8;
    vetor[index * size + 3] = value;
}

void bastore(Frame &frame)
{
    int value = get_int(frame);
    int index = get_int(frame);
    int reference = get_int(frame);

    Runtime &runtime = Runtime::getInstance();
    uint8_t *vetor = ((array_t *)runtime.instances[reference])->bytes;
    uint32_t size = ((array_t *)runtime.instances[reference])->size;

    vetor[index * size] = value;
}

void castore(Frame &frame)
{
    int value = get_int(frame);
    int index = get_int(frame);
    int reference = get_int(frame);

    Runtime &runtime = Runtime::getInstance();
    uint8_t *vetor = ((array_t *)runtime.instances[reference])->bytes;
    uint32_t size = ((array_t *)runtime.instances[reference])->size;

    vetor[index * size] = value;
}

void sastore(Frame &frame)
{
    int value = get_int(frame);
    int index = get_int(frame);
    int reference = get_int(frame);

    Runtime &runtime = Runtime::getInstance();
    uint8_t *vetor = ((array_t *)runtime.instances[reference])->bytes;
    uint32_t size = ((array_t *)runtime.instances[reference])->size;

    vetor[index * size] = value >> 8;
    vetor[index * size + 1] = value;
}

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

void iushr(Frame &frame)
{

    int x = get_int(frame) & 0x1F;
    int y = get_int(frame);
    uint64_t mask = ~mask_shift[x + 32];
    frame.operand_stack.push((y >> x) & mask);
}

void lushr(Frame &frame)
{
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
    int32_t add = (int32_t)(int8_t)(frame.code->code[++frame.pc]);
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

void l2i(Frame &frame)
{
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

void i2s(Frame &frame)
{
    frame.operand_stack.push((int16_t)get_int(frame));
}

void lcmp(Frame &frame)
{
    long long x = get_long(frame);
    long long y = get_long(frame);
    frame.operand_stack.push(y > x ? 1 : y < x ? -1 : 0);
}

void fcmpl(Frame &frame)
{
    float fval2 = get_float(frame);
    float fval1 = get_float(frame);
    frame.operand_stack.push(fval1 > fval2 ? 1 : fval1 == fval2 ? 0 : -1);
}

void fcmpg(Frame &frame)
{
    float fval2 = get_float(frame);
    float fval1 = get_float(frame);
    frame.operand_stack.push(fval1 < fval2 ? -1 : fval1 == fval2 ? 0 : 1);
}

void dcmpl(Frame &frame)
{
    double val2 = get_double(frame);
    double val1 = get_double(frame);
    frame.operand_stack.push(val1 > val2 ? 1 : val1 == val2 ? 0 : -1);
}

void dcmpg(Frame &frame)
{
    double val2 = get_double(frame);
    double val1 = get_double(frame);
    frame.operand_stack.push(val1 < val2 ? -1 : val1 == val2 ? 0 : 1);
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
    int32_t offset = (int16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
    if (y == x)
        frame.pc += offset - 3;
}

void if_icmpne(Frame &frame)
{
    int32_t x = get_int(frame);
    int32_t y = get_int(frame);
    int32_t offset = (int16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
    if (y != x)
        frame.pc += offset - 3;
}

void if_icmplt(Frame &frame)
{
    int32_t x = get_int(frame);
    int32_t y = get_int(frame);
    int32_t offset = (int16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
    if (y < x)
        frame.pc += offset - 3;
}

void if_icmpge(Frame &frame)
{
    int32_t x = get_int(frame);
    int32_t y = get_int(frame);
    int32_t offset = (int16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
    if (y >= x)
        frame.pc += offset - 3;
}

void if_icmpgt(Frame &frame)
{
    int32_t x = get_int(frame);
    int32_t y = get_int(frame);
    int32_t offset = (int16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
    if (y > x)
        frame.pc += offset - 3;
}

void if_icmple(Frame &frame)
{
    int32_t x = get_int(frame);
    int32_t y = get_int(frame);
    int32_t offset = (int16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
    if (y <= x)
        frame.pc += offset - 3;
}

void if_acmpeq(Frame &frame)
{
    uint32_t x = get_int(frame);
    uint32_t y = get_int(frame);
    int32_t offset = (int16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
    if (y == x)
        frame.pc += offset - 3;
}

void if_acmpne(Frame &frame)
{
    uint32_t x = get_int(frame);
    uint32_t y = get_int(frame);
    int32_t offset = (int16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
    if (y != x)
        frame.pc += offset - 3;
}

void c_goto(Frame &frame)
{
    frame.pc += ((((int32_t)(int8_t)frame.code->code[++frame.pc]) << 8) | frame.code->code[++frame.pc]) - 3;
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

void tableswitch(Frame &frame)
{
    uint32_t instruction_pc = frame.pc;
    frame.pc += (4 - (frame.pc % 4)) % 4;
    int32_t def = (frame.code->code[frame.pc] << 24) | (frame.code->code[++frame.pc] << 16) | (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    int32_t low = (frame.code->code[++frame.pc] << 24) | (frame.code->code[++frame.pc] << 16) | (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    int32_t high = (frame.code->code[++frame.pc] << 24) | (frame.code->code[++frame.pc] << 16) | (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    frame.pc++;
    int32_t index = get_int(frame);
    if (index < low || index > high)
    {
        frame.pc = instruction_pc + def;
    }
    else
    {
        int32_t indice = frame.pc + (index - low) * 4;
        frame.pc = instruction_pc + ((frame.code->code[indice] << 24) | (frame.code->code[indice + 1] << 16) | (frame.code->code[indice + 2] << 8) | frame.code->code[indice + 3]);
    }
}

void lookupswitch(Frame &frame)
{
    uint32_t instruction_pc = frame.pc;
    frame.pc += (4 - (frame.pc % 4)) % 4;
    int32_t def = (frame.code->code[frame.pc] << 24) | (frame.code->code[++frame.pc] << 16) | (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    int32_t npairs = (frame.code->code[++frame.pc] << 24) | (frame.code->code[++frame.pc] << 16) | (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    int32_t key = get_int(frame);

    while (npairs--)
    {
        int32_t switch_key = (frame.code->code[++frame.pc] << 24) | (frame.code->code[++frame.pc] << 16) | (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
        int32_t offset = (frame.code->code[++frame.pc] << 24) | (frame.code->code[++frame.pc] << 16) | (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
        if (key == switch_key)
        {
            frame.pc = instruction_pc + offset;
            return;
        }
    }

    frame.pc = instruction_pc + def;
}

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

// TODO interromper a jvm e imprimir o erro.
void getstatic(Frame &frame)
{
    uint16_t field_ref_index = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    std::string class_name = frame.class_info->class_file->get_string_constant_pool(field_ref_index);
    uint8_t field_size = FieldInfo::field_size_bytes(frame.class_info->class_file->get_string_constant_pool(field_ref_index, 2));

    if (class_name.compare("java/lang/System") == 0) // Qualquer field acessado na java/lang/System eh essencialmente desprezado
    {
        frame.operand_stack.push(0);
        if (field_size == 8)
            frame.operand_stack.push(0);
        return;
    }

    Runtime &runtime = Runtime::getInstance();

    ClassInfo *class_info = ExecModule::prepare_class(runtime, class_name);

    if (class_info != nullptr)
    {
        auto field_it = class_info->staticIndexByName.find(frame.class_info->class_file->get_string_constant_pool(field_ref_index, 1));
        if (field_it != class_info->staticIndexByName.end())
        {
            uint8_t *bytes = (uint8_t *)(class_info->staticBytes + field_it->second);
            if (field_size <= 4) // campo com 1, 2 ou 4 bytes
            {
                uint32_t word;
                memcpy(&word + (sizeof(uint32_t) - field_size), bytes, field_size);
                frame.operand_stack.push(word);
            }
            else // campo com 8 bytes
            {
                frame.operand_stack.push(*(uint32_t *)(bytes + 4));
                frame.operand_stack.push(*(uint32_t *)bytes);
            }
        }
        else
        {
            printf("ERRO\n");
            // Field nao encontrado. TODO interromper a jvm e imprimir o erro.
            return;
        }
    }
    else
        frame.pc -= 3; // retorna pra essa instrucao apos rodar os metodos <clinit>
}

void putstatic(Frame &frame)
{
    uint16_t field_ref_index = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    std::string class_name = frame.class_info->class_file->get_string_constant_pool(field_ref_index);
    uint8_t field_size = FieldInfo::field_size_bytes(frame.class_info->class_file->get_string_constant_pool(field_ref_index, 2));

    if (class_name.compare("java/lang/System") == 0) // Qualquer field acessado na java/lang/System eh essencialmente desprezado
    {
        frame.operand_stack.pop();
        if (field_size == 8)
            frame.operand_stack.pop();
        return;
    }

    Runtime &runtime = Runtime::getInstance();

    ClassInfo *class_info = ExecModule::prepare_class(runtime, class_name);

    if (class_info != nullptr)
    {
        auto field_it = class_info->staticIndexByName.find(frame.class_info->class_file->get_string_constant_pool(field_ref_index, 1));
        // TODO fazer as verificacoes de acesso e tipo
        if (field_it != class_info->staticIndexByName.end())
        {
            uint8_t *bytes = (uint8_t *)(class_info->staticBytes + field_it->second);
            if (field_size <= 4) // campo com 1, 2 ou 4 bytes
            {
                uint32_t word = frame.operand_stack.top();
                memcpy(bytes, &word + (sizeof(uint32_t) - field_size), field_size);
                frame.operand_stack.pop();
            }
            else // campo com 8 bytes
            {
                memcpy(bytes, &frame.operand_stack.top(), 4);
                frame.operand_stack.pop();
                memcpy(bytes + 4, &frame.operand_stack.top(), 4);
                frame.operand_stack.pop();
            }
        }
        else
        {
            printf("ERRO\n");
            // Field nao encontrado. TODO interromper a jvm e imprimir o erro.
            return;
        }
    }
    else
        frame.pc -= 3; // retorna pra essa instrucao apos rodar os metodos <clinit>
}

// TODO testar
void getfield(Frame &frame)
{
    uint16_t field_ref_index = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    uint32_t reference = get_int(frame);

    // TODO precisa dar throw NullPointerException
    if(reference == 0)
    {
        printf("ACESSANDO NULO???\n");
        return;
    }

    std::string class_name = frame.class_info->class_file->get_string_constant_pool(field_ref_index);
    uint8_t field_size = FieldInfo::field_size_bytes(frame.class_info->class_file->get_string_constant_pool(field_ref_index, 2));

    // TODO adicionar verificacoes pra classes nativas, tem que ignorar elas?

    Runtime &runtime = Runtime::getInstance();

    // TODO o nome da classe eh REALMENTE o nome que deve ser acessado? Parece ter casos que NAO.
    ClassInfo *class_info = ExecModule::prepare_class(runtime, class_name);

    if (class_info != nullptr)
    {
        auto field_it = class_info->fieldIndexByName.find(frame.class_info->class_file->get_string_constant_pool(field_ref_index, 1));
        if (field_it != class_info->fieldIndexByName.end())
        {
            // TODO implementar checagem de acesso e tipo, tem outros lugares onde precisa ser implementado tambem.
            uint8_t *bytes = (uint8_t *)(runtime.instances[reference] + field_it->second);
            if (field_size <= 4) // campo com 1, 2 ou 4 bytes
            {
                uint32_t word;
                memcpy(&word + (sizeof(uint32_t) - field_size), bytes, field_size);
                frame.operand_stack.push(word);
            }
            else // campo com 8 bytes
            {
                frame.operand_stack.push(*(uint32_t *)(bytes + 4));
                frame.operand_stack.push(*(uint32_t *)bytes);
            }
        }
        else
        {
            printf("ERRO\n");
            // Field nao encontrado. TODO interromper a jvm e imprimir o erro.
            return;
        }
    }
    else
        frame.pc -= 3; // retorna pra essa instrucao apos rodar os metodos <clinit>
}

// TODO testar
void putfield(Frame &frame)
{
    uint16_t field_ref_index = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    uint32_t reference = get_int(frame);

    // TODO precisa dar throw NullPointerException
    if(reference == 0)
    {
        printf("ACESSANDO NULO???\n");
        return;
    }

    std::string class_name = frame.class_info->class_file->get_string_constant_pool(field_ref_index);
    uint8_t field_size = FieldInfo::field_size_bytes(frame.class_info->class_file->get_string_constant_pool(field_ref_index, 2));

    // TODO adicionar verificacoes pra classes nativas, tem que ignorar elas?

    Runtime &runtime = Runtime::getInstance();

    // TODO o nome da classe eh REALMENTE o nome que deve ser acessado? Parece ter casos que NAO.
    ClassInfo *class_info = ExecModule::prepare_class(runtime, class_name);

    if (class_info != nullptr)
    {
        auto field_it = class_info->fieldIndexByName.find(frame.class_info->class_file->get_string_constant_pool(field_ref_index, 1));
        if (field_it != class_info->fieldIndexByName.end())
        {
            // TODO implementar checagem de acesso e tipo, tem outros lugares onde precisa ser implementado tambem.
            uint8_t *bytes = (uint8_t *)(runtime.instances[reference] + field_it->second);
            if (field_size <= 4) // campo com 1, 2 ou 4 bytes
            {
                uint32_t word = frame.operand_stack.top();
                memcpy(bytes, &word + (sizeof(uint32_t) - field_size), field_size);
                frame.operand_stack.pop();
            }
            else // campo com 8 bytes
            {
                memcpy(bytes, &frame.operand_stack.top(), 4);
                frame.operand_stack.pop();
                memcpy(bytes + 4, &frame.operand_stack.top(), 4);
                frame.operand_stack.pop();
            }
        }
        else
        {
            printf("ERRO\n");
            // Field nao encontrado. TODO interromper a jvm e imprimir o erro.
            return;
        }
    }
    else
        frame.pc -= 3; // retorna pra essa instrucao apos rodar os metodos <clinit>
}

// ToDo corrigir char
// TODO implementar regras de acesso
// TODO implementar busca em superclasses e interfaces(fudeu)
// TODO implementar threading? (precisa?)
// TODO "Dispatch based on class" significa que temos que salvar a classe exata instanciada pra saber qual usar aqui.
// TODO testar
void invokevirtual(Frame &frame)
{
    uint16_t x = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];

    std::string class_name = frame.class_info->class_file->get_string_constant_pool(x);
    std::string method_name = frame.class_info->class_file->get_string_constant_pool(x, 1);
    std::string method_desc = frame.class_info->class_file->get_string_constant_pool(x, 2);

    Runtime &runtime = Runtime::getInstance();

    // Simulação do println
    if (class_name.compare("java/io/PrintStream") == 0)
    {
        if (method_name.compare("println") == 0 || method_name.compare("print") == 0)
        {
            char endln = method_name.compare("println") == 0 ? '\n' : '\0';
            if (method_desc.compare("(C)V") == 0)
            {
                printf("%c%c", frame.operand_stack.top(), endln);
                frame.operand_stack.pop();
                frame.operand_stack.pop();
            }
            else if (method_desc.compare("(I)V") == 0)
            {
                printf("%d%c", frame.operand_stack.top(), endln);
                frame.operand_stack.pop();
                frame.operand_stack.pop();
            }
            else if (method_desc.compare("(J)V") == 0)
            {
                uint32_t a = frame.operand_stack.top();
                frame.operand_stack.pop();
                uint64_t b = frame.operand_stack.top();
                frame.operand_stack.pop();
                printf("%lld%c", (b << 32) + (long long)a, endln);
                frame.operand_stack.pop();
            }
            else if (method_desc.compare("(F)V") == 0)
            {
                uint32_t a = frame.operand_stack.top();
                frame.operand_stack.pop();
                float f;
                memcpy(&f, &a, sizeof(float));
                printf("%f%c", f, endln);
                frame.operand_stack.pop();
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
                printf("%lf%c", d, endln);
                frame.operand_stack.pop();
            }
            else if (method_desc.compare("()V") == 0)
            {
                printf("\n");
            }
            else if (method_desc.compare("(Ljava/lang/String;)V") == 0)
            {
                printf("%s%c", (char *)runtime.instances[get_int(frame)], endln);
            }
            else
                printf("invokevirtual FUNCAO DESCONHECIDA: %s.%s <%s>\n", class_name.c_str(), method_name.c_str(), method_desc.c_str());
            return;
        }
    }
    else if (class_name.compare("java/util/Scanner") == 0) { return; }
    else if (class_name.compare("java/lang/StringBuilder") == 0)
    {
/*  Nao vou implementar sem saber se precisa
        printf("invokevirtual FUNCAO DESCONHECIDA: %s.%s <%s>\n", class_name.c_str(), method_name.c_str(), method_desc.c_str());
        if(method_name.compare("append") == 0)
        {
            if(method_desc.compare("(Ljava/lang/String;)Ljava/lang/StringBuilder;") == 0)
            {

                
            }
            else if(method_desc.compare("(I)Ljava/lang/StringBuilder;") == 0)
            {

            }
            else if(method_desc.compare("(J)Ljava/lang/StringBuilder;") == 0)
            {

            }
            else if(method_desc.compare("(F)Ljava/lang/StringBuilder;") == 0)
            {

            }
            else if(method_desc.compare("()Ljava/lang/StringBuilder;") == 0)
            {

            }
        }
        else if(method_name.compare("toString") == 0)
        {

        } */
        return;
    }

    printf("%s\n", class_name.c_str());
    ClassInfo *class_info = ExecModule::prepare_class(runtime, class_name);
    if (class_info != nullptr)
    {
        for (MethodInfo &method : class_info->class_file->methods)
        {
            bool class_name_equal = class_info->class_file->get_string_constant_pool(method.name_index).compare(method_name) == 0;
            bool class_desc_equal = class_info->class_file->get_string_constant_pool(method.descriptor_index).compare(method_desc) == 0;
            
            if (class_name_equal && class_desc_equal)
            {
                std::vector<uint32_t> args;
                int index = 0;
                for (int i = 1; method_desc[i] != ')'; i++, index++)
                {
                    if (method_desc[i] == 'L')
                    {
                        args.push_back(get_int(frame));
                        while (method_desc[++i] != ';')
                            ;
                    }
                    else if (method_desc[i] == '[')
                    {
                        args.push_back(get_int(frame));
                        while (method_desc[++i] == '[')
                            ;
                        if (method_desc[i] == 'L')
                            while (method_desc[++i] != ';')
                                ;
                        else
                            i++;
                    }
                    else if (method_desc[i] == 'D' || method_desc[i] == 'J')
                    {
                        args.push_back(get_int(frame));
                        args.push_back(get_int(frame));
                    }
                    else
                        args.push_back(get_int(frame));
                }

                args.push_back(get_int(frame)); // Adiciona objectref nos argumentos.

                runtime.stack_frames.push(Frame(class_info, method));

                for (; index >= 0; index--)
                    runtime.stack_frames.top().local_variables[args.size() - index - 1] = args[index];
            }
        }
    }
    else
        frame.pc -= 3;
}

// ToDo corrigir char
// TODO implementar regras de acesso
// TODO implementar busca em superclasses e interfaces(fudeu)
// TODO implementar threading? (precisa?)
// TODO testar
void invokespecial(Frame &frame)
{
    uint16_t index = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];

    std::string class_name = frame.class_info->class_file->get_string_constant_pool(index);
    std::string method_name = frame.class_info->class_file->get_string_constant_pool(index, 1);
    std::string method_desc = frame.class_info->class_file->get_string_constant_pool(index, 2);

    Runtime &runtime = Runtime::getInstance();
}

void invokestatic(Frame &frame)
{
    uint16_t index = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];

    std::string class_name = frame.class_info->class_file->get_string_constant_pool(index);
    std::string method_name = frame.class_info->class_file->get_string_constant_pool(index, 1);
    std::string method_desc = frame.class_info->class_file->get_string_constant_pool(index, 2);

    Runtime &runtime = Runtime::getInstance();

    ClassInfo *class_info = ExecModule::prepare_class(runtime, class_name);
    if(class_info != nullptr)
    {
        for (MethodInfo &method : class_info->class_file->methods)
        {
            bool class_name_equal = class_info->class_file->get_string_constant_pool(method.name_index).compare(method_name) == 0;
            bool class_desc_equal = class_info->class_file->get_string_constant_pool(method.descriptor_index).compare(method_desc) == 0;
            
            if (class_name_equal && class_desc_equal)
            {
                std::vector<uint32_t> args;
                int index = 0;
                for (int i = 1; method_desc[i] != ')'; i++, index++)
                {
                    if (method_desc[i] == 'L')
                    {
                        args.push_back(get_int(frame));
                        while (method_desc[++i] != ';')
                            ;
                    }
                    else if (method_desc[i] == '[')
                    {
                        args.push_back(get_int(frame));
                        while (method_desc[++i] == '[')
                            ;
                        if (method_desc[i] == 'L')
                            while (method_desc[++i] != ';')
                                ;
                        else
                            i++;
                    }
                    else if (method_desc[i] == 'D' || method_desc[i] == 'J')
                    {
                        args.push_back(get_int(frame));
                        args.push_back(get_int(frame));
                    }
                    else
                        args.push_back(get_int(frame));
                }

                runtime.stack_frames.push(Frame(class_info, method));

                for (; index >= 0; index--)
                    runtime.stack_frames.top().local_variables[args.size() - index - 1] = args[index];
            }
        }
    }
}

void invokeinterface(Frame &frame) {}
void invokedynamic(Frame &frame) {}

void c_new(Frame &frame)
{
    uint16_t index = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];

    std::string class_name = frame.class_info->class_file->get_string_constant_pool(index);

    Runtime &runtime = Runtime::getInstance();

    if (class_name.compare("java/lang/StringBuilder") == 0)
    {
        std::string *s = new std::string();
        runtime.instances.push_back((uint8_t *)s);
        frame.operand_stack.push(runtime.instances.size() - 1);
        return;
    }
    else if(class_name.compare("java/util/Scanner") == 0)
    {
        frame.operand_stack.push(0); // Objetos de classes do proprio java devem ser ignorados?
        return;
    }

    ClassInfo *class_info = ExecModule::prepare_class(runtime, class_name);
    if (class_info != nullptr)
    {
        frame.operand_stack.push(runtime.instances.size());
        if (class_info->fieldBytesAmmount > 0)
            runtime.instances.push_back(new uint8_t[class_info->fieldBytesAmmount]{0});
        else
            runtime.instances.push_back(nullptr); // TODO Isso ta certo? Eh melhor nao adicionar nada?
                                                  //Se n adicionar nada aqui tem que botar outra coisa no operand_stack, por exemplo 0, ou vai dar erro depois.
    }
    else
        frame.pc -= 3;
}

void newarray(Frame &frame)
{
    Runtime &runtime = Runtime::getInstance();
    uint8_t type = frame.code->code[++frame.pc];
    uint32_t count = get_int(frame);
    uint8_t size;
    switch (type)
    {
    case 4: // Boolean
    case 5: // Char
    case 8: // Byte
        size = 1;
        break;
    case 9: // Short
        size = 2;
        break;
    case 6:  // Float
    case 10: // Int
        size = 4;
        break;
    case 7:  // Double
    case 11: // Long
        size = 8;
        break;
    }

    array_t *ar = new array_t;
    ar->size = size;
    ar->lenght = count;
    ar->bytes = new uint8_t[count * size]{0};

    frame.operand_stack.push(runtime.instances.size());
    runtime.instances.push_back((uint8_t *)ar);
}

void anewarray(Frame &frame)
{
    Runtime &runtime = Runtime::getInstance();
    uint16_t index = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];

    ExecModule::prepare_class(runtime, frame.class_info->class_file->get_string_constant_pool(index));

    uint32_t count = get_int(frame);
    array_t *ar = new array_t;
    ar->size = 4;
    ar->lenght = count;
    ar->bytes = new uint8_t[count * ar->size]{0};

    frame.operand_stack.push(runtime.instances.size());
    runtime.instances.push_back((uint8_t *)ar);
}

void arraylength(Frame &frame)
{
    Runtime &runtime = Runtime::getInstance();
    uint32_t reference = get_int(frame);

    frame.operand_stack.push(((array_t *)runtime.instances[reference])->lenght);
}

void athrow(Frame &frame) {}
void checkcast(Frame &frame) {}
void instanceof (Frame & frame) {}
void monitorenter(Frame &frame) {}
void monitorexit(Frame &frame) {}

void wide(Frame &frame)
{
    uint8_t opcode = frame.code->code[++frame.pc];
    if (opcode == 0x84) // IINC
    {
        uint16_t index = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
        int32_t add = (int32_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
        frame.local_variables[index] = (int32_t)(frame.local_variables[index]) + add;
    }
    else if (opcode == 0x16 || opcode == 0x18) // LLOAD DLOAD
    {
        uint16_t index = (uint16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
        frame.operand_stack.push(frame.local_variables[index]);
        frame.operand_stack.push(frame.local_variables[index + 1]);
    }
    else if (opcode == 0x15 || opcode == 0x17 || opcode == 0x19) // ILOAD FLOAD ALOAD
    {
        uint16_t index = (uint16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
        frame.operand_stack.push(frame.local_variables[index]);
    }
    else if (opcode == 0x37 || opcode == 0x39) // LSTORE DSTORE
    {
        uint16_t index = (uint16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
        frame.local_variables[index + 1] = frame.operand_stack.top();
        frame.operand_stack.pop();
        frame.local_variables[index] = frame.operand_stack.top();
        frame.operand_stack.pop();
    }
    else if (opcode == 0xa9) // RET
    {
        uint16_t index = (uint16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
        frame.pc = frame.local_variables[index] - 1;
    }
    else // if(opcode == 0x36 || opcode == 0x38 || opcode == 0x3a) // ISTORE FSTORE ASTORE
    {
        uint16_t index = (uint16_t)((frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc]);
        frame.local_variables[index] = frame.operand_stack.top();
        frame.operand_stack.pop();
    }
}

void multianewarray(Frame &frame)
{
    Runtime &runtime = Runtime::getInstance();
    uint32_t index = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    uint8_t dimensions = frame.code->code[++frame.pc];
    std::string reference = frame.class_info->class_file->get_string_constant_pool(index);

    reference.erase(std::remove(reference.begin(), reference.end(), '['), reference.end());
    uint8_t size;
    if (reference.compare("Z") == 0 || reference.compare("C") == 0 || reference.compare("B") == 0)
    {
        size = 1;
    }
    else if (reference.compare("S") == 0)
    {
        size = 2;
    }
    else if (reference.compare("F") == 0 || reference.compare("I") == 0)
    {
        size = 4;
    }
    else if (reference.compare("D") == 0 || reference.compare("J") == 0)
    {
        size = 8;
    }
    else
    {
        size = 4;
    }

    int size_dim[dimensions];
    for (int i = 0; i < dimensions; i++)
    {
        size_dim[i] = get_int(frame);
    }

    frame.operand_stack.push(gera_multiarray(size_dim, runtime, size, --dimensions));
}

void ifnull(Frame &frame)
{
    uint32_t value = get_int(frame);
    int32_t offset = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    if (value == 0) // Indice considerado como NULL
        frame.pc += offset - 3;
}

void ifnonnull(Frame &frame)
{
    uint32_t value = get_int(frame);
    int32_t offset = (frame.code->code[++frame.pc] << 8) | frame.code->code[++frame.pc];
    if (value != 0) // Indice considerado como NULL
        frame.pc += offset - 3;
}

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