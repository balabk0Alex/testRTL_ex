// generate_all_sequences.cpp
// Генерация всех возможных последовательностей из 6 состояний (8^6 = 262144 вариантов)

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <array>
#include <chrono>

class TestWriter {
private:
    std::ofstream file;
    uint64_t total_written = 0;
    
public:
    bool open(const std::string& filename, bool clear_existing = true) {
        std::ios::openmode mode = std::ios::binary;
        if (clear_existing) {
            mode |= std::ios::trunc;
        } else {
            mode |= std::ios::app;
        }
        
        file.open(filename, mode);
        return file.is_open();
    }
    
    void write_transaction(bool inp1, bool inp2, bool inp3) {
        uint8_t packed = (inp3 << 2) | (inp2 << 1) | inp1;
        file.write(reinterpret_cast<char*>(&packed), 1);
        total_written++;
    }
    
    void write_state(int state) {
        // state: 0-7, где биты: [valid, inp2, inp1]
        // или в вашем формате: [valid_i, inp2, inp1]
        uint8_t packed = static_cast<uint8_t>(state & 0x07);
        file.write(reinterpret_cast<char*>(&packed), 1);
        total_written++;
    }
    
    void write_sequence(const std::array<int, 6>& seq) {
        for (int i = 0; i < 6; i++) {
            write_state(seq[i]);
        }
    }
    
    void close() {
        if (file.is_open()) {
            std::cout << "Total bytes written: " << total_written << std::endl;
            std::cout << "Total sequences: " << (total_written / 6) << std::endl;
            file.close();
        }
    }
    
    uint64_t getTotalWritten() const { return total_written; }
};

// Рекурсивная генерация всех последовательностей
class SequenceGenerator {
private:
    TestWriter& writer;
    std::array<int, 6> current;
    uint64_t sequences_generated = 0;
    
public:
    SequenceGenerator(TestWriter& w) : writer(w) {}
    
    void generate_all() {
        generate_recursive(0);
        std::cout << "\n=== GENERATION COMPLETE ===" << std::endl;
        std::cout << "Total sequences generated: " << sequences_generated << std::endl;
        std::cout << "Expected: 8^6 = " << pow(8, 6) << std::endl;
    }
    
private:
    void generate_recursive(int depth) {
        if (depth == 6) {
            writer.write_sequence(current);
            sequences_generated++;
            
            // Прогресс каждые 10000 последовательностей
            if (sequences_generated % 10000 == 0) {
                std::cout << "Generated " << sequences_generated 
                          << " sequences..." << std::endl;
            }
            return;
        }
        
        for (int state = 0; state < 8; state++) {
            current[depth] = state;
            generate_recursive(depth + 1);
        }
    }
};

// Оптимизированная версия (без рекурсии, линейный перебор)
class OptimizedGenerator {
private:
    TestWriter& writer;
    
public:
    OptimizedGenerator(TestWriter& w) : writer(w) {}
    
    void generate_all() {
        uint64_t total = 1ULL << 18;  // 2^18 = 262144
        std::array<int, 6> seq;
        
        std::cout << "Generating " << total << " sequences..." << std::endl;
        
        for (uint64_t state_code = 0; state_code < total; state_code++) {
            // Распаковываем 18-битное число в 6 состояний по 3 бита
            for (int i = 0; i < 6; i++) {
                // Младшие 3 бита - первое состояние и т.д.
                seq[i] = (state_code >> (i * 3)) & 0x7;
            }
            
            writer.write_sequence(seq);
            
            if ((state_code + 1) % 10000 == 0) {
                std::cout << "Generated " << (state_code + 1) 
                          << " sequences..." << std::endl;
            }
        }
        
        std::cout << "\n=== GENERATION COMPLETE ===" << std::endl;
        std::cout << "Total sequences generated: " << total << std::endl;
    }
};

// Класс для чтения и верификации сгенерированного файла
class SequenceReader {
private:
    std::ifstream file;
    uint64_t total_sequences = 0;
    
public:
    bool open(const std::string& filename) {
        file.open(filename, std::ios::binary);
        if (!file.is_open()) return false;
        
        // Получаем размер файла
        file.seekg(0, std::ios::end);
        size_t file_size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        total_sequences = file_size / 6;  // 6 байт на последовательность
        std::cout << "Opened " << filename << ", size: " << file_size 
                  << " bytes, sequences: " << total_sequences << std::endl;
        return true;
    }
    
    bool read_next_sequence(std::array<int, 6>& seq) {
        uint8_t buffer[6];
        if (!file.read(reinterpret_cast<char*>(buffer), 6)) {
            return false;
        }
        
        for (int i = 0; i < 6; i++) {
            seq[i] = buffer[i] & 0x07;
        }
        return true;
    }
    
    void close() {
        if (file.is_open()) file.close();
    }
    
    uint64_t getTotalSequences() const { return total_sequences; }
    
    void print_statistics() {
        std::cout << "\n=== FILE STATISTICS ===" << std::endl;
        std::cout << "Total sequences: " << total_sequences << std::endl;
        std::cout << "Expected: 8^6 = " << pow(8, 6) << std::endl;
        
        // Подсчёт распределения состояний
        std::array<int, 8> state_count = {0};
        
        std::array<int, 6> seq;
        while (read_next_sequence(seq)) {
            for (int i = 0; i < 6; i++) {
                state_count[seq[i]]++;
            }
        }
        
        // Сброс для повторного чтения
        file.clear();
        file.seekg(0, std::ios::beg);
        
        std::cout << "\nState distribution (each of 6 positions):" << std::endl;
        for (int s = 0; s < 8; s++) {
            std::cout << "  State " << s << ": " << state_count[s] << " times" << std::endl;
        }
    }
};

int main(int argc, char** argv) {
    std::string filename = "all_sequences.bin";
    bool optimized = true;  // true - быстрый перебор, false - рекурсивный
    
    std::cout << "╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║     GENERATING ALL 8^6 = 262144 SEQUENCES              ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
    
    TestWriter writer;
    
    if (!writer.open(filename, true)) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return 1;
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    
    if (optimized) {
        OptimizedGenerator generator(writer);
        generator.generate_all();
    } else {
        SequenceGenerator generator(writer);
        generator.generate_all();
    }
    
    writer.close();
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "\nTime taken: " << duration.count() << " ms" << std::endl;
    
    // Проверка сгенерированного файла
    std::cout << "\n=== VERIFYING GENERATED FILE ===" << std::endl;
    SequenceReader reader;
    if (reader.open(filename)) {
        reader.print_statistics();
        reader.close();
    }
    
    // Информация о размере
    std::cout << "\nFile size: " << (262144 * 6) << " bytes = " 
              << (262144 * 6 / 1024) << " KB" << std::endl;
    
    return 0;
}