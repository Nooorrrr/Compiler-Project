# Compiler-Project

This is a project about building a compiler        

## Getting Started

These instructions will guide you on how to set up and run this project on your local machine for development and testing purposes.

---

## Prerequisites

Ensure you have the following installed on your system:

- **Flex**: A fast lexical analyzer generator
- **Bison**: A parser generator
- **GCC**: A C compiler

---

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Nooorrrr/Compiler-Project
   ```

2. Navigate to the project directory:
   ```bash
   cd Compiler-Project
   ```

---

## Running the Project

To build and run the project, use the following commands:

1. Generate the lexer:
   ```bash
   flex lexer.l
   ```

2. Generate the parser:
   ```bash
   bison -d parser.y
   ```

3. Compile the generated files:
   ```bash
   gcc -o output lex.yy.c parser.tab.c -lfl
   ```

4. Run the executable:
   ```bash
   ./output test.c
   ```

---
