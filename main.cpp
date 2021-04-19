#include <iostream>
#include <vector>

#define VERSION "0.01b"


const int WIN_SCORE = 3;
const int DRAW_SCORE = 1;
const int LOSE_SCORE = 0;

/*
 * За победу в Матче начисляются три очка, за ничью одно очко, за поражение очки не начисляются.
 * Команда, набравшая большее количество очков, располагается в текущей и итоговой турнирной таблице выше команды,
 * набравшей меньшее количество очков.
 */

using namespace std;

/*
 * QGraphicsScene - графика
 */

/*
 * Команда
 */
class Team {
private:
    int score;
    int win_count;      // Победы
    int lose_count;     // Поражения
    int draw_count;     // Ничья
    int goals_scored;   // Забито мячей
    int goals_conceded; // Пропущенно мячей
    string title;
public:
    /*
     * Создание команды
     */
    Team() {
        title = "";
        score = 0;
        win_count = 0;
        lose_count = 0;
        draw_count = 0;
        goals_scored = 0;
        goals_conceded = 0;
    }

    /*
     * Создание команды с заранее заданными данными
     */
    Team(string t) { // Может быть использовано
        title = t;
        score = 0;
        win_count = 0;
        lose_count = 0;
        draw_count = 0;
        goals_scored = 0;
        goals_conceded = 0;
    }

    /*
     * Создание команды с заранее заданными данными
     */
    Team(string t,
         int Score,
         int Win_count,
         int Lose_count,
         int Draw_count,
         int Goals_scored,
         int Goals_conceded) {
        title = t;
        score = Score;
        win_count = Win_count;
        lose_count = Lose_count;
        draw_count = Draw_count;
        goals_scored = Goals_scored;
        goals_conceded = Goals_conceded;
    }

    /*
     * Создаем команду путем копирования
     */
    Team(const Team &obj) {
        title = obj.title; // Копируем название команды
        score = obj.score;
        win_count = obj.win_count;
        lose_count = obj.lose_count;
        draw_count = obj.draw_count;
        goals_scored = obj.goals_scored;
        goals_conceded = obj.goals_conceded;
    }

    /*
     * Деструктор
     */
    ~Team() {
        // cout << "Object destroyed" << endl;
    }

    /*
     * Используется для получения названия команды
     *
     * return string
     */
    string get_name() {
        return title;
    }

    int get_score() {
        return score;
    }

    int get_count_wins() {
        return win_count;
    }

    int get_count_lose() {
        return lose_count;
    }

    int get_count_draw() {
        return draw_count;
    }

    int get_goals_scored() {
        return goals_scored;
    }

    int get_goals_conceded() {
        return goals_conceded;
    }

    /**** FUNC *****/
    void set_score(int count) {
        score = count;
    }

    void set_count_wins(int count) {
        win_count = count;
    }

    void set_count_lose(int count) {
        lose_count = count;
    }

    void set_count_draw(int count) {
        draw_count = count;
    }

    void set_goals_scored(int count) {
        goals_scored = count;
    }

    void set_goals_conceded(int count) {
        goals_conceded = count;
    }

    friend istream& operator>>(istream&in, Team&t) {
        cout << "Название команды: "; in >> t.title;
        // cout << "Набрано очков: "; in >> t.score;
        return in;
    }

    friend ostream& operator<<(ostream&out, const Team&t) {
        cout << "Название команды: " << t.title << endl;
        cout << "\tНабрано очков: " << t.score << endl;
        cout << "\tПобед: " << t.win_count << endl;
        cout << "\tПоражений: " << t.lose_count << endl;
        cout << "\tНичья: " << t.draw_count << endl;
        cout << "\tЗабито: " << t.goals_scored << endl;
        cout << "\tПропущено: " << t.goals_conceded << endl;
        return out;
    }

    Team& operator=(const Team &t) {
        if (&t == this) {
            // На самом деле проверка не особо нужна, но иногда пригодится
            return *this;
        }
        title = t.title; // Копируем название команды
        score = t.score;
        win_count = t.win_count;
        lose_count = t.lose_count;
        draw_count = t.draw_count;
        goals_scored = t.goals_scored;
        goals_conceded = t.goals_conceded;
        return *this;
    }
};

