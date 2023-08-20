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
