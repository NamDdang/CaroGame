#include "View.h"
using namespace View;
void GameView::prompt(string s)
{
    cout << s;
}
void GameView::prompt(string s, int Color)
{
    SetColor(Color);
    cout << s;
}
void GameView::DrawBoard(Board* board)
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
void GameView::DrawGameScreen(Game* game)
{
    prompt("=> ", YELLOW);
    prompt("Player ", WHITE);
    prompt(game->GetUser1().GetName() + " ", P1);
    prompt("= ", YELLOW);
    prompt("X", WHITE);
    prompt(", ", YELLOW);
    prompt("Player ", WHITE);
    prompt(game->GetUser2().GetName() + " ", P2);
    prompt("= ", YELLOW);
    prompt("O", WHITE);
    prompt(": \n", YELLOW);
    DrawBoard(game->GetBoard());
}
void GameView::MainMenu()
{
    prompt("*-------", YELLOW);
    prompt("MAIN MENU", WHITE);
    prompt("-------*\n", YELLOW);
    prompt("1.New ", RED);
    prompt("game \n", WHITE);
    prompt("2.Replay\n", RED);
    prompt("3.Players' ", RED);
    prompt("Information\n", WHITE);
    prompt("4.Guide\n", RED);
    prompt("5.Exit\n", RED);
    prompt("Press number to choice:", WHITE);
}
void GameView::Guide()
{
    prompt("*-------", YELLOW);
    prompt("Guide", WHITE);
    prompt("-------*\n", YELLOW);
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
}
