DPCPP_CXX = dpcpp
DPCPP_CXXFLAGS = -std=c++17 -g -o
DPCPP_EXE_NAME = bilinear_quad_dpc
DPCPP_SOURCES = bilinear_quad.cpp

CXX = icpx

all:
	$(DPCPP_CXX) $(DPCPP_CXXFLAGS) $(DPCPP_EXE_NAME) $(DPCPP_SOURCES)
run:
	./$(DPCPP_EXE_NAME)
clean:
	rm -rf $(DPCPP_EXE_NAME)