#include<io.h>
#include<fcntl.h>
#include "Console.h"
#include "CompleteUI.h"

CompleteUI::CompleteUI(Position pos) : Object(pos), m_gm(nullptr), m_mapManager(nullptr)
{
    m_gm = GameManager::GetInst();
    m_mapManager = MapManager::GetInst();
    wstring chapi[] =
    {
        L" ⁜⁜    ⁜⁜        ",
        L"⁜@⨛⁜  ⁜@⨛⁜       ",
        L" ⁜⁜    ⁜⁜        ",
        L"  ⁜⁜⁜⁜⁜⁜⁜⁜⁜⁜     ",
        L" ⁜∷∷⁜∷∷∷∷∷∷∷∷⁜   ",
        L"⁜∷∷∷∷∷∷∷∷∷∷∷∷∷** ",
        L" ⁜⁜⁜⁜⁜⁜∷∷∷∷∷∷∷++*",
        L" ⨛⁜***+⨛⁜∷∷∷∷∷++*",
        L"   ⁜*+++++⁜++++* ",
        L"    ⁜⁜⁜⁜⁜⁜**++*  ",
        L"  ⁜⁜⁜        ⁜   ",
        L" ⁜           ⁜⁜⁜ ",
        L"             ⁜  ⁜"
    };
    std::copy(std::begin(chapi), std::end(chapi), m_chapi);
    wstring blue[] =
    {
        L"   ɷ         ",
        L"  ╱╱         ",
        L"(∵)  < 옹씌]",
        L"╱  ╲         ",
        L" ⌈⌉          "
    };
    std::copy(std::begin(blue), std::end(blue), m_blue);
}

void CompleteUI::Update()
{
#pragma region 조건 입력
    Challenge condi = m_gm->m_condition;
    int paragon = 0;
    switch (condi) //값 찾기
    {
    case Challenge::TIME:
        paragon = m_gm->m_playTime;
		num = std::to_wstring(paragon)
            + L" 초";
        break;
    case Challenge::MOVE:
        paragon = m_gm->m_moveCount;
        num = std::to_wstring(paragon)
            + L" 움직임";
        break;
    default:
        break;
    }

    //별
    wstring word = L"";
    for (int i = 1; i <= 3; i++) //조건 입력
    {
        int value = m_gm->m_conditionValue - (i * 10); //조건 값
        bool check = value > paragon; //범위 안인지
        word += wstring(check ? L"★ " : L"☆ ");
    }
    star = word;

#pragma endregion



}

void CompleteUI::Render() const
{
    if (m_mapManager->m_isRendering) return;

    int coutmode = _setmode(_fileno(stdout), _O_U16TEXT);

#pragma region 차피
    int size = sizeof(m_chapi) / sizeof(wstring);
    for (int i = 0; i < size; i++)
    {
        Gotoxy(MAP_WIDTH, height + i);
        DrawWord(m_chapi[i]);
    }
#pragma endregion

#pragma region 알려주기 (정보)
    Gotoxy(MARGIN, height); //별
    DrawWord(star);
    Gotoxy(MARGIN, height + 2);
    DrawWord(num);
    Gotoxy(MARGIN, height + 4);
    DrawWord(L"축하합니다!");
#pragma endregion

#pragma region 피크민
    int si = sizeof(m_blue) / sizeof(wstring);
    for (int i = 0; i < si; i++)
    {
        Gotoxy(MARGIN, height + 8 + i);
        DrawWord(m_blue[i]);
    }
#pragma endregion


    int wcoutmode = _setmode(_fileno(stdout), coutmode);
}
void CompleteUI::DrawWord(wstring word) const
{
    SetColor(COLOR::VIOLET, COLOR::SKYBLUE);
    for (int i = 0; i < word.size(); i++)
    {
        switch (word[i])
        {
        case L'@':
            SetColor(COLOR::LIGHT_BLUE, COLOR::BLACK);
            break;
        case L'*':
            SetColor(COLOR::RED, COLOR::BLACK);
            break;
        case L'+':
            SetColor(COLOR::LIGHT_RED, COLOR::BLACK);
            break;
        case L'∷':
            SetColor(COLOR::LIGHT_YELLOW, COLOR::BLACK);
            break;
        case L'⁜':
            SetColor(COLOR::YELLOW, COLOR::BLACK);
            break;
        case L'⨛':
            SetColor(COLOR::WHITE, COLOR::BLACK);
            break;
        case L'★':
            SetColor(COLOR::LIGHT_GREEN, COLOR::BLACK);
            break;
        case L'☆':
            SetColor(COLOR::RED, COLOR::BLACK);
            break;
        case L'ɷ':
            SetColor(COLOR::LIGHT_RED, COLOR::BLACK);
            break;
        case L'∵':
        case L'⫽':
        case L'╱':
        case L'╲':
        case L'⌈':
        case L'⌉':
        case L')':
        case L'(':
			SetColor(COLOR::LIGHT_BLUE, COLOR::BLACK);
            break;
        default:
            SetColor(COLOR::LIGHT_YELLOW, COLOR::BLACK);
            break;
        }

        wcout << word[i];
    }
    wcout << L"\n";
}
