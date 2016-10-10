SRC = WPx5_neutral.txt
log.log: $(SRC)
	cp $< $@ && tail $@
