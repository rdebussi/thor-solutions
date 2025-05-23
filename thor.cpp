#include <iostream>
#include <windows.h>
#include <string>
#include <map>
#include <functional>

using namespace std;

class ThorSystem {
private:
    map<int, pair<string, function<void()>>> options;
    
    // Cores para console
    void setConsoleColor(int color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }
    
    // Cabeçalho estilizado
    void displayHeader() {
        setConsoleColor(12); // Vermelho brilhante
        cout << "\n";
        cout << "  ████████╗██╗  ██╗ ██████╗ ██████╗ \n";
        cout << "  ╚══██╔══╝██║  ██║██╔═══██╗██╔══██╗\n";
        cout << "     ██║   ███████║██║   ██║██████╔╝\n";
        cout << "     ██║   ██╔══██║██║   ██║██╔══██╗\n";
        cout << "     ██║   ██║  ██║╚██████╔╝██║  ██║\n";
        cout << "     ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝\n";
        
        setConsoleColor(14); // Amarelo brilhante
        cout << "\n    Sistema de Suporte Técnico v4.0\n";
        cout << "      Desenvolvido por Rafael Debussi    \n\n";
    }
    
    // Menu principal estilizado
    void displayMenu() {
        setConsoleColor(11); // Ciano brilhante
        cout << "╔═══════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                   MENU PRINCIPAL                             ║\n";
        cout << "╠═══════════════════════════════════════════════════════════════════════════════╣\n";
        
        setConsoleColor(15); // Branco brilhante
        for (const auto& option : options) {
            cout << "║ ";
            setConsoleColor(10); // Verde brilhante
            cout << "[" << option.first << "]";
            setConsoleColor(15); // Branco
            cout << " " << option.second.first;
            
            // Preencher espaços para alinhar
            int spaces = 73 - option.second.first.length();
            for (int i = 0; i < spaces; i++) cout << " ";
            cout << "║\n";
        }
        
        setConsoleColor(11); // Ciano
        cout << "╚═══════════════════════════════════════════════════════════════════════════════╝\n";
        
        setConsoleColor(14); // Amarelo
        cout << "\n➤ Digite sua opção: ";
        setConsoleColor(15); // Branco
    }
    
    // Executar comando com feedback
    void executeCommand(const string& command, const string& description) {
        setConsoleColor(13); // Magenta brilhante
        cout << "\n╔═══════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ EXECUTANDO: " << description;
        int spaces = 65 - description.length();
        for (int i = 0; i < spaces; i++) cout << " ";
        cout << "║\n";
        cout << "╚═══════════════════════════════════════════════════════════════════════════════╝\n";
        
        setConsoleColor(11); // Ciano
        cout << "\n⚡ Comando: " << command << "\n\n";
        
        setConsoleColor(14); // Amarelo
        cout << "Executando comando...";
        
        int result = system(command.c_str());
        
        if (result == 0) {
            setConsoleColor(10); // Verde
            cout << " ✓ SUCESSO!\n";
        } else {
            setConsoleColor(12); // Vermelho
            cout << " ✗ ERRO (Código: " << result << ")\n";
        }
        
        setConsoleColor(15); // Branco
        // Removido o cin.ignore() e cin.get() daqui
    }
    
