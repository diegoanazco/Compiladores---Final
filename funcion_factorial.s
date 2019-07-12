.data
.text
main:
sw $fp , 0($sp)
addiu $sp, $sp, -4
li $a0,4
li $t1,1
li $t2,4
for:
beq $a0,$t1,f_entry
sw $a0, 0($sp)
addiu $sp,$sp,-4
add $a0,$a0,-1
b for
f_entry:
move $fp,$sp
sw $ra,0($sp)
lw $a1, 4($fp)
mul $a0,$a1,$a0
addiu $sp,$sp,4
beq $a1, $t2, end
j f_entry
end:
li $v0,1
syscall
li $v0,10
syscall
