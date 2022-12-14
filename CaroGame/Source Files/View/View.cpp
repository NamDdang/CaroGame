#include "../../Header Files/View/View.h"
#include <windows.h>
#include <iostream>
#include <conio.h>
using namespace std;
void View::SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    //We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
void View::prompt(string s)
{
    cout << s;
}
void View::prompt(string s, int Color)
{
    SetColor(Color);
    cout << s;
}
void View::screenGetCommand(char& command)
{
    cin >> command;
}
char* InputStringName(const int k)
{
    char* kq = new char[k + 1]; // tao mang
    int n, index = 0;
    do
    {
    loop:;
        n = _getch(); // lay ma ASCII
        // Neu thuoc 0-9, A-Z, a-z hoac dau '.' va chuoi đang co it hon k ky tu thi cho phep
        if (((n >= '0' && n <= '9') || (n >= 'A' && n <= 'Z') || (n >= 'a' && n <= 'z') || n == '.') && index < k)
        {
            cout << char(n); // xuat ky tu do ra man hinh
            kq[index++] = n; // Luu vao mang
        }
        else if (n == '\b' && index > 0) // Neu nhan dau BackSpace ma chuoi khong rong
        {
            cout << "\b \b"; // Xoa 1 ky tu tren man hinh
            kq[--index] = 0; // Xoa 1 ky tu trong chuoi kq
        }
        if (n == 13 && index == 0) goto loop; // Neu nhan Enter ma chua nhap gi thi khong cho phep
    } while (n != 13); // Cu lap lai trong khi chua nhap Enter

    kq[index] = 0; // Ket thuc chuoi
    cout << '\n';
    return kq;
}
void View::screenGetStringName(string& name)
{
    name = InputStringName(8);
}
bool isIPAddress(string ip)
{
    int count = 0;
    for (int i = 0; i < ip.size(); i++)
    {
        if ((ip[i] < '0' || ip[i] > '9') && ip[i] != '.')
        {
            return false;
        }
        if (ip[i] == '.')
        {
            count++;
            if (i == 0) return false;
            if (i >= 1 && ip[i - 1] == '.') return false;
            if (i == 2 && ip[i - 2] == '0') return false;
            if (i >= 3 && ip[i - 1] == '0' && ip[i - 2] == '0' && ip[i - 3] != '1' && ip[i - 3] != '2') return false;
            if (i >= 3 && ip[i - 1] >= '6' && ip[i - 1] <= '9' && ip[i - 2] == '5' && ip[i - 3] == '2') return false;
            if (i >= 3 && ip[i - 2] >= '6' && ip[i - 2] <= '9' && ip[i - 3] == '2') return false;
            if (i >= 4 && ip[i - 1] != '.' && ip[i - 2] != '.' && ip[i - 3] != '.' && ip[i - 4] != '.') return false;
        }
        if (count > 0) // Tranh truy cap ra ngoai mang string
        {
            if (i == ip.size() - 1)
            {
                if (ip[i] == '.') return false;
                if (ip[i] == '0' && ip[i - 1] == '0' && ip[i - 2] != '1' && ip[i - 2] != '2') return false;
                if (ip[i] >= '6' && ip[i] <= '9' && ip[i - 1] == '5' && ip[i - 2] == '2') return false;
                if (ip[i - 1] >= '6' && ip[i - 1] <= '9' && ip[i - 2] == '2') return false;
                if (ip[i] != '.' && ip[i - 1] != '.' && ip[i - 2] != '.' && ip[i - 3] != '.') return false;
            }
        }
    }
    if (count != 3) return false;
    return true;
}
void View::screenGetIPAddress(string &ipAddress)
{
    prompt("(Input \"localhost\" if server is working on your PC)\n", YELLOW);
    do
    {
        prompt("Input server's ip address: ", WHITE);
        ipAddress = InputStringName(15);
        if (ipAddress == "localhost") ipAddress = "127.0.0.1";
        if (!isIPAddress(ipAddress))
        {
            prompt("Invalid ip address.\n", YELLOW);
        }
    } while (!isIPAddress(ipAddress));
}
void View::DrawBoard(Board* board)
{
    for (int y = -1; y <= board->getSize() - 1; y++) // row
    {
        for (int x = -1; x <= board->getSize(); x++) // col
        {
            if (y == -1)
            {
                if (x == -1) cout << "   ";
                else if (x >= 0 && x <= board->getSize() - 1)
                {
                    SetColor(RED);
                    cout << "  " << x << " ";
                }
            }
            if (y >= 0 && y <= board->getSize() - 1)
            {
                if (x == -1)
                {
                    SetColor(RED);
                    cout << " " << y << " ";
                }
                else if (x >= 0 && x <= board->getSize() - 1)
                {
                    SetColor(YELLOW);
                    cout << "| ";
                    if (board->GetXO(x, y) == VX)
                    {
                        SetColor(P1);
                        cout << 'X';
                    }
                    else if (board->GetXO(x, y) == VO)
                    {
                        SetColor(P2);
                        cout << 'O';
                    }
                    else
                    {
                        cout << ' ';
                    }
                    SetColor(YELLOW);
                    cout << " ";
                }
                else cout << "|";
            }
        }
        cout << endl;
        for (int x = -1; x <= board->getSize(); x++)
        {
            if (x == -1) cout << "   ";
            else if (x >= 0 && x <= board->getSize() - 1)
            {
                SetColor(YELLOW);
                cout << "|---";
            }
            else cout << "|";
        }
        cout << endl;
    }
}
void View::DrawGameScreen(Game* game)
{
    prompt("=> ", YELLOW);
    prompt("Player ", WHITE);
    prompt(game->GetPlayer1().GetName() + " ", P1);
    prompt("= ", YELLOW);
    prompt("X", WHITE);
    prompt(", ", YELLOW);
    prompt("Player ", WHITE);
    prompt(game->GetPlayer2().GetName() + " ", P2);
    prompt("= ", YELLOW);
    prompt("O", WHITE);
    prompt(": \n", YELLOW);
    DrawBoard(game->GetBoard());
}
void View::MenuHeader(int header)
{
    prompt("*-------", YELLOW);
    switch (header)
    {
    case MAIN_MENU:
        prompt("MAIN MENU", WHITE);
        break;
    case PLAY_WITH_OTHER:
        prompt("Play with other", WHITE);
        break;
    case REPLAY:
        prompt("Replay", WHITE);
        break;
    case PLAYER_INFORMATION:
        prompt("Players's Information", WHITE);
        break;
    case SHOW_ALL_PLAYER:
        prompt("Players's Records", WHITE);
        break;
    case SEARCH_PLAYER_BY_NAME:
        prompt("Search Player by Name", WHITE);
        break;
    case GUIDE:
        prompt("Guide", WHITE);
        break;
    case PLAY_ONLINE:
        prompt("Play online", WHITE);
        break;
    case USER_INFORMATION:
        prompt("User's Information", WHITE);
        break;
    default:
        break;
    }
    prompt("-------*\n", YELLOW);
}
void View::MainMenu()
{
    prompt("1.New ", RED);
    prompt("game \n", WHITE);
    prompt("2.Replay\n", RED);
    prompt("3.Player's ", RED);
    prompt("Information\n", WHITE);
    prompt("4.Play ", RED);
    prompt("online\n", WHITE);
    prompt("5.Guide\n", RED);
    prompt("6.Exit\n", RED);
    prompt("Press number to choice:", WHITE);
}
void View::GameOverMenu()
{
    prompt("Do you want to play again?\n", YELLOW);
    prompt("1.Play ", RED);
    prompt("again\n", WHITE);
    prompt("2.Back ", RED);
    prompt("to MAIN MENU\n", WHITE);
    prompt("Press number to choice:", WHITE);
}
void View::AskToSaveReplay()
{
    prompt("Do you want to save replay?\n", YELLOW);
    prompt("1.Yes\n", WHITE);
    prompt("2.No\n", WHITE);
    prompt("Press number to choice:", WHITE);
}
void View::Replay()
{
    prompt("1.Replay ", RED);
    prompt("again\n", WHITE);
    prompt("2.Choose ", RED);
    prompt("another replay\n", WHITE);
    prompt("3.Back ", RED);
    prompt("to MAIN MENU\n", WHITE);
    prompt("Press number to choice:", WHITE);
}
void View::PlayerInfomationMenu()
{
    prompt("1.Show ", RED);
    prompt("All Player\n", WHITE);
    prompt("2.Search ", RED);
    prompt("player by Name\n", WHITE);
    prompt("3.Back ", RED);
    prompt("to MAIN MENU\n", WHITE);
    prompt("Press number to choice:", WHITE);
}
void View::ShowAllPlayer()
{
    prompt("1.Back ", RED);
    prompt("to Player's Infomation\n", WHITE);
    prompt("2.Back ", RED);
    prompt("to MAIN MENU\n", WHITE);
    prompt("Press number to choice:", WHITE);
}
void View::SearchPlayerByName()
{
    prompt("1.Continue ", RED);
    prompt("Search\n", WHITE);
    prompt("2.Back ", RED);
    prompt("to Player's Infomation\n", WHITE);
    prompt("3.Back ", RED);
    prompt("to MAIN MENU\n", WHITE);
    prompt("Press number to choice:", WHITE);
}
void View::Guide()
{
    SetColor(WHITE);
    prompt("*Trong qua trinh choi, ban lan luot nhap toa do vi tri muon danh = (so dong, so cot)\n");
    prompt("*Ban khong duoc nhap vao vi tri da duoc danh dau hoac ngoai pham vi ban co, neu nhap sai se phai nhap lai\n");
    prompt("*Dieu kien de chien thang tro choi la ben nao co duoc 4 quan co lien tiep theo duong cheo, hang ngang hay \ncot doc truoc va chi bi chan mot dau\n");
    prompt(" VD: XXXX -> Win\n");
    prompt("     OXXXX -> Win\n");
    prompt("     OXXXXO -> NO Win\n");
    prompt("     OXXXX O -> Win\n");
    prompt("*Neu ma tat ca cac o bi danh dau het ma chua co nguoi thang thi 2 nguoi choi se hoa nhau\n");
    prompt("*Tro choi se chi dung lai khi mot trong hai nguoi choi thang hoac ca hai hoa nhau\n");
    prompt("*Thank you! Chuc ban choi vui(^_^)\n");
    prompt("1.Back ", RED);
    prompt("to MAIN MENU\n", WHITE);
    prompt("Press number to choice:", WHITE);
}
void View::PlayOnline()
{
    prompt("1.Login\n", RED);
    prompt("2.Register\n", RED);
    prompt("3.Back ", RED);
    prompt("to MAIN MENU\n", WHITE);
    prompt("Press number to choice:", WHITE);
}
void View::PlayOnlineAfterLogin()
{
    prompt("1.Play ", RED);
    prompt("as Server\n", WHITE);
    prompt("2.Play ", RED);
    prompt("as Client\n", WHITE);
    prompt("3.User's ", RED);
    prompt("Information\n", WHITE);
    prompt("4.Back ", RED);
    prompt("to MAIN MENU\n", WHITE);
    prompt("Press number to choice:", WHITE);
}