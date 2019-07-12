# Informe Final - Compiladores 

El siguiente archivo .cpp tiene como finalidad crear la definición y la invocación de un factorial en SPIM. 
Funcion_factorial genera un archivo .s con la finalidad de poder correrlo en el programa llamado "QTSPIM" para poder probar y ejecutar el código. Comencemos a explicar el código.

## Cabecera

Esta función no tiene mucho misterio, cuando creamos un archivo .s necesitamos agregar ciertos datos por defecto. Notamos que aquí iniciamos nuestro "main" donde se encontrará nuestra invocación.

```
void cabecera()
{
	os <<".data"<<endl;
	os <<".text"<<endl;
	os <<"main:"<<endl;
}

``` 
## Invocacion

Aquí tenemos a la invocación del factorial, recibe un parametro entero que es el número de factorial que queremos obtener.
* En la primera linea apuntamos tanto fp como sp al inicio de la pila. 
* Movemos el puntero del sp en la pila.
* Recibimos el valor que este en nuestro parametro de entrada y lo guardamos en a0.
* Creamos una variable contador del for para llenar la pila.
* Creamos una variable contador del f_entry para hacer pop en la pila o vaciarla.

``` 
void invocacion(int a)
{
	os << "sw $fp , 0($sp)" << endl;
	os << "addiu $sp, $sp, -4" << endl;
	os << "li $a0," << a << endl;
	os << "li $t1,1" << endl;
	os << "li $t2," << a <<endl;
}
``` 

##  Bucle_For

El bucle for se encarga de llenar la pila con los datos del factorial, por ejemplo, si nos pide factorial del número 3, lo que almacenará en la pila serán los valores: 3,2,1. 
De igual manera vamos restando el acumulador. Podemos observar también que para poder insertar todo los valores del factorial, vamos moviendo el sp en la pila, por ello está dentro del bucle for. 
``` 
void bucle_for()
{
	os << "for:" << endl;
	os << "beq $a0,$t1,f_entry"<<endl;
	os << "sw $a0, 0($sp)" << endl;
	os << "addiu $sp,$sp,-4"<<endl;
	os << "add $a0,$a0,-1"<<endl;
	os << "b for"<<endl;
}
``` 

## F_Entry()

F_entry es el encargado de poder hacer todos los pop de la pila como usted nos enseñó que siempre debe quedar. Y también vamos multiplicando los valores que hemos metido a la pila en nuestro bucle for para poder hallar el factorial.
``` 
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
``` 
## Definicion

Como vemos tanto en la función bucle_for y en la función f_entry realizamos todo el proceso de la definición del factorial, por lo cual en esta función solo las llamamos.

``` 
void definicion()
{
	bucle_for();
	f_entry();
}
``` 
## End

En nuestra función end lo que hacemos es imprimir el resultado del factorial que se ha quedado en el acumulador, y finalmente terminamos todo el proceso.

``` 
void end()
{
	os << "end:" <<endl;
	os << "li $v0,1"<<endl;
	os << "syscall" << endl;
	os << "li $v0,10" << endl;
	os << "syscall" << endl;
}
``` 
## Main

En el main solo llamamos en orden a los procedimientos para que se pueda crear nuestro archivo .s con éxito. Luego declaramos la variable factorial, para poder pasarle a nuestra función invocación. Llamamos a definición para que saque el factorial (en este caso de 4). Terminamos con end.

``` 
int main()
{
	cabecera();
	int factorial = 4;
	invocacion(factorial);
	definicion();
	end();
	return 0;
}
``` 

## Pruebas

Subo un video de youtube donde probamos el factorial de 4 y luego probamos con el factorial de 7. 

https://youtu.be/6yddKkHtj1Y

