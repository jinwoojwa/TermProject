#include <iostream>
// < cstdlib > 와 <ctime> 은 rand() 함수 사용과 시드 초기화를 위해 사용됨.
#include <cstdlib>
#include <ctime>
#include <vector>
#include <conio.h>
#include <windows.h>

using namespace std;

const int WIDTH = 100;
const int HEIGHT = 25;
const int WORD_TERM = 1777;

struct RainWord {
    int x = 0; // 단어의 x 좌표
    int y = 0; // 단어의 y 좌표
    string word;
};

vector<RainWord> rainWords;

// 데코레이터 패턴을 위한 추상 클래스
class WordDecorator {
public:
    virtual string decorate(const string& input) = 0;
};

// 알파벳 옵션 데코레이터
class AlphabetDecorator : public WordDecorator {
public:
    virtual string decorate(const string& input) override {
        return input;
    }
};

// 특수문자 옵션 데코레이터
class SpecialCharacterDecorator : public WordDecorator {
public:
    virtual string decorate(const string& input) override {
        string str = input;

        // input 뒤에 특수문자 추가
        str += getSpecialCharacter();

        return str;
    }
private:
    // 특수문자 중에서 랜덤한 값을 반환해주는 함수
    char getSpecialCharacter() {
        const string specialCharacters = "!@#$%^&*()_+-=[]{}|;:'\",.<>?/";
        int randomIdx = rand() % specialCharacters.length();
        return specialCharacters[randomIdx];
    }
};

// 숫자 옵션 데코레이터
class NumberDecorator : public WordDecorator {
public:
    virtual string decorate(const string& input) override {
        string str = input;
        int length = str.length();
        string numbers = "0123456789";

        // 무작위 위치 선택
        int randomIndex = rand() % (length + 1);

        // 무작위 위치에 무작위로 선택된 숫자 추가
        str.insert(randomIndex, 1, numbers[rand() % numbers.length()]);

        return str;
    }
};

class DecoratedStr {
private:
    vector<WordDecorator*> Wdecorator;

public:
    DecoratedStr() {}

    void addDecorator(WordDecorator* decorator) {
        Wdecorator.push_back(decorator);
    }

    vector<WordDecorator*> getDeco() const {
        return Wdecorator;
    }

    string randomWord() {
        string characters = "abcdefghijklmnopqrstuvwxyz";

        // 글자 길이 : 1에서 7까지의 랜덤한 값
        int length = rand() % 7 + 1;

        string randStr;
        for (int i = 0; i < length; ++i) {
            randStr += characters[rand() % characters.length()];
        }

        for (WordDecorator* decorator : Wdecorator) {
            randStr = decorator->decorate(randStr);
        }
        return randStr;
    }
};

// 랜덤으로 콘솔창에서 단어가 떨어지는 위치를 지정해주는 함수
int RandomXPosition() {
    return rand() % WIDTH;
}

void makeWord(DecoratedStr& deco) {
    RainWord newstr;
    newstr.x = RandomXPosition();
    newstr.y = 0;
    newstr.word = deco.randomWord();
    rainWords.push_back(newstr);
}

