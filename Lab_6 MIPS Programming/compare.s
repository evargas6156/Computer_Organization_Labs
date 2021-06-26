	.data
n:	.word 25
str1:   .asciiz "Less than\n"
str2:   .asciiz "Less than or equal to\n"
str3:   .asciiz "Greater than\n"
str4:   .asciiz "Greater than or equal to\n"


	.text
	
main: 
	la $t0, n
	lw $s0, 0($t0) 
	
	li $v0, 5
	syscall
	
	add $s1, $v0, $0
	
	#slt $t0, $s1, $s0
	#bne $t0, $0, lessthan
		#li	$v0, 4   #prints out if greater than or equal to  if not it branches to less than 
		#la	$a0, str4
		#syscall
		#j after
	
#lessthan:
	#li	$v0, 4
	#la	$a0, str1
	#syscall
	#j after
	
	slt $t0, $s0, $s1
	bne $t0, 1, lessthanequal
		li	$v0, 4
		la	$a0, str3
		syscall
		j after
lessthanequal:
	li	$v0, 4
	la	$a0, str2
	syscall
	j after
after: 