// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdata_comparator.h for the primary calling header

#include "Vdata_comparator__pch.h"

VL_ATTR_COLD void Vdata_comparator___024root___eval_static(Vdata_comparator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___eval_static\n"); );
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vdata_comparator___024root___eval_initial(Vdata_comparator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___eval_initial\n"); );
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vdata_comparator___024root___eval_final(Vdata_comparator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___eval_final\n"); );
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdata_comparator___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vdata_comparator___024root___eval_phase__stl(Vdata_comparator___024root* vlSelf);

VL_ATTR_COLD void Vdata_comparator___024root___eval_settle(Vdata_comparator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___eval_settle\n"); );
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vdata_comparator___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("data_comparator.sv", 1, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 10000 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vdata_comparator___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vdata_comparator___024root___eval_triggers_vec__stl(Vdata_comparator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___eval_triggers_vec__stl\n"); );
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vdata_comparator___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdata_comparator___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vdata_comparator___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vdata_comparator___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vdata_comparator___024root___stl_sequent__TOP__0(Vdata_comparator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___stl_sequent__TOP__0\n"); );
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.outp_o = (1U & ((IData)(vlSelfRef.data_comparator__DOT__res_internal) 
                              >> 5U));
    vlSelfRef.valid_o = (1U & ((IData)(vlSelfRef.data_comparator__DOT__valid_internal) 
                               >> 5U));
}

VL_ATTR_COLD void Vdata_comparator___024root___eval_stl(Vdata_comparator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___eval_stl\n"); );
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vdata_comparator___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vdata_comparator___024root___eval_phase__stl(Vdata_comparator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___eval_phase__stl\n"); );
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vdata_comparator___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vdata_comparator___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vdata_comparator___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vdata_comparator___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vdata_comparator___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdata_comparator___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vdata_comparator___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vdata_comparator___024root___ctor_var_reset(Vdata_comparator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdata_comparator___024root___ctor_var_reset\n"); );
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rstn = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5377340664288042355ull);
    vlSelf->inp1_i = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 10463514259095920975ull);
    vlSelf->inp2_i = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 6024601929028990744ull);
    vlSelf->valid_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 550966959580451262ull);
    vlSelf->outp_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8308918884968975913ull);
    vlSelf->valid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10854271546065566948ull);
    vlSelf->data_comparator__DOT__res_internal = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 9686700772074855637ull);
    vlSelf->data_comparator__DOT__valid_internal = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 3618794770779879164ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
