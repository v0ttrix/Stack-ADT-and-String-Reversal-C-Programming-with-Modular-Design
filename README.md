# Stack ADT and String Reversal - C Programming with Modular Design

## Overview

This project demonstrates professional C programming practices through the implementation of a Stack Abstract Data Type (ADT) and its application in string reversal. The project showcases modular design, proper memory management, and robust error handling.

## Project Structure

```
Stack-ADT-and-String-Reversal-C-Programming-with-Modular-Design/
├── src/
│   ├── dynamic_stack/          # Dynamic stack implementation
│   ├── static_stack/           # Static stack implementation  
│   └── common/                 # Shared utilities
├── include/                    # Header files
├── tests/                      # Unit tests
├── docs/                       # Documentation
├── Makefile                    # Build configuration
└── README.md                   # This file
```

## Features

### Dynamic Stack (Spec1)
- Dynamic memory allocation
- Configurable stack size
- Comprehensive error handling
- Memory leak prevention
- Thread-safe operations

### Static Stack (Spec2)  
- Fixed-size character stack
- String reversal functionality
- Input validation
- Buffer overflow protection

## Building the Project

### Prerequisites
- GCC compiler (version 7.0 or higher)
- Make utility
- Standard C library

### Compilation
```bash
# Build all components
make all

# Build specific components
make dynamic_stack
make static_stack

# Clean build artifacts
make clean
```

## Usage

### Dynamic Stack Example
```bash
./bin/dynamic_stack_demo
```

### String Reversal Example
```bash
./bin/string_reversal_demo
```

## API Documentation

### Dynamic Stack API
- `Stack* stack_create(size_t capacity)` - Create new stack
- `bool stack_push(Stack* stack, int value)` - Push value onto stack
- `bool stack_pop(Stack* stack, int* value)` - Pop value from stack
- `bool stack_is_empty(const Stack* stack)` - Check if stack is empty
- `bool stack_is_full(const Stack* stack)` - Check if stack is full
- `void stack_destroy(Stack* stack)` - Free stack memory

### Static Stack API
- `bool char_stack_push(char c)` - Push character onto stack
- `bool char_stack_pop(char* c)` - Pop character from stack
- `bool char_stack_is_empty(void)` - Check if stack is empty
- `bool char_stack_is_full(void)` - Check if stack is full
- `void char_stack_clear(void)` - Clear all stack contents

## Design Principles

1. **Modular Design**: Separate concerns with clear interfaces
2. **Error Handling**: Comprehensive validation and error reporting
3. **Memory Safety**: Proper allocation, deallocation, and bounds checking
4. **Code Quality**: Consistent style, meaningful names, and documentation
5. **Testability**: Unit tests for all major functionality

## Testing

Run the test suite:
```bash
make test
```

## Contributing

1. Follow the established coding style
2. Add unit tests for new functionality
3. Update documentation as needed
4. Ensure memory safety and error handling

## Author

Jaden Mardini - Computer Science Student

## License

This project is for educational purposes.
