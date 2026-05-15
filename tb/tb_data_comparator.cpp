#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vdata_comparator.h"
#include "Vdata_comparator___024root.h"
#include <iomanip>


#include "tb_data_comparator.hpp"
#include "TestReader.cpp"
vluint64_t sim_time = 0;
vluint64_t clock_counter = 0 ;
vluint64_t max_sim_time = 0 ;


void showProgress(uint64_t current, uint64_t total) {
    if (total == 0) return;
    
    int percent = (current * 100) / total;
    int bar_width = 40;
    int pos = (bar_width * current) / total;
    
    std::cout << "\r[";
    for (int i = 0; i < bar_width; i++) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << percent << "% (" << current << "/" << total << ")";
    std::cout << std::flush;
}

class DCOutTx{
    public:
    bool outp_o;
    bool valid_o;
};


class DCInTx
{
    public:
    uint16_t inp1_i;
    uint16_t inp2_i;
    bool valid_i; 
    bool rstn;
};



class DCScb {
private:
    std::deque<DCInTx*> in_q;
    int total_tests = 0;
    int passed_tests = 0;
    int failed_tests = 0;
    int timeout_tests = 0;
    std::ofstream log_file;
    
public:
    DCScb() {
        // Создаём файл с временной меткой
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        char filename[64];
        std::strftime(filename, sizeof(filename), "../results/test_results_%Y%m%d_%H%M%S.log", &tm);
        log_file.open(filename);
        
        if (log_file.is_open()) {
            log_file << "Test Results Log - " << std::asctime(&tm) << std::endl;
            log_file << "====================================\n" << std::endl;
        }
    }
    
    ~DCScb() {
        if (log_file.is_open()) {
            log_file.close();
        }
    }
    
    void writeIn(DCInTx *tx) {
        in_q.push_back(tx);
        if (tx->rstn && tx->valid_i) {
            total_tests++;
        }
    }
    
    void writeOut(DCOutTx* tx) {
    DCInTx* in = NULL;
    
    if (in_q.size() < 7) {
        delete tx;
        return;
    }

    
    in = in_q.front();
    in_q.pop_front();
    
    // ВСЕГДА проверяем выход, даже если не было валидного входа!
    bool expected = (in->rstn && in->valid_i) ? (in->inp1_i == in->inp2_i) : false;
    bool actual = tx->outp_o;
    bool valid_actual = tx->valid_o;
    int test_num = passed_tests + failed_tests + timeout_tests + 1;
    
    // Логируем входные данные
    // std::cout << "\n[DEBUG] Test #" << test_num << ": "
            //   << "rstn=" << in->rstn 
            //   << ", valid_i=" << in->valid_i
            //   << ", expected=" << expected
            //   << ", valid_o=" << valid_actual
            //   << ", outp_o=" << actual << std::endl;
    
    // Вывод в консоль с деталями
    // printTestResult(test_num, in, expected, actual, valid_actual);
    
    // Запись в файл
    logTestResult(test_num, in, expected, actual, valid_actual);
    
    // Обновление статистики в зависимости от сценария
    if (in->rstn && in->valid_i) {
        // Сценарий 1: Был валидный вход - ждём выход через 6 тактов
        if (valid_actual == 1 && actual == expected) {
            passed_tests++;
            // std::cout << "  ✓ VALID INPUT: correct output" << std::endl;
        } else if (valid_actual == 0) {
            timeout_tests++;
            // std::cout << "  ✗ VALID INPUT: timeout (no valid_o)" << std::endl;
        } else {
            failed_tests++;
            // std::cout << "  ✗ VALID INPUT: wrong output (expected=" 
                    //   << expected << ", got=" << actual << ")" << std::endl;
        }
    } 
    else if (!in->rstn) {
        // Сценарий 2: Был сброс - выход должен быть 0
        if (valid_actual == 0 && actual == 0) {
            passed_tests++;
            // std::cout << "  ✓ RESET: output is 0 as expected" << std::endl;
        } else if (valid_actual == 1) {
            failed_tests++;
            // std::cout << "  ✗ RESET: unexpected valid_o=1" << std::endl;
        } else if (actual == 1) {
            failed_tests++;
            // std::cout << "  ✗ RESET: unexpected outp_o=1" << std::endl;
        } else {
            passed_tests++;
            // std::cout << "  ✓ RESET: output is 0" << std::endl;
        }
    }
    else if (!in->valid_i) {
        // Сценарий 3: Не было валидного входа - выход должен быть 0
        if (valid_actual == 0 && actual == 0) {
            passed_tests++;
            // std::cout << "  ✓ NO INPUT: output is 0 as expected" << std::endl;
        } else {
            failed_tests++;
            // std::cout << "  ✗ NO INPUT: unexpected output (valid_o=" 
                    //   << valid_actual << ", outp_o=" << actual << ")" << std::endl;
        }
    }
    
    delete in;
    delete tx;
}
    