    // Pausar com estilo e opção de continuar
    bool pauseWithOptions() {
        setConsoleColor(8); // Cinza
        cout << "\n" << string(79, '-') << "\n";
        
        setConsoleColor(10); // Verde brilhante
        cout << "╔═══════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                           COMANDO EXECUTADO COM SUCESSO                       ║\n";
        cout << "╚═══════════════════════════════════════════════════════════════════════════════╝\n";
        
        setConsoleColor(14); // Amarelo
        cout << "\n➤ Deseja executar outro comando? ";
        setConsoleColor(11); // Ciano
        cout << "[S/N]: ";
        setConsoleColor(15); // Branco
        
        char choice;
        cin >> choice;
        
        // Converter para maiúscula
        choice = toupper(choice);
        
        if (choice == 'S' || choice == 'Y') {
            return true; // Continuar executando comandos
        } else {
            setConsoleColor(12); // Vermelho
            cout << "\n╔═══════════════════════════════════════════════════════════════════════════════╗\n";
            cout << "║                           ENCERRANDO SISTEMA THOR                         ║\n";
            cout << "║                          Obrigado por utilizar!                           ║\n";
            cout << "╚═══════════════════════════════════════════════════════════════════════════╝\n";
            setConsoleColor(15);
            return false; // Sair do programa
        }
    }

public:
    ThorSystem() {
        // Configurar opções do sistema com suas soluções específicas
        options[0] = {"Adicionar Impressora", [this]() {
            executeCommand("rundll32 printui.dll,PrintUIEntry /in /n \"\\\\200.131.55.200\\impressao\"", 
                          "Adicionando Impressora de Rede");
        }};
        
        options[1] = {"Corrigir Erro 0x00000709", [this]() {
            executeCommand("reg add \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Policies\\Microsoft\\Windows NT\\Printers\\RPC\" /v RpcUseNamedPipeProtocol /t REG_DWORD /d 1 /f", 
                          "Alterando Políticas de Grupo - RPC");
        }};
        
        options[2] = {"Corrigir Erro 0x0000011b (Reboot)", [this]() {
            executeCommand("reg add \"HKLM\\System\\CurrentControlSet\\Control\\Print\" /v RpcAuthnLevelPrivacyEnabled /t REG_DWORD /d 0 /f && shutdown /r /t 5 /f", 
                          "Alterando Registry e Reiniciando Sistema");
        }};
        
        options[3] = {"Instalar GPEDIT.MSC", [this]() {
            // Comando complexo executado em etapas
            setConsoleColor(13);
            cout << "\n╔═══════════════════════════════════════════════════════════════════════════════╗\n";
            cout << "║ INSTALANDO GPEDIT.MSC - Editor de Política de Grupo                          ║\n";
            cout << "╚═══════════════════════════════════════════════════════════════════════════════╝\n";
            
            setConsoleColor(11);
            cout << "\n⚡ Executando instalação de pacotes...\n";
            
            // Executar comandos DISM sequencialmente
            int result1 = system("FOR %F IN (\"%SystemRoot%\\servicing\\Packages\\Microsoft-Windows-GroupPolicy-ClientTools-Package~*.mum\") DO (DISM /Online /NoRestart /Add-Package:\"%F\")");
            int result2 = system("FOR %F IN (\"%SystemRoot%\\servicing\\Packages\\Microsoft-Windows-GroupPolicy-ClientExtensions-Package~*.mum\") DO (DISM /Online /NoRestart /Add-Package:\"%F\")");
            
            if (result1 == 0 && result2 == 0) {
                setConsoleColor(10);
                cout << "✓ GPEDIT.MSC instalado com sucesso!\n";
            } else {
                setConsoleColor(12);
                cout << "✗ Erro na instalação do GPEDIT.MSC\n";
            }
            setConsoleColor(15);
            // Removido cin.ignore() e cin.get() daqui também
        }};
        
        options[4] = {"Instalar NDD Print", [this]() {
            setConsoleColor(13);
            cout << "\n╔═══════════════════════════════════════════════════════════════════════════════╗\n";
            cout << "║ INSTALANDO NDD PRINT AGENT                                                   ║\n";
            cout << "╚═══════════════════════════════════════════════════════════════════════════════╝\n";
            
            setConsoleColor(11);
            cout << "\n⚡ Mapeando unidade de rede...\n";
            system("net use Z: /delete 2>nul");
            
            int mapResult = system("net use Z: \"\\\\200.131.55.200\\Drivers e Manuais\\Print Agent\"");
            if (mapResult == 0) {
                setConsoleColor(10);
                cout << "✓ Unidade mapeada com sucesso!\n";
                setConsoleColor(14);
                cout << "🚀 Iniciando instalação via rede...\n";
                system("start Z:\\nddPrintAgentSetup-x64_5.24.1.msi");
                setConsoleColor(10);
                cout << "✓ Instalador iniciado!\n";
            } else {
                setConsoleColor(12);
                cout << "✗ Erro ao mapear unidade de rede\n";
            }
            setConsoleColor(15);
            // Removido cin.ignore() e cin.get() daqui também
        }};
        
        options[5] = {"Servidor pedindo Usuario/Senha", [this]() {
            executeCommand("reg add \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Policies\\Microsoft\\Windows NT\\Printers\\RPC\" /v RpcUseNamedPipeProtocol /t REG_DWORD /d 1 /f", 
                          "Alterando Políticas de Grupo - Autenticação RPC");
        }};
        
        options[6] = {"Atualizar Office", [this]() {
            setConsoleColor(13);
            cout << "\n╔═══════════════════════════════════════════════════════════════════════════════╗\n";
            cout << "║ ATUALIZANDO MICROSOFT OFFICE                                                  ║\n";
            cout << "╚═══════════════════════════════════════════════════════════════════════════════╝\n";
            
            setConsoleColor(11);
            cout << "\n⚡ Navegando para diretório do Office...\n";
            system("cd \"C:\\Program Files\\Common Files\\Microsoft Shared\\ClickToRun\"");
            
            setConsoleColor(14);
            cout << "🔄 Iniciando atualização do Office...\n";
            int result = system("\"C:\\Program Files\\Common Files\\Microsoft Shared\\ClickToRun\\OfficeC2RClient.exe\" /update user updatetoversion=16.0.13801.20266");
            
            if (result == 0) {
                setConsoleColor(10);
                cout << "✓ Comando de atualização executado com sucesso!\n";
            } else {
                setConsoleColor(12);
                cout << "✗ Erro na execução da atualização\n";
            }
            setConsoleColor(15);
            // Removido cin.ignore() e cin.get() daqui também
        }};
        
        options[7] = {"Erro pasta compartilhada (gpedit.msc)", [this]() {
            executeCommand("reg add \"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\LanmanWorkstation\\Parameters\" /v \"AllowInsecureGuestAuth\" /t REG_DWORD /d 1 /f", 
                          "Alterando Políticas do Sistema - LanmanWorkstation");
        }};
        
        options[8] = {"Impressora em Rede - Acesso Negado", [this]() {
            executeCommand("icacls \"%systemroot%\\System32\\spool\\PRINTERS\" /grant \"Todos:(OI)(CI)F\" /t /c", 
                          "Concedendo Permissões para Pasta PRINTERS");
        }};
        
        options[9] = {"Sair do Sistema", [this]() {
            setConsoleColor(12); // Vermelho
            cout << "\n╔═══════════════════════════════════════════════════════════════════════════════╗\n";
            cout << "║                           ENCERRANDO SISTEMA THOR                         ║\n";
            cout << "║                          Obrigado por utilizar!                           ║\n";
            cout << "╚═══════════════════════════════════════════════════════════════════════════════╝\n";
            setConsoleColor(15);
            exit(0);
        }};
    }
    
    void run() {
        // Configurar console
        system("chcp 65001 > nul"); // UTF-8
        system("title Thor - Sistema de Suporte Técnico");
        
        while (true) {
            system("cls");
            displayHeader();
            displayMenu();
            
            int choice;
            cin >> choice;
            
            if (options.find(choice) != options.end()) {
                if (choice == 9) {
                    // Executar opção de saída diretamente
                    options[choice].second();
                    break;
                } else {
                    // Executar comando e perguntar se quer continuar
                    options[choice].second();
                    
                    // Perguntar se quer executar outro comando
                    if (!pauseWithOptions()) {
                        break; // Sair do loop principal
                    }
                    // Se retornou true, continua o loop e mostra o menu novamente
                }
            } else {
                setConsoleColor(12); // Vermelho
                cout << "\n✗ Opção inválida! Tente novamente.\n";
                setConsoleColor(14); // Amarelo
                cout << "\nPressione ENTER para continuar...";
                setConsoleColor(15); // Branco
                cin.ignore();
                cin.get();
            }
        }
    }
};

int main() {
    try {
        ThorSystem thor;
        thor.run();
    } catch (const exception& e) {
        cout << "Erro crítico: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}