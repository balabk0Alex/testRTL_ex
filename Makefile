# ============================================
# Data Comparator Verification Makefile
# ============================================


MODULE = data_comparator
SV_DIR = sv
TB_DIR = tb
SIM_DIR = sim

VERILATOR_FLAGS = -Wall --trace --coverage \
	--coverage-line \
	--coverage-toggle \
	--coverage-user



.PHONY: build
build: $(SIM_DIR)/obj_dir/V$(MODULE)
	@echo ""
	@echo "✓ Build completed"
	@echo "  Executable: $(SIM_DIR)/obj_dir/V$(MODULE)"

# run_test - запуск единичного теста
.PHONY: run_test
run_test: build
	@echo ""
	@echo "=== RUNNING SINGLE TEST ==="
	@mkdir -p $(SIM_DIR)
	@cd $(SIM_DIR) && ./obj_dir/V$(MODULE) 1
	@echo ""
	@echo "✓ Single test completed"

# run_regression - запуск набора тестов (полное покрытие)
.PHONY: run_regression
run_regression: build
	@echo ""
	@echo "=== RUNNING FULL REGRESSION ==="
	@mkdir -p $(SIM_DIR)
	@if [ -f test_files/all_sequences.bin ]; then \
		cp test_files/all_sequences.bin $(SIM_DIR)/ 2>/dev/null || true; \
	fi
	@cd $(SIM_DIR) && ./obj_dir/V$(MODULE) 3
	@echo ""
	@echo "✓ Regression completed"



.PHONY: run_custom
run_custom: build
	@echo ""
	@echo "=== RUNNING CUSTOM TEST: $(TEST) ==="
	@mkdir -p $(SIM_DIR)
	@cd $(SIM_DIR) && ./obj_dir/V$(MODULE) 1 $(TEST)
	@echo ""
	@echo "✓ Custom test completed"


.PHONY: sim
sim: waveform.vcd

.PHONY: waves
waves: waveform.vcd
	@echo ""
	@echo "### OPENING WAVEFORM ###"
	@gtkwave waveform.vcd

waveform.vcd: $(SIM_DIR)/obj_dir/V$(MODULE)
	@echo ""
	@echo "### SIMULATING WITH WAVEFORM ###"
	@cd $(SIM_DIR) && ./obj_dir/V$(MODULE) 1
	@if [ -f $(SIM_DIR)/waveform.vcd ]; then cp $(SIM_DIR)/waveform.vcd .; fi


.PHONY: coverage
coverage: run_regression
	@echo "=== GENERATING COVERAGE REPORT ==="
	verilator_coverage --write-info coverage.info coverage.dat
	genhtml coverage.info --output-directory coverage_report --title "Coverage Report" --legend
	@echo "Report: coverage_report/index.html"

.PHONY: view_coverage
view_coverage: coverage
	xdg-open coverage_report/index.html 2>/dev/null || open coverage_report/index.html 2>/dev/null || echo "Open coverage_report/index.html manually"


.PHONY: lint
lint: $(SV_DIR)/$(MODULE).sv
	@echo ""
	@echo "=== LINTING RTL ==="
	verilator --lint-only $(SV_DIR)/$(MODULE).sv
	@echo "✓ Lint completed"


$(SIM_DIR)/obj_dir/V$(MODULE): $(SIM_DIR)/.stamp.verilate
	@echo ""
	@echo "### BUILDING SIMULATOR ###"
	@$(MAKE) -C $(SIM_DIR)/obj_dir -f V$(MODULE).mk V$(MODULE) -s

# Вериляция (Verilate)
$(SIM_DIR)/.stamp.verilate: $(SV_DIR)/$(MODULE).sv $(TB_DIR)/tb_$(MODULE).cpp
	@echo
	@echo "### VERILATING ###"
	@mkdir -p $(SIM_DIR)
	cd $(SIM_DIR) && verilator -Wall --trace \
    --coverage \
    --coverage-line \
    --coverage-toggle \
    --coverage-user \
    -cc ../$(SV_DIR)/$(MODULE).sv --exe ../$(TB_DIR)/tb_$(MODULE).cpp
	@touch $@

.PHONY: clean
clean:
	@echo ""
	@echo "=== CLEANING ==="
	rm -rf $(SIM_DIR)
	rm -f waveform.vcd
	rm -f coverage.dat coverage.info
	rm -rf coverage_report
	@echo "✓ Clean completed"


.PHONY: clean_results
clean_results:
	@echo ""
	@echo "=== CLEANING RESULTS ==="
	rm -rf results
	rm -f $(SIM_DIR)/test_results_*.log
	@echo "✓ Results cleaned"



# Coverage report
.PHONY: coverage
coverage: run_regression
	@echo "=== GENERATING COVERAGE REPORT ==="
	verilator_coverage --write-info coverage.info coverage.dat
	genhtml coverage.info --output-directory coverage_report --title "Coverage Report" --legend
	@echo "Report: coverage_report/index.html"

.PHONY: view_coverage
view_coverage: coverage
	xdg-open coverage_report/index.html 2>/dev/null || open coverage_report/index.html 2>/dev/null || echo "Open coverage_report/index.html manually"

# Справка
.PHONY: help
help:
	@echo ""
	@echo "╔════════════════════════════════════════════════════════════╗"
	@echo "║     Data Comparator Verification - Makefile Help           ║"
	@echo "╚════════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "📌 ОСНОВНЫЕ ЦЕЛИ (обязательные):"
	@echo "  make build           - Compile RTL and verification environment"
	@echo "  make run_test        - Run single test"
	@echo "  make run_regression  - Run full regression (all tests)"
	@echo ""
	@echo "📁 ПРИМЕРЫ ЗАПУСКА:"
	@echo "  make build                          # Build only"
	@echo "  make run_regression                 # Full regression"
	@echo "  make coverage && make view_coverage # Coverage report"(NOT ACTUAL!!!)
	@echo "  make clean                          # Full cleanup"
	@echo "" 	