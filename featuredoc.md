# Disponens Omnia feature document

Disponens omnia is a language with the following keywords:

+ int
+ char
+ float
+ func
+ enum
+ struct
+ union
+ mut
+ unsigned
+ signed
+ short
+ if
+ else
+ return
+ sizeof
+ stack
+ register
+ file

these keywords can be split into the following categories
+ types
+ type modifiers
+ mutability
+ control flow
+ compile constant retrieval
+ variable scope modifiers

We will now categorize the keywords above

+ types
    - int
    - char
    - float
    - func
    - enum
    - struct
    - union
+ type modifiers
    - signed
    - unsigned
    - short
+ mutability
    - mut
    - const
+ control flow
    - if
    - else
    - return
+ compile constant retrieval
    - sizeof
+ variable storage modifiers
    - stack
    - register
    - file

We shall now define the usage of these categories
+ types
    denote how much space, and in what way the values given should be handled
+ type modifiers
    these change the usage of a type, for example, short int is 16 bytes while int is 32
+ mutability
    denote whether or not a variable can be changed, const by default
+ control flow
    allows for code to be run under specific circumstances
+ compile constant retrieval
    certain constants are stored by the compiler, i.e the number of bytes in an integer, these keywords retrieve them for the usage of a program
+ variable storage modifiers
    change the way in which a variable is stored

## language features
Disponens omnia has three major categories of features,
+ computation: mathematical operations
+ variables: the ability to store and move around values with little issue
+ functions: the ability to run code blocks repeatedly with parameters and return to the original place in running
+ control flow: the ability to run code blocks depending on conditions

## computation

Disponens omnia supports the following operations:

+ '\+': addition: a '\+' b
+ '\-': subtraction: a '\-' b
+ '\*': multiplication: a '\*' b
+ '/': division: a '/' b
+ ',': does two expressions and evaluates to the second: a ',' b
+ '=': sets variable a to b and returns b: a '=' b
+ '\>': checks if a is greater than b and returns 1 on true and 0 on false: a '\>' b
+ '\<': similar to greater, but instead checks for less than: a '\<' b
+ '\!': if a is 0 return 1 else return 0: '\!'a
+ '|': checks if a or be are not 0, and returns 1 if true and 0 on false: a '|' b
+ '&': checks if a and be are not 0, and returns 1 if true and 0 on false: a '&' b

additionally mathematical expressions can be placed in brackets to ensure their sooner completion
i.e `(a + b) * 5`

## syntax clarifications

throughout the course of this document we will be defining the syntax as so:

any word surrounded by angle brackets ('\<' or '\>') are tokens

brackets seperate terms, '('\<iden\> | \<constant\> ')' | \<expr\> is different to \<iden\> | \<constant\> | \<expr\>

defining expressions:
```
<expr>
    <iden> | <const> |
    (<expr> <operator> <expr>) |
    ('(' <expr> ')')
```

## variables

As one may understand from other languages variables are an incredibly important part of any programming language.
Variables can be in one of two states at compile time, declared, and defined. A variable must be declared before its definition. Declaration saves a variables identifyer and type to the compiler, definition just assigns that identifyer a value

Declaration Syntax
```
<var dec>
    'mut'? <type modifyer> <type> <iden>';'
```
Definition Syntax
```
<var def>
    <iden> '=' <expr>';'
```
for example:
```C
mut unsigned int X;
X = 10;
```

if a variable is constant then it can only be defind once, but if it is mutable it can be defined as many times as you want (provided the redefinition is happening in the scope the variable was first defined, or a scope local to the scope the first definition)

## functions

Functions in disponens omnia work similarly to the way they would in other languages. The only major difference is that they must be declared similarly to variables.
```
NOTE: functions in disponens omnia use the CDECL calling convention
CDECL is defined as so:
    arguments are pushed right to left, and the calling function cleans the stack so the following function:
        function = (int x, int y) return int {
            return 0;
        }
    would be called as so in assembly
        push y
        push x
        call function
        add esp, 8
    and in the function definition
        push ebp
        mov ebp, esp ; create new stack frame
        mov eax, 0
        pop ebp ; return to old stack frame
        ret
```
functions in disponens omnia are defined as a pointer to the assembly produced by its code for example:

```C
func function;
function = (int x) return int {
    return x + 10;
}
```

becomes:

```x86asm
function: ;x is on the top of the stack
    push ebp
    mov ebp, esp
    mov eax, [ebp + 8]
    add eax, 10
    pop ebp
    ret
```

and one can simply pass around reference to function for example:

```C
func function;
function = (int x) return int {
    return x + 10;
}
func function_2;
function_2 = (func function, int x) return int {
    return function(x);
}

func main;
main = () return int {
    function_2(function, 10);
    return 0;
}
```
`NOTE: main is the entry function to the program`
becomes:

```x86asm
function: ; x on top of stack
    
    ret
function_2: ; function is on top of stack, x is below it
```











