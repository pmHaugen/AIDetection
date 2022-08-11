#include <iostream>
#include <ctime>
#include <chrono>
#include <Windows.h>
#include <stack>
#include <cmath>

using namespace std;

class robot
{
public:
    char easyAI()
    {
        return i;
    }
    char meduimAI()
    {
        Sleep(100);
        return i;
    }
    char hardAI()
    {
        //srand (time(NULL));
        float delay = rand() % 9000 + 1000;
        cout << delay;
        Sleep(delay);
        return i;
    }
private:
    char i = 'x';
};

int main()
{
    bool useAI = false;
    int AILevel = 0;
    std::stack<float> timingStack;
    cout << "Press 1 to use AI" << endl << "Press 2 to not cheat" << endl;
    int a;
    cin >> a;

    if(a == 1)
    {
        cout << "Choose AI level. 1 = easy. 2 = medium. 3 = hard(not working atm)." << endl;
        cin >> AILevel;
        switch(AILevel)
        {
        case 1:
            AILevel = 1;
            break;
        case 2:
            AILevel = 2;
            break;
        case 3:
            AILevel = 3;
            break;
        }
    }


    float n = 10;
    bool bRobot = false;
    clock_t now = clock();
    robot r;
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    m_StartTime = std::chrono::system_clock::now();
    while (n)
    {
        std::chrono::time_point<std::chrono::system_clock> timingStart;
        timingStart = std::chrono::system_clock::now();
        bool test = false;
        while (!test)
        {
            cout << "press x and enter " << n << " times" << endl;
            char x = ' ';
            if(a == 2)
                cin >> x;
            if(a == 1)
            {
                if(AILevel == 1)
                    x = r.easyAI();
                if(AILevel == 2)
                    x = r.meduimAI();
                if(AILevel == 3)
                    x = r.hardAI();
            }
            if(x == 'x')
            {
                system("CLS");
                test = true;
            }
        }
        n--;
        std::chrono::time_point<std::chrono::system_clock> timingEnd;
        timingEnd = std::chrono::system_clock::now();
        timingStack.push(std::chrono::duration_cast<std::chrono::milliseconds>(timingEnd - timingStart).count());
    }
    float total = 0;
    float data[10];

    for(int i = 0; i<10; i++)
    {
        data[i] = timingStack.top();
        total += timingStack.top();
        timingStack.pop();
    }

    float average = total / 10;
    cout << "Average: " << average << endl;


    float standardDeviation = 0;
    for(int i = 0; i < 10; ++i)
    {
       standardDeviation += pow(data[i] - average, 2);
     }
    cout << "Diviation: " << sqrt(standardDeviation / 10);


    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    m_EndTime = std::chrono::system_clock::now();


    bool tooFast = false;
    bool badDeviation = false;
    if(sqrt(standardDeviation / 10) <= 200)
    {
        bRobot = true;
        badDeviation = true;
    }
    if (std::chrono::duration_cast<std::chrono::milliseconds>(m_EndTime - m_StartTime).count() < 1000)
    {
        bRobot = true;
        tooFast = true;
    }
    Sleep(1000);
    cout << "Complete!" << endl;
    if (bRobot == true)
    {
        cout << "YOU ARE A ROBOT!!!" << endl;
        if(tooFast)
            cout << "Because you were too fast!" << endl;
        else if(badDeviation)
            cout << "You are too accurate!" << endl;
    }
    else
    {
        cout << "You are a human!";
    }
}
