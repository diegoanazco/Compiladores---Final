#include <iostream>
#include <fstream>
using namespace std;

ofstream os("funcion_factorial.s");


void cabecera()
{
	os <<".data"<<endl;
	os <<".text"<<endl;
	os <<"main:"<<endl;
}

void invocacion(int a)
{
	os << "sw $fp , 0($sp)" << endl;
	os << "addiu $sp, $sp, -4" << endl;
	os << "li $a0," << a << endl;
	os << "li $t1,1" << endl;
	os << "li $t2," << a <<endl;
}

void bucle_for()
{
	os << "for:" << endl;
	os << "beq $a0,$t1,f_entry"<<endl;
	os << "sw $a0, 0($sp)" << endl;
	os << "addiu $sp,$sp,-4"<<endl;
	os << "add $a0,$a0,-1"<<endl;
	os << "b for"<<endl;
}

void f_entry()
{
	os << "f_entry:"<<endl;
	os << "move $fp,$sp"<<endl;
	os << "sw $ra,0($sp)"<<endl;
	os << "lw $a1, 4($fp)" << endl;
	os << "mul $a0,$a1,$a0" << endl;
	os << "addiu $sp,$sp,4" << endl;
	os << "beq $a1, $t2, end" <<endl;
	os << "j f_entry"<<endl;
}


void definicion()
{
	bucle_for();
	f_entry();
}

void end()
{
	os << "end:" <<endl;
	os << "li $v0,1"<<endl;
	os << "syscall" << endl;
	os << "li $v0,10" << endl;
	os << "syscall" << endl;
}

int main()
{
	cabecera();
	int factorial = 7;
	invocacion(7);
	definicion();
	end();
	return 0;
}
