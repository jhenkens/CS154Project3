addi $10, $0, 1
addi $12, $0, 5
reset: addi $10, $10, 2
addi $11, $0, 0
start: addi $11, $11, 1
bge $11, $10, end
jal start
end: bne $12, $10, reset
addi $10, $0, 15
addi $11, $0, 25
add $30, $31, $0
add $13, $11, $10
xori $14, $11, 15
slt $12, $10, $11
slt $15, $11, $10
slt $16, $10, $10
sub $17, $10, $11
sub $18, $11, $10
addi $10, $0, 8
sw $11, 0($10)
lw $19, 0($10)
addi $1, $0, 0
addi $5, $0, 3
prefinalloop: addi $1, $1, 1
addi $7, $0, 0
bne $1, $5, prefinalloop
addi $2, $0, 0
addi $5, $0, 5
finalloop: addi $2, $2, 1
addi $7, $0, 0
bne $2, $5, finalloop
bne $19, $0, trueend
add $21, $0, $19
trueend: add $20, $0, $19
