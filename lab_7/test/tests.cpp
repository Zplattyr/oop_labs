#include <gtest/gtest.h>
#include <vector>
#include "battlefield.h"

TEST(FactoryTest, TEST_01) {
    std::shared_ptr<Factory> fD = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fD->create("testname", 10,20);
    ASSERT_TRUE(dragon->type() == DRAGON && dragon->coords().x == 10 && dragon->coords().y == 20);
}

TEST(FactoryTest, TEST_02) {
    std::shared_ptr<Factory> fK = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fK->create("testname", 10,20);
    ASSERT_TRUE(knight->type() == KNIGHT && knight->coords().x == 10 && knight->coords().y == 20);
}

TEST(FactoryTest, TEST_03) {
    std::shared_ptr<Factory> fP = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fP->create("testname", 10,20);
    ASSERT_TRUE(princess->type() == PRINCESS && princess->coords().x == 10 && princess->coords().y == 20);
}

TEST(BattleCheck, TEST_01) {
    std::shared_ptr<Factory> fP = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fP->create("testname", 10,20);
    std::shared_ptr<Factory> fK = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fK->create("testname", 10,20);
    ASSERT_TRUE(!princess->accept(knight));
}

TEST(BattleCheck, TEST_02) {
    std::shared_ptr<Factory> fP = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fP->create("testname", 10,20);
    std::shared_ptr<Factory> fK = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fK->create("testname", 10,20);
    ASSERT_TRUE(!princess->accept(knight) && !knight->accept(princess));
}

TEST(BattleCheck, TEST_03) {
    std::shared_ptr<Factory> fP = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fP->create("testname", 10,20);
    std::shared_ptr<Factory> fD = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fD->create("testname", 10,20);
    std::cout << dragon->accept(princess) << ' ' << !princess->accept(dragon) << std::endl;
    ASSERT_TRUE(dragon->accept(princess) && !princess->accept(dragon));
}

TEST(BattleCheck, TEST_04) {
    std::shared_ptr<Factory> fK = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fK->create("testname", 10,20);
    std::shared_ptr<Factory> fD = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fD->create("testname", 10,20);
    ASSERT_TRUE(!dragon->accept(knight) && knight->accept(dragon));
}

TEST(Kill, TEST_01) {
    std::shared_ptr<Factory> fK = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fK->create("testname", 10,20);
    std::shared_ptr<Factory> fD = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fP = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fP->create("testname", 10,20);
    knight->kill(); dragon->kill(); princess->kill();
    ASSERT_TRUE(!knight->is_alive() && !dragon->is_alive() && !princess->is_alive());
}

TEST(Distance, TEST_01) {
    std::shared_ptr<Factory> fK = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fK->create("testname", 10,20);
    std::shared_ptr<Factory> fD = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fP = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fP->create("testname", 30,20);
    ASSERT_TRUE(fabs(princess->npcDistance(dragon) - 20) < ESPILON);
}

TEST(Distance, TEST_02) {
    std::shared_ptr<Factory> fK = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fK->create("testname", 10,20);
    std::shared_ptr<Factory> fD = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fP = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fP->create("testname", -30, -20);
    ASSERT_TRUE(fabs(princess->npcDistance(dragon) - 56.568) < ESPILON);
}

TEST(BattlefieldTEST, TEST_01) {
    std::shared_ptr<Factory> fK = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fK->create("testname", 10,20);
    std::shared_ptr<Factory> fD = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fP = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fP->create("testname", -30,-20);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(knight);
    btf->placeHero(dragon);
    btf->placeHero(princess);
    ASSERT_TRUE(btf->npc().size() == 3);
}

TEST(BattlefieldTEST, TEST_02) {
    std::shared_ptr<Factory> fK = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fK->create("testname", 10,20);
    std::shared_ptr<Factory> fD = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fP = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fP->create("testname", 10,20);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(knight);
    btf->placeHero(dragon);
    btf->placeHero(princess);
    ASSERT_NO_THROW(btf->battle(1,2));
}

TEST(BattlefieldTEST, TEST_03) {
    std::shared_ptr<Factory> fK = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fK->create("testname", 10,20);
    std::shared_ptr<Factory> fD = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fP = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fP->create("testname", 10,20);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(knight);
    btf->placeHero(dragon);
    btf->placeHero(princess);
    btf->battle(1,2);
    btf->removeDeadmen();
    ASSERT_TRUE(btf->npc().size() == 2);
}

TEST(BattlefieldTEST, TEST_04) {
    std::shared_ptr<Factory> fK = std::make_shared<KnightFactory>();
    std::shared_ptr<NPC> knight = fK->create("testname", 10,20);
    std::shared_ptr<Factory> fD = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> dragon = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fP = std::make_shared<PrincessFactory>();
    std::shared_ptr<NPC> princess = fP->create("testname", 10,20);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->fillRandomly(1,10,10,10);
    ASSERT_TRUE(btf->npc().size()==30);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}