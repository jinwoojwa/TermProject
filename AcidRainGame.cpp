#include <iostream>
// < cstdlib > �� <ctime> �� rand() �Լ� ���� �õ� �ʱ�ȭ�� ���� ����.
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
    int x = 0; // �ܾ��� x ��ǥ
    int y = 0; // �ܾ��� y ��ǥ
    string word;
};

vector<RainWord> rainWords;

// ���ڷ����� ������ ���� �߻� Ŭ����
class WordDecorator {
public:
    virtual string decorate(const string& input) = 0;
};

// ���ĺ� �ɼ� ���ڷ�����
class AlphabetDecorator : public WordDecorator {
public:
    virtual string decorate(const string& input) override {
        return input;
    }
};

// Ư������ �ɼ� ���ڷ�����
class SpecialCharacterDecorator : public WordDecorator {
public:
    virtual string decorate(const string& input) override {
        string str = input;

        // input �ڿ� Ư������ �߰�
        str += getSpecialCharacter();

        return str;
    }
private:
    // Ư������ �߿��� ������ ���� ��ȯ���ִ� �Լ�
    char getSpecialCharacter() {
        const string specialCharacters = "!@#$%^&*()_+-=[]{}|;:'\",.<>?/";
        int randomIdx = rand() % specialCharacters.length();
        return specialCharacters[randomIdx];
    }
};

// ���� �ɼ� ���ڷ�����
class NumberDecorator : public WordDecorator {
public:
    virtual string decorate(const string& input) override {
        string str = input;
        int length = str.length();
        string numbers = "0123456789";

        // ������ ��ġ ����
        int randomIndex = rand() % (length + 1);

        // ������ ��ġ�� �������� ���õ� ���� �߰�
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

        // ���� ���� : 1���� 7������ ������ ��
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

// �������� �ܼ�â���� �ܾ �������� ��ġ�� �������ִ� �Լ�
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

// Ŀ���� ������ �ʵ��� ���ִ� �Լ�
void SetCursorHidden() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void clean() {
    // COORD ����ü�� �����Ͽ� Ŀ���� ���ο� ��ġ�� (0, 0)���� �����մϴ�.
    COORD cursorPosition = { 0, 0 };

    // SetConsoleCursorPosition �Լ��� ����Ͽ� Ŀ���� ���ο� ��ġ�� �̵���ŵ�ϴ�.
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

    cout << "LIFE: " << life << "     SCORE: " << score << "     �Է� : " << input;

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
    cout << "                        Programmed by ������\n\n";
    cout << "                   LIFE�� 0�� �Ǹ� ������ ����˴ϴ�.\n\n";
    cout << "                    �ִ��� ���� ������ ������!!\n\n";
    cout << "                       ���� ��带 ������ �ּ���.\n";
    cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";

    cout << "\n\n";

    cout << "GAME MODE: 1. ���ĺ�\n" << endl;
    cout << "           2. ���ĺ� + ����\n" << endl;
    cout << "           3. ���ĺ� + Ư������\n" << endl;

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
        cout << "�߸��� �Է°��Դϴ�. �⺻ �ɼ����� �����ϰڽ��ϴ�." << endl;
        deco.addDecorator(new AlphabetDecorator());
        break;
    }

    clock_t startTime = clock();
    clock_t strTime = clock();
    string input;

    int LIFE = 3;
    int SCORE = 0;

    while (LIFE > 0) {
        // WORD_TERM ���ݸ��� ���ο� �ܾ� ����, ���� �� �ð� �ʱ�ȭ
        if (clock() - startTime > WORD_TERM) {
            makeWord(deco);
            startTime = clock();
        }

        // SPEED ���ݸ��� ���� �������� �ִ� ��� �ܾ �� ĭ�� �Ʒ��� �̵���Ű��, ȭ���� ����� ����
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

        // _kbhit() �Լ��� Ű���� �Է��� �ִ��� Ȯ���ϴ� �Լ�
        if (_kbhit()) {
            // _getch() �Լ��� ����ڰ� Ű�� ������ ���� Ű�� ASCII ���� ��ȯ��
            char key = _getch();
            // ����ڰ� backspace�� ������ �� ���� (�ƿ� ��������)
            if (key == '\b' && !input.empty()) {
                input.clear();
            }
            // ����ڰ� Enter Ű�� ������ �� ����
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
            cout << "���� ����!!\n" << endl;
            cout << "����: " << SCORE << "��\n";
            break;
        }
    }

    for (WordDecorator* decorator : deco.getDeco()) {
        delete decorator;
    }

    return 0;
}