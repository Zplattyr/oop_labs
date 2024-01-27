#pragma once
#include "npc.h"

class Dragon : public NPC {
    public:
        Dragon(std::string npcName, const int &x, const int &y);

        bool accept(std::shared_ptr<NPC> defender) override;
};

class VisitorDragon: public Visitor {
    public: 
        bool visit(std::shared_ptr<NPC> defender, bool backward_compatibility) override;
};

class DragonFactory : public Factory {
    public:
        std::shared_ptr<NPC> create(std::string npcName, int x, int y) override;
        std::shared_ptr<NPC> create(std::istream &is) override;
        std::shared_ptr<NPC> create(std::ifstream &ifs) override;
};