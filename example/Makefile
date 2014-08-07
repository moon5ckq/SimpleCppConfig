TARGET = example
all: $(TARGET)

INCLUDE = -I..
OPTFLAGS = -O2
CFLAGS = \
	$(INCLUDE) \
	$(OPTFLAGS)

$(TARGET): example.cpp
	g++ $^ $(CFLAGS) -o $@

run: $(TARGET)
	@echo start running `$(TARGET)`
	@$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean