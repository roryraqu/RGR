CXX = g++
CXXFLAGS = -std=c++17 -fPIC
LDFLAGS = -shared

PKG_DIR = package
SRC_DIR = ../src
LIB_DIR = ../lib
BIN = cipher

all: $(PKG_DIR)/bin/cipher \
	$(PKG_DIR)/lib/libmatrix.so \
	$(PKG_DIR)/lib/libgronsfeld.so \
	$(PKG_DIR)/lib/libpolibius.so

$(PKG_DIR)/bin/cipher: $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -I$(LIB_DIR)/general -I$(LIB_DIR)/passwd $< $(LIB_DIR)/general/general.cpp $(LIB_DIR)/passwd/passwd.cpp -o $@

$(PKG_DIR)/lib/libmatrix.so: $(LIB_DIR)/matrix/matrix.cpp $(LIB_DIR)/matrix/matrix.h $(LIB_DIR)/general/general.cpp $(LIB_DIR)/general/general.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(LIB_DIR)/matrix/matrix.cpp $(LIB_DIR)/general/general.cpp

$(PKG_DIR)/lib/libgronsfeld.so: $(LIB_DIR)/gronsfeld/gronsfeld.cpp $(LIB_DIR)/gronsfeld/gronsfeld.h $(LIB_DIR)/general/general.cpp $(LIB_DIR)/general/general.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(LIB_DIR)/gronsfeld/gronsfeld.cpp $(LIB_DIR)/general/general.cpp

$(PKG_DIR)/lib/libpolibius.so: $(LIB_DIR)/polibius/polibius.cpp $(LIB_DIR)/polibius/polibius.h $(LIB_DIR)/general/general.cpp $(LIB_DIR)/general/general.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(LIB_DIR)/polibius/polibius.cpp $(LIB_DIR)/general/general.cpp