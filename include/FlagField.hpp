/**
 * @file FlagField.hpp
 * @author Ray Richter
 * @brief Declaration and definition of the FlagField class and class members.
 * @details Operator reference table:
 * LHS type  | OP | RHS type  | RET type  | Description
 * ----------|----|-----------|-----------|-------------
 * Unary Operators
 * OP   | Name                      | Description
 * -----|---------------------------|--------
 * !	| Logical NOT	            | Returns `true` if no flags are set
 * &	| Address-of	            | Not changed
 * ( )	| Cast Operator	            | Casts a byte to a FlagField
 * *	| Pointer dereference	    | Returns the address of the byte arrat
 * +	| Unary Plus prefix	        | Sets every flag
 * +	| Unary Plus postfix	    | ?
 * ++	| Increment 1 prefix	    | Sets the first unset flag
 * ++	| Increment 1 postfix	    | Makes a new FlagField
 * -	| Unary negation prefix	    | Clears every flag
 * -	| Unary negation postfix	| ?
 * --	| Decrement 1 prefix	    | Clears the first set flag
 * --	| Decrement 1 postfix	    | Makes a new FlagField
 * ~	| One's complement	        | Toggles every flag
 * 
 * Binary Operators
 * OP   | Name                      | Description
 * -----|---------------------------|--------
 * ,	| Comma	                    | Combines flags
 * !=	| Inequality	            | Returns `true` if the flag(s) are not set
 * %	| Modulus	                | ?
 * %=	| Modulus assignment	    | ?
 * &    | Bitwise AND	            | Makes a new FlagField with matching flags
 * &&	| Logical AND	            | Returns `true` if matching flags are set
 * &=	| Bitwise AND assignment    | Sets flags
 * ( )	| Function call	            | Returns `true` if every flag is set
 * *	| Multiplication	        | Bool: Creates a new FlagField b ? same : empty
 *      |                           | uint: ? Makes a scaled FlagField ?
 * *=	| Multiplication assignment	| Bool: Clears the FlagField if `false`
 * +	| Addition	                | Makes a new FlagField with matching flags
 * +=	| Addition assignment	    | Sets flags
 * -	| Subtraction	            | Makes a new flagfield without matching flags
 * -=	| Subtraction assignment	| Clears flags
 * ->	| Member selection	        | ? isSet ?
 * ->*	| Pointer-to-member sel	    | ?
 * /	| Division	                | ?
 * /=	| Division assignment	    | ?
 * <	| Less than	                | Compares number of set flags
 * <<	| Left shift	            | ?
 * <<=	| Left shift assignment	    | ?
 * <=	| Less than or equal to	    | Compares number of set flags
 * =	| Assignment	            | Clear then set
 * ==	| Equality	                | uint: Returns `true` if flag is set
 *      |                           | FlagField: Returns `true` if all flags match
 * >	| Greater than	            | Compares number of set flags
 * >=	| Greater than or equal to	| Compares number of set flags
 * >>	| Right shift	            | ?
 * >>=	| Right shift assignment	| ?
 * [ ]	| Array subscript	        | Binary flag check
 * ^	| Exclusive OR	            | Makes a new FlagField with toggled flags
 * ^=	| Exclusive OR assignment	| Toggles flags
 * |	| Bitwise inclusive OR	    | Makes a new FlagField with OR flags
 * ||	| Logical OR	            | Returns `true` if any flag is matching
 * |=	| Bitwise inclusive OR ass	| Combines flags
 */
#pragma once
#ifndef FLAGFIELD_HPP
#define FLAGFIELD_HPP

// #define FLAGFIELD_DEBUG
// #define FLAGFIELD_NO_VALIDATE

#include <cstdint>
#include <stdarg.h>
#include <stdexcept>
#include <ostream>

#ifndef FLAGFIELD_DEBUG
#define FF_DEBUG(msg)
#else
#define FF_DEBUG(msg) std::cout << "[FlagField]: " << msg << std::endl
#endif

#ifdef FLAGFIELD_NO_VALIDATE
#define FF_VD(idx)                              \
if (idx >= MAX) { return false; }
#else
#define FF_VD(idx)                              \
if (idx >= MAX) { throw std::out_of_range(      \
    "[FlagField] - ERROR: Index out of range!"  \
    return false;                               \
); }
#endif

