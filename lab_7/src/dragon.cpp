#include "dragon.h"

Dragon::Dragon(std::string npcName, const int &x, const int &y) : NPC{npcName, DRAGON, x, y, RANGE::AR_DRAGON, RANGE::MR_DRAGON} {}

bool Dragon::accept(std::shared_ptr<NPC> defender) {
    VisitorDragon v;
    return v.visit(defender, BACKWARD_COMPATIBILITY);
}

bool VisitorDragon::visit(std::shared_ptr<NPC> defender, bool backward_compatibility) {
    if ((defender->type() == PRINCESS) || (!backward_compatibility)) {
        defender->kill();
        return true;
    } else {
        return false;
    }
}

std::shared_ptr<NPC> DragonFactory::create(std::string npcName, int x, int y) {
    std::shared_ptr<NPC> result = std::make_shared<Dragon>(npcName, x, y);
    return result;
}

std::shared_ptr<NPC> DragonFactory::create(std::istream &is) {
    point tmp;
    is >> tmp.x; is >> tmp.y;
    std::string name_;
    is >> name_;
    std::shared_ptr<NPC> result = std::make_shared<Dragon>(name_, tmp.x, tmp.y);
    return result;
}

std::shared_ptr<NPC> DragonFactory::create(std::ifstream &ifs) {
    int x; int y; int type;
    std::string name_;
    ifs >> x; ifs >> y; ifs >> type; ifs >> name_;
    std::shared_ptr<NPC> result = std::make_shared<Dragon>(name_, x, y);
    return result;
}