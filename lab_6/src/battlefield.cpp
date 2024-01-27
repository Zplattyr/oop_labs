#include "battlefield.h"

std::ostream &operator << (std::ostream &os, Battlefield &btf) {
    os << "This is a battlefield" << std::endl;
    os << "There are " << btf._npcList.size() << " fighters." << std::endl;
    for (auto npc: btf._npcList) {
        os << *npc;
    }
    return os;
}

Battlefield::Battlefield() : _size(BTF_SIZE,BTF_SIZE), _npcList(), _observers() {}

void Battlefield::attachObs(std::shared_ptr<Observer> obs) {
    _observers.push_back(obs);
}

void Battlefield::detachObs(std::shared_ptr<Observer> obs) {
    if (!_observers.remove(obs)) {
        throw std::logic_error("Observer not in observer list");
    }
}

void Battlefield::fillRandomly(size_t seed, size_t knights, size_t dragons, size_t princesses) {
    srand(seed);
    std::vector<std::string> princessNames = {"Алисия", "Изабелла", "Виктория", "Евангелина", "Катерина", "Анастасия", "Марианна", "Элизабет", "Оливия", "София", "Николь", "Александра", "Амелия", "Изольда", "Лорена"};
    std::vector<std::string> dragonNames = {"Драко", "Фаэр", "Инферно", "Шторм", "Кристаллос", "Аурора", "Вулкан", "Эльдорадо", "Лунтик", "Хаос", "Феникс", "Скай", "Оникс", "Авалон", "Мидгард", "Смауг", "Арагон", "Изерион", "Серафим", "Тайфун"};
    std::vector<std::string> knightNames = {"Артур", "Ланселот", "Гавейн", "Персиваль", "Галахад", "Тристан", "Бедивер", "Гарет", "Гавин", "Ивен"};
    std::shared_ptr<Factory> factoryD = std::make_shared<DragonFactory>();
    std::shared_ptr<Factory> factoryK = std::make_shared<KnightFactory>();
    std::shared_ptr<Factory> factoryP = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> knightNPC;
    std::shared_ptr<NPC> princessNPC;
    std::shared_ptr<NPC> dragonNPC;
    size_t c_p = 0, c_d = 0, c_k = 0;
    while(c_d < dragons || c_p < princesses || c_k < knights) {
        std::string rndName;
        switch (rand() % 3 + 1) {
            case DRAGON:
                if (c_d < dragons) {
                    rndName = dragonNames[std::rand() % dragonNames.size()];
                    dragonNPC = factoryD->create(rndName, rand() % BTF_SIZE, rand() % BTF_SIZE);
                    this->placeHero(dragonNPC);
                    c_d++;
                }
                break;
            case PRINCESS:
                rndName = princessNames[std::rand() % princessNames.size()];
                if (c_p < princesses) {
                    princessNPC = factoryP->create(rndName, rand() % BTF_SIZE, rand() % BTF_SIZE);
                    this->placeHero(princessNPC);
                    c_p++;
                }
                break;
            case KNIGHT:
                if (c_k < knights) {
                    rndName = knightNames[std::rand() % knightNames.size()];
                    knightNPC = factoryK->create(rndName, rand() % BTF_SIZE, rand() % BTF_SIZE);
                    this->placeHero(knightNPC);
                    c_k++;
                }
                break;
            default:
                break;
        }
    }
}

void Battlefield::notify(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender, int cmd) {
    switch (cmd) {
        case Commands::LOSE:
            for (auto obs: _observers) {
                obs->fight(attacker, defender, cmd);
            }
            break;
        case Commands::WIN:
            for (auto obs: _observers) {
                obs->fight(attacker, defender, cmd);
            }
            break;
        case Commands::BATTLE_START:
            for (auto obs: _observers) {
                obs->battleStart(this->_size, this->_npcList);
            }
            break;
        case Commands::BATTLE_END:
            for (auto obs: _observers) {
                obs->battleEnd(this->_size, this->_npcList);
            }
            break;
        default:
            throw std::logic_error("Unknown notify");
        }
}

