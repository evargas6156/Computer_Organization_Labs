.data 
greeting: .asciiz "Welcome to BobCat Candy, home to the famous BobCat Bars!\n"
input1: .asciiz "Please enter the price of a BobCat Bar: \n"
invalInput1: .asciiz "Please enter a price greater than zero!\n"
input2: .asciiz "Please enter the number of wrappers needed to exchange for a new bar: \n"
invalInput2: .asciiz "Please enter a number of wrappers greater than one!\n"
input3: .asciiz "How much do you have?\n"
invalInput3: .asciiz "Please enter an amount of money greater than or equal to zero!\n"
goodInput: .asciiz "Good! Let me run the number...\n"
maxBars1: .asciiz "You first buy "
maxBars2: .asciiz " bars.\n"
newBars1: .asciiz "Then, you will get another "
newBars2: .asciiz " bars.\n"
finalOut1: .asciiz "With $"
finalOut2: .asciiz ", you will recieve a maximum of "
finalOut3: .asciiz " BobCat Bars!\n"
# Declare any necessary data here



.text

main:
		#This is the main program.
		#It first asks user to enter the price of each BobCat Bar.
		#It then asks user to enter the number of bar wrappers needed to exchange for a new bar.
		#It then asks user to enter how much money he/she has.
		#It then calls maxBars function to perform calculation of the maximum BobCat Bars the user will receive based on the information entered. 
		#It then prints out a statement about the maximum BobCat Bars the user will receive.
		
		addi $sp, $sp -8	# Feel free to change the increment if you need for space.
		sw $ra, 0($sp)
		# Implement your main here
		
		#print the greeting
		li $v0, 4 
		la $a0, greeting 
		syscall 
		
		#ask the user for the first input
		li $v0, 4 
		la $a0, input1 
		syscall 	
		
		#get the first input, price, from the user, save into $s0, repeat until valid 
		li $v0, 5	
		syscall
		add $s0, $v0, $zero	
		
		whileL1: bgt $s0, $zero, getInput2
			li $v0, 4 
			la $a0, invalInput1 
			syscall 
			
			li $v0, 5	
			syscall
			add $s0, $v0, $zero
			
			j whileL1	
		
	getInput2:
		#ask user for second input 
		li $v0, 4 
		la $a0, input2
		syscall 	
		
		#get the first input, price, from the user, save into $s1, repeat until valid 
		li $v0, 5	
		syscall
		add $s1, $v0, $zero	
		
		addi $t0, $zero, 1
		whileL2: bgt $s1, $t0, getInput3
			li $v0, 4 
			la $a0, invalInput2 
			syscall 
			
			li $v0, 5	
			syscall
			add $s1, $v0, $zero
			
			j whileL2	
		
	getInput3:
		#ask user for third input 
		li $v0, 4 
		la $a0, input3
		syscall 	
		
		#get the first input, price, from the user, save into $s2, repeat until valid 
		li $v0, 5	
		syscall
		add $s2, $v0, $zero	
		
		whileL3: bge $s2, $zero, AfterInput
			li $v0, 4 
			la $a0, invalInput3
			syscall 
			
			li $v0, 5	
			syscall
			add $s2, $v0, $zero
			
			j whileL3	
		
		
	AfterInput:
		#store third inpout to stack as its needed after function call
		sw $s2, 4($sp)
		
		#print the good input confirmation 
		li $v0, 4 
		la $a0, goodInput  
		syscall 
		
		#prepare arguments for max bars function 
		add $a1, $s0, $zero
		add $a0, $s1, $zero
		add $a2, $s2, $zero
		
		# Call maxBars to calculate the maximum number of BobCat Bars
		jal maxBars
		 	
		#restore money from stack and save v0 to s0
		add $s0, $v0, $zero
		lw $s1, 4($sp)
		
		# Print out final statement here
		li $v0, 4 
		la $a0, finalOut1 
		syscall
			
		li $v0, 1
		add $a0, $s1, $zero
		syscall
			
		li $v0, 4 
		la $a0, finalOut2
		syscall
		
		li $v0, 1
		add $a0, $s0, $zero
		syscall
			
		li $v0, 4 
		la $a0, finalOut3
		syscall

		j end			# Jump to end of program
maxBars:
		# This function calculates the maximum number of BobCat Bars.
		# It takes in 3 arguments ($a0, $a1, $a2) as n, price, and money. It returns the maximum number of bars
		
		#create space for two ints on the stack and save ra
		addi $sp, $sp, -8
		sw $ra, 0($sp)
		
		#calculate the bars purchased by divinding money by price store in $s0
		div $s0, $a2, $a1
		#save $a0 into $s1
		add, $s1, $a0, $zero
		
		bne $s0, $zero, MaxBarsElse
			#if purchased bars is zero, set return to zero and end function
			add $v0, $zero, $zero
			j EndMaxBars
		MaxBarsElse:	
			#print the amount of bars purchased
			li $v0, 4 
			la $a0, maxBars1 
			syscall
			
			li $v0, 1
			add $a0, $s0, $zero
			syscall
			
			
			li $v0, 4 
			la $a0, maxBars2
			syscall
			
			#set up arguments for helper function and save necessary parameters  
			sw $s0, 4($sp)
			add $a0, $s0, $zero
			add $a1, $s1, $zero 
			
			# Call a helper function to keep track of the number of bars.
			jal newBars
			
			#add pruchased bars to the value returned by newbars and return
			lw $s0, 4($sp)
			add $v0, $v0, $s0
			
			j EndMaxBars
		

	EndMaxBars:	
		lw $ra, 0($sp)
		addi $sp, $sp, 8
		jr $ra
		# End of maxBars

newBars:
		# This function calculates the number of BobCat Bars a user will receive based on n.
		# It takes in 2 arguments ($a0, $a1) as number of wrappers left so far and n.
		
		#create space for two numbers on the stack and store ra
		addi $sp, $sp, -8
		sw $ra, 0($sp)
		
		bge $a0, $a1, NewBarsElse
			#if numbars < n then return 0
			add $v0, $zero, $zero 
			j EndNewBars
		NewBarsElse:
			#calculate number of bree bars by dividing numBars by n 
			div $s0, $a0, $a1
			
			#store a0 into s1
			add $s1, $a0, $zero
			
			#print the amount of free bars recieved 
			li $v0, 4 
			la $a0, newBars1 
			syscall
			
			li $v0, 1
			add $a0, $s0, $zero
			syscall
			
			
			li $v0, 4 
			la $a0, newBars2
			syscall
			
			#prepare to recurssively call new bars
			#set up arguments and store free bars to stack a1 remains the same 
			sw $s0, 4($sp)
			add $a0, $s0, $zero
			
			jal newBars 
			
			#restore free bars from stack and add it to return value 
			lw $s0, 4($sp)
			add $v0, $v0, $s0 
			
			j EndNewBars 
	EndNewBars:
		lw $ra, 0($sp)
		addi, $sp, $sp, 8	
		jr $ra
		# End of newBars

end: 
		# Terminating the program
		lw $ra, 0($sp)
		addi $sp, $sp 8
		li $v0, 10 
		syscall
