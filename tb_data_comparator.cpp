#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vdata_comparator.h"
#include "Vdata_comparator___024root.h"



#include "tb_data_comparator.hpp"
#include "TestReader.cpp"
vluint64_t sim_time = 0;
vluint64_t clock_counter = 0 ;
vluint64_t max_sim_time = 0 ;


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

// ALU scoreboard
class DCScb {
    private:
        std::deque<DCInTx*> in_q;

    public:
        // Input interface monitor port
        void writeIn(DCInTx *tx){
            in_q.push_back(tx);
        }

        // Output interface monitor port
        void writeOut(DCOutTx* tx){
            
            DCInTx* in = NULL;

            if(in_q.size() < 7 )
            {

            }
            else
            {
               
                in = in_q.front();
                in_q.pop_front();
                if(in->rstn && in->valid_i){
                if(tx->valid_o == 1 && tx->outp_o == (in->inp1_i == in->inp2_i))
                {
                    std::cout << "1" << std::endl;
                }
                else
                {
                  std::cout <<"inp1_i: "<< in->inp1_i<< std::endl;
                  std::cout <<"inp2_i: "<< in->inp2_i<< std::endl;

                }
            }
            else
            {
             std::cout << "3"<< std::endl;
           
            }
            // As the transaction items were allocated on the heap, it's important
            // to free the memory after they have been used
            delete in;

            }

            delete tx;







            // We should never get any data from the output interface
            // before an input gets driven to the input interface
          
          
            /*if(in_q.empty()){
                std::cout <<"Fatal Error in AluScb: empty AluInTx queue" << std::endl;
                exit(1);
            }

            DCInTx* in;
            in = in_q.front();
            in_q.pop_front();

            if((in->inp1_i == in->inp2_i) == tx->outp_o){
                std::cout << "TEST IS SUCCESS" << std::endl;
            }
            else 
            {
                std::cout << "TEST IS FAIL" << std::endl;  
                std::cout << "inp1:" << in->inp1_i<< std::endl;
                std::cout << "inp1:" <<in->inp2_i<< std::endl;
                std::cout << "outp_o:" <<tx->outp_o<< std::endl;

            }
            // As the transaction items were allocated on the heap, it's important
            // to free the memory after they have been used
            delete in;
            delete tx;*/

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
    Vdata_comparator *dut = new Vdata_comparator;

    Verilated::traceEverOn(true);
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

    BinaryTestReader test_file("tests.bin");

    test_file.readAll();
    n_test = test_file.size();


    std::vector<DCInTxInp> test_t;

    test_t = test_file.getTransactions();

    std::cout << test_t.size() << std::endl ;
    
    //std::vector<DCInTxInp*> all_test = generateAllVariationsPointers();
    
    
    //////////////////////////////////////////////////
    //all_test.insert(all_test.end(), 10, nullptr);
    n_test = test_t.size();

    int delay = 6;
    max_sim_time = 2*n_test + 2*delay ;

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
            
        }


        m_trace->dump(sim_time);
        sim_time++;
     

    }


    m_trace->close();
    delete dut;
    exit(EXIT_SUCCESS);
}
