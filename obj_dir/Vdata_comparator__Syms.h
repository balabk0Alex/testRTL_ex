// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VDATA_COMPARATOR__SYMS_H_
#define VERILATED_VDATA_COMPARATOR__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vdata_comparator.h"

// INCLUDE MODULE CLASSES
#include "Vdata_comparator___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vdata_comparator__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vdata_comparator* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vdata_comparator___024root     TOP;

    // CONSTRUCTORS
    Vdata_comparator__Syms(VerilatedContext* contextp, const char* namep, Vdata_comparator* modelp);
    ~Vdata_comparator__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
