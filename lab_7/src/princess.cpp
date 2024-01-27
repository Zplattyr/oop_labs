#include "princess.h"

Princess::Princess(std::string npcName, const int &x, const int &y) : NPC{npcName, PRINCESS, x, y,RANGE::AR_PRINCESS, RANGE::MR_PRINCESS} {}

bool Princess::accept(std::shared_ptr<NPC> defender) {
    VisitorPrincess v;
    return v.visit(defender, BACKWARD_COMPATIBILITY);
}

bool VisitorPrincess::visit(std::shared_ptr<NPC> defender, bool backward_compatibility) {
    if (!backward_compatibility){
        defender->kill();
        return true;
    } else {
        return false;
    }
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