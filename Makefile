CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I .
 
TARGET = bank_system
 
SRCS = main.cpp \
       Transaction.cpp \
       Account.cpp \
       SavingsAccount.cpp \
       CheckingAccount.cpp \
       BankSystem.cpp
 
all: $(TARGET)
 
$(TARGET):
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)
 
clean:
	del /f $(TARGET).exe 2>nul || rm -f $(TARGET)
 
run: all
	./$(TARGET)
 
.PHONY: all clean run
