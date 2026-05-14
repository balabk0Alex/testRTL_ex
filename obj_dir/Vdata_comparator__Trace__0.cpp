// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vdata_comparator__Syms.h"


void Vdata_comparator___024root__trace_chg_0_sub_0(Vdata_comparator___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vdata_comparator___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root__trace_chg_0\n"); );
    // Body
    Vdata_comparator___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vdata_comparator___024root*>(voidSelf);
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vdata_comparator___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vdata_comparator___024root__trace_chg_0_sub_0(Vdata_comparator___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root__trace_chg_0_sub_0\n"); );
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 0);
    bufp->chgBit(oldp+0,(vlSelfRef.clk));
    bufp->chgBit(oldp+1,(vlSelfRef.rstn));
    bufp->chgSData(oldp+2,(vlSelfRef.inp1_i),10);
    bufp->chgSData(oldp+3,(vlSelfRef.inp2_i),10);
    bufp->chgBit(oldp+4,(vlSelfRef.valid_i));
    bufp->chgBit(oldp+5,(vlSelfRef.outp_o));
    bufp->chgBit(oldp+6,(vlSelfRef.valid_o));
    bufp->chgCData(oldp+7,(vlSelfRef.data_comparator__DOT__res_internal),6);
    bufp->chgCData(oldp+8,(vlSelfRef.data_comparator__DOT__valid_internal),6);
}

void Vdata_comparator___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root__trace_cleanup\n"); );
    // Locals
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    Vdata_comparator___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vdata_comparator___024root*>(voidSelf);
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