/// @brief A class to manage a field of flags.
/// @note FlagFields can be created in reference to enums that define flag indices.
/// @note Example usage: 
/// ```
/// typedef enum Flags {
///     A, B, C, D, E, F, G, H, MAX
/// } Flags;
/// 
/// FlagField<MAX, Flags> example_ff;
///
/// example_ff += B; // Sets flag B
///
/// if (example_ff(B, C)) {} // Checks if flags B and C are set
/// ```
/// @tparam MAX The maximum number of flags to manage. Default = `8`.
/// @tparam E The enum to set as a reference. Default = `size_t`.
template <size_t MAX = 8, class E = size_t>
class FlagField {
    static_assert(std::is_enum<E>::value || std::is_integral<E>::value,
        "[FlagField] - ERROR: FlagField must use an enum or integral type!");
    static_assert(MAX > 0, "[FlagField] - ERROR: Number of managed flags must be > 0!");
public:
/// @section Constructors and Deconstructors
    /// @brief Explicit constructor from a list of flags.
    template <typename... Flags>
    explicit FlagField(Flags... flags) {
        FF_DEBUG("Creating FlagField from a list of flags with size: " << size());
        // Initialize flags array to zero
        clear();
        // Set the flag arguements
        set(flags...);
    }

    /// @brief Copy constructor. 
    FlagField(const FlagField<MAX, E> &other) {
        FF_DEBUG("Creating FlagField from another FlagField both with size: " << size());
        // Initialize flags array to zero
        clear();
        set(other);
    }

    /// @brief Default constructor.
    FlagField() {
        FF_DEBUG("Creating FlagField with default constructor and size: " << size());
        // Initialize flags array to zero
        clear(); 
    }

    /// @brief Deconstructor.
    ~FlagField() { 
        FF_DEBUG("Deconstructing FlagField with size: " << size());
    }

/// @section Accessors

/// @subsection Set Functions

    /// @brief Sets every flag.
    void set() {
        FF_DEBUG("Setting every flag.");
        for (size_t i = 0; i < sizeBytes(); i++) {
            flags_[i] = 0xFF;
        }
    }

    /// @brief Set a flag at the given index.
    void set(const E& index) {
        FF_VD(index);
        FF_DEBUG("Set flag at index: " << index);
        flags_[index / 8] |= (1 << (index % 8));
    }

    /// @brief Sets flags from another FlagField.
    void set(const FLagField& other) {
        FF_DEBUG("Set flags from another FlagField.");
        for (size_t i = 0; i < sizeBytes(); i++) {
            flags_[i] |= other.flags_[i];
        }
    }

    /// @brief Sets a list of flags at the given indices.
    template <typename... O> void set(const E& index, const O&... indices) {
        set(index); set(indices...);
    }

/// @subsection Clear Functions

    /// @brief Clears every flag.
    void clear() {
        FF_DEBUG("Clearing every flag.");
        for (size_t i = 0; i < sizeBytes(); i++) {
            flags_[i] = 0;
        }
    }

    /// @brief Clears a flag at the given index.
    void clear(const E& index) {
        FF_VD(index);
        FF_DEBUG("Cleared flag at index: " << index);
        flags_[index / 8] &= ~(1 << (index % 8));
    }

    /// @brief Clears flags from another FlagField.
    void clear(const FlagField& other) {
        FF_DEBUG("Clearing flags from another FlagField.");
        for (size_t i = 0; i < sizeBytes(); i++) {
            flags_[i] &= ~other.flags_[i];
        }
    }

    /// @brief Clears flags from a list of flag indices.
    template <typename... O> void clear(const E& index, const O&... indices) {
        clear(index); clear(indices...);
    }

/// @subsection Toggle Functions

    /// @brief Toggles every flag.
    void toggle() {
        FF_DEBUG("Toggling every flag.");
        for (size_t i = 0; i < sizeBytes(); i++) {
            flags_[i] ^= 0xFF;
        }
    }

