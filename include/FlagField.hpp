#pragma once
#ifndef FLAGFIELD_HPP__
#define FLAGFIELD_HPP__
/**
 * @file include/flagfield.hpp
 * @author Ray Richter
 * @brief Declaration and definition of the FlagField class and class members.
 */

#include <cstdint>
#include <functional>
#include <stdarg.h>
#include <stdexcept>
#include <ostream>

#ifdef FLAGFIELD_DEBUG
#define FF_DEBUG_MSG(msg) std::cout << msg << std::endl
#else
#define FF_DEBUG_MSG(msg)
#endif

// #define FF_USE_HEAP

/// @brief A class to manage a field of flags.
/// @tparam numFlags The maximum number of flags managed. Default = 8.
template <size_t numFlags = 8>
class FlagField {
/// @section Constructors and Deconstructors
public:
    /// @brief Explicit constructor from a list of flags.
    template <typename... Flags>
    explicit FlagField(Flags... flags) {
        FF_DEBUG_MSG("Creating FlagField from a list of flags...");
#ifdef FF_USE_HEAP
        flags_ = new uint8_t[(numFlags + 7) / 8];
#endif
        // Initialize flags array to zero
        fill_(0);

        // Set the flag arguements
        setFlags(flags...);
    }

    /// @brief Copy constructor. 
    FlagField(const FlagField<numFlags> &other) {
        FF_DEBUG_MSG("Creating FlagField from another FlagField both with size: " << numFlags); // Debug stament
        // Copy flags from other
    #ifdef FF_USE_HEAP
        flags_ = new uint8_t[(numFlags + 7) / 8];
    #endif
        // Initialize flags array to zero
        fill_(0);
        for (size_t i = 0; i < (numFlags + 7) / 8; i++) flags_[i] = other.flags_[i];
    }

    /// @brief Default constructor.
    FlagField() {
        FF_DEBUG_MSG("Creating FlagField with default constructor with size: " << numFlags); // Debug stament
    #ifdef FF_USE_HEAP
        flags_ = new uint8_t[(numFlags + 7) / 8];
    #endif
        // Initialize flags array to zero
        fill_(0); }

    /// @brief Deconstructor.
    ~FlagField() { 
        FF_DEBUG_MSG("Deconstructing FlagField with size: " << numFlags); // Debug stament
    #ifdef FF_USE_HEAP
        delete[] flags_;
    #endif
    }

/// @section Accessors

    /// @brief Set a flag at the given index.
    void setFlag(const size_t &index) {
        if (index >= numFlags) throw std::out_of_range("Set Flag Err: Index out of range");
        FF_DEBUG_MSG("Setting flag at index: " << index); // Debug stament
        flags_[index / 8] |= (1 << (index % 8)); }
    /// @brief Set a list of flags.
    void setFlags(const size_t &flag) { setFlag(flag); }
    /// @brief Set a list of flags.
    template <typename... Flags>
    void setFlags(const size_t &flag, Flags... flags) 
    { setFlag(flag); setFlags(flags...); }
    /// @brief Clear a flag at the given index.
    void clearFlag(const size_t &index) {
        if (index >= numFlags) throw std::out_of_range("Clear Flag Err: Index out of range");
        FF_DEBUG_MSG("Clearing flag at index: " << index); // Debug stament
        flags_[index / 8] &= ~(1 << (index % 8)); }
    /// @brief Toggle a flag at the given index.
    void toggleFlag(const size_t &index) {
        if (index >= numFlags) throw std::out_of_range("Toggle Flag Err: Index out of range");
        FF_DEBUG_MSG("Toggling flag at index: " << index); // Debug stament
        flags_[index / 8] ^= (1 << (index % 8)); }
    /// @brief Query a flag at the given index.
    bool isFlagSet(const size_t &index) const {
        if (index >= numFlags) throw std::out_of_range("Is Flag Set Err: Index out of range");
        FF_DEBUG_MSG("Checking if flag is set at index: " << index); // Debug stament
        return flags_[index / 8] & (1 << (index % 8)); }
    /// @brief Gets the number of managed flags.
    constexpr size_t size() const { return numFlags; }

/// @section Binary Integer Operators

    /// @brief Clears all flags and sets the given flag.
    FlagField<numFlags>& operator= (const size_t &index) {
        fill_(0); setFlag(index); return *this; }
    /// @brief Returns `true` if only the given flag is set.
    bool operator==(const size_t &index) const {
        for (size_t i = 0; i < (size() + 7) / 8; i++) {
            if (flags_[i] != 0) { if (flags_[i] != (1 << (i % 8))) return false; }
        } return true; }
    /// @brief Returns `true` if the given flag is set.
    bool operator& (const size_t &index) const { return isFlagSet(index); }
    /// @brief Clears the given flag.
    FlagField<numFlags>& operator&=(const size_t &index) {
        clearFlag(index); return *this; }
    /// @brief Sets the given flag.
    FlagField<numFlags>& operator|=(const size_t &index) {
        setFlag(index); return *this; }
    /// @brief Flips the given flag.
    FlagField<numFlags>& operator^=(const size_t &index) {
        toggleFlag(index); return *this; }
    /// @brief Sets the given flag.
    FlagField<numFlags>& operator+=(const size_t &index) {
        setFlag(index); return *this; }
    /// @brief Clears the given flag.
    FlagField<numFlags>& operator-=(const size_t &index) {
        clearFlag(index); return *this; }

/// @section Binary Boolean Operators

