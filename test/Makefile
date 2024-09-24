PATHR = test/bin/results/
PATHT = test/
PATHB = test/bin/
PATHU = test/unity/

BUILD_PATHS = $(PATHB) $(PATHR)

SRCT = $(wildcard $(PATHT)*.c)
SRCU = $(wildcard $(PATHU)*.c)
CC_PREFIX = /usr/local/i386elfgcc/bin/i386-elf-


# COMPILE=$(CC_PREFIX)gcc
COMPILE=gcc
MKDIR = mkdir -p
RM = rm -rf 

PASSED = `grep -s PASS: $(PATHR)*.txt`
FAIL = `grep -s FAIL: $(PATHR)*.txt`
IGNORE = `grep -s IGNORE: $(PATHR)*.txt`
PASSED_COUNT = `grep -s -c PASS: $(PATHR)*.txt`
FAIL_COUNT = `grep -s -c FAIL: $(PATHR)*.txt`
IGNORE_COUNT = `grep -s -c IGNORE: $(PATHR)*.txt`

RESULTS = $(patsubst $(PATHT)%_test.c,$(PATHR)%_result.txt,$(SRCT))


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

$(PATHR)%_result.txt: $(PATHB)%.out
	@./$< > $@ 2>&1 || true

$(PATHB)%.out: $(PATHT)%_test.c
	@$(COMPILE) $(SRCU) -DTEST -Werror -g -std=c11 -ffreestanding -iquote ./src/ $< -o $@

$(PATHB):
	@$(MKDIR) $(PATHB)

$(PATHR):
	@$(MKDIR) $(PATHR)

clean:
	@$(RM) $(PATHB)