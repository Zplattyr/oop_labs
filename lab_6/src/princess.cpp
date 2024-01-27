#include "princess.h"

Princess::Princess(std::string npcName, const int &x, const int &y) : NPC{npcName, PRINCESS, x, y} {}

bool Princess::accept(std::shared_ptr<NPC> defender) {
    VisitorPrincess v;
    return v.visit(defender);
}

bool VisitorPrincess::visit(std::shared_ptr<NPC> defender) {
    return false;
}

std::shared_ptr<NPC> PrincessFactory::create(std::string npcName, int x, int y) {
    std::shared_ptr<NPC> result = std::make_shared<Princess>(npcName, x, y);
    return result;
}

std::shared_ptr<NPC> PrincessFactory::create(std::istream &is) {
    point tmp;
    is >> tmp.x; is >> tmp.y;
    std::string name_;
    is >> name_;
    std::shared_ptr<NPC> result = std::make_shared<Princess>(name_, tmp.x, tmp.y);
    return result;
}

std::shared_ptr<NPC> PrincessFactory::create(std::ifstream &ifs) {
    int x; int y; int type;
    std::string name_;
    ifs >> x; ifs >> y; ifs >> type; ifs >> name_;
    std::shared_ptr<NPC> result = std::make_shared<Princess>(name_, x, y);
    return result;
}