    /// @brief Makes a new FlagField object with the same flags if `true` or no flags if `false`.
    FlagField<numFlags>  operator* (const bool &keep) const {
        FlagField<numFlags> ret = *this; ret *= keep; return ret; }
    /// @brief Clears all flags if `false`, keeps all flags if `true`.
    FlagField<numFlags>& operator*=(const bool &keep) {
        if (!keep) { fill_(0); } return *this; }

/// @section Binary FlagField Operators

    /// @brief Clears all flags and sets the given flags.
    FlagField<numFlags>& operator= (const FlagField<numFlags> &other) {
        for (size_t i = 0; i < (size() + 7) / 8; i++) { flags_[i] = other.flags_[i]; }
        return *this; }
    /// @brief Clears every non matching flag in the given FlagField.
    FlagField<numFlags>& operator&=(const FlagField<numFlags> &other) {
        fillOp_(other, [](uint8_t& byte, const uint8_t& other) -> uint8_t& {
            byte &= other;
            return byte;
        }); return *this; }
    /// @brief Makes a new FlagField object with matching flags.
    FlagField<numFlags>  operator& (const FlagField<numFlags> &other) const {
        FlagField<numFlags> ret = *this; ret &= other; return ret; }
    /// @brief Sets every flag in the given FlagField.
    FlagField<numFlags>& operator|=(const FlagField<numFlags> &other) {
        fillOp_(other, [](uint8_t& byte, const uint8_t& other) -> uint8_t& {
            byte |= other;
            return byte;
        }); return *this; }
    /// @brief Makes a new FlagField object with both flags.
    FlagField<numFlags>  operator| (const FlagField<numFlags> &other) const {
        FlagField<numFlags> ret = *this; ret |= other; return ret; }
    /// @brief Toggles every flag in the given FlagField.
    FlagField<numFlags>& operator^=(const FlagField<numFlags> &other) {
        fillOp_(other, [](uint8_t& byte, const uint8_t& other) -> uint8_t& {
            byte ^= other;
            return byte;
        }); return *this; }
    /// @brief Makes a new FlagField object with XOR flags.
    FlagField<numFlags>  operator^ (const FlagField<numFlags> &other) const {
        FlagField<numFlags> ret = *this; ret ^= other; return ret; }
    /// @brief Returns `true` if the same flags are set.
    bool       operator==(const FlagField<numFlags> &other) const {
        for (size_t i = 0; i < (size() + 7) / 8; i++) { if (flags_[i] != other.flags_[i]) return false; }
        return true; }
    /// @brief Returns `false` if the same flags are set.
    bool       operator!=(const FlagField<numFlags> &other) const {
        return !operator==(other); }
    /// @brief Compares the number of set flags.
    bool       operator> (const FlagField<numFlags> &other) const {
        return countSetBits_() > other.countSetBits_(); }
    /// @brief Compares the number of set flags.
    bool       operator< (const FlagField<numFlags> &other) const {
        return other.operator>(*this); }
    /// @brief Compares the number of set flags.
    bool       operator>=(const FlagField<numFlags> &other) const {
        return !operator<(other); }
    /// @brief Compares the number of set flags.
    bool       operator<=(const FlagField<numFlags> &other) const {
        return !operator>(other); }
    /// @brief Makes a new FlagField object with both flags.
    FlagField<numFlags>  operator+ (const FlagField<numFlags> &other) const {
        FlagField<numFlags> ret = *this; ret += other; return ret; }
    /// @brief Makes a new FlagField object with flags removed.
    FlagField<numFlags>  operator- (const FlagField<numFlags> &other) const {
        FlagField<numFlags> ret = *this; ret -= other; return ret; }
    /// @brief Sets the given flags.
    FlagField<numFlags>& operator+=(const FlagField<numFlags> &other) {
        fillOp_(other, [](uint8_t& byte, const uint8_t& other) -> uint8_t& {
            byte |= other;
            return byte;
        }); return *this; }
    /// @brief Clears the given flags.
    FlagField<numFlags>& operator-=(const FlagField<numFlags> &other) {
        fillOp_(other, [](uint8_t& byte, const uint8_t& other) -> uint8_t& {
            byte &= ~other;
            return byte;
        }); return *this; }

/// @section Member Access Operators

    /// @brief Returns `true` if indexed flag is set.
    bool    operator()(const size_t &index) const { return isFlagSet(index); }
    /// @brief Returns a copy of the queried flag byte.
    /// @param index The byte index to return. Must be < (size - 1) / 8.
    uint8_t operator[](const size_t &index) const {
        if (index >= (size() + 7) / 8) throw std::out_of_range("Byte retrieval error: Index out of range");
        return flags_[index]; }

/// @section Unary Prefix Operators

