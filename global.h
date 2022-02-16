

/* represent the symbols table */
typedef struct symbol{
    char *name;
    int value;/* the line of the definition*/
    int baseAddress;
    int offset;
    int attributes;
    struct symbol * next;
}symbol ;

/* represent a memory word (code)*/
typedef struct memory_word1{
    unsigned int destination_address :2;
    unsigned int destination_register :4;
    unsigned int source_address :2;
    unsigned int source_register :4;
    unsigned int funct :4;
}memory_word1;

/* represent a memory word(opcode)*/
typedef struct memory_word2{
    unsigned int opcode : 16;
}memory_word2;

/* represent a machine code */
typedef struct machine_code{
    union memory_word
    {
        memory_word1 *code;
        memory_word2 *data;
    }word;
    int A;
    int R;
    int E;
    int missing_lable;
}machine_code;

machine_code memory[8092];/* the memory image*/

typedef struct function{
    char *name;
    int funct;
    int opcode;
    int operands;
}function;

enum regN{
    R0 = 0, R1,R2,R3,R4,R5,R6,R7
    ,R8,R9,R10,R11,R12,R13,R14,R15,R16 }register_number;

char **reg = {"r0","r1","r2","r3","r4","r5","r6","r7","r8","r9",
                "r10","r11","r12","r13","r14","r15","r16"}; /* register names*/
