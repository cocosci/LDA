CC = g++
MAIN = final

ALLCPP = test.cpp dataset.cpp lda.cpp
$(MAIN): $(ALLCPP)
	$(CC) -o $(MAIN) $(ALLCPP) -I.
