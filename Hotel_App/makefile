# # Tên file thực thi
# TARGET = Hotel_App

# # Thư mục chứa file header, file nguồn và file thực thi
# INCDIR = Inc
# SRCDIR = Src
# BINDIR = bin

# # Tìm tất cả các file nguồn .cpp trong thư mục SRCDIR
# SRCS = $(wildcard $(SRCDIR)/*.cpp)

# # Tạo danh sách các file object .o tương ứng trong thư mục BINDIR
# OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(BINDIR)/%.o)

# # Compiler và các flags cho compiler
# CXX = g++
# CXXFLAGS = -Wall -std=c++11 -I$(INCDIR)

# # Rule mặc định để biên dịch chương trình
# all: $(BINDIR)/$(TARGET)

# # Tạo thư mục bin nếu chưa tồn tại
# $(BINDIR):
# 	mkdir -p $(BINDIR)

# # Rule để tạo file thực thi trong thư mục bin
# $(BINDIR)/$(TARGET): $(OBJS) | $(BINDIR)
# 	$(CXX) $(CXXFLAGS) -o $(BINDIR)/$(TARGET) $(OBJS)

# # Rule để tạo các file object (.o) trong thư mục bin từ file source (.cpp)
# $(BINDIR)/%.o: $(SRCDIR)/%.cpp | $(BINDIR)
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Rule để dọn dẹp các file biên dịch
# clean:
# 	rm -f $(BINDIR)/*.o $(BINDIR)/$(TARGET)

# # Rule để chạy chương trình từ thư mục bin
# run: all
# 	./$(BINDIR)/$(TARGET)

# Tên file thực thi
TARGET = main

# Thư mục chứa header và source files
HEADER_DIR = Inc
SOURCE_DIR = Src
BINARY_DIR = Bin

# Các tệp nguồn và tệp object tương ứng
SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SOURCE_DIR)/%.cpp=$(BINARY_DIR)/%.o)

# Trình biên dịch và các cờ
CC = g++
CFLAGS = -I$(HEADER_DIR) -Wall -Wextra

# Quy tắc đầu tiên là quy tắc mặc định sẽ được thực thi
all: $(BINARY_DIR)/$(TARGET)	# make

# Tạo thư mục bin nếu chưa tồn tại
$(BINARY_DIR):
	mkdir -p $(BINARY_DIR)

# Quy tắc để tạo ra tệp thực thi
$(BINARY_DIR)/$(TARGET): $(OBJECTS) | $(BINARY_DIR)
	$(CC) -o $@ $^

# Quy tắc để biên dịch các tệp .c thành .o
$(BINARY_DIR)/%.o: $(SOURCE_DIR)/%.cpp | $(BINARY_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Quy tắc để làm sạch thư mục build
clean:
	rm -f $(BINARY_DIR)/*.o $(BINARY_DIR)/$(TARGET)

run: $(BINARY_DIR)/$(TARGET)
	./$(BINARY_DIR)/$(TARGET)

# Quy tắc giả (phony target)
.PHONY: all