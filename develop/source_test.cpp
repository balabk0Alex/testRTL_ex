//Goal this file is creating test 
#include <iostream>
#include <fstream>




class TestWriter {
private:
    std::ofstream file;
    
public:
    bool open(const std::string& filename, bool clear_existing = true) {

    
        std::ios::openmode mode = std::ios::binary;
        if (clear_existing) {
            mode |= std::ios::trunc;  // clear existing file
        } else {
            mode |= std::ios::app;     //in end
        }
        
        file.open(filename, mode);
        return file.is_open();
    }
    
    void write_transaction(bool inp1, bool inp2, bool inp3) {
        uint8_t packed = (inp3 << 2) | (inp2 << 1) | inp1;
        file.write(reinterpret_cast<char*>(&packed), 1);
    }
    
    void close() {
        if (file.is_open()) {
            file.close();
        }
    }
};

// Использование
int main() {
    TestWriter writer;
    
    // Очистит существующий файл
    writer.open("tests.bin", true);
    writer.write_transaction(1, 1, 1);  // 000: inp1=0, inp2=0, valid=0
writer.write_transaction(1, 1, 1);  // 001: inp1=0, inp2=0, valid=1 (EQUAL)
writer.write_transaction(1, 1, 1);  // 010: inp1=0, inp2=1, valid=0
writer.write_transaction(1, 1, 1);  // 011: inp1=0, inp2=1, valid=1 (UNEQUAL)
writer.write_transaction(1, 1, 1);  // 100: inp1=1, inp2=0, valid=0
writer.write_transaction(1, 0, 1);  // 101: inp1=1, inp2=0, valid=1 (UNEQUAL)
writer.write_transaction(1, 1, 0);  // 110: inp1=1, inp2=1, valid=0
writer.write_transaction(1, 1, 1);  // 111: inp1=1, inp2=1, valid=1 (EQUAL)
    writer.close();
    
}