// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdata_comparator.h for the primary calling header

#include "Vdata_comparator__pch.h"

void Vdata_comparator___024root___ctor_var_reset(Vdata_comparator___024root* vlSelf);

Vdata_comparator___024root::Vdata_comparator___024root(Vdata_comparator__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vdata_comparator___024root___ctor_var_reset(this);
}

void Vdata_comparator___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vdata_comparator___024root::~Vdata_comparator___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