    /// @brief Returns `true` if no flags are set.
    bool operator!() const {
        for (size_t i = 0; i < (size() + 7) / 8; i++) { if (flags_[i] != 0) return false; }
        return true; }
    /// @brief Flips every flag.
    FlagField<numFlags>& operator~() { fillOp_([](uint8_t& byte) -> uint8_t& {
        byte = ~byte;
        return byte;
    }); return *this;}

    /// @brief Gets a pointer to this FlagField.
    FlagField<numFlags>* operator&() const { return (FlagField<numFlags>*)this; }
    /// @brief Gets a pointer to the flags array.
    uint8_t* operator*() { return flags_; }
    /// @brief Explicit cast to bool. `false` if no flags are set.
    explicit operator bool() const { return !operator!(); }

    // /// @brief TODO
    // uint8_t*   operator+()const;
    // /// @brief TODO
    // uint8_t*   operator-()const;
    // /// @brief TODO
    // operator uint8_t()const;
    
/// @section Unary Postfix Operators

    /// @brief Sets every flag.
    FlagField<numFlags>& operator++() { fill_(0xFF); return *this; }
    /// @brief Clears every flag.
    FlagField<numFlags>& operator--() { fill_(0);    return *this; }

/// @section Out Stream Operator

    /// @brief Outputs the flags to the given output stream.
    friend std::ostream& operator<<(std::ostream &os, const FlagField<numFlags> &ff) {
        os << "FlagField<" << numFlags << ">: 0b";
        for (size_t i = 0; i < numFlags; i++) { 
            if (i % 8 == 0 && i != 0) os << " ";
            os << (ff.isFlagSet(i) ? "1" : "0"); 
        }
        return os;
    }
    
/// @section Private Members
private:
#ifdef FF_USE_HEAP
    /// @brief An array of flags on the heap. 8]; 
    uint8_t* flags_ = new uint8_t[(numFlags + 7) / 8]; 
#else
    /// @brief An array of flags on the stack.
    uint8_t flags_[(numFlags + 7) / 8];
#endif
    /// @brief Fill the flag array with the given `uint8_t` value.
    void fill_(const uint8_t &fill) 
    {   for (size_t i = 0; i < (size() + 7) / 8; i++) flags_[i] = fill; }
    /// @brief Fill another flag array with the given `uint8_t` value.
    void fill_(FlagField<numFlags> &other, const uint8_t &fill) const 
    {   for (size_t i = 0; i < (size() + 7) / 8; i++) other.flags_[i] = fill; }

    /// @brief Applies the given operation to each byte in the flag array.
    /// @param rhs The right hand side of the operation.
    /// @param op The `uint8_t& op(uint8_t&, const size_t&)` operation to apply.
    void fillOp_(
        const size_t &rhs, 
        std::function<uint8_t& (uint8_t&, const size_t&)> op_
    ) { for (size_t i = 0; i < (size() + 7) / 8; i++) op_(flags_[i], rhs); }
    
    /// @brief Applies the given operation to each byte in the flag array.
    /// @param ret The return flag array for the operation.
    /// @param rhs The right hand side of the operation.
    /// @param op The `uint8_t& op(uint8_t&, const size_t&)` operation to apply.
    void fillOp_(
        FlagField<numFlags> &ret,
        const size_t &rhs, 
        std::function<uint8_t (const uint8_t&, const size_t&)> op_
    ) const { for (size_t i = 0; i < (size() + 7) / 8; i++) ret.flags_[i] = op_(flags_[i], rhs); }

    /// @brief Applies the given operation to each byte in the flag array.
    /// @param rhs The right hand side of the operation.
    /// @param op The `uint8_t& op(uint8_t&, const uint8_t&)` operation to apply.
    void fillOp_(
        const FlagField<numFlags> &rhs, 
        std::function<uint8_t& (uint8_t&, const uint8_t&)> op_
    ) { for (size_t i = 0; i < (size() + 7) / 8; i++) op_(flags_[i], rhs.flags_[i]); }

    /// @brief Applies the given operation to each byte in the flag array.
    /// @param ret The return flag array for the operation.
    /// @param rhs The right hand side of the operation.
    /// @param op The `uint8_t& op(uint8_t&, const uint8_t&)` operation to apply.
    void fillOp_(
        FlagField<numFlags> &ret,
        const FlagField<numFlags> &rhs, 
        std::function<uint8_t (const uint8_t&, const uint8_t&)> op_
    ) const { for (size_t i = 0; i < (size() + 7) / 8; i++) ret.flags_[i] = op_(flags_[i], rhs.flags_[i]); }

    /// @brief Applies the given unary operation to each byte in the flag array.
    /// @param op The `uint8_t& op(uint8_t&)` operation to apply.
    void fillOp_(std::function<uint8_t& (uint8_t&)> op_) {
        for (size_t i = 0; i < (size() + 7) / 8; i++) op_(flags_[i]); }
    
    /// @brief Counts the number of 1s in a byte.
    int countSetBits_(uint8_t byte) const {
        int count = 0;
        while (byte) count += byte & 1; byte >>= 1;
        return count; }
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