// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vdata_comparator.h for the primary calling header

#ifndef VERILATED_VDATA_COMPARATOR___024ROOT_H_
#define VERILATED_VDATA_COMPARATOR___024ROOT_H_  // guard

#include "verilated.h"


class Vdata_comparator__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vdata_comparator___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rstn,0,0);
    VL_IN8(valid_i,0,0);
    VL_OUT8(outp_o,0,0);
    VL_OUT8(valid_o,0,0);
    CData/*5:0*/ data_comparator__DOT__res_internal;
    CData/*5:0*/ data_comparator__DOT__valid_internal;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    VL_IN16(inp1_i,9,0);
    VL_IN16(inp2_i,9,0);
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vdata_comparator__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vdata_comparator___024root(Vdata_comparator__Syms* symsp, const char* namep);
    ~Vdata_comparator___024root();
    VL_UNCOPYABLE(Vdata_comparator___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
