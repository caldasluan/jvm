#ifndef JVM_INSTRUCTIONS_H
#define JVM_INSTRUCTIONS_H

#define OP_NO 0                // no bytes
#define OP_1_LV 1              // 1 byte local variable
#define OP_LDC 2               // 1 byte that references something in the constant pool
#define OP_BIPUSH 3            // 1 byte to be sign extended and pushed
#define OP_2_CP 4              // 2 bytes that references something in the constant pool
#define OP_2_CPWIDE 5          // 2 bytes references a two word constant
#define OP_SIPUSH 6            // 2 bytes to be sign extended and pushed
#define OP_2_BRANCH 7          // 2 bytes of offset to be added to PC
#define OP_4_BRANCH 8          // 4 bytes of offset to be added to PC
#define OP_IINC 9              // 1 byte local variable, 1 byte to be sign extended added to local variable
#define OP_INVOKE_DYNAMIC 10   // 2 bytes references constant pool, 2 bytes = 0
#define OP_INVOKE_INTERFACE 11 // 2 bytes references constant pool, 1 byte ammount of arguments, 1 byte = 0 (why tho?)
#define OP_LOOKUPSWITCH 12     // 0-3 padding, 4 bytes default, 4 bytes npairs, (8*npairs) bytes pairs
#define OP_MULTIANEWARRAY 13   // 2 bytes constant index, 1 byte dimension of multiaarray
#define OP_NEWARRAY 14         // 1 byte array type
#define OP_TABLESWITCH 15      // 0-3 padding, 4 bytes default, 4 bytes low, 4 bytes high, (4 *(high - low + 1)) bytes branch offsets
#define OP_WIDE 16             // 1 byte of opcode to be widened, 2 bytes

#include <array>
#include <cstdint>
#include <string>
#include "../model/Frame.h"

int get_int(Frame &frame);
long long get_long(Frame &frame);
float get_float(Frame &frame);
double get_double(Frame &frame);
MethodInfo *getMethod(ClassFile *class_file, std::string method_name, std::string method_desc);

