// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vdata_comparator__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vdata_comparator::Vdata_comparator(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vdata_comparator__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rstn{vlSymsp->TOP.rstn}
    , valid_i{vlSymsp->TOP.valid_i}
    , outp_o{vlSymsp->TOP.outp_o}
    , valid_o{vlSymsp->TOP.valid_o}
    , inp1_i{vlSymsp->TOP.inp1_i}
    , inp2_i{vlSymsp->TOP.inp2_i}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vdata_comparator::Vdata_comparator(const char* _vcname__)
    : Vdata_comparator(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vdata_comparator::~Vdata_comparator() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vdata_comparator___024root___eval_debug_assertions(Vdata_comparator___024root* vlSelf);
#endif  // VL_DEBUG
void Vdata_comparator___024root___eval_static(Vdata_comparator___024root* vlSelf);
void Vdata_comparator___024root___eval_initial(Vdata_comparator___024root* vlSelf);
void Vdata_comparator___024root___eval_settle(Vdata_comparator___024root* vlSelf);
void Vdata_comparator___024root___eval(Vdata_comparator___024root* vlSelf);

void Vdata_comparator::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vdata_comparator::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vdata_comparator___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vdata_comparator___024root___eval_static(&(vlSymsp->TOP));
        Vdata_comparator___024root___eval_initial(&(vlSymsp->TOP));
        Vdata_comparator___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vdata_comparator___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vdata_comparator::eventsPending() { return false; }

uint64_t Vdata_comparator::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vdata_comparator::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vdata_comparator___024root___eval_final(Vdata_comparator___024root* vlSelf);

VL_ATTR_COLD void Vdata_comparator::final() {
    contextp()->executingFinal(true);
    Vdata_comparator___024root___eval_final(&(vlSymsp->TOP));
    contextp()->executingFinal(false);
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vdata_comparator::hierName() const { return vlSymsp->name(); }
const char* Vdata_comparator::modelName() const { return "Vdata_comparator"; }
unsigned Vdata_comparator::threads() const { return 1; }
void Vdata_comparator::prepareClone() const { contextp()->prepareClone(); }
void Vdata_comparator::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vdata_comparator::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false}};
};

//============================================================
// Trace configuration

void Vdata_comparator___024root__trace_decl_types(VerilatedVcd* tracep);

void Vdata_comparator___024root__trace_init_top(Vdata_comparator___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vdata_comparator___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vdata_comparator___024root*>(voidSelf);
    Vdata_comparator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    Vdata_comparator___024root__trace_decl_types(tracep);
    Vdata_comparator___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vdata_comparator___024root__trace_register(Vdata_comparator___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vdata_comparator::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vdata_comparator::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP), name(), false, 9);
    Vdata_comparator___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
