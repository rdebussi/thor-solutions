# 🔧 ThorSystem - Sistema de Suporte Técnico v4.0

> Desenvolvido por **Rafael Debussi**

ThorSystem é uma aplicação em C++ para automação de tarefas comuns de suporte técnico em ambientes Windows. Com uma interface em console estilizada, o sistema permite executar comandos administrativos como instalação de impressoras, correção de erros de registro, instalação de pacotes do sistema e outros, de forma rápida e amigável.

---

## ✨ Funcionalidades

- 📠 Adicionar impressora de rede automaticamente.
- 🔧 Corrigir erros comuns como `0x00000709` e `0x0000011b`.
- ⚙️ Alterar configurações de registro do Windows com comandos automatizados.
- 🖥️ Instalar o editor de políticas de grupo (`gpedit.msc`) em versões do Windows que não o incluem por padrão.
- 📦 Instalar o NDD Print Agent diretamente da rede.
- 🛡️ Corrigir problema de autenticação do servidor com RPC.
- 📥 Atualizar o Microsoft Office.

---

## 🧱 Estrutura do Projeto

- Interface estilizada com uso de **cores no console Windows** (via `SetConsoleTextAttribute`).
- Uso de **funções lambda** para acoplamento de comandos a menus.
- Comandos de sistema são executados com feedback visual.
- Design modular com classe `ThorSystem`.

---

## 🖥️ Requisitos

- Sistema Operacional: **Windows**
- Compilador C++ com suporte à biblioteca **Windows.h** (ex: MSVC, MinGW)
- Permissões de administrador (para que comandos funcionem corretamente)

---

## ▶️ Como Compilar

1. **Abra seu compilador C++ com suporte a Windows API**.
2. Compile com um comando como:

   ```bash
   g++ -o ThorSystem.exe main.cpp
