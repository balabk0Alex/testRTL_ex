#pragma once

class DCInTxInp
{
    public:
    DCInTxInp(bool equal = false, bool valid = false, bool rst = false)
        : signal_i1_i2_is_equal(equal), valid_i(valid), rstn(rst) {}

    bool signal_i1_i2_is_equal;
    bool valid_i; 
    bool rstn;
};