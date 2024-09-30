TEST_PATH = test/
UNITY_SRC_PATH = test/unity/
TEST_LIBC_SRC_PATH = src/libc
TEST_BIN_PATH = test/bin/
TEST_RESULT_PATH = test/bin/results/
TEST_LIBC_BIN_PATH = test/bin/libc

BUILD_PATHS = $(TEST_BIN_PATH) $(TEST_RESULT_PATH) $(TEST_LIBC_BIN_PATH)

TEST_SRC = $(wildcard $(TEST_PATH)*.c)
UNITY_SRC = $(wildcard $(UNITY_SRC_PATH)*.c)
TEST_LIBC_SRC = $(wildcard $(TEST_LIBC_SRC_PATH)/*.c)
TEST_LIBC_OBJ = $(patsubst $(TEST_LIBC_SRC_PATH)%.c,$(TEST_LIBC_BIN_PATH)%.o,$(TEST_LIBC_SRC))

COMPILE=gcc
TEST_CC = -Werror -g -std=c11 -ffreestanding 
MKDIR = mkdir -p
RM = rm -rf 

PASSED = `grep -s :PASS $(TEST_RESULT_PATH)*.txt`
FAIL = `grep -s :FAIL $(TEST_RESULT_PATH)*.txt`
IGNORE = `grep -s :IGNORE $(TEST_RESULT_PATH)*.txt`
PASSED_COUNT = `grep -s :PASS $(TEST_RESULT_PATH)*.txt | wc -l`
FAIL_COUNT = `grep -s :FAIL $(TEST_RESULT_PATH)*.txt | wc -l`
IGNORE_COUNT = `grep -s :IGNORE $(TEST_RESULT_PATH)*.txt | wc -l`

RESULTS = $(patsubst $(TEST_PATH)%_test.c,$(TEST_RESULT_PATH)%_result.txt,$(TEST_SRC))

test: clean $(BUILD_PATHS) $(RESULTS)
	@echo "-----------------------\n\tIGNORES\n-----------------------"
	@echo "$(IGNORE)"
	@echo "\n-------------------------\n\tFAILURES\n-------------------------"
	@echo "$(FAIL)"
	@echo "\n-----------------------\n\tPASSED\n-----------------------"
	@echo "$(PASSED)"
	@echo "\n-----------------------"
	@echo "PASSED: $(PASSED_COUNT) FAIL: $(FAIL_COUNT) IGNORE: $(IGNORE_COUNT)"
	@echo "-----------------------\n"

$(TEST_RESULT_PATH)%_result.txt: $(TEST_BIN_PATH)%.out
	@./$< > $@ 2>&1 || true

$(TEST_LIBC_BIN_PATH)/%.o: $(TEST_LIBC_SRC_PATH)/%.c
	@$(COMPILE) $(TEST_CC) -c $< -o $@ 

$(TEST_BIN_PATH)%.out: $(TEST_PATH)%_test.c $(TEST_LIBC_OBJ)  
	@$(COMPILE) $(UNITY_SRC) $< $(TEST_LIBC_OBJ) -DTEST $(TEST_CC) -iquote ./src/ -o $@

$(TEST_BIN_PATH):
	@$(MKDIR) $(TEST_BIN_PATH)

$(TEST_RESULT_PATH):
	@$(MKDIR) $(TEST_RESULT_PATH)

$(TEST_LIBC_BIN_PATH):
	@$(MKDIR) $(TEST_LIBC_BIN_PATH)

clean:
	@$(RM) $(TEST_BIN_PATH)