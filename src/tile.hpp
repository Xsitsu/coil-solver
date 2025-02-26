#ifndef TILE_HPP_INCLUDE
#define TILE_HPP_INCLUDE

class Tile
{
public:
    Tile();

    int GetNumberWalls() const;

    void SetConnectionUp(bool val);
    void SetConnectionDown(bool val);
    void SetConnectionLeft(bool val);
    void SetConnectionRight(bool val);
    void SetIsWall();

    bool HasConnectionUp() const;
    bool HasConnectionDown() const;
    bool HasConnectionLeft() const;
    bool HasConnectionRight() const;
    bool IsWall() const;
    bool IsValid() const;

private:
    bool connection_up;
    bool connection_down;
    bool connection_left;
    bool connection_right;

    bool is_wall;
    bool is_valid;

};


#endif // TILE_HPP_INCLUDE