vector<Team> teams;

int teamExists(string key) {
    int elem = -1;
    for(auto i = teams.begin(); i < teams.end();) {
        elem++;
        if (i->get_name() == key) {
            return elem;
        }
        i++;
    }
    return -1;
}

bool addTeam() {
    int count = 0;
    cout << "Сколько команд будет добавлено?" << endl;
    cout << "Для отмены введите 0" << endl;
    cout << "> "; cin >> count;

    Team t;
    bool found;
    for(int i = 0; i < count; i++) {
        found = true;
        while (found) {
            found = false;
            cin >> t;
            if (teamExists(t.get_name()) != -1) {
                found = true;
                cout << "Уже существует команда с таким названием! Введите другое!" << endl;
            }
        }
        teams.push_back(t);
    }
    return true;
}

int addTeam(string team_name) {
    int teamId;
    if((teamId = teamExists(team_name)) != -1)
        return teamId;

    Team t(team_name);
    teams.push_back(t);
    return -1;
}

class Match {
private:
    string team_1;
    string team_2;
    int score_1;
    int score_2;
public:
    Match() {
        team_1 = "";
        team_2 = "";
        score_1 = 0;
        score_2 = 0;
    }


    friend istream& operator>>(istream&in, Match&t) {
        int teamIdOne,
            teamIdTwo;

        int goals_scored_one = 0,       // Забил
            goals_scored_two = 0;       // Забил

        cout << "Название 1ой команды: "; in >> t.team_1;
        cout << "Введите количество забитых мячей: "; in >> goals_scored_one;
        teamIdOne = teamExists(t.team_1);

        bool err = false;
        do {
            cout << "Название 2ой команды: ";
            in >> t.team_2;
            if(t.team_1 == t.team_2) {
                cerr << "Команда не может играть против себя же!" << endl;
                err = true;
            } else err = false;
        } while (err);
        cout << "Введите количество забитых мячей: ";
        in >> goals_scored_two;
        teamIdTwo = teamExists(t.team_2);

        /*
        if((teamIdTwo = addTeam(t.team_2)) != -1) {
            // Если такая команда уже есть
            Team teamTwo(teams[teamIdTwo]);
            // team.addScore(50);
           // teams[teamId] = team;
        } else {
        }
         */

        // Узнаем победивших
        int winTeam;
        if(goals_scored_one > goals_scored_two)         winTeam = 1;
        else if(goals_scored_one < goals_scored_two)    winTeam = 2;
        else winTeam = 0;

        // Теперь обновим информацию

        /* Команда 1 */
        Team team(t.team_1);
        if(teamIdOne != -1) {
            team = teams[teamIdOne];
        }
        if(winTeam == 1) {
            team.set_count_wins(team.get_count_wins()+1);
            team.set_score(team.get_score()+WIN_SCORE);
        } else if(winTeam == 2) {
            team.set_count_lose(team.get_count_lose()+1);
            team.set_score(team.get_score()+LOSE_SCORE);
        } else if(winTeam == 0) {
            team.set_count_draw(team.get_count_draw()+1);
            team.set_score(team.get_score()+DRAW_SCORE);
        }
        team.set_goals_scored(team.get_goals_scored()+goals_scored_one);
        team.set_goals_conceded(team.get_goals_conceded()+goals_scored_two);
        if(teamIdOne == -1) {
            // cout << "Добавление первой";
            teams.push_back(team);
        } else {
            // cout << "Замена первой";
            teams[teamIdOne] = team;
        }
        /* Команда 2 */
        Team teamTwo(t.team_2);
        if(teamIdTwo != -1) {
            teamTwo = teams[teamIdTwo];
        }
        if(winTeam == 2) {
            teamTwo.set_count_wins(teamTwo.get_count_wins()+1);
            teamTwo.set_score(teamTwo.get_score()+WIN_SCORE);
        } else if(winTeam == 1) {
            teamTwo.set_count_lose(teamTwo.get_count_lose()+1);
            teamTwo.set_score(teamTwo.get_score()+LOSE_SCORE);
        } else if(winTeam == 0) {
            teamTwo.set_count_draw(teamTwo.get_count_draw()+1);
            teamTwo.set_score(teamTwo.get_score()+DRAW_SCORE);
        }
        teamTwo.set_goals_scored(teamTwo.get_goals_scored()+goals_scored_two);
        teamTwo.set_goals_conceded(teamTwo.get_goals_conceded()+goals_scored_one);
        if(teamIdTwo == -1) {
            // cout << "Добавление второй";
            teams.push_back(teamTwo);
        } else {
            // cout << "Замена второй";
            teams[teamIdTwo] = teamTwo;
        }

        return in;
    }


