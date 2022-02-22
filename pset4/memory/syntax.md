# Addresses
## Address operator

```c
&
```

This operator returns the position of something in memory

```c
int number = 50;
int *address_in_memory = &number;
printf("%i\n", number); //Output: 50
printf("%p\n", address_in_memory); //Output: 0x7ffc58133d8c
```

## Dereference operator

```c
*
```

This operator returns the contents of a pointer

```c
int number = 50;
int *address_in_memory = &number;
int what_is_inside = *address_in_memory;
printf("%i\n", number); //Output: 50
printf("%p\n", address_in_memory); //Output: 0x7ffc58133d8c
printf("%i\n", what_is_inside); //Output: 50
```

# Pointers

In C, a pointer is a type like ``int`` or ``char``, but instead of storing a number or a character, it stores a position in the computer's memory in the form of a hexadecimal number like 0xFFFFFFFFFFFF. But to create a pointer, in addition to declaring a position, it is also necessary to declare the type of data stored in that position.

## Creating a pointer

```c
//Declaring common variables 
int n = 50;
char c = 'A';
char s[] = "CS50";

//Declaring pointers
int *point_n = &n;
char *point_c = &c;
char *point_s = &s;
```