void nop(Frame &);
void aconst_null(Frame &);
void iconst_m1(Frame &);
void iconst_0(Frame &);
void iconst_1(Frame &);
void iconst_2(Frame &);
void iconst_3(Frame &);
void iconst_4(Frame &);
void iconst_5(Frame &);
void lconst_0(Frame &);
void lconst_1(Frame &);
void fconst_0(Frame &);
void fconst_1(Frame &);
void fconst_2(Frame &);
void dconst_0(Frame &);
void dconst_1(Frame &);
void bipush(Frame &);
void sipush(Frame &);
void ldc(Frame &);
void ldc_w(Frame &);
void ldc2_w(Frame &);
void iload(Frame &);
void lload(Frame &);
void fload(Frame &);
void dload(Frame &);
void aload(Frame &);
void iload_0(Frame &);
void iload_1(Frame &);
void iload_2(Frame &);
void iload_3(Frame &);
void lload_0(Frame &);
void lload_1(Frame &);
void lload_2(Frame &);
void lload_3(Frame &);
void fload_0(Frame &);
void fload_1(Frame &);
void fload_2(Frame &);
void fload_3(Frame &);
void dload_0(Frame &);
void dload_1(Frame &);
void dload_2(Frame &);
void dload_3(Frame &);
void aload_0(Frame &);
void aload_1(Frame &);
void aload_2(Frame &);
void aload_3(Frame &);
void iaload(Frame &);
void laload(Frame &);
void faload(Frame &);
void daload(Frame &);
void aaload(Frame &);
void baload(Frame &);
void caload(Frame &);
void saload(Frame &);
void istore(Frame &);
void lstore(Frame &);
void fstore(Frame &);
void dstore(Frame &);
void astore(Frame &);
void istore_0(Frame &);
void istore_1(Frame &);
void istore_2(Frame &);
void istore_3(Frame &);
void lstore_0(Frame &);
void lstore_1(Frame &);
void lstore_2(Frame &);
void lstore_3(Frame &);
void fstore_0(Frame &);
void fstore_1(Frame &);
void fstore_2(Frame &);
void fstore_3(Frame &);
void dstore_0(Frame &);
void dstore_1(Frame &);
void dstore_2(Frame &);
void dstore_3(Frame &);
void astore_0(Frame &);
void astore_1(Frame &);
void astore_2(Frame &);
void astore_3(Frame &);
void iastore(Frame &);
void lastore(Frame &);
void fastore(Frame &);
void dastore(Frame &);
void aastore(Frame &);
void bastore(Frame &);
void castore(Frame &);
void sastore(Frame &);
void pop(Frame &);
void pop2(Frame &);
void dup(Frame &);
void dup_x1(Frame &);
void dup_x2(Frame &);
void dup2(Frame &);
void dup2_x1(Frame &);
void dup2_x2(Frame &);
void swap(Frame &);
void iadd(Frame &);
void ladd(Frame &);
void fadd(Frame &);
void dadd(Frame &);
void isub(Frame &);
void lsub(Frame &);
void fsub(Frame &);
void dsub(Frame &);
void imul(Frame &);
void lmul(Frame &);
void fmul(Frame &);
void dmul(Frame &);
void idiv(Frame &);
void ldiv(Frame &);
void fdiv(Frame &);
void ddiv(Frame &);
void irem(Frame &);
void lrem(Frame &);
void frem(Frame &);
void drem(Frame &);
void ineg(Frame &);
void lneg(Frame &);
void fneg(Frame &);
void dneg(Frame &);
void ishl(Frame &);
void lshl(Frame &);
void ishr(Frame &);
void lshr(Frame &);
void iushr(Frame &);
void lushr(Frame &);
void iand(Frame &);
void land(Frame &);
void ior(Frame &);
void lor(Frame &);
void ixor(Frame &);
void lxor(Frame &);
void iinc(Frame &);
void i2l(Frame &);
void i2f(Frame &);
void i2d(Frame &);
void l2i(Frame &);
void l2f(Frame &);
void l2d(Frame &);
void f2i(Frame &);
void f2l(Frame &);
void f2d(Frame &);
void d2i(Frame &);
void d2l(Frame &);
void d2f(Frame &);
void i2b(Frame &);
void i2c(Frame &);
void i2s(Frame &);
void lcmp(Frame &);
void fcmpl(Frame &);
void fcmpg(Frame &);
void dcmpl(Frame &);
void dcmpg(Frame &);
void ifeq(Frame &);
void ifne(Frame &);
void iflt(Frame &);
void ifge(Frame &);
void ifgt(Frame &);
void ifle(Frame &);
void if_icmpeq(Frame &);
void if_icmpne(Frame &);
void if_icmplt(Frame &);
void if_icmpge(Frame &);
void if_icmpgt(Frame &);
void if_icmple(Frame &);
void if_acmpeq(Frame &);
void if_acmpne(Frame &);
void c_goto(Frame &);
void jsr(Frame &);
void ret(Frame &);
void tableswitch(Frame &);
void lookupswitch(Frame &);
void ireturn(Frame &);
void lreturn(Frame &);
void freturn(Frame &);
void dreturn(Frame &);
void areturn(Frame &);
void c_return(Frame &);
void getstatic(Frame &);
void putstatic(Frame &);
void getfield(Frame &);
void putfield(Frame &);
void invokevirtual(Frame &);
void invokespecial(Frame &);
void invokestatic(Frame &);
void invokeinterface(Frame &);
void invokedynamic(Frame &);
void c_new(Frame &);
void newarray(Frame &);
void anewarray(Frame &);
void arraylength(Frame &);
void athrow(Frame &);
void checkcast(Frame &);
void instanceof (Frame &);
void monitorenter(Frame &);
void monitorexit(Frame &);
void wide(Frame &);
void multianewarray(Frame &);
void ifnull(Frame &);
void ifnonnull(Frame &);
void goto_w(Frame &);
void jsr_w(Frame &);

class Instruction
{
public:
  Instruction(const char *_mnemonic, const uint8_t _operands, void (*_execution)(Frame &)) : mnemonic(_mnemonic), operands(_operands), execution(_execution){};