    void printTestResult(int num, DCInTx* in, bool expected, bool actual, bool valid) {
    std::cout << "\n┌─────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│ Test #" << std::setw(3) << num << "                                               │" << std::endl;
    std::cout << "├─────────────────────────────────────────────────┤" << std::endl;
    
    // INPUT section
    std::cout << "│ INPUT:                                           │" << std::endl;
    std::cout << "│   rstn:    " << in->rstn << "                                                 │" << std::endl;
    std::cout << "│   valid_i: " << in->valid_i << "                                                 │" << std::endl;
    
    if (in->rstn && in->valid_i) {
        std::cout << "│   inp1:    " << std::setw(5) << in->inp1_i << "                                             │" << std::endl;
        std::cout << "│   inp2:    " << std::setw(5) << in->inp2_i << "                                             │" << std::endl;
        std::cout << "│   equal:   " << (expected ? "YES" : "NO") << "                                             │" << std::endl;
    } else {
        std::cout << "│   (no valid input or reset)                     │" << std::endl;
    }
    
    // OUTPUT section
    std::cout << "│ OUTPUT:                                          │" << std::endl;
    std::cout << "│   valid_o: " << valid << "                                                 │" << std::endl;
    std::cout << "│   outp_o:  " << actual << "                                                 │" << std::endl;
    
    // RESULT section
    std::cout << "│ RESULT:                                          │" << std::endl;
    
    if (in->rstn && in->valid_i) {
        // Был валидный вход
        if (valid && actual == expected) {
            std::cout << "│   ✓ PASSED (correct output)                     │" << std::endl;
        } else if (!valid) {
            std::cout << "│   ✗ TIMEOUT (no output after 6 cycles)         │" << std::endl;
        } else {
            std::cout << "│   ✗ FAILED (expected=" << expected << ", got=" << actual << ")                │" << std::endl;
        }
    } 
    else if (!in->rstn) {
        // Был сброс
        if (!valid && actual == 0) {
            std::cout << "│   ✓ PASSED (reset state correct)               │" << std::endl;
        } else {
            std::cout << "│   ✗ FAILED (invalid output during reset)       │" << std::endl;
        }
    }
    else if (!in->valid_i) {
        // Не было валидного входа
        if (!valid && actual == 0) {
            std::cout << "│   ✓ PASSED (no output without input)           │" << std::endl;
        } else {
            std::cout << "│   ✗ FAILED (unexpected output)                 │" << std::endl;
        }
    }
    
    std::cout << "└─────────────────────────────────────────────────┘" << std::endl;
}
    
