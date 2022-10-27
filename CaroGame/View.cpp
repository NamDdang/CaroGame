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
void GameView::MenuHeader(int header)
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
void GameView::MainMenu()
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
void GameView::GameOverMenu()
{
    prompt("Do you want to play again?\n", YELLOW);
    prompt("1.Play ", RED);
    prompt("again\n", WHITE);
    prompt("2.Back ", RED);
    prompt("to MAIN MENU\n", WHITE);
    prompt("Press number to choice:", WHITE);
}
void GameView::AskToSaveReplay()
{
    prompt("Do you want to save replay?\n", YELLOW);
    prompt("1.Yes\n", WHITE);
    prompt("2.No\n", WHITE);
    prompt("Press number to choice:", WHITE);
}
void GameView::Replay()
{
    prompt("1.Replay ", RED);
    prompt("again\n", WHITE);
    prompt("2.Choose ", RED);
    prompt("another replay\n", WHITE);
    prompt("3.Back ", RED);
    prompt("to MAIN MENU\n", WHITE);
    prompt("Press number to choice:", WHITE);
}
void GameView::PlayerInfomationMenu()
{
    prompt("1.Show ", RED);
    prompt("All Player\n", WHITE);
    prompt("2.Search ", RED);
    prompt("player by Name\n", WHITE);
    prompt("3.Back ", RED);
    prompt("to MAIN MENU\n", WHITE);
    prompt("Press number to choice:", WHITE);
}
void GameView::ShowAllPlayer()
{
    prompt("1.Back ", RED);
    prompt("to Player's Infomation\n", WHITE);
    prompt("2.Back ", RED);
    prompt("to MAIN MENU\n", WHITE);
    prompt("Press number to choice:", WHITE);
}
void GameView::SearchPlayerByName()
{
    prompt("1.Continue ", RED);
    prompt("Search\n", WHITE);
    prompt("2.Back ", RED);
    prompt("to Player's Infomation\n", WHITE);
    prompt("3.Back ", RED);
    prompt("to MAIN MENU\n", WHITE);
    prompt("Press number to choice:", WHITE);
}
void GameView::Guide()
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
void GameView::PlayOnline()
{
    prompt("1.Login\n", RED);
    prompt("2.Register\n", RED);
    prompt("3.Back ", RED);
    prompt("to MAIN MENU\n", WHITE);
    prompt("Press number to choice:", WHITE);
}
void GameView::PlayOnlineAfterLogin()
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