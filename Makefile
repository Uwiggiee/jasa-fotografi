# Compiler yang mau dipakai
CXX = g++

# Flag/opsi compiler (ini yang bikin program kamu lebih aman & bisa kasih warning)
CXXFLAGS = -Wall -std=c++17

# Direktori include buat header files (.h)
INCLUDES = -I./include

# Nama program hasil compile-an
TARGET = booking_system

# Daftar semua source files
SOURCES = $(wildcard src/*.cpp)

# Daftar object files (dibuat dari source files)
OBJECTS = $(SOURCES:.cpp=.o)

# Perintah default yang dijalankan waktu ketik 'make'
all: $(TARGET)

# Aturan buat bikin program akhir
$(TARGET): $(OBJECTS)
    $(CXX) $(OBJECTS) -o $(TARGET)

# Aturan buat compile source files jadi object files
%.o: %.cpp
    $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Buat bersihin file hasil compile (object files dan program)
clean:
    rm -f $(OBJECTS) $(TARGET)

# Buat ngerun program
run: $(TARGET)
    ./$(TARGET)