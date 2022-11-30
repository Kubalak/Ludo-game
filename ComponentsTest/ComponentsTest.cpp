#include "pch.h"
#include "CppUnitTest.h"
#include "../BaseEngine/Tile.hpp"
#include "../BaseEngine/Player.hpp"
#include "../BaseEngine/Dice.hpp"
#include "../BaseEngine/PlayerContainer.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ComponentsTest
{	Player first("First"), second("second");
	std::array<Counter*, 4> firstc = first.getCounters(), secondc = second.getCounters();
	

	TEST_CLASS(TileTest)
	{
	public:
		
		TEST_METHOD(AddToTileTest)
		{
			Tile tile;
			Assert::IsTrue(tile.addToTile(firstc[0]));
		}
		TEST_METHOD(AddSizeTest)
		{
			Tile tile;
			tile.addToTile(firstc[0]);
			Assert::AreEqual(1, static_cast<int>(tile.getCounters().size()));
		}
		TEST_METHOD(DoubleAdditionTest)
		{
			Tile tile;
			tile.addToTile(firstc[0]);
			Assert::IsFalse(tile.addToTile(firstc[0]));
		}
		TEST_METHOD(DoubleAdditionSizeTest)
		{
			Tile tile;
			tile.addToTile(firstc[0]);
			tile.addToTile(firstc[0]);
			Assert::AreEqual(1, static_cast<int>(tile.getCounters().size()));
		}
		TEST_METHOD(AddDifferentTest) {
			Tile tile;
			tile.addToTile(firstc[0]);
			Assert::IsTrue(tile.addToTile(secondc[0]));
		}
		TEST_METHOD(AddDifferentSizeTest) {
			Tile tile;
			tile.addToTile(firstc[0]);
			tile.addToTile(firstc[2]);
			tile.addToTile(secondc[0]);
			Assert::AreEqual(1, static_cast<int>(tile.getCounters().size()));
		}
		TEST_METHOD(AddDifferentObjectTest) {
			Tile tile;
			tile.addToTile(firstc[0]);
			tile.addToTile(firstc[2]);
			tile.addToTile(secondc[0]);
			Assert::IsTrue(tile.getCounters()[0] == secondc[0]);
		}
		TEST_METHOD(LastBeatSizeTest) {
			Tile tile;
			tile.addToTile(firstc[0]);
			tile.addToTile(firstc[2]);
			tile.addToTile(secondc[0]);
			Assert::AreEqual(2, static_cast<int>(tile.lastBeat.size()));
		}
		TEST_METHOD(LastBeatObjectTest) {
			Tile tile;
			tile.addToTile(firstc[0]);
			tile.addToTile(firstc[2]);
			tile.addToTile(secondc[0]);
			Assert::IsTrue(tile.lastBeat[0] == firstc[0] && tile.lastBeat[1] == firstc[2]);
		}
		TEST_METHOD(moveCounterTest) {
			Tile a, b;
			a.addToTile(firstc[0]);
			a.addToTile(firstc[1]);
			Assert::IsTrue(a.movePlayerCounter(b, first));
		}
		TEST_METHOD(moveCounterFSizeTest) {
			Tile a, b;
			a.addToTile(firstc[0]);
			a.addToTile(firstc[1]);
			a.movePlayerCounter(b, first);
			Assert::AreEqual(1U, a.getCounters().size());;
		}
		TEST_METHOD(moveCounterSSizeTest) {
			Tile a, b;
			a.addToTile(firstc[0]);
			a.addToTile(firstc[1]);
			a.movePlayerCounter(b, first);
			Assert::AreEqual(1U, b.getCounters().size());;
		}
	};
	/*TEST_CLASS(PlayerTest) // Nie potrzeba wiêcej testów - brak zmian.
	{
	public:
		TEST_METHOD(IdTest) {
			Player p("Player", 10);
			Assert::AreEqual(10, static_cast<int>(p.getId()));
		}
		TEST_METHOD(CounterContainerTest) {
			Assert::AreEqual(4, static_cast<int>(first.getCounters().size()));
		}
		TEST_METHOD(PlayerCounterUniqueTest) {
			bool unique = true;
			for (unsigned int i = 0; i < first.getCounters().size(); ++i)
				for (unsigned int j = i + 1; j < first.getCounters().size(); ++j)
					if (firstc[i] == firstc[j])
						unique = false;
			Assert::IsTrue(unique);
		}
		TEST_METHOD(PlayerCounterOwnershipTest) {
			Assert::AreEqual(first.getId(), firstc[0]->getOwner());
		}
	};*/
	/*TEST_CLASS(DiceTest) { // Nie potrzeba wiêcej testów
		Dice dice;
	public:
		TEST_METHOD(LastTest) {
			unsigned int value = dice.roll();
			Assert::AreEqual(value, dice.getLast());
		}
	};*/
	TEST_CLASS(PlayerContainerTest) {
		
	public:
		TEST_METHOD(HolderSizeTest) {
			PlayerContainer PC1(new Player(), 0);
			Assert::AreEqual(4U, PC1.holderCount());
		}
		TEST_METHOD(HolderPopTest) {
			PlayerContainer PC1(new Player(), 0);
			Assert::IsNotNull(PC1.holderPop());
		}
		TEST_METHOD(EmptyHolderPopTest) {
			PlayerContainer PC1(new Player(), 0);
			PC1.holderPop();
			PC1.holderPop();
			PC1.holderPop();
			PC1.holderPop();
			Assert::IsNull(PC1.holderPop());
		}
		TEST_METHOD(AddToHolderTest) {
			PlayerContainer PC1(new Player(), 0);
			Counter* c = PC1.holderPop();
			Assert::IsTrue(PC1.addToHolder(c));
		}
		TEST_METHOD(AddExistingToHolderTest) {
			Player* p = new Player();
			PlayerContainer PC1(p, 0);
			Counter* c = p->getCounters()[0];
			Assert::IsFalse(PC1.addToHolder(c));
		}
		TEST_METHOD(AddNotOwnedToHolderTest) {
			Player* p = new Player();
			Player p1;
			PlayerContainer PC1(p, 0);
			Counter* c = p1.getCounters()[0];
			PC1.holderPop();
			Assert::IsFalse(PC1.addToHolder(c));
		}
		TEST_METHOD(AddToLastTest) {
			PlayerContainer PC1(new Player(), 0);
			Counter* c = PC1.holderPop();
			Assert::IsTrue(PC1.addToLast(c));
		}
		TEST_METHOD(AddToLastExistInHolderTest) {
			Player* p = new Player();
			PlayerContainer PC1(p, 0);
			Counter* c = p->getCounters()[0];
			Assert::IsFalse(PC1.addToLast(c));
		}
		TEST_METHOD(AddToLastNotOwnedTest) {
			Player* p = new Player();
			Player p1;
			PlayerContainer PC1(p, 0);
			Counter* c = p1.getCounters()[0];
			PC1.holderPop();
			Assert::IsFalse(PC1.addToLast(c));
		}
		TEST_METHOD(AddToLastExistInFirstLastTest) {
			PlayerContainer PC1(new Player(), 0);
			Counter* c = PC1.holderPop();
			PC1.addToLast(c);
			Assert::IsFalse(PC1.addToLast(c));
		}
		TEST_METHOD(AddToLastExistInLastTest) {
			PlayerContainer PC1(new Player(), 0);
			Counter* c = PC1.holderPop();
			PC1.addToLast(c);
			Assert::IsFalse(PC1.addToLast(c,1));
		}
		TEST_METHOD(IsFinishedTest) {
			PlayerContainer PC1(new Player(), 0);
			PC1.addToLast(PC1.holderPop());
			Assert::IsFalse(PC1.allIn());
		}
		TEST_METHOD(IsFinishedAllOnFirstTest) {
			PlayerContainer PC1(new Player(), 0);
			Counter* c;
			while ((c = PC1.holderPop()) != nullptr)
				PC1.addToLast(c);
			Assert::IsFalse(PC1.allIn());
		}
		TEST_METHOD(IsFinishedAllOnLastTest) {
			PlayerContainer PC1(new Player(), 0);
			Counter* c;
			while ((c = PC1.holderPop()) != nullptr)
				PC1.addToLast(c, 5);
			Assert::IsTrue(PC1.allIn());
		}
		TEST_METHOD(CanMoveTest) {
			PlayerContainer PC1(new Player(), 0);
			Assert::IsFalse(PC1.canMove());
		}
		TEST_METHOD(CanMoveCounterOnFirstTest) {
			PlayerContainer PC1(new Player(), 0);
			PC1.addToLast(PC1.holderPop());
			Assert::IsTrue(PC1.canMove());
		}
		TEST_METHOD(CanMoveAllOnLastTest) {
			PlayerContainer PC1(new Player(), 0);
			Counter* c;
			while ((c = PC1.holderPop()) != nullptr)
				PC1.addToLast(c, 5);
			Assert::IsFalse(PC1.canMove());
		}
	};
	//TODO: Sprawdziæ pozosta³e metody i czy gettery do wszystkiego co konieczne istniej¹.
}
