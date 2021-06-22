#include <stdio.h>
#include <string.h>

#define LIMIT 40

int getMask(int start, int end, int type){
    if (end > 31 || end < 0 || start > end || (type != 0 && type != 1) || start > 31 || start < 0){
        return 0;
    }
    unsigned int mask = ~(~0 << (end - start + 1)) << (start);
    if (start == 0 && end == 31){
        mask = -1;
    }
    if (type == 0){
        return ~mask;
    }
    return mask;
}

int getSubInt(int start, int stop, int num){
    if ((stop > 31 || stop < 0) || (start > 31 || start < 0) || (start > stop)){
        return 0;
    }
    unsigned int ret = ((getMask(start, stop, 1) & num));
    return ret >> start;
}

void printAssembly(char filename[]);


//**************************************************
//Make sure to comment main out before submitting
//**************************************************

void printAdd(int num);
void printAnd(int num);
void printBr(int num, int pc);
void printJmpRet(int num);
void printJsrJsrr(int num, int pc);
void printLd(int num, int pc);
void printLdi(int num, int pc);
void printLdr(int num);
void printLea(int num, int pc);
void printNot(int num);
void printRti(int num);
void printSt(int num, int pc);
void printSti(int num, int pc);
void printStr(int num);
void printTrap(int num);

int main()
{
    char file[] = "test1.hex";
    printAssembly(file);
}

void printAssembly(char filename[])
{
    FILE *infile;
    infile = fopen(filename, "r");
    if (infile == NULL){
    printf("File %s is null.\n", filename);
    } 
    else 
    {
        int count = 0;
        int instruction = 0;
        int pc = 0;
        int bitshift = 0;
        //Read the initial PC as an integer and save


        //While not at end of file and not over the limit
        while (fscanf(infile, "%x", &instruction) != EOF && count < LIMIT) {
            count++;  //Count number of lines for limit
            //Remove the print and put your code here
            //Increment the PC
            //Figure out the oppcode from the high order 4 bits of the instruction
            //Use a big if or switch to call the appropriate print function.
            //Pass the function the full instruction and the PC, but only if necessary.
            bitshift = (instruction >> 12) & 15;
            
            if (count == 1)
            {
                pc = instruction;
            }
            else if (bitshift == 1)
            {
                printAdd(instruction);
            }
            else if(bitshift == 5)
            {
                printAnd(instruction);
            }
            else if (bitshift == 0)
            {
                printBr(instruction, pc);
            }
            else if (bitshift == 12)
            {
                printJmpRet(instruction);
            }
            else if (bitshift == 4)
            {
                printJsrJsrr(instruction, pc);
            }
            else if (bitshift == 2)
            {
                printLd(instruction, pc);
            }
            else if (bitshift == 10)
            {
                printLdi(instruction, pc);
            }
            else if (bitshift == 6)
            {
                printLdr(instruction);
            }
            else if (bitshift == 14)
            {
                printLea(instruction, pc);
            }
            else if (bitshift == 9)
            {
                printNot(instruction);
            }
            else if (bitshift == 12)
            {
                printJmpRet(instruction);
            }
            else if (bitshift == 8)
            {
                printRti(instruction);
            }
            else if (bitshift == 3)
            {
                printSt(instruction, pc);
            }
            else if (bitshift == 11)
            {
                printSti(instruction, pc);
            }
            else if (bitshift == 7)
            {
                printStr(instruction);
            }
            else if (bitshift == 15)
            {
                printTrap(instruction);
            }
            pc++;
        }
    }
}

