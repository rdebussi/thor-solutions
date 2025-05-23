# ============================================================================
# THOR SYSTEM - Makefile Otimizado para Compilação Estática
# ============================================================================

# Configurações do projeto
PROJECT_NAME = thor
TARGET = $(PROJECT_NAME)
SRC = thor.cpp
VERSION = 2.0

# Configurações do compilador
CXX = g++
WINDRES = windres

# Flags de compilação otimizadas para distribuição estática
CXXFLAGS = -std=c++17 \
           -static \
           -static-libgcc \
           -static-libstdc++ \
           -Wall \
           -Wextra \
           -O3 \
           -DNDEBUG \
           -ffunction-sections \
           -fdata-sections \
           -march=native \
           -mtune=native

# Flags do linker para otimização de tamanho
LDFLAGS = -static \
          -static-libgcc \
          -static-libstdc++ \
          -Wl,--gc-sections \
          -Wl,--strip-all \
          -s

# Bibliotecas necessárias
LIBS = -lkernel32 -luser32 -lgdi32

# Arquivos de recursos (opcional)
RC_FILE = resource.rc
RES_FILE = resource.o

# Detectar sistema operacional
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    EXE_EXT := .exe
    RM_CMD := del /Q
    MKDIR_CMD := mkdir
else
    DETECTED_OS := $(shell uname -s)
    EXE_EXT := 
    RM_CMD := rm -f
    MKDIR_CMD := mkdir -p
endif

# Diretórios
BUILD_DIR = build
DIST_DIR = dist

# ============================================================================
# REGRAS PRINCIPAIS
# ============================================================================

# Regra padrão
all: info $(TARGET)

# Informações do build
info:
	@echo ============================================================================
	@echo THOR SYSTEM v$(VERSION) - Build Configuration
	@echo ============================================================================
	@echo OS Detectado: $(DETECTED_OS)
	@echo Compilador: $(CXX)
	@echo Arquivo fonte: $(SRC)
	@echo Target: $(TARGET)$(EXE_EXT)
	@echo ============================================================================

# Compilação principal
$(TARGET): $(SRC)
	@echo [BUILD] Compilando $(TARGET)...
	$(CXX) $(CXXFLAGS) -o $(TARGET)$(EXE_EXT) $(SRC) $(LDFLAGS) $(LIBS)
	@echo [SUCCESS] Compilacao concluida: $(TARGET)$(EXE_EXT)

# Compilação com recursos (Windows)
# Compilação com recursos (Windows)
$(TARGET)-with-resources: $(SRC) $(RES_FILE)
	@echo [BUILD] Compilando $(TARGET) com recursos...
	$(WINDRES) $(RC_FILE) -O coff -o resource.o
	$(CXX) $(CXXFLAGS) -o $(TARGET)$(EXE_EXT) $(SRC) resource.o $(LDFLAGS) $(LIBS)
	@echo [SUCCESS] Compilacao com recursos concluida: $(TARGET)$(EXE_EXT)


# Compilar arquivo de recursos
$(RES_FILE): $(RC_FILE)
	@echo [RES] Compilando recursos...
	$(WINDRES) $(RC_FILE) -O coff -o $(RES_FILE)

# ============================================================================
# BUILDS ESPECIAIS
# ============================================================================

# Build de debug
debug: CXXFLAGS = -std=c++17 -static -static-libgcc -static-libstdc++ -Wall -Wextra -g -DDEBUG -O0
debug: LDFLAGS = -static -static-libgcc -static-libstdc++
debug: $(TARGET)
	@echo [DEBUG] Build de debug concluido

# Build otimizado para tamanho
tiny: CXXFLAGS += -Os -fno-exceptions -fno-rtti
tiny: $(TARGET)
	@echo [TINY] Build otimizado para tamanho concluido

# Build para distribuição
release: clean $(TARGET) strip package
	@echo [RELEASE] Build de release concluido

# ============================================================================
# UTILITÁRIOS
# ============================================================================

# Otimizar executável (strip)
strip:
ifeq ($(DETECTED_OS),Windows)
	@echo [STRIP] Removendo símbolos de debug...
	strip --strip-all $(TARGET)$(EXE_EXT)
else
	@echo [STRIP] Strip não disponível nesta plataforma
endif

