#include "knight.h"

Knight::Knight(std::string npcName, const int &x, const int &y) : NPC{npcName, KNIGHT, x, y} {}

bool Knight::accept(std::shared_ptr<NPC> defender) {
    VisitorKnight v;
    return v.visit(defender);
}

bool VisitorKnight::visit(std::shared_ptr<NPC> defender) {
    if (defender->type() == DRAGON) {
        defender->kill();
        return true;
    } else {
        return false;
    }
}

std::shared_ptr<NPC> KnightFactory::create(std::string npcName, int x, int y) {
    std::shared_ptr<NPC> result = std::make_shared<Knight>(npcName, x, y);
    return result;
}

std::shared_ptr<NPC> KnightFactory::create(std::istream &is) {
    point tmp;
    is >> tmp.x; is >> tmp.y;
    std::string name_;
    is >> name_;
    std::shared_ptr<NPC> result = std::make_shared<Knight>(name_, tmp.x, tmp.y);
    return result;
}

std::shared_ptr<NPC> KnightFactory::create(std::ifstream &ifs) {
    int x; int y; int type;
    std::string name_;
    ifs >> x; ifs >> y; ifs >> type; ifs >> name_;
    std::shared_ptr<NPC> result = std::make_shared<Knight>(name_, x, y);
    return result;
}