void printAdd(int instruction)
{
    int dReg = getSubInt(9, 11, instruction);
    int sReg1 = getSubInt(6, 8, instruction);
    int sReg2 = getSubInt(0, 2, instruction);
    int fifthBit = getSubInt(5,5,instruction);
    if (fifthBit == 1)
    {
        int imm = getSubInt(0, 4, instruction);
        if (getSubInt(4, 4, instruction) == 1)
        {
            sReg2 = ((~imm) & 15) + 1;
            printf("ADD\tR%d, R%d, #-%d\n", dReg, sReg1, sReg2);
        }
        else
        {
            sReg2 = imm;
            printf("ADD\tR%d, R%d, #%d\n", dReg, sReg1, sReg2);
        }
    }
    else
    {
        sReg2 = instruction & 7;
        printf("ADD\tR%d, R%d, R%d\n", dReg, sReg1, sReg2);
    }
}
void printAnd(int instruction)
{
     int dReg = getSubInt(9, 11, instruction);
     int sReg1 = getSubInt(6, 8, instruction);
     int sReg2 = getSubInt(0, 2, instruction);
     int fifthBit = getSubInt(5,5,instruction);
     if (fifthBit == 1)
     {
        int imm = getSubInt(0, 4, instruction);
        if (getSubInt(4, 4, instruction) == 1)
        {
            sReg2 = ((~imm) & 15) + 1;
            printf("AND\tR%d, R%d, #-%d\n", dReg, sReg1, sReg2);
        }
        else
        {
            sReg2 = imm;
            printf("AND\tR%d, R%d, #%d\n", dReg, sReg1, sReg2);
        }
    }
    else
    {
        sReg2 = instruction & 7;
        printf("AND\tR%d, R%d, R%d\n", dReg, sReg1, sReg2);
    }
}
void printBr(int instruction, int pc)
{
     int signBit = getSubInt(9, 11, instruction);
     int signNum = getSubInt(8,8,instruction);
     int offset = getSubInt(0,7,instruction);
     if (signBit == 0)
     {
         printf("BR\t");
     }
     else if (signBit == 1)
     {
         printf("BRP\t");
     }
     else if (signBit == 2)
     {
         printf("BRZ\t");
     }
     else if (signBit == 3)
     {
         printf("BRZP\t");
     }
     else if (signBit == 4)
     {
         printf("BRN\t");
     }
     else if (signBit == 5)
     {
        printf("BRNP\t");
     }
     else if (signBit == 6)
     {
         printf("BRNZ\t");
     }
     else if (signBit == 7)
     {
         printf("BRNZP\t");
     }
     int pcOff = 0;
     if (signNum == 1)
     {
         pcOff = pc - (((~offset) & 255) + 1);
     }
     else
     {
         pcOff = pc + offset;
     }
     printf("x%X\n", pcOff);
}
void printJmpRet(int instruction)
{
    int reg = getSubInt(6,8,instruction);
    if (reg == 7)
    {
        printf("RET\n");
    }
    else
    {
        printf("JMP\tR%d\n", reg);
    }
}
void printJsrJsrr(int instruction, int pc)
{
    int whichOne = getSubInt(11,11,instruction);
    if (whichOne == 1)
    {
        int signBit = getSubInt(10,10,instruction);
        int offset = getSubInt(0,9,instruction);
        int pcOff = 0;
        if (signBit == 1)
        {
            pcOff = pc - (((~offset) & 255) + 1);
        }
        else
        {
            pcOff = pc + offset;
        }
        printf("JSR\tx%X\n", pcOff);
    }
    else
    {
        int reg = getSubInt(6,8,instruction);
        printf("JSRR\tR%d\n", reg);
    }
}
void printLd(int instruction, int pc)
{
    int reg = getSubInt(9,11,instruction);
    int signBit = getSubInt(8,8,instruction);
    int offset = getSubInt(0,7,instruction);
    int pcOff = 0;
    if (signBit == 1)
    {
        pcOff = pc - (((~offset) & 255) + 1);
    }
    else
    {
        pcOff = pc + offset;
    }
    printf("LD\tR%d, x%X\n", reg, pcOff);
}
void printLdi(int instruction, int pc)
{
    int reg = getSubInt(9,11,instruction);
    int signBit = getSubInt(8,8,instruction);
    int offset = getSubInt(0,7,instruction);
    int pcOff = 0;
    if (signBit == 1)
    {
        pcOff = pc - (((~offset) & 255) + 1);
    }
    else
    {
        pcOff = pc + offset;
    }
    printf("LDI\tR%d, x%X\n", reg, pcOff);
}
void printLdr(int instruction)
{
    int dReg = getSubInt(9,11,instruction);
    int sReg = getSubInt(6,8,instruction);
    int signBit = getSubInt(5,5,instruction);
    int offset = getSubInt(0,4,instruction);
    if (signBit == 1)
    {
        offset = (((~offset) & 31) + 1);
        printf("LDR\tR%d, R%d, #-%d\n", dReg, sReg, offset);
    }
    else
    {
        printf("LDR\tR%d, R%d, #%X\n", dReg, sReg, offset);
    }
}
void printLea(int instruction, int pc)
{
    int reg = getSubInt(9,11,instruction);
    int signBit = getSubInt(8,8,instruction);
    int offset = getSubInt(0,7,instruction);
    int pcOff = 0;
    if (signBit == 1)
    {
        pcOff = pc - (((~offset) & 255) + 1);
    }
    else
    {
        pcOff = pc + offset;
    }
    printf("LEA\tR%d, x%X\n", reg, pcOff);
}
void printNot(int instruction)
{
    int dReg = getSubInt(9,11,instruction);
    int sReg = getSubInt(6,8,instruction);
    printf("NOT\tR%d, R%d\n", dReg, sReg);
}
void printRti(int instruction)
{
    printf("RTI\n");
}
void printSt(int instruction, int pc)
{
    int reg = getSubInt(9,11,instruction);
    int signBit = getSubInt(8,8,instruction);
    int offset = getSubInt(0,7,instruction);
    int pcOff = 0;
    if (signBit == 1)
    {
        pcOff = pc - (((~offset) & 255) + 1);
    }
    else
    {
        pcOff = pc + offset;
    }
    printf("ST\tR%d, x%X\n", reg, pcOff);
}
void printSti(int instruction, int pc)
{
    int reg = getSubInt(9,11,instruction);
    int signBit = getSubInt(8,8,instruction);
    int offset = getSubInt(0,7,instruction);
    int pcOff = 0;
    if (signBit == 1)
    {
        pcOff = pc - (((~offset) & 255) + 1);
    }
    else
    {
        pcOff = pc + offset;
    }
    printf("STI\tR%d, x%X\n", reg, pcOff);
}
void printStr(int instruction)
{
    int dReg = getSubInt(9,11,instruction);
    int sReg = getSubInt(6,8,instruction);
    int signBit = getSubInt(5,5,instruction);
    int offset = getSubInt(0,4,instruction);
    if (signBit == 1)
    {
        offset = (((~offset) & 31) + 1);
        printf("STR\tR%d, R%d, #-%d\n", dReg, sReg, offset);
    }
    else
    {
        printf("STR\tR%d, R%d, #%X\n", dReg, sReg, offset);
    }
}
void printTrap(int instruction)
{
    int trap = getSubInt(0,11,instruction);
    if (trap == 32)
    {
        printf("GETC\n");
    }
    else if (trap == 33)
    {
        printf("OUT\n");
    }
    else if (trap == 34)
    {
        printf("PUTS\n");
    }
    else if (trap == 35)
    {
        printf("IN\n");
    }
    else if (trap == 36)
    {
        printf("PUTSP\n");
    }
    else if (trap == 37)
    {
        printf("HALT\n");
    }
}