# Verificar dependências
check-deps:
	@echo [CHECK] Verificando dependências...
	@ldd $(TARGET)$(EXE_EXT) 2>/dev/null || echo "Executável estático - sem dependências externas"

# Verificar tamanho do executável
size:
	@echo [SIZE] Tamanho do executável:
ifeq ($(DETECTED_OS),Windows)
	@dir $(TARGET)$(EXE_EXT) | findstr $(TARGET)
else
	@ls -lh $(TARGET)$(EXE_EXT)
endif

# Teste rápido
test: $(TARGET)
	@echo [TEST] Executando teste básico...
	@echo 9 | $(TARGET)$(EXE_EXT)

# ============================================================================
# EMPACOTAMENTO E DISTRIBUIÇÃO
# ============================================================================

# Criar diretório de distribuição
$(DIST_DIR):
	$(MKDIR_CMD) $(DIST_DIR)

# Empacotar para distribuição
package: $(DIST_DIR)
	@echo [PACKAGE] Criando pacote de distribuição...
	copy $(TARGET)$(EXE_EXT) $(DIST_DIR)\
	@echo Executável copiado para $(DIST_DIR)/

# Criar instalador (se disponível)
installer: package
	@echo [INSTALLER] Criando instalador...
	@echo "Instalador não implementado ainda"

# ============================================================================
# LIMPEZA
# ============================================================================

# Limpeza básica
clean:
	@echo [CLEAN] Removendo arquivos temporários...
ifeq ($(DETECTED_OS),Windows)
	$(RM_CMD) $(TARGET)$(EXE_EXT) 2>NUL || echo.
	$(RM_CMD) $(RES_FILE) 2>NUL || echo.
	$(RM_CMD) *.o 2>NUL || echo.
else
	$(RM_CMD) $(TARGET)$(EXE_EXT)
	$(RM_CMD) $(RES_FILE)
	$(RM_CMD) *.o
endif

# Limpeza completa
distclean: clean
	@echo [DISTCLEAN] Limpeza completa...
ifeq ($(DETECTED_OS),Windows)
	rmdir /S /Q $(BUILD_DIR) 2>NUL || echo.
	rmdir /S /Q $(DIST_DIR) 2>NUL || echo.
else
	$(RM_CMD) -rf $(BUILD_DIR)
	$(RM_CMD) -rf $(DIST_DIR)
endif

# ============================================================================
# AJUDA E INFORMAÇÕES
# ============================================================================

# Mostrar ajuda
help:
	@echo ============================================================================
	@echo THOR SYSTEM - Makefile Help
	@echo ============================================================================
	@echo Targets disponíveis:
	@echo.
	@echo   all              - Build padrão (otimizado)
	@echo   debug            - Build com símbolos de debug
	@echo   tiny             - Build otimizado para tamanho mínimo
	@echo   release          - Build completo para distribuição
	@echo   strip            - Remove símbolos de debug do executável
	@echo   check-deps       - Verifica dependências do executável
	@echo   size             - Mostra o tamanho do executável
	@echo   test             - Executa teste básico
	@echo   package          - Cria pacote para distribuição
	@echo   clean            - Remove arquivos temporários
	@echo   distclean        - Limpeza completa
	@echo   help             - Mostra esta ajuda
	@echo.
	@echo Exemplos de uso:
	@echo   make             - Compilação padrão
	@echo   make debug       - Compilação para debug
	@echo   make release     - Build completo para distribuição
	@echo   make clean       - Limpeza dos arquivos gerados
	@echo ============================================================================

# Mostrar informações do sistema
sysinfo:
	@echo ============================================================================
	@echo INFORMAÇÕES DO SISTEMA
	@echo ============================================================================
	@echo OS: $(DETECTED_OS)
	@echo Compilador: $(shell $(CXX) --version | head -n1)
	@echo Make: $(shell make --version | head -n1)
ifeq ($(DETECTED_OS),Windows)
	@echo Arquitetura: $(PROCESSOR_ARCHITECTURE)
else
	@echo Arquitetura: $(shell uname -m)
endif
	@echo ============================================================================

# ============================================================================
# REGRAS ESPECIAIS
# ============================================================================

# Prevenir conflitos com arquivos de mesmo nome
.PHONY: all clean distclean help info debug tiny release strip check-deps size test package installer sysinfo

# Manter arquivos intermediários importantes
.PRECIOUS: $(RES_FILE)