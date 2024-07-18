CC=gcc
TARGET=pipe
NUM=50

all:main.c
	$(CC) main.c -o $(TARGET)

run:$(TARGET)
	@echo "Iniciando o Programa com input numérico de: $(NUM)\n\n"
	./$(TARGET) $(NUM)

