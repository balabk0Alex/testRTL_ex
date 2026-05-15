#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>

#include "tb_data_comparator.hpp"

using TestTransaction = DCInTxInp;


class BinaryTestReader {
private:
    std::string filename;
    std::vector<TestTransaction> transactions;
    
public:
    // Конструктор
    explicit BinaryTestReader(const std::string& fname) : filename(fname) {}
    
    bool readAll() {
        transactions.clear();
        
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file " << filename << std::endl;
            return false;
        }
        
        // Получаем размер файла
        file.seekg(0, std::ios::end);
        size_t file_size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        if (file_size == 0) {
            std::cerr << "Warning: File is empty" << std::endl;
            return true;
        }
        
        // Читаем побайтно
        uint8_t packed;
        size_t bytes_read = 0;
        
        while (file.read(reinterpret_cast<char*>(&packed), 1)) {
            // Распаковываем биты
            bool inp1 = packed & 1;
            bool inp2 = (packed >> 1) & 1;
            bool inp3 = (packed >> 2) & 1;
            
            transactions.emplace_back(inp1, inp2, inp3);
            bytes_read++;
        }
        
        file.close();
        
        std::cout << "Successfully read " << transactions.size() 
                  << " transactions from " << filename << std::endl;
        
        return true;
    }
    
    // Получить вектор
    const std::vector<TestTransaction>& getTransactions() const {
        return transactions;
    }
    
    size_t size() const {
        return transactions.size();
    }
    
    const TestTransaction& operator[](size_t index) const {
        return transactions[index];
    }
    
    void clear() {
        transactions.clear();
    }
    
    void printAll() const {
        std::cout << "\n=== Transactions from " << filename << " ===" << std::endl;
        for (size_t i = 0; i < transactions.size(); i++) {
            std::cout << "[" << i << "] ";
            //transactions[i].print();
            std::cout << std::endl;
        }
        std::cout << "Total: " << transactions.size() << " transactions\n" << std::endl;
    }
};