    void logTestResult(int num, DCInTx* in, bool expected, bool actual, bool valid) {
    if (!log_file.is_open()) return;
    
    log_file << "Test #" << num << std::endl;
    log_file << "  rstn:    " << in->rstn << std::endl;
    log_file << "  valid_i: " << in->valid_i << std::endl;
    
    if (in->rstn && in->valid_i) {
        log_file << "  inp1:    " << in->inp1_i << std::endl;
        log_file << "  inp2:    " << in->inp2_i << std::endl;
        log_file << "  equal:   " << expected << std::endl;
    } else if (!in->rstn) {
        log_file << "  scenario: RESET" << std::endl;
    } else {
        log_file << "  scenario: NO INPUT" << std::endl;
    }
    
    log_file << "  valid_o: " << valid << std::endl;
    log_file << "  outp_o:  " << actual << std::endl;
    
    // Result
    if (in->rstn && in->valid_i) {
        if (valid && actual == expected) {
            log_file << "  Result: PASSED (valid input, correct output)" << std::endl;
        } else if (!valid) {
            log_file << "  Result: TIMEOUT (no output after 6 cycles)" << std::endl;
        } else {
            log_file << "  Result: FAILED (expected=" << expected << ")" << std::endl;
        }
    } 
    else if (!in->rstn) {
        if (!valid && actual == 0) {
            log_file << "  Result: PASSED (reset state OK)" << std::endl;
        } else {
            log_file << "  Result: FAILED (invalid output during reset)" << std::endl;
        }
    }
    else if (!in->valid_i) {
        if (!valid && actual == 0) {
            log_file << "  Result: PASSED (no output without input)" << std::endl;
        } else {
            log_file << "  Result: FAILED (unexpected output)" << std::endl;
        }
    }
    log_file << std::endl;
}
    
    void printFinalReport() {
        int total = passed_tests + failed_tests + timeout_tests;
        float pass_rate = total > 0 ? (passed_tests * 100.0f / total) : 0;
        
        std::cout << "\n\n";
        std::cout << "╔══════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║                   FINAL TEST REPORT                  ║" << std::endl;
        std::cout << "╠══════════════════════════════════════════════════════╣" << std::endl;
        std::cout << "║  Total tests:  " << std::setw(5) << total << "                                  ║" << std::endl;
        std::cout << "║  Passed:       " << std::setw(5) << passed_tests << " ( " << std::setw(5) 
                  << std::fixed << std::setprecision(1) << pass_rate << "% )                      ║" << std::endl;
        std::cout << "║  Failed:       " << std::setw(5) << failed_tests << "                                  ║" << std::endl;
        std::cout << "║  Timeout:      " << std::setw(5) << timeout_tests << "                                  ║" << std::endl;
        std::cout << "╠══════════════════════════════════════════════════════╣" << std::endl;
        
        if (failed_tests == 0 && timeout_tests == 0) {
            std::cout << "║                                                      ║" << std::endl;
            std::cout << "║         ★★★★★  ALL TESTS PASSED!  ★★★★★           ║" << std::endl;
        } else {
            std::cout << "║                                                      ║" << std::endl;
            std::cout << "║         ⚠⚠⚠  SOME TESTS FAILED!  ⚠⚠⚠              ║" << std::endl;
            std::cout << "║                                                      ║" << std::endl;
            std::cout << "║  Check the log file for details                     ║" << std::endl;
        }
        std::cout << "╚══════════════════════════════════════════════════════╝" << std::endl;
        
        if (log_file.is_open()) {
            std::cout << "\nDetailed log saved to file" << std::endl;
        }
    }
    
    void cleanup() {
        while (!in_q.empty()) {
            delete in_q.front();
            in_q.pop_front();
        }
    }
};





DCInTx * generatorDCInTx(DCInTxInp txInp, bool is_NULL)///!!!
{
    if(!is_NULL)
    {
        DCInTx *tx = new DCInTx();
        if(txInp.signal_i1_i2_is_equal)
        {
            tx->inp1_i = rand() & 0x3FF;; //сгенерируй 10 битное число рандомное
            tx->inp2_i = tx->inp1_i;

        }
        else
        {
            tx->inp1_i = rand() & 0x3FF;; //сгенерируй 10 битное число рандомное
            tx->inp2_i =rand() & 0x3FF; ; //сгенерируй 10 битное число рандомное

        }

        tx->valid_i = txInp.valid_i;
        tx->rstn = txInp.rstn;

        return tx;
    }

    return NULL;

}



class DCInDrv
{
    private:
    Vdata_comparator *dut;
    public:
    DCInDrv(Vdata_comparator *dut){
        this->dut = dut;
    }

    void drive(DCInTx *tx)
    {

        if(tx != NULL)
        {
            dut->inp1_i =tx->inp1_i & 0x3FF; 
            dut->inp2_i = tx->inp2_i & 0x3FF;
            dut->valid_i = tx->valid_i;
            dut->rstn = tx->rstn;
        }

        delete tx;
    }
};


