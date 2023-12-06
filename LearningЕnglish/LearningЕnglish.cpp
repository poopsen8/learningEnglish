#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <string>
#include <time.h>
#include <thread>


#define PATH_REPEAT "repeat_Words.txt"
#define PATH_STUDIED "studied_Words.txt"

class LearningЕnglish
{
public:
    void start();
    
private:
    bool studied_words();
    bool repeat_words();
    void splitting_words(const std::vector<std::string> arrLineWords);
    void training(const int numberWords);
    void timeUpdates(const int timeTraining);

private:
    int m_studiedOrRepeat; // 2 повторить ,1 учить новые слова
    std::vector<std::string> m_arrWordsEN;
    std::vector<std::string> m_arrWordsRU;
    bool m_exitTraining;
public:

};

void LearningЕnglish::timeUpdates(const int timeTraining) {
   
    time_t t1 = time(NULL);
    tm timeNew = *localtime(&t1);
    tm timeFinal = timeNew;
    timeFinal.tm_min = timeFinal.tm_min + timeTraining;

    for (;;)
    {
        Sleep(1000);
        time_t t1 = time(NULL);
        timeNew = *localtime(&t1);
        //std::cout << timeNew.tm_hour << " " << timeNew.tm_min << " " << timeNew.tm_sec << std::endl;
        if (timeFinal.tm_min <= timeNew.tm_min && timeFinal.tm_sec <= timeNew.tm_sec)
        {
            this->m_exitTraining = true;
            break;
        }
    }
    
}


void LearningЕnglish::training(const int timeTraining){
    std::thread threadTimeUpdates(&LearningЕnglish::timeUpdates, this, timeTraining);

    int wordIndex;
    std::string wordAnswer;
    system("cls");
    std::cout << "\n Ну что же тогда начинаем))\n";
    for (; ;)
    {
        if (this->m_exitTraining)
        {
            threadTimeUpdates.join();
            system("cls");
            break;
        }

        time_t t1 = time(NULL);
        wordIndex = rand() % this->m_arrWordsEN.size();
        std::cout << this->m_arrWordsEN[wordIndex] << " : ";
        std::cin >> wordAnswer;

        if (wordAnswer == this->m_arrWordsRU[wordIndex])
        {
            std::cout << "\nправильный ответ. Живи пока..." << std::endl;
        }
        else
        {
            std::cout << "\nОтвет не верный, вот так надо было : " << this->m_arrWordsRU[wordIndex] << std::endl;
        }
        Sleep(100);
  
        system("pause");
        system("cls");
    }

 
  
}



void LearningЕnglish::splitting_words(std::vector<std::string> arrLineWords) {


    std::string word;
    // хотел сделать одним массивом ,но сука не работает и все .так тоже нормально..
    for (size_t i = 0; i < arrLineWords.size(); i++)
    {
        arrLineWords[i].erase(remove(arrLineWords[i].begin(), arrLineWords[i].end(), ' '), arrLineWords[i].end());

        for (size_t j = 0; j < arrLineWords[i].size(); j++)
        {
            if (arrLineWords[i][j] != '-')
            {   
                word = word + arrLineWords[i][j];
            }
            else
            {
                this->m_arrWordsEN.push_back(word);
                word.clear();
            }
        }
        this->m_arrWordsRU.push_back(word);
        word.clear();
    }
}

bool LearningЕnglish::repeat_words() {
    std::fstream repeatFile;
    repeatFile.open(PATH_REPEAT);
    if (!repeatFile.is_open())
    {
        std::cout << "\nПохожа файла \"repeat_Words.txt\" не существует :((";
        Sleep(350);
        std::cout << "\n Нечего я создам его за вас ;)";
        Sleep(350);
        std::cout << "\n Но если у вас его не было, вам нечего повторять...\n";
        Sleep(210);
        repeatFile.close();
        repeatFile.open(PATH_REPEAT, std::fstream::app);
        repeatFile.close();
        return false;
    }
    else {
        std::vector<std::string> arrRepeatWords;
        std::string line;
        
        while (std::getline(repeatFile, line))
        {
            arrRepeatWords.push_back(line);
        }

        if (arrRepeatWords.size() == 0)
        {
            std::cout << "Аммэ.. похожа в этом файле ничего нет +_+\n";
        }
        else
        {
            int timeTraining = 0;
            this->splitting_words(arrRepeatWords);
            do
            {
                switch (timeTraining)
                {
                case 0:
                    std::cout << "\nСколько будем повторять в минутах ?)";
                    std::cin >> timeTraining;
                    break;
                default:
                    std::cout << "\nНу ты же не будешь столько сидеть";
                    std::cout << "\nДавай возьмем цифру по реалистичнее) : ";
                    std::cin >> timeTraining;
                    break;
                }

            } while (timeTraining > 30);
  
            this->training(timeTraining);
            std::cout << "\nПохоже время уже кончилось) что будем делать дальше ?)\n";
        }
        
    }

    repeatFile.close();

    return true;
}


bool LearningЕnglish::studied_words() {
    std::fstream studiedFile;
    studiedFile.open(PATH_STUDIED);
    if (!studiedFile.is_open())
    {
        std::cout << "\nТак.. похожа файла \"studied_Words.txt\" не существует !_!";
        Sleep(350);
        std::cout << "\n Нечего я создам его за вас;)";
        Sleep(350);
        std::cout << "\n не забудь добавить туда слова 0_0\n";
        Sleep(210);
        studiedFile.close();
        studiedFile.open(PATH_STUDIED, std::fstream::app);
        studiedFile.close();
        return false;
    }
    else {
        std::vector<std::string> arrStudiedWords;
        std::string line;


        while (std::getline(studiedFile, line))
        {
            arrStudiedWords.push_back(line);
        }

        if (arrStudiedWords.size() == 0)
        {
            std::cout << "Аэмм.. похожа в файле ничего нет... как же так...\n";
        }
        else
        {
            this->splitting_words(arrStudiedWords);
 
            int timeTraining = 0;
            do
            {
                switch (timeTraining)
                {
                case 0:
                    std::cout << "\nСколько будем повторять в минутах ?)";
                    std::cin >> timeTraining;
                    break;
                default:
                    std::cout << "\nНу ты же не будешь столько сидеть";
                    std::cout << "\nДавай возьмем цифру по реалистичнее) : ";
                    std::cin >> timeTraining;
                    break;
                }

            } while (timeTraining > 30);

        
            this->training(timeTraining);
            std::cout << "\nПохоже время уже кончилось) что будем делать дальше ?)\n";
        }
        
    }
   
    studiedFile.close();

    return true;
}


void LearningЕnglish::start(){

    for (;;)
    {
        std::cout << "Что будем учить или повторять ? 1 / 2 - ";
        std::cin >> this->m_studiedOrRepeat;
   
        switch (m_studiedOrRepeat)
        {
        case 1:
            this->LearningЕnglish::studied_words();
            break;
        case 2:
            this->LearningЕnglish::repeat_words();
            break;
        default:
            std::cout << "\nтак что не то -_-, надо еще разок\n";
            continue;
        }
    }
  
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    LearningЕnglish lEng;
    lEng.start();

}

