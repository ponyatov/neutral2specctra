SRC = WPx5_neutral.txt
log.log: $(SRC) ./exe.exe
	./exe.exe < $< > $@ && tail $@
C = lex.yy.c
./exe.exe: $(C)
	$(CXX) -o $@ $(C)
lex.yy.c: lpp.lpp
	flex $<
