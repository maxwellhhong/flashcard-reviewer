#include "deck.hpp"

Deck::Deck(const std::string &filename) {
  std::ifstream ifs{filename};
  if (!ifs.is_open()) { throw new std::invalid_argument("File not found."); }

  ifs >> flashcards_len >> flashcards_width >> default_front >> default_back;
  if (ifs.fail()) {
    throw new std::runtime_error("File has wrong format."); 
  } else if ((default_front >= flashcards_width) | (default_back >= flashcards_width)) {
    throw new std::invalid_argument("Invalid default side values.");
  }

  ConstructEmpty2dStringArray(flashcards, flashcards_len, flashcards_width);
  Fill2dStringArray(ifs, flashcards, flashcards_len, flashcards_width);

  shuffle_representation = new IntDeck(flashcards_len);
}

Deck::~Deck() {
  for (size_t i = 0; i < flashcards_len; i++) {
    delete[] flashcards[i];
  }
  delete[] flashcards;
  flashcards = nullptr;
  flashcards_len = 0;
}

void Deck::Draw() {
  (*shuffle_representation).RandomChoose();
  PrintSide(default_front);
  std::cout << std::endl << std::endl;
  show_lock = false;
}

void Deck::Show() {
  if (show_lock) { 
    std::cout << "Draw a card first!" << std::endl;
    return;
  }
  (*shuffle_representation).SetReinsertedFalse();
  PrintSide(default_front);
  std::cout << " : ";
  PrintSide(default_back);
  std::cout << std::endl << std::endl;
}

void Deck::PrintSide(size_t side) {
  if ((*shuffle_representation).GetCurrentFlag() != nullptr) {
    std::cout << GetSide(((*shuffle_representation).GetCurrentFlag())->next->num, side);
  }
}

void ConstructEmpty2dStringArray(std::string** &ptr, size_t height, size_t width) {
  ptr = new std::string*[height];
  for (size_t i = 0; i < height; i++) {
    ptr[i] = new std::string[width];
  }
}

void Fill2dStringArray(std::ifstream &input, std::string** &ptr, size_t height, size_t width) {
  size_t i = 0;
  size_t j = 0;

  std::string side;
  char ch;

  input.get(ch);
  if (ch != '\n') { throw new std::runtime_error("File formatted incorrectly."); }

  while (input.get(ch)) {
    if ((i >= width) | (j >= height)) {
        throw new std::invalid_argument("File does not match given height and width.");
    }
    switch (ch) {
      case '|':
        ptr[j][i] = side;
        side.clear();
        i++;
        break;
      case '\n':
        ptr[j][i] = side;
        side.clear();
        i = 0;
        j++;
        break;
      default:
        side.push_back(ch);
    }
  }

  ptr[j][i] = side;
  side.clear();
}

void Deck::Interface() {
  std::cout << "Type 'h' for [h]elp! Type 't' to [t]erminate/stop this program!\n" << std::endl;
  bool cont_interface = true;
  while (cont_interface) {
    
    std::cout << "Command: ";

    if (isdigit(std::cin.peek())) {
      CommandInterpreterDigit();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    char input_ch;
    std::cin >> input_ch;

    if (std::cin.peek() != '\n') {
      std::cout << "Use a single character!\n" << std::endl;
    } else if (isdigit(input_ch)) {
        std::cout << "Incorrect number format!\n" << std::endl;
    } else if (input_ch == 't') {
      std::cout << "Program [t]erminated!\n" << std::endl;
      cont_interface = false;
    } else {
      CommandInterpreterChar(input_ch);
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

void Deck::CommandInterpreterDigit() {
  size_t number;
  std::cin >> number;

  if (std::cin.peek() != '\n') {
    std::cout << "Incorrect number format!\n" << std::endl;
  } else if (number >= flashcards_width) {
    std::cout << "Side number out of range!\n" << std::endl;
  } else {
    PrintSide(number);
  }
}

void Deck::CommandInterpreterChar(char ch) {
  switch (ch) {
    case ('d'):
      ClearTerm();
      std::cout << "[d]raw:\n" << std::endl;
      Draw();
      break;
    case ('s'):
      ClearTerm();
      std::cout << "[s]how:\n" << std::endl;
      Show();
      break;
    case ('i'):
      Reinsert();
      std::cout << "Card re[i]nserted!\n" << std::endl;
      break;
    case ('r'):
      ClearTerm();
      Reset();
      std::cout << "Deck [r]eset!\n" << std::endl;
      break;
    case ('h'):
      Help();
      break;
    case ('m'): 
      More();
      break;
    case ('f'):
      FlashcardDeckFormatting();
      break;
    default:
      std::cout << "No such command!\n" << std::endl;
  }
}

void ClearTerm() {
  system("clear"); // for linux/mac
  // system("cls"); // for windows
}

void Help() {
  std::cout << "\n[h]elp:\n\n"
               "With a properly formatted flashcard deck, this program allows you to [d]raw a random flashcard to see its front.\n"
               "Then you can [s]how to see the contents on the back and remove the card from the deck.\n"
               "By [r]einserting the revealed card, it will remain in the deck instead.\n"
               "Once the deck is empty, all cards are reinserted automatically the next time you [d]raw.\n"
               "The deck can be [r]eset manually as well. To end the program, use [t]erminate.\n\n"
               "For more detail on each command, use [m]ore.\n"
               "For flashcard deck formatting instructions, use [f]lashcard deck formatting.\n" << std::endl;
}

// list of detailed descriptions of each command's function
void More() {
  std::cout << "\n[m]ore:\n\n" 
               "[d]raw: Removes previous [s]hown card from card pool unless it was re[i]nserted. Then, if the card pool is empty, automatically [r]esets it.\n"
               "Then selects a random card from card pool and prints the contents of the assigned \"front\" side.\n"
               "[s]how: If a card has been selected by the [d]raw command, prints the contents of assigned \"front\" and \"back\" sides of said card.\n"
               "re[i]nsert: Prevents the next [d]raw command from removing the currently selected card from the card pool.\n"
               "[r]eset: Changes the state of the card pool such that all flashcards are now in the card pool.\n"
               "number commands (eg: [0]): prints the contents of the corresponding side of the currently selected card. [0] corresponds to the first side of a flashcard\n" << std::endl;
}

// explains how to format a flashdeck and limitations
void FlashcardDeckFormatting() {
  std::cout << "How to format a custom flashdeck file:\n\n The first line of the file must be the following four numbers delimited by ' ' or ',' character:\n"
               "    1. The number of flashcards\n    2. The number of sides on all flashcards (note: all flashcards must have the same number of sides)\n"
               "    3. The number of the \"front\" side, the contents of which will be printed upon [d]raw or [s]how\n"
               "    4. The number of the \"back\" side, the contents of which will be printed upon [s]how.\n\n"
               "The subsequent lines of the file should contain the contents of a corresponding flashcard.\n"
               "The contents of each side of a flashcard should be separated by the '|' character."<< std::endl;
}