    /// @brief Toggles a flag at the given index.
    void toggle(const E& index) {
        FF_VD(index);
        FF_DEBUG("Toggled flag at index: " << index);
        flags_[index / 8] ^= (1 << (index % 8));
    }

    /// @brief Toggles flags from another FlagField.
    void toggle(const FlagField& other) {
        FF_DEBUG("Clearing flags from another FlagField.");
        for (size_t i = 0; i < sizeBytes(); i++) {
            flags_[i] ^= other.flags_[i];
        }
    }

    /// @brief Toggles flags from a list of flag indices.
    template <typename... O> void toggle(const E& index, const O&... indices) {
        toggle(index); toggle(indices...);
    }

/// @subsection Query Functions

    /// @brief Returns `true` if every flag is set.
    bool isSet() {
        constexpr uint8_t mask = (1 << size() % 8) - 1;
        for (size_t i = 0; i < sizeBytes() - 1; i++) {
            if (flags_[i] != 0xFF) return false;
        }
        if (flags_[sizeBytes() - 1] & mask != mask) return false;
        return true;
    }

    /// @brief Returns `true` if the flag at the given index is set.
    bool isSet(const E& index) {
        FF_VD(index);
        FF_DEBUG("Checking if flag at index " << index << " is set.");
        return flags_[index / 8] & (1 << (index % 8));
    }

    /// @brief Returns `true` if the other FlagField's flags are set in this FlagField.
    bool isSet(const FlagField& other) {
        constexpr uint8_t mask = (1 << size() % 8) - 1;
        // Check that every byte except the last matches
        for (size_t i = 0; i < sizeBytes() - 1; i++) {
            if (flags_[i] != other.flags_[i]) return false;
        }
        // Check the last byte after masking out the unmanaged flags
        if ((flags_[sizeBytes() - 1]        & lastMask) != 
            (other.flags_[sizeBytes() - 1]  & lastMask)) return false;
        return true;
    }

    /// @brief Returns `true` if every flag at every index is set.
    template <typename... O> bool isSet(const E& index, const O&... indices) {
        return isSet(index) && isSet(indices...);
    }

/// @subsection FlagField State Functions

    /// @brief Gets the number of managed flags.
    constexpr size_t size() const { return MAX; }

    /// @brief Gets the number of bytes managed.w
    constexpr size_t sizeBytes() const { return (MAX + 7) / 8; }

    constexpr const char* name() const { return typeid(E).name(); }

    /// @brief Counts the number of set flags.
    size_t numSetFlags() const {
        size_t count = 0;
        for (size_t i = 0; i < sizeBytes(); i++) { count += countBits_(flags_[i]); }
        return count;
    }

/// @section Operator Overloads

/// @subsection Unary Operators

    /// @brief Returns `true` if no flags are set.
    bool operator!() const { return !this->isSet(); }

    /// @brief Returns a pointer to the flag byte array.
    uint8_t* operator*() const { return &flags_; }

    /// @brief Sets every flag.
    FlagField& operator+() { set(); return *this; }

    /// @brief Sets the first unset flag.
    FlagField& operator++() { 
        size_t idx = 0;
        while(idx < size()) {
            // If flag is not set, set it and return
            if (!this->isSet(idx)) { 
                this->set(idx); 
                return *this; 
            }
            idx++;
        }
        // Every flag is set
        return *this;
    }

    /// @brief Makes a new FlagField copy with the first unset flag set.
    FlagField operator++(int) {
        FlagField x = *this;
        x++;
        return x;
    }

    /// @brief Clears every flag.
    FlagField& operator-() { clear(); return *this; }

    /// @brief Clears the first set flag.
    FlagField& operator--() {
        size_t idx = 0;
        while(idx < size()) {
            // If flag is set, clear it and return
            if (this->isSet(idx)) { 
                this->clear(idx); 
                return *this; 
            }
            idx++;
        }
        // Every flag is set
        return *this;
    }

    /// @brief Makes a new FlagField copy with the first set flag cleared.
    FlagField operator--(int) {
        FlagField x = *this;
        x--;
        return x;
    }

    /// @brief Toggles every flag.
    FlagField& operator~() { this->toggle(); return *this; }

/// @subsection Binary Operators

