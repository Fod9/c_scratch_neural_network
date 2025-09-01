CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I. -Ilayers -Imlp
TARGET = main
SRCDIR = .

# Trouve automatiquement tous les fichiers .c
SOURCES = $(shell find $(SRCDIR) -name "*.c")
OBJECTS = $(SOURCES:.c=.o)

# Règle principale : crée l'exécutable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Règle générique : compile chaque .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoie les fichiers compilés
clean:
	find . -name "*.o" -delete
	rm -f $(TARGET)

# Recompile tout depuis zéro
rebuild: clean $(TARGET)

.PHONY: clean rebuild