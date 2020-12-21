include CONFIG.cfg

.PHONY: all check clean

CC = gcc
EXEC_FILE = $(BUILD_DIR)/$(NAME)
OBJECTS = $(BUILD_DIR)/sorter.o $(BUILD_DIR)/read.o $(BUILD_DIR)/sort.o 
LOGS = $(patsubst $(TEST_DIR)/%.in, $(TEST_DIR)/%.log, $(wildcard $(TEST_DIR)/*.in))
PRESENCE_ERR = $(BUILD_DIR)/errors.err

all: $(EXEC_FILE)

$(EXEC_FILE) : $(OBJECTS) | $(BUILD_DIR)
	$(CC) $^ -o $@

$(OBJECTS): $(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c | $(BUILD_DIR)
	$(CC) -c $< -o $@

$(BUILD_DIR):	
	@mkdir -p $@ 

clean:
	$(RM) $(OBJECTS) $(LOGS) $(BUILD_DIR)/$(NAME) $(PRESENCE_ERR)

check: $(LOGS)
	@if [ -f $(PRESENCE_ERR) ]; then \
		exit 1; \
	fi

$(LOGS): $(TEST_DIR)/%.log: $(TEST_DIR)/%.in $(TEST_DIR)/%.out $(EXEC_FILE)
	@$(BUILD_DIR)/$(NAME) $< >$@
	@if cmp -s $(TEST_DIR)/$*.out $@; then \
		echo Test $* - was successful; \
	else \
		echo Test $* - was failed; \
		touch $(PRESENCE_ERR); \
	fi