    /// @brief Sets flags at the given indices.
    FlagField& operator,(const E& idx) { this->set(idx); return *this; }
    /// @brief Sets flags at the given indices.
    FlagField& operator,(const FlagField& idx) { this->set(idx); return *this; }

/// @subsubsection Comparison Operator Functions

    /// @brief Returns `true` if the indexed flag is set.
    bool operator==(const E& idx) const { return this->isSet(idx); }
    /// @brief Returns `true` if every flag matches.
    bool operator==(const FlagField& other) const { return this->isSet(other); }

    /// @brief Returns `true` if the flag at the given index is not set.
    bool operator!=(const E& idx) const { return !this->isSet(idx); }
    /// @brief Returns `true` if the flag at the given index is not set.
    bool operator!=(const FlagField& other) const { return !this->isSet(other); }

    bool operator< (const FlagField& other) const { return this->numSetFlags() <  other.numSetFlags(); }
    bool operator<=(const FlagField& other) const { return this->numSetFlags() <= other.numSetFlags(); }
    bool operator> (const FlagField& other) const { return this->numSetFlags() >  other.numSetFlags(); }
    bool operator>=(const FlagField& other) const { return this->numSetFlags() >= other.numSetFlags(); }

/// @subsubsection AND Operator Functions

    /// @brief Returns `true` if matching flags are set.
    bool operator&&(const E& idx) const { return this->isSet(idx); }
    /// @brief Returns `true` if matching flags are set.
    bool operator&&(const FlagField& other) const { return this->isSet(other); }

    /// @brief Sets matching flags.
    FlagField& operator&=(const E& idx) {
        FF_VD(idx); FF_DEBUG("Bitwise AND at index: " << idx);
        bool keep = this->isSet(idx);
        this->clear();
        if (keep) { this->set(idx); }
        return *this;
    }
    /// @brief Sets matching flags.
    FlagField& operator&=(const FlagField& other) {
        FF_VD(idx); FF_DEBUG("Bitwise FlagField AND");
        for (size_t i = 0; i < sizeBytes(); i++) {
            flags_[i] &= other.flags_[i];
        }
        return *this;
    }

    /// @brief Makes a new FlagField with matching flags.
    FlagField operator&(const E& idx) const {
        FlagField x(this);
        x &= idx;
        return x;
    }
    /// @brief Makes a new FlagField with matching flags.
    FlagField operator&(const FlagField& other) const {
        FlagField x(this);
        x &= other;
        return x;
    }

/// @subsubsection OR Operator Functions

    /// @brief Returns `true` if any flag matches.
    bool operator||(const E& idx) const { return this->isSet(idx); }
    /// @brief Returns `true` if any flag matches.
    bool operator||(const FlagField& idx) const { 
        constexpr uint8_t mask = (1 << size() % 8) - 1;
        for (size_t i = 0; i < sizeBytes() - 1; i++) {
            if (flags_[i] & other.flags_[i] != 0) return true;
        }
        if (flags_[i] & other.flags_[i] & mask != 0) return true;
        return false; 
    }

    /// @brief Sets combined flags.
    FlagField& operator|=(const E& idx) {
        FF_VD(idx); FF_DEBUG("Bitwise OR at index: " << idx);
        this->set(idx);
        return *this;
    }
    /// @brief Sets combined flags.
    FlagField& operator|=(const FlagField& other) {
        FF_VD(idx); FF_DEBUG("Bitwise FlagField OR");
        for (size_t i = 0; i < sizeBytes(); i++) {
            flags_[i] |= other.flags_[i];
        }
        return *this;
    }

    /// @brief Makes a new FlagField with combined flags.
    FlagField operator|(const E& idx) const {
        FlagField x(this);
        x |= idx;
        return x;
    }
    /// @brief Makes a new FlagField with combined flags.
    FlagField operator|(const FlagField& other) const {
        FlagField x(this);
        x |= other;
        return x;
    }

/// @subsubsection Assignment Operators

    /// @brief Sets only the flag at the given index.
    FlagField& operator=(const E& idx) {
        this->clear();
        this->set(idx);
        return *this;
    }
    /// @brief Sets the flags from another FlagField.
    FlagField& operator=(const FlagField& other) {
        if (this != &other) {
            this->clear();
            this->set(other);
        }
        return *this;
    }

/// @subsubsection Access Operators