    friend ostream& operator<<(ostream&out, const Match&t) {
        cout << t.team_1 << " VS " << t.team_2 << endl;
        return out;
    }
};

vector<Match> matches;

bool addMatch() {
    Match t;
    cin >> t;
    matches.push_back(t);
    return true;
}

int prompt_menu_item() {
    int variant = -1;
    cout << "Главное меню:" << endl;
    cout << "\t\t\t1. Добавить команду" << endl;
    cout << "\t\t\t2. Удалить команду" << endl;
    cout << "\t\t\t3. Показать команды" << endl;
    cout << "\t\t\t4. Рейтинг команд" << endl;
    cout << "\t\t\t5. Проверка существования команды" << endl;
    cout << "\t\t\t6. Добавить матч" << endl;
    cout << "\t\t\t7. Список матчей" << endl;
    cout << endl << "\t\t\t0. Выход" << endl;
    cout << "> ";
    cin >> variant;
    return variant;
}

struct less_than_key
{
    inline bool operator() (Team struct1, Team struct2)
    {
        return (struct1.get_score() > struct2.get_score());
    }
};

int main() {
    cout << "Используется версия: " << VERSION << endl << endl;

    int variant;
    while((variant = prompt_menu_item()) != 0) {
        switch (variant) {
            case 1: {
                addTeam();
                break;
            }
            case 2: {
                cout << "\t\t\t\t\t\tУДАЛЕНИЕ КОМАНДЫ" << endl;
                string key;
                cout << "> ";
                cin >> key;

                bool bFound = false;
                for(auto i = teams.begin(); i < teams.end();) {
                    if(i->get_name() == key) {
                        bFound = true;
                        teams.erase(i);
                        break;
                    } else {
                        i++;
                    }
                }
                if(bFound) {
                    cout << "Команда " << key << " успешно удалена" << endl;
                } else {
                    cout << "По вашему запросу ничего не найдено" << endl;
                }
            }
            case 3: {
                cout << "\t\t\t\t\t\tСПИСОК КОМАНД" << endl;
                for(auto i:teams) {
                    cout << i;
                }
                break;
            }
            case 4: {
                sort(teams.begin(), teams.end(), less_than_key());
                cout << "\t\t\t\t\t\tРЕЙТИНГ КОМАНД" << endl;
                for(auto i:teams) {
                    cout << i;
                }
                break;
            }
            case 5: {
                cout << "\t\t\t\t\t\tСУЩЕСТВУЕТ ЛИ КОМАНДА" << endl;
                string key;
                cout << "> ";
                cin >> key;

                cout << (teamExists(key) != -1 ? "Команда найдена" : "Команда не найдена") << endl;
                break;
            }
            case 6: {
                cout << "\t\t\t\t\t\tДОБАВИТЬ МАТЧ" << endl;
                addMatch();
                break;
            }
            case 7: {
                cout << "\t\t\t\t\t\tСписок матчей" << endl;
                for(auto i:matches) {
                    cout << i;
                }
                break;
            }
            case 0: {
                cout << "Выходим из программы.." << endl;
                exit(EXIT_SUCCESS);
            }
            default: {
                cerr << "Вы выбрали неверный пункт меню" << endl;
            }
        }
    }
    return 0;
}