  const char *mnemonic;
  const uint8_t operands;
  void (*execution)(Frame &);
};

const std::array<Instruction, 202> instructions_mnemonics = {
    /* 0x00 */ Instruction("nop", OP_NO, &nop),
    /* 0x01 */ Instruction("aconst_null", OP_NO, &aconst_null),
    /* 0x02 */ Instruction("iconst_m1", OP_NO, &iconst_m1),
    /* 0x03 */ Instruction("iconst_0", OP_NO, &iconst_0),
    /* 0x04 */ Instruction("iconst_1", OP_NO, &iconst_1),
    /* 0x05 */ Instruction("iconst_2", OP_NO, &iconst_2),
    /* 0x06 */ Instruction("iconst_3", OP_NO, &iconst_3),
    /* 0x07 */ Instruction("iconst_4", OP_NO, &iconst_4),
    /* 0x08 */ Instruction("iconst_5", OP_NO, &iconst_5),
    /* 0x09 */ Instruction("lconst_0", OP_NO, &lconst_0),
    /* 0x0a */ Instruction("lconst_1", OP_NO, &lconst_1),
    /* 0x0b */ Instruction("fconst_0", OP_NO, &fconst_0),
    /* 0x0c */ Instruction("fconst_1", OP_NO, &fconst_1),
    /* 0x0d */ Instruction("fconst_2", OP_NO, &fconst_2),
    /* 0x0e */ Instruction("dconst_0", OP_NO, &dconst_0),
    /* 0x0f */ Instruction("dconst_1", OP_NO, &dconst_1),
    /* 0x10 */ Instruction("bipush", OP_BIPUSH, &bipush),
    /* 0x11 */ Instruction("sipush", OP_SIPUSH, &sipush),
    /* 0x12 */ Instruction("ldc", OP_LDC, &ldc),
    /* 0x13 */ Instruction("ldc_w", OP_2_CP, &ldc_w),
    /* 0x14 */ Instruction("ldc2_w", OP_2_CPWIDE, &ldc2_w),
    /* 0x15 */ Instruction("iload", OP_1_LV, &iload),
    /* 0x16 */ Instruction("lload", OP_1_LV, &lload),
    /* 0x17 */ Instruction("fload", OP_1_LV, &fload),
    /* 0x18 */ Instruction("dload", OP_1_LV, &dload),
    /* 0x19 */ Instruction("aload", OP_1_LV, &aload),
    /* 0x1a */ Instruction("iload_0", OP_NO, &iload_0),
    /* 0x1b */ Instruction("iload_1", OP_NO, &iload_1),
    /* 0x1c */ Instruction("iload_2", OP_NO, &iload_2),
    /* 0x1d */ Instruction("iload_3", OP_NO, &iload_3),
    /* 0x1e */ Instruction("lload_0", OP_NO, &lload_0),
    /* 0x1f */ Instruction("lload_1", OP_NO, &lload_1),
    /* 0x20 */ Instruction("lload_2", OP_NO, &lload_2),
    /* 0x21 */ Instruction("lload_3", OP_NO, &lload_3),
    /* 0x22 */ Instruction("fload_0", OP_NO, &fload_0),
    /* 0x23 */ Instruction("fload_1", OP_NO, &fload_1),
    /* 0x24 */ Instruction("fload_2", OP_NO, &fload_2),
    /* 0x25 */ Instruction("fload_3", OP_NO, &fload_3),
    /* 0x26 */ Instruction("dload_0", OP_NO, &dload_0),
    /* 0x27 */ Instruction("dload_1", OP_NO, &dload_1),
    /* 0x28 */ Instruction("dload_2", OP_NO, &dload_2),
    /* 0x29 */ Instruction("dload_3", OP_NO, &dload_3),
    /* 0x2a */ Instruction("aload_0", OP_NO, &aload_0),
    /* 0x2b */ Instruction("aload_1", OP_NO, &aload_1),
    /* 0x2c */ Instruction("aload_2", OP_NO, &aload_2),
    /* 0x2d */ Instruction("aload_3", OP_NO, &aload_3),
    /* 0x2e */ Instruction("iaload", OP_NO, &iaload),
    /* 0x2f */ Instruction("laload", OP_NO, &laload),
    /* 0x30 */ Instruction("faload", OP_NO, &faload),
    /* 0x31 */ Instruction("daload", OP_NO, &daload),
    /* 0x32 */ Instruction("aaload", OP_NO, &aaload),
    /* 0x33 */ Instruction("baload", OP_NO, &baload),
    /* 0x34 */ Instruction("caload", OP_NO, &caload),
    /* 0x35 */ Instruction("saload", OP_NO, &saload),
    /* 0x36 */ Instruction("istore", OP_1_LV, &istore),
    /* 0x37 */ Instruction("lstore", OP_1_LV, &lstore),
    /* 0x38 */ Instruction("fstore", OP_1_LV, &fstore),
    /* 0x39 */ Instruction("dstore", OP_1_LV, &dstore),
    /* 0x3a */ Instruction("astore", OP_1_LV, &astore),
    /* 0x3b */ Instruction("istore_0", OP_NO, &istore_0),
    /* 0x3c */ Instruction("istore_1", OP_NO, &istore_1),
    /* 0x3d */ Instruction("istore_2", OP_NO, &istore_2),
    /* 0x3e */ Instruction("istore_3", OP_NO, &istore_3),
    /* 0x3f */ Instruction("lstore_0", OP_NO, &lstore_0),
    /* 0x40 */ Instruction("lstore_1", OP_NO, &lstore_1),
    /* 0x41 */ Instruction("lstore_2", OP_NO, &lstore_2),
    /* 0x42 */ Instruction("lstore_3", OP_NO, &lstore_3),
    /* 0x43 */ Instruction("fstore_0", OP_NO, &fstore_0),
    /* 0x44 */ Instruction("fstore_1", OP_NO, &fstore_1),
    /* 0x45 */ Instruction("fstore_2", OP_NO, &fstore_2),
    /* 0x46 */ Instruction("fstore_3", OP_NO, &fstore_3),
    /* 0x47 */ Instruction("dstore_0", OP_NO, &dstore_0),
    /* 0x48 */ Instruction("dstore_1", OP_NO, &dstore_1),
    /* 0x49 */ Instruction("dstore_2", OP_NO, &dstore_2),
    /* 0x4a */ Instruction("dstore_3", OP_NO, &dstore_3),
    /* 0x4b */ Instruction("astore_0", OP_NO, &astore_0),
    /* 0x4c */ Instruction("astore_1", OP_NO, &astore_1),
    /* 0x4d */ Instruction("astore_2", OP_NO, &astore_2),
    /* 0x4e */ Instruction("astore_3", OP_NO, &astore_3),
    /* 0x4f */ Instruction("iastore", OP_NO, &iastore),
    /* 0x50 */ Instruction("lastore", OP_NO, &lastore),
    /* 0x51 */ Instruction("fastore", OP_NO, &fastore),
    /* 0x52 */ Instruction("dastore", OP_NO, &dastore),
    /* 0x53 */ Instruction("aastore", OP_NO, &aastore),
    /* 0x54 */ Instruction("bastore", OP_NO, &bastore),
    /* 0x55 */ Instruction("castore", OP_NO, &castore),
    /* 0x56 */ Instruction("sastore", OP_NO, &sastore),
    /* 0x57 */ Instruction("pop", OP_NO, &pop),
    /* 0x58 */ Instruction("pop2", OP_NO, &pop2),
    /* 0x59 */ Instruction("dup", OP_NO, &dup),
    /* 0x5a */ Instruction("dup_x1", OP_NO, &dup_x1),
    /* 0x5b */ Instruction("dup_x2", OP_NO, &dup_x2),
    /* 0x5c */ Instruction("dup2", OP_NO, &dup2),
    /* 0x5d */ Instruction("dup2_x1", OP_NO, &dup2_x1),
    /* 0x5e */ Instruction("dup2_x2", OP_NO, &dup2_x2),
    /* 0x5f */ Instruction("swap", OP_NO, &swap),
    /* 0x60 */ Instruction("iadd", OP_NO, &iadd),
    /* 0x61 */ Instruction("ladd", OP_NO, &ladd),
    /* 0x62 */ Instruction("fadd", OP_NO, &fadd),
    /* 0x63 */ Instruction("dadd", OP_NO, &dadd),
    /* 0x64 */ Instruction("isub", OP_NO, &isub),
    /* 0x65 */ Instruction("lsub", OP_NO, &lsub),
    /* 0x66 */ Instruction("fsub", OP_NO, &fsub),
    /* 0x67 */ Instruction("dsub", OP_NO, &dsub),
    /* 0x68 */ Instruction("imul", OP_NO, &imul),
    /* 0x69 */ Instruction("lmul", OP_NO, &lmul),
    /* 0x6a */ Instruction("fmul", OP_NO, &fmul),
    /* 0x6b */ Instruction("dmul", OP_NO, &dmul),
    /* 0x6c */ Instruction("idiv", OP_NO, &idiv),
    /* 0x6d */ Instruction("ldiv", OP_NO, &ldiv),
    /* 0x6e */ Instruction("fdiv", OP_NO, &fdiv),
    /* 0x6f */ Instruction("ddiv", OP_NO, &ddiv),
    /* 0x70 */ Instruction("irem", OP_NO, &irem),
    /* 0x71 */ Instruction("lrem", OP_NO, &lrem),
    /* 0x72 */ Instruction("frem", OP_NO, &frem),
    /* 0x73 */ Instruction("drem", OP_NO, &drem),
    /* 0x74 */ Instruction("ineg", OP_NO, &ineg),
    /* 0x75 */ Instruction("lneg", OP_NO, &lneg),
    /* 0x76 */ Instruction("fneg", OP_NO, &fneg),
    /* 0x77 */ Instruction("dneg", OP_NO, &dneg),
    /* 0x78 */ Instruction("ishl", OP_NO, &ishl),
    /* 0x79 */ Instruction("lshl", OP_NO, &lshl),
    /* 0x7a */ Instruction("ishr", OP_NO, &ishr),
    /* 0x7b */ Instruction("lshr", OP_NO, &lshr),
    /* 0x7c */ Instruction("iushr", OP_NO, &iushr),
    /* 0x7d */ Instruction("lushr", OP_NO, &lushr),
    /* 0x7e */ Instruction("iand", OP_NO, &iand),
    /* 0x7f */ Instruction("land", OP_NO, &land),
    /* 0x80 */ Instruction("ior", OP_NO, &ior),
    /* 0x81 */ Instruction("lor", OP_NO, &lor),
    /* 0x82 */ Instruction("ixor", OP_NO, &ixor),
    /* 0x83 */ Instruction("lxor", OP_NO, &lxor),
    /* 0x84 */ Instruction("iinc", OP_IINC, &iinc),
    /* 0x85 */ Instruction("i2l", OP_NO, &i2l),
    /* 0x86 */ Instruction("i2f", OP_NO, &i2f),
    /* 0x87 */ Instruction("i2d", OP_NO, &i2d),
    /* 0x88 */ Instruction("l2i", OP_NO, &l2i),
    /* 0x89 */ Instruction("l2f", OP_NO, &l2f),
    /* 0x8a */ Instruction("l2d", OP_NO, &l2d),
    /* 0x8b */ Instruction("f2i", OP_NO, &f2i),
    /* 0x8c */ Instruction("f2l", OP_NO, &f2l),
    /* 0x8d */ Instruction("f2d", OP_NO, &f2d),
    /* 0x8e */ Instruction("d2i", OP_NO, &d2i),
    /* 0x8f */ Instruction("d2l", OP_NO, &d2l),
    /* 0x90 */ Instruction("d2f", OP_NO, &d2f),
    /* 0x91 */ Instruction("i2b", OP_NO, &i2b),
    /* 0x92 */ Instruction("i2c", OP_NO, &i2c),
    /* 0x93 */ Instruction("i2s", OP_NO, &i2s),
    /* 0x94 */ Instruction("lcmp", OP_NO, &lcmp),
    /* 0x95 */ Instruction("fcmpl", OP_NO, &fcmpl),
    /* 0x96 */ Instruction("fcmpg", OP_NO, &fcmpg),
    /* 0x97 */ Instruction("dcmpl", OP_NO, &dcmpl),
    /* 0x98 */ Instruction("dcmpg", OP_NO, &dcmpg),
    /* 0x99 */ Instruction("ifeq", OP_2_BRANCH, &ifeq),
    /* 0x9a */ Instruction("ifne", OP_2_BRANCH, &ifne),
    /* 0x9b */ Instruction("iflt", OP_2_BRANCH, &iflt),
    /* 0x9c */ Instruction("ifge", OP_2_BRANCH, &ifge),
    /* 0x9d */ Instruction("ifgt", OP_2_BRANCH, &ifgt),
    /* 0x9e */ Instruction("ifle", OP_2_BRANCH, &ifle),
    /* 0x9f */ Instruction("if_icmpeq", OP_2_BRANCH, &if_icmpeq),
    /* 0xa0 */ Instruction("if_icmpne", OP_2_BRANCH, &if_icmpne),
    /* 0xa1 */ Instruction("if_icmplt", OP_2_BRANCH, &if_icmplt),
    /* 0xa2 */ Instruction("if_icmpge", OP_2_BRANCH, &if_icmpge),
    /* 0xa3 */ Instruction("if_icmpgt", OP_2_BRANCH, &if_icmpgt),
    /* 0xa4 */ Instruction("if_icmple", OP_2_BRANCH, &if_icmple),
    /* 0xa5 */ Instruction("if_acmpeq", OP_2_BRANCH, &if_acmpeq),
    /* 0xa6 */ Instruction("if_acmpne", OP_2_BRANCH, &if_acmpne),
    /* 0xa7 */ Instruction("goto", OP_2_BRANCH, &c_goto),
    /* 0xa8 */ Instruction("jsr", OP_2_BRANCH, &jsr),
    /* 0xa9 */ Instruction("ret", OP_1_LV, &ret),
    /* 0xaa */ Instruction("tableswitch", OP_TABLESWITCH, &tableswitch),
    /* 0xab */ Instruction("lookupswitch", OP_LOOKUPSWITCH, &lookupswitch),
    /* 0xac */ Instruction("ireturn", OP_NO, &ireturn),
    /* 0xad */ Instruction("lreturn", OP_NO, &lreturn),
    /* 0xae */ Instruction("freturn", OP_NO, &freturn),
    /* 0xaf */ Instruction("dreturn", OP_NO, &dreturn),
    /* 0xb0 */ Instruction("areturn", OP_NO, &areturn),
    /* 0xb1 */ Instruction("return", OP_NO, &c_return),
    /* 0xb2 */ Instruction("getstatic", OP_2_CP, &getstatic),
    /* 0xb3 */ Instruction("putstatic", OP_2_CP, &putstatic),
    /* 0xb4 */ Instruction("getfield", OP_2_CP, &getfield),
    /* 0xb5 */ Instruction("putfield", OP_2_CP, &putfield),
    /* 0xb6 */ Instruction("invokevirtual", OP_2_CP, &invokevirtual),
    /* 0xb7 */ Instruction("invokespecial", OP_2_CP, &invokespecial),
    /* 0xb8 */ Instruction("invokestatic", OP_2_CP, &invokestatic),
    /* 0xb9 */ Instruction("invokeinterface", OP_INVOKE_INTERFACE, &invokeinterface),
    /* 0xba */ Instruction("invokedynamic", OP_INVOKE_DYNAMIC, &invokedynamic),
    /* 0xbb */ Instruction("new", OP_2_CP, &c_new),
    /* 0xbc */ Instruction("newarray", OP_NEWARRAY, &newarray),
    /* 0xbd */ Instruction("anewarray", OP_2_CP, &anewarray),
    /* 0xbe */ Instruction("arraylength", OP_NO, &arraylength),
    /* 0xbf */ Instruction("athrow", OP_NO, &athrow),
    /* 0xc0 */ Instruction("checkcast", OP_2_CP, &checkcast),
    /* 0xc1 */ Instruction("instanceof", OP_2_CP, & instanceof),
    /* 0xc2 */ Instruction("monitorenter", OP_NO, &monitorenter),
    /* 0xc3 */ Instruction("monitorexit", OP_NO, &monitorexit),
    /* 0xc4 */ Instruction("wide", OP_WIDE, &wide),
    /* 0xc5 */ Instruction("multianewarray", OP_MULTIANEWARRAY, &multianewarray),
    /* 0xc6 */ Instruction("ifnull", OP_2_BRANCH, &ifnull),
    /* 0xc7 */ Instruction("ifnonnull", OP_2_BRANCH, &ifnonnull),
    /* 0xc8 */ Instruction("goto_w", OP_4_BRANCH, &goto_w),
    /* 0xc9 */ Instruction("jsr_w", OP_4_BRANCH, &jsr_w)};

