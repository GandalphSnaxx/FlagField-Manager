# FlagField Library

## Overview
The FlagField Library is a header only C++ library designed to manage a bytefield of flags. It provides a simple and efficient way to set, clear, toggle, and check flags within a byte or a number of bytes, making it useful for applications that require bit manipulation. Operator overloads are also provided for faster and easier implementation.

## Features
- Manage a bytefield of flags with a single byte or multiple bytes.
- Templates for setting the number of managed flags and ensuring type safety:
  - `FlagField`: Default constructor that manages 8 flags.
  - `FlagField<x>`: `x` is the number of flags to manage. Default `x` is 8.
  - `FlagField<ENUM_MAX, enum>`: Constructs a FlagField in reference to an enum that contains flag indices.
- Constructors:
  - `FlagField()`: Default constructor initalizes every flag to 0.
  - `FlagField(1, 2, 3...)`: Constructs a `FlagField` with pre set flags at the given indices.
  - `FlagField(other)`: Constructs a `FlagField` as a copy of another `FlagField`.
- Public methods to manipulate flags:
  - `set()`: Sets every flag.
  - `set(index)`: Sets a flag at the given index.
  - `set(other)`: Sets flags from another FlagField of the same type and size.
  - `set(i1, i2, i3...)`: Sets flags at each index.
  - `clear()`: Clears every flag.
  - `clear(index)`: Clears a flag at the given index.
  - `clear(other)`: Clears flags from another FlagField of the same type and size.
  - `clear(i1, i2, i3...)`: Clears flags at each index.
  - `toggle()`: Flips every flag.
  - `toggle(index)`: Flips a flag at the given index.
  - `toggle(other)`: Flips set flags from another FlagField of the same type and size.
  - `toggle(i1, i2, i3...)`: Flips flags at each index.
  - `isSet()`: Returns `true` if every flag is set.
  - `isSet(index)`: Returns `true` if the flag at the given index is set.
  - `isSet(other)`: Returns `true` if every set flag in the other FlagField is set.
  - `isSet(i1, i2, i3...)`: Returns `true` if every flag at the given indices is set.
  - `isNSet()`: Returns `true` if every flag is not set.
  - `isNSet(index)`: Returns `true` if the flag at the given index is not set.
  - `isNSet(other)`: Returns `true` if every set flag in the other FlagField is not set.
  - `isNSet(i1, i2, i3...)`: Returns `true` if every flag at the given indices is not set.
  - `size()`: Returns the number of managed flags.
  - `sizeBytes()`: Returns the number of managed bytes.
  - `name()`: Gets the name of the referenced type.
  - `numSetFlags()`: Returns the number of set flags.
- Operator overloads for faster implementation in your project.
  - Unary Operators:
  
| OP | Usage | Description |
| :---: | :--- | :--- |
| ! | ```!ff``` | Returns `true` if no flags are set |
| & | ```&ff``` | Not changed - Gets a pointer to the `ff` |
| * | ```*ff``` | Returns the address of the byte array |
| + | ```+ff``` | Sets every flag |
| ++ | ```++ff``` | Sets the first unset flag |
| ++ | ```ff++``` | Sets the first unset flag |
| - | ```-ff``` | Clears every flag |
| -- | ```--ff``` | Clears the first set flag |
| -- | ```ff--``` | Clears the first set flag |
| ~ | ```~ff``` | Toggles every flag |

  - Binary Integer or Enum Operators (`index` is either an integer value or an enum value):

| OP | Usage | Description |
| :---: | :--- | :--- |
| = | ```ff = index``` | Clears `ff` then sets the flag at `index` |
| , | ```ff, index``` | Sets the flag at `index` |
| == | ```ff == index``` | Returns `true` if the flag at `index` is set |
| != | ```ff != index``` | Returns `true` if the flag at `index` is not set |
| && | ```ff && index``` | Returns `true` if the flag at the given index is set |
| &= | ```ff &= index``` | Clears the flag at `index` |
| & | ```ff & index``` | Returns a new FlagField `ff &= index` |
| \|\| | ```ff \|\| index``` | Returns `true` if the flag at `index` is set |
| \|= | ```ff \|= index``` | Clears `ff` then sets the flag at `index` if it was set |
| \| | ```ff \| index``` | Returns a new FlagField `ff \|= index` |
| ( ) | ```ff(i1, i2, i3...)``` | Returns `true` if every flag at the given indices are set |
| [ ] | ```ff[index]``` | Returns `index` if the flag at `index` is set |
| += | ```ff += index``` | Sets the flag at `index` |
| + | ```ff + index``` | Returns a new FlagField `ff += index` |
| -= | ```ff -= index``` | Clears the flag at `index` |
| - | ```ff - index``` | Returns a new FlagField `ff -= index` |
| ^= | ```ff ^= index``` | Toggles the flag at `index` |
| ^ | ```ff ^ index``` | Returns a new FlagField `ff ^= index` |

  - Binary FlagField Operators:

| OP | Usage | Description |
| :---: | :--- | :--- |
| = | ```ff1 = ff2``` | Makes `ff1` identical to `ff2` |
| , | ```ff1, ff2``` | Sets `ff2`'s flags in `ff1` |
| == | ```ff1 == ff2``` | Returns `true` if every flag matches |
| != | ```ff1 != ff2``` | Returns `true` if every set flag in the other FlagField is not set |
| < | ```ff1 < ff2``` | Compares the number of set flags |
| > | ```ff1 < ff2``` | Compares the number of set flags |
| <= | ```ff1 < ff2``` | Compares the number of set flags |
| >= | ```ff1 < ff2``` | Compares the number of set flags |
| && | ```ff1 && ff2``` | Returns `true` if every set flag in `ff2` is set in `ff1` |
| &= | ```ff1 &= ff2``` | Performs bitwise `AND` for every flag |
| & | ```ff1 & ff2``` | Returns a new FlagField `ff1 &= ff2` |
| \|\| | ```ff1 \|\| ff2``` | Returns `true` if any set flag index matches |
| \|= | ```ff1 \|= ff2``` | Sets only matching flags |
| \| | ```ff1 \| ff2``` | Returns a new FlagField `ff1 \|= ff2` |
| ( ) | ```ff1(ff2)``` | Returns `true` if every set flag in `ff2` is set in `ff1` |
| += | ```ff1 += ff2``` | Sets `ff1`'s flags set in `ff2` |
| + | ```ff1 + ff2``` | Returns a new FlagField `ff1 += ff2` |
| -= | ```ff1 -= ff2``` | Clears `ff1`'s flags set in `ff2` |
| - | ```ff1 - ff2``` | Returns a new FlagField `ff1 -= ff2` |
| ^= | ```ff1 ^= ff2``` | Toggles `ff1`'s flags set in `ff2` |
| ^ | ```ff1 ^ ff2``` | Returns a new FlagField `ff1 ^= ff2` |

  - Other operators:

| OP | Usage | Description |
| :---: | :--- | :--- |
| <<= | ```ff <<= bytefield` | Sets this FlagField from a bytefield (either a single byte or a ```std::array```) |
| *= | ```ff *= bool``` | Clears the FlagField if `false` |
| * | ```ff * bool``` | Returns a new FlagField `ff *= bool` |
| << | ```std::cout << ff``` | Adds `"FlagField<size(), name()>: [...]"` to an out stream where ... is `.` for unset flags and `\|` for set flags |

- Defines can be set for validation and/or debugging:
  - `FLAGFIELD_NO_VALIDATE`: Define for disabling index validation.
  - `FLAGFIELD_DEBUG`: Define for enabling print statements whenever a function or operator is used.
- Easy integration with existing C++ projects.

## Installation
To use the ByteField Library, you copy FlagField.hpp into your project.

## Testing

1. Clone the repository:
   ```
   git clone https://github.com/GandalphSnaxx/FlagField-Manager.git
   ```

2. Navigate to the project directory:
   ```
   cd the/file/you/specified
   ```

3. Run the config and compile script:
   ```
   .\config_and_compile.bat
   ```

4. Run the generated executable:
   ```
   .\tests\Debug\FlagField_Tests.exe
   ```

## Usage
To use the FlagField class in your project, include the header file and create an instance of the class. Here is a simple example:

```cpp
// #define FLAGFIELD_DEBUG // Enables print statements for debugging
// #define FLAGFIELD_NO_VALIDATE // Saves a small amount of time
#include <FlagField.hpp>

typedef enum Flags {
   FLAG_A,
   FLAG_B,
   FLAG_C,
   FLAG_D,
   FLAG_MAX
} Flags;

int main() {
   FlagField<FLAG_MAX, Flags> ff;

   ff += FLAG_A;
   ff += FLAG_C;

   if (ff(FLAG_A, FLAG_B)) { /* do something */ }

   -ff;

   bool setIf = true;
   ff += FLAG_A * setIf;

   return 0;
}
```

## Testing
Unit tests for the ByteField class are provided in the `tests` directory. 

## License
This project is licensed under the MIT License. See the LICENSE file for more details.