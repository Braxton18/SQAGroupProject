IDIR = ./include
SRC_DIRS  = ./src
CC = g++
CFLAGS= -o

TARGET_EXEC = final_project

SRCS = $(shell find $(SRC_DIRS) -name '*.cpp')

proj1: $(SRCS) $(IDIR)
	$(CC) $(CFLAGS) $(TARGET_EXEC) -I $(IDIR) $(SRCS)

run:
	./$(TARGET_EXEC)
clean:
	rm $(TARGET_EXEC)
cleartxt:
	> products.txt 
	> uniqueNums.txt 
	> userNames.txt 
	> cardNums.txt 
	> customer.txt 
	> customerNum.txt 
	> customers.txt 
	> transactions.txt
	> rewards.txt
