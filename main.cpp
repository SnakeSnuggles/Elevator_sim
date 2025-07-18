#include <iostream>
#include <vector>
#include <random>
#include <windows.h>
#include <string>
#include <unordered_map>

class Elevator {
    private:
        int floors;
    public:
        int at_floor;
        Elevator(int num_floors) : at_floor(0), floors(num_floors) {}
        void go_up() {
            if(at_floor < floors - 1) {
                at_floor++;
            }
        }
        void go_down() {
            if(at_floor > 0) {
                at_floor--;
            }
        }
};

struct Person {
    int elevator;
    int floor;
    int to_floor;
};

std::random_device dev;
std::mt19937 rng(dev());

int random_int(int min, int max) {
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

    return dist(rng);
}

Person generate_person(int number_elevators, int number_floors) {
    int from_floor, to_floor;
    do {
        from_floor = random_int(0, number_floors - 1 );
        to_floor = random_int(0, number_floors - 1);
    } while (from_floor == to_floor);

    
    int elevator_index = random_int(0, number_elevators - 1);

    return Person{elevator_index, from_floor, to_floor};
}

class SimulationManager {
    private:
        int number_elevators = 5, number_floors = 5;
        std::vector<Elevator> elevator_group;
        std::vector<Person> list_people;
    public:
        SimulationManager() {                
            list_people.push_back(Person{0, 4, 3});
            list_people.push_back(Person{1, 2, 3});
            list_people.push_back(Person{2, 3, 3});
            list_people.push_back(Person{3, 1, 3});
            list_people.push_back(Person{4, 3, 3});

            for(int i = 0; i< number_elevators; ++i) {
                    elevator_group.push_back(Elevator{number_floors});
            }
        }

        void tick() {
            for(Person &p : list_people) {
                Elevator &elevator = elevator_group[p.elevator];

                if(p.floor > elevator.at_floor) {
                    elevator.go_up();
                }
                else if (p.floor < elevator.at_floor) {
                    elevator.go_down();
                }
            }
        }

        void draw() {
            system("cls");
            
            std::unordered_map<int, std::unordered_map<int, bool>> whereperson;
            for(Person &p : list_people) {
                whereperson[p.elevator][p.floor] = true;
            }
            for(int j = number_floors - 1; j >= 0; --j) {
                std::cout << j << " | ";
                for(int i = 0; i < number_elevators; ++i) {
                    if(elevator_group[i].at_floor == j) {
                        std::cout << "█";
                    }
                    else {
                        std::cout << "░";
                    }
                    std::string is_per = (whereperson[i][j] == true) ? "☺" : " ";
                    std::cout << is_per;
                    std::cout << " ";

                }
                std::cout << "\n";
            }
            std::cout << "    ";
            for(int i = 0; i < number_elevators; ++i) {
                std::cout << i << "  ";
            }

        }

};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    
    SimulationManager manager{};
    while(true) {
        manager.draw();
        manager.tick();

        std::cin.get();
    }

}
