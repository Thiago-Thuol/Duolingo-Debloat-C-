CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g
BUILD    := build
TARGET   := main

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=$(BUILD)/%.o)
DEPS := $(OBJS:.o=.d)

all: $(TARGET)

# make cheat: limpa os objetos e recompila com -DCHEAT
cheat: CXXFLAGS += -DCHEAT
cheat: 
	  rm -f $(BUILD)/Game.o
	  $(MAKE) $(TARGET) CXXFLAGS="$(CXXFLAGS)"

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

$(BUILD)/%.o: %.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD) $(TARGET)

-include $(DEPS)

.PHONY: all cheat run clean