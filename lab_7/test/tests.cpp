#include <gtest/gtest.h>
#include <vector>
#include "battlefield.h"

TEST(FactoryTest, TEST_01) {
    std::shared_ptr<DragonFactory> fD = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fD->create("TEST", 10,20);
    ASSERT_TRUE(dragon->type() == DRAGON && dragon->coords().x == 10 && dragon->coords().y == 20);
}

TEST(FactoryTest, TEST_02) {
    std::shared_ptr<Factory> fD = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fD->create("TEST", 10,20);
    ASSERT_TRUE(knight->type() == KNIGHT && knight->coords().x == 10 && knight->coords().y == 20);
}

TEST(FactoryTest, TEST_03) {
    std::shared_ptr<Factory> fD = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fD->create("TEST", 10,20);
    ASSERT_TRUE(princess->type() == PRINCESS && princess->coords().x == 10 && princess->coords().y == 20);
}

TEST(BattleCheck, TEST_01) {
    std::shared_ptr<Factory> fD = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fD->create("TEST", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fO->create("TEST", 10,20);
    ASSERT_NO_THROW(!princess->accept(knight));
}

TEST(BattleCheck, TEST_02) {
    std::shared_ptr<Factory> fD = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fD->create("TEST", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fO->create("TEST2", 10,20);
    std::shared_ptr<VisitorKnight> v1 = std::make_shared<VisitorKnight>();
    std::shared_ptr<VisitorPrincess> v2 = std::make_shared<VisitorPrincess>();
    ASSERT_NO_THROW(!princess->accept(knight) && !knight->accept(princess));
}

TEST(BattleCheck, TEST_03) {
    std::shared_ptr<Factory> fD = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fD->create("TEST", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fO->create("TEST2", 10,20);
    ASSERT_NO_THROW(dragon->accept(princess) && !princess->accept(dragon));
}

TEST(BattleCheck, TEST_04) {
    std::shared_ptr<Factory> fD = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fD->create("TEST", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fO->create("TEST2", 10,20);
    ASSERT_NO_THROW(!dragon->accept(knight) && knight->accept(dragon));
}

TEST(Kill, TEST_01) {
    std::shared_ptr<Factory> fD = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fD->create("TEST", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fO->create("TEST2", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fS->create("TEST3", 10,20);
    knight->kill(); dragon->kill(); princess->kill();
    ASSERT_TRUE(!knight->is_alive() && !dragon->is_alive() && !princess->is_alive());
}

TEST(Distance, TEST_01) {
    std::shared_ptr<Factory> fD = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fD->create("TEST", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fO->create("TEST2", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fS->create("TEST3", 30,20);
    ASSERT_TRUE(fabs(princess->npcDistance(dragon) - 20) < ESPILON);
}

TEST(Distance, TEST_02) {
    std::shared_ptr<Factory> fD = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fD->create("TEST", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fO->create("TEST2", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fS->create("TEST3", -30,-20);
    ASSERT_TRUE(fabs(princess->npcDistance(dragon) - 56.568) < ESPILON);
}

TEST(BattlefieldTEST, TEST_01) {
    std::shared_ptr<Factory> fD = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fD->create("TEST", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fO->create("TEST2", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fS->create("TEST3", -30,-20);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(knight);
    btf->placeHero(dragon);
    btf->placeHero(princess);
    ASSERT_TRUE(btf->npc().size() == 3);
}

TEST(BattlefieldTEST, TEST_02) {
    std::shared_ptr<Factory> fD = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fD->create("TEST", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fO->create("TEST2", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fS->create("TEST3", 10,20);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(knight);
    btf->placeHero(dragon);
    btf->placeHero(princess);
    ASSERT_NO_THROW(btf->battle());
}

TEST(BattlefieldTEST, TEST_04) {
    std::shared_ptr<Factory> fD = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fD->create("TEST", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fO->create("TEST2", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fS->create("TEST3", 10,20);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->fillRandomly(10,10,10);
    ASSERT_TRUE(btf->npc().size()==30);
}


TEST(NPCmoveTEST, TEST_01) {
    std::shared_ptr<Factory> fD = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fD->create("TEST", 0, 0);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(knight);
    knight->move(10, 10);
    bool check = false;
    for (auto &&npc : btf->npc())
    {
        if ((npc->coords().x == 10) && (npc->coords().y == 10)) check = true;
    }
    
    ASSERT_TRUE(check);
}

TEST(NPCmoveTEST, TEST_02) {
    std::shared_ptr<Factory> fD = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fD->create("TEST", 10, 10);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(knight);
    knight->move(-10,-10);
    bool check = false;
    for (auto &&npc : btf->npc())
    {
        if ((npc->coords().x == 0) && (npc->coords().y == 0)) check = true;
    }
    
    ASSERT_TRUE(check);
}

TEST(NPCmoveTEST, TEST_03) {
    std::shared_ptr<Factory> fD = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fD->create("TEST", 10, 10);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(knight);
    knight->move(-20,-11);
    bool check = false;
    for (auto &&npc : btf->npc())
    {

        if ((npc->coords().x == 10) && (npc->coords().y == 10)) check = true;
    }
    
    ASSERT_TRUE(check);
}

TEST(NPCmoveTEST, TEST_04) {
    std::shared_ptr<Factory> fD = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fD->create("TEST", BTF_SIZE-1, BTF_SIZE-1);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(knight);
    knight->move(1,1);
    bool check = false;
    for (auto &&npc : btf->npc())
    {
        if ((npc->coords().x == BTF_SIZE) && (npc->coords().y == BTF_SIZE)) check = true;
    }
    
    ASSERT_TRUE(check);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
