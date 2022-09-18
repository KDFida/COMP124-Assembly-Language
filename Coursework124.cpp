#include <stdio.h> 
#include <stdlib.h> 

int main(void) {
    // Student ID: 201578434
    // Declare variables here (C syntax) 
    // All these variables are used later
    int num, number;
    int counterPositive = 0;
    int counterNegative = 0; 
    int counterZero = 0;
    char numberRequested[] = "How many numbers: ";
    char enterNumberText[] = "Enter a number: ";
    char numberFmt[] = "%d";
    char hyphens[] = "------------\n";
    char positive[] = "Positive: %2d";
    char negative[] = "\nNegative: %2d";
    char zero[] = "\nZero: %6d";

    _asm {

        // Put address of string to the accumulator, in this case address of numberRequested
        // which then is pushed into a stack (stack the parameter)
        // the string is then outputted to the terminal, in this case "How many numbers: ".
        // Finally restore the stack by clearing the stack (clean 4 bytes from stack)
        lea eax, numberRequested
        push eax
        call printf
        add esp, 4

        // Put the address of integer num to the accumulator,
        // which then is pushed into a stack (stack the parameter).
        // Put the address of format of the input in the accumulator, in this case numberFmt,
        // this is also pushed into the stack (stack the parameter).
        // Then call scanf to allow the user to input and the input will be stored in num.
        // Finally restore the stack by clearing the stack (clean 8 bytes from stack)
        lea eax, num
        push eax
        lea eax, numberFmt
        push eax 
        call scanf
        add esp, 8

        // Move the value in num into ecx, the counter register.
        // This sets up a loop counter.
        mov ecx, num
        enterNumberLoop:

            // Save the ecx in to the stack
            // Put address of string to the accumulator, in this case enterNumberText
            // which then is pushed into a stack (stack the parameter)
            // the string is then outputted to the terminal, in this case Enter a number: ".
            // Finally restore the stack by clearing the stack (remove parameter)    
            push ecx
            lea eax, enterNumberText 
            push eax 
            call printf
            pop eax

            // Put the address of int to the accumulator, in this case address of number,
            // which then is pushed into a stack (stack the parameter).
            // Put the address of format of the input in the accumulator, in this case numberFmt,
            // this is also pushed into the stack (stack the parameter).
            // Then call scanf to allow the user to input and the input will be stored in number.
            // Finally restore the stack by clearing the stack (clean 8 bytes from stack)
            lea eax, number
            push eax
            lea eax, numberFmt
            push eax
            call scanf
            add esp, 8

            // Move the value in number into eax, the accumulator.
            // Compare the accumulator to value 0.
            // If accumulator is greater than 0 then jump to label p.
            // Else if the accumulator is less than 0, then jump to label number
            // Else if the accumulator is equal to 0, then jump to label z.
            mov eax, number
            cmp eax, 0
            jg p
            jl n
            je z

                // When label p is called, 1 is added to the counterPositive
                // then jump to label end
                p: 
                    add counterPositive, 1
                    jmp end
                
                // When label n is called, 1 is added to the counterNegative
                // then jump to label end
                n:
                    add counterNegative, 1
                    jmp end

                // When label z is called, 1 is added to the counterZero
                // then jump to label end
                z:
                    add counterZero, 1
                    jmp end
                end:
        
        // loop is based on the ecx, when the ecx reaches value 0 the loop terminates
        // and retore ecx (pop ecx)
            pop ecx
        loop enterNumberLoop 
        
        // Put address of string to the accumulator, in this case address of hyphens
        // which then is pushed into a stack (stack the parameter)
        // the string is then outputted to the terminal, in this case "------------\n".
        // Finally restore the stack by clearing the stack (clean 4 bytes from stack)
        lea eax, hyphens
        push eax
        call printf
        add esp, 4

        // Push counterPositive in to the stack.
        // Put the address of integer positive in the accumulator,
        // output the value of counterPositive.
        // Finally restore the stack by clearing the stack (clean 8 bytes from stack)
        push counterPositive
        lea eax, positive
        push eax 
        call printf
        add esp, 8

        // Push counterNegative in to the stack.
        // Put the address of integer negative in the accumulator,
        // output the value of counterNegative.
        // Finally restore the stack by clearing the stack (clean 8 bytes from stack)
        push counterNegative
        lea eax, negative
        push eax 
        call printf
        add esp, 8

        // Push counterZero in to the stack.
        // Put the address of integer zero in the accumulator,
        // output the value of counterZero.
        // Finally restore the stack by clearing the stack (clean 8 bytes from stack)
        push counterZero
        lea eax, zero
        push eax 
        call printf
        add esp, 8
    }
    return 0;
}