	.data
str1:   .asciiz "Please enter a number: "
str2:   .asciiz "Sum of positive numbers is: \n"
str3:   .asciiz "\nSum of negative numbers is: \n"
	
	
	.text
	
loop: 	
	#ask the user for input
	li	$v0, 4
	la	$a0, str1
	syscall
	
	#get input and store it in $v0
	li $v0, 5    
	syscall
	
	#if surrent inout is less than 0 ass to negative sum in $s0, otherwise add to positive sum in $s1
	slt $t0, $v0, $0
	bne $t0, 1, positive
		add $s0, $s0, $v0
		j done 
	positive: 
		add $s1, $s1, $v0
		j done
	done:
	#if the current input does not equal zero then loop again
	bne $v0, $0, loop 
	
output: 
	#print the positive sum 
	li	$v0, 4
	la	$a0, str2
	syscall	
	
	li $v0, 1       
	add $a0, $0, $s1 
	syscall 
	
	#print the negative sum 
	li	$v0, 4
	la	$a0, str3
	syscall
	
	li $v0, 1       
	add $a0, $0, $s0 
	syscall 
	
	
		