class DCInMon{
    private:
    Vdata_comparator *dut;
    DCScb *scb;
    public:
    DCInMon(Vdata_comparator *dut, DCScb *scb){
        this->dut = dut;
        this->scb = scb;
    }



    void monitor()
    {
        DCInTx *tx = new DCInTx();
        tx->inp1_i = dut->inp1_i;
        tx->inp2_i = dut->inp2_i;
        tx->rstn = dut->rstn;
        tx->valid_i = dut->valid_i;
        
        scb->writeIn(tx); 

    }
};




class DCOutMon{
    private:
    Vdata_comparator *dut;
    DCScb *scb;

    public:
    DCOutMon(Vdata_comparator *dut, DCScb *scb){
        this->dut = dut;
        this->scb = scb;
    }

    void monitor()
    {
        DCOutTx *tx = new DCOutTx();
        tx->outp_o = dut->outp_o;
        tx->valid_o = dut->valid_o;

        scb->writeOut(tx);
    }
};


std::vector<DCInTxInp*> generateAllVariationsPointers() {
    std::vector<DCInTxInp*> variations;
    variations.reserve(8);
    
    for (int i = 0; i < 8; i++) {
        DCInTxInp* obj = new DCInTxInp(
            bool((i >> 2) & 1),
            bool((i >> 1) & 1),
            bool((i >> 0) & 1)
        );
        variations.push_back(obj);
    }
    
    return variations;
}


#define MAX_SIM_TIME 30 
#define VERIF_START_TIME 10

int main(int argc, char** argv, char** env ){

    int mode = 1;
    if (argc > 1) {
        mode = atoi(argv[1]);}

    

    Vdata_comparator *dut = new Vdata_comparator;

    Verilated::traceEverOn(true);
    Verilated::commandArgs(argc, argv);
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    dut->trace(m_trace , 5);
    m_trace->open("waveform.vcd");

    dut->clk = 0;
    dut->rstn = 1;
    
    
    DCScb    *scb    = new DCScb();
    DCInTx *tx ;

    //////////////////////////////////////////////////

    uint64_t n_test;
    DCInTxInp *txInp = new DCInTxInp;
    txInp->rstn = 1;
    txInp->valid_i = 1;
    txInp->signal_i1_i2_is_equal = 0;

    BinaryTestReader test_file("../test_files/all_sequences.bin");

    test_file.readAll();
    n_test = test_file.size();


    std::vector<DCInTxInp> test_t;
    test_t = test_file.getTransactions();

    if(mode == 1)
    {
        test_t.assign(1, test_t[0]);
    }


    std::cout << test_t.size() << std::endl ;
   
    
    //std::vector<DCInTxInp*> all_test = generateAllVariationsPointers();
    
    
    //////////////////////////////////////////////////
    //all_test.insert(all_test.end(), 10, nullptr);
    n_test = test_t.size();

    int delay = 6;
    max_sim_time = 2*n_test + 2*delay;

    std::cout << n_test << std::endl;

    size_t n_test_exec = 0;

    DCInDrv  *drv    = new DCInDrv(dut);
    DCInMon *inMon = new DCInMon(dut, scb);
    DCOutMon *outMon = new DCOutMon(dut, scb);
    //init input parameters

    while (sim_time < max_sim_time){

        dut->clk ^= 1; 
        dut->eval();


        if(dut->clk)
        {

            if(n_test_exec < n_test)
                tx = generatorDCInTx(test_t[n_test_exec],0);
            else
            {
                tx = NULL;

            }
              
                
                
            drv->drive(tx);//here signal in DUT

           inMon->monitor();
           outMon->monitor();
            n_test_exec++;
            showProgress(n_test_exec, n_test) ;

            
        }


        m_trace->dump(sim_time);
        sim_time++;
     

    }


    scb->printFinalReport();
    std::cout << "Просмотреть детальные результаты тестирования вы можете в папке results" << std::endl;
    m_trace->close();
    delete dut;
    exit(EXIT_SUCCESS);
}
