

#include piece.h

  Class King: public Piece {
    public:
      King(string colour, int curX, int curY);
      bool isValid(int endX, int endY);
  };

