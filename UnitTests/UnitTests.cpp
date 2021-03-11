 
#include "pch.h"
#include "CppUnitTest.h"


#include "../9MensMorris/9MensMorris.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(TestRedPlacement)
		{
			morisGame* Board = new morisGame;
			Board->setBoard();
			Board->setBoardPiece(0);
			bool chk = Board->boardSpaces[0]->isPlayerOne();
			Assert::AreEqual(chk, true);

		}
	};
}