    /// @brief Returns `true` if every flag is set.
    bool operator()(const E& idx) const { return this->isSet(idx); }
    /// @brief Returns `true` if every flag is set.
    bool operator()(const FlagField& other) const { return this->isSet(other); }
    /// @brief Returns `true` if every flag is set.
    template <typename... Fs> bool operator()(const Fs&... idxs) const { return this->isSet(idxs...); }

    /// @brief Returns `index` if the indexed flag is set.
    E operator[](const E& idx) const { return this->isSet(idx) * idx; }

/// @subsubsection Arithmatic Operators

    /// @brief Sets the flag at the given index.
    FlagField& operator+=(const E& idx) {
        this->set(idx); return *this;
    }
    /// @brief Sets the flag at the given index.
    FlagField& operator+=(const FlagField& idx) {
        this->set(idx); return *this;
    }
    /// @brief Sets the flag at the given index.
    FlagField operator+(const E& idx) const {
        FlagField x(this);
        x.set(idx);
        return x;
    }
    /// @brief Sets the flag at the given index.
    FlagField operator+(const FlagField& idx) const {
        FlagField x(this);
        x.set(idx);
        return x;
    }

    /// @brief Clears the flag at the given index.
    FlagField& operator-=(const E& idx) {
        this->clear(idx); return *this;
    }
    /// @brief Clears the flag at the given index.
    FlagField& operator-=(const FlagField& idx) {
        this->clear(idx); return *this;
    }
    /// @brief Clears the flag at the given index.
    FlagField operator-(const E& idx) const {
        FlagField x(this);
        x.clear(idx);
        return x;
    }
    /// @brief Clears the flag at the given index.
    FlagField operator-(const FlagField& idx) const {
        FlagField x(this);
        x.clear(idx);
        return x;
    }

    /// @brief Clears every flag if false.
    FlagField& operator*=(const bool& b) {
        if (!b) this->clear();
        return *this;
    }
    /// @brief Creates a new empty (if `false`) or identical (if `true`) FlagField.
    FlagField operator*(const bool& b) const {
        FlagField x;
        if (b) x.set(this);
        return x;
    }

    /// @brief Toggles the flag at the given index.
    FlagField& operator^=(const E& idx) {
        this->toggle(idx);
        return *this;
    }
    /// @brief Toggles the flags at the given indices.
    FlagField& operator^=(const FlagField& idx) {
        this->toggle(idx);
        return *this;
    }
    /// @brief Toggles the flag at the given index.
    FlagField operator^(const E& idx) const {
        FlagField x(this);
        x.toggle(idx);
        return x;
    }
    /// @brief Toggles the flag at the given index.
    FlagField operator^(const FlagField& idx) const {
        FlagField x(this);
        x.toggle(idx);
        return x;
    }

/// @subsection Out Stream Operator Overloads

    std::ostream& operator<<(std::ostream& os, const FlagField& ff) {
        os << "FlagField<" << ff.name() << ", " << ff.size() << ">: [";
        for (size_t i = 0; i < size(); i++) {
            if ((i % 4 == 0) && (i != 0) && (i != ff.size() - 1)) os << " ";
            os << ff.isSet(i) ? "." : "|";
        }
        return os << "]";
    }
    
/// @section Private Members
private:
    /// @brief An array of flags on the stack.
    uint8_t flags_[sizeBytes()];

    /// @brief Counts the number of 1s in a byte.
    int countBits_(uint8_t byte) const {
        int count = 0;
        while (byte) { count += byte & 1; byte >>= 1; }
        return count;
    }
};

// /// @section FlagField Related Functions

// template <size_t numFlags = 8>
// std::ostream& operator<<(std::ostream &os, const FlagField<numFlags> &ff) {
//     os << "FlagField<" << numFlags << ">: 0b";
//     for (size_t i = 0; i < numFlags; i++) { 
//         if (i % 8 == 0 && i != 0) os << " ";
//         os << (ff.isFlagSet(i) ? "1" : "0"); 
//     }
//     return os;
// }

#endif // FLAGFIELD_HPP