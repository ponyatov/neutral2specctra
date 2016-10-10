SRC = WPx5_neutral.txt
log.log: $(SRC) ./exe.exe
	./exe.exe < $< > $@ && tail $@
C = cpp.cpp ypp.tab.cpp lex.yy.c
H = hpp.hpp ypp.tab.hpp
CXXFLAGS += -std=gnu++11
./exe.exe: $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C)
lex.yy.c: lpp.lpp
	flex $<
ypp.tab.cpp: ypp.ypp
	bison $<
