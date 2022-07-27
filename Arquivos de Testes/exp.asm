SECAO TEXTO

        INPUT A
        INPUT B
        LOAD B
        SUB UM
        STORE CONT
        COPY A, RES
LOOP:   LOAD RES ;10
        MULT A
        STORE RES
        LOAD CONT
        SUB UM
        STORE CONT
        JMPZ FIM
        JMP LOOP
FIM:    OUTPUT RES ;24
        STOP
    
SECAO DADOS
A: SPACE ;27
B: SPACE ;28
CONT: SPACE ;29
RES: SPACE ;30
UM: CONST 1 ;31