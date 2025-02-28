#include <iostream>
#include <cstdlib>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner WinnerInRounds;
	string WinnerNameInRounds = "";
};

struct stGameResult
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner WinnerInGame;
	string WinnerNameInGame = "";
};

int RandomNumber(int From, int To)
{
	int RandNum = 0;

	RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

string Tabs(short NumberOfTabs)
{
	string Tab = "";

	for (int i = 0; i < NumberOfTabs; i++)
	{
		Tab = Tab + "\t";
	}
	return Tab;
}

string Slash(short NumberOfSlash)
{
	string Slash = "";

	for (int i = 0; i < NumberOfSlash; i++)
	{
		Slash = Slash + "_";
	}
	return Slash;
}

short ReadHowManyRounds()
{
	short HowManyRounds = 0;

	do
	{
		cout << "Please Enter How Many Rounds You Want to Play From 1 to 10?" << endl;
		cin >> HowManyRounds;

	} while (HowManyRounds < 1 || HowManyRounds > 10);
	return HowManyRounds;
}

enGameChoice ReadPlayer1Choice()
{
	short Player1Choice = 0;

	do
	{
		cout << "Your Choice : [1]:Stone , [2]:Paper , [3]:Scissors? ";
		cin >> Player1Choice;

	} while (Player1Choice < 1 || Player1Choice > 3);
	return (enGameChoice)Player1Choice;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWinnerTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Stone:
	{
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;
	}
	case enGameChoice::Paper:
	{
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;
	}
	case enGameChoice::Scissors:
	{
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;
	}
	};

	return enWinner::Player1;
}

enWinner WhoWinnerTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
	{
		return enWinner::Player1;
	}
	else if (ComputerWinTimes > Player1WinTimes)
	{
		return enWinner::Computer;
	}
	else
	{
		return enWinner::Draw;
	}
}

string WinnerName(enWinner Winner)
{
	string ArrWinnerName[3] = { "Player1","Computer","No Winner" };
	return ArrWinnerName[Winner - 1];
}

string ChoiceName(enGameChoice Choice)
{
	string ArrGameChoice[3] = { "Stone", "Paper", "Scissors" };
	return ArrGameChoice[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
	{
		system("Color 2F");
		break;
	}
	case enWinner::Computer:
	{
		cout << "\a";
		system("Color 4F");
		break;
	}
	default:
	{
		system("Color 6F");
		break;
	}
	};
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
	cout << endl << endl << Slash(20) << "Round [" << RoundInfo.RoundNumber << "]" << Slash(30) << endl << endl;
	cout << "Player1 Choice      : " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice     : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner        : [" << RoundInfo.WinnerNameInRounds << "]" << endl;
	cout << Slash(59) << endl;

	SetWinnerScreenColor(RoundInfo.WinnerInRounds);
}

stGameResult FillGameResult(short GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResult GameResult;

	GameResult.GameRounds = GameRounds;
	GameResult.Player1WinTimes = Player1WinTimes;
	GameResult.ComputerWinTimes = ComputerWinTimes;
	GameResult.DrawTimes = DrawTimes;
	GameResult.WinnerInGame = WhoWinnerTheGame(Player1WinTimes, ComputerWinTimes);
	GameResult.WinnerNameInGame = WinnerName(GameResult.WinnerInGame);

	return GameResult;
}

stGameResult PlayGame(short HowManyRounds)
{
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	stRoundInfo RoundInfo;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] : begins :" << endl << endl;

		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.WinnerInRounds = WhoWinnerTheRound(RoundInfo);
		RoundInfo.WinnerNameInRounds = WinnerName(RoundInfo.WinnerInRounds);

		PrintRoundResult(RoundInfo);

		if (RoundInfo.WinnerInRounds == enWinner::Player1)
		{
			Player1WinTimes++;
		}
		else if (RoundInfo.WinnerInRounds == enWinner::Computer)
		{
			ComputerWinTimes++;
		}
		else
		{
			DrawTimes++;
		}
	}

	return FillGameResult(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

void ShowGameOverScreen()
{
	cout << endl << endl << Tabs(3) << Slash(57) << endl << endl;
	cout << Tabs(5) << "    +++ Game Over +++" << endl << endl;
	cout << Tabs(3) << Slash(57) << endl << endl;
}

void ShowFinalGameResultOnScreen(stGameResult GameResult)
{
	cout << Tabs(3) << Slash(20) << " [ Game Result ] " << Slash(20) << endl << endl;
	cout << Tabs(3) << "Game Rounds              : " << GameResult.GameRounds << endl;
	cout << Tabs(3) << "Player1 Won Times        : " << GameResult.Player1WinTimes << endl;
	cout << Tabs(3) << "Computer Won Times       : " << GameResult.ComputerWinTimes << endl;
	cout << Tabs(3) << "Draw Times               : " << GameResult.DrawTimes << endl;
	cout << Tabs(3) << "Fianl Winner             : " << GameResult.WinnerNameInGame << endl;
	cout << Tabs(3) << Slash(57) << endl;
}

void ResetScreen()
{
	system("cls");
	system("Color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stGameResult GameResult = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResultOnScreen(GameResult);

		cout << endl << Tabs(3) << "Do You Want to Play Again Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}