SRC_PATH = $(PWD)/src
TEST_PATH = $(PWD)/test
C_FILE = ip_math.c
OBJ_FILE = $(C_FILE:.c=.o)
TEST_FILE = test.c
LIBRARY_NAME = libipmath.so
LDFALGS = -L$(SRC_PATH) -lipmath

.PHONY: object library test

all: object library test

object: 
	$(CC) -fPIC -c -g $(SRC_PATH)/$(C_FILE) -o $(SRC_PATH)/$(OBJ_FILE)

library: object
	$(CC) -shared $(SRC_PATH)/$(OBJ_FILE) -o $(SRC_PATH)/$(LIBRARY_NAME)

test: library
	$(CC) $(TEST_PATH)/$(TEST_FILE) -g -o $(TEST_PATH)/$(basename $(TEST_FILE)) $(LDFALGS)
	ln -sf $(SRC_PATH)/$(LIBRARY_NAME) $(TEST_PATH)/$(LIBRARY_NAME)

clean:
	rm -f $(SRC_PATH)/$(LIBRARY_NAME) $(TEST_PATH)/$(LIBRARY_NAME) \
		$(SRC_PATH)/$(OBJ_FILE) $(TEST_PATH)/$(basename $(TEST_FILE))


	