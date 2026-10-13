# C++ Modules 05–09

[![CI](https://github.com/man-Yocto/cpp-modules-05-09/actions/workflows/ci.yml/badge.svg)](https://github.com/man-Yocto/cpp-modules-05-09/actions/workflows/ci.yml)

The second half of the 42 C++ curriculum: exceptions, casts, templates, and the STL — ending with
three small real-world programs. Everything is written in **C++98** and compiled with
`-Wall -Wextra -Werror -std=c++98`.

## Modules

| Module | Topic | Exercises |
|---|---|---|
| **cpp05** | Exceptions | `Bureaucrat` with grade-range exceptions · `Form` signing · abstract `AForm` with `ShrubberyCreationForm`, `RobotomyRequestForm`, `PresidentialPardonForm` · `Intern` (form factory) |
| **cpp06** | C++ casts | `ScalarConverter` (char/int/float/double literal detection and conversion, `static_cast`) · `Serializer` (`reinterpret_cast` pointer ↔ `uintptr_t`) · `identify` (runtime type identification with `dynamic_cast`) |
| **cpp07** | Templates | `swap`/`min`/`max` function templates · `iter` (apply a function to any array) · `Array<T>` class template with bounds-checked `operator[]` |
| **cpp08** | Templated containers, iterators, algorithms | `easyfind` (search any STL container) · `Span` (shortest/longest span over thousands of numbers) · `MutantStack` (an iterable `std::stack`) |
| **cpp09** | STL in practice | **`btc`** — Bitcoin exchange: looks up historical rates from a CSV database (`std::map`) and validates every input line · **`RPN`** — Reverse Polish Notation calculator (`std::stack`) · **`PmergeMe`** — Ford–Johnson merge-insertion sort implemented on two containers (`std::vector`, `std::list`) with timing comparison |

## Build & run

Each exercise is self-contained with its own `Makefile`:

```bash
cd cpp09/ex01
make
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"

cd ../ex02
make
./PmergeMe 3 5 9 7 4
```

## Key technical challenges

- **Exception-safe design** — custom exception classes derived from `std::exception`, thrown and
  caught across class hierarchies.
- **Choosing the right cast** — `static_cast`, `reinterpret_cast` and `dynamic_cast`, and when each
  one is correct.
- **Generic code** — writing templates that work with any type or container and keep compile errors
  readable.
- **Ford–Johnson (merge-insertion) sort** — pairing elements, recursively sorting the larger ones,
  and binary-inserting the rest — implemented twice, on a random-access container and a linked
  list, to compare their performance.
- **Robust input parsing** — dates, numbers and malformed lines in the Bitcoin exchange.

## What I learned

<!-- TODO: write this section yourself -->