void Battlefield::placeHero(std::shared_ptr<NPC> npc) {
    if (npc->coords().x < BTF_SIZE && npc->coords().y < BTF_SIZE) _npcList.push_back(npc);
}

void Battlefield::removeDeadmen() {
    _npcList.erase(std::remove_if(_npcList.begin(), _npcList.end(), [](std::shared_ptr<NPC> npc) {return !npc->is_alive(); }), _npcList.end());
}

void Battlefield::removeHero(std::shared_ptr<NPC> npc) {
    if (!_npcList.remove(npc)) {
        throw std::logic_error("NPC not on battlefield");
    }
}

std::list<std::shared_ptr<NPC>> Battlefield::npc() {
    return _npcList;
}

void Battlefield::battle(size_t rounds, double d) {
    this->notify(nullptr, nullptr, Commands::BATTLE_START);
    for (size_t i = 0; i < rounds; ++i) {
        for (auto attacker : _npcList) {
            bool success1;
            bool success2;
            for (auto defender : _npcList) {
                if (attacker != defender && attacker->is_alive() && defender->is_alive() && d > defender->npcDistance(attacker)) {
                    success1 = attacker->accept(defender);
                    this->notify(attacker, defender, success1);
                    success2 = defender->accept(attacker);
                    this->notify(defender, attacker, success2);
                }
            }
        }
        d+=d;
    }
    this->notify(nullptr, nullptr, Commands::BATTLE_END);
}

void ObserverBattlefieldOstream::battleStart(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> npcList) {
    std::cout << std::endl << "-------- Battle started --------" << std::endl;
    std::cout << "There are " << npcList.size() << " fighters." << std::endl;
    for (auto npc: npcList) {
        std::cout << *npc;
    }
    std::cout << std::endl;
}

void ObserverBattlefieldOstream::battleEnd(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> npcList) {
    std::cout << std::endl << "-------- Battle ended --------" << std::endl;
    std::cout << "There was " << npcList.size() << " fighters." << std::endl;
    for (auto npc: npcList) {
        std::cout << *npc;
    }
    std::cout << std::endl;
}


void ObserverBattlefieldOstream::fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) {
    if (win) {
        std::cout << std::endl << "Murder --------" << std::endl;
        std::cout << "Attacker: " << *attacker << "Defender: " << *defender << std::endl;
    } else {
        std::cout << std::endl << "Failed attack attempt --------" << std::endl;
        std::cout << "Attacker: " << *attacker << "Defender: " << *defender << std::endl;
    }
}

ObserverBattlefieldFile::ObserverBattlefieldFile() {
    const time_t tm = time(nullptr);
    char buf[64];
    strftime(buf, std::size(buf), "%d.%m.%Y-%H.%M.%S", localtime(&tm));
    file.open("log" + std::string(buf) + ".txt");
}

ObserverBattlefieldFile::~ObserverBattlefieldFile() {
    file.close();
}

void ObserverBattlefieldFile::fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) {
    if (win) {
        file << '\n' << "Murder --------" << '\n';
        file << "Attacker: " << *attacker << "Defender: " << *defender << '\n';
    } else {
        file << '\n' << "Failed attack attempt --------" << '\n';
        file << "Attacker: " << *attacker << "Defender: " << *defender << '\n';
    }
}

void ObserverBattlefieldFile::battleStart(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> npcList) {
    file << std::endl << "-------- Battle started --------" << std::endl;
    file << "There are " << npcList.size() << " fighters." << std::endl;
    for (auto npc: npcList) {
        file << *npc;
    }
    file << std::endl;
}

void ObserverBattlefieldFile::battleEnd(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> npcList) {
    file << std::endl << "-------- Battle ended --------" << std::endl;
    file << "There was " << npcList.size() << " fighters." << std::endl;
    for (auto npc: npcList) {
        file << *npc;
    }
    file << std::endl;
}