const char *const array_types[] = {
    "",
    "",
    "",
    "",
    "T_BOOLEAN",
    "T_CHAR",
    "T_FLOAT",
    "T_DOUBLE",
    "T_BYTE",
    "T_SHORT",
    "T_INT",
    "T_LONG"};

const uint64_t mask_shift[] = {
    0x0000000000000000,
    0x8000000000000000,
    0xC000000000000000,
    0xE000000000000000,
    0xF000000000000000,
    0xF800000000000000,
    0xFC00000000000000,
    0xFE00000000000000,
    0xFF00000000000000,
    0xFF80000000000000,
    0xFFC0000000000000,
    0xFFE0000000000000,
    0xFFF0000000000000,
    0xFFF8000000000000,
    0xFFFC000000000000,
    0xFFFE000000000000,
    0xFFFF000000000000,
    0xFFFF800000000000,
    0xFFFFC00000000000,
    0xFFFFE00000000000,
    0xFFFFF00000000000,
    0xFFFFF80000000000,
    0xFFFFFC0000000000,
    0xFFFFFE0000000000,
    0xFFFFFF0000000000,
    0xFFFFFF8000000000,
    0xFFFFFFC000000000,
    0xFFFFFFE000000000,
    0xFFFFFFF000000000,
    0xFFFFFFF800000000,
    0xFFFFFFFC00000000,
    0xFFFFFFFE00000000,
    0xFFFFFFFF00000000,
    0xFFFFFFFF80000000,
    0xFFFFFFFFC0000000,
    0xFFFFFFFFE0000000,
    0xFFFFFFFFF0000000,
    0xFFFFFFFFF8000000,
    0xFFFFFFFFFC000000,
    0xFFFFFFFFFE000000,
    0xFFFFFFFFFF000000,
    0xFFFFFFFFFF800000,
    0xFFFFFFFFFFC00000,
    0xFFFFFFFFFFE00000,
    0xFFFFFFFFFFF00000,
    0xFFFFFFFFFFF80000,
    0xFFFFFFFFFFFC0000,
    0xFFFFFFFFFFFE0000,
    0xFFFFFFFFFFFF0000,
    0xFFFFFFFFFFFF8000,
    0xFFFFFFFFFFFFC000,
    0xFFFFFFFFFFFFE000,
    0xFFFFFFFFFFFFF000,
    0xFFFFFFFFFFFFF800,
    0xFFFFFFFFFFFFFC00,
    0xFFFFFFFFFFFFFE00,
    0xFFFFFFFFFFFFFF00,
    0xFFFFFFFFFFFFFF80,
    0xFFFFFFFFFFFFFFC0,
    0xFFFFFFFFFFFFFFE0,
    0xFFFFFFFFFFFFFFF0,
    0xFFFFFFFFFFFFFFF8,
    0xFFFFFFFFFFFFFFFC,
    0xFFFFFFFFFFFFFFFE,
    0xFFFFFFFFFFFFFFFF,
};

#endif // JVM_INSTRUCTIONS_H