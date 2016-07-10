#include "Game.h"

Game::Game()
{
}

Game::Game(Player player1, Player player2, char* word, char* input) : player1(player1), player2(player2), word(word), input(input)
{
}

bool Game::letterInput() //Verify the letter
{
	cout << endl;
	setw("Digite un car\240cter:\n");
	char letter = toupper(readString()[0]);
	int index = word.find(letter);
	if (index >= 0 && input[index] == letter)
		return true;
	bool pass = false;
	while (index >= 0)
	{
		pass = true;
		input[index] = letter;
		index = word.find(letter, index + 1);
	}
	return pass;
}

void Game::setw(string i, int q)
{
	int pos;
	if (q == 0)
		pos = (80 - strlen(i.c_str())) / 2;
	else
		pos = (80 - q) / 2;
	for (int j = 0; j < pos; j++)
		cout << " ";
	if (q == 0)
		cout << i;
	else
		for (int j = 0; j < q; j++)
			cout << i[j];
}

void Game::UI()
{
	/* system("Color XY") X= color fondo Y= color letras
	0 = Negro       8 = Gris
	1 = Azul        9 = Azul claro
	2 = Verde       A = Verde claro
	3 = Aguamarina  B = Aguamarina claro
	4 = Rojo        C = Rojo claro
	5 = Púrpura     D = Púrpura claro
	6 = Amarillo    E = Amarillo claro
	7 = Blanco      F = Blanco brillante
	*/
	system("Color F2");
	setw("Bienvenido al juego del ahorcado\n");
	cout << endl;
	setw("Ingrese el nombre del primer jugador:\n");
	player1.setName(readString());
	cout << endl;
	setw("Ingrese el nombre del segundo jugador:\n");
	player2.setName(readString());
	bool turn = true; //which player goes, true is first player
	do
	{
		system("cls");
		if (turn)
		{
			system("Color F5");
			setw(player1.getName() + " c\243al es la palabra que desea que " + player2.getName() + " adivine?\n");
		}
		else
		{
			system("Color F3");
			setw(player2.getName() + " c\243al es la palabra que desea que " + player1.getName() + " adivine?\n");
		}
		word = readString();
		input.clear();
		for (int i = 0; i < word.size(); i++)
			word[i] = toupper(word[i]);
		input.resize(word.size(), '\376');
		int attempts = 0; //max of 7
		while (attempts < 7) //game
		{
			system("cls");
			if (turn)
			{
				system("Color F3");
				setw(player2.getName() + " tienes " + static_cast<char>((7 - attempts) + '0') + " intento/s.\n");
			}
			else
			{
				system("Color F5");
				setw(player1.getName() + " tienes " + static_cast<char>((7 - attempts) + '0') + " intento/s.\n");
			}
			print(attempts);
			if (!letterInput())
				++attempts;
			if (isWinner())
			{
				if (turn)
				{
					cout << endl;
					setw("Felicidades " + player2.getName() + " has ganado.\n");
					player2.setPoints(player2.getPoints() + 1);
					save(player2); //Save points and name
				}
				else
				{
					cout << endl;
					setw("Felicidades " + player1.getName() + " has ganado.\n");
					player1.setPoints(player1.getPoints() + 1);
					save(player1); //Save points and name
				}
				cin.get();
				break;
			}
			if (attempts == 7)
			{
				system("cls");
				system("Color FC");
				setw("Has PERDIDO!\n");
				print(attempts);
				cin.get();
			}
		}
		turn = !turn; //change turns
	}
	while (option());//if decides to continue
}

void Game::print(int i)
{
	cout << endl;
	switch (i)
	{
	case 0:
		{
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			break;
		}
	case 1:
		{
			setw("\304\304\304\277   \n");
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			break;
		}
	case 2:
		{
			setw("\304\304\304\277   \n");
			setw("   \262   \n");
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			break;
		}
	case 3:
		{
			setw("\304\304\304\277   \n");
			setw("   \262   \n");
			setw("   \263   \n");
			setw("   \263   \n");
			setw("   \263   \n");
			cout << endl;
			break;
		}
	case 4:
		{
			setw("\304\304\304\277   \n");
			setw("   \262   \n");
			setw("  \134\263   \n");
			setw("   \263   \n");
			setw("   \263   \n");
			cout << endl;
			break;
		}
	case 5:
		{
			setw("\304\304\304\277   \n");
			setw("   \262   \n");
			setw("  \134\263\057  \n");
			setw("   \263   \n");
			setw("   \263   \n");
			cout << endl;
			break;
		}
	case 6:
		{
			setw("\304\304\304\277   \n");
			setw("   \262   \n");
			setw("  \134\263\057  \n");
			setw("   \263   \n");
			setw("   \263   \n");
			setw("  \057    \n");
			break;
		}
	case 7:
		{
			setw("\304\304\304\277   \n");
			setw("   \262   \n");
			setw("  \134\263\057  \n");
			setw("   \263   \n");
			setw("   \263   \n");
			setw("  \057 \134  \n");
			break;
		}
	}
	cout << endl;
	setw(input, word.size());
	cout << endl;
}

bool Game::isWinner() const
{
	return word.compare(input) == 0;
}

void Game::save(Player p) const
{
	ofstream file;
	file.open(p.getName() + ".txt", ios::app);
	if (file.is_open())
		file << "Palabra: " << word << ", Puntaje: " << p.getPoints() << endl;
	else
	{
		cout << "No se pudo crear o acceder al registro\n";
		cin.get();
	}
	file.close();
}

bool Game::option()
{
	system("cls");
	system("Color F1");
	setw("Desea continuar, SI o NO?: ");
	return toupper(readString()[0]) == 'S';
}

string Game::readString()
{
	string i;
	getline(cin, i);
	if (i == "")
		return readString();
	return i;
}

Game::~Game()
{
}
