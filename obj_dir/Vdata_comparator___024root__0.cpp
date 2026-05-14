// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdata_comparator.h for the primary calling header

#include "Vdata_comparator__pch.h"

void Vdata_comparator___024root___eval_triggers_vec__act(Vdata_comparator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___eval_triggers_vec__act\n"); );
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((IData)(vlSelfRef.clk) 
                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

bool Vdata_comparator___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vdata_comparator___024root___nba_sequent__TOP__0(Vdata_comparator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___nba_sequent__TOP__0\n"); );
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*5:0*/ __Vdly__data_comparator__DOT__res_internal;
    __Vdly__data_comparator__DOT__res_internal = 0;
    CData/*5:0*/ __Vdly__data_comparator__DOT__valid_internal;
    __Vdly__data_comparator__DOT__valid_internal = 0;
    // Body
    __Vdly__data_comparator__DOT__valid_internal = vlSelfRef.data_comparator__DOT__valid_internal;
    __Vdly__data_comparator__DOT__res_internal = vlSelfRef.data_comparator__DOT__res_internal;
    if (vlSelfRef.rstn) {
        if (vlSelfRef.valid_i) {
            __Vdly__data_comparator__DOT__valid_internal 
                = (1U | (IData)(__Vdly__data_comparator__DOT__valid_internal));
            __Vdly__data_comparator__DOT__res_internal 
                = ((0x3eU & (IData)(__Vdly__data_comparator__DOT__res_internal)) 
                   | ((IData)(vlSelfRef.inp1_i) == (IData)(vlSelfRef.inp2_i)));
        }
        __Vdly__data_comparator__DOT__valid_internal 
            = ((1U & (IData)(__Vdly__data_comparator__DOT__valid_internal)) 
               | (0x0000003eU & ((IData)(vlSelfRef.data_comparator__DOT__valid_internal) 
                                 << 1U)));
        __Vdly__data_comparator__DOT__res_internal 
            = ((1U & (IData)(__Vdly__data_comparator__DOT__res_internal)) 
               | (0x0000003eU & ((IData)(vlSelfRef.data_comparator__DOT__res_internal) 
                                 << 1U)));
    } else {
        __Vdly__data_comparator__DOT__valid_internal = 0U;
        __Vdly__data_comparator__DOT__res_internal = 0U;
    }
    vlSelfRef.data_comparator__DOT__valid_internal 
        = __Vdly__data_comparator__DOT__valid_internal;
    vlSelfRef.data_comparator__DOT__res_internal = __Vdly__data_comparator__DOT__res_internal;
    vlSelfRef.valid_o = (1U & ((IData)(vlSelfRef.data_comparator__DOT__valid_internal) 
                               >> 5U));
    vlSelfRef.outp_o = (1U & ((IData)(vlSelfRef.data_comparator__DOT__res_internal) 
                              >> 5U));
}

void Vdata_comparator___024root___eval_nba(Vdata_comparator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___eval_nba\n"); );
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vdata_comparator___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vdata_comparator___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdata_comparator___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vdata_comparator___024root___eval_phase__act(Vdata_comparator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___eval_phase__act\n"); );
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vdata_comparator___024root___eval_triggers_vec__act(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vdata_comparator___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vdata_comparator___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vdata_comparator___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vdata_comparator___024root___eval_phase__nba(Vdata_comparator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___eval_phase__nba\n"); );
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vdata_comparator___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vdata_comparator___024root___eval_nba(vlSelf);
        Vdata_comparator___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vdata_comparator___024root___eval(Vdata_comparator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___eval\n"); );
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vdata_comparator___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("data_comparator.sv", 1, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vdata_comparator___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("data_comparator.sv", 1, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vdata_comparator___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vdata_comparator___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vdata_comparator___024root___eval_debug_assertions(Vdata_comparator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___eval_debug_assertions\n"); );
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rstn & 0xfeU)))) {
        Verilated::overWidthError("rstn");
    }
    if (VL_UNLIKELY(((vlSelfRef.inp1_i & 0xfc00U)))) {
        Verilated::overWidthError("inp1_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.inp2_i & 0xfc00U)))) {
        Verilated::overWidthError("inp2_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.valid_i & 0xfeU)))) {
        Verilated::overWidthError("valid_i");
    }
}
#endif  // VL_DEBUG
