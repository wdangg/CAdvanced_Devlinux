# Homework 01. Library Management System 🚀

## 1. Overview
The **Library Management System** is a simple modular C project that manages books, users, and borrowing activities through a terminal interface. It uses linked lists and dynamic memory to keep the system lightweight and easy to extend.

## 2. Features
- Manage books: add / delete / modify
- Manage users: add / delete / modify
- Borrow & return books with validations
- Console tables showing borrower names and a user's borrowed-book list 

## 3. Prerequisites
- A C compiler (GCC/Clang)
- `make` recommended for convenience (or use raw `gcc` commands)

## 4. Build & Run
- Using `make`:

```sh
make clear
make build
make run
```
or 
```sh
make all # clear build run
```
- Direct `gcc` (example):

```sh
gcc -std=c11 -O2 -g -Wall -Wextra src/main.c lib/Book/Book.c lib/User/User.c \
                lib/Borrow/Borrow.c lib/Common/Common.c Utils/Utils.c -Iinc \
                -Ilib/Book -Ilib/User -Ilib/Common -Ilib/Borrow -IUtils \
                -o out.exe -Wl,-Map=out.map
```

On Windows you can run the `gcc` command in MinGW/MSYS2 by creating a project and adding the `.c` files.

## 5. Usage
- Menus are text-driven. Pick options by entering the digit shown.
- When returning a book, the app now lists only users who have borrowed books, then lists only the selected user's borrowed books to choose from.

## 6. Notes / Coding Style
- Functions were adjusted to avoid early `return`/`break` inside (return only at function end) where requested.
- Comparisons were standardized to place constants (e.g. `NULL`, `0`) on the left side.
- Header `@brief` comments updated with concise `@param`/`@return` descriptions.