// 커서가 보이지 않도록 해주는 함수
void SetCursorHidden() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void clean() {
    // COORD 구조체를 생성하여 커서의 새로운 위치를 (0, 0)으로 설정합니다.
    COORD cursorPosition = { 0, 0 };

    // SetConsoleCursorPosition 함수를 사용하여 커서를 새로운 위치로 이동시킵니다.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void display(const string& input, int life, int score) {
    clean();

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            bool isSpace = true;
            for (const RainWord& str : rainWords) {
                if (i == str.y && j >= str.x && j < str.x + str.word.length()) {
                    cout << str.word[j - str.x];
                    isSpace = false;
                    break;
                }
            }
            if (isSpace) {
                cout << ' ';
            }
        }
        cout << endl;
    }

    cout << "LIFE: " << life << "     SCORE: " << score << "     입력 : " << input;

    for (int i = 0; i < WIDTH - input.length(); ++i) {
        cout << ' ';
    }

    cout << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    SetCursorHidden();

    cout << "\n\n";
    cout << "     ###     ####    ####  ######     #######      ###   #### ####    ##\n";
    cout << "    ## ##   ##   ##   ##    ##   ##    ##   ##    ## ##   ##  ## ##   ##\n";
    cout << "   #######  ##        ##    ##    ##   ######    #######  ##  ##  ##  ##\n";
    cout << "   ##   ##  ##   ##   ##    ##   ##    ##  ###   ##   ##  ##  ##   ## ##\n";
    cout << "   ##   ##   ####    ####  ######     ###   #### ##   ## #### ##    ####\n";

    cout << "\n\n";

    cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    cout << "                        Programmed by 좌진우\n\n";
    cout << "                   LIFE가 0이 되면 게임이 종료됩니다.\n\n";
    cout << "                    최대한 많은 점수를 얻어보세요!!\n\n";
    cout << "                       게임 모드를 선택해 주세요.\n";
    cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";

    cout << "\n\n";

    cout << "GAME MODE: 1. 알파벳\n" << endl;
    cout << "           2. 알파벳 + 숫자\n" << endl;
    cout << "           3. 알파벳 + 특수문자\n" << endl;

    int opt;
    cin >> opt;

    DecoratedStr deco;

    switch (opt) {
    case 1:
        deco.addDecorator(new AlphabetDecorator());
        break;
    case 2:
        deco.addDecorator(new AlphabetDecorator());
        deco.addDecorator(new NumberDecorator());
        break;
    case 3:
        deco.addDecorator(new AlphabetDecorator());
        deco.addDecorator(new SpecialCharacterDecorator());
        break;
    default:
        cout << "잘못된 입력값입니다. 기본 옵션으로 시작하겠습니다." << endl;
        deco.addDecorator(new AlphabetDecorator());
        break;
    }

    clock_t startTime = clock();
    clock_t strTime = clock();
    string input;

    int LIFE = 3;
    int SCORE = 0;

    while (LIFE > 0) {
        // WORD_TERM 간격마다 새로운 단어 생성, 생성 후 시간 초기화
        if (clock() - startTime > WORD_TERM) {
            makeWord(deco);
            startTime = clock();
        }

        // SPEED 간격마다 현재 떨어지고 있는 모든 단어를 한 칸씩 아래로 이동시키고, 화면을 벗어나면 삭제
        const int MIN_SPEED = 250;
        const int MAX_SPEED = 500;

        int randomSpeed = rand() % (MAX_SPEED - MIN_SPEED + 1) + MIN_SPEED;

        if (clock() - strTime > randomSpeed) {
            for (RainWord& str : rainWords) {
                str.y++;
                if (str.y >= HEIGHT) {
                    rainWords.erase(rainWords.begin());
                    LIFE--;
                }
            }
            strTime = clock();
        }

        display(input, LIFE, SCORE);

        // _kbhit() 함수는 키보드 입력이 있는지 확인하는 함수
        if (_kbhit()) {
            // _getch() 함수는 사용자가 키를 누르면 눌린 키의 ASCII 값을 반환함
            char key = _getch();
            // 사용자가 backspace를 눌렀을 때 동작 (아예 지워버림)
            if (key == '\b' && !input.empty()) {
                input.clear();
            }
            // 사용자가 Enter 키를 눌렀을 때 동작
            else if (key == '\r') {
                for (int i = 0; i < rainWords.size(); ++i) {
                    if (input == rainWords[i].word) {
                        rainWords.erase(rainWords.begin() + i);
                        SCORE += 100;
                        break;
                    }
                }
                input.clear();
            }
            else {
                input += key;
            }
        }

        if (LIFE == 0) {
            cout << "게임 종료!!\n" << endl;
            cout << "점수: " << SCORE << "점\n";
            break;
        }
    }

    for (WordDecorator* decorator : deco.getDeco()) {
        delete decorator;
    }

    return